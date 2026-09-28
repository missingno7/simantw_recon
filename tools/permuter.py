"""Randomized, source-preserving MSC 7.00 function search.

    python tools/permuter.py SOURCE.c --function _Symbol [--time-limit 900]
        [--iterations 100000] [--beam 8] [--seed N] [--allow-risky]
        [--only mutation,...] [--out build/permuter/SYMBOL_TIMESTAMP]

Only the requested function body is regenerated. Candidate batches go through the
assigned-profile compiler cache, strict member comparison, and codegen_diff diagnosis.
This is diagnostic tooling; it never publishes or promotes source.
"""
from __future__ import annotations

import argparse
import copy
import difflib
import hashlib
import json
import math
import random
import re
import sys
import time
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import c_source
import permuter_mutations as M
from common import relative

GOOD = {'CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'}
STEERING_MUTATIONS = {'register_toggle', 'introduce_temp', 'assign_in_cond', 'type_change'}


def digest(text: str) -> str:
    return hashlib.sha256(text.encode('ascii', 'strict')).hexdigest()


def source_function(source: str, requested: str) -> str:
    names = [f['name'] for f in c_source.top_level_functions(source)]
    candidates = (requested, requested.lstrip('_'), '_' + requested.lstrip('_'))
    found = [name for name in candidates if name in names]
    if not found:
        raise ValueError(f'{requested} has no matching top-level C function; found {names[:12]}')
    return found[0]


def _number(text):
    if text is None:
        return None
    token = text.strip().split()[0].rstrip('hH')
    try:
        return int(token, 0)
    except ValueError:
        try:
            return int(token, 10)
        except ValueError:
            return None


def frame_size(diagnostic):
    """Return the explicit BP frame allocation from the aligned prologue."""
    rows = diagnostic.get('aligned_asm') or []
    for row in rows[:8]:
        for side in ('target', 'candidate'):
            asm = (row.get(side) or '').strip().lower()
            match = re.match(r'enter\s+([^,]+)', asm)
            if match:
                return side, _number(match.group(1))
            match = re.match(r'sub\s+sp,\s*([^,]+)', asm)
            if match:
                return side, _number(match.group(1))
    return None


def _fixup_noise(row):
    target = (row.get('target') or '').lower()
    candidate = (row.get('candidate') or '').lower()
    differences = set(row.get('differences') or [])
    if not differences:
        return False
    allowed = {'memory_operand', 'immediate_or_binding', 'alignment_uncertain'}
    rendered = 'resolved fixup' in target or 'resolved fixup' in candidate
    selector = 'es:[' in target or 'es:[' in candidate
    return differences <= allowed and (rendered or selector)


def score(comparison):
    """Strict result first, then frame, divergence position and aligned diagnostic cost."""
    diagnostic = comparison.get('diagnostic') or {}
    rows = diagnostic.get('aligned_asm') or []
    first, cost = None, 0.0
    for index, row in enumerate(rows):
        differences = set(row.get('differences') or [])
        if not differences or _fixup_noise(row):
            continue
        if first is None:
            first = index
        if 'instruction_shape' in differences:
            cost += 1.0
        else:
            if differences & {'register_allocation', 'register_role', 'call_frame_or_segment_register'}:
                cost += 0.35
            if differences & {'stack_local_layout', 'memory_operand'}:
                cost += 0.5
            if differences & {'branch_target'}:
                cost += 0.4
            if differences & {'immediate_or_binding'}:
                cost += 0.25
            if not differences & {'register_allocation', 'register_role', 'call_frame_or_segment_register',
                                 'stack_local_layout', 'memory_operand', 'branch_target',
                                 'immediate_or_binding'}:
                cost += 1.0
    if first is None:
        first = len(rows) + 1
    frames = {}
    for row in rows[:8]:
        for side in ('target', 'candidate'):
            asm = (row.get(side) or '').strip().lower()
            match = re.match(r'enter\s+([^,]+)', asm)
            if match:
                frames[side] = _number(match.group(1))
            else:
                match = re.match(r'sub\s+sp,\s*([^,]+)', asm)
                if match:
                    frames[side] = _number(match.group(1))
    frame_equal = frames.get('target') == frames.get('candidate') if frames else True
    strict_exact = comparison.get('result') in GOOD and diagnostic.get('exact_match') is True
    if comparison.get('result') == 'COMPILE_FAILED' or not diagnostic:
        frame_equal, first, cost = False, 0, 1_000_000.0
    opcode_matches = int(diagnostic.get('opcode_matches') or 0)
    return {
        'strict_exact': strict_exact,
        'strict_result': comparison.get('result'),
        'frame_equal': frame_equal,
        'target_frame': frames.get('target'),
        'candidate_frame': frames.get('candidate'),
        'first_divergence_row': first,
        'aligned_cost': round(cost, 4),
        'opcode_matches': opcode_matches,
        'opcode_total': int(diagnostic.get('opcode_total') or 0),
        'candidate_bytes': diagnostic.get('candidate_bytes'),
        'target_bytes': diagnostic.get('target_bytes'),
        'register_differences': diagnostic.get('register_only_differences'),
        'stack_differences': diagnostic.get('stack_local_differences'),
        'branch_differences': diagnostic.get('branch_target_differences'),
        'categories': diagnostic.get('categories') or [],
        'first_structural_difference': diagnostic.get('first_structural_difference'),
    }


def rank(value):
    return (int(value['strict_exact']), int(value['frame_equal']), value['first_divergence_row'],
            -value['aligned_cost'], value['opcode_matches'])


def improves(candidate, incumbent):
    if incumbent is None:
        return True
    if candidate['strict_exact'] != incumbent['strict_exact']:
        return candidate['strict_exact']
    if candidate['frame_equal'] != incumbent['frame_equal']:
        return candidate['frame_equal']
    return (candidate['first_divergence_row'] > incumbent['first_divergence_row'] or
            candidate['aligned_cost'] < incumbent['aligned_cost'])


def mutation_kind(description):
    return (description.split(':', 1)[0].split('(', 1)[0]).strip()


def classify_chain(chain):
    kinds = {mutation_kind(x) for x in chain}
    steering = sorted(kinds & STEERING_MUTATIONS)
    return ('STEERED' if steering else 'NATURAL', steering)


def masked_member_signature(receipt, symbol):
    """Hash emitted member bytes after masking only the candidate's OMF fixup fields."""
    object_name = receipt.get('object')
    if not object_name:
        return None
    try:
        import omf
        module = omf.parse((ROOT / object_name).read_bytes())
        pubs = [p for p in module['publics'] if p['name'] == symbol]
        if len(pubs) != 1:
            return None
        public = pubs[0]
        segno = public['segment']
        code = bytes.fromhex(module['segments'][segno - 1]['data_hex'])
        begin = public['offset']
        end = min([p['offset'] for p in module['publics']
                   if p['segment'] == segno and p['offset'] > begin] + [len(code)])
        member = bytearray(code[begin:end])
        for fixup in module.get('fixups', []):
            if fixup.get('segment') != segno:
                continue
            at = fixup['offset'] - begin
            for i in range(max(0, at), min(len(member), at + fixup.get('width', 2))):
                member[i] = 0
        return hashlib.sha256(member).hexdigest()
    except Exception:
        return (receipt.get('object_identity') or {}).get('sha256')


QUALIFIER = re.compile(r'\b(volatile|far|_far|__far)\b')


def qualifier_drift(baseline, variant):
    """True when a variant has more `volatile` or fewer `far` tokens than the baseline source."""
    def counts(text):
        found = QUALIFIER.findall(re.sub(r'/\*.*?\*/|//[^\n]*', ' ', text, flags=re.S))
        return found.count('volatile'), len(found) - found.count('volatile')
    bv, bf = counts(baseline)
    vv, vf = counts(variant)
    return vv > bv or vf < bf


@dataclass
class Entry:
    identifier: int
    source: str
    body: object
    score: dict
    comparison: dict
    chain: list[str]
    parent: int | None
    signature: str | None = None
    duplicate_output: bool = False


class DedupeIndex:
    """Deduplicate source text and fixup-masked member bytes independently."""
    def __init__(self):
        self.sources = set()
        self.outputs = set()

    def add_source(self, source):
        key = digest(source)
        fresh = key not in self.sources
        self.sources.add(key)
        return fresh

    def add_output(self, signature):
        if not signature:
            return True
        fresh = signature not in self.outputs
        self.outputs.add(signature)
        return fresh


class Permuter:
    def __init__(self, source_path, symbol, args):
        from promote import function_flags
        self.symbol = symbol
        self.args = args
        self.source_path = Path(source_path).resolve()
        self.original = self.source_path.read_text(encoding='ascii')
        self.function = source_function(self.original, symbol)
        self.codec = M.BodyCodec(self.original, self.function)
        self.flags_profile, self.flags = function_flags(symbol)
        self.rng = random.Random(args.seed)
        self.started = time.perf_counter()
        stamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        out = Path(args.out).resolve() if args.out else ROOT / 'build' / 'permuter' / f'{symbol}_{stamp}'
        if not out.is_relative_to(ROOT / 'build' / 'permuter'):
            raise ValueError('output must stay under build/permuter/')
        self.out = out
        self.out.mkdir(parents=True, exist_ok=True)
        (self.out / 'batches').mkdir(exist_ok=True)
        (self.out / 'baseline.c').write_text(self.original, encoding='ascii')
        self.regenerated = self.codec.splice(self.codec.render(copy.deepcopy(self.codec.body)))
        (self.out / 'regenerated_baseline.c').write_text(self.regenerated, encoding='ascii')
        self.counts = {'evaluations': 0, 'compiler_misses': 0, 'compile_errors': 0,
                       'duplicate_source': 0, 'duplicate_output': 0, 'no_mutation': 0,
                       'hygiene_rejected': 0}
        self.dedupe = DedupeIndex()
        self.variant_log = (self.out / 'variants.jsonl').open('w', encoding='utf-8')
        self.batch_no = 0
        self.next_id = 1
        self.baseline_original = None
        self.baseline_regenerated = None
        self.best = None
        self.beam = []
        self.history = []
        self.improvements = []

    def _run_batch(self, rows, phase='search'):
        if not rows:
            return []
        import codegen_grinder
        self.batch_no += 1
        directory = self.out / 'batches' / f'{phase}_{self.batch_no:05d}'
        spec = {'symbol': self.symbol, 'compiler': 'msc700', 'flags': self.flags,
                'sources': [row['source'] for row in rows], 'max_candidates': len(rows)}
        report = codegen_grinder.run(spec, relative(directory), cache=True)
        self.counts['evaluations'] += len(rows)
        self.counts['compiler_misses'] += report.get('cache', {}).get('misses', 0)
        by_index = {row['candidate']: row for row in report['results']}
        result = []
        for index, original in enumerate(rows):
            record = by_index.get(index)
            if record is None:
                continue
            comparison = record.get('comparison') or {}
            value = score(comparison)
            signature = masked_member_signature(record.get('receipt') or {}, self.symbol)
            result.append((original, record, value, signature))
        return result

    def _record(self, entry, record, value, signature, phase='search'):
        receipt = record.get('receipt') or {}
        result = record.get('comparison') or {}
        row = {'id': entry.identifier, 'parent': entry.parent, 'phase': phase,
               'mutations': entry.chain, 'mutation_kinds': [mutation_kind(x) for x in entry.chain],
               'source_sha256': digest(entry.source), 'masked_member_sha256': signature,
               'strict_result': value['strict_result'], 'score': value,
               'cache_hit': not bool(receipt.get('object')) or receipt.get('timing', {}).get('cache_hit'),
               'compile_exit_code': receipt.get('exit_code'),
               'compiler_log_tail': (receipt.get('stdout') or '')[-800:] if not receipt.get('exit_code') else None}
        self.variant_log.write(json.dumps(row, sort_keys=True) + '\n')
        self.variant_log.flush()
        self.counts['compile_errors'] += int(value['strict_result'] == 'COMPILE_FAILED')
        if signature:
            duplicate = not self.dedupe.add_output(signature)
            if duplicate:
                self.counts['duplicate_output'] += 1
        else:
            duplicate = False
        return Entry(entry.identifier, entry.source, entry.body, value, result,
                     entry.chain, entry.parent, signature, duplicate)

    def evaluate_baselines(self):
        candidates = [
            {'id': 0, 'parent': None, 'chain': [], 'body': copy.deepcopy(self.codec.body), 'source': self.original},
            {'id': 1, 'parent': None, 'chain': [], 'body': copy.deepcopy(self.codec.body), 'source': self.regenerated},
        ]
        for candidate in candidates:
            self.dedupe.add_source(candidate['source'])
        evaluated = self._run_batch(candidates, 'baseline')
        for item, record, value, signature in evaluated:
            entry = self._record(Entry(item['id'], item['source'], item['body'], value,
                                       record['comparison'], [], None), record, value,
                                 signature, 'baseline')
            if item['id'] == 0:
                self.baseline_original = entry
            else:
                self.baseline_regenerated = entry
        root = self.baseline_original or self.baseline_regenerated
        self.best = root
        self.beam = [root]
        self.history = [{'elapsed_seconds': 0, 'id': root.identifier,
                         'first_divergence_row': root.score['first_divergence_row'],
                         'aligned_cost': root.score['aligned_cost']}]
        print(f"[permuter] {self.symbol} profile={self.flags_profile['name']} baseline="
              f"{self.baseline_original.score if self.baseline_original else 'failed'}", flush=True)
        print(f"[permuter] AST round-trip={self.baseline_regenerated.score if self.baseline_regenerated else 'failed'}",
              flush=True)

    def _child(self, parent):
        body = copy.deepcopy(parent.body)
        chain = list(parent.chain)
        descriptions = []
        count = self.rng.choices([1, 2, 3], [0.62, 0.28, 0.10])[0]
        for _ in range(count):
            description = M.mutate(body, self.rng, allow_risky=self.args.allow_risky,
                                   only=self.allowed_mutations, tries=20)
            if description:
                descriptions.append(description)
        if not descriptions:
            self.counts['no_mutation'] += 1
            return None
        problems = set(M.local_hygiene(body)) - self.base_problems
        if problems:
            self.counts['hygiene_rejected'] += 1
            return None
        try:
            body_text = self.codec.render(body)
            text = self.codec.splice(body_text)
        except Exception:
            return None
        if qualifier_drift(self.regenerated, text):
            # The parser maps MSC `far` onto `volatile`; a mutation that creates a declaration
            # without source-position metadata can emit `volatile` where `far` was meant
            # (f-perm-07 _DoSow, 2026-09-28). No mutation may add `volatile` or drop `far`.
            self.counts['qualifier_rejected'] = self.counts.get('qualifier_rejected', 0) + 1
            return None
        if not self.dedupe.add_source(text):
            self.counts['duplicate_source'] += 1
            return None
        identifier = self.next_id
        self.next_id += 1
        return {'id': identifier, 'parent': parent.identifier, 'body': body,
                'source': text, 'chain': chain + descriptions}

    def _select_beam(self, entry, parent):
        if entry.duplicate_output:
            return
        if improves(entry.score, self.best.score):
            old = self.best
            self.best = entry
            self.history.append({'elapsed_seconds': round(time.perf_counter() - self.started, 2),
                                 'id': entry.identifier,
                                 'first_divergence_row': entry.score['first_divergence_row'],
                                 'aligned_cost': entry.score['aligned_cost']})
            self.improvements.append({'id': entry.identifier, 'parent': parent.identifier,
                                      'from': old.score, 'to': entry.score,
                                      'mutations': entry.chain})
            (self.out / 'best.c').write_text(entry.source, encoding='ascii')
            print(f"[permuter] #{entry.identifier}: first row {old.score['first_divergence_row']} -> "
                  f"{entry.score['first_divergence_row']}, cost {old.score['aligned_cost']} -> "
                  f"{entry.score['aligned_cost']}; {'; '.join(entry.chain[-3:])}", flush=True)
        if len(self.beam) < self.args.beam:
            self.beam.append(entry)
            return
        worst = max(self.beam, key=lambda x: rank(x.score))
        if rank(entry.score) > rank(worst.score):
            self.beam.remove(worst)
            self.beam.append(entry)
        elif (rank(entry.score) == rank(parent.score) and self.rng.random() < 0.25) or \
                (entry.score['aligned_cost'] >= self.best.score['aligned_cost'] and self.rng.random() < 0.08):
            victims = [x for x in self.beam if x is not self.best]
            if victims:
                self.beam.remove(self.rng.choice(victims))
                self.beam.append(entry)

    def search(self):
        self.base_problems = set(M.local_hygiene(self.codec.body))
        self.allowed_mutations = set(self.args.only.split(',')) if self.args.only else None
        self.evaluate_baselines()
        (self.out / 'best.c').write_text(self.best.source, encoding='ascii')
        if self.best.score['strict_exact'] and not self.args.keep_going:
            return
        began = time.perf_counter()
        while self.counts['evaluations'] < self.args.iterations:
            elapsed = time.perf_counter() - began
            if elapsed >= self.args.time_limit:
                break
            batch = []
            attempts = 0
            while len(batch) < self.args.batch_size and attempts < self.args.batch_size * 30:
                attempts += 1
                parent = self.best if self.rng.random() < 0.42 else self.rng.choice(self.beam)
                child = self._child(parent)
                if child:
                    batch.append(child)
            if not batch:
                print('[permuter] no mutation applicable in this beam; stopping', flush=True)
                break
            evaluated = self._run_batch(batch)
            entries_by_id = {x['id']: x for x in batch}
            for item, record, value, signature in evaluated:
                entry = self._record(Entry(item['id'], item['source'], item['body'], value,
                                           record['comparison'], item['chain'], item['parent']),
                                     record, value, signature)
                parent = next((x for x in self.beam + [self.best]
                               if x.identifier == item['parent']), self.best)
                self._select_beam(entry, parent)
            if self.best.score['strict_exact'] and not self.args.keep_going:
                break
        (self.out / 'best.c').write_text(self.best.source, encoding='ascii')

    def minimize(self):
        baseline = self.baseline_original.source if self.baseline_original else self.regenerated
        before = baseline.splitlines(keepends=True)
        after = self.best.source.splitlines(keepends=True)
        changes = [op for op in difflib.SequenceMatcher(a=before, b=after,
                    autojunk=False).get_opcodes() if op[0] != 'equal']

        def build(keep):
            out, cursor = [], 0
            for index, (_tag, a1, a2, b1, b2) in enumerate(changes):
                out.extend(before[cursor:a1])
                out.extend(after[b1:b2] if index in keep else before[a1:a2])
                cursor = a2
            out.extend(before[cursor:])
            return ''.join(out)

        keep = set(range(len(changes)))
        target_rank = rank(self.best.score)
        compiles = 0
        rounds = 0
        for _ in range(6):
            if not keep:
                break
            trials = []
            for idx in sorted(keep):
                text = build(keep - {idx})
                try:
                    fc = M.BodyCodec(text, self.function)
                    body = fc.body
                    if set(M.local_hygiene(body)) - self.base_problems:
                        continue
                except Exception:
                    continue
                trials.append({'id': self.next_id, 'parent': self.best.identifier,
                               'chain': self.best.chain, 'body': body, 'source': text,
                               'removed_hunk': idx})
                self.next_id += 1
            if not trials:
                break
            evaluated = self._run_batch(trials, 'minimize')
            compiles += len(trials)
            rounds += 1
            for item, record, value, signature in evaluated:
                self._record(Entry(item['id'], item['source'], item['body'], value,
                                   record['comparison'], item['chain'], item['parent']),
                             record, value, signature, 'minimize')
            accepted = [x for x in evaluated if rank(x[2]) >= target_rank]
            if not accepted:
                break
            # Take one independently unnecessary hunk at a time, then re-check
            # the interactions against the updated compact source.
            item, record, value, signature = accepted[0]
            keep.remove(item['removed_hunk'])
        final_source = build(keep)
        if final_source != self.best.source:
            verified = self._run_batch([{'id': self.next_id, 'parent': self.best.identifier,
                          'chain': self.best.chain, 'body': self.best.body,
                          'source': final_source}], 'minimize_final')
            compiles += 1
            if verified:
                item, record, value, signature = verified[0]
                self._record(Entry(item['id'], item['source'], item['body'], value,
                                   record['comparison'], item['chain'], item['parent']),
                             record, value, signature, 'minimize_final')
            if verified and rank(verified[0][2]) >= target_rank:
                final_score = verified[0][2]
            else:
                final_source = self.best.source
                final_score = self.best.score
        else:
            final_score = self.best.score
        (self.out / 'best_min.c').write_text(final_source, encoding='ascii')
        diff = ''.join(difflib.unified_diff(before, final_source.splitlines(keepends=True),
                                            fromfile='baseline_body', tofile='best_min', n=1))
        (self.out / 'best_min.diff').write_text(diff, encoding='ascii')
        return {'diff_hunks': len(changes), 'hunks_retained': len(keep), 'rounds': rounds,
                'candidate_compiles': compiles, 'score': final_score}

    def finish(self, minimization):
        self.variant_log.close()
        elapsed = time.perf_counter() - self.started
        natural_class, steering = classify_chain(self.best.chain)
        exact_path = None
        if self.best.score['strict_exact']:
            exact_path = self.out / f'{self.symbol}_exact.c'
            exact_path.write_text(self.best.source, encoding='ascii')
            (self.out / f'{self.symbol}_exact.json').write_text(json.dumps({
                'symbol': self.symbol, 'strict_result': self.best.score['strict_result'],
                'source_class': natural_class, 'steering_mutations': steering,
                'mutation_chain': self.best.chain,
                'whole_member_comparison': self.best.comparison,
                'note': 'DIAGNOSTIC_ONLY; independent verify/admission is required.'}, indent=2), encoding='utf-8')
        best_diag = (self.best.comparison or {}).get('diagnostic') or {}
        baseline_score = (self.baseline_original.score if self.baseline_original else {})
        summary = {
            'symbol': self.symbol, 'function': self.function, 'input': str(self.source_path),
            'profile': self.flags_profile['name'], 'flags': self.flags,
            'elapsed_seconds': round(elapsed, 2), 'seed': self.args.seed,
            'time_limit_seconds': self.args.time_limit, 'iteration_limit': self.args.iterations,
            'counts': self.counts,
            'candidate_evaluations_per_second': round(self.counts['evaluations'] / max(elapsed, 0.001), 3),
            'compiler_misses_per_second': round(self.counts['compiler_misses'] / max(elapsed, 0.001), 3),
            'duplicate_source_rate': round(self.counts['duplicate_source'] / max(self.counts['evaluations'] + self.counts['duplicate_source'], 1), 4),
            'duplicate_output_rate': round(self.counts['duplicate_output'] / max(self.counts['evaluations'], 1), 4),
            'baseline': baseline_score, 'regenerated_baseline': self.baseline_regenerated.score if self.baseline_regenerated else None,
            'best': self.best.score, 'baseline_to_best_earliest_movement':
                self.best.score['first_divergence_row'] - baseline_score.get('first_divergence_row', 0)
                if baseline_score else None,
            'best_chain': self.best.chain, 'best_source_class': natural_class,
            'steering_mutations': steering, 'exact_source': str(exact_path) if exact_path else None,
            'minimization': minimization, 'history': self.history, 'improvements': self.improvements,
            'diagnostic_categories': best_diag.get('categories'),
            'promotion': 'NONE: strict comparison is diagnostic; no source was promoted.',
        }
        (self.out / 'summary.json').write_text(json.dumps(summary, indent=2), encoding='utf-8')
        print(f"[permuter] done {self.symbol}: {self.counts['evaluations']} evaluations in {elapsed:.1f}s, "
              f"{self.counts['compiler_misses']} compiler misses, best={self.best.score}, "
              f"class={natural_class}, exact={bool(exact_path)}", flush=True)
        print(f'[permuter] outputs: {self.out}', flush=True)
        return summary

    def close(self):
        if not self.variant_log.closed:
            self.variant_log.close()


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('source', help='whole TU or candidate source containing the target function')
    parser.add_argument('--function', required=True, help='MAPSYM symbol, including leading underscore')
    parser.add_argument('--time-limit', type=float, default=600.0)
    parser.add_argument('--iterations', type=int, default=100000)
    parser.add_argument('--batch-size', type=int, default=48)
    parser.add_argument('--beam', type=int, default=8)
    parser.add_argument('--seed', type=int, default=None)
    parser.add_argument('--allow-risky', action='store_true')
    parser.add_argument('--only', help='comma-separated mutation names')
    parser.add_argument('--keep-going', action='store_true')
    parser.add_argument('--no-minimize', action='store_true')
    parser.add_argument('--out')
    args = parser.parse_args(argv)
    args.seed = args.seed if args.seed is not None else random.SystemRandom().randrange(1 << 30)
    if args.batch_size < 1 or args.batch_size > 256:
        parser.error('--batch-size must be between 1 and 256')
    if args.beam < 1:
        parser.error('--beam must be positive')
    worker = Permuter(args.source, args.function, args)
    try:
        worker.search()
        minimized = None if args.no_minimize else worker.minimize()
        worker.finish(minimized)
    finally:
        worker.close()
    return 0


if __name__ == '__main__':
    raise SystemExit(main())

"""Cluster open functions by the compiler symptom at their earliest meaningful divergence.

    python tools/residue_clusters.py [--min 0.8] [--json OUT]

For every open GAME function whose best preserved draft reaches the --min opcode ratio, the aligned
diagnostic of that draft is walked from the top. Rows whose only differences are operands rendered as
fixups (relocation/selector placement) are skipped as layout noise. The first remaining row is
classified:

  FRAME_SIZE            the ENTER/`sub sp` frame size differs
  SIGNEDNESS            jl/jg/jle/jge versus jb/ja/jbe/jae on the same compare
  CFG_DESTINATION       a branch lands on a different aligned instruction (search.py branch_destinations)
  BLOCK_ORDER           an inserted/missing jmp/jcc or a branch-target-only difference
  WRONG_REGISTER        same instruction, only register choice differs
  WRONG_STACK_SLOT      same instruction, only the [bp-N] home differs
  RELOAD_OR_SPILL       a load from / store to a BP home present on one side only
  FAR_POINTER           LES/LDS, `mov es,`, `push es:[..]` or a saved selector present on one side only
  FLAG_TEST             an `or r,r`/`test`/`cmp` present on one side only
  EXPRESSION_SHAPE      a different arithmetic/addressing instruction (strength reduction, CSE, operand order)
  CALL_SEQUENCE         argument pushes or call form differ
  RELOCATION_ONLY       all opcodes match; only fixup/placement operands differ

This is a routing diagnostic: it names the first compiler decision to explain, never a proof.
"""
import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, cards, recipes, write_json
from codegen_diff import branch_destinations

SIGNED = {'jl', 'jg', 'jle', 'jge', 'jnge', 'jnle', 'jnl', 'jng'}
UNSIGNED = {'jb', 'ja', 'jbe', 'jae', 'jnae', 'jnbe', 'jnb', 'jna', 'jc', 'jnc'}
NOISE = {'memory_operand', 'immediate_or_binding', 'alignment_uncertain'}


def op(text):
    return (text or '').strip().split(' ', 1)


def fixup_text(text):
    return 'resolved fixup' in (text or '')


def classify(rows):
    dests = {d['target_offset'] for d in branch_destinations(rows)}
    for i, r in enumerate(rows):
        diffs = set(r.get('differences') or [])
        if not diffs:
            continue
        t, c = r.get('target'), r.get('candidate')
        tm, cm = op(t)[0] if t else None, op(c)[0] if c else None
        # Operand-only differences where either side is a rendered fixup: placement noise.
        if t and c and tm == cm and diffs <= NOISE and (fixup_text(t) or fixup_text(c) or 'es:[' in (t + c)):
            continue
        if i < 3 and tm == cm == 'enter' or (tm == cm == 'sub' and 'sp' in (t or '')):
            return 'FRAME_SIZE', i, r
        if r.get('target_offset') in dests:
            return 'CFG_DESTINATION', i, r
        if tm and cm and tm != cm and ({tm, cm} <= SIGNED | UNSIGNED) and (tm in SIGNED) != (cm in SIGNED):
            return 'SIGNEDNESS', i, r
        if tm == cm:
            if diffs <= {'register_allocation', 'register_role'}:
                return 'WRONG_REGISTER', i, r
            if diffs <= {'stack_local_layout', 'memory_operand'} and '[bp' in (t or '') and '[bp' in (c or ''):
                return 'WRONG_STACK_SLOT', i, r
            if diffs == {'branch_target'}:
                return 'BLOCK_ORDER', i, r
            if tm in ('push', 'call', 'lcall'):
                return 'CALL_SEQUENCE', i, r
            return 'EXPRESSION_SHAPE', i, r
        one = t or c
        mnem = op(one)[0]
        text = one or ''
        if mnem in ('les', 'lds') or text.startswith('mov es,') or 'es:[' in text and mnem == 'push' or re.match(r'mov word ptr \[bp - [^\]]+\], (es|ds)', text):
            return 'FAR_POINTER', i, r
        if mnem.startswith('j') or mnem in ('jmp', 'nop'):
            return 'BLOCK_ORDER', i, r
        if mnem in ('or', 'test', 'cmp') and (mnem != 'or' or len(set(op(text)[1].replace(' ', '').split(','))) == 1):
            return 'FLAG_TEST', i, r
        if '[bp' in text and mnem == 'mov':
            return 'RELOAD_OR_SPILL', i, r
        if mnem in ('push', 'call', 'lcall', 'add') and ('sp' in text or mnem != 'add'):
            return 'CALL_SEQUENCE', i, r
        return 'EXPRESSION_SHAPE', i, r
    return 'RELOCATION_ONLY', None, None


def best_rows(entry):
    """Aligned rows of the frontier draft (latest earliest divergence) when recorded, else the best draft."""
    best = entry.get('frontier') or entry.get('best') or {}
    try:
        results = json.load(open(ROOT / best['origin'], encoding='utf-8'))['results']
    except (OSError, ValueError, KeyError, TypeError):
        return None, best
    row = None
    if best.get('candidate') is not None:
        row = next((r for r in results if r.get('candidate') == best['candidate']), None)
    row = row or next((r for r in results if (r['comparison'].get('diagnostic') or {}).get('opcode_matches') == best.get('opcode_matches')), None)
    return ((row or {}).get('comparison', {}).get('diagnostic') or {}).get('aligned_asm'), best


def cluster(minimum=0.8):
    adm = recipes()
    by_symbol = {c['symbol']: c for c in cards()}
    ledger = json.load(open(ROOT / 'evidence/recovery/drafts/index.json', encoding='utf-8'))
    out = {}
    for key, entry in ledger.items():
        symbol = key if key in by_symbol else '_' + key
        if symbol in adm or symbol not in by_symbol or by_symbol[symbol].get('ownership') != 'GAME':
            continue
        rows, best = best_rows(entry)
        m, t = best.get('opcode_matches'), best.get('opcode_total')
        if not rows or not m or not t or m / t < minimum:
            continue
        kind, index, row = classify(rows)
        out.setdefault(kind, []).append(dict(symbol=symbol, opcodes='%d/%d' % (m, t), ratio=round(m / t, 3),
                                             bytes='%s/%s' % (best.get('candidate_bytes'), best.get('target_bytes')),
                                             first_row=index, target=(row or {}).get('target'), candidate=(row or {}).get('candidate'),
                                             draft=best.get('source')))
    for rows in out.values():
        rows.sort(key=lambda r: -r['ratio'])
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--min', type=float, default=0.8)
    ap.add_argument('--json')
    args = ap.parse_args()
    clusters = cluster(args.min)
    if args.json:
        write_json(Path(args.json), clusters)
    total = sum(len(v) for v in clusters.values())
    print('%d open functions at >= %.0f%% opcodes' % (total, args.min * 100))
    for kind, rows in sorted(clusters.items(), key=lambda kv: -len(kv[1])):
        print('\n%s (%d)' % (kind, len(rows)))
        for r in rows:
            print('  %-26s %-9s %-9s  T: %-38s C: %s' % (r['symbol'], r['opcodes'], r['bytes'], (r['target'] or '-')[:38], (r['candidate'] or '-')[:38]))


if __name__ == '__main__':
    main()

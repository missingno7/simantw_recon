"""Durable best readable draft per function, plus free-form investigation notes.

Scratch search output stays in ignored build/search/. The best draft of each
symbol is copied here so unit assembly and later investigators can use it from
a fresh checkout. The rank is a diagnostic ordering, never recovery proof.
"""
import shutil
from common import ROOT, identity, read_json, write_json
from publication import file_lock, timestamp

DRAFTS = ROOT / 'evidence/recovery/drafts'
INDEX = DRAFTS / 'index.json'
LOCK = ROOT / 'build/locks/drafts.lock'
GOOD = ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')


def rank(comparison):
    """(strict, exact body, aligned opcodes, -size delta): the ordering unit assembly uses."""
    from tu_assembly import body_exact
    d = comparison.get('diagnostic') or {}
    if d.get('opcode_matches') is None:
        return None
    return [comparison.get('result') in GOOD, body_exact(comparison), d['opcode_matches'], -abs(d.get('candidate_bytes', 0) - d.get('target_bytes', 0))]


def load():
    return read_json(INDEX) if INDEX.exists() else {}


def entry(symbol):
    return load().get(symbol) or {}


def lock():
    return file_lock(LOCK, 120, 'draft ledger is busy')


def frontier_rank(comparison):
    """(strict, exact body, earliest meaningful divergence row, aligned opcodes).

    The row comes from residue_clusters.classify (fixup-only placement rows skipped). A draft
    that fixes an EARLIER compiler decision (e.g. the frame) ranks higher than one that only
    matches more opcodes further down, even if its opcode count is lower."""
    from tu_assembly import body_exact
    from residue_clusters import classify
    d = comparison.get('diagnostic') or {}
    rows = d.get('aligned_asm') or []
    if d.get('opcode_matches') is None or not rows:
        return None
    _, index, _ = classify(rows)
    return [comparison.get('result') in GOOD, body_exact(comparison), len(rows) + 1 if index is None else index, d['opcode_matches']]


def _store_frontier(row, symbol, source_path, digest, comparison, origin, flags, candidate):
    key = frontier_rank(comparison)
    front = row.get('frontier')
    if key is None or (front and (front.get('sha256') == digest or key <= front.get('key', []))):
        return False
    d = comparison.get('diagnostic') or {}
    destination = DRAFTS / symbol.lstrip('_') / (digest[:12] + '.c')
    destination.parent.mkdir(parents=True, exist_ok=True)
    if not destination.exists():
        shutil.copyfile(source_path, destination)
    row['frontier'] = dict(source=destination.relative_to(ROOT).as_posix(), sha256=digest, key=key, first_divergence_row=key[2],
                           opcode_matches=d.get('opcode_matches'), opcode_total=d.get('opcode_total'),
                           candidate_bytes=d.get('candidate_bytes'), target_bytes=d.get('target_bytes'),
                           flags=flags, origin=origin, candidate=candidate, recorded=timestamp())
    return True


def store(symbol, source_path, comparison, origin, flags, basis=None, candidate=None):
    """Keep source_path as the symbol's best draft when it outranks the stored one, and as its
    frontier draft when its earliest meaningful divergence is later than the stored frontier's."""
    key = rank(comparison)
    if key is None:
        return False
    d = comparison.get('diagnostic') or {}
    digest = identity(source_path)['sha256']
    with lock():
        ledger = load()
        row = ledger.setdefault(symbol, {})
        if _store_frontier(row, symbol, source_path, digest, comparison, origin, flags, candidate):
            write_json(INDEX, dict(sorted(ledger.items())))
        best = row.get('best')
        if best and best['sha256'] == digest:
            return False
        if best and best.get('key') and key <= best['key']:
            return False
        destination = DRAFTS / symbol.lstrip('_') / (digest[:12] + '.c')
        destination.parent.mkdir(parents=True, exist_ok=True)
        if not destination.exists():
            shutil.copyfile(source_path, destination)
        row['best'] = dict(source=destination.relative_to(ROOT).as_posix(), sha256=digest, key=key,
                           basis=basis or ('EXACT_BODY_CANDIDATE' if key[1] else 'BEST_CANDIDATE_NOT_EXACT'),
                           result=comparison.get('result'), opcode_matches=d.get('opcode_matches'), opcode_total=d.get('opcode_total'),
                           candidate_bytes=d.get('candidate_bytes'), target_bytes=d.get('target_bytes'), flags=flags, origin=origin, recorded=timestamp())
        write_json(INDEX, dict(sorted(ledger.items())))
        return True


def note(symbol, text, origin='investigator'):
    with lock():
        ledger = load()
        ledger.setdefault(symbol, {}).setdefault('notes', []).append(dict(text=text, origin=origin, recorded=timestamp()))
        write_json(INDEX, dict(sorted(ledger.items())))


def best_source(symbol):
    best = entry(symbol).get('best')
    return ROOT / best['source'] if best else None

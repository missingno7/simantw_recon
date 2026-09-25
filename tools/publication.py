"""Single-writer publication of the canonical recovery state.

One OS lock serializes promotions; a journal restores every core file if a
publication is interrupted. Scratch search never takes this lock.
"""
import base64
import json
import os
import time
from contextlib import contextmanager
from datetime import datetime, timezone
from common import ROOT, FormatError, read_json, sha256

CORE = ['src/recovery.json', 'build/recovered/manifest.json', 'build/recovery/verified-objects.json', 'docs/progress.json']
JOURNAL = ROOT / 'build/publication.json'
LOCK = ROOT / 'build/publication.lock'


def timestamp():
    return datetime.now(timezone.utc).isoformat()


def atomic_bytes(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + '.publication-tmp')
    temporary.write_bytes(data)
    temporary.replace(path)


def atomic_json(path, value):
    atomic_bytes(path, (json.dumps(value, indent=2) + '\n').encode())


@contextmanager
def file_lock(path, timeout, message):
    """Exclusive OS file lock; waits up to timeout seconds (0 = non-blocking)."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('a+b') as handle:
        handle.seek(0); handle.write(b'0'); handle.flush()
        deadline = time.monotonic() + timeout
        while True:
            handle.seek(0)
            try:
                if os.name == 'nt':
                    import msvcrt
                    msvcrt.locking(handle.fileno(), msvcrt.LK_NBLCK, 1)
                else:
                    import fcntl
                    fcntl.flock(handle.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
                break
            except OSError as exc:
                if time.monotonic() >= deadline:
                    raise FormatError(message) from exc
                time.sleep(0.05)
        try:
            yield
        finally:
            handle.seek(0)
            if os.name == 'nt':
                msvcrt.locking(handle.fileno(), msvcrt.LK_UNLCK, 1)
            else:
                fcntl.flock(handle.fileno(), fcntl.LOCK_UN)


def publication_lock(timeout=900):
    return file_lock(LOCK, timeout, 'another promotion holds the publication lock')


def recover():
    """Roll back a prepared-but-uncommitted publication. Refuses to overwrite unrelated edits."""
    if not JOURNAL.exists():
        return dict(status='NO_JOURNAL')
    journal = read_json(JOURNAL)
    if journal['status'] != 'PREPARED':
        return dict(status=journal['status'])
    if set(journal['old']) != set(CORE):
        raise FormatError('invalid publication journal')
    for name in CORE:
        path = ROOT / name
        current = sha256(path.read_bytes()) if path.exists() else None
        old = base64.b64decode(journal['old'][name]) if journal['old'][name] is not None else None
        if current not in (journal['new'][name], sha256(old) if old is not None else None):
            raise FormatError('publication journal conflicts with a later edit of ' + name + '; resolve against ' + JOURNAL.relative_to(ROOT).as_posix())
    for name in CORE:
        old = journal['old'][name]
        if old is None:
            (ROOT / name).unlink(missing_ok=True)
        else:
            atomic_bytes(ROOT / name, base64.b64decode(old))
    journal['status'] = 'ROLLED_BACK_AFTER_INTERRUPTION'
    atomic_json(JOURNAL, journal)
    return dict(status=journal['status'])


def commit(values, label):
    """Write every core file or none; the journal names the publication."""
    if set(values) != set(CORE):
        raise FormatError('incomplete publication')
    encoded = {p: (json.dumps(v, indent=2) + '\n').encode() for p, v in values.items()}
    old = {p: base64.b64encode((ROOT / p).read_bytes()).decode() if (ROOT / p).exists() else None for p in CORE}
    journal = dict(status='PREPARED', created=timestamp(), label=label, new={p: sha256(data) for p, data in encoded.items()}, old=old)
    atomic_json(JOURNAL, journal)
    try:
        for path, data in encoded.items():
            atomic_bytes(ROOT / path, data)
    except Exception:
        recover()
        raise
    committed = {k: v for k, v in journal.items() if k != 'old'}
    committed['status'] = 'COMMITTED'
    atomic_json(JOURNAL, committed)

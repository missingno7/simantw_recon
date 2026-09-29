"""Fingerprints of the shared repository state that can change a draft's result or a conclusion.

    python tools/shared_state.py            # current component fingerprints
    python tools/shared_state.py --diff OLD.json

A draft's C source is self-contained, so a recompile of the same file can only
change its strict/diagnostic result when one of these changes:

  toolchain   the pinned compiler/linker lock (layout/toolchain.json)
  compiler    compile wrapper/service implementation (object bytes are cached against it)
  matcher     strict matcher, diagnostic diff, body classifier and residue classifier code
  profiles    compiler profile catalogue/assignments (layout/compiler-profiles.json)

Other components do not change a recompile of the same file, but they change
derived variants (typedb resync, unit composition) and can invalidate an earlier
negative conclusion:

  admissions  src/recovery.json: newly admitted dependencies, typedb evidence, unit members
  units       layout/translation-units.json and the admitted unit records
  typedb      the declaration-database tool
  composer    unit composer / TU assembly implementation
  facts       the MSC 7.00 fact register (docs/msc7-codegen.md)
  permuter    permuter and its mutation catalogue
  pragmas     reviewed pragma / inline-asm lists

Every fingerprint is a SHA-256 over file bytes with line endings normalised, so a
CRLF/LF checkout difference is not a change.
"""
import argparse
import hashlib
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, read_json

COMPONENTS = {
    'toolchain': ['layout/toolchain.json'],
    'compiler': ['tools/compiler.py', 'tools/compiler_service.py', 'tools/compiler_worker.py', 'tools/compiler_wait.asm',
                 'layout/compiler-service.json'],
    'matcher': ['tools/library_match.py', 'tools/recovery_gate.py', 'tools/codegen_diff.py', 'tools/codegen_grinder.py',
                'tools/topology_diagnostics.py', 'tools/residue_clusters.py', 'tools/omf.py', 'tools/analysis.py'],
    'profiles': ['layout/compiler-profiles.json'],
    'admissions': ['src/recovery.json'],
    'units': ['layout/translation-units.json'],
    'typedb': ['tools/typedb.py', 'tools/c_source.py'],
    'composer': ['tools/unit_composer.py', 'tools/tu_assembly.py', 'tools/pool_search.py'],
    'facts': ['docs/msc7-codegen.md'],
    'permuter': ['tools/permuter.py', 'tools/permuter_mutations.py'],
    'pragmas': ['layout/pragma-review.json', 'layout/inline-asm-review.json'],
}

# A recompile of an unchanged draft can differ only when one of these moved.
RECOMPILE = ('toolchain', 'compiler', 'matcher', 'profiles')
# A shared change worth a sweep: anything that can change a recompile or a derived variant.
SWEEP_TRIGGERS = RECOMPILE + ('admissions', 'units', 'typedb', 'composer', 'pragmas')
# Changes that can invalidate an earlier negative experiment conclusion.
CONCLUSION = SWEEP_TRIGGERS + ('facts', 'permuter')


def _digest(paths, root=ROOT):
    h = hashlib.sha256()
    for rel in paths:
        path = Path(root) / rel
        h.update(rel.encode() + b'\0')
        if path.is_file():
            h.update(path.read_bytes().replace(b'\r\n', b'\n'))
        else:
            h.update(b'<missing>')
        h.update(b'\0')
    return h.hexdigest()[:16]


def fingerprint(root=ROOT):
    return {name: _digest(paths, root) for name, paths in COMPONENTS.items()}


def fingerprint_at(commit, root=ROOT):
    """Fingerprint of the committed tree at COMMIT (for records written before fingerprints existed)."""
    import subprocess
    out = {}
    for name, paths in COMPONENTS.items():
        h = hashlib.sha256()
        for rel in paths:
            h.update(rel.encode() + b'\0')
            proc = subprocess.run(['git', 'show', '%s:%s' % (commit, rel)], cwd=root, capture_output=True)
            h.update(proc.stdout.replace(b'\r\n', b'\n') if proc.returncode == 0 else b'<missing>')
            h.update(b'\0')
        out[name] = h.hexdigest()[:16]
    return out


def recompile_key(fp):
    return hashlib.sha256(json.dumps({k: fp[k] for k in RECOMPILE}, sort_keys=True).encode()).hexdigest()[:16]


def changed(old, new, components=None):
    names = components or tuple(COMPONENTS)
    return sorted(k for k in names if (old or {}).get(k) != (new or {}).get(k))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--diff', help='earlier fingerprint JSON to compare with')
    args = ap.parse_args()
    now = fingerprint()
    if args.diff:
        old = read_json(Path(args.diff))
        old = old.get('fingerprint', old)
        print(json.dumps(dict(changed=changed(old, now), sweep_triggers=changed(old, now, SWEEP_TRIGGERS), current=now), indent=2))
    else:
        print(json.dumps(now, indent=2))


if __name__ == '__main__':
    main()

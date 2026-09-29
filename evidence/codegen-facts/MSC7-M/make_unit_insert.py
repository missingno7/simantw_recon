"""Insert an open draft into its admitted unit source at the address-order position.

Usage: make_unit_insert.py UNIT_SOURCE DRAFT BEFORE_FUNCTION OUT
BEFORE_FUNCTION is the unit function whose definition follows the draft in the
original code segment. File-scope declarations of the draft are kept verbatim.
"""
import re
import sys
from pathlib import Path


def insert(unit, draft, before, out):
    lines = Path(unit).read_text(encoding='latin1').split('\n')
    pat = re.compile(r'^[A-Za-z_].*\b' + re.escape(before) + r'\s*\(')
    idx = None
    for i, line in enumerate(lines):
        if pat.match(line) and not line.rstrip().endswith(';'):
            idx = i
            break
    if idx is None:
        raise SystemExit('definition of %s not found' % before)
    # keep a preceding comment block attached to the following function
    while idx > 0 and lines[idx - 1].strip().startswith(('/*', '*')):
        idx -= 1
    text = '\n'.join(lines[:idx]) + '\n/* ---- f-study-bm: open draft inserted in address order ---- */\n' + \
        Path(draft).read_text(encoding='latin1') + '\n/* ---- end inserted draft ---- */\n' + '\n'.join(lines[idx:])
    Path(out).write_text(text, encoding='latin1')


if __name__ == '__main__':
    insert(*sys.argv[1:5])

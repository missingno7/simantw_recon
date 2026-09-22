"""Record a reviewed isolated source for a symbol.

A supervisor-reviewed source (a candidate rewritten to the object-level
declaration truth) is verified strictly under the symbol's object profile and,
when its body is exact, entered in evidence/topology/supervisor-unit-sources/
reviewed.json so scaffolded units can claim the member. Nothing is admitted
here; admission happens only through a unit's strict byte-level match.
"""
import argparse
from common import ROOT
import tu_assembly as tu


def main():
    p = argparse.ArgumentParser()
    p.add_argument('symbol')
    p.add_argument('source', help='path under evidence/topology/supervisor-unit-sources/')
    p.add_argument('--note', default='')
    a = p.parse_args()
    row = tu.record_reviewed_source(a.symbol, ROOT / a.source, a.note)
    print(a.symbol, row['result'], 'exact_body=%s' % row['exact_body'], row['issues'])


if __name__ == '__main__':
    main()

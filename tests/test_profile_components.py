"""A build-topology component is one object and must resolve to one profile."""
import copy
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, FormatError, read_json
import compiler_profiles as cp


class ComponentProfileTests(unittest.TestCase):
    def test_current_catalog_is_consistent(self):
        cp.validate()

    def test_split_profile_inside_one_component_is_refused(self):
        topology = read_json(ROOT / 'evidence/topology/build-topology.json')
        cat = cp.catalog()
        component = None
        for unit in topology['units']:
            for comp in unit['components']:
                names = {cp.resolve(p, cat)['name'] for p in comp['publics']}
                if len(comp['publics']) >= 2 and names == {cat['default_profile']}:
                    component = comp
                    break
            if component:
                break
        self.assertIsNotNone(component)
        bad = copy.deepcopy(cat)
        other = next(name for name in bad['profiles'] if name != bad['default_profile'])
        bad['assignments'].append(dict(id='test-split', profile=other, symbols=[component['publics'][0]],
                                       strength='STRICT', evidence=[], reason='test'))
        with self.assertRaises(FormatError) as raised:
            cp.validate(bad)
        self.assertIn('resolves to several profiles', str(raised.exception))


if __name__ == '__main__':
    unittest.main()

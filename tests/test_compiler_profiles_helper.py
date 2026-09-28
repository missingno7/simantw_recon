"""Helper evidence is scoped and admitted through the existing profile gates."""
import copy
import sys
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import compiler_profiles as cp
import static_probe


CONTEXT = 'antedit:C19C'
CALLER = '_DrawMap'
ASSIGNMENT = 'asg-antedit-c19c-og'


class HelperProfileEvidence(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Prime the immutable topology cache before read_json is mocked by tests.
        cls.component = cp.component_of(CALLER)
        cls.context = cp.catalog()['contexts'][CONTEXT]
        target, _bindings, _names, extent = static_probe.original_bytes(3, 0xD7A0)
        cls.helper_extent = dict(start=0xD7A0, end=extent['end'], upper=extent['upper'],
                                 status=extent.get('status'), target_bytes=len(target))

    def evidence(self, symbol='helper:3:D7A0', discriminating='DIAGNOSTIC', minimal='DIAGNOSTIC',
                 string_ops=None):
        return dict(symbol=symbol, like=CALLER, segment='ANTEDIT_MODULE',
                    helper_extent=self.helper_extent if symbol == 'helper:3:D7A0' else None,
                    string_ops=['cmpsb', 'movsw', 'movsb'] if string_ops is None else string_ops,
                    discriminating={'ogi': discriminating},
                    minimal_over_parent={'ogi': minimal})

    def run_assign(self, evidence, profile='ogi', supersede=ASSIGNMENT):
        cat = copy.deepcopy(cp.catalog())
        # Independent of the live catalog: start from a plain og assignment for the context.
        cat['assignments'] = [a for a in cat['assignments'] if a.get('context') != CONTEXT]
        cat['assignments'].append(dict(id=ASSIGNMENT, context=CONTEXT, profile='og', symbols=[], strength='DIAGNOSTIC',
                                       evidence=[], reason='test fixture', reviewed='test'))
        read_json = cp.read_json
        def read_evidence(path):
            return evidence if Path(path).name == 'test-helper.json' else read_json(path)
        with mock.patch.object(cp, 'catalog', return_value=cat), \
             mock.patch.object(cp, 'read_json', side_effect=read_evidence), \
             mock.patch.object(cp, 'validate', return_value={}), \
             mock.patch.object(cp, 'write_json') as writer:
            result = cp.assign(CONTEXT, profile, 'test profile evidence', ['build/test-helper.json'],
                               dry_run=True, supersede=supersede)
            writer.assert_not_called()
            self.assertNotIn(supersede, [a['id'] for a in cp.catalog()['assignments']])
            self.assertTrue(any(a['id'] == result['id'] for a in cp.catalog()['assignments']))
            return result

    def test_helper_inside_context_is_accepted(self):
        result = self.run_assign(self.evidence())
        self.assertEqual(result['profile'], 'ogi')
        self.assertEqual(result['supersedes'], ASSIGNMENT)

    def test_helper_outside_context_range_is_refused(self):
        record = self.evidence(symbol='helper:3:8000')
        record['helper_extent'] = dict(start=0x8000, end=0x8004, upper=0x9000,
                                       status='PROBABLE', target_bytes=4)
        read_json = cp.read_json
        def read_evidence(path):
            return record if Path(path).name == 'test-helper.json' else read_json(path)
        with mock.patch.object(cp, 'catalog', return_value=copy.deepcopy(cp.catalog())), \
             mock.patch.object(cp, 'read_json', side_effect=read_evidence), \
             mock.patch.object(cp, 'validate', return_value={}):
            with self.assertRaisesRegex(cp.FormatError, 'outside the context code range'):
                cp.assign(CONTEXT, 'ogi', 'test', ['build/test-helper.json'],
                          dry_run=True, supersede=ASSIGNMENT)

    def test_non_discriminating_helper_is_refused(self):
        record = self.evidence(discriminating='NONE', minimal='NONE')
        read_json = cp.read_json
        def read_evidence(path):
            return record if Path(path).name == 'test-helper.json' else read_json(path)
        with mock.patch.object(cp, 'catalog', return_value=copy.deepcopy(cp.catalog())), \
             mock.patch.object(cp, 'read_json', side_effect=read_evidence), \
             mock.patch.object(cp, 'validate', return_value={}):
            with self.assertRaisesRegex(cp.FormatError, 'does not discriminate profile ogi'):
                cp.assign(CONTEXT, 'ogi', 'test', ['build/test-helper.json'],
                          dry_run=True, supersede=ASSIGNMENT)

    def test_intrinsic_profile_requires_target_string_fingerprints(self):
        record = self.evidence(string_ops=[])
        read_json = cp.read_json
        def read_evidence(path):
            return record if Path(path).name == 'test-helper.json' else read_json(path)
        with mock.patch.object(cp, 'catalog', return_value=copy.deepcopy(cp.catalog())), \
             mock.patch.object(cp, 'read_json', side_effect=read_evidence), \
             mock.patch.object(cp, 'validate', return_value={}):
            with self.assertRaisesRegex(cp.FormatError, 'intrinsic profile requires string-intrinsic fingerprints'):
                cp.assign(CONTEXT, 'ogi', 'test', ['build/test-helper.json'],
                          dry_run=True, supersede=ASSIGNMENT)

    def test_member_evidence_keeps_existing_path(self):
        record = dict(symbol=CALLER, discriminating={'ogi': 'DIAGNOSTIC'},
                      minimal_over_parent={'ogi': 'DIAGNOSTIC'}, string_ops=['cmpsb'])
        result = self.run_assign(record)
        self.assertEqual(result['strength'], 'DIAGNOSTIC')
        self.assertEqual(result['evidence'], ['build/test-helper.json'])


if __name__ == '__main__':
    unittest.main()

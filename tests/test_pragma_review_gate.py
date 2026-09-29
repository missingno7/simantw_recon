"""Per-function optimize pragmas require an exact, evidenced review entry."""
import sys
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import compiler_profiles
import promote
from common import FormatError

SET = '#pragma optimize("e", off)'
RESTORE = '#pragma optimize("", on)'
SOURCE = f'''/* reviewed pragma source */
{SET}
int Sample(int x)
{{
    return x + 1;
}}
{RESTORE}
'''
REVIEW = {
    'description': 'test review',
    'functions': {
        '_Sample': {
            'pragma_text': SET,
            'restore_text': RESTORE,
            'evidence': ['tests/test_pragma_review_gate.py'],
        },
    },
}
FLAGS = compiler_profiles.profile_flags('baseline', '_TEXT')


class PragmaReviewGate(unittest.TestCase):
    def check(self, source, review=REVIEW):
        with mock.patch.object(promote, 'read_json', return_value=review):
            return promote.check_source(source, FLAGS, allow_pragma_optimize=True)

    def test_listed_exact_pair_is_accepted_for_source_check(self):
        self.assertTrue(self.check(SOURCE))

    def test_unlisted_function_is_refused(self):
        with self.assertRaisesRegex(FormatError, 'unreviewed #pragma optimize'):
            self.check(SOURCE.replace('Sample', 'Unlisted'), {'functions': {}})

    def test_different_setting_text_is_refused(self):
        with self.assertRaisesRegex(FormatError, 'differs from layout/pragma-review.json'):
            self.check(SOURCE.replace('"e", off', '"g", off'))

    def test_non_optimize_pragma_remains_refused(self):
        source = SOURCE.replace('return x + 1;', '#pragma loop_opt(off)\n    return x + 1;')
        with self.assertRaisesRegex(FormatError, 'without assembly or compiler pragmas'):
            self.check(source)

    def test_restore_must_be_empty_on(self):
        source = SOURCE.replace(RESTORE, '#pragma optimize("e", on)')
        review = {'functions': {'_Sample': {
            'pragma_text': SET,
            'restore_text': '#pragma optimize("e", on)',
            'evidence': ['tests/test_pragma_review_gate.py'],
        }}}
        with self.assertRaisesRegex(FormatError, 'restore.*must be'):
            self.check(source, review)

    def test_optimize_stays_banned_without_review_mode(self):
        with self.assertRaisesRegex(FormatError, 'requires a reviewed per-function entry'):
            promote.check_source(SOURCE, FLAGS)


if __name__ == '__main__':
    unittest.main()

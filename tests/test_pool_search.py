"""Pool-aware isolated-search prefix planning."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from pool_search import (component_pool_prefix_words, load_component_pool_map,
                         pool_word_references)
import tu_assembly as tu


class PoolSearchPlanningTests(unittest.TestCase):
    def test_prefix_words_are_sorted_by_original_selector_position(self):
        pool_map = dict(scope=dict(pool_words=['0x010C', '0x0108', '0x0112', '0x010A', '0x010E']),
                        words=[dict(word=w) for w in ['0x0112', '0x010A', '0x0108', '0x010E', '0x010C']])
        functions = {'_Target': dict(slots=[0x010E, 0x0110])}
        self.assertEqual(component_pool_prefix_words(pool_map, '_Target', functions),
                         [0x0108, 0x010A, 0x010C])

    def test_unattributed_selector_holes_follow_the_relocation_inventory(self):
        pool_map = dict(scope=dict(pool_words=['0x0100', '0x0104']),
                        words=[dict(word='0x0100'), dict(word='0x0104')])
        functions = {'_Target': dict(slots=[0x0106])}
        self.assertEqual(component_pool_prefix_words(pool_map, '_Target', functions,
                                                     selector_words={0x0100: 8, 0x0102: 9, 0x0104: 8}),
                         [0x0100, 0x0102, 0x0104])

    def test_unresolved_words_allocate_distinct_references_in_word_order(self):
        words = [0x0200, 0x0202]
        pool_map = dict(words=[
            dict(word='0x0202', symbol='UNRESOLVED', confidence='UNRESOLVED',
                 ne_relocation=dict(target_segment_number=1)),
            dict(word='0x0200', symbol='UNRESOLVED', confidence='UNRESOLVED',
                 ne_relocation=dict(target_segment_number=1)),
        ])
        symbols = dict(segments=[dict(number=1, symbols=[
            dict(name='_FirstTarget', offset=0), dict(name='_SecondTarget', offset=2),
        ])])
        refs, unresolved = pool_word_references(pool_map, words,
                                               {0x0200: 1, 0x0202: 1}, {}, symbols)
        self.assertEqual([r['word'] for r in refs], words)
        self.assertEqual([r['name'] for r in refs], ['FirstTarget', 'SecondTarget'])
        self.assertEqual(unresolved, ['0200', '0202'])

    def test_unresolved_standins_avoid_candidate_file_symbols(self):
        pool_map = dict(words=[])
        symbols = dict(segments=[dict(number=1, symbols=[
            dict(name='_CandidateGlobal', offset=0), dict(name='_OtherGlobal', offset=2),
        ])])
        refs, _ = pool_word_references(pool_map, [0x0200], {0x0200: 1}, {}, symbols,
                                       used_names={'CandidateGlobal'})
        self.assertEqual(refs[0]['name'], 'OtherGlobal')

    def test_mapless_component_returns_no_map(self):
        with tempfile.TemporaryDirectory() as tmp:
            self.assertIsNone(load_component_pool_map('sample:0000', tmp))
        self.assertEqual(component_pool_prefix_words(None, '_Target', {'_Target': {'slots': [0x100]}}), [])

    def test_map_only_prefix_keeps_only_mapped_selector_words(self):
        pool_map = dict(scope=dict(pool_words=['0x0100', '0x0104']),
                        words=[dict(word='0x0100')])
        self.assertEqual(component_pool_prefix_words(pool_map, '_Target',
                                                     {'_Target': {'slots': [0x0106]}}),
                         [0x0100, 0x0104])

    def test_candidate_pool_must_be_one_contiguous_ascending_block(self):
        good, _ = tu.assemblable(['_Target'], {'_Target': {'slots': [0x0104, 0x0106]}})
        split, reason = tu.assemblable(['_Target'], {'_Target': {'slots': [0x0104, 0x010A]}})
        reordered, order_reason = tu.assemblable(['_Target'], {'_Target': {'slots': [0x0106, 0x0104]}})
        self.assertTrue(good)
        self.assertFalse(split)
        self.assertIn('not contiguous', reason)
        self.assertFalse(reordered)
        self.assertIn('differs from the original pool order', order_reason)


if __name__ == '__main__':
    unittest.main()

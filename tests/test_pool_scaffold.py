"""Pool scaffolding: stand-ins in the reserved segment are ignored by the matcher, everything else stays strict."""
import copy
import json
import sys
import unittest
from unittest import mock
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture
import ne, mapsym
from library_match import compare_member, import_symbols, SCAFFOLD_SEGMENT
import tu_assembly as tu


class MatcherScaffoldTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.module = json.loads((ROOT / 'evidence/topology/supervisor-far-code-offsets/loc5-module.json').read_text())
        cls.raw = fixture('SIMANTW.EXE')
        cls.image = ne.parse(cls.raw)
        cls.symbols = mapsym.parse(fixture('SIMANTW.SYM'))
        cls.imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')

    def with_segment(self, name, klass='CODE', public=None):
        module = copy.deepcopy(self.module)
        module['segments'].append(dict(index=len(module['segments']) + 1, name=name, klass=klass, length=6, data_hex='b80000c3' + '9090', initialized_ranges=[[0, 6]]))
        module['segments'][-1]['class'] = klass
        if public:
            module['publics'].append(dict(name=public, offset=0, type_index=0, segment=module['segments'][-1]['index'], group=0, frame=None, local=False))
        return module

    def check(self, module):
        return compare_member(module, self.raw, self.image, self.symbols, self.imports)

    def test_reserved_scaffold_segment_is_skipped_and_recorded(self):
        result = self.check(self.with_segment(SCAFFOLD_SEGMENT, public='_pool_stub_Anything'))
        self.assertEqual(result['result'], 'CONFIRMED_MEMBER')
        self.assertEqual(result['scaffold_segments'], [SCAFFOLD_SEGMENT])

    def test_other_unplaced_code_segment_still_fails(self):
        result = self.check(self.with_segment('EXTRA_TEXT', public='_pool_stub_Other'))
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertIn('unplaced contribution EXTRA_TEXT', result['issues'])

    def test_scaffold_segment_with_a_mapsym_public_is_not_scaffolding(self):
        # A real symbol placed in the reserved segment anchors it like any code
        # and its bytes are compared: this fixture's bytes are not _StopSimulation.
        result = self.check(self.with_segment(SCAFFOLD_SEGMENT, public='_StopSimulation'))
        self.assertNotEqual(result['result'], 'CONFIRMED_MEMBER')
        self.assertEqual(result.get('scaffold_segments', []), [])

    def test_scaffold_segment_of_data_class_is_not_skipped(self):
        result = self.check(self.with_segment(SCAFFOLD_SEGMENT, klass='DATA'))
        self.assertIn('unplaced contribution ' + SCAFFOLD_SEGMENT, result['issues'])


class ComposerScaffoldTests(unittest.TestCase):
    def test_admitted_unit_yard_source_supersedes_parked_draft(self):
        target = json.loads((ROOT / 'src/recovery.json').read_text())['targets']['_YardArea']
        reviewed = tu.admitted_unit_member_source('_YardArea', target)
        self.assertEqual(reviewed['source'], 'evidence/topology/supervisor-unit-sources/YardArea-patchRgn2.c')
        self.assertEqual(tu.preserved_sources()['_YardArea']['source'], reviewed['source'])
        with mock.patch.object(tu, 'identity', return_value={'sha256': 'stale'}):
            with self.assertRaisesRegex(tu.FormatError, 'identity is stale'):
                tu.admitted_unit_member_source('_YardArea', target)
        with mock.patch.object(tu, 'read_json', return_value={'sources': {'_YardArea': {
                'source': 'build/codegen-cache/ignored/INPUT.C', 'identity': {'sha256': 'x'}}}}):
            self.assertIsNone(tu.admitted_unit_member_source('_YardArea', target))
        with mock.patch.object(tu, 'read_json', return_value={'sources': {'_YardArea': {
                'source': 'src/recovered/wf_tu_whole_unit.c', 'identity': {'sha256': 'x'}}}}):
            self.assertIsNone(tu.admitted_unit_member_source('_YardArea', target))

    def test_member_without_selector_slots_needs_no_pool_standins(self):
        self.assertEqual(tu.required_pool_block([0xc19e, 0xc1a0, 0xc1a2], []), [])
        self.assertEqual(tu.required_pool_block([0xc19e, 0xc1a0, 0xc1a2], [0xc1a0]), [0xc19e, 0xc1a0])

    def test_unknown_prior_public_owns_only_direct_relocated_selector_reads(self):
        publics = ['_Prior', '_Claimed', '_Later']
        functions = {'_Prior': {'size': None}, '_Claimed': {'size': 100}, '_Later': {'size': None}}
        card = lambda symbol, rows: dict(symbol=symbol, extent={'status': 'PROBABLE'}, disassembly=rows)
        rows = [dict(mnemonic='mov', operands='es, word ptr [0xc142]'),
                dict(mnemonic='mov', operands='es, word ptr [0xc144]'),
                dict(mnemonic='mov', operands='ax, word ptr [0xc146]'),
                dict(mnemonic='mov', operands='es, word ptr [0xc148]')]
        cards = [card('_Prior', rows), card('_Later', rows)]
        owners = tu.prior_unknown_pool_owners(publics, ['_Claimed'], functions, cards,
                                              {0xc142: 9, 0xc144: 8, 0xc146: 9},
                                              [0xc142, 0xc144, 0xc146, 0xc148])
        self.assertEqual(owners, {0xc142: '_Prior', 0xc144: '_Prior'})
        functions['_Prior']['size'] = 40
        self.assertEqual(tu.prior_unknown_pool_owners(publics, ['_Claimed'], functions,
                                                       cards, {0xc142: 9}, [0xc142]), {})

    def test_negative_index_data_addends_place_distinct_dog_tables(self):
        data = bytes.fromhex('ffff0300010404030702010001020001020202010001000100010201020000010201')
        original = bytearray(0x2000)
        original[0x188e:0x1890] = data[:2]
        original[0x18d8:0x18e0] = data[2:10]
        original[0x1918:0x1930] = data[10:]
        anchors = {0: {0x188e}, 10: {0x190e}, 22: {0x190e},
                   65526: {0x18d6}, 65530: {0x18d6}}
        pieces = tu.negative_index_data_pieces(data, anchors, original, '_DrawDog')
        self.assertEqual([(p['offset'], p['length'], p['candidate_start']) for p in pieces],
                         [(0x188e, 2, 0), (0x18d8, 8, 2), (0x1918, 24, 10)])

    def test_negative_index_data_addend_refuses_undistinguished_zeroes(self):
        with self.assertRaisesRegex(tu.FormatError, 'no unique initialized DATA placement'):
            tu.negative_index_data_pieces(b'\0' * 8, {65530: {0x100}}, bytearray(0x200), '_Example')

    def test_mixed_dog_data_gap_is_not_emitted_as_a_literal(self):
        pieces = [dict(segment='_DATA', offset=0x188e, length=2, member='_DrawDog'),
                  dict(segment='_DATA', offset=0x18d8, length=8, member='_DrawDog')]
        plan = tu.data_fillers(pieces, {'data_words': []}, {'_DrawDog': {'offset': 0}})
        self.assertEqual(plan['literals'], [])
        self.assertIn('pool_data_fill_1890', plan['fillers']['_DrawDog'][0])

    def test_all_zero_private_word_is_not_inferred_as_a_literal(self):
        self.assertFalse(tu.private_data_is_literal(b'\x00\x00'))
        self.assertTrue(tu.private_data_is_literal(b'\r\x00'))
        self.assertFalse(tu.private_data_is_literal(b'\x01\x00'))
        self.assertFalse(tu.private_data_is_literal(b'\xff\xffA\x00'))

    def test_reviewed_scaffold_identifies_only_separate_stand_ins(self):
        text = '#pragma alloc_text(POOLSTUB_TEXT, filler)\nvoid far filler(void) { }\nvoid far Real(void) { }'
        plan = tu.reviewed_scaffold(text, ['_Real'], ['_Real'])
        self.assertEqual(plan['stubs'], [dict(function='filler')])
        with self.assertRaisesRegex(tu.FormatError, 'real component public'):
            tu.reviewed_scaffold(text.replace('filler', 'Real'), ['_Real'], ['_Real'])
        with self.assertRaisesRegex(tu.FormatError, 'lacks a definition'):
            tu.reviewed_scaffold('#pragma alloc_text(POOLSTUB_TEXT, filler)', ['_Real'], ['_Real'])

    def test_reference_expressions_read_values_not_addresses(self):
        self.assertEqual(tu.reference_expression('A', 'extern unsigned char far A[12][16];'), 'A[0][0]')
        self.assertEqual(tu.reference_expression('B', 'extern int far B;'), '(int)B')
        self.assertEqual(tu.reference_expression('C', 'extern struct Point far C;'), '*(int far *)&C')
        self.assertEqual(tu.reference_expression('S', 'extern struct Rec far S[7];'), '*(int far *)S')
        self.assertEqual(tu.reference_expression('D', None), 'D')

    def test_scaffold_text_declares_only_non_member_names_and_moves_runs(self):
        plan = dict(stubs=[dict(function='_Gap', position=1, references=[dict(word=0xc61a, segment=8, name='Shared', basis='CLAIMED_MEMBER_NAME'), dict(word=0xc61c, segment=8, name='Rep', basis='SEGMENT_REPRESENTATIVE')])],
                    runs=[['_A'], ['_B', '_C']])
        parts = tu.scaffold_text(plan, {'Shared': 'extern int far Shared[4];'})
        self.assertEqual(parts['declarations'], ['extern int far Rep;  /* scaffold reference for pool word C61C (segment 8, SEGMENT_REPRESENTATIVE) */'])
        self.assertIn('    t = Shared[0];', parts['definitions'][0]['text'])
        self.assertIn('    t = Rep;', parts['definitions'][0]['text'])
        self.assertEqual(parts['pragmas'], ['#pragma alloc_text(%s, pool_stub_Gap)' % tu.SCAFFOLD_SEGMENT, '#pragma alloc_text(RUN2_TEXT, B, C)'])
        self.assertEqual(parts['definitions'][0]['rank_name'], '_Gap')
        self.assertIn('SCAFFOLD, not recovered source', parts['definitions'][0]['text'])

    def test_compose_drops_unclaimed_definitions_and_their_statics(self):
        folder = ROOT / 'build/tests/scaffold'
        folder.mkdir(parents=True, exist_ok=True)
        (folder / 'unit.c').write_text('extern int far Shared;\nstatic int table[2] = {1, 2};\nstatic int keep = 3;\n\nvoid far A(void)\n{\n    Shared = keep;\n}\n\nvoid far Gap(void)\n{\n    Shared = table[0];\n}\n\nvoid far B(void)\n{\n    Shared = 2;\n}\n', encoding='latin1')
        rel = (folder / 'unit.c').relative_to(ROOT).as_posix()
        result = tu.compose({'_A': rel, '_B': rel}, ['_A', '_B'], 'unit', exclude_definitions=['Gap'],
                            extra_definitions=[dict(name='pool_stub_Gap', text='void far pool_stub_Gap(void)\n{\n}', rank_name='_Gap')], rank_order=['_A', '_Gap', '_B'], pragmas=['#pragma alloc_text(POOLSTUB_TEXT, pool_stub_Gap)'])
        self.assertEqual(result['status'], 'COMPOSED')
        text = result['text']
        self.assertNotIn('void far Gap(void)', text)
        self.assertNotIn('table[2]', text)
        self.assertIn('static int keep = 3;', text)
        self.assertLess(text.index('void far A(void)'), text.index('pool_stub_Gap(void)\n{'))
        self.assertLess(text.index('pool_stub_Gap(void)\n{'), text.index('void far B(void)'))
        self.assertLess(text.index('#pragma alloc_text'), text.index('void far A(void)'))


class ComposerConflictTests(unittest.TestCase):
    def write(self, name, lines):
        folder = ROOT / 'build/tests/scaffold'
        folder.mkdir(parents=True, exist_ok=True)
        (folder / name).write_text(chr(10).join(lines) + chr(10), encoding='latin1')
        return (folder / name).relative_to(ROOT).as_posix()

    def test_shape_variants_become_per_member_views(self):
        a = self.write('a.c', ['extern unsigned char near LifeB[];', 'extern int far Flag;', 'void far A(void)', '{', '    LifeB[3] = Flag;', '}'])
        b = self.write('b.c', ['extern unsigned char near LifeB[128][64];', 'extern int far Flag[];', 'void far B(void)', '{', '    LifeB[1][2] = Flag[0];', '}'])
        r = tu.compose({'_A': a, '_B': b}, ['_A', '_B'], 'unit')
        self.assertEqual(r['status'], 'COMPOSED')
        text = r['text']
        self.assertIn('extern unsigned char near LifeB[128][64];', text)
        self.assertNotIn('extern unsigned char near LifeB[];', text)
        self.assertIn('#define LifeB ((unsigned char near *)LifeB)', text)
        self.assertIn('#define Flag ((Flag)[0])', text)
        self.assertLess(text.index('#define LifeB'), text.index('void far A(void)'))
        self.assertLess(text.index('void far A(void)'), text.index('#undef LifeB'))
        self.assertLess(text.index('#undef LifeB'), text.index('void far B(void)'))

    def test_element_type_views_and_distance_conflicts(self):
        a = self.write('c.c', ['extern int far Map[];', 'void far A(void)', '{', '    Map[1] = 2;', '}'])
        b = self.write('d.c', ['extern unsigned char far Map[];', 'void far B(void)', '{', '    Map[1] = 2;', '}'])
        r = tu.compose({'_A': a, '_B': b}, ['_A', '_B'], 'unit')
        self.assertEqual(r['status'], 'COMPOSED')
        self.assertTrue('#define Map ((int far *)Map)' in r['text'] or '#define Map ((unsigned char far *)Map)' in r['text'])
        c = self.write('e.c', ['extern int near Map[];', 'void far C(void)', '{', '    Map[1] = 2;', '}'])
        r = tu.compose({'_A': a, '_C': c}, ['_A', '_C'], 'unit')
        self.assertEqual(r['status'], 'DECLARATION_CONFLICT')

    def test_struct_tags_are_renamed_per_source_and_function_macros_do_not_clash(self):
        a = self.write('f.c', ['struct Bucket { int count; };', 'extern struct Bucket far *far handles[];', 'extern unsigned char far T[];', 'void far A(void)', '{', '    handles[0]->count = T[1];', '}'])
        b = self.write('g.c', ['struct Bucket { int other; int count; };', 'extern struct Bucket far *far handles[];', '#define T(i) (i)', 'void far B(void)', '{', '    handles[1]->count = T(3);', '}'])
        r = tu.compose({'_A': a, '_B': b}, ['_A', '_B'], 'unit')
        self.assertEqual(r['status'], 'COMPOSED', r.get('conflicts'))
        text = r['text']
        self.assertIn('struct Bucket_2 {', text)
        self.assertEqual(r['tag_renames'], {'_B': {'struct Bucket': 'struct Bucket_2'}})
        self.assertIn('#define T(i) (i)', text)
        self.assertLess(text.index('void far A(void)'), text.index('#define T(i) (i)'))
        self.assertIn('#undef T', text)


class SubmissionPragmaTests(unittest.TestCase):
    def submission(self, lines, scaffold):
        import recovery_workflow as wf
        folder = ROOT / 'build/tests/scaffold'
        folder.mkdir(parents=True, exist_ok=True)
        (folder / 'sub.c').write_text(chr(10).join(lines) + chr(10), encoding='latin1')
        flags = ['/AL', '/G2', '/Gs', '/Oelw', '/NTSIMANT_MODULE']
        job = dict(symbol='_A', flags=flags, lane='TU_ASSEMBLY', publics=['_A'], scaffold=dict(unit='x') if scaffold else None)
        spec = dict(symbol='_A', compiler='msc700', flags=flags, publics=['_A'], semantic_summary='test', max_candidates=1, axes=[], source=(folder / 'sub.c').relative_to(ROOT).as_posix())
        return lambda: wf.check_submission(spec, job)

    def test_alloc_text_allowed_only_for_scaffolded_units(self):
        from common import FormatError
        lines = ['void far A(void);', '#pragma alloc_text(POOLSTUB_TEXT, A)', 'void far A(void)', '{', '}']
        self.submission(lines, True)()
        with self.assertRaises(FormatError):
            self.submission(lines, False)()

    def test_other_pragmas_stay_forbidden_in_scaffolded_units(self):
        from common import FormatError
        with self.assertRaises(FormatError):
            self.submission(['#pragma pack(1)', 'void far A(void)', '{', '}'], True)()
        with self.assertRaises(FormatError):
            self.submission(['void far A(void);', '#pragma alloc_text(_TEXT, A)', 'void far A(void)', '{', '}'], True)()


if __name__ == '__main__':
    unittest.main()

"""Pool scaffolding: stand-ins in the reserved segment are ignored by the matcher, everything else stays strict."""
import copy
import json
import sys
import unittest
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
    def test_reference_expressions_read_values_not_addresses(self):
        self.assertEqual(tu.reference_expression('A', 'extern unsigned char far A[12][16];'), 'A[0][0]')
        self.assertEqual(tu.reference_expression('B', 'extern int far B;'), '(int)B')
        self.assertEqual(tu.reference_expression('C', 'extern struct Point far C;'), '*(int far *)&C')
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

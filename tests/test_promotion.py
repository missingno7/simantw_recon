"""Admission, publication and search boundaries; no live manifests mutated."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import FormatError, identity, sha256, read_json
import compiler
import codegen_cache as cache
import publication
import promote
import recovery_gate as gate

FLAGS = ['/AL', '/G2', '/Gs', '/Oelw', '/NTGR_MODULE']


class ScopeTests(unittest.TestCase):
    def setUp(self):
        self.module = dict(publics=[dict(name='_a', segment=1, offset=0)], segments=[dict(name='GR', **{'class': 'CODE'}, length=4, initialized_ranges=[(0, 4)])])
        self.targets = {'_a': dict(segment=1, offset=10, size=4, code_segment='GR', extent_status='CONFIRMED')}
    def check(self):
        with patch.object(gate, 'unique_symbol', return_value=(1, 10)):
            gate.check_coverage(self.module, {}, self.targets)
    def test_full_scope_accepted(self): self.check()
    def test_matching_prefix_is_not_a_function(self):
        self.module['segments'][0]['length'] = 3
        with self.assertRaisesRegex(FormatError, 'coverage'): self.check()
    def test_hole_is_not_initialized_coverage(self):
        self.module['segments'][0]['initialized_ranges'] = [(0, 1), (2, 4)]
        with self.assertRaisesRegex(FormatError, 'coverage'): self.check()
    def test_wrong_public_rejected(self):
        self.module['publics'][0]['name'] = '_b'
        with self.assertRaisesRegex(FormatError, 'public'): self.check()
    def test_wrong_group_rejected(self):
        self.module['segments'][0]['name'] = 'OTHER'
        with self.assertRaisesRegex(FormatError, 'group'): self.check()
    def test_wrong_mapsym_address_rejected(self):
        self.targets['_a']['offset'] = 11
        with self.assertRaisesRegex(FormatError, 'MAPSYM'): self.check()
    def test_probable_is_not_admitted_scope(self):
        self.targets['_a']['extent_status'] = 'PROBABLE'
        with self.assertRaisesRegex(FormatError, 'unreviewed'): self.check()
    def test_complete_member_mismatch_rejected(self):
        with patch.object(gate, 'check_coverage'), patch.object(gate, 'compare_member', return_value=dict(result='NO_COMPLETE_MATCH', issues=['private CONST'])):
            with self.assertRaisesRegex(FormatError, 'complete member'): gate.check_member({}, b'', {}, {}, {}, {})


class AdmissionCFGTests(unittest.TestCase):
    def admit(self, original, candidate, entries):
        module = dict(publics=[dict(name='_a', segment=1, offset=0)], segments=[dict(name='GR', **{'class': 'CODE'}, length=len(candidate), initialized_ranges=[(0, len(candidate))], data_hex=candidate.hex())])
        symbols = dict(segments=[dict(number=1, name='GR', symbols=[dict(name=name, offset=pos) for name, pos in entries])])
        image = dict(segments=[dict(kind='CODE', file_offset=0, logical_size=len(original), relocations=[])])
        return gate.admission_targets(module, original, image, symbols, ['_a'])
    def test_original_extent_must_be_covered(self):
        with self.assertRaisesRegex(FormatError, 'full original'):
            self.admit(bytes.fromhex('90cb'), bytes.fromhex('cb'), [('_a', 0)])
    def test_incoming_jump_rejects_isolated_tail(self):
        with self.assertRaisesRegex(FormatError, 'cross-entry'):
            self.admit(bytes.fromhex('cbebfd'), bytes.fromhex('cb'), [('_a', 0), ('_b', 1)])
    def test_alias_is_not_independent_function(self):
        with self.assertRaisesRegex(FormatError, 'alias'):
            self.admit(bytes.fromhex('cb'), bytes.fromhex('cb'), [('_a', 0), ('_alias', 0)])
    def test_jump_table_requires_expert_evidence(self):
        with self.assertRaisesRegex(FormatError, 'expert extent'):
            self.admit(bytes.fromhex('ffe3'), bytes.fromhex('ffe3'), [('_a', 0)])
    def test_closed_isolated_scope_is_eligible(self):
        target = self.admit(bytes.fromhex('90cb'), bytes.fromhex('90cb'), [('_a', 0)])
        self.assertEqual(target['_a']['size'], 2)


class TemporaryRoot(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(); self.addCleanup(self.tmp.cleanup); self.root = Path(self.tmp.name)
        for module in (compiler, cache, publication, promote):
            p = patch.object(module, 'ROOT', self.root); p.start(); self.addCleanup(p.stop)
        p = patch.object(promote, 'relative', side_effect=lambda path: Path(path).resolve().relative_to(self.root.resolve()).as_posix()); p.start(); self.addCleanup(p.stop)
        for name, value in (('JOURNAL', self.root / 'build/publication.json'), ('LOCK', self.root / 'build/publication.lock')):
            p = patch.object(publication, name, value); p.start(); self.addCleanup(p.stop)
    def put(self, name, data):
        path = self.root / name; path.parent.mkdir(parents=True, exist_ok=True); path.write_text(data); return path
    def fixture(self):
        self.put('layout/toolchain.json', '{"files":{}}'); self.put('tools/compiler.py', 'wrapper'); self.put('input.c', 'int f(void) {return 1;}'); self.put('output.obj', 'OMF')
        return dict(exit_code=0, unsupported_option=False, source='input.c', source_identity=identity(self.root / 'input.c'), object='output.obj',
                    object_identity=identity(self.root / 'output.obj'), toolchain_lock_sha256=sha256((self.root / 'layout/toolchain.json').read_bytes()))


class ReceiptAndCacheTests(TemporaryRoot):
    def test_failed_or_unknown_option_receipt_rejected(self):
        r = self.fixture()
        for changes in [dict(exit_code=1), dict(unsupported_option=True)]:
            with self.assertRaises(FormatError): compiler.validate_receipt(dict(r, **changes))
    def test_lock_cache_never_skips_object_or_source_hash(self):
        r = self.fixture(); seen = set()
        with patch.object(compiler, 'verify_lock') as lock:
            compiler.validate_receipt(r, seen); compiler.validate_receipt(r, seen); self.assertEqual(lock.call_count, 1)
            self.put('input.c', 'changed')
            with self.assertRaisesRegex(FormatError, 'source'): compiler.validate_receipt(r, seen)
            self.put('input.c', 'int f(void) {return 1;}'); self.put('output.obj', 'changed')
            with self.assertRaisesRegex(FormatError, 'object'): compiler.validate_receipt(r, seen)
    def test_cache_reuses_receipt_and_recompiles_corrupt_object(self):
        original = self.fixture(); jobs = [dict(source='input.c', flags=['/AL'])]
        def compile_jobs(jobs, compiler_name):
            return [(self.root / 'output.obj', dict(original, source=j['source'], compiler=compiler_name, flags=j['flags'], batch_directory='one-boot')) for j in jobs]
        with patch.object(cache, 'compile_batch', side_effect=compile_jobs) as worker:
            first, a = cache.compile_cached(jobs); second, b = cache.compile_cached(jobs)
            self.assertEqual((a['misses'], b['hits'], b['environment_launches'], worker.call_count), (1, 1, 0, 1))
            first[0][0].write_text('corrupt')
            _, c = cache.compile_cached(jobs); self.assertEqual((c['misses'], worker.call_count), (1, 2))
    def test_changed_toolchain_snapshot_is_rejected(self):
        r = self.fixture(); self.put('layout/toolchain.json', '{"files":{},"changed":true}')
        with self.assertRaisesRegex(FormatError, 'toolchain'): compiler.validate_receipt(r)


class SourceRuleTests(unittest.TestCase):
    def test_uncatalogued_flags_rejected(self):
        with self.assertRaisesRegex(FormatError, 'catalog'):
            promote.check_source('int a(void) { return 1; }', ['/AL', '/G2', '/Gs', '/Ox', '/NTGR_MODULE'])
    def test_catalogued_profile_accepted(self):
        promote.check_source('int a(void) { return 1; }', FLAGS)
    def test_assembly_or_absolute_pointer_rejected(self):
        for code in ['int a(void) { _asm nop; }', 'char far *p=(char far *)0x12345678;', '#include <x.h>\nint a;', '#pragma pack(1)\nint a;']:
            with self.assertRaises(FormatError): promote.check_source(code, FLAGS)
    def test_unfinished_source_rejected(self):
        for code in ['/* TODO */ int a;', '/* only a comment */']:
            with self.assertRaises(FormatError): promote.check_source(code, FLAGS)
    def test_semantic_summary_required(self):
        with self.assertRaisesRegex(FormatError, 'semantic'): promote.semantic_summary('int a;')
        self.assertEqual(promote.semantic_summary('/* Return one */ int a;'), 'Return one')
        self.assertEqual(promote.semantic_summary('int a;', 'Given'), 'Given')


class PublicationTests(TemporaryRoot):
    def prepare(self):
        for name in publication.CORE: self.put(name, 'old')
        return {p: dict(new=p) for p in publication.CORE}
    def test_partial_commit_restores_every_old_file(self):
        values = self.prepare(); original = publication.atomic_bytes; calls = []
        def fail_once(path, data):
            calls.append(path)
            if len(calls) == 3: raise OSError('simulated disk failure')
            original(path, data)
        with patch.object(publication, 'atomic_bytes', side_effect=fail_once):
            with self.assertRaises(OSError): publication.commit(values, 'x')
        self.assertTrue(all((self.root / p).read_text() == 'old' for p in publication.CORE))
        self.assertEqual(read_json(publication.JOURNAL)['status'], 'ROLLED_BACK_AFTER_INTERRUPTION')
    def test_committed_publication_keeps_no_rollback_copy(self):
        values = self.prepare(); publication.commit(values, 'x')
        journal = read_json(publication.JOURNAL)
        self.assertEqual(journal['status'], 'COMMITTED'); self.assertNotIn('old', journal)
        self.assertEqual(publication.recover()['status'], 'COMMITTED')
    def test_interrupted_publication_rolls_back(self):
        self.prepare()
        publication.atomic_json(publication.JOURNAL, dict(status='PREPARED', new={p: sha256(b'new') for p in publication.CORE},
                                                           old={p: __import__('base64').b64encode(b'old').decode() for p in publication.CORE}))
        self.put(publication.CORE[0], 'new')
        self.assertEqual(publication.recover()['status'], 'ROLLED_BACK_AFTER_INTERRUPTION')
        self.assertEqual((self.root / publication.CORE[0]).read_text(), 'old')
    def test_recovery_refuses_to_overwrite_a_later_edit(self):
        self.prepare()
        publication.atomic_json(publication.JOURNAL, dict(status='PREPARED', new={p: sha256(b'new') for p in publication.CORE},
                                                           old={p: __import__('base64').b64encode(b'old').decode() for p in publication.CORE}))
        self.put(publication.CORE[1], 'unrelated user edit')
        with self.assertRaisesRegex(FormatError, 'conflicts'): publication.recover()
        self.assertEqual((self.root / publication.CORE[1]).read_text(), 'unrelated user edit')
    def test_lock_waits_then_times_out(self):
        with publication.publication_lock():
            with self.assertRaisesRegex(FormatError, 'publication lock'):
                with publication.publication_lock(timeout=0.2): pass


class PromotionTests(TemporaryRoot):
    def run_admit(self, comparison_error=None, recipes=None, verify_only=False):
        recipes = recipes or {}
        self.put('build/recovered/obj.obj', 'OMF')
        for name in promote.PROOF_TOOLS: self.put(name, 'tool')
        documents = {'src/recovery.json': dict(targets=dict(recipes)), 'build/recovered/manifest.json': dict(game_objects=[], runtime_objects=[]),
                     'evidence/symbols/inventory.json': dict(symbols=[dict(name='_a', ownership='GAME')])}
        reader = lambda path: documents[Path(path).relative_to(self.root).as_posix()]
        module = dict(publics=[dict(name='_a', segment=1, offset=0)], segments=[dict(index=1, name='GR_MODULE', **{'class': 'CODE'})])
        check = patch.object(promote, 'check_member', side_effect=FormatError(comparison_error)) if comparison_error else patch.object(promote, 'check_member', return_value=dict(result='CONFIRMED_MEMBER'))
        with patch.object(promote, 'read_json', side_effect=reader), patch.object(promote, 'verify', return_value=dict(game=[], runtime=[])) as verify, \
             patch.object(promote, 'compile_source', return_value=(self.root / 'build/recovered/obj.obj', dict(exit_code=0))), patch.object(promote, 'validate_receipt'), \
             patch.object(promote.omf, 'parse', return_value=module), patch.object(promote, 'fixture', return_value=b''), patch.object(promote.ne, 'parse'), \
             patch.object(promote.mapsym, 'parse'), patch.object(promote, 'import_symbols'), patch.object(promote, 'admission_targets', return_value={'_a': dict(size=1)}), \
             check, patch.object(publication, 'commit') as commit,              patch('image.build', return_value=dict(status='HYBRID_EXACT', owned=dict(C=1), debt_total=0, claim_conflicts=dict(bytes=0), problems=[])):
            try:
                return promote.admit('a', ['_a'], b'/* a */ int a;', FLAGS, dict(name='baseline'), 'a', verify_only), commit, verify
            except FormatError as exc:
                return exc, commit, verify
    def test_mismatch_publishes_nothing_and_leaves_no_source(self):
        result, commit, _ = self.run_admit('complete member comparison failed')
        self.assertIsInstance(result, FormatError)
        commit.assert_not_called()
        self.assertEqual(list((self.root / 'src/recovered').glob('*.c')), [])
        self.assertFalse((self.root / 'evidence/recovery/promotions').exists())
    def test_exact_candidate_publishes_once(self):
        result, commit, verify = self.run_admit()
        self.assertEqual(result['status'], 'PROMOTED'); commit.assert_called_once()
        self.assertEqual(verify.call_count, 2)
        self.assertTrue((self.root / 'src/recovered' / (result['id'] + '.c')).exists())
    def test_verify_only_never_publishes(self):
        result, commit, _ = self.run_admit(verify_only=True)
        self.assertEqual(result['admission'], 'PASSED'); commit.assert_not_called()
        self.assertFalse((self.root / 'src/recovered').exists())
    def test_function_promotion_cannot_replace_an_admitted_recipe(self):
        result, commit, _ = self.run_admit(recipes={'_a': dict(source='old.c')})
        self.assertIsInstance(result, FormatError); self.assertIn('already admitted', str(result)); commit.assert_not_called()


class SearchHasNoBudgetTests(unittest.TestCase):
    def test_repeated_identical_rounds_are_allowed(self):
        import search
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory); source = root / 'a.c'; source.write_text('/* x */ int a;')
            report = dict(cache={}, results=[dict(candidate=0, choices={'input': 0}, receipt=dict(stdout=''), comparison=dict(result='NO_COMPLETE_MATCH'))])
            with patch.object(search, 'ROOT', root), patch.object(search, 'relative', side_effect=lambda p: str(p)), patch.object(search, 'run', return_value=report) as run, \
                 patch('promote.function_flags', return_value=(dict(name='baseline'), FLAGS)), patch.object(search, 'recipes', return_value={}):
                for _ in range(3):
                    result = search.search('_a', [str(source)])
                    self.assertEqual(result['candidates'], 1)
            self.assertEqual(run.call_count, 3)


if __name__ == '__main__':
    unittest.main()

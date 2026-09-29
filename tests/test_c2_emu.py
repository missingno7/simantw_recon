"""Focused tests for the emulated MSC 7.00 passes and the allocator instrumentation.

The emulator runs the authentic, unmodified C13216/C23216/C33216 images; the
golden values below were cross-checked against the DOSBox compiler service
(build/workers/f-alloc-emu/corpus_validation.json: 406/406 admitted sources
byte-identical).
"""
import faulthandler
import hashlib
import sys
import unittest
from pathlib import Path

from tools import c2_emu

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ['/AL', '/G2', '/Gs', '/Oelw', '/NT_TEXT']

TOY_LOOP = b"""extern int g(int);
extern int tab[100];
int f(int a, int b)
{
    int i, s = 0;
    for (i = 0; i < a; i++)
        s += tab[i] + g(b);
    return s + b;
}
"""

TOY_HOMES = b"""extern int g(int *);
extern int h(int, int, int);
int f(int n)
{
    int a, b, c;
    g(&a); g(&b); g(&c); g(&c); g(&c); g(&b);
    return h(a, b, c);
}
"""


_FAULTHANDLER = False


def setUpModule():
    # Unicorn's mem_map provokes first-chance access violations that it handles
    # itself; Windows faulthandler would print them as if fatal. Silence it here.
    global _FAULTHANDLER
    _FAULTHANDLER = faulthandler.is_enabled()
    faulthandler.disable()


def tearDownModule():
    if _FAULTHANDLER:
        faulthandler.enable(file=sys.stderr)


class PassEmulatorTests(unittest.TestCase):
    def test_ms32krnl_ordinals_resolve_to_win32_names(self):
        ex = c2_emu.krnl_exports()
        self.assertEqual(ex[0x19A], '_CreateFileA@28')
        self.assertEqual(ex[0x208], '_VirtualAlloc@16')
        self.assertEqual(ex[0x234], '_ExitProcess@4')

    def test_cl_flag_translation_matches_captured_pass_flags(self):
        cl = c2_emu.CLFlags(['/AL', '/G2', '/Gs', '/Oegilw', '/GA', '/NTGR_MODULE'])
        self.assertEqual(cl.c2(), '-ef "T:\\BIN\\c23.err" -il "W:\\185436" -A lfd -Bm 2048 '
                                  '-Oc -Oe -Og -Ol -On -Ot -Ow -G2 -GA -NT "GR_MODULE" -W 1 ')
        c1 = cl.c1()
        self.assertIn('-Oc -Oe -Og -Oi -Ol -On -Oo -Ot -Ow -Ze -G2 -GA -Gs', c1)
        self.assertIn('-D_WINDOWS', c1)
        self.assertIn('-GA -NM "input" -NT "GR_MODULE"', cl.c3())
        with self.assertRaises(ValueError):
            c2_emu.CLFlags(['/AL', '/Ox'])

    def test_admitted_source_object_is_byte_identical_to_dosbox(self):
        r = c2_emu.compile_c((ROOT / 'src/recovered/ABS.c').read_bytes(),
                             ['/AL', '/G2', '/Gs', '/Oelw', '/NTSIMANT_MODULE'])
        self.assertEqual(r.rc, {'c1': 0, 'c2': 0, 'c3': 0})
        self.assertEqual(hashlib.sha256(r.obj).hexdigest(),
                         '53d6cb4e6715e0f55e2b5cca6453d9b877a26d711a257edbdc38cc8398425ca5')

    def test_c1_minus_oe_is_carried_in_the_il_not_the_c2_command_line(self):
        cl = c2_emu.CLFlags(BASELINE)
        files = c2_emu.error_files()
        files['W:\\INPUT.C'] = TOY_LOOP
        with_oe, _ = c2_emu.run_pass('C13216.EXE', cl.c1(), dict(files))
        without, _ = c2_emu.run_pass('C13216.EXE', cl.c1().replace(' -Oe', ''), dict(files))
        a = with_oe.files[c2_emu.IL_PREFIX + 'EX']
        b = without.files[c2_emu.IL_PREFIX + 'EX']
        diff = [i for i in range(min(len(a), len(b))) if a[i] != b[i]]
        self.assertEqual(len(diff), 1)
        self.assertEqual(a[diff[0]] ^ b[diff[0]], 0x10)


class AllocatorTests(unittest.TestCase):
    def test_weight_formula_uses_depth_of_last_block_and_degree(self):
        from tools import alloc_trace
        _r, fns = alloc_trace.trace_source(TOY_LOOP, BASELINE)
        rows = alloc_trace.candidate_table(fns[0])
        loop_tmp = next(r for r in rows if r['name'] == 'tmp@-6' and r['depth'] == 1)
        # 0x440edc: uses * 16 * 4**depth // (degree + 1) + 0x8000
        self.assertEqual(loop_tmp['weight'], loop_tmp['uses'] * 16 * 4 // (loop_tmp['degree'] + 1) + 0x8000)
        self.assertEqual(loop_tmp['regname'], 'si')

    def test_model_reproduces_final_registers(self):
        from tools import regalloc_model as rm
        for src, flags in ((TOY_LOOP, BASELINE),
                           ((ROOT / 'src/recovered/AddBlackAnts-145548139d.c').read_bytes(),
                            ['/AL', '/G2', '/Gs', '/Oeglw', '/NTSIMTWO_MODULE'])):
            _r, fns = rm.capture(src, flags)
            rows = rm.compare(fns)
            self.assertTrue(rows)
            self.assertTrue(all(not r['mismatches'] for r in rows))
            full = rm.compare_full(fns)
            self.assertTrue(all(not r['final'] for r in full))

    def test_model_is_sensitive_to_the_register_order(self):
        from tools import regalloc_model as rm
        _r, fns = rm.capture((ROOT / 'src/recovered/AddBlackAnts-145548139d.c').read_bytes(),
                             ['/AL', '/G2', '/Gs', '/Oeglw', '/NTSIMTWO_MODULE'])
        orig = rm.Model.pick
        try:
            rm.Model.pick = lambda self, *a: {6: 7, 7: 6}.get(orig(self, *a), orig(self, *a))
            self.assertTrue(any(r['mismatches'] for r in rm.compare(fns)))
        finally:
            rm.Model.pick = orig

    def test_home_colouring_places_heaviest_home_nearest_bp(self):
        from tools import regalloc_model as rm
        _r, fns = rm.capture_homes(TOY_HOMES, BASELINE)
        rows = rm.compare_homes(fns)
        self.assertEqual(rows[0]['mismatches'], [])
        names = {d['id']: d['name'] for d in fns[0]['before']}
        by_slot = sorted(rows[0]['predicted'].items(), key=lambda kv: kv[1])
        self.assertEqual([names[i] for i, _s in by_slot], ['c', 'b', 'a'])

    def test_first_fit_shares_slots_between_non_interfering_homes(self):
        from tools import regalloc_model as rm
        before = [dict(id=1, weight=0x8010, size=2, interf=[]),
                  dict(id=2, weight=0x8008, size=2, interf=[]),
                  dict(id=3, weight=0x8004, size=4, interf=[1])]
        self.assertEqual(rm.predict_homes(before), {1: 0, 2: 0, 3: 2})


if __name__ == '__main__':
    unittest.main()

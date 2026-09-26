"""Source gate: `_asm` only in reviewed functions whose signature occurs in the original."""
import sys
import unittest
from pathlib import Path
from unittest import mock
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import promote
from common import FormatError

CARDS = [dict(symbol='_Rand2', disassembly=[dict(mnemonic='enter', operands='2, 0'), dict(mnemonic='mov', operands='dx, 0')]),
         dict(symbol='_Other', disassembly=[dict(mnemonic='ret', operands='')])]
REVIEW = dict(functions={'_Rand2': dict(signature='mov dx, 0'), '_Other': dict(signature='mov dx, 0')})
SOURCE = '''static unsigned int seed;
int Rand2(void)
{
    int result;
    _asm {
        mov dx, 0
        mov ax, seed
    }
    return result;
}
'''


class InlineAsmGate(unittest.TestCase):
    def gate(self, source, review=REVIEW):
        with mock.patch.object(promote, 'cards', return_value=CARDS), \
             mock.patch.object(promote, 'read_json', return_value=review), \
             mock.patch.object(promote.INLINE_ASM_REVIEW.__class__, 'is_file', return_value=True):
            return promote.reviewed_inline_asm(source)

    def test_reviewed_block_is_blanked(self):
        cleaned = self.gate(SOURCE)
        self.assertNotIn('_asm', cleaned)
        self.assertIn('return result;', cleaned)

    def test_unreviewed_function_keeps_block(self):
        self.assertIn('_asm', self.gate(SOURCE.replace('Rand2', 'Rand3')))

    def test_signature_must_occur_in_original(self):
        with self.assertRaises(FormatError):
            self.gate(SOURCE.replace('Rand2', 'Other'))

    def test_byte_emission_refused(self):
        with self.assertRaises(FormatError):
            self.gate(SOURCE.replace('mov dx, 0', '_emit 0x90'))

    def test_function_spans(self):
        spans = promote.function_spans('int a(void) { if (1) { } }\nstatic int b;\nvoid c(int x) { }')
        self.assertEqual([s[0] for s in spans], ['a', 'c'])


if __name__ == '__main__':
    unittest.main()

"""ASM source admission rules are exercised without launching a DOS runner."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from assembler import check_asm_source
from common import FormatError


HEADER = """; small hand-written routine
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _probe
_probe PROC NEAR
"""
FOOTER = """_probe ENDP
_TEXT ENDS
END
"""


class AssemblySourceRuleTests(unittest.TestCase):
    def test_real_instructions_and_ordinary_directives_are_accepted(self):
        source = HEADER + "    mov ax, 1\n    jmp finished\n    nop\nfinished:\n    ret\n" + FOOTER
        self.assertTrue(check_asm_source(source))

    def test_code_segment_byte_data_is_refused(self):
        source = HEADER + "    db 90h, 0C3h\n" + FOOTER
        with self.assertRaisesRegex(FormatError, 'byte data in a code segment'):
            check_asm_source(source)

    def test_numeric_word_data_is_not_a_dispatch_table(self):
        source = HEADER + "targets dw 0010h, 0020h\n    ret\n" + FOOTER
        with self.assertRaisesRegex(FormatError, 'label/offset jump table'):
            check_asm_source(source)

    def test_label_offset_dispatch_table_is_allowed_in_code(self):
        source = HEADER + "    jmp word ptr [bx]\ntargets dw OFFSET case_a, OFFSET case_b\ncase_a:\n    ret\ncase_b:\n    ret\n" + FOOTER
        self.assertTrue(check_asm_source(source))

    def test_data_directives_outside_code_are_not_misclassified(self):
        source = HEADER + "    ret\n" + FOOTER + "_DATA SEGMENT WORD PUBLIC 'DATA'\ncount dw 2\n_DATA ENDS\n"
        self.assertTrue(check_asm_source(source))

    def test_include_and_macro_languages_are_refused(self):
        for body in ("INCLUDE \"other.inc\"\n", "INCBIN \"machine.bin\"\n", "helper MACRO\nENDM\n"):
            with self.subTest(body=body), self.assertRaises(FormatError):
                check_asm_source(HEADER + body + FOOTER)

    def test_unknown_assembler_pseudo_directive_is_refused(self):
        source = HEADER + ".MAGIC 1\n    ret\n" + FOOTER
        with self.assertRaisesRegex(FormatError, 'unknown assembler directive'):
            check_asm_source(source)


if __name__ == '__main__':
    unittest.main()

"""The ABI audit must distinguish LINK-lowered far calls from true near calls."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from call_abi_audit import audit_source


class CallAbiAuditTests(unittest.TestCase):
    def test_near_prototype_is_flagged_only_for_linker_lowered_far_call(self):
        card = {"disassembly": [
            {"offset": 0x100, "bytes": "90", "mnemonic": "nop", "references": []},
            {"offset": 0x101, "bytes": "0e", "mnemonic": "push", "references": []},
            {"offset": 0x102, "bytes": "e80100", "mnemonic": "call", "references": [
                {"kind": "near_call", "offset": 0x106, "names": ["_FarTarget"]}
            ]},
            {"offset": 0x105, "bytes": "e80100", "mnemonic": "call", "references": [
                {"kind": "near_call", "offset": 0x109, "names": ["_NearTarget"]}
            ]},
        ]}
        source = "extern int near FarTarget(void);\nextern int near NearTarget(void);\n"
        resolved, findings = audit_source(source, card)
        self.assertEqual(resolved, 2)
        self.assertEqual(len(findings), 1)
        self.assertEqual(findings[0]["callee"], "FarTarget")
        self.assertEqual(findings[0]["sites"][0]["bytes"], "900ee80100")
        self.assertEqual(findings[0]["line"], 1)

    def test_far_prototype_and_unnamed_call_do_not_trigger(self):
        card = {"disassembly": [
            {"offset": 0x100, "bytes": "90", "mnemonic": "nop", "references": []},
            {"offset": 0x101, "bytes": "0e", "mnemonic": "push", "references": []},
            {"offset": 0x102, "bytes": "e80100", "mnemonic": "call", "references": [
                {"kind": "near_call", "offset": 0x106, "names": ["_FarTarget"]}
            ]},
        ]}
        source = "extern int far FarTarget(void);\nextern int near Unknown(void);\n"
        self.assertEqual(audit_source(source, card), (0, []))


if __name__ == "__main__":
    unittest.main()

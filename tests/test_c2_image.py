import struct
import unittest

from tools.c2_image import C2Image, C2ImageError


def fixture_image():
    """Minimal MZ + early DOSX32 image with code and string objects."""
    raw = bytearray(0x240)
    raw[:2] = b"MZ"
    struct.pack_into("<I", raw, 0x3C, 0x40)
    h = 0x40
    raw[h:h + 4] = b"PE\0\0"
    struct.pack_into("<I", raw, h + 0x24, 0x1000)
    struct.pack_into("<I", raw, h + 0x28, 0x400000)
    struct.pack_into("<I", raw, h + 0x50, 2)
    struct.pack_into("<I", raw, h + 0x54, 0x100)
    struct.pack_into("<I", raw, h + 0x6C, 0)
    # Six DWORDs per object: RVA, VirtualSize, SeekOffset, OnDiskSize,
    # ObjectFlags, Reserved.
    struct.pack_into("<6I", raw, 0x100, 0x1000, 16, 0x180, 16, 0x2005, 0)
    struct.pack_into("<6I", raw, 0x118, 0x200, 32, 0x1C0, 32, 0x2003, 0)
    # mov eax, 0x400200 ; push dword ptr [0x400210] ; ret
    raw[0x180:0x18C] = b"\xB8\x00\x02\x40\x00\xFF\x35\x10\x02\x40\x00\xC3"
    raw[0x1C0:0x1C9] = b"allocator\0"
    struct.pack_into("<I", raw, 0x1D0, 0x400200)
    return bytes(raw)


class C2ImageTests(unittest.TestCase):
    def test_header_and_object_table(self):
        image = C2Image(fixture_image())
        self.assertEqual(image.header_offset, 0x40)
        self.assertEqual(image.image_base, 0x400000)
        self.assertEqual(image.entry_point_rva, 0x1000)
        self.assertEqual(image.object_table_offset, 0x100)
        self.assertEqual([o.executable for o in image.objects], [True, False])

    def test_round_trip_uses_on_disk_extent(self):
        image = C2Image(fixture_image())
        self.assertEqual(image.file_to_va(0x183), 0x401003)
        self.assertEqual(image.va_to_file(0x401003), 0x183)
        with self.assertRaises(C2ImageError):
            image.file_to_va(0x190)  # end is exclusive
        with self.assertRaises(C2ImageError):
            image.va_to_file(0x402010)  # outside file-backed bytes

    def test_strings_and_direct_instruction_xref(self):
        image = C2Image(fixture_image())
        strings = image.find_strings(["alloc"])
        self.assertEqual([(s.file_offset, s.va, s.text) for s in strings],
                         [(0x1C0, 0x400200, "allocator")])
        xrefs = image.cross_references(strings)
        self.assertEqual(len(xrefs), 1)
        self.assertEqual((xrefs[0].source_file_offset, xrefs[0].source_va),
                         (0x180, 0x401000))
        self.assertEqual(xrefs[0].kind, "immediate")
        self.assertEqual([p["cell_file_offset"] for p in image.pointer_cells(strings)], [0x1D0])

    def test_follows_pointer_cell_to_code_xref(self):
        image = C2Image(fixture_image())
        result = image.string_xrefs(image.find_strings(["alloc"]))
        self.assertEqual(len(result["direct"]), 1)
        self.assertEqual(len(result["pointer_cells"]), 1)
        self.assertEqual(len(result["via_pointer_cells"]), 1)
        ref = result["via_pointer_cells"][0]
        self.assertEqual(ref["cell_file_offset"], 0x1D0)
        self.assertEqual(ref["source_file_offset"], 0x185)
        self.assertIn("[0x400210]", ref["instruction"])

    def test_rejects_bad_signature_and_out_of_bounds_table(self):
        raw = bytearray(fixture_image())
        raw[0x40:0x44] = b"NOPE"
        with self.assertRaises(C2ImageError):
            C2Image(bytes(raw))
        raw = bytearray(fixture_image())
        struct.pack_into("<I", raw, 0x40 + 0x54, 0x230)
        with self.assertRaises(C2ImageError):
            C2Image(bytes(raw))


if __name__ == "__main__":
    unittest.main()

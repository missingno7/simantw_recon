import hashlib
import struct
import unittest

from tools import mac_ref


def iso_dir_record(name: bytes, lba: int, size: int, flags: int = 0) -> bytes:
    pad = b"\0" if len(name) % 2 == 0 else b""
    record = bytearray(33 + len(name) + len(pad))
    record[0] = len(record)
    struct.pack_into("<I", record, 2, lba)
    struct.pack_into(">I", record, 6, lba)
    struct.pack_into("<I", record, 10, size)
    struct.pack_into(">I", record, 14, size)
    record[25] = flags
    record[32] = len(name)
    record[33:33 + len(name)] = name
    return bytes(record)


class MacRefParsingTests(unittest.TestCase):
    def test_iso9660_file_tree_and_hash(self):
        image = bytearray(22 * 2048)
        pvd = memoryview(image)[16 * 2048:17 * 2048]
        pvd[0] = 1
        pvd[1:6] = b"CD001"
        pvd[6] = 1
        root = iso_dir_record(b"\0", 20, 2048, flags=2)
        pvd[156:156 + len(root)] = root
        directory = bytearray(2048)
        dot = iso_dir_record(b"\0", 20, 2048, flags=2)
        dotdot = iso_dir_record(b"\1", 20, 2048, flags=2)
        file = iso_dir_record(b"FOO.TXT;1", 21, 3)
        directory[:len(dot)] = dot
        directory[len(dot):len(dot) + len(dotdot)] = dotdot
        directory[len(dot) + len(dotdot):len(dot) + len(dotdot) + len(file)] = file
        image[20 * 2048:21 * 2048] = directory
        image[21 * 2048:21 * 2048 + 3] = b"abc"
        files = mac_ref.parse_iso(bytes(image))
        self.assertEqual(len(files), 1)
        self.assertEqual(files[0]["path"], "FOO.TXT")
        self.assertEqual(files[0]["size"], 3)
        self.assertEqual(files[0]["sha256"], hashlib.sha256(b"abc").hexdigest())

    def test_apm_partition_record(self):
        image = bytearray(3 * 512)
        image[:2] = b"ER"
        struct.pack_into(">H", image, 2, 512)
        entry = memoryview(image)[512:1024]
        entry[:2] = b"PM"
        struct.pack_into(">I", entry, 4, 1)
        struct.pack_into(">I", entry, 8, 2)
        struct.pack_into(">I", entry, 12, 1)
        entry[16:20] = b"Test"
        entry[48:53] = b"Apple"
        parts = mac_ref.parse_apm(bytes(image))
        self.assertEqual(parts[0]["start_block"], 2)
        self.assertEqual(parts[0]["block_count"], 1)
        self.assertEqual(parts[0]["name"], "Test")

    def test_resource_fork_type_and_payload(self):
        data_off = 256
        payload = b"abc"
        data_area = struct.pack(">I", len(payload)) + payload
        map_off = data_off + len(data_area)
        resource_map = bytearray(50)
        struct.pack_into(">H", resource_map, 24, 28)  # type list
        struct.pack_into(">H", resource_map, 26, 50)  # empty name list
        struct.pack_into(">H", resource_map, 28, 0)  # one type
        resource_map[30:34] = b"CODE"
        struct.pack_into(">H", resource_map, 34, 0)  # one resource
        struct.pack_into(">H", resource_map, 36, 10)  # ref list at 38
        struct.pack_into(">h", resource_map, 38, 7)
        struct.pack_into(">H", resource_map, 40, 0xFFFF)
        resource_map[42] = 0
        resource_map[43:46] = b"\0\0\0"
        fork = bytearray(map_off + len(resource_map))
        struct.pack_into(">IIII", fork, 0, data_off, map_off, len(data_area), len(resource_map))
        fork[data_off:map_off] = data_area
        fork[map_off:] = resource_map
        resources, info = mac_ref.parse_resource_fork(bytes(fork))
        self.assertEqual(info["resource_count"], 1)
        self.assertEqual(resources[0]["type"], "CODE")
        self.assertEqual(resources[0]["id"], 7)
        self.assertEqual(resources[0]["data"], payload)

    def test_macsbug_variable_name_after_rts(self):
        code = bytearray(b"\0\0\0\0")
        code.extend(bytes.fromhex("4e56 0000 4e5e 4e75"))
        code.extend(bytes([0x87]))
        code.extend(b"_DoWork")
        code.extend(b"\0\0")  # aligned zero-length constant block
        symbols = mac_ref.scan_macsbug_symbols(bytes(code))
        self.assertEqual(len(symbols), 1)
        self.assertEqual(symbols[0]["name"], "_DoWork")
        spans = mac_ref.function_spans(1, bytes(code))
        self.assertEqual((spans[0]["start"], spans[0]["end"], spans[0]["size"]), (4, 12, 8))

    def test_macsbug_fixed_name_after_rts(self):
        code = b"\0\0\0\0" + bytes.fromhex("4e75") + b"_DoThing\0\0"
        symbols = mac_ref.scan_macsbug_symbols(code)
        self.assertEqual([item["name"] for item in symbols], ["_DoThing"])


class MacRefCorrespondenceTests(unittest.TestCase):
    def test_known_case_and_underscore_pair(self):
        sym = {"sha256": "fixture", "segments": [{"number": 1, "symbols": [
            {"name": "_DoWork", "offset": 0x1234}]}]}
        recovery = {"targets": {"_DoWork": {"proof": "BYTE_MATCHED_RECONSTRUCTION"}}}
        spans = {2: [{"name": "dowork", "code_id": 2, "start": 0x80,
                      "end": 0xA0, "size": 0x20}]}
        result = mac_ref.correspondence_from_records(sym, recovery, spans,
            {"export_count": 1, "source": "fixture"})
        self.assertEqual(result["coverage"]["admitted_with_mac_counterpart"], 1)
        self.assertEqual(result["coverage"]["open_with_mac_counterpart"], 0)
        self.assertEqual(result["symbols"]["_DoWork"]["mac"][0]["code_id"], 2)
        self.assertEqual(result["symbols"]["_DoWork"]["mac"][0]["size"], 0x20)


if __name__ == "__main__":
    unittest.main()

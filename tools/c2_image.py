"""Reader for the early DOSX32/PE image format used by MSC 7.00 C23216.

This is not a general PE parser. It implements the six-DWORD object table
documented for the C7 pass executables and deliberately maps only file-backed
object bytes. Capstone is loaded lazily so the offset mapper is usable without
the optional disassembler dependency.
"""
from __future__ import annotations

import argparse
import json
import re
import struct
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Iterable


class C2ImageError(ValueError):
    """Malformed or unsupported C23216 image."""


@dataclass(frozen=True)
class ObjectEntry:
    index: int
    rva: int
    virtual_size: int
    seek_offset: int
    on_disk_size: int
    flags: int
    reserved: int

    @property
    def file_end(self) -> int:
        return self.seek_offset + self.on_disk_size

    @property
    def rva_end(self) -> int:
        return self.rva + self.on_disk_size

    @property
    def executable(self) -> bool:
        # DOSX32 ObjectFlags uses bit 2 for executable (observed 0x2005 vs
        # 0x2003 in C23216: the former is the code object, the latter data).
        return bool(self.flags & 0x4)


@dataclass(frozen=True)
class StringRecord:
    file_offset: int
    va: int
    text: str


@dataclass(frozen=True)
class Xref:
    target_file_offset: int
    target_va: int
    source_file_offset: int
    source_va: int
    kind: str
    instruction: str


class C2Image:
    """Parsed DOSX32/early-PE image with offset/VA translation."""

    def __init__(self, data: bytes, *, header_offset: int | None = None,
                 table_offset: int | None = None):
        self.data = bytes(data)
        if header_offset is None:
            if len(data) < 0x40 or data[:2] != b"MZ":
                raise C2ImageError("missing DOS MZ header")
            header_offset = _u32(data, 0x3C)
        if header_offset < 0 or header_offset + 0x70 > len(data):
            raise C2ImageError("PE header lies outside file")
        if data[header_offset:header_offset + 4] != b"PE\0\0":
            raise C2ImageError(f"missing PE\\0\\0 signature at 0x{header_offset:x}")
        self.header_offset = header_offset
        self.entry_point_rva = _u32(data, header_offset + 0x24)
        self.image_base = _u32(data, header_offset + 0x28)
        self.number_of_objects = _u32(data, header_offset + 0x50)
        self.object_table_rva = _u32(data, header_offset + 0x54)
        self.number_of_special_rvas = _u32(data, header_offset + 0x6C)
        if self.number_of_objects == 0 or self.number_of_objects > 4096:
            raise C2ImageError(f"implausible object count {self.number_of_objects}")

        # In DOSX32 the header metadata is resident at RVA==raw offset. The
        # C23216 image follows this convention: ObjectTableRVA 0x1cc4 points
        # directly at raw 0x1cc4, before the first mapped object (RVA 0x20000).
        # Keep an override for fixture/forensic use, but refuse to guess a
        # translated table location from ordinary PE section rules.
        if table_offset is None:
            table_offset = self.object_table_rva
        self.object_table_offset = table_offset
        table_size = self.number_of_objects * 24
        if table_offset < 0 or table_offset + table_size > len(data):
            raise C2ImageError("object table lies outside file")
        self.objects = []
        for i in range(self.number_of_objects):
            vals = struct.unpack_from("<6I", data, table_offset + i * 24)
            obj = ObjectEntry(i, *vals)
            if obj.on_disk_size and obj.file_end > len(data):
                raise C2ImageError(f"object {i} file extent lies outside image")
            if obj.rva + obj.virtual_size > 0x1_0000_0000:
                raise C2ImageError(f"object {i} virtual extent overflows 32-bit address space")
            self.objects.append(obj)

    @classmethod
    def read(cls, path: str | Path, **kwargs) -> "C2Image":
        return cls(Path(path).read_bytes(), **kwargs)

    def object_for_file_offset(self, file_offset: int) -> ObjectEntry | None:
        found = [o for o in self.objects if o.seek_offset <= file_offset < o.file_end]
        if len(found) > 1:
            raise C2ImageError(f"ambiguous object mapping for file offset 0x{file_offset:x}")
        return found[0] if found else None

    def object_for_va(self, va: int) -> ObjectEntry | None:
        rva = va - self.image_base
        found = [o for o in self.objects if o.rva <= rva < o.rva_end]
        if len(found) > 1:
            raise C2ImageError(f"ambiguous object mapping for VA 0x{va:x}")
        return found[0] if found else None

    def file_to_va(self, file_offset: int) -> int:
        obj = self.object_for_file_offset(file_offset)
        if obj is None:
            raise C2ImageError(f"file offset 0x{file_offset:x} is not in an on-disk object")
        return self.image_base + obj.rva + (file_offset - obj.seek_offset)

    def va_to_file(self, va: int) -> int:
        obj = self.object_for_va(va)
        if obj is None:
            raise C2ImageError(f"VA 0x{va:x} is not backed by an on-disk object")
        return obj.seek_offset + (va - self.image_base - obj.rva)

    def find_strings(self, needles: Iterable[str | bytes] | None = None,
                     *, minimum: int = 4) -> list[StringRecord]:
        """Return printable NUL-terminated ASCII strings in file-backed objects.

        If needles are given, retain any string containing one of them. Search
        is intentionally limited to mapped objects rather than DOSX32 tables.
        """
        wanted = [n.decode("ascii", "replace") if isinstance(n, bytes) else n
                  for n in (needles or ())]
        records: list[StringRecord] = []
        for obj in self.objects:
            start, end = obj.seek_offset, obj.file_end
            chunk = self.data[start:end]
            for match in re.finditer(rb"[\x20-\x7e]{%d,}\x00" % minimum, chunk):
                raw = match.group()[:-1]
                try:
                    text = raw.decode("ascii")
                except UnicodeDecodeError:
                    continue
                if wanted and not any(n in text for n in wanted):
                    continue
                off = start + match.start()
                records.append(StringRecord(off, self.file_to_va(off), text))
        return records

    def disassemble(self, *, executable_only: bool = True):
        """Yield (object, file offset, VA, capstone instruction) in file order."""
        try:
            from capstone import Cs, CS_ARCH_X86, CS_MODE_32
        except ImportError as exc:  # pragma: no cover - environment dependent
            raise RuntimeError("capstone is required for disassembly") from exc
        md = Cs(CS_ARCH_X86, CS_MODE_32)
        md.detail = True
        for obj in self.objects:
            if executable_only and not obj.executable:
                continue
            start, end = obj.seek_offset, obj.file_end
            base_va = self.image_base + obj.rva
            for insn in md.disasm(self.data[start:end], base_va):
                yield obj, start + insn.address - base_va, insn.address, insn

    def cross_references(self, targets: Iterable[StringRecord | int]) -> list[Xref]:
        """Find direct immediate/moffs xrefs from executable instructions.

        `targets` may be StringRecord objects or file offsets. The report keeps
        the originating target string offset so repeated substrings are
        distinguishable. Indirect references through compiler tables are not
        guessed; the pointer-cell scan in `pointer_cells` is available for a
        second-stage xref investigation.
        """
        try:
            from capstone.x86 import X86_OP_IMM, X86_OP_MEM
        except ImportError as exc:  # pragma: no cover
            raise RuntimeError("capstone is required for xref scanning") from exc
        records = list(targets)
        by_va: dict[int, list[int]] = {}
        for target in records:
            off = target.file_offset if isinstance(target, StringRecord) else int(target)
            va = self.file_to_va(off)
            by_va.setdefault(va, []).append(off)
        xrefs: list[Xref] = []
        for _obj, source_off, source_va, insn in self.disassemble():
            for operand in insn.operands:
                values: list[tuple[int, str]] = []
                if operand.type == X86_OP_IMM:
                    values.append((operand.imm & 0xFFFFFFFF, "immediate"))
                elif operand.type == X86_OP_MEM and operand.mem.base == 0 and operand.mem.index == 0:
                    values.append((operand.mem.disp & 0xFFFFFFFF, "absolute-memory"))
                for value, kind in values:
                    for target_off in by_va.get(value, ()):
                        xrefs.append(Xref(target_off, value, source_off, source_va,
                                          kind, f"{insn.mnemonic} {insn.op_str}"))
        return xrefs

    def pointer_cells(self, targets: Iterable[StringRecord | int]) -> list[dict]:
        """Find file-backed DWORD cells containing mapped target VAs."""
        target_map: dict[int, list[int]] = {}
        for target in targets:
            off = target.file_offset if isinstance(target, StringRecord) else int(target)
            target_map.setdefault(self.file_to_va(off), []).append(off)
        rows = []
        for obj in self.objects:
            # The pointer tables and source records in C23216 are DWORD
            # aligned relative to file offset. Bytewise scanning sees many
            # false matches one byte before a genuine pointer because its
            # preceding padding byte is zero.
            first = (obj.seek_offset + 3) & ~3
            for cell in range(first, obj.file_end - 3, 4):
                value = _u32(self.data, cell)
                for target_off in target_map.get(value, ()):
                    rows.append({"cell_file_offset": cell, "cell_va": self.file_to_va(cell),
                                 "target_file_offset": target_off, "target_va": value,
                                 "object": obj.index, "executable_object": obj.executable})
        return rows

    def string_xrefs(self, strings: Iterable[StringRecord]) -> dict:
        """Report direct string refs and executable refs to pointer cells.

        C23216 stores many file/identifier string pointers in records. The
        latter need a two-stage lookup: find data DWORDs that point at the
        string, then find instructions that read those DWORD locations.
        """
        strings = list(strings)
        cells = self.pointer_cells(strings)
        indirect = []
        cell_offsets = sorted({row["cell_file_offset"] for row in cells})
        for cell_off in cell_offsets:
            for ref in self.cross_references([cell_off]):
                targets = sorted({row["target_file_offset"] for row in cells
                                  if row["cell_file_offset"] == cell_off})
                indirect.append({
                    "cell_file_offset": cell_off,
                    "cell_va": self.file_to_va(cell_off),
                    "target_file_offsets": targets,
                    "target_strings": [next(s.text for s in strings if s.file_offset == off)
                                       for off in targets],
                    "source_file_offset": ref.source_file_offset,
                    "source_va": ref.source_va,
                    "kind": ref.kind,
                    "instruction": ref.instruction,
                })
        return {"direct": [asdict(x) for x in self.cross_references(strings)],
                "pointer_cells": cells,
                "via_pointer_cells": indirect}

    def summary(self) -> dict:
        return {
            "header_offset": self.header_offset,
            "entry_point_rva": self.entry_point_rva,
            "entry_point_va": self.image_base + self.entry_point_rva,
            "image_base": self.image_base,
            "number_of_objects": self.number_of_objects,
            "object_table_rva": self.object_table_rva,
            "object_table_offset": self.object_table_offset,
            "number_of_special_rvas": self.number_of_special_rvas,
            "objects": [asdict(o) | {"file_end": o.file_end, "rva_end": o.rva_end,
                                     "executable": o.executable} for o in self.objects],
        }


def _u32(data: bytes, offset: int) -> int:
    if offset < 0 or offset + 4 > len(data):
        raise C2ImageError(f"32-bit field outside file at 0x{offset:x}")
    return struct.unpack_from("<I", data, offset)[0]


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("image", type=Path)
    ap.add_argument("--strings", nargs="*", help="only list strings containing these terms")
    ap.add_argument("--xrefs", action="store_true", help="find direct instruction refs to selected/all strings")
    ap.add_argument("--minimum-string", type=int, default=4)
    args = ap.parse_args()
    image = C2Image.read(args.image)
    report = image.summary()
    strings = image.find_strings(args.strings, minimum=args.minimum_string)
    report["strings"] = [asdict(s) for s in strings]
    if args.xrefs:
        report["string_xrefs"] = image.string_xrefs(strings)
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()

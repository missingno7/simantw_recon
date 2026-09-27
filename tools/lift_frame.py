"""Frame oracle and candidate ordering search for the MSC 7 lifter.

The target side is read from the byte-identical admitted-source `/Zi` record;
the candidate side is read from search.py's `/Zi` frame report.  This remains a
diagnostic and generation aid.  Whole-member proof still belongs to search and
promotion.
"""
from __future__ import annotations

from dataclasses import dataclass
from itertools import permutations
from typing import Any, Iterable

import frame_map


def signature(report: dict[str, Any] | None) -> tuple[Any, ...] | None:
    """Names differ between lifted and admitted source; compare homes/registers."""
    if not report or report.get("status") != "OK":
        return None
    homes = tuple(sorted((int(x["offset"]), int(x.get("size") or 2))
                         for x in report.get("candidate_locals", [])))
    regs = tuple(sorted((str(x.get("register")), frame_map.type_size(int(x.get("type", 0))) or 2)
                        for x in report.get("candidate_registers", [])))
    return report.get("candidate_enter"), homes, regs


def frame_exact(candidate: dict[str, Any] | None, oracle: dict[str, Any] | None) -> bool:
    """Whether MSC emitted the same frame extent, stack homes, and register set."""
    left, right = signature(candidate), signature(oracle)
    return left is not None and right is not None and left == right


def target_access_exact(candidate: dict[str, Any] | None) -> bool:
    """Fallback when an admitted `/Zi` oracle is unavailable.

    Requires the same ENTER size and every observed target BP slot to be covered
    by a candidate named home at the same displacement.
    """
    if not candidate or candidate.get("status") != "OK":
        return False
    if candidate.get("candidate_enter") != candidate.get("target_enter"):
        return False
    homes = candidate.get("candidate_locals", [])
    target = candidate.get("target_slots", {})
    for offset_text, widths in target.items():
        offset = int(offset_text)
        need = max((w for w in widths if isinstance(w, int)), default=1)
        if not any(int(h["offset"]) == offset and (h.get("size") or 2) >= need for h in homes):
            return False
    target_starts = {int(x) for x in target}
    if any(int(h["offset"]) not in target_starts for h in homes):
        return False
    return True


@dataclass(frozen=True)
class FrameVariant:
    name: str
    order: tuple[str, ...]
    merges: tuple[tuple[str, ...], ...] = ()


class FrameSolver:
    """Controlled declaration-order candidates from observed BP slot evidence."""

    def __init__(self, slots: Iterable[Any], disassembly: list[dict[str, Any]]):
        self.slots = list(slots)
        self.disassembly = disassembly
        self.first_use: dict[str, int] = {}
        self.refs: dict[str, int] = {}
        self.loop_refs: dict[str, int] = {}
        self.address_taken: set[str] = set()
        self.overlap_groups: list[tuple[str, ...]] = []
        loop_spans: list[tuple[int, int]] = []
        for row in disassembly:
            mnemonic = str(row.get("mnemonic", "")).lower()
            offset = int(row.get("offset", 0))
            if mnemonic.startswith("j"):
                try:
                    target = int(str(row.get("operands", "")).split()[0], 0)
                    if target < offset:
                        loop_spans.append((target, offset))
                except (ValueError, IndexError):
                    pass
        for index, row in enumerate(disassembly):
            text = str(row.get("operands", ""))
            mnemonic = str(row.get("mnemonic", "")).lower()
            offset = int(row.get("offset", index))
            for slot in self.slots:
                off = abs(int(slot.displacement))
                if f"bp - 0x{off:x}" in text.lower() or f"bp - {off}" in text.lower():
                    self.first_use.setdefault(slot.name, index)
                    self.refs[slot.name] = self.refs.get(slot.name, 0) + 1
                    if mnemonic == "lea":
                        self.address_taken.add(slot.name)
                    if any(start <= offset <= end for start, end in loop_spans):
                        self.loop_refs[slot.name] = self.loop_refs.get(slot.name, 0) + 1
        # Overlapping observations can be one wider local viewed at several
        # offsets, or distinct split locals. Keep the observed split as the
        # default and offer a byte-array merge only as a compiler-tested trial.
        remaining = set(range(len(self.slots)))
        while remaining:
            i = remaining.pop()
            group = {i}
            changed = True
            while changed:
                changed = False
                a0 = int(self.slots[i].displacement)
                a1 = a0 + int(self.slots[i].width)
                for j in list(remaining):
                    b0 = int(self.slots[j].displacement)
                    b1 = b0 + int(self.slots[j].width)
                    if max(a0, b0) < min(a1, b1) or any(
                            max(int(self.slots[k].displacement), b0) <
                            min(int(self.slots[k].displacement) + int(self.slots[k].width), b1)
                            for k in group):
                        group.add(j); remaining.remove(j); changed = True
            if len(group) > 1:
                self.overlap_groups.append(tuple(self.slots[k].name for k in sorted(group)))
        self._orders = self._build_orders()

    def _build_orders(self) -> list[FrameVariant]:
        names = [x.name for x in self.slots]
        if len(names) < 2:
            return [FrameVariant("observed", tuple(names))]
        orders: list[FrameVariant] = []
        def add(label: str, seq: list[str]):
            value = tuple(seq)
            if value not in {x.order for x in orders}:
                orders.append(FrameVariant(label, value))
        add("bp-near-first", names)
        add("bp-far-first", list(reversed(names)))
        add("first-use", sorted(names, key=lambda n: (self.first_use.get(n, 10**9), n)))
        add("reference-hot", sorted(names, key=lambda n: (-self.refs.get(n, 0), self.first_use.get(n, 10**9), n)))
        add("small-first", sorted(names, key=lambda n: (next(x.width for x in self.slots if x.name == n), self.first_use.get(n, 10**9))))
        if names and all(n in self.address_taken for n in names):
            add("address-only", sorted(names, key=lambda n: (
                next(x.width for x in self.slots if x.name == n),
                -self.refs.get(n, 0), self.first_use.get(n, 10**9), n)))
        add("loop-hot", sorted(names, key=lambda n: (-self.loop_refs.get(n, 0),
                                                       -self.refs.get(n, 0),
                                                       self.first_use.get(n, 10**9), n)))
        # Probe each pairwise declaration exchange; this catches the common
        # mixed-width home-order residue without exploding into n! candidates.
        for i in range(len(names) - 1):
            trial = list(names)
            trial[i], trial[i + 1] = trial[i + 1], trial[i]
            add(f"swap-{i}-{i+1}", trial)
        if len(names) <= 5:
            for n, seq in enumerate(permutations(names)):
                add(f"perm-{n}", list(seq))
                if len(orders) >= 24:
                    break
        return orders

    def variants(self, limit: int = 24) -> list[FrameVariant]:
        variants = list(self._orders)
        base = tuple(x.name for x in self.slots)
        for i, group in enumerate(self.overlap_groups):
            variants.append(FrameVariant(f"merge-{i}", base, (group,)))
        return variants[:max(1, limit)]


__all__ = ["FrameSolver", "FrameVariant", "frame_exact", "signature", "target_access_exact"]

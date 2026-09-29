"""Trace MSC 7.00 C2's global register allocator (globregs.c / glregs86.c) on a C source.

Runs CL's three passes under tools/c2_emu.py (byte-identical to the DOSBox
compiler on all admitted sources) and instruments C23216 to dump, for every
function compiled with /Oe, the allocator's candidate table:

  * one row per live-range candidate ("web"): variable name (or temp@BPoff),
    register class, first/last block order numbers, loop depth of the last
    block, static use count, interference degree, weight, flags, the order in
    which the colouring loop (0x441404) took it, whether it was allocated or
    spilled, the physical register chosen by 0x441a80/0x466a20, and whether
    the post-pass 0x442fac dropped a register for lack of payoff.

Recovered C2 addresses (C23216.EXE, image base 0x400000):

  0x43edd4  per-function global register allocation driver (arg: block list)
  0x440c7c  class loop (class 1 = byte, 2 = word, 3 = segment/far halves)
  0x441020  interference: +0x10 bitset, +0x14 degree (# overlapping ranges with uses)
  0x440edc  weight: uses*16*4^depth/(degree+1) + 0x8000 (depth from LAST block)
  0x441330  insertion sort by weight, descending (ties: later element first)
  0x441404  colouring/selection loop (80% window, more uses wins)
  0x441658  can-allocate test (free registers in every block of the range)
  0x4416e4  commit: reg=0xffff, decrement free counts in the range's blocks
  0x441a80  physical register choice through 0x466a20
  0x466a20  register picker: live-across-call (+0x2c&0x40) -> SI, DI; else DX, CX, SI, DI
  0x442fac  drop SI/DI/CX if (saves+1) > uses

Usage::

    python tools/alloc_trace.py SOURCE.c [CL flags...]  (default /AL /G2 /Gs /Oelw /NT_TEXT)
    python tools/alloc_trace.py --symbol _Func DRAFT.c   (flags from the symbol's profile)
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import c2_emu  # noqa: E402

REGNAMES = {0: 'ax', 1: 'cx', 2: 'dx', 3: 'bx', 6: 'si', 7: 'di', 8: 'es', 9: 'cs', 10: 'ss', 11: 'ds',
            0xE: 'al', 0xF: 'cl', 0x10: 'dl', 0x11: 'bl', 0x12: 'ah', 0x13: 'ch', 0x14: 'dh', 0x15: 'bh',
            -2: '-', -1: 'pending'}
CLASS_LISTS = (0x488D90, 0x488F2C, 0x4853F4)   # spill/work list, second list, allocated list
CUR_CLASS = 0x487960
FUNC_SYM = 0x471ED8


def _ident(b):
    s = b.split(b'\0')[0]
    try:
        t = s.decode('ascii')
    except UnicodeDecodeError:
        return None
    return t if t and (t[0].isalpha() or t[0] == '_') and all(c.isalnum() or c == '_' for c in t) else None


class Tracer:
    def __init__(self, emu):
        self.emu = emu
        self.functions = []
        self.cur = None
        e = emu
        e.add_code_hook(0x43EDD4, self.on_func)
        e.add_code_hook(0x440EDC, self.on_weight_entry)
        e.add_code_hook(0x441558, self.on_pick)
        e.add_code_hook(0x441566, self.on_alloc)
        e.add_code_hook(0x441590, self.on_spill)
        e.add_code_hook(0x4412F2, self.on_trivial)      # 0x441274 trivially-colourable fast path
        e.add_code_hook(0x441EC2, self.on_regpick)
        e.add_code_hook(0x443048, self.on_drop)
        e.add_code_hook(0x440CD3, self.on_weighted)
        e.add_code_hook(0x440E19, self.on_weighted)
        e.add_code_hook(0x4417C5, self.on_unassign)
        e.add_code_hook(0x4427E5, self.on_repick)
        e.add_code_hook(0x43EFE9, lambda _e: self.snapshot('before_colour'))
        e.add_code_hook(0x43EFEE, lambda _e: self.snapshot('after_colour'))
        e.add_code_hook(0x43EFF3, lambda _e: self.snapshot('final'))

    # ---------------------------------------------------------------- decoding
    def sym_name(self, sym):
        e = self.emu
        if not sym:
            return None
        raw = bytes(e.uc.mem_read(sym, 0x60))
        for off in (0x1C, 0x20, 0x34):
            n = _ident(raw[off:off + 32])
            if n:
                return n
        return 'sym@%x' % sym

    def cand(self, c):
        e = self.emu
        raw = bytes(e.uc.mem_read(c, 0x3C))
        cid = struct.unpack_from('<h', raw, 0)[0]
        v = struct.unpack_from('<I', raw, 4)[0]
        node = e.rd32(v + 4)
        op = e.rd32(node)
        typ = e.rd16(node + 6)
        sym = e.rd32(node + 8)
        name = None
        bpoff = None
        if sym:
            name = self.sym_name(sym)
            flags = e.rd16(sym + 0xC)
            if e.rd16(sym + 4) == 1 and not flags & 0x8000:
                bpoff = struct.unpack('<h', e.uc.mem_read(sym + 0x18, 2))[0]
        else:
            try:
                child = e.rd32(node + 0x10)
                if child and e.rd32(child) == 0x26:
                    bpoff = struct.unpack('<i', e.uc.mem_read(child + 0x10, 4))[0]
            except Exception:
                bpoff = None
            name = 'tmp@%d' % bpoff if bpoff is not None else 'tmp@%x' % node
        first, last = struct.unpack_from('<II', raw, 8)
        depth = 0
        lp = e.rd32(last + 0x24) if last else 0
        while lp:
            depth += 1
            lp = e.rd32(lp + 8)
        ring = []
        r = struct.unpack_from('<I', raw, 0x38)[0]
        n = 0
        while r and r != c and n < 64:
            ring.append(e.rd16(r))
            r = e.rd32(r + 0x38)
            n += 1
        reg = struct.unpack_from('<h', raw, 0x20)[0]
        return dict(id=cid, name=name, op=op, type=typ, bp=bpoff,
                    first=e.rd16(first + 0x5C) if first else None,
                    last=e.rd16(last + 0x5C) if last else None,
                    depth=depth, uses=struct.unpack_from('<h', raw, 0x28)[0],
                    degree=struct.unpack_from('<h', raw, 0x14)[0],
                    weight=struct.unpack_from('<I', raw, 0x24)[0],
                    flags=struct.unpack_from('<I', raw, 0x2C)[0],
                    mask=struct.unpack_from('<I', raw, 0x1C)[0],
                    reg=reg, regname=REGNAMES.get(reg, str(reg)), ring=ring, addr=c)

    def walk(self, head):
        out = []
        n = 0
        while head and n < 4096:
            out.append(head)
            head = self.emu.rd32(head + 0x30)
            n += 1
        return out

    def lists(self):
        e = self.emu
        res = {}
        for base, label in ((0x488D90, 'work'), (0x488F2C, 'other'), (0x4853F4, 'alloc')):
            for k in range(4):
                res['%s%d' % (label, k)] = [self.cand(c) for c in self.walk(e.rd32(base + 4 * k))]
        return res

    # ---------------------------------------------------------------- hooks
    def on_func(self, e):
        fsym = e.rd32(FUNC_SYM)
        self.cur = dict(function=self.sym_name(fsym) if fsym else None, events=[], snapshots={},
                        weights={})
        self.functions.append(self.cur)

    def on_weight_entry(self, e):
        cls = e.rd32(CUR_CLASS)
        head = e.arg(0)
        self.cur['events'].append(('weigh', cls, [e.rd16(c) for c in self.walk(head)]))

    def on_weighted(self, e):
        cls = e.rd32(CUR_CLASS)
        head = e.rd32(0x488D90 + 4 * cls)
        w = self.cur['weights']
        for c in self.walk(head):
            d = self.cand(c)
            w[d['id']] = dict(cls=cls, weight=d['weight'], degree=d['degree'], uses=d['uses'],
                              depth=d['depth'], flags=d['flags'], first=d['first'], last=d['last'])
        self.cur['events'].append(('weighted', cls, [(e.rd16(c), e.rd32(c + 0x24)) for c in self.walk(head)]))

    def on_unassign(self, e):
        from unicorn.x86_const import UC_X86_REG_ESI, UC_X86_REG_EIP
        c = e.reg_read(UC_X86_REG_ESI)
        self.cur['events'].append(('unassign', e.rd32(CUR_CLASS), e.rd16(c), REGNAMES.get(e.rd16(c + 0x20), '?')))

    def on_repick(self, e):
        from unicorn.x86_const import UC_X86_REG_ESI, UC_X86_REG_EBP
        c = e.reg_read(UC_X86_REG_ESI)
        new = struct.unpack('<h', e.uc.mem_read(e.reg_read(UC_X86_REG_EBP) - 0xC, 2))[0]
        self.cur['events'].append(('repick', e.rd32(CUR_CLASS), e.rd16(c),
                                   REGNAMES.get(struct.unpack('<h', e.uc.mem_read(c + 0x20, 2))[0], '?'),
                                   REGNAMES.get(new, str(new))))

    def on_pick(self, e):
        # edi points at the list link holding the chosen candidate
        from unicorn.x86_const import UC_X86_REG_EDI
        link = e.reg_read(UC_X86_REG_EDI)
        c = e.rd32(link)
        self.cur['events'].append(('pick', e.rd32(CUR_CLASS), e.rd16(c)))

    def on_alloc(self, e):
        from unicorn.x86_const import UC_X86_REG_EDI
        c = e.rd32(e.reg_read(UC_X86_REG_EDI))
        self.cur['events'].append(('alloc', e.rd32(CUR_CLASS), e.rd16(c)))

    def on_spill(self, e):
        from unicorn.x86_const import UC_X86_REG_EDI
        c = e.rd32(e.reg_read(UC_X86_REG_EDI))
        self.cur['events'].append(('spill', e.rd32(CUR_CLASS), e.rd16(c)))

    def on_trivial(self, e):
        from unicorn.x86_const import UC_X86_REG_ESI
        c = e.reg_read(UC_X86_REG_ESI)
        self.cur['events'].append(('trivial', e.rd32(CUR_CLASS), e.rd16(c)))

    def on_regpick(self, e):
        from unicorn.x86_const import UC_X86_REG_ESI, UC_X86_REG_EAX
        c = e.reg_read(UC_X86_REG_ESI)
        reg = e.reg_read(UC_X86_REG_EAX)
        if reg & 0x80000000:
            reg -= 1 << 32
        self.cur['events'].append(('reg', e.rd32(CUR_CLASS), e.rd16(c), REGNAMES.get(reg, str(reg))))

    def on_drop(self, e):
        from unicorn.x86_const import UC_X86_REG_EAX
        c = e.reg_read(UC_X86_REG_EAX)
        self.cur['events'].append(('drop', None, e.rd16(c), REGNAMES.get(e.rd16(c + 0x20), '?')))

    def snapshot(self, label):
        self.cur['snapshots'][label] = self.lists()


def _patch_emu():
    # small helper so hooks can read registers through the emulator object
    def reg_read(self, r):
        return self.uc.reg_read(r)
    c2_emu.PassEmulator.reg_read = reg_read


_patch_emu()


def trace_source(source: bytes, flags):
    tracer = {}

    def hooks(emu):
        tracer['t'] = Tracer(emu)
    res = c2_emu.compile_c(source, flags, c2_hooks=hooks)
    return res, tracer['t'].functions


def candidate_table(fn):
    """Merge snapshots into one row per candidate id."""
    rows = {}
    for label in ('before_colour', 'after_colour', 'final'):
        snap = fn['snapshots'].get(label, {})
        for lst, cands in snap.items():
            for c in cands:
                r = rows.setdefault(c['id'], dict(c))
                r.setdefault('lists', {})[label] = lst
                if label == 'before_colour':
                    r.update({k: c[k] for k in ('uses', 'degree', 'weight', 'flags', 'depth', 'first', 'last')})
                if label == 'final':
                    r['reg'] = c['reg']
                    r['regname'] = c['regname']
    order = {}
    k = 0
    for ev in fn['events']:
        if ev[0] in ('pick', 'trivial'):
            order.setdefault(ev[2], k)
            k += 1
        if ev[0] in ('alloc', 'spill', 'trivial'):
            rows.get(ev[2], {})['decision'] = 'alloc' if ev[0] != 'spill' else 'spill'
        if ev[0] == 'reg' and ev[2] in rows:
            rows[ev[2]]['picked'] = ev[3]
        if ev[0] == 'drop' and ev[2] in rows:
            rows[ev[2]]['dropped'] = ev[3]
    for cid, r in rows.items():
        r['order'] = order.get(cid)
        wt = fn['weights'].get(cid)
        if wt:
            r.update(wt)
    for ev in fn['events']:
        if ev[0] == 'unassign' and ev[2] in rows:
            rows[ev[2]]['unassigned'] = ev[3]
        if ev[0] == 'repick' and ev[2] in rows:
            rows[ev[2]]['repicked'] = ev[4]
        if ev[0] == 'drop' and ev[2] in rows:
            rows[ev[2]]['dropped'] = ev[3]
    return sorted(rows.values(), key=lambda r: (r.get('order') is None, r.get('order') or 0, r['id']))


def cls_of(r):
    if 'cls' in r:
        return r['cls']
    return {'work1': 1, 'work2': 2, 'work3': 3, 'other1': 1, 'other2': 2, 'other3': 3,
            'alloc1': 1, 'alloc2': 2, 'alloc3': 3}.get(r.get('lists', {}).get('before_colour'), 0)


def format_function(fn):
    out = ['== %s' % fn['function']]
    out.append('%3s %-14s %3s %5s %4s %5s %5s %3s %8s %8s %5s %-6s %-5s %s' % (
        'id', 'name', 'cls', 'blk', 'dep', 'uses', 'deg', 'ord', 'weight', 'flags', 'dec', 'picked', 'final', 'ring'))
    for r in candidate_table(fn):
        picked = r.get('picked', '') + ('>' + r['repicked'] if r.get('repicked') else '') +             ('!' if r.get('unassigned') else '') + ('$' if r.get('dropped') else '')
        out.append('%3d %-14s %3s %2s-%-2s %4d %5d %5d %3s %8x %8x %5s %-6s %-5s %s' % (
            r['id'], (r['name'] or '?')[:14], cls_of(r), r['first'], r['last'], r['depth'], r['uses'],
            r['degree'], '' if r.get('order') is None else r['order'], r['weight'], r['flags'],
            r.get('decision', ''), picked, r['regname'], ','.join(map(str, r['ring']))))
    return '\n'.join(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('source')
    ap.add_argument('flags', nargs='*')
    ap.add_argument('--symbol', help='take CL flags from this symbol\'s assigned profile')
    ap.add_argument('--function', help='only print this compiled function (C name, no underscore)')
    ap.add_argument('--json', help='write the raw trace as JSON')
    ap.add_argument('--events', action='store_true', help='also print the allocator event log')
    a = ap.parse_args(argv)
    flags = a.flags
    if a.symbol:
        from promote import function_flags
        _p, flags = function_flags(a.symbol)
    if not flags:
        flags = ['/AL', '/G2', '/Gs', '/Oelw', '/NT_TEXT']
    res, fns = trace_source(Path(a.source).read_bytes(), flags)
    if res.rc.get('c1') or res.rc.get('c2'):
        print(res.messages)
    for fn in fns:
        if a.function and fn['function'] != a.function:
            continue
        print(format_function(fn))
        if a.events:
            for ev in fn['events']:
                print('   ', ev)
    if a.json:
        Path(a.json).write_text(json.dumps(fns, indent=1, default=str))


if __name__ == '__main__':
    main()

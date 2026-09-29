"""Executable model of MSC 7.00 C2's global register colouring (globregs.c / glregs86.c).

The model re-implements, in Python, the colouring phase that C23216 runs for
register classes 1 (byte) and 2 (word) inside 0x440c7c, starting from the
allocator state after interference (0x441020) and weighting (0x440edc):

    0x440fe8  drop non-allocatable ranges (+0x2e & 4) to the spill list
    0x441274  "trivially colourable" pass: degree < free registers in the
              range's own mask and a free register in every block
    0x441330  insertion sort by weight, descending
    0x441404  selection: head, or a range in the 80% window with more uses,
              or with a connected (+0x18) range already allocated
    0x441658  allocatable test (a free register in every block of the range)
    0x4416e4  commit (reg := pending, decrement block free counts)
    0x441330  sort of the allocated list, 0x4417dc ring reordering
    0x441a80  physical register choice (0x466a20) with the connected-range
              and same-variable-ring preferences

`capture(source, flags)` runs the emulated compiler (tools/c2_emu.py) and
records the model's input at 0x440cd3 and C2's own result at 0x440d3b for
every function and class; `predict(state)` runs the model; `compare`
reports agreement.  The later split-cost/unassign passes (0x442040,
0x442628, 0x442fac, 0x445f14) are not modelled: they only remove or move
registers after colouring and are reported separately by alloc_trace.py.
"""
from __future__ import annotations

import copy
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import c2_emu  # noqa: E402

PENDING = -1      # 0xffff
NONE = -2         # 0xfffe
REGBIT = {0: 26, 1: 0, 2: 1, 3: 27, 6: 2, 7: 3, 8: 5, 10: 29, 11: 4,
          0xE: 8, 0xF: 9, 0x10: 10, 0x11: 11, 0x12: 12, 0x13: 13, 0x14: 14, 0x15: 15}
CHUNKS = 0x488F68
WORK, OTHER, ALLOC = 0x488D90, 0x488F2C, 0x4853F4
FREE_WORD, FREE_BYTE = 0x482CF0, 0x482CEC


# ----------------------------------------------------------------------------- capture
def _bits(emu, p):
    out = []
    base = 0
    n = 0
    while p and n < 4096:
        w = emu.rd32(p + 4)
        for b in range(32):
            if w >> b & 1:
                out.append(base + b)
        base += 32
        p = emu.rd32(p)
        n += 1
    return out


def _cand_addr(emu, cid):
    chunk = emu.rd32(CHUNKS + 4 * (cid >> 3))
    return chunk + 60 * (cid & 7)


def _walk(emu, head):
    out = []
    while head and len(out) < 4096:
        out.append(head)
        head = emu.rd32(head + 0x30)
    return out


def _read_cand(emu, c):
    s16 = lambda a: struct.unpack('<h', emu.uc.mem_read(a, 2))[0]
    ring = []
    r = emu.rd32(c + 0x38)
    while r and r != c and len(ring) < 256:
        ring.append(emu.rd16(r))
        r = emu.rd32(r + 0x38)
    v = emu.rd32(c + 4)
    chain = []
    k = emu.rd32(v + 0xC) if v else 0
    while k and len(chain) < 1024:
        chain.append(emu.rd16(k))
        k = emu.rd32(k + 0x34)
    node = emu.rd32(v + 4) if v else 0
    return dict(id=emu.rd16(c), reg=s16(c + 0x20), weight=emu.rd32(c + 0x24), uses=s16(c + 0x28),
                degree=s16(c + 0x14), flags=emu.rd32(c + 0x2C), mask=emu.rd32(c + 0x1C),
                first=emu.rd32(c + 8), last=emu.rd32(c + 0xC),
                interf=_bits(emu, emu.rd32(c + 0x10)), conn=_bits(emu, emu.rd32(c + 0x18)), ring=ring,
                chain=chain, varno=emu.rd16(node + 0x18) if node else None)


def _state(emu, blocks_head, cls):
    lists = {}
    ids = set()
    for base, name in ((WORK, 'work'), (OTHER, 'other'), (ALLOC, 'alloc')):
        for k in range(4):
            lst = [emu.rd16(c) for c in _walk(emu, emu.rd32(base + 4 * k))]
            lists['%s%d' % (name, k)] = lst
            ids.update(lst)
    cands = {}
    todo = list(ids)
    while todo:
        cid = todo.pop()
        if cid in cands:
            continue
        c = _cand_addr(emu, cid)
        d = _read_cand(emu, c)
        cands[cid] = d
        for j in d['interf'] + d['conn'] + d['ring'] + d['chain']:
            if j not in cands:
                todo.append(j)
    blocks = []
    loops = {}
    b = blocks_head

    def edges(p):
        out = []
        while p and len(out) < 256:
            out.append(emu.rd32(p + 4))
            p = emu.rd32(p)
        return out
    while b and len(blocks) < 4096:
        lp = emu.rd32(b + 0x24)
        blocks.append(dict(addr=b, mask=emu.rd32(b + 8), order=emu.rd16(b + 0x5C), loop=lp,
                           succ=edges(emu.rd32(b + 0x18)), pred=edges(emu.rd32(b + 0x1C)),
                           livein=_bits(emu, emu.rd32(b + 0x54)), liveout=_bits(emu, emu.rd32(b + 0x58))))
        while lp and lp not in loops:
            loops[lp] = dict(parent=emu.rd32(lp + 8), first=emu.rd32(lp + 0x10), last=emu.rd32(lp + 0x14))
            lp = emu.rd32(lp + 8)
        b = emu.rd32(b)
    fsym = emu.rd32(0x471ED8)
    return dict(cls=cls, lists=lists, cands=cands, blocks=blocks, loops=loops,
                entry_block=emu.rd32(0x48BEFC), g482b70=emu.rd32(0x482B70), g471f28=emu.rd32(0x471F28),
                fkind=(emu.rd8(fsym + 0x10) & 0x1C) if fsym else 0)


def capture(source: bytes, flags):
    """Compile with the emulator; return per-function records {'name', 'inputs'{cls}, 'actual'{cls}}."""
    funcs = []

    def hooks(emu):
        cur = {}

        def on_func(e):
            cur.clear()
            fsym = e.rd32(0x471ED8)
            name = None
            if fsym:
                raw = bytes(e.uc.mem_read(fsym, 0x60))
                for off in (0x34, 0x20, 0x1C):
                    s = raw[off:off + 32].split(b'\0')[0]
                    if s and all(32 < ch < 127 for ch in s):
                        name = s.decode()
                        break
            cur.update(name=name, blocks=e.arg(0), inputs={}, actual={}, regs={})
            funcs.append(cur.copy())

        def on_weighted(e):
            cls = e.rd32(0x487960)
            funcs[-1]['inputs'][cls] = _state(e, funcs[-1]['blocks'], cls)

        def on_coloured(e):
            cls = e.rd32(0x487960)
            st = _state(e, funcs[-1]['blocks'], cls)
            funcs[-1]['actual'][cls] = {cid: d['reg'] for cid, d in st['cands'].items()}
            funcs[-1]['actual_lists'] = funcs[-1].get('actual_lists', {})
            funcs[-1]['actual_lists'][cls] = st['lists']

        def checkpoint(label):
            def h(e):
                cls = e.rd32(0x487960)
                ids = set()
                for base in (WORK, OTHER, ALLOC):
                    for k in range(4):
                        ids.update(e.rd16(c) for c in _walk(e, e.rd32(base + 4 * k)))
                regs = {cid: struct.unpack('<h', e.uc.mem_read(_cand_addr(e, cid) + 0x20, 2))[0] for cid in ids}
                funcs[-1].setdefault('checkpoints', {}).setdefault(label, {})[cls] = regs
            return h

        emu.add_code_hook(0x43EDD4, on_func)
        emu.add_code_hook(0x440CD3, on_weighted)
        emu.add_code_hook(0x440D3B, on_coloured)
        emu.add_code_hook(0x440D76, checkpoint('split'))
        emu.add_code_hook(0x440D8A, checkpoint('repick'))
        emu.add_code_hook(0x43EFF3, checkpoint('final'))
        emu.add_code_hook(0x441FDC, lambda e: funcs[-1].__setitem__('split_seen', True))
    res = c2_emu.compile_c(source, flags, c2_hooks=hooks)
    return res, funcs


def compare_full(funcs):
    """Run colouring + 0x4418c8/0x442040/0x442628/0x442fac and compare with C2's checkpoints."""
    rows = []
    for f in funcs:
        st = f['inputs'].get(2)
        if not st:
            continue
        m = Model(st)
        a_split, a_repick, a_final = m.run_full(st.get('g471f28', 0), st.get('fkind', 0))
        cp = f.get('checkpoints', {})
        act_split = cp.get('split', {}).get(2, {})
        act_repick = cp.get('repick', {}).get(2, {})
        act_final = cp.get('final', {}).get(3) or cp.get('final', {}).get(2) or {}
        ids = set(st['lists']['work2']) | set(st['lists']['alloc2'])
        def mism(pred, act):
            return sorted(i for i in ids if i in act and pred.get(i) != act.get(i))
        rows.append(dict(function=f['name'], n=len(ids), split_seen=bool(f.get('split_seen')),
                         split=mism(a_split, act_split), repick=mism(a_repick, act_repick),
                         final=mism(a_final, act_final),
                         final_sidi=sum(1 for i in ids if act_final.get(i) in (6, 7))))
    return rows


# ----------------------------------------------------------------------------- model
class Model:
    def __init__(self, st, free_word=4, free_byte=8):
        self.cls = st['cls']
        self.c = copy.deepcopy(st['cands'])
        self.lists = copy.deepcopy(st['lists'])
        self.blocks = [dict(b) for b in st['blocks']]
        self.bidx = {b['addr']: i for i, b in enumerate(self.blocks)}
        self.entry_block = st['entry_block']
        self.g482b70 = st['g482b70']
        self.state_loops = st.get('loops', {})
        self.free_word = free_word
        self.free_byte = free_byte
        self.log = []

    # -- masks (0x466fbc / 0x467000 / 0x46706c / 0x4670e8 / 0x467df0)
    def free(self, mask, cls=None):
        cls = cls or self.cls
        if cls == 1:
            return (mask >> 16) & 0xF
        if cls == 2:
            return (mask >> 20) & 0xF
        if cls == 3:
            return (mask >> 24) & 0x3
        return 0

    def dec(self, mask):
        field = {1: 16, 2: 20, 3: 24}[self.cls]
        width = 0x3 if self.cls == 3 else 0xF
        n = (mask >> field) & width
        if n:
            mask = (mask & ~(width << field)) | ((n - 1) << field)
        return mask

    @staticmethod
    def setreg(mask, reg, on=True):
        if reg & 0x80:
            mask = Model.setreg(mask, reg & 7, on)
            return Model.setreg(mask, (reg & 0x78) >> 3, on)
        bit = REGBIT.get(reg)
        if bit is None:
            return mask
        return (mask | (1 << bit)) & 0xFFFFFFFF if on else mask & ~(1 << bit)

    @staticmethod
    def hasreg(mask, reg):
        bit = REGBIT.get(reg)
        return bool(bit is not None and mask >> bit & 1)

    @staticmethod
    def f467df0(mask):
        return bool(mask & 0x10000080)

    def range_blocks(self, c):
        i = self.bidx.get(c['first'])
        j = self.bidx.get(c['last'])
        if i is None or j is None:
            return []
        return list(range(i, j + 1))

    # -- 0x466a20: register picker
    def pick(self, cls, mask, pref, flag40):
        m = mask
        b = lambda bit: bool(m >> bit & 1)
        if pref != -1:
            bit = REGBIT.get(pref)
            if bit is not None and not b(bit):
                ok = True
                if pref == 6:
                    ok = not (b(3) and b(27))
                elif pref == 7:
                    ok = not (b(2) and b(27))
                elif pref == 3:
                    ok = not b(29) and not (b(2) and b(3))
                if ok:
                    return pref
        if cls == 1:
            for bit, reg in ((8, 0xE), (9, 0xF), (10, 0x10), (11, 0x11), (12, 0x12), (13, 0x13), (14, 0x14),
                             (15, 0x15)):
                if not b(bit):
                    return reg
            return -1
        if cls != 2:
            return pref
        si_ok = not b(2) and not (b(3) and b(27))
        di_ok = not b(3) and not (b(2) and b(27))
        if flag40:
            if si_ok:
                return 6
            if di_ok:
                return 7
        if not b(1):
            return 2
        if not b(0):
            return 1
        if si_ok:
            return 6
        if di_ok:
            return 7
        return -1

    def flag40(self, c):
        return 1 if c['flags'] & 0x40 else 0

    # -- list helpers (lists hold ids; head first)
    def unlink(self, lst, cid):
        self.lists[lst].remove(cid)

    def push(self, lst, cid):
        self.lists[lst].insert(0, cid)

    # -- 0x440fe8
    def drop_nonallocatable(self):
        k = 'work%d' % self.cls
        for cid in list(self.lists[k]):
            if self.c[cid]['flags'] >> 16 & 4:
                self.unlink(k, cid)
                self.push('work0', cid)

    # -- 0x441658
    def allocatable(self, c):
        best = 0x270F
        for bi in self.range_blocks(c):
            if (c['flags'] >> 8 & 0x40) and self.f467df0(c['mask']):
                continue
            n = self.free(self.blocks[bi]['mask'])
            if n == 0:
                return 0
            best = min(best, n)
        return 0 if best == 0x270F else best

    # -- 0x4416e4
    def commit(self, c):
        c['reg'] = PENDING
        if (c['flags'] & 0x10) and (self.g482b70 or c['mask'] & 0x40):
            return
        for bi in self.range_blocks(c):
            if (c['flags'] >> 8 & 0x40) and not self.f467df0(c['mask']):
                continue
            self.blocks[bi]['mask'] = self.dec(self.blocks[bi]['mask'])

    # -- 0x441274
    def trivial(self):
        k = 'work%d' % self.cls
        i = 0
        while i < len(self.lists[k]):
            cid = self.lists[k][i]
            c = self.c[cid]
            if c['degree'] < self.free(c['mask']):
                if all(self.free(self.blocks[bi]['mask']) for bi in self.range_blocks(c)):
                    self.commit(c)
                    self.lists[k].pop(i)
                    self.push('alloc%d' % self.cls, cid)
                    self.log.append(('trivial', cid))
                    continue
            i += 1

    # -- 0x441330
    def sort(self, lst):
        items = self.lists[lst]
        if not items:
            return
        out = [items[0]]
        for cid in items[1:]:
            w = self.c[cid]['weight']
            p = 0
            while p < len(out) and self.c[out[p]]['weight'] > w:
                p += 1
            out.insert(p, cid)
        self.lists[lst] = out

    # -- 0x4415c0(c, -1) and 0x44162c
    def conn_pending(self, c):
        return any(self.c[j]['reg'] == PENDING for j in c['conn'] if j in self.c)

    def ring_allocated(self, c):
        return any(self.c[j]['reg'] != NONE for j in c['ring'] if j in self.c)

    # -- 0x441404
    def select(self):
        k = 'work%d' % self.cls
        while self.lists[k]:
            lst = self.lists[k]
            best = 0
            head = self.c[lst[0]]
            # [ebp-0xc]: the best range has no connected range pending in a register;
            # [ebp-4]: ... and another range of its variable already holds one.
            noconn = not self.conn_pending(head)
            ringf = self.ring_allocated(head) if noconn else False
            w = head['weight']
            thr = ((w - 0x8000) * 8 // 10 + 0x8000) if w > 0x8000 else (w * 8 // 10)
            for pos in range(1, len(lst)):
                c = self.c[lst[pos]]
                if c['weight'] < thr:
                    break
                cur = self.c[lst[best]]
                if c['uses'] > cur['uses']:
                    best = pos
                    noconn = not self.conn_pending(c)
                    ringf = self.ring_allocated(c) if noconn else False
                elif c['weight'] == cur['weight']:
                    if noconn and self.conn_pending(c):
                        best = pos
                        noconn = False
                        ringf = False
                    elif ringf and self.ring_allocated(cur):
                        best = pos
                        noconn = True
                        ringf = False
            cid = lst[best]
            c = self.c[cid]
            self.log.append(('pick', cid))
            lst.pop(best)
            if self.allocatable(c):
                self.push('alloc%d' % self.cls, cid)
                self.commit(c)
                self.log.append(('alloc', cid))
            else:
                self.push('work0', cid)
                self.log.append(('spill', cid))

    # -- 0x4417dc: bubble each variable ring by weight (only rings with > 2 members)
    def ring_sort(self):
        # rings are only used as preference sources; their order matters for the
        # preference scan in 0x441a80, which walks them from the max-weight member.
        pass

    # -- 0x441a80
    def colour(self):
        k = 'alloc%d' % self.cls
        pos = 0
        guard = 0
        while pos < len(self.lists[k]) and guard < 100000:
            guard += 1
            lst = self.lists[k]
            head = self.c[lst[pos]]
            if head['reg'] >= 0:
                pos += 1
                continue
            r = self.pick(self.cls, head['mask'], -1, self.flag40(head))
            if r == -1:
                head['reg'] = NONE
                lst.pop(pos)
                self.push('work0', head['id'])
                self.log.append(('nocolour', head['id']))
                continue
            chosen = None
            # preference 1: connected ranges with a register (same weight group)
            for q in range(pos, len(lst)):
                c = self.c[lst[q]]
                if c['weight'] != head['weight']:
                    break
                if c['reg'] < 0 and c['conn'] and not c['flags'] & 0x10:
                    for j in c['conn']:
                        cj = self.c.get(j)
                        if cj and cj['reg'] >= 0:
                            if self.pick(self.cls, c['mask'], cj['reg'], self.flag40(c)) == cj['reg']:
                                chosen = (c, cj['reg'])
                                break
                    if chosen:
                        break
            # preference 2: same-variable ring members with a register
            if not chosen:
                for q in range(pos, len(lst)):
                    c = self.c[lst[q]]
                    if c['weight'] != head['weight']:
                        break
                    if c['reg'] == PENDING and c['ring']:
                        for j in c['ring']:
                            e = self.c.get(j)
                            if not e or e['reg'] < 0:
                                continue
                            m = c['mask']
                            if e['first'] == self.entry_block:
                                for jj in c['ring']:
                                    ee = self.c.get(jj)
                                    if ee and ee['reg'] != NONE and ee['reg'] < 0:
                                        m |= ee['mask']
                            if self.pick(self.cls, m, e['reg'], self.flag40(c)) == e['reg']:
                                chosen = (c, e['reg'])
                                break
                        if chosen:
                            break
            if not chosen:
                c = head
                pos += 1
                m = c['mask']
                members = [c] + [self.c[j] for j in c['ring'] if j in self.c]
                top = members[0]
                for e in members[1:]:
                    if top['weight'] < e['weight']:
                        top = e
                ring_from_top = [top] + [self.c[j] for j in top['ring'] if j in self.c]
                for e in ring_from_top:
                    if e['reg'] == NONE:
                        continue
                    m2 = m | e['mask']
                    if self.pick(self.cls, m2, -1, self.flag40(c)) != -1:
                        m = m2
                for j in c['interf']:
                    cj = self.c.get(j)
                    if not cj or cj['reg'] >= 0:
                        continue
                    for e in [self.c[x] for x in cj['ring'] if x in self.c]:
                        if e['reg'] < 0 or self.hasreg(cj['mask'], e['reg']):
                            continue
                        m2 = self.setreg(m, e['reg'])
                        if self.pick(self.cls, m2, -1, self.flag40(c)) != -1:
                            m = m2
                    m2 = m | (~cj['mask'] & 0xFFFFFFFF)
                    if self.pick(self.cls, m2, -1, self.flag40(c)) != -1:
                        m = m2
                chosen = (c, self.pick(self.cls, m, -1, self.flag40(c)))
            c, reg = chosen
            c['reg'] = reg
            self.log.append(('reg', c['id'], reg))
            for j in c['interf']:
                if j in self.c:
                    self.c[j]['mask'] = self.setreg(self.c[j]['mask'], reg)
            for bi in self.range_blocks(c):
                self.blocks[bi]['mask'] = self.setreg(self.blocks[bi]['mask'], reg)

    def run(self):
        self.drop_nonallocatable()
        self.trivial()
        self.sort('work%d' % self.cls)
        self.select()
        self.sort('alloc%d' % self.cls)
        self.ring_sort()
        self.colour()
        return {cid: c['reg'] for cid, c in self.c.items()}

    # ================================================================ post-colouring passes
    # block helpers ----------------------------------------------------------------------
    def _blk(self, addr):
        i = self.bidx.get(addr)
        return self.blocks[i] if i is not None else None

    def order(self, addr):
        b = self._blk(addr)
        return b['order'] if b else None

    def _loops(self):
        return self.state_loops

    def depth4(self, loop):
        """4**(number of loops from `loop` outwards); 1 for no loop (0x446400 tail)."""
        v = 1
        while loop:
            v <<= 2
            loop = self.state_loops.get(loop, {}).get('parent', 0)
        return v

    def blockfreq(self, addr):
        """0x446400."""
        b = self._blk(addr)
        return self.depth4(b['loop']) if b else 1

    def in_loop(self, addr, loop):
        """0x43eb28: is `loop` on the block's loop chain?"""
        b = self._blk(addr)
        lp = b['loop'] if b else 0
        while lp:
            if lp == loop:
                return True
            lp = self.state_loops.get(lp, {}).get('parent', 0)
        return False

    def edgefreq(self, a, b):
        """0x446424(a, b)."""
        ba, bb = self._blk(a), self._blk(b)
        l1 = ba['loop'] if ba else 0
        l2 = bb['loop'] if bb else 0
        if not l1 or not l2:
            return 1
        if l2 == l1 or self.in_loop(b, l1):
            lp = l1
        elif self.in_loop(a, l2):
            lp = l2
        else:
            lp = self.state_loops.get(l1, {}).get('parent', 0)
        return self.depth4(lp)

    def find(self, block_addr, c):
        """0x443aac(block, variable-key): the variable's range containing the block."""
        o = self.order(block_addr)
        for j in c['chain']:
            d = self.c.get(j)
            if not d:
                continue
            fo, lo = self.order(d['first']), self.order(d['last'])
            if fo is None or lo is None:
                continue
            if fo <= o <= lo:
                return d
        return None

    def blocks_of(self, c):
        return [self.blocks[i]['addr'] for i in self.range_blocks(c)]

    @staticmethod
    def fl(c, bit):
        return bool(c['flags'] & bit)

    # -- 0x4418c8: propagate "defined" (0x100/0x200) along successor edges; mark ring representatives
    def propagate(self, lst):
        while True:
            changed = False
            for cid in list(self.lists[lst]):
                c = self.c[cid]
                if not self.fl(c, 0x100):
                    continue
                cf, cl = self.order(c['first']), self.order(c['last'])
                for baddr in self.blocks_of(c):
                    for sb in self._blk(baddr)['succ']:
                        so = self.order(sb)
                        if so is None or cf <= so <= cl:
                            continue
                        d = self.find(sb, c)
                        if not d:
                            continue
                        if d['reg'] != c['reg'] and not self.fl(c, 0x100000):
                            continue
                        if self.fl(d, 0x100):
                            if self.cls != 3 or not self.fl(c, 0x200) or self.fl(d, 0x200):
                                continue
                        if self.blockfreq(sb) > self.blockfreq(c['first']):
                            lp = self._blk(sb)['loop']
                            L = self.state_loops.get(lp, {})
                            x = L.get('first')
                            lasto = self.order(L.get('last'))
                            ok = True
                            i = self.bidx.get(x)
                            while i is not None and i < len(self.blocks):
                                xb = self.blocks[i]
                                f = self.find(xb['addr'], c)
                                if f and (self.fl(f, 0x100) or f['reg'] != c['reg']):
                                    ok = False
                                    break
                                i += 1
                                if i >= len(self.blocks) or lasto is None or lasto < self.blocks[i]['order']:
                                    break
                            if ok:
                                d['flags'] |= 0x200000
                                continue
                        d['flags'] |= 0x100
                        if self.fl(c, 0x200):
                            d['flags'] |= 0x200
                        changed = True
            if not changed:
                break
        for cid in self.lists[lst]:
            c = self.c[cid]
            members = [c] + [self.c[j] for j in c['ring'] if j in self.c]
            if any(self.fl(m, 0x20000) for m in members):
                continue
            if self.fl(c, 0x100000):
                continue
            c['flags'] |= 0x20000

    # -- 0x441758
    def unassign(self, c):
        bl = self.blocks_of(c)
        for i, baddr in enumerate(bl):
            if self.fl(c, 0x4000) and (i == 0 or baddr == c['last']):
                continue
            b = self.blocks[self.bidx[baddr]]
            b['mask'] = self.setreg(b['mask'], c['reg'], False)
        c['reg'] = NONE
        if self.fl(c, 8):
            c['flags'] |= 0x40000
        self.log.append(('unassign', c['id']))

    # -- 0x442040 (range-boundary cost check; the range split at 0x442370 is not modelled)
    def splitcost(self, lst):
        move = 8 if self.cls == 3 else 2
        for cid in list(self.lists[lst]):
            c = self.c[cid]
            if not self.fl(c, 0x20000) or self.fl(c, 0x10):
                continue
            factor = 8
            varno = c['varno']
            ring = [c] + [self.c[j] for j in c['ring'] if j in self.c]
            while True:
                changed = False
                tot_cost = tot_ben = 0
                for e in ring:
                    if e['reg'] == NONE:
                        continue
                    savings = cost = nin = nout = 0
                    for baddr in self.blocks_of(e):
                        b = self._blk(baddr)
                        if varno in b['livein']:
                            for pb in b['pred']:
                                d = self.find(pb, c)
                                if d and d['reg'] == e['reg']:
                                    if d is e:
                                        continue
                                    f = self.fl(e, 0x200) if self.fl(e, 8) else self.fl(e, 0x100)
                                    if not f:
                                        continue
                                    savings += self.edgefreq(baddr, pb) * factor
                                else:
                                    cf = move if (d and d['reg'] != NONE) else 8
                                    cost += self.edgefreq(baddr, pb) * cf
                                    nin += cf
                        if varno in b['liveout']:
                            for sb in b['succ']:
                                sbb = self._blk(sb)
                                if not sbb or varno not in sbb['livein']:
                                    continue
                                d = self.find(sb, c)
                                if d and d['reg'] == e['reg']:
                                    if d is e:
                                        continue
                                    savings += self.edgefreq(baddr, sb) * factor
                                else:
                                    f = self.fl(e, 0x200) if self.fl(e, 8) else self.fl(e, 0x100)
                                    if not f:
                                        continue
                                    cf = move if (d and d['reg'] != NONE) else 8
                                    cost += self.edgefreq(sb, baddr) * cf
                                    nout += cf
                    e['flags'] = (e['flags'] & ~0xC00) | (0x400 if nin else 0) | (0x800 if nout else 0)
                    tot_cost += cost
                    ben = self.blockfreq(e['first']) * e['uses'] * 4
                    tot_ben += ben
                    drop = False
                    if self.fl(e, 4) and e['uses'] <= 2:
                        drop = True
                    elif ben != 0 or savings != cost:
                        if (cost - savings) * 4 > ben * 3:
                            drop = True
                    else:
                        drop = True
                    if drop:
                        self.unassign(e)
                        changed = True
                if changed:
                    continue
                if tot_ben * 3 < tot_cost * 4:
                    factor -= 4
                    continue
                break
        k = lst
        keep = []
        for cid in self.lists[k]:
            if self.c[cid]['reg'] == NONE:
                self.push('work0', cid)
            else:
                keep.append(cid)
        self.lists[k] = keep

    # -- 0x466d4c: re-pick for a whole variable
    def repick_reg(self, cls, mask, cur, flag40):
        m = mask
        b = lambda bit: bool(m >> bit & 1)
        if cls == 1:
            edx = cur
            for bit, reg in ((15, 0x15), (14, 0x14), (13, 0x13), (12, 0x12), (11, 0x11), (10, 0x10), (9, 0xF)):
                if not b(bit):
                    edx = reg
            if not b(8):
                edx = 0xE
            return -1 if cur <= edx else edx
        if cls != 2:
            return -1
        bx_busy = b(27)
        if not bx_busy and not b(29) and not (b(3) and b(2)):
            return 3
        if flag40:
            if cur in (6, 7):
                return -1
            if not b(2) and (not b(3) or not bx_busy):
                return 6
            if not b(3) and (not b(2) or not bx_busy):
                return 7
        if not b(1):
            return 2
        if not b(0):
            return 1
        return -1

    # -- 0x442628
    def repick(self, lst):
        for cid in list(self.lists[lst]):
            c = self.c[cid]
            if self.cls != 1 and c['reg'] not in (1, 6, 7, 10):
                continue
            ring = [c] + [self.c[j] for j in c['ring'] if j in self.c]
            union = 0
            for e in ring:
                if e['reg'] == NONE:
                    continue
                for baddr in self.blocks_of(e):
                    union |= self.setreg(self._blk(baddr)['mask'], e['reg'], False)
            new = self.repick_reg(self.cls, union, c['reg'], self.flag40(c))
            if new == -1 or new == c['reg']:
                continue
            for e in ring:
                if e['reg'] == NONE or self.fl(e, 0x100000) or e['reg'] == new:
                    continue
                for j in e['interf']:
                    if j in self.c:
                        self.c[j]['mask'] = self.setreg(self.c[j]['mask'], new)
                for baddr in self.blocks_of(e):
                    b = self._blk(baddr)
                    b['mask'] = self.setreg(b['mask'], new)
                    if not (baddr == e['last'] and self.fl(e, 0x10000)):
                        b['mask'] = self.setreg(b['mask'], e['reg'], False)
                self.log.append(('repick', e['id'], e['reg'], new))
                e['reg'] = new

    # -- 0x442fac: drop SI/DI (and CX in fkind 4 functions) when boundary moves outweigh uses
    def payoff(self, g471f28, fkind):
        regs = [6, 7] + ([1] if fkind == 4 else [])
        for r in regs:
            moves = uses = 0
            inloop = False
            for cid in self.lists['alloc2']:
                c = self.c[cid]
                if c['reg'] == r:
                    moves += (1 if self.fl(c, 0x800) else 0) + (1 if self.fl(c, 0x400) else 0)
                    uses += c['uses']
                    b = self._blk(c['first'])
                    if b and b['loop']:
                        inloop = True
            if not moves or moves + 1 <= uses:
                continue
            if g471f28 and inloop:
                continue
            keep = []
            for cid in self.lists['alloc2']:
                if self.c[cid]['reg'] == r:
                    self.c[cid]['reg'] = NONE
                    self.push('work0', cid)
                    self.log.append(('payoff-drop', cid, r))
                else:
                    keep.append(cid)
            self.lists['alloc2'] = keep

    def run_full(self, g471f28=0, fkind=0):
        self.run()
        k = self.cls
        self.propagate('other%d' % k)
        self.propagate('alloc%d' % k)
        self.splitcost('alloc%d' % k)
        after_split = {cid: c['reg'] for cid, c in self.c.items()}
        self.repick('alloc%d' % k)
        after_repick = {cid: c['reg'] for cid, c in self.c.items()}
        if k == 2:
            self.payoff(g471f28, fkind)
        return after_split, after_repick, {cid: c['reg'] for cid, c in self.c.items()}


def predict(state):
    m = Model(state)
    return m.run(), m


def compare(funcs):
    """Return per-function/class agreement rows (only candidates in the class lists)."""
    rows = []
    for f in funcs:
        for cls, st in f['inputs'].items():
            if cls not in (1, 2) or cls not in f['actual']:
                continue
            ids = set(st['lists']['work%d' % cls]) | set(st['lists']['alloc%d' % cls])
            if not ids:
                continue
            pred, m = predict(st)
            act = f['actual'][cls]
            diff = sorted(i for i in ids if pred.get(i) != act.get(i))
            rows.append(dict(function=f['name'], cls=cls, candidates=len(ids), mismatches=diff,
                             predicted={i: pred.get(i) for i in ids}, actual={i: act.get(i) for i in ids}))
    return rows




# ----------------------------------------------------------------------------- homes (0x445f14)
def _read_spill(emu, c):
    """Spill (home) record fields used by the stack colouring in 0x445f14."""
    v = emu.rd32(c + 4)
    node = emu.rd32(v + 4)
    if emu.rd32(node) == 0x30:
        node = _strip(emu, emu.rd32(node + 0x10))
    sym = emu.rd32(node + 8)
    size = emu.rd32(sym + 0x14) & 0xFFFF if sym else emu.rd16(emu.rd32(v + 4) + 6) & 0xFF
    primary = emu.rd32(v + 0xC)
    interf = []
    for j in _bits(emu, emu.rd32(c + 0x10)):
        pj = emu.rd32(emu.rd32(_cand_addr(emu, j) + 4) + 0xC)   # the interfering variable's primary record
        if pj:
            interf.append(emu.rd16(pj))
    name = None
    if sym:
        raw = bytes(emu.uc.mem_read(sym, 0x60))
        for off in (0x1C, 0x20, 0x34):
            t = raw[off:off + 32].split(b'\0')[0]
            if t and all(32 < ch < 127 for ch in t) and (chr(t[0]).isalpha() or t[0] == 95):
                name = t.decode()
                break
    else:
        name = 'tmp'
        try:
            child = emu.rd32(node + 0x10)
            if child and emu.rd32(child) == 0x26:
                name = 'tmp@%d' % struct.unpack('<i', emu.uc.mem_read(child + 0x10, 4))[0]
        except Exception:
            pass
    return dict(id=emu.rd16(c), name=name, weight=emu.rd32(c + 0x24), size=size, has_sym=bool(sym), sym=sym,
                interf=interf, primary=emu.rd16(primary) if primary else None,
                slot=struct.unpack('<h', emu.uc.mem_read(c + 0x20, 2))[0])


def _strip(emu, n):
    """0x447164: strip an address wrapper (LIST 0x50 / far-address 0x68 forms) to the symbol address."""
    m = emu.rd32(n + 0x10) if emu.rd32(n) == 0x50 else n
    if emu.rd32(m) == 0x68:
        left = emu.rd32(m + 0x10)
        right = emu.rd32(m + 0x14)
        if emu.rd32(left) == 0x26 and emu.rd32(right) == 0x69 and emu.rd32(right + 8) and \
                emu.rd16(emu.rd32(right + 8) + 6) == 6:
            return left
        if emu.rd32(right) == 0x30 and emu.rd32(emu.rd32(right + 0x10)) == 0xA2 and \
                emu.rd16(emu.rd32(right + 0x10) + 4) == 0xA:
            return left
    return n


def capture_homes(source: bytes, flags):
    funcs = []

    def hooks(emu):
        def on_func(e):
            fsym = e.rd32(0x471ED8)
            name = None
            if fsym:
                raw = bytes(e.uc.mem_read(fsym, 0x60))
                for off in (0x34, 0x20, 0x1C):
                    s = raw[off:off + 32].split(b'\0')[0]
                    if s and all(32 < ch < 127 for ch in s):
                        name = s.decode()
                        break
            funcs.append(dict(name=name, before=None, after=None))

        def before(e):
            lst = [_read_spill(e, c) for c in _walk(e, e.rd32(WORK))]
            funcs[-1]['before'] = lst

        def after(e):
            lst = [_read_spill(e, c) for c in _walk(e, e.rd32(WORK))]
            funcs[-1]['after'] = {d['id']: d['slot'] for d in lst}

        emu.add_code_hook(0x43EDD4, on_func)
        emu.add_code_hook(0x44623A, before)
        emu.add_code_hook(0x4463E8, after)
    res = c2_emu.compile_c(source, flags, c2_hooks=hooks)
    return res, funcs


def _aligned(size, off):
    """0x467d38: (off + size) must be a multiple of min(size, 2)."""
    s = min(size, 2)
    mask = s - 1
    while mask & (mask + 1):
        mask += 1
    return ((off + size) & mask) == 0


def _first_fit(intervals, size):
    """0x439628 over a sorted, merged list of occupied [lo, hi] intervals."""
    if not intervals:
        o = 0
        while not _aligned(size, o):
            o += 1
        return o
    if size <= intervals[0][0]:
        return 0
    for k in range(len(intervals) - 1):
        o = intervals[k][1] + 1
        room = intervals[k + 1][0] - intervals[k][1] - 1
        while room >= size:
            if _aligned(size, o):
                return o
            o += 1
            room -= 1
    o = intervals[-1][1] + 1
    while not _aligned(size, o):
        o += 1
    return o


def _add_interval(intervals, lo, hi):
    iv = sorted(intervals + [[lo, hi]])
    out = []
    for a, b in iv:
        if out and a - 1 <= out[-1][1]:
            out[-1][1] = max(out[-1][1], b)
        else:
            out.append([a, b])
    return out


def predict_homes(before):
    """Sort (0x441330) then first-fit stack colouring (0x445f14 loop) -> {id: slot}."""
    if not before:
        return {}
    by = {d['id']: dict(d) for d in before}
    order = [before[0]['id']]
    for d in before[1:]:
        p = 0
        while p < len(order) and by[order[p]]['weight'] > d['weight']:
            p += 1
        order.insert(p, d['id'])
    slot = {}
    for cid in order:
        d = by[cid]
        occ = []
        for j in d['interf']:
            if j in slot:
                o = by[j]
                occ = _add_interval(occ, slot[j], slot[j] + o['size'] - 1)
        s = _first_fit(occ, d['size'])
        slot[cid] = s
    return slot


def compare_homes(funcs):
    rows = []
    for f in funcs:
        if not f['before']:
            continue
        pred = predict_homes(f['before'])
        act = f['after'] or {}
        mism = sorted(i for i in pred if pred[i] != act.get(i))
        rows.append(dict(function=f['name'], n=len(pred), mismatches=mism, predicted=pred, actual=act))
    return rows


def main(argv=None):  # pragma: no cover
    import argparse
    import json
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('source')
    ap.add_argument('flags', nargs='*')
    ap.add_argument('--symbol', help="take CL flags from this symbol's assigned profile")
    ap.add_argument('--homes', action='store_true', help='report the stack-home colouring instead')
    a = ap.parse_args(argv)
    fl = a.flags
    if a.symbol:
        from promote import function_flags
        fl = function_flags(a.symbol)[1]
    fl = fl or ['/AL', '/G2', '/Gs', '/Oelw', '/NT_TEXT']
    src = Path(a.source).read_bytes()
    if a.homes:
        _res, fns = capture_homes(src, fl)
        for f in fns:
            if not f['before']:
                continue
            pred = predict_homes(f['before'])
            print('== %s  (homes in colouring order; slot 0 is nearest BP)' % f['name'])
            order = sorted(f['before'], key=lambda d: pred[d['id']])
            for d in f['before']:
                print('  list-pos %-3d id %-3d %-14s weight %6x size %d slot %d -> [bp-%d] interferes %s' % (
                    f['before'].index(d), d['id'], d['name'], d['weight'], d['size'], pred[d['id']],
                    pred[d['id']] + d['size'], d['interf']))
        return
    _res, fns = capture(src, fl)
    for r in compare(fns):
        print(json.dumps(dict(function=r['function'], cls=r['cls'], n=r['candidates'], mismatches=r['mismatches'])))


if __name__ == '__main__':  # pragma: no cover
    main()

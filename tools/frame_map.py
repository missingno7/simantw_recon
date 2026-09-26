"""Diagnostic frame map: where a candidate's named locals live versus the target frame.

    python tools/search.py SYMBOL candidate.c --frame

MSC 7.00 with /Zi emits CodeView symbols but byte-identical code (checked per
candidate: the map is reported only when the /Zi code segment equals the plain
compile). The CodeView BP-relative and register records give each named local's
exact frame offset or register. The target side is inferred from the original
function's `[bp-N]` accesses and their widths. The report names candidate
locals the target frame never touches and target slots no candidate local
covers, e.g. "extra 2-byte local pp at -2; target frame is 4 bytes".

Diagnostic only: nothing here is proof, and the strict matcher never reads it.
"""
import re
import struct

CV_REGISTERS = {1: 'al', 2: 'cl', 3: 'dl', 4: 'bl', 5: 'ah', 6: 'ch', 7: 'dh', 8: 'bh', 9: 'ax', 10: 'cx', 11: 'dx', 12: 'bx',
                13: 'sp', 14: 'bp', 15: 'si', 16: 'di'}
BASIC_SIZE = {0x10: 1, 0x20: 1, 0x70: 1, 0x11: 2, 0x21: 2, 0x72: 2, 0x73: 2, 0x12: 4, 0x22: 4, 0x74: 4, 0x75: 4}
WIDTH = {'byte': 1, 'word': 2, 'dword': 4}


def segments(data):
    """Segment name -> initialized bytes, for any OMF object (incl. CodeView $$SYMBOLS)."""
    names, order, content = [None], [], {}
    i = 0
    while i + 3 <= len(data):
        kind = data[i]
        length = struct.unpack_from('<H', data, i + 1)[0]
        body = data[i + 3:i + 3 + length - 1]
        i += 3 + length
        if kind == 0x96:
            j = 0
            while j < len(body):
                n = body[j]
                names.append(body[j + 1:j + 1 + n].decode('latin1'))
                j += 1 + n
        elif kind in (0x98, 0x99):
            j = 1 + (3 if (body[0] >> 5) == 0 else 0)
            size = struct.unpack_from('<H' if kind == 0x98 else '<I', body, j)[0]
            j += 2 if kind == 0x98 else 4
            index = body[j] if body[j] < 0x80 else ((body[j] & 0x7F) << 8) | body[j + 1]
            order.append(names[index])
            content[len(order)] = bytearray(size)
        elif kind in (0xA0, 0xA1):
            wide = kind == 0xA1
            seg = body[0]
            offset = struct.unpack_from('<I' if wide else '<H', body, 1)[0]
            chunk = body[5 if wide else 3:]
            content[seg][offset:offset + len(chunk)] = chunk
    return {order[k - 1]: bytes(v) for k, v in content.items()}


def type_size(index):
    if index < 0x1000:
        mode = (index >> 8) & 7
        if mode == 1:
            return 2
        if mode in (2, 3):
            return 4
        return BASIC_SIZE.get(index & 0xFF)
    return None


def codeview_locals(symbols, procedure):
    """Named locals of one procedure from CV4 16-bit records: frame homes and registers."""
    homes, registers, current, i = [], [], None, 4
    while i + 4 <= len(symbols):
        length, kind = struct.unpack_from('<HH', symbols, i)
        record = symbols[i + 4:i + 2 + length]
        i += 2 + length
        if length < 2:
            break
        if kind in (0x0104, 0x0105, 0x0204, 0x0205):
            n = record[25]
            current = record[26:26 + n].decode('latin1')
        elif current and current.lstrip('_') == procedure.lstrip('_'):
            if kind == 0x0100:
                offset, typ = struct.unpack_from('<hH', record, 0)
                n = record[4]
                if offset < 0:
                    homes.append(dict(name=record[5:5 + n].decode('latin1'), offset=offset, size=type_size(typ), type=typ))
            elif kind == 0x0002:
                typ, reg = struct.unpack_from('<HH', record, 0)
                n = record[4]
                registers.append(dict(name=record[5:5 + n].decode('latin1'), register=CV_REGISTERS.get(reg, reg), type=typ))
    return homes, registers


def target_frame(disassembly):
    """ENTER size and the target's [bp-N] slots with observed access widths."""
    enter, slots = None, {}
    for row in disassembly:
        mnemonic, operands = row['mnemonic'], str(row['operands'])
        if mnemonic == 'enter' and enter is None:
            enter = int(operands.split(',')[0], 0)
        for m in re.finditer(r'(?:(byte|word|dword) ptr )?(?:ss:)?\[bp - (0x[0-9a-f]+|\d+)\]', operands):
            offset = -int(m.group(2), 0)
            if mnemonic in ('les', 'lds'):
                width = 4
            elif mnemonic == 'lea':
                width = 'address'
            else:
                width = WIDTH.get(m.group(1))
            slots.setdefault(offset, set()).add(width)
    return enter, {k: sorted(v, key=str) for k, v in sorted(slots.items(), reverse=True)}


def compare(homes, registers, candidate_enter, enter, slots):
    """Plain-language mismatches between candidate homes and target slots."""
    touched = set()
    for offset, widths in slots.items():
        span = max([w for w in widths if isinstance(w, int)] or [1])
        touched.update(range(offset, offset + span))
    findings = []
    starts = sorted(slots)
    same_frame = enter == candidate_enter   # both None: neither side has a frame
    for home in homes:
        span = range(home['offset'], home['offset'] + (home['size'] or 2))
        if not touched.intersection(span):
            # A register-resident local keeps a reserved CodeView home; with an
            # equal frame size an untouched home is normal, not a residue.
            if not same_frame:
                findings.append('candidate local %s (%s bytes) at bp%d is never accessed by the target: an extra memory local (make it a register candidate, merge it, or drop it)'
                                % (home['name'], home['size'] or '?', home['offset']))
        elif home['offset'] not in slots:
            nearest = min(starts, key=lambda o: abs(o - home['offset'])) if starts else None
            findings.append('candidate local %s (%s bytes) starts at bp%d but the target never accesses bp%d; nearest target slot bp%s: a local in between is missing or extra'
                            % (home['name'], home['size'] or '?', home['offset'], home['offset'], nearest))
    covered = set()
    for home in homes:
        covered.update(range(home['offset'], home['offset'] + (home['size'] or 2)))
    if not same_frame:
        # Compiler temporaries also occupy unnamed target slots; they only
        # matter when the frames differ in size.
        for offset, widths in slots.items():
            if offset not in covered:
                findings.append('target slot bp%d (%s) has no named candidate local (a missing local, or a compiler temporary)' % (offset, '/'.join(map(str, widths))))
    if enter is not None and candidate_enter is not None and enter != candidate_enter:
        named = sorted({(h['offset'], h['size'] or 2) for h in homes})
        findings.append('frame size differs: target ENTER %d, candidate ENTER %d (candidate named homes: %s)'
                        % (enter, candidate_enter, ', '.join('bp%d/%d' % x for x in named)))
    return findings


def frame_report(symbol, source, flags, plain_object, disassembly, compiler='msc700'):
    """Compile `source` with /Zi and report the named-local frame map, or why not."""
    from codegen_cache import compile_cached
    import omf
    module = omf.parse(plain_object.read_bytes())
    public = next((p for p in module['publics'] if p['name'].lstrip('_') == symbol.lstrip('_') and p['segment']), None)
    if public is None:
        return dict(status='NOT_APPLICABLE', reason='symbol is not public in the candidate object')
    plain_code = bytes.fromhex(module['segments'][public['segment'] - 1]['data_hex'])
    flags = list(flags)
    zi = flags[:-1] + ['/Zi', flags[-1]] if flags and flags[-1].startswith('/NT') else flags + ['/Zi']
    compiled, _ = compile_cached([dict(source=source, flags=zi)], compiler)
    obj, receipt = compiled[0]
    if obj is None or receipt.get('exit_code'):
        return dict(status='NOT_APPLICABLE', reason='/Zi compile failed')
    segs = segments(obj.read_bytes())
    code = next((data for name, data in segs.items() if data == plain_code), None)
    if code is None:
        return dict(status='NOT_APPLICABLE', reason='/Zi changed the code; CodeView frame map not trusted')
    homes, registers = codeview_locals(segs.get('$$SYMBOLS', b''), symbol)
    enter, slots = target_frame(disassembly)
    at = public['offset']
    candidate_enter = int.from_bytes(code[at + 1:at + 3], 'little') if code[at:at + 1] == b'\xc8' else None
    return dict(status='OK', candidate_locals=homes, candidate_registers=registers, candidate_enter=candidate_enter,
                target_enter=enter, target_slots={str(k): v for k, v in slots.items()},
                findings=compare(homes, registers, candidate_enter, enter, slots))

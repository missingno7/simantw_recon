"""Differentially execute one NE function and one compiled C candidate.

This is a bounded diagnostic emulator, not a Windows compatibility layer. It
executes integer 16-bit x86 in Unicorn with fixture-backed NE segments, maps
OMF references into the same synthetic address space, executes oracle game and
runtime code, and scripts only imported Windows/OS calls.
Unsupported instructions, unresolved fixups, invalid memory accesses, and
instruction-limit hits are reported as unsupported instead of equivalence.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
import random
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

from common import ROOT, FormatError, fixture, write_json
import compiler_profiles
import mapsym
import ne
import omf

try:
    import capstone as cs
    from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_INVALID, X86_REG_DS
    from unicorn import Uc, UC_ARCH_X86, UC_MODE_16, UcError
    from unicorn import (UC_HOOK_CODE, UC_HOOK_MEM_WRITE,
                         UC_HOOK_MEM_READ_UNMAPPED, UC_HOOK_MEM_WRITE_UNMAPPED,
                         UC_HOOK_MEM_FETCH_UNMAPPED)
    from unicorn.x86_const import *
except ImportError as exc:  # pragma: no cover - environment diagnostic
    raise FormatError('emu_diff requires the installed unicorn==2.1.4 and capstone==5.0.7') from exc


STACK_SELECTOR = 0xB000
PRIVATE_SELECTOR_BASE = 0xC000
STUB_SELECTOR = 0x7000
RETURN_IP = 0xFFF0
PAGE = 0x1000
ADDRESS_SPACE = 0x100000
SYNTHETIC_SELECTOR = 0xF000


def _decoder():
    result = cs.Cs(cs.CS_ARCH_X86, cs.CS_MODE_16)
    result.detail = True
    return result


def _word(data, pos):
    return int.from_bytes(data[pos:pos + 2], 'little')


def _put(data, pos, value, size):
    if pos < 0 or pos + size > len(data):
        raise FormatError(f'relocation outside segment at {pos:#x}')
    data[pos:pos + size] = int(value & ((1 << (size * 8)) - 1)).to_bytes(size, 'little')


def _selector(segment_number):
    return 0x1000 + (segment_number - 1) * 0x1000


def _base(selector):
    return selector << 4


def _parse_int(text):
    text = text.strip()
    return int(text, 0)


def _parse_arg(text):
    if '=' not in text:
        raise FormatError('--arg must be NAME=VALUE')
    name, value = text.split('=', 1)
    if ':' in value:
        off, seg = value.split(':', 1)
        return name, (_parse_int(off) & 0xffff, _parse_int(seg) & 0xffff)
    return name, (_parse_int(value) & 0xffff,)


def _parse_stub(text):
    if '=' not in text:
        raise FormatError('--stub must be CALLEE=AX or CALLEE=AX:DX')
    name, result = text.split('=', 1)
    words = tuple(_parse_int(x) & 0xffff for x in result.split(':'))
    if not 1 <= len(words) <= 2:
        raise FormatError('--stub accepts AX or AX:DX')
    return name, words + ((0,) if len(words) == 1 else ())


def _c_parameters(source, symbol):
    """Small signature reader for input shaping; it does not parse C generally."""
    name = re.escape(symbol.lstrip('_'))
    match = re.search(r'\b' + name + r'\s*\(([^()]*)\)\s*\{', source)
    if not match:
        return []
    params = []
    for ordinal, part in enumerate(match.group(1).split(',')):
        part = part.strip()
        if not part or part == 'void':
            continue
        ident = re.search(r'([A-Za-z_]\w*)\s*(?:\[[^]]*\])?\s*$', part)
        pname = ident.group(1) if ident else f'arg{ordinal}'
        pointer = '*' in part or re.search(r'\b(far|huge)\b', part) is not None
        far_pointer = pointer and not re.search(r'\bnear\b', part)
        long_value = re.search(r'\b(long|double)\b', part) is not None
        byte_value = re.search(r'\b(char|BYTE|unsigned\s+char)\b', part) is not None and not pointer
        params.append(dict(name=pname, pointer=pointer, far_pointer=far_pointer,
                           words=2 if far_pointer or long_value else 1,
                           byte=byte_value, declaration=part))
    return params


def _c_return_words(source, symbol):
    """Infer ABI return width from this draft's simple function definition."""
    name = re.escape(symbol.lstrip('_'))
    match = re.search(r'([^;{}]*?)\b' + name + r'\s*\([^{}]*\)\s*\{', source, re.S)
    if not match:
        return 2
    declaration = match.group(1).rsplit(';', 1)[-1].rsplit('}', 1)[-1]
    declaration = re.sub(r'/\*.*?\*/|//[^\r\n]*', ' ', declaration, flags=re.S)
    if re.search(r'\bvoid\b', declaration) and '*' not in declaration:
        return 0
    if re.search(r'\b(long|double)\b', declaration):
        return 2
    if '*' in declaration:
        return 2 if re.search(r'\b(far|huge)\b', declaration) else 1
    if re.search(r'\b(char|short|int|enum)\b', declaration):
        return 1
    # Unknown typedefs may alias a long or pointer. Comparing both registers
    # is conservative until the declaration can be resolved from source.
    return 2


def _signature_word_counts(source, fx):
    """Read simple file-scope extern prototypes for call argument labeling."""
    counts = {}
    prototype = re.compile(r'\bextern\s+([^;{}]*?)\b([A-Za-z_]\w*)\s*\(([^()]*?)\)\s*;', re.S)
    for match in prototype.finditer(source):
        name, params = match.group(2), match.group(3).strip()
        if not params or params == 'void':
            count = 0
        else:
            count = 0
            for part in params.split(','):
                part = part.strip()
                if not part or part == '...':
                    continue
                pointer = '*' in part or '[' in part
                far_pointer = pointer and not re.search(r'\bnear\b', part)
                long_value = re.search(r'\b(long|double)\b', part) is not None
                count += 2 if far_pointer or long_value else 1
        counts[name.lstrip('_')] = count
        imported = fx.import_names.get(name.upper()) or fx.import_names.get(name.lstrip('_').upper())
        if imported:
            counts[imported] = count
    return counts


def _argument_words(params, overrides, rng):
    words = []
    labels = []
    for p in params:
        raw = overrides.get(p['name'])
        if raw is None:
            # Point pointers at a mapped zero-filled tail of DGROUP, byte enums
            # sample common switch tags, and scalar words stay compact.
            if p['pointer']:
                raw = (0xF000, 0xA000) if p.get('far_pointer') else (0xF000,)
            elif p['byte']:
                raw = (rng.choice((0x00, 0x20, 0x60, 0x80, 0xA0, 0xC0, 0x10, 0x30)),)
            else:
                raw = (rng.randrange(0, 17),)
        raw = tuple(raw)
        while len(raw) < p['words']:
            raw += (0,)
        words.extend(raw[:p['words']])
        labels.append(dict(name=p['name'], words=list(raw[:p['words']]), declaration=p['declaration']))
    return words, labels


@dataclass
class Fixture:
    raw: bytes
    image: dict
    symbols: dict
    cards: list
    card_by_symbol: dict
    symbol_locations: dict
    names_by_location: dict
    data_symbols: dict
    segment_bytes: dict
    import_stubs: dict
    import_names: dict

    @classmethod
    def load(cls):
        raw = fixture('SIMANTW.EXE')
        image = ne.parse(raw)
        symbols = mapsym.parse(fixture('SIMANTW.SYM'))
        cards = [json.loads(x) for x in (ROOT / 'evidence/disassembly/cards.jsonl').read_text(encoding='utf-8').splitlines()]
        locs, names, data = {}, {}, {}
        for seg in symbols['segments']:
            for item in seg['symbols']:
                key = (seg['number'], item['offset'])
                names.setdefault(key, []).append(item['name'])
                locs[item['name']] = key
                if seg['number'] >= 8:
                    data.setdefault(seg['number'], []).append(item)
        seg_bytes = {}
        for seg in image['segments']:
            if seg['file_offset'] is None:
                seg_bytes[seg['number']] = bytearray(seg['logical_size'])
            else:
                start = seg['file_offset']
                seg_bytes[seg['number']] = bytearray(raw[start:start + seg['logical_size']])
        stub_map = {}
        import_names = {}
        try:
            from library_match import import_symbols
            sdk_imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
        except (OSError, FormatError):
            sdk_imports = {}
        for s in image['segments']:
            for relocation in s['relocations']:
                target = relocation['target']
                if target['kind'] == 'import':
                    identity = _import_name(target)
                    stub_map.setdefault(identity, 0xF000 + len(stub_map) * 4)
        for name, target in sdk_imports.items():
            identity = f"{target['module']}!#{target['ordinal']}"
            import_names[name.upper()] = identity
            if identity in stub_map:
                import_names[name.lstrip('_').upper()] = identity
        return cls(raw, image, symbols, cards, {c['symbol']: c for c in cards}, locs,
                   names, data, seg_bytes, stub_map, import_names)

    def nearest_symbol(self, segment, offset):
        rows = self.data_symbols.get(segment, [])
        if not rows:
            rows = self.symbols['segments'][segment - 1]['symbols']
        eligible = [item for item in rows if item['offset'] <= offset]
        if not eligible:
            return None
        item = max(eligible, key=lambda x: x['offset'])
        return {'symbol': item['name'], 'offset': offset - item['offset']}


def _import_name(target):
    return f"{target['module']}!{target.get('name', '#' + str(target.get('ordinal', '?')))}"


def _target_code_and_extent(fx, symbol):
    card = fx.card_by_symbol.get(symbol)
    if card is None:
        raise FormatError('unknown function symbol: ' + symbol)
    extent = card.get('extent') or {}
    if extent.get('end') is None or not extent.get('size'):
        raise FormatError(f'target extent is not closed for {symbol}')
    segno, start = card['segment'], card['offset']
    ns = fx.image['segments'][segno - 1]
    original = bytes(fx.segment_bytes[segno][start:extent['end']])
    return card, segno, start, extent, original


def _patch_ne_segments(fx):
    segments = {n: bytearray(data) for n, data in fx.segment_bytes.items()}
    imports_at = {}
    for seg in fx.image['segments']:
        buf = segments[seg['number']]
        for relocation in seg['relocations']:
            target = relocation['target']
            source_type = relocation['source_type']
            for site in relocation['sites']:
                if target['kind'] == 'internal':
                    target_segment = target['segment']
                    if not 1 <= target_segment <= len(fx.image['segments']):
                        raise FormatError('NE relocation points to an invalid segment')
                    selector = _selector(target_segment)
                    addend = int.from_bytes(buf[site:site + 2], 'little') if relocation['additive'] and source_type not in (2, 5) else 0
                    offset = (target.get('offset', 0) + addend) & 0xffff
                elif target['kind'] == 'import':
                    identity = _import_name(target)
                    selector, offset = STUB_SELECTOR, fx.import_stubs[identity]
                    imports_at[(seg['number'], site)] = identity
                elif target['kind'] == 'entry':
                    entry = next((e for e in fx.image['entries'] if e['ordinal'] == target['ordinal']), None)
                    if not entry:
                        raise FormatError('NE entry relocation has no entry')
                    selector, offset = _selector(entry['segment']), entry['offset']
                elif target['kind'] == 'os_fixup':
                    # The OS patches these sites at load time. Keep their raw
                    # bytes and retain an explicit marker; reaching one in the
                    # requested function is refused below.
                    imports_at[(seg['number'], site)] = f"OSFIXUP:{target['type']}"
                    continue
                else:
                    raise FormatError(f"unsupported NE relocation target {target['kind']}")
                if source_type == 0:
                    _put(buf, site, offset, 1)
                elif source_type == 2:
                    _put(buf, site, selector, 2)
                elif source_type == 3:
                    _put(buf, site, offset, 2)
                    _put(buf, site + 2, selector, 2)
                elif source_type == 5:
                    value = offset
                    if relocation['additive']:
                        value = (value + _word(buf, site)) & 0xffff
                    _put(buf, site, value, 2)
                else:
                    raise FormatError(f'NE relocation source type {source_type} is unsupported')
    return segments, imports_at


def _group_selector(module, group_index):
    group = module['groups'][group_index - 1]
    if not group['segments']:
        raise FormatError('OMF group has no segments')
    name = group['name'].upper()
    if name == 'DGROUP':
        return _selector(10)
    if name == 'SIMANT_DATA_GROUP':
        return _selector(8)
    if name == 'PACK':
        return _selector(9)
    return _selector_for_omf_segment(module, group['segments'][0])


def _selector_for_omf_segment(module, seg_index):
    # The caller attaches this map before resolving any OMF references.
    return module['_selector_map'][seg_index]


def _resolve_omf_target(fx, module, fixup, selector_map):
    method, index = fixup['target_method'], fixup['target_index']
    if method == 0:
        target_seg = index
        offset = module.get('_group_offsets', {}).get(target_seg, 0) + module.get('_group_bases', {}).get(target_seg, 0)
        if target_seg == module.get('_rebase_segment'):
            offset += module.get('_rebase_delta', 0)
        return selector_map[target_seg], offset & 0xffff, None
    if method == 1:
        group = module['groups'][index - 1]
        base = module.get('_group_base_by_index', {}).get(index, 0)
        return _group_selector(module, index), base, group['name']
    if method == 2:
        ext = module['externals'][index - 1]
        name = ext['name']
        if ext.get('local'):
            local = [p for p in module['publics'] if p['name'] == name and p.get('local') and p['segment']]
            if len(local) == 1:
                pub = local[0]
                segno = pub['segment']
                offset = module.get('_group_offsets', {}).get(segno, 0) + module.get('_group_bases', {}).get(segno, 0) + pub['offset']
                return selector_map[segno], offset, name
        if name in fx.symbol_locations:
            seg, off = fx.symbol_locations[name]
            return _selector(seg), off, name
        # Imports have no MAPSYM location. Give them shared synthetic stub slots.
        matches = [key for key in fx.import_stubs if key.endswith('!' + name) or key.split('!', 1)[-1].upper() == name.upper()]
        canonical = fx.import_names.get(name.lstrip('_').upper())
        if canonical and canonical in fx.import_stubs:
            matches.append(canonical)
        if len(matches) == 1:
            return STUB_SELECTOR, fx.import_stubs[matches[0]], matches[0]
        if len(set(matches)) > 1:
            raise FormatError(f'ambiguous OMF import mapping for {name}')
        # A newly introduced external still gets a deterministic candidate-side
        # stub. It will diverge from the target call sequence if it is reached.
        identity = 'CANDIDATE!' + name
        fx.import_stubs.setdefault(identity, 0xF000 + len(fx.import_stubs) * 4)
        return STUB_SELECTOR, fx.import_stubs[identity], identity
    if method == 3:
        return (index & 0xffff), 0, None
    raise FormatError(f'unsupported OMF target method {method}')


def _patch_omf(module, fx, source_code_seg, target_segno, target_start, target_pub_offset, oracle_imports):
    """Resolve candidate fixups, returning bytes and source-site bindings."""
    buffers = {s['index']: bytearray.fromhex(s['data_hex']) for s in module['segments']}
    selectors = {}
    group_offsets, group_bases, group_base_by_index = {}, {}, {}
    next_selector = PRIVATE_SELECTOR_BASE
    group_members = {}
    for group in module['groups']:
        name = group['name'].upper()
        if name == 'DGROUP':
            group_selector, group_base = _selector(10), 0xE000
        elif name == 'SIMANT_DATA_GROUP':
            group_selector, group_base = _selector(8), 0
        elif name == 'PACK':
            group_selector, group_base = _selector(9), 0
        else:
            group_selector, group_base = None, 0
        cursor = 0
        for seg_index in group['segments']:
            seg = module['segments'][seg_index - 1]
            alignment = {1: 1, 2: 2, 3: 16, 4: 256, 5: 4, 6: 4, 7: 4}.get(seg['alignment'])
            if alignment is None:
                raise FormatError(f"unsupported OMF alignment {seg['alignment']} in {seg['name']}")
            cursor = (cursor + alignment - 1) // alignment * alignment
            group_offsets[seg_index] = cursor
            group_bases[seg_index] = group_base
            group_members[seg_index] = group_selector
            cursor += seg['length']
        group_base_by_index[group['index']] = group_base
        if name == 'DGROUP' and group_base + cursor > 0x10000:
            raise FormatError('candidate DGROUP contribution exceeds its synthetic range')
        if group_selector is None:
            for seg_index in group['segments']:
                group_members[seg_index] = next_selector
                next_selector += 0x1000
    for seg in module['segments']:
        if seg['class'] == 'CODE':
            selectors[seg['index']] = _selector(target_segno)
        elif seg['index'] in group_members and group_members[seg['index']] is not None:
            selectors[seg['index']] = group_members[seg['index']]
        elif seg['name'].upper() == 'SIMANT_DATA_GROUP':
            selectors[seg['index']] = _selector(8)
        elif seg['name'].upper() == 'PACK':
            selectors[seg['index']] = _selector(9)
        else:
            selectors[seg['index']] = next_selector
            next_selector += 0x1000
    module['_group_offsets'] = group_offsets
    module['_group_bases'] = group_bases
    module['_group_base_by_index'] = group_base_by_index
    module['_rebase_segment'] = source_code_seg
    module['_rebase_delta'] = target_start - target_pub_offset
    module['_selector_map'] = selectors
    by_site = {}
    for f in module['fixups']:
        buf = buffers[f['segment']]
        selector, target_offset, target_name = _resolve_omf_target(fx, module, f, selectors)
        raw_addend = int.from_bytes(buf[f['offset']:f['offset'] + min(2, f['width'])], 'little')
        target_offset = (target_offset + f['displacement']) & 0xffff
        source_offset = f['offset']
        if f['segment'] == source_code_seg:
            source_offset = target_start + (f['offset'] - target_pub_offset)
        loc = f['location_type']
        if loc in (0, 4):
            _put(buf, f['offset'], target_offset + raw_addend, 1)
        elif loc in (1, 5):
            value = target_offset
            if f['self_relative']:
                value = (target_offset - (source_offset + f['width'])) & 0xffff
            else:
                value = (value + raw_addend) & 0xffff
            _put(buf, f['offset'], value, 2)
        elif loc == 2:
            frame_method, frame_index = f['frame_method'], f['frame_index']
            if frame_method == 0:
                frame_selector = selectors[frame_index]
            elif frame_method == 1:
                frame_selector = _group_selector(module, frame_index)
            elif frame_method == 2:
                frame_selector, _, _ = _resolve_omf_target(fx, module, dict(f, target_method=2, target_index=frame_index), selectors)
            elif frame_method in (4, 5):
                frame_selector = selector
            else:
                raise FormatError(f'unsupported OMF frame method {frame_method}')
            _put(buf, f['offset'], frame_selector, 2)
        elif loc == 3:
            _put(buf, f['offset'], target_offset + raw_addend, 2)
            _put(buf, f['offset'] + 2, selector, 2)
        elif loc in (9, 13):
            value = target_offset
            if f['self_relative']:
                value = (target_offset - (source_offset + f['width'])) & 0xffffffff
            _put(buf, f['offset'], value, 4)
        else:
            raise FormatError(f'OMF fixup location {loc} is unsupported')
        by_site[(f['segment'], f['offset'])] = dict(name=target_name, selector=selector, offset=target_offset,
                                                     width=f['width'], source_offset=source_offset)
    return buffers, selectors, by_site


def _map_candidate_private(module, buffers, selectors):
    rows = []
    grouped = {seg for g in module['groups'] if g['name'].upper() == 'DGROUP' for seg in g['segments']}
    for seg_index in grouped:
        seg = module['segments'][seg_index - 1]
        if seg['length']:
            rows.append(dict(selector=_selector(10), name=seg['name'], data=bytes(buffers[seg_index]),
                             offset=module['_group_bases'].get(seg_index, 0) + module['_group_offsets'].get(seg_index, 0),
                             segment=10, overlay=True))
    for seg in module['segments']:
        if seg['class'] == 'CODE' or seg['index'] in grouped:
            continue
        if selectors[seg['index']] in (_selector(8), _selector(9)):
            if seg['length']:
                raise FormatError(f"candidate far-data contribution {seg['name']} has no proven placement")
        else:
            if seg['length']:
                rows.append(dict(selector=selectors[seg['index']], name=seg['name'], data=bytes(buffers[seg['index']])))
    if any(row['selector'] > 0xF000 for row in rows):
        raise FormatError('candidate has too many private segments for the synthetic real-mode address map')
    return rows


def _function_map(fx):
    by_addr = {}
    for seg in fx.symbols['segments']:
        if seg['number'] > 7:
            continue
        for item in seg['symbols']:
            by_addr[(seg['number'], item['offset'])] = item['name']
    return by_addr


def _target_relocations(fx, segment):
    by_site = {}
    for rel in fx.image['segments'][segment - 1]['relocations']:
        for site in rel['sites']:
            by_site[site] = rel
    return by_site


def _code_returns_far(code, origin):
    rows = list(_decoder().disasm(code, origin))
    returns = [i.mnemonic for i in rows if i.group(cs.CS_GRP_RET)]
    if not returns:
        raise FormatError('function extent contains no decoded return')
    return all(x.startswith('retf') for x in returns)


def _arg_push_count(code_segment, offset, origin, lower_bound):
    # Best-effort argument count from contiguous pushes immediately before a
    # call. The raw words remain useful even when MSC interleaves setup code.
    begin = max(lower_bound, offset - 24)
    rows = list(_decoder().disasm(code_segment[begin:offset], begin + origin))
    count = 0
    for ins in reversed(rows):
        if ins.mnemonic != 'push':
            break
        count += 1
    return min(count, 12)


@dataclass
class Side:
    name: str
    segno: int
    function_offset: int
    extent_size: int
    code: bytes
    segments: dict
    reloc_sites: dict
    imports_at: dict = field(default_factory=dict)
    omf_fixups: dict = field(default_factory=dict)
    symbol_overrides: dict = field(default_factory=dict)
    selector_overrides: dict = field(default_factory=dict)
    private_segments: list = field(default_factory=list)


def _target_side(fx, symbol, target_extent_data):
    card, segno, start, extent, code = _target_code_and_extent(fx, symbol)
    for relocation in fx.image['segments'][segno - 1]['relocations']:
        if relocation['target']['kind'] == 'os_fixup' and any(start <= site < extent['end'] for site in relocation['sites']):
            raise FormatError(f"target function uses OS fixup type {relocation['target']['type']} at {relocation['sites']}")
    segments, imports_at = _patch_ne_segments(fx)
    code = bytes(segments[segno][start:extent['end']])
    return Side('target', segno, start, len(code), code, segments,
                _target_relocations(fx, segno), imports_at=imports_at,
                symbol_overrides=_function_map(fx)), card


def _candidate_side(fx, symbol, source, candidate_obj, target_side, card):
    module = omf.parse(candidate_obj.read_bytes())
    pubs = [p for p in module['publics'] if p['name'] == symbol]
    if len(pubs) != 1:
        raise FormatError('compiled candidate has no unique requested public')
    pub = pubs[0]
    oseg = module['segments'][pub['segment'] - 1]
    if oseg['class'] != 'CODE':
        raise FormatError('candidate public is not in a CODE segment')
    candidate_extent_end = min([p['offset'] for p in module['publics'] if p['segment'] == pub['segment'] and p['offset'] > pub['offset']] + [oseg['length']])
    raw_code = bytes.fromhex(oseg['data_hex'])[pub['offset']:candidate_extent_end]
    # All candidate function instructions run at the original public's CS:IP;
    # constant relocation of the body preserves internal relative branches.
    patched, selectors, fixups = _patch_omf(module, fx, pub['segment'], target_side.segno,
                                            target_side.function_offset, pub['offset'],
                                            target_side.imports_at)
    patched_code = patched[pub['segment']]
    # Use the rebased full object code only for calculating the initial function
    # bytes; relocate function bytes' fixup sites into their oracle positions.
    code_template = bytearray(patched_code[pub['offset']:candidate_extent_end])
    decoded_function = list(_decoder().disasm(code_template, target_side.function_offset))
    for (sidx, site), row in fixups.items():
        if sidx != pub['segment'] or not (pub['offset'] <= site < candidate_extent_end):
            continue
        if not (row.get('name') or '').startswith('CANDIDATE!'):
            continue
        translated = target_side.function_offset + site - pub['offset']
        if not any(ins.group(cs.CS_GRP_CALL) and ins.address <= translated < ins.address + ins.size for ins in decoded_function):
            raise FormatError(f"unresolved OMF external data reference {row['name']} at {translated:04X}")
    for (sidx, site), row in fixups.items():
        if sidx != pub['segment'] or not (pub['offset'] <= site < candidate_extent_end):
            continue
        local = site - pub['offset']
        # The object was patched for its old segment offset; recalculate common
        # segment-relative fixups at the oracle entry offset.
        f = next(f for f in module['fixups'] if f['segment'] == sidx and f['offset'] == site)
        if f['location_type'] in (1, 5) and f['self_relative']:
            value = (row['offset'] - (target_side.function_offset + local + f['width'])) & 0xffff
            _put(code_template, local, value, 2)
    function_end = target_side.function_offset + len(code_template)
    if function_end > 0xfff0:
        raise FormatError('candidate function does not fit the target code segment')
    segments, imports_at = _patch_ne_segments(fx)
    candidate_reloc_sites = {site: row for site, row in target_side.reloc_sites.items()
                              if not target_side.function_offset <= site < target_side.function_offset + target_side.extent_size}
    for (sidx, site), row in fixups.items():
        if sidx != pub['segment'] or not (pub['offset'] <= site < candidate_extent_end):
            continue
        candidate_reloc_sites[target_side.function_offset + site - pub['offset']] = {
            'candidate_target': row['name'], 'source_type': module['fixups'][0]['location_type'] if module['fixups'] else None,
            'candidate_site': site, 'import': row['name'] if row['name'] and '!' in row['name'] else None,
        }
    private = _map_candidate_private(module, patched, selectors)
    selector_overrides = {selector: dict(name=name, data=data) for selector, name, data in []}
    return Side('candidate', target_side.segno, target_side.function_offset, len(code_template),
                bytes(code_template), segments, candidate_reloc_sites, imports_at=imports_at,
                omf_fixups=fixups, selector_overrides=selector_overrides, private_segments=private), module


def _direct_global_inputs(fx, symbol, target_side, rng):
    """Return small scalar DGROUP sites read via direct DS operands."""
    card, segno, start, extent, code = _target_code_and_extent(fx, symbol)
    segment_symbols = fx.symbols['segments'][9]['symbols']
    starts = {x['offset']: x['name'] for x in segment_symbols}
    found = {}
    for ins in _decoder().disasm(code, start):
        if ins.mnemonic in ('les', 'lds'):
            continue
        for operand in ins.operands:
            if operand.type != X86_OP_MEM or operand.mem.base or operand.mem.index:
                continue
            if operand.mem.segment not in (X86_REG_INVALID, cs.x86_const.X86_REG_DS):
                continue
            off = operand.mem.disp & 0xffff
            # Skip loader selector pools; they carry segment selectors rather
            # than scalar game state.
            if any(r['source_type'] == 2 and off in r['sites'] for r in fx.image['segments'][9]['relocations']):
                continue
            earlier = [x for x in segment_symbols if x['offset'] <= off]
            if not earlier:
                continue
            owner = max(earlier, key=lambda x: x['offset'])
            width = max(1, min(2, operand.size or 2))
            found[(10, off, width)] = dict(segment=10, offset=off, width=width,
                                           symbol=owner['name'], value=rng.randrange(0, 17))
    return list(found.values())


def _address_labels(fx, module=None, private_segments=()):
    labels = []
    for p in private_segments:
        if p.get('overlay'):
            labels.append(dict(selector=p['selector'], base=_base(p['selector']) + p['offset'],
                               length=len(p['data']), segment=p['name'], kind='private_overlay'))
    for seg in fx.image['segments']:
        selector = _selector(seg['number'])
        labels.append(dict(selector=selector, base=_base(selector), length=0x10000,
                           segment=seg['number'], kind='ne'))
    labels.append(dict(selector=STACK_SELECTOR, base=_base(STACK_SELECTOR), length=0x10000,
                       segment='STACK', kind='stack'))
    for p in private_segments:
        if p.get('overlay'):
            continue
        labels.append(dict(selector=p['selector'], base=_base(p['selector']), length=max(PAGE, ((len(p['data']) + PAGE - 1) // PAGE) * PAGE),
                           segment=p['name'], kind='private'))
    return labels


def _event_location(fx, labels, address):
    for row in labels:
        if row['base'] <= address < row['base'] + row['length']:
            offset = address - row['base']
            if row['kind'] == 'ne' and row['segment'] >= 8:
                nearest = fx.nearest_symbol(row['segment'], offset)
                return dict(segment=row['segment'], offset=offset, symbol=nearest['symbol'] if nearest else None,
                            symbol_offset=nearest['offset'] if nearest else None)
            return dict(segment=row['segment'], offset=offset)
    return dict(segment='UNMAPPED', offset=address)


def _block_for_ip(ip, function_offset, heads, extent_size):
    offset = ip - function_offset
    if not 0 <= offset < extent_size:
        return None
    eligible = [head for head in heads if head <= ip]
    return max(eligible) - function_offset if eligible else 0


def _linear_ranges(uc):
    return [(start, end + 1) for start, end, _ in uc.mem_regions()]


def _map_synthetic_memory(uc, address, size, seed, memory_mode, synthesized_pages):
    """Map absent pages with seed-stable contents shared by the two runs."""
    if size <= 0:
        size = 1
    first = address & ~(PAGE - 1)
    last = (address + size - 1) & ~(PAGE - 1)
    ranges = _linear_ranges(uc)
    page = first
    while page <= last:
        if not any(start <= page and page + PAGE <= end for start, end in ranges):
            if page < 0 or page + PAGE > 0x110000:
                raise FormatError(f'synthetic memory address outside real-mode range: {page:#x}')
            uc.mem_map(page, PAGE)
            if memory_mode == 'zeros':
                content = bytes(PAGE)
            else:
                rng = random.Random((seed << 24) ^ page ^ 0x5A17D1FF)
                content = bytes(rng.getrandbits(8) for _ in range(PAGE))
            uc.mem_write(page, content)
            synthesized_pages.add(page)
            ranges.append((page, page + PAGE))
        page += PAGE


def _memory_operand_address(uc, ins, mem):
    base = uc.reg_read(_capstone_reg_to_unicorn(mem.base)) if mem.base else 0
    index = uc.reg_read(_capstone_reg_to_unicorn(mem.index)) if mem.index else 0
    offset = (base + index * mem.scale + mem.disp) & 0xffff
    if mem.segment not in (0, X86_REG_INVALID):
        selector = uc.reg_read(_capstone_reg_to_unicorn(mem.segment))
    else:
        default = UC_X86_REG_SS if mem.base == cs.x86_const.X86_REG_BP or mem.index == cs.x86_const.X86_REG_BP else UC_X86_REG_DS
        selector = uc.reg_read(default)
    return selector, offset, _base(selector) + offset


def _selector_known(fx, side, selector):
    known = {_selector(n) for n in range(1, 11)} | {STACK_SELECTOR, STUB_SELECTOR, SYNTHETIC_SELECTOR}
    known.update(p['selector'] for p in side.private_segments)
    return selector in known


def _pointer_labels(fx, labels, selector, offset):
    location = _event_location(fx, labels, _base(selector) + (offset & 0xffff))
    if location.get('segment') == 'UNMAPPED':
        return None
    return dict(segment=location.get('segment'), symbol=location.get('symbol'),
                symbol_offset=location.get('symbol_offset'), offset=location.get('offset'))


def _block_heads(code, origin):
    rows = list(_decoder().disasm(code, origin))
    heads = {origin}
    known = {i.address: i for i in rows}
    for ins in rows:
        if ins.group(cs.CS_GRP_JUMP):
            if ins.operands and ins.operands[0].type == X86_OP_IMM:
                destination = ins.operands[0].imm & 0xffff
                if destination in known:
                    heads.add(destination)
            if ins.mnemonic != 'jmp' and ins.address + ins.size in known:
                heads.add(ins.address + ins.size)
        elif ins.group(cs.CS_GRP_CALL) and ins.address + ins.size in known:
            heads.add(ins.address + ins.size)
    return heads


def _resolve_call(side, fx, ins, module=None, current_segno=None, within_root=True):
    site_candidates = range(ins.address, ins.address + ins.size)
    if within_root:
        reloc_sites = side.reloc_sites
    elif current_segno and 1 <= current_segno <= len(fx.image['segments']):
        reloc_sites = _target_relocations(fx, current_segno)
    else:
        reloc_sites = {}
    for site in site_candidates:
        row = reloc_sites.get(site)
        if not row:
            continue
        if 'candidate_target' in row:
            return row.get('candidate_target') or f"FIXUP_{site:04X}"
        target = row['target']
        if target['kind'] == 'os_fixup':
            return None
        if target['kind'] == 'import':
            return _import_name(target)
        if target['kind'] == 'internal':
            offset = target.get('offset', 0)
            if ins.mnemonic == 'lcall' and ins.bytes and ins.bytes[0] == 0x9a and len(ins.bytes) >= 5:
                offset = int.from_bytes(ins.bytes[1:3], 'little')
            return fx.names_by_location.get((target['segment'], offset), [None])[0] or f"SEG{target['segment']}:{offset:04X}"
    if ins.mnemonic == 'call' and ins.operands and ins.operands[0].type == X86_OP_IMM:
        off = ins.operands[0].imm & 0xffff
        call_segno = current_segno or side.segno
        return side.symbol_overrides.get((call_segno, off)) or fx.names_by_location.get((call_segno, off), [None])[0] or f"{call_segno}:{off:04X}"
    if ins.mnemonic == 'lcall' and len(ins.operands) >= 2 and all(op.type == X86_OP_IMM for op in ins.operands[:2]):
        selector = ins.operands[0].imm & 0xffff
        offset = ins.operands[1].imm & 0xffff
        segment = next((n for n in range(1, 11) if _selector(n) == selector), None)
        if segment:
            return fx.names_by_location.get((segment, offset), [None])[0]
    if ins.mnemonic in ('lcall', 'call'):
        return None
    return None


def _return_cleanup(fx, callee):
    location = fx.symbol_locations.get(callee)
    if not location:
        return 0
    segno, start = location
    card = fx.card_by_symbol.get(callee)
    if not card or not card.get('extent', {}).get('end'):
        return 0
    ns = fx.image['segments'][segno - 1]
    data = fx.segment_bytes[segno][start:card['extent']['end']]
    rows = list(_decoder().disasm(bytes(data), start))
    for ins in reversed(rows):
        if ins.group(cs.CS_GRP_RET) and ins.operands and ins.operands[0].type == X86_OP_IMM:
            return ins.operands[0].imm & 0xffff
    return 0


def _callee_returns_far(fx, callee):
    location = fx.symbol_locations.get(callee)
    card = fx.card_by_symbol.get(callee)
    if not location or not card or not card.get('extent', {}).get('end'):
        return False
    segno, start = location
    end = card['extent']['end']
    return _code_returns_far(bytes(fx.segment_bytes[segno][start:end]), start)


def _decode_indirect_target(uc, ins, side, fx):
    op = ins.operands[0]
    if op.type == X86_OP_IMM:
        if ins.mnemonic == 'lcall' and len(ins.operands) >= 2:
            selector = op.imm & 0xffff
            target_off = ins.operands[1].imm & 0xffff
            segment = next((n for n in range(1, 11) if _selector(n) == selector), None)
            if segment:
                return fx.names_by_location.get((segment, target_off), [None])[0], target_off
            return None, target_off
        return None, op.imm & 0xffff
    if op.type == X86_OP_MEM:
        mem = op.mem
        base = uc.reg_read(_capstone_reg_to_unicorn(mem.base)) if mem.base else 0
        index = uc.reg_read(_capstone_reg_to_unicorn(mem.index)) if mem.index else 0
        offset = (base + index * mem.scale + mem.disp) & 0xffff
        segment = mem.segment or X86_REG_DS
        segreg = _capstone_reg_to_unicorn(segment)
        sel = uc.reg_read(segreg) if segment not in (0, X86_REG_INVALID) else uc.reg_read(UC_X86_REG_DS)
        addr = _base(sel) + offset
        data = bytes(uc.mem_read(addr, 4 if ins.mnemonic == 'lcall' else 2))
        target_off = int.from_bytes(data[:2], 'little')
        target_seg = int.from_bytes(data[2:4], 'little') if ins.mnemonic == 'lcall' else sel
        for identity, off in fx.import_stubs.items():
            if target_seg == STUB_SELECTOR and off == target_off:
                return identity, target_off
        for key, name in fx.names_by_location.items():
            segno, symoff = key
            if _selector(segno) == target_seg and symoff == target_off:
                return name[0] if name else None, target_off
        for segno in range(1, 8):
            if target_seg == _selector(segno) and target_off < len(fx.segment_bytes[segno]):
                named = fx.names_by_location.get((segno, target_off), [None])[0]
                return named or f'SEG{segno}:{target_off:04X}', target_off
    if op.type == 1:
        reg = _capstone_reg_to_unicorn(op.reg)
        target_off = uc.reg_read(reg) & 0xffff
        named = side.symbol_overrides.get((side.segno, target_off)) or fx.names_by_location.get((side.segno, target_off), [None])[0]
        return named or f'SEG{side.segno}:{target_off:04X}', target_off
    return None, 0


def _capstone_reg_to_unicorn(reg):
    mapping = {
        cs.x86_const.X86_REG_AX: UC_X86_REG_AX, cs.x86_const.X86_REG_BX: UC_X86_REG_BX,
        cs.x86_const.X86_REG_CX: UC_X86_REG_CX, cs.x86_const.X86_REG_DX: UC_X86_REG_DX,
        cs.x86_const.X86_REG_SI: UC_X86_REG_SI, cs.x86_const.X86_REG_DI: UC_X86_REG_DI,
        cs.x86_const.X86_REG_BP: UC_X86_REG_BP, cs.x86_const.X86_REG_SP: UC_X86_REG_SP,
        cs.x86_const.X86_REG_CS: UC_X86_REG_CS, cs.x86_const.X86_REG_DS: UC_X86_REG_DS,
        cs.x86_const.X86_REG_ES: UC_X86_REG_ES, cs.x86_const.X86_REG_SS: UC_X86_REG_SS,
    }
    return mapping.get(reg, UC_X86_REG_AX)


def _observe_memory_reads(uc, ins, fx, global_reads):
    """Resolve scalar DS/ES reads from current registers without a memory hook."""
    bp = cs.x86_const.X86_REG_BP
    for operand in ins.operands:
        if operand.type != X86_OP_MEM or not operand.access or not (operand.access & cs.CS_AC_READ):
            continue
        mem = operand.mem
        base = uc.reg_read(_capstone_reg_to_unicorn(mem.base)) if mem.base else 0
        index = uc.reg_read(_capstone_reg_to_unicorn(mem.index)) if mem.index else 0
        offset = (base + index * mem.scale + mem.disp) & 0xffff
        if mem.segment not in (0, X86_REG_INVALID):
            selector = uc.reg_read(_capstone_reg_to_unicorn(mem.segment))
        else:
            selector = uc.reg_read(UC_X86_REG_SS if mem.base == bp or mem.index == bp else UC_X86_REG_DS)
        segment = next((n for n in range(1, 11) if _selector(n) == selector), None)
        if segment is None or segment < 8 or operand.size not in (1, 2):
            continue
        if offset + operand.size > len(fx.segment_bytes[segment]):
            continue
        if any(rel['source_type'] == 2 and offset in rel['sites']
               for rel in fx.image['segments'][segment - 1]['relocations']):
            continue
        owner = fx.nearest_symbol(segment, offset)
        name = owner['symbol'] if owner else None
        if name and any(word in name.lower() for word in ('ptr', 'pointer')):
            continue
        key = (segment, offset, operand.size)
        global_reads[key] = dict(segment=segment, offset=offset, width=operand.size, symbol=name)


def _run_side(fx, side, params, overrides, stub_script, seed, instruction_limit,
              global_overrides, strict=False, memory_mode='seeded', seed_null_far_pointers=True,
              call_signatures=None, trace_execution=False):
    memory = {n: bytearray(buf) for n, buf in side.segments.items()}
    # Candidate private data is independent, while references to public oracle
    # globals already resolve to the shared NE segment selectors.
    for p in side.private_segments:
        if p.get('overlay'):
            target = memory[p['segment']]
            start = p['offset']
            if start + len(p['data']) > 0x10000:
                raise FormatError('candidate private DGROUP overlay exceeds synthetic DGROUP')
            if len(target) < 0x10000:
                target.extend(bytes(0x10000 - len(target)))
            target[start:start + len(p['data'])] = p['data']
        else:
            memory[-p['selector']] = bytearray(p['data'])
    for item in global_overrides:
        if item['segment'] in memory:
            buf = memory[item['segment']]
            _put(buf, item['offset'], item['value'], item['width'])
    u = Uc(UC_ARCH_X86, UC_MODE_16)
    labels = _address_labels(fx, private_segments=side.private_segments)
    for row in labels:
        length = max(PAGE, ((row['length'] + PAGE - 1) // PAGE) * PAGE)
        base = row['base']
        if row['kind'] == 'private_overlay':
            continue
        if base + length > 0x110000:
            raise FormatError('synthetic segment layout exceeds real-mode address space')
        u.mem_map(base, length)
        if row['kind'] == 'ne':
            u.mem_write(base, bytes(memory[row['segment']]))
        elif row['kind'] == 'stack':
            u.mem_write(base, bytes(length))
        elif row['kind'] == 'private':
            data = next(p['data'] for p in side.private_segments if p['selector'] == row['selector'])
            u.mem_write(base, data)
    code_base = _base(_selector(side.segno))
    # In target runs this equals the fixture bytes. Candidate code overlays the
    # exact extent in that same segment so DS/CS-relative semantics stay equal.
    if side.name == 'candidate':
        u.mem_write(code_base + side.function_offset, side.code)
    u.mem_write(code_base + RETURN_IP, b'\x90')
    u.reg_write(UC_X86_REG_CS, _selector(side.segno))
    u.reg_write(UC_X86_REG_DS, _selector(10))
    u.reg_write(UC_X86_REG_ES, _selector(10))
    u.reg_write(UC_X86_REG_SS, STACK_SELECTOR)
    u.reg_write(UC_X86_REG_SP, 0xE000)
    for reg in (UC_X86_REG_AX, UC_X86_REG_BX, UC_X86_REG_CX, UC_X86_REG_DX,
                UC_X86_REG_SI, UC_X86_REG_DI, UC_X86_REG_BP):
        u.reg_write(reg, random.Random(seed ^ reg).randrange(0x10000))
    is_far = _code_returns_far(side.code, side.function_offset)
    args, labeled_args = _argument_words(params, overrides, random.Random(seed + 17))
    stack_offset = 0xE000 - (4 if is_far else 2) - 2 * len(args)
    ret_bytes = bytearray()
    ret_bytes += RETURN_IP.to_bytes(2, 'little')
    if is_far:
        ret_bytes += _selector(side.segno).to_bytes(2, 'little')
    ret_bytes += b''.join((x & 0xffff).to_bytes(2, 'little') for x in args)
    u.mem_write(_base(STACK_SELECTOR) + stack_offset, bytes(ret_bytes))
    u.reg_write(UC_X86_REG_SP, stack_offset)
    observables, coverage, global_reads = [], set(), {}
    observable_memory = {}
    synthesized_pages, synthesized_selectors, seeded_far_pointers = set(), {}, []
    heads = _block_heads(side.code, side.function_offset)
    ins_by_ip = {i.address: i for i in _decoder().disasm(side.code, side.function_offset)}
    error = {'value': None}
    returned = {'value': False}
    last_instruction = {'offset': None}
    active_root = {'offset': 0, 'block': 0}
    instruction_count = {'value': 0}
    execution_trace = []
    recent_instructions = []

    def event_root_location(ip, current_cs):
        if current_cs == _selector(side.segno) and side.function_offset <= ip < side.function_offset + side.extent_size:
            return ip - side.function_offset, _block_for_ip(ip, side.function_offset, heads, side.extent_size)
        return active_root['offset'], active_root['block']

    def map_far_pointer(uc, ins):
        if ins.mnemonic not in ('les', 'lds') or len(ins.operands) < 2 or ins.operands[1].type != X86_OP_MEM:
            return False
        data_selector, _, address = _memory_operand_address(uc, ins, ins.operands[1].mem)
        if address < 0 or address + 4 > 0x110000:
            return False
        try:
            raw = bytes(uc.mem_read(address, 4))
        except UcError:
            return False
        pointer_offset = int.from_bytes(raw[:2], 'little')
        pointer_selector = int.from_bytes(raw[2:], 'little')
        if data_selector in (_selector(8), _selector(9), _selector(10)) and pointer_offset == 0 and pointer_selector == 0 and seed_null_far_pointers:
            pointer_offset, pointer_selector = 0x0100, SYNTHETIC_SELECTOR
            uc.mem_write(address, pointer_offset.to_bytes(2, 'little') + pointer_selector.to_bytes(2, 'little'))
            seeded_far_pointers.append(dict(address=_event_location(fx, labels, address), linear_address=address,
                                            selector=pointer_selector, offset=pointer_offset))
        if _selector_known(fx, side, pointer_selector):
            return False
        # Unknown segment values can alias mapped NE pages in real mode. Load
        # them through a dedicated synthetic segment so both sides see the
        # same pointer graph rather than unrelated neighbouring fixture data.
        dest = ins.operands[0]
        if dest.type != 1:
            return False
        uc.reg_write(_capstone_reg_to_unicorn(dest.reg), pointer_offset)
        uc.reg_write(UC_X86_REG_ES if ins.mnemonic == 'les' else UC_X86_REG_DS, SYNTHETIC_SELECTOR)
        synthesized_selectors[pointer_selector] = SYNTHETIC_SELECTOR
        uc.reg_write(UC_X86_REG_IP, (ins.address + ins.size) & 0xffff)
        return True

    def on_code(uc, address, size, user):
        ip = uc.reg_read(UC_X86_REG_IP)
        csreg = uc.reg_read(UC_X86_REG_CS)
        if csreg == _selector(side.segno) and ip == RETURN_IP:
            returned['value'] = True
            uc.emu_stop()
            return
        instruction_count['value'] += 1
        last_instruction['offset'] = ip - side.function_offset if csreg == _selector(side.segno) and side.function_offset <= ip < side.function_offset + side.extent_size else last_instruction['offset']
        if instruction_count['value'] > instruction_limit:
            error['value'] = 'instruction limit reached (possible loop)'
            uc.emu_stop()
            return
        in_root = code_base + side.function_offset <= address < code_base + side.function_offset + side.extent_size
        if in_root:
            if ip in heads:
                coverage.add(ip - side.function_offset)
            active_root['offset'] = ip - side.function_offset
            active_root['block'] = _block_for_ip(ip, side.function_offset, heads, side.extent_size)
        ins = ins_by_ip.get(ip) if csreg == _selector(side.segno) else None
        if ins is None:
            # Calls inside the fixture's other code are also stubbed, using a
            # fresh decode at the current address.
            ins = next(_decoder().disasm(bytes(uc.mem_read(address, min(15, size + 8))), ip, count=1), None)
        if trace_execution:
            execution_trace.append(dict(cs=csreg, ip=ip, sp=uc.reg_read(UC_X86_REG_SP),
                                        bp=uc.reg_read(UC_X86_REG_BP), ds=uc.reg_read(UC_X86_REG_DS),
                                        instruction=f'{ins.mnemonic} {ins.op_str}' if ins else None))
            if len(execution_trace) > 512:
                del execution_trace[0]
        if ins:
            recent_instructions.append(ins)
            if len(recent_instructions) > 64:
                del recent_instructions[0]
        if ins and csreg == _selector(side.segno):
            _observe_memory_reads(uc, ins, fx, global_reads)
        if ins and map_far_pointer(uc, ins):
            return
        if ins and ins.mnemonic == 'int' and ins.operands and ins.operands[0].type == X86_OP_IMM:
            vector = ins.operands[0].imm & 0xff
            if vector not in (0x10, 0x13, 0x16, 0x1a, 0x21, 0x2f):
                error['value'] = f'unsupported interrupt/control instruction int {vector:#x} at {ip:04X}'
                uc.emu_stop()
                return
            registers = [uc.reg_read(reg) & 0xffff for reg in
                         (UC_X86_REG_AX, UC_X86_REG_BX, UC_X86_REG_CX, UC_X86_REG_DX,
                          UC_X86_REG_SI, UC_X86_REG_DI, UC_X86_REG_DS, UC_X86_REG_ES)]
            ah = registers[0] >> 8
            callee = f'DOS!INT{vector:02X}_{ah:02X}'
            scripted = stub_script.get(callee, stub_script.get(callee.upper()))
            call_offset, call_block = event_root_location(ip, csreg)
            dx_pointer = _pointer_labels(fx, labels, registers[6], registers[3])
            view_payload = json.dumps(sorted(observable_memory.items()), separators=(',', ':')).encode('ascii')
            observables.append(dict(kind='call', callee=callee, argument_words=registers,
                                    argument_pointers=[dict(word_index=3, form='far', selector=registers[6], **dx_pointer)]
                                    if dx_pointer and dx_pointer.get('symbol') else [],
                                    result=dict(ax=scripted[0], dx=scripted[1]) if scripted else 'default-preserve-registers',
                                    memory_view_sha256=hashlib.sha256(view_payload).hexdigest(),
                                    memory_view_bytes=len(observable_memory), instruction_offset=call_offset,
                                    basic_block=call_block, instruction=f'int {vector:#x}', import_call=True,
                                    os_interrupt=True))
            if scripted:
                uc.reg_write(UC_X86_REG_AX, scripted[0])
                uc.reg_write(UC_X86_REG_DX, scripted[1])
            uc.reg_write(UC_X86_REG_IP, (ip + ins.size) & 0xffff)
            return
        if ins is None or not ins.group(cs.CS_GRP_CALL):
            if ins and ins.mnemonic in ('int3', 'iret', 'iretq'):
                error['value'] = f'unsupported interrupt/control instruction {ins.mnemonic} at {ip:04X}'
                uc.emu_stop()
            return
        current_segno = ((csreg - 0x1000) // 0x1000) + 1 if 0x1000 <= csreg <= 0xA000 and csreg % 0x1000 == 0 else None
        callee = _resolve_call(side, fx, ins, current_segno=current_segno, within_root=in_root)
        if callee is None:
            # Resolve register and memory indirect calls only when their target
            # is a mapped MAPSYM function or synthetic import.
            callee, _ = _decode_indirect_target(uc, ins, side, fx)
        if not callee:
            detail = ''
            if ins.operands and ins.operands[0].type == X86_OP_MEM:
                selector, offset, address = _memory_operand_address(uc, ins, ins.operands[0].mem)
                width = 4 if ins.mnemonic == 'lcall' else 2
                try:
                    raw = bytes(uc.mem_read(address, width))
                    detail = f' through {selector:04X}:{offset:04X} -> {raw.hex()}'
                except UcError:
                    pass
            error['value'] = f'unresolved indirect call at {ip:04X}{detail}'
            uc.emu_stop()
            return
        if callee.startswith('CANDIDATE!'):
            error['value'] = f'candidate call has no oracle or OS import binding: {callee}'
            uc.emu_stop()
            return
        # Use the instructions actually executed before this call. Decoding a
        # fixed 24-byte window can start mid-instruction and miss a push such
        # as `push ds`, causing incorrect imported Pascal stack cleanup.
        count = 0
        for previous in reversed(recent_instructions[:-1]):
            if previous.mnemonic != 'push':
                break
            count += 1
        count = min(count, 12)
        manual_far_selector = bool(ins.mnemonic == 'call' and len(recent_instructions) >= 2 and
                                   recent_instructions[-2].mnemonic == 'push' and
                                   recent_instructions[-2].op_str.lower() == 'cs' and
                                   _callee_returns_far(fx, callee))
        if manual_far_selector:
            count = max(0, count - 1)
        if call_signatures:
            declared_count = call_signatures.get(callee.lstrip('_'), call_signatures.get(callee))
            if declared_count is not None:
                count = declared_count
        sp = uc.reg_read(UC_X86_REG_SP)
        argument_sp = (sp + 2) & 0xffff if manual_far_selector else sp
        words = [int.from_bytes(uc.mem_read(_base(STACK_SELECTOR) + ((argument_sp + 2 * i) & 0xffff), 2), 'little') for i in range(count)]
        ret = stub_script.get(callee, stub_script.get(callee.upper(), (0, 0)))
        normalized_pointers = []
        for i, word in enumerate(words):
            near = _pointer_labels(fx, labels, uc.reg_read(UC_X86_REG_DS), word)
            if near and near.get('symbol'):
                normalized_pointers.append(dict(word_index=i, form='near', **near))
            if i + 1 < len(words) and _selector_known(fx, side, words[i + 1]):
                far = _pointer_labels(fx, labels, words[i + 1], word)
                if far and (far.get('symbol') or far.get('segment') == 'STACK'):
                    normalized_pointers.append(dict(word_index=i, form='far', selector=words[i + 1],
                                                    stack_local=far.get('segment') == 'STACK' and word < stack_offset,
                                                    **far))
        argument_word_keys = list(words)
        for pointer in normalized_pointers:
            if pointer.get('form') == 'far' and pointer.get('stack_local'):
                argument_word_keys[pointer['word_index']] = 'STACK_LOCAL_POINTER'
                if pointer['word_index'] + 1 < len(argument_word_keys):
                    argument_word_keys[pointer['word_index'] + 1] = 'STACK_SELECTOR'
        view_payload = json.dumps(sorted(observable_memory.items()), separators=(',', ':')).encode('ascii')
        call_offset, call_block = event_root_location(ip, csreg)
        is_import = '!' in callee and not callee.startswith('CANDIDATE!') and callee in fx.import_stubs
        event = dict(kind='call', callee=callee, argument_words=words,
                     argument_word_keys=argument_word_keys,
                     argument_pointers=normalized_pointers,
                     stack_words_snapshot=[int.from_bytes(uc.mem_read(_base(STACK_SELECTOR) + ((sp + 2 * i) & 0xffff), 2), 'little') for i in range(min(8, 16))],
                     result=dict(ax=ret[0], dx=ret[1]) if is_import else 'executed-oracle-code',
                     memory_view_sha256=hashlib.sha256(view_payload).hexdigest(),
                     memory_view_bytes=len(observable_memory), instruction_offset=call_offset,
                     basic_block=call_block, instruction=f'{ins.mnemonic} {ins.op_str}', import_call=is_import)
        observables.append(event)
        if not is_import:
            # Internal game calls and MSC runtime helpers execute from oracle
            # code; only true imported entries use scripted return values.
            return
        # Skipping CALL has the same net stack effect as a normal call/return.
        # Apply Pascal cleanup inferred from the callee's RET immediate.
        cleanup = _return_cleanup(fx, callee)
        if in_root and side.name == 'candidate':
            next_offset = ip - side.function_offset + ins.size
            next_ins = next(_decoder().disasm(side.code[next_offset:next_offset + 15], next_offset, count=1), None)
        else:
            call_segment = current_segno if current_segno in side.segments else side.segno
            segment_code = bytes(side.segments[call_segment])
            next_offset = ip + ins.size
            next_ins = next(_decoder().disasm(segment_code[next_offset:next_offset + 15], next_offset, count=1), None)
        caller_cleanup = bool(next_ins and next_ins.mnemonic == 'add' and next_ins.op_str.lower().startswith('sp,'))
        if not cleanup and count and not caller_cleanup:
            # Imported Pascal APIs often have no MAPSYM body from which to read
            # RET n. In their call site, absence of caller ADD SP is the ABI cue.
            cleanup = 2 * count
        if cleanup:
            uc.reg_write(UC_X86_REG_SP, (sp + cleanup) & 0xffff)
        uc.reg_write(UC_X86_REG_AX, ret[0])
        uc.reg_write(UC_X86_REG_DX, ret[1])
        uc.reg_write(UC_X86_REG_IP, (ip + ins.size) & 0xffff)

    def on_write(uc, access, address, size, value, user):
        current_ip = uc.reg_read(UC_X86_REG_IP)
        offset, block = event_root_location(current_ip, uc.reg_read(UC_X86_REG_CS))
        loc = _event_location(fx, labels, address)
        if isinstance(loc.get('segment'), int) and loc['segment'] <= 7:
            error['value'] = 'self-modifying code write at ' + json.dumps(loc, sort_keys=True)
            uc.emu_stop()
            return
        is_local_stack = loc.get('segment') == 'STACK' and loc.get('offset', 0) < stack_offset
        if is_local_stack and not strict:
            return
        masked_value = value & ((1 << (size * 8)) - 1)
        observables.append(dict(kind='write', address=loc, linear_address=address, size=size, value=masked_value,
                                instruction_offset=offset, basic_block=block,
                                strict_stack=loc.get('segment') == 'STACK'))
        for byte_index in range(size):
            observable_memory[address + byte_index] = (masked_value >> (8 * byte_index)) & 0xff

    def on_unmapped(uc, access, address, size, value, user):
        try:
            _map_synthetic_memory(uc, address, size, seed, memory_mode, synthesized_pages)
            return True
        except (UcError, FormatError) as exc:
            error['value'] = f'cannot synthesize memory at {address:#x}: {exc}'
            return False

    u.hook_add(UC_HOOK_CODE, on_code)
    u.hook_add(UC_HOOK_MEM_WRITE, on_write)
    u.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED | UC_HOOK_MEM_FETCH_UNMAPPED, on_unmapped)
    try:
        u.emu_start(code_base + side.function_offset, 0, count=instruction_limit + 1)
    except UcError as exc:
        if not error['value']:
            error['value'] = f'Unicorn execution error: {exc} at CS:IP={u.reg_read(UC_X86_REG_CS):04X}:{u.reg_read(UC_X86_REG_IP):04X}'
    result = dict(status='OK' if returned['value'] and not error['value'] else 'UNSUPPORTED',
                  error=error['value'], returned=returned['value'], observables=observables,
                  coverage=sorted(coverage), instructions=instruction_count['value'],
                  global_reads=list(global_reads.values()),
                  return_value=dict(ax=u.reg_read(UC_X86_REG_AX), dx=u.reg_read(UC_X86_REG_DX)),
                  return_instruction_offset=last_instruction['offset'],
                  return_basic_block=active_root['block'],
                  execution_trace=execution_trace,
                  synthesized_memory=dict(used=bool(synthesized_pages or synthesized_selectors or seeded_far_pointers),
                                         mode=memory_mode, pages=sorted(synthesized_pages),
                                         selector_loads=[dict(original=int(k), synthetic=int(v)) for k, v in sorted(synthesized_selectors.items())],
                                         seeded_far_pointers=seeded_far_pointers),
                  arguments=labeled_args)
    return result


def _first_divergence(target, candidate, return_words=2):
    a, b = target['observables'], candidate['observables']
    target_calls = [event for event in a if event['kind'] == 'call']
    candidate_calls = [event for event in b if event['kind'] == 'call']
    left_counts = Counter(_observable_key(event) for event in target_calls)
    right_counts = Counter(_observable_key(event) for event in candidate_calls)
    call_mismatch = None
    if left_counts != right_counts:
        shared = Counter({key: min(left_counts[key], right_counts[key]) for key in left_counts})
        def first_unmatched(events, matched):
            remaining = matched.copy()
            for event in events:
                key = _observable_key(event)
                if remaining[key]:
                    remaining[key] -= 1
                else:
                    return event
            return None
        left = first_unmatched(target_calls, shared)
        right = first_unmatched(candidate_calls, shared)
        call_mismatch = dict(index=0, target=left, candidate=right,
                             target_instruction_offset=left.get('instruction_offset') if left else None,
                             candidate_instruction_offset=right.get('instruction_offset') if right else None,
                             target_basic_block=left.get('basic_block') if left else None)

    def final_writes(events):
        state, writers = {}, {}
        for event in events:
            if event['kind'] != 'write':
                continue
            value = event['value']
            for byte_index in range(event['size']):
                address = event['linear_address'] + byte_index
                state[address] = (value >> (8 * byte_index)) & 0xff
                writers[address] = event
        return state, writers

    left_state, left_writers = final_writes(a)
    right_state, right_writers = final_writes(b)
    write_mismatches = []
    for address in sorted(set(left_state) | set(right_state)):
        if left_state.get(address) != right_state.get(address):
            left, right = left_writers.get(address), right_writers.get(address)
            details = dict(linear_address=address, target_value=left_state.get(address),
                           candidate_value=right_state.get(address))
            write_mismatches.append(dict(index=0,
                                         target=dict(kind='write', event=left, byte=details) if left else None,
                                         candidate=dict(kind='write', event=right, byte=details) if right else None,
                                         target_instruction_offset=left.get('instruction_offset') if left else None,
                                         candidate_instruction_offset=right.get('instruction_offset') if right else None,
                                         target_basic_block=left.get('basic_block') if left else None))

    def order_key(row):
        offsets = [value for value in (row.get('target_instruction_offset'), row.get('candidate_instruction_offset'))
                   if value is not None]
        return min(offsets) if offsets else float('inf')
    write_mismatch = min(write_mismatches, key=order_key) if write_mismatches else None

    differences = [item for item in (call_mismatch, write_mismatch) if item]
    target_return = {register: target['return_value'][register] for register in ('ax', 'dx')[:return_words]}
    candidate_return = {register: candidate['return_value'][register] for register in ('ax', 'dx')[:return_words]}
    if target_return != candidate_return:
        differences.append(dict(index=len(a), target=dict(kind='return', **target_return),
                                candidate=dict(kind='return', **candidate_return),
                                target_instruction_offset=target.get('return_instruction_offset'),
                                candidate_instruction_offset=candidate.get('return_instruction_offset'),
                                target_basic_block=target.get('return_basic_block')))
    if not differences:
        return None
    return min(differences, key=order_key)


def _observable_key(event):
    if event['kind'] == 'call':
        pointers = []
        stack_local_words = {pointer.get('word_index') for pointer in event.get('argument_pointers', [])
                             if pointer.get('form') == 'far' and pointer.get('stack_local')}
        for pointer in event.get('argument_pointers', []):
            if pointer.get('form') == 'near' and pointer.get('word_index') in stack_local_words:
                # The same word can look like a DGROUP offset when interpreted
                # with DS, even though its pushed selector identifies SS.
                continue
            if pointer.get('stack_local'):
                # Stack frame offsets are compiler layout. The argument still
                # identifies a local object, while raw addresses and offsets
                # vary with harmless frame-layout changes.
                pointers.append({key: value for key, value in pointer.items()
                                 if key not in ('offset', 'symbol_offset')})
            else:
                pointers.append(pointer)
        return (event['kind'], event['callee'], tuple(event.get('argument_word_keys', event['argument_words'])),
                json.dumps(pointers, sort_keys=True),
                json.dumps(event['result'], sort_keys=True),
                event.get('memory_view_sha256'))
    return event


def _execution_divergence(target, candidate):
    return dict(index=-1,
                target=dict(kind='execution', status=target['status'], error=target.get('error')),
                candidate=dict(kind='execution', status=candidate['status'], error=candidate.get('error')),
                target_instruction_offset=target.get('return_instruction_offset'),
                candidate_instruction_offset=candidate.get('return_instruction_offset'),
                target_basic_block=target.get('return_basic_block'))


def compare(symbol, draft, runs=100, seed=1, arg_values=(), stub_values=(), instruction_limit=200000,
            strict=False, memory_mode='seeded', seed_null_far_pointers=True):
    if runs < 1:
        raise FormatError('--runs must be positive')
    fx = Fixture.load()
    card, segno, start, extent, target_code = _target_code_and_extent(fx, symbol)
    path = Path(draft).resolve()
    try:
        relpath = path.relative_to(ROOT).as_posix()
    except ValueError:
        raise FormatError('candidate source must be inside this worktree')
    source = path.read_text(encoding='latin1')
    return_words = _c_return_words(source, symbol)
    profile = compiler_profiles.resolve(symbol)
    flags = compiler_profiles.profile_flags(profile['name'], card['segment_name'])
    out = ROOT / 'build/emu_diff/compile' / (symbol.lstrip('_'))
    out.mkdir(parents=True, exist_ok=True)
    staged = out / (path.name if path.name.lower().endswith('.c') else 'candidate.c')
    staged.write_text(source, encoding='latin1')
    from codegen_cache import compile_cached
    compiled, cache_info = compile_cached([dict(source=staged.relative_to(ROOT).as_posix(), flags=flags)], 'msc700')
    obj, receipt = compiled[0]
    if obj is None or receipt.get('exit_code'):
        raise FormatError('candidate compilation failed: ' + receipt.get('stdout', 'no compiler receipt'))
    if receipt.get('unsupported_option'):
        raise FormatError('compiler ignored a requested profile option')
    try:
        target_side, _ = _target_side(fx, symbol, target_code)
        candidate_side, module = _candidate_side(fx, symbol, source, obj, target_side, card)
    except FormatError as exc:
        return dict(schema='emu-diff/1', symbol=symbol, draft=relpath, profile=profile['name'], flags=flags,
                    compiled_object=receipt.get('object'), compiled_object_sha256=receipt.get('object_identity', {}).get('sha256'),
                    compiler_cache=cache_info,
                    target=dict(segment=segno, entry=start, extent=extent['size'], status=extent['status']),
                    runs=runs, executed_runs=0, seed=seed, instruction_limit=instruction_limit,
                    comparison_mode='strict' if strict else 'observable', synthesized_memory_mode=memory_mode,
                    result='UNSUPPORTED', equivalence_scope='not executed: candidate relocation/layout is unsupported',
                    first_divergence=None, unsupported=dict(phase='relocation/layout', reason=str(exc)),
                    target_basic_blocks_reached=[], observed_globals=[], sampled_results=[])
    params = _c_parameters(source, symbol)
    call_signatures = _signature_word_counts(source, fx)
    arg_overrides = dict(_parse_arg(x) for x in arg_values)
    stub_script = dict(_parse_stub(x) for x in stub_values)
    results = []
    discovered_globals = {}
    for run_index in range(runs):
        run_seed = seed + run_index
        rng = random.Random(run_seed)
        global_overrides = []
        if run_index:
            global_overrides = _direct_global_inputs(fx, symbol, target_side, rng)
            for site in list(discovered_globals.values())[:8]:
                value = rng.randrange(0, 17)
                global_overrides.append(dict(site, value=value))
        # Explicit CLI arguments are stable; automatically generated scalar
        # arguments vary by run, while pointer arguments stay null unless given.
        target = _run_side(fx, target_side, params, arg_overrides, stub_script, run_seed,
                           instruction_limit, global_overrides, strict, memory_mode, seed_null_far_pointers,
                           call_signatures)
        candidate = _run_side(fx, candidate_side, params, arg_overrides, stub_script, run_seed,
                              instruction_limit, global_overrides, strict, memory_mode, seed_null_far_pointers,
                              call_signatures)
        if target['status'] == 'OK':
            for item in target.get('global_reads', []):
                discovered_globals[(item['segment'], item['offset'], item['width'])] = item
        if candidate['status'] == 'OK':
            for item in candidate.get('global_reads', []):
                discovered_globals[(item['segment'], item['offset'], item['width'])] = item
        if target['status'] != 'OK' or candidate['status'] != 'OK':
            if target['status'] != candidate['status'] or target.get('error') != candidate.get('error'):
                divergence = _execution_divergence(target, candidate)
                status = 'DIVERGED'
            else:
                divergence = None
                status = 'UNSUPPORTED'
        else:
            divergence = _first_divergence(target, candidate, return_words)
            status = 'DIVERGED' if divergence else 'NO_DIVERGENCE'
        results.append(dict(run=run_index, seed=run_seed, status=status, divergence=divergence,
                            target=target, candidate=candidate, global_inputs=global_overrides))
        # An unsupported instruction/path cannot contribute useful additional
        # samples under this model. Stop immediately instead of disguising a
        # partial attempt as a full equivalence campaign.
        if status == 'UNSUPPORTED':
            break
    overall = 'UNSUPPORTED' if any(x['status'] == 'UNSUPPORTED' for x in results) else 'DIVERGED' if any(x['status'] == 'DIVERGED' for x in results) else 'NO_DIVERGENCE'
    report = dict(schema='emu-diff/2', symbol=symbol, draft=relpath, profile=profile['name'], flags=flags,
                  compiled_object=receipt['object'], compiled_object_sha256=receipt.get('object_identity', {}).get('sha256'),
                  compiler_cache=cache_info,
                  target=dict(segment=segno, entry=start, extent=extent['size'], status=extent['status']),
                  runs=runs, executed_runs=len(results), seed=seed, instruction_limit=instruction_limit, result=overall,
                  return_words=return_words,
                  comparison_mode='strict' if strict else 'observable', synthesized_memory_mode=memory_mode,
                  seed_null_far_pointers=seed_null_far_pointers,
                  equivalence_scope='sampled execution; oracle code and MSC runtime helpers run directly, imported Windows/OS calls use scripted stubs; this is not a proof of full Win16 behavior',
                  first_divergence=next((dict(run=x['run'], seed=x['seed'], **x['divergence']) for x in results if x['divergence']), None),
                  unsupported=next((dict(run=x['run'], target=x['target']['error'], candidate=x['candidate']['error']) for x in results if x['status']=='UNSUPPORTED'), None),
                  target_basic_blocks_reached=sorted(set(y for x in results for y in x['target']['coverage'])),
                  synthesized_memory_runs=[dict(run=x['run'], target=x['target']['synthesized_memory'],
                                                candidate=x['candidate']['synthesized_memory'])
                                           for x in results if x['target']['synthesized_memory']['used'] or x['candidate']['synthesized_memory']['used']],
                  observed_globals=sorted(discovered_globals.values(), key=lambda x: (x['segment'], x['offset'], x['width'])),
                  sampled_results=[dict(run=x['run'], status=x['status'], target_return=x['target']['return_value'],
                                        candidate_return=x['candidate']['return_value'], target_calls=sum(e['kind']=='call' for e in x['target']['observables']),
                                        candidate_calls=sum(e['kind']=='call' for e in x['candidate']['observables'])) for x in results])
    return report


def _render(report):
    lines = [f"{report['symbol']}: {report['result']} over {report['executed_runs']}/{report['runs']} requested run(s)",
             f"profile={report['profile']} target={report['target']['segment']}:{report['target']['entry']:04X} extent={report['target']['extent']} bytes",
             report['equivalence_scope']]
    if report.get('first_divergence'):
        d = report['first_divergence']
        lines += [f"first divergence: run {d['run']} seed {d['seed']} at target function offset {d['target_instruction_offset']} block {d.get('target_basic_block')}",
                  '  target: ' + json.dumps(d['target'], sort_keys=True),
                  '  candidate: ' + json.dumps(d['candidate'], sort_keys=True)]
    if report.get('unsupported'):
        lines.append('unsupported: ' + json.dumps(report['unsupported'], sort_keys=True))
    lines.append('target basic-block offsets reached: ' + ', '.join(f'{x:04X}' for x in report['target_basic_blocks_reached']))
    return '\n'.join(lines)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('symbol', nargs='?')
    parser.add_argument('draft', nargs='?')
    parser.add_argument('--runs', type=int, default=100)
    parser.add_argument('--seed', type=int, default=1)
    parser.add_argument('--arg', action='append', default=[], help='named argument override NAME=VALUE (far pointer: OFFSET:SELECTOR)')
    parser.add_argument('--stub', action='append', default=[], help='scripted call result CALLEE=AX[:DX]')
    parser.add_argument('--instruction-limit', type=int, default=200000)
    parser.add_argument('--strict', action='store_true', help='include local stack-frame writes in observable comparison')
    parser.add_argument('--memory', choices=('seeded', 'zeros'), default='seeded',
                        help='contents for lazily synthesized pages (default: deterministic seeded bytes)')
    parser.add_argument('--null-far-pointers', choices=('seed', 'keep'), default='seed',
                        help='seed null global far pointers with a synthetic segment, or preserve null values')
    parser.add_argument('--json', dest='json_path')
    args = parser.parse_args(argv)
    if not args.symbol or not args.draft:
        parser.error('SYMBOL and DRAFT.c are required')
    report = compare(args.symbol, args.draft, args.runs, args.seed, args.arg, args.stub, args.instruction_limit,
                     args.strict, args.memory, args.null_far_pointers == 'seed')
    destination = Path(args.json_path) if args.json_path else ROOT / 'build/emu_diff' / f'{args.symbol.lstrip("_")}.json'
    if not destination.is_absolute():
        destination = ROOT / destination
    write_json(destination, report)
    print(_render(report))
    print(f'JSON: {destination.relative_to(ROOT).as_posix() if destination.is_relative_to(ROOT) else destination}')
    return 0 if report['result'] != 'UNSUPPORTED' else 2


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except FormatError as exc:
        print('emu_diff: ' + str(exc), file=sys.stderr)
        raise SystemExit(2)

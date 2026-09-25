"""Rebuild and compare the original Win16 resource lane with Microsoft RC.

All oracle payloads and trial executables are written under ignored build/.
This tool never changes the fixture, recovery ledger, or tracked source assets.
"""
import argparse
import json
import os
import shutil
import subprocess
import tempfile
from pathlib import Path

from common import ROOT, FormatError, fixture, identity, read_json, sha256, write_json
import ne


ORACLE = 'SIMANTW.EXE'
RC_CANDIDATES = {
    'sdk300': 'toolchain/sdk300/RESTOOLS',
    'sdk310': 'toolchain/sdk310/RESTOOLS',
    'win30sdk-1200k': 'toolchain/WIN30SDK-1200K-DEVTOOLS/RESTOOLS',
    'msc600a': 'toolchain/msc600a/BIN',
}
DEFAULT_TEST_EXE = 'build/PARTLINK/PARTIAL.EXE'
DEFAULT_EXTRACT = 'build/resources/extracted/final'
MEMORY_BITS = {'MOVEABLE': 0x0010, 'PURE': 0x0020, 'PRELOAD': 0x0040, 'DISCARDABLE': 0x1000}
KNOWN_TYPES = {1: 'CURSOR', 2: 'BITMAP', 3: 'ICON', 4: 'MENU', 5: 'DIALOG',
               6: 'STRING', 7: 'FONTDIR', 8: 'FONT', 9: 'ACCELERATOR', 10: 'RCDATA',
               12: 'GROUP_CURSOR', 14: 'GROUP_ICON', 15: 'NAMETABLE', 16: 'VERSION'}
CONTROL_CLASSES = {0x80: 'BUTTON', 0x81: 'EDIT', 0x82: 'STATIC', 0x83: 'LISTBOX',
                   0x84: 'SCROLLBAR', 0x85: 'COMBOBOX'}
ACCEL_FLAGS = {0x01: 'VIRTKEY', 0x02: 'NOINVERT', 0x04: 'SHIFT',
               0x08: 'CONTROL', 0x10: 'ALT'}


def _resource_key(resource):
    identity = resource['identity']
    return (resource['type'].get('id', resource['type'].get('name')),
            identity.get('id', identity.get('name')))


def _repo_path(value, default):
    """Resolve a CLI path while keeping all reads and writes inside this repo."""
    path = Path(value) if value else Path(default)
    if not path.is_absolute(): path = ROOT / path
    path = path.resolve()
    try:
        path.relative_to(ROOT.resolve())
    except ValueError:
        raise FormatError('resource paths must stay inside the repository: ' + str(path))
    return path


def _rc_id(value):
    if 'id' in value:
        return str(value['id'])
    return _quote(value['name'])


def _quote(value):
    """Quote an ANSI RC string while preserving its original single-byte bytes."""
    out = []
    for char in value:
        byte = ord(char)
        if char == '"': out.append('\\"')
        elif char == '\\': out.append('\\\\')
        elif char == '\n': out.append('\\n')
        elif char == '\r': out.append('\\r')
        elif char == '\t': out.append('\\t')
        elif 32 <= byte < 127: out.append(char)
        else: out.append('\\%03o' % byte)
    return '"' + ''.join(out) + '"'


def _read_cstring(data, pos):
    end = data.find(b'\0', pos)
    if end < 0:
        raise FormatError('unterminated dialog/menu string at %04X' % pos)
    return data[pos:end].decode('latin1'), end + 1


def _read_dialog_atom(data, pos, standard_class=False):
    if pos >= len(data): raise FormatError('truncated dialog atom')
    first = data[pos]
    if first == 0: return None, pos + 1
    if first == 0xff:
        if pos + 3 > len(data): raise FormatError('truncated ordinal dialog atom')
        return {'ordinal': int.from_bytes(data[pos + 1:pos + 3], 'little')}, pos + 3
    if standard_class and first in CONTROL_CLASSES:
        return {'class_ordinal': first}, pos + 1
    return _read_cstring(data, pos)


def _write_dialog_atom(value, standard_class=False):
    if value is None: return b'\0'
    if isinstance(value, dict):
        if 'class_ordinal' in value:
            ordinal = value['class_ordinal']
            if not standard_class or ordinal not in CONTROL_CLASSES:
                raise FormatError('unsupported predefined dialog class ordinal')
            return bytes([ordinal])
        if 'ordinal' in value:
            ordinal = value['ordinal']
            if not 0 <= ordinal <= 0xffff: raise FormatError('dialog atom ordinal outside WORD')
            return b'\xff' + ordinal.to_bytes(2, 'little')
        raise FormatError('invalid dialog atom')
    return value.encode('latin1') + b'\0'


def decode_dialog(data):
    """Decode a Win16 DLGTEMPLATE, retaining alignment and unused tail bytes."""
    if len(data) < 13: raise FormatError('short Win16 dialog resource')
    model = {'style': int.from_bytes(data[0:4], 'little'), 'count': data[4],
             'x': int.from_bytes(data[5:7], 'little', signed=True),
             'y': int.from_bytes(data[7:9], 'little', signed=True),
             'width': int.from_bytes(data[9:11], 'little', signed=True),
             'height': int.from_bytes(data[11:13], 'little', signed=True)}
    p = 13
    model['menu'], p = _read_dialog_atom(data, p)
    model['class'], p = _read_dialog_atom(data, p)
    model['title'], p = _read_dialog_atom(data, p)
    model['font'] = None
    if model['style'] & 0x40:
        if p + 2 > len(data): raise FormatError('truncated dialog FONTINFO')
        point = int.from_bytes(data[p:p + 2], 'little', signed=True); p += 2
        face, p = _read_cstring(data, p)
        model['font'] = {'point': point, 'face': face}
    model['header_padding'] = b''
    model['controls'] = []
    for _ in range(model['count']):
        prepad = b''
        if p + 14 > len(data): raise FormatError('truncated dialog control template')
        row = {'x': int.from_bytes(data[p:p + 2], 'little', signed=True),
               'y': int.from_bytes(data[p + 2:p + 4], 'little', signed=True),
               'width': int.from_bytes(data[p + 4:p + 6], 'little', signed=True),
               'height': int.from_bytes(data[p + 6:p + 8], 'little', signed=True),
               'id': int.from_bytes(data[p + 8:p + 10], 'little'),
               'style': int.from_bytes(data[p + 10:p + 14], 'little'),
               'prepad': prepad}
        p += 14
        row['class'], p = _read_dialog_atom(data, p, standard_class=True)
        row['title'], p = _read_dialog_atom(data, p)
        if p >= len(data): raise FormatError('truncated dialog control creation-data length')
        extra_size = data[p]; p += 1
        if p + extra_size > len(data): raise FormatError('truncated dialog control creation data')
        row['extra'] = data[p:p + extra_size]; p += extra_size
        row['postpad'] = b''
        model['controls'].append(row)
    model['trailer'] = data[p:]
    return model


def encode_dialog(model):
    """Serialize a decoded Win16 dialog model; used for lossless parser tests."""
    out = bytearray()
    out += int(model['style']).to_bytes(4, 'little')
    controls = model['controls']
    if len(controls) > 255: raise FormatError('Win16 dialog has over 255 controls')
    out.append(len(controls))
    for field in ('x', 'y', 'width', 'height'):
        out += (int(model[field]) & 0xffff).to_bytes(2, 'little')
    out += _write_dialog_atom(model['menu'])
    out += _write_dialog_atom(model['class'])
    out += _write_dialog_atom(model['title'])
    font = model.get('font')
    if font is not None:
        out += (font['point'] & 0xffff).to_bytes(2, 'little')
        out += font['face'].encode('latin1') + b'\0'
    for row in controls:
        for field in ('x', 'y', 'width', 'height', 'id'):
            out += (int(row[field]) & 0xffff).to_bytes(2, 'little')
        out += int(row['style']).to_bytes(4, 'little')
        out += _write_dialog_atom(row['class'], standard_class=True)
        out += _write_dialog_atom(row['title'])
        extra = row.get('extra', b'')
        if len(extra) > 255: raise FormatError('Win16 dialog control creation data exceeds BYTE')
        out.append(len(extra)); out += extra
    out += model.get('trailer', b'')
    return bytes(out)


def _dialog_atom_rc(value, class_field=False):
    if value is None: return '\"\"'
    if isinstance(value, dict):
        if 'class_ordinal' in value:
            return _rc_quote_or_class(CONTROL_CLASSES[value['class_ordinal']])
        return str(value['ordinal'])
    return _quote(value)


def _rc_quote_or_class(value):
    return _quote(value)


def dialog_source(resource, model):
    lines = [_rc_id(resource['identity']) + ' DIALOG ' + ' '.join(_mem_options(resource['flags'])) +
             ' %d, %d, %d, %d' % (model['x'], model['y'], model['width'], model['height'])]
    lines.append('STYLE 0x%08X' % model['style'])
    if model['title'] is not None:
        lines.append('CAPTION ' + _dialog_atom_rc(model['title']))
    if model['menu'] is not None: lines.append('MENU ' + _dialog_atom_rc(model['menu']))
    if model['class'] is not None: lines.append('CLASS ' + _dialog_atom_rc(model['class']))
    if model['font'] is not None:
        lines.append('FONT %d, %s' % (model['font']['point'], _quote(model['font']['face'])))
    lines.append('BEGIN')
    for row in model['controls']:
        cls = row['class']
        if isinstance(cls, dict) and 'class_ordinal' in cls:
            class_name = CONTROL_CLASSES[cls['class_ordinal']]
        elif isinstance(cls, dict):
            class_name = str(cls['ordinal'])
        else:
            class_name = _quote(cls or '')
        lines.append('    CONTROL %s, %d, %s, 0x%08X, %d, %d, %d, %d' %
                     (_dialog_atom_rc(row['title']), row['id'], class_name, row['style'],
                      row['x'], row['y'], row['width'], row['height']))
    lines.append('END')
    return '\n'.join(lines)


MENU_FLAGS = {0x0001: 'GRAYED', 0x0002: 'INACTIVE', 0x0008: 'CHECKED',
              0x0020: 'MENUBARBREAK', 0x0040: 'MENUBREAK', 0x0100: 'OWNERDRAW',
              0x4000: 'HELP'}
MENU_POPUP = 0x0010
MENU_END = 0x0080
MENU_SEPARATOR = 0x0800


def _parse_menu_level(data, pos):
    items = []
    while True:
        if pos + 2 > len(data): raise FormatError('truncated MENU item flags')
        flags = int.from_bytes(data[pos:pos + 2], 'little'); pos += 2
        row = {'flags': flags}
        if flags & MENU_POPUP:
            row['id'] = None
            row['text'], pos = _read_cstring(data, pos)
            row['children'], pos = _parse_menu_level(data, pos)
        else:
            if pos + 2 > len(data): raise FormatError('truncated MENU item ID')
            row['id'] = int.from_bytes(data[pos:pos + 2], 'little'); pos += 2
            row['text'], pos = _read_cstring(data, pos)
            row['children'] = None
        items.append(row)
        if flags & MENU_END: return items, pos


def decode_menu(data):
    if len(data) < 4: raise FormatError('short Win16 MENU resource')
    version = int.from_bytes(data[0:2], 'little')
    offset = int.from_bytes(data[2:4], 'little')
    pos = 4 + offset
    if pos > len(data): raise FormatError('MENU item offset exceeds resource')
    items, pos = _parse_menu_level(data, pos)
    return {'version': version, 'offset': offset, 'padding': data[4:4 + offset],
            'items': items, 'trailer': data[pos:]}


def _encode_menu_level(items):
    if not items: raise FormatError('empty MENU level')
    out = bytearray()
    for index, row in enumerate(items):
        flags = row['flags'] & ~MENU_END
        if index == len(items) - 1: flags |= MENU_END
        out += flags.to_bytes(2, 'little')
        if flags & MENU_POPUP:
            out += row['text'].encode('latin1') + b'\0'
            out += _encode_menu_level(row['children'])
        else:
            out += int(row['id']).to_bytes(2, 'little')
            out += (row.get('text') or '').encode('latin1') + b'\0'
    return bytes(out)


def encode_menu(model):
    offset = int(model.get('offset', 0))
    padding = model.get('padding', b'')
    if len(padding) != offset: raise FormatError('MENU offset/padding length mismatch')
    return (int(model['version']).to_bytes(2, 'little') + offset.to_bytes(2, 'little') +
            padding + _encode_menu_level(model['items']) + model.get('trailer', b''))


def _menu_options(flags):
    unsupported = flags & ~(MENU_POPUP | MENU_END | MENU_SEPARATOR | sum(MENU_FLAGS))
    if unsupported: raise FormatError('unsupported MENU flags 0x%04X' % unsupported)
    return [name for bit, name in MENU_FLAGS.items() if flags & bit]


def _menu_level_source(items, indent):
    lines = []
    for row in items:
        options = _menu_options(row['flags'])
        suffix = ', ' + ', '.join(options) if options else ''
        if row['flags'] & MENU_POPUP:
            lines.append(indent + 'POPUP ' + _quote(row['text']) + suffix)
            lines.append(indent + 'BEGIN')
            lines.extend(_menu_level_source(row['children'], indent + '    '))
            lines.append(indent + 'END')
        elif row['flags'] & MENU_SEPARATOR:
            lines.append(indent + 'MENUITEM SEPARATOR' + suffix)
        else:
            lines.append(indent + 'MENUITEM ' + _quote(row['text'] or '') + ', ' +
                         str(row['id']) + suffix)
    return lines


def menu_source(resource, model):
    lines = [_rc_id(resource['identity']) + ' MENU ' + ' '.join(_mem_options(resource['flags'])), 'BEGIN']
    lines.extend(_menu_level_source(model['items'], '    '))
    lines.append('END')
    return '\n'.join(lines)


def decode_accelerators(data):
    rows = []; pos = 0
    while pos + 5 <= len(data):
        flags = data[pos]
        key = int.from_bytes(data[pos + 1:pos + 3], 'little')
        command = int.from_bytes(data[pos + 3:pos + 5], 'little')
        rows.append({'flags': flags, 'key': key, 'command': command})
        pos += 5
        if flags & 0x80: return {'entries': rows, 'trailer': data[pos:]}
    raise FormatError('accelerator table has no final LAST record')


def encode_accelerators(model):
    out = bytearray()
    for row in model['entries']:
        flags = row['flags']
        out.append(flags)
        out += int(row['key']).to_bytes(2, 'little')
        out += int(row['command']).to_bytes(2, 'little')
    return bytes(out) + model.get('trailer', b'')


def accelerator_source(resource, model):
    # Win3 RC's ACCELERATORS grammar has no memory-attribute clause; the RC default is MOVEABLE PURE.
    lines = [_rc_id(resource['identity']) + ' ACCELERATORS', 'BEGIN']
    for row in model['entries']:
        options = []
        if row['flags'] & 0x01: options.append('VIRTKEY')
        elif row['flags'] & ~0x80 & 0x1e: options.append('ASCII')
        for bit, token in ACCEL_FLAGS.items():
            if row['flags'] & bit and bit != 0x01: options.append(token)
        unsupported = row['flags'] & ~(0x80 | sum(ACCEL_FLAGS))
        if unsupported: raise FormatError('unsupported accelerator flags 0x%02X' % unsupported)
        lines.append('    0x%04X, %d%s' % (row['key'], row['command'],
                     ', ' + ', '.join(options) if options else ''))
    lines.append('END')
    return '\n'.join(lines)


def _mem_options(flags):
    result = []
    result.append('MOVEABLE' if flags & MEMORY_BITS['MOVEABLE'] else 'FIXED')
    result.append('PURE' if flags & MEMORY_BITS['PURE'] else 'IMPURE')
    result.append('PRELOAD' if flags & MEMORY_BITS['PRELOAD'] else 'LOADONCALL')
    result.append('DISCARDABLE' if flags & MEMORY_BITS['DISCARDABLE'] else 'NONDISCARDABLE')
    return result


def _resource_type_token(resource):
    typ = resource['type']
    if 'id' in typ:
        value = typ['id']
        if value in (5, 9): return KNOWN_TYPES[value]
        return str(value)
    return _quote(typ['name'])


def _stringtable_source(resources, payloads):
    if not resources: return []
    flags = {row['flags'] for row in resources}
    if len(flags) != 1:
        raise FormatError('STRINGTABLE blocks have differing memory flags; one RC STRINGTABLE statement cannot preserve them')
    lines = ['STRINGTABLE ' + ' '.join(_mem_options(next(iter(flags)))), 'BEGIN']
    for row in resources:
        block = row['identity']['id']
        data = payloads[_resource_key(row)]
        if len(data) < 32: raise FormatError('short STRINGTABLE block %d' % block)
        pos = 0
        for index in range(16):
            size = int.from_bytes(data[pos:pos + 2], 'little'); pos += 2
            if pos + size > len(data): raise FormatError('truncated STRINGTABLE block %d' % block)
            text = data[pos:pos + size].decode('latin1'); pos += size
            if text:
                string_id = (block - 1) * 16 + index
                lines.append('    %d, %s' % (string_id, _quote(text)))
        if any(data[pos:]):
            raise FormatError('nonzero bytes after STRINGTABLE block %d' % block)
    lines.append('END')
    return ['\n'.join(lines)]


def _build_group_image(group, payloads, lookup, output_path, cursor=False):
    packed = payloads[_resource_key(group)]
    if len(packed) < 6: raise FormatError('short group image resource: ' + str(group['identity']))
    reserved = int.from_bytes(packed[0:2], 'little')
    group_type = int.from_bytes(packed[2:4], 'little')
    count = int.from_bytes(packed[4:6], 'little')
    if reserved != 0 or group_type != (2 if cursor else 1) or 6 + count * 14 > len(packed):
        raise FormatError('invalid group image directory: ' + str(group['identity']))
    records = []
    images = []
    leaf_type = 1 if cursor else 3
    for i in range(count):
        p = 6 + i * 14
        item = packed[p:p + 14]
        width, height, colors, reserved_byte = item[:4]
        first_word = int.from_bytes(item[4:6], 'little')
        second_word = int.from_bytes(item[6:8], 'little')
        image_size = int.from_bytes(item[8:12], 'little')
        leaf_id = int.from_bytes(item[12:14], 'little')
        key = (leaf_type, leaf_id)
        if key not in lookup: raise FormatError('group image refers to missing leaf resource %r' % (key,))
        leaf = payloads[_resource_key(lookup[key])]
        image = leaf[4:4 + image_size] if cursor else leaf[:image_size]
        if len(image) != image_size: raise FormatError('group image leaf is shorter than directory size')
        records.append((width, height, colors, reserved_byte, first_word, second_word, image_size))
        images.append(image)
    offset = 6 + count * 16
    directory = bytearray((0).to_bytes(2, 'little') + (2 if cursor else 1).to_bytes(2, 'little') + count.to_bytes(2, 'little'))
    for row in records:
        width, height, colors, reserved_byte, first_word, second_word, image_size = row
        directory += bytes((width, height, colors, reserved_byte))
        directory += first_word.to_bytes(2, 'little') + second_word.to_bytes(2, 'little')
        directory += image_size.to_bytes(4, 'little') + offset.to_bytes(4, 'little')
        offset += image_size
    for image in images: directory += image
    output_path.write_bytes(directory)


def build_script(image, raw, output_dir):
    """Extract payloads and decompile RC-readable templates in NE table order."""
    payload_dir = output_dir / 'payloads'
    payload_dir.mkdir(parents=True, exist_ok=True)
    resources = image['resources']
    payloads = {_resource_key(row): raw[row['offset']:row['offset'] + row['size']] for row in resources}
    lookup = {}
    for row in resources:
        t = row['type'].get('id')
        rid = row['identity'].get('id')
        if t is not None and rid is not None: lookup[(t, rid)] = row
    lines = ['/* Decompiled from the verified SIMANTW.EXE fixture. */']
    strings = [row for row in resources if row['type'].get('id') == 6]
    string_lines = _stringtable_source(strings, payloads)
    string_emitted = False
    grouped_leaf_keys = set()
    group_files = {}
    for index, row in enumerate(resources):
        t = row['type'].get('id')
        if t not in (12, 14): continue
        cursor = t == 12
        ext = 'CUR' if cursor else 'ICO'
        name = 'R%02d.%s' % (index, ext)
        path = payload_dir / name
        _build_group_image(row, payloads, lookup, path, cursor=cursor)
        group_files[_resource_key(row)] = name
        group_type = 1 if cursor else 3
        packed = payloads[_resource_key(row)]
        count = int.from_bytes(packed[4:6], 'little')
        for child in range(count):
            entry = packed[6 + child * 14:6 + (child + 1) * 14]
            grouped_leaf_keys.add((group_type, int.from_bytes(entry[12:14], 'little')))
    inventory = []
    for index, row in enumerate(resources):
        type_id = row['type'].get('id')
        entry = {'index': index, 'type': row['type'], 'type_name': row['type_name'],
                 'identity': row['identity'], 'flags': row['flags'], 'flag_names': row['flag_names'],
                 'size': row['size'], 'sha256': row['sha256'], 'offset': row['offset']}
        inventory.append(entry)
        if type_id == 6:
            if not string_emitted:
                lines.extend(string_lines); string_emitted = True
            continue
        if type_id in (1, 3) and (type_id, row['identity'].get('id')) in grouped_leaf_keys:
            # RC emits these RT_CURSOR/RT_ICON leaf entries when it reads each
            # CUR/ICO directory, preserving their original ordinal IDs.
            continue
        if type_id == 4:
            lines.append(menu_source(row, decode_menu(payloads[_resource_key(row)])))
        elif type_id == 5:
            lines.append(dialog_source(row, decode_dialog(payloads[_resource_key(row)])))
        elif type_id == 9:
            lines.append(accelerator_source(row, decode_accelerators(payloads[_resource_key(row)])))
        elif type_id in (12, 14):
            ext = 'CURSOR' if type_id == 12 else 'ICON'
            name = group_files[_resource_key(row)]
            lines.append('%s %s %s "%s"' % (_rc_id(row['identity']), ext,
                         ' '.join(_mem_options(row['flags'])), 'payloads/' + name))
        elif type_id in (1, 3):
            # A standalone image needs an image-directory source for RC.
            raise FormatError('orphan cursor/icon leaf has no group directory to name it')
            name = 'R%02d.BIN' % index
            (payload_dir / name).write_bytes(payloads[_resource_key(row)])
            lines.append('%s %s %s "%s"' % (_rc_id(row['identity']), str(type_id),
                         ' '.join(_mem_options(row['flags'])), 'payloads/' + name))
        elif type_id == 2:
            # NE RT_BITMAP excludes the 14-byte BITMAPFILEHEADER. RC's BITMAP
            # input requires it, so construct the standard file wrapper locally.
            payload = payloads[_resource_key(row)]
            if len(payload) < 4: raise FormatError('short bitmap resource')
            dib_size = int.from_bytes(payload[:4], 'little')
            if dib_size < 12 or dib_size > len(payload): raise FormatError('invalid bitmap DIB header')
            name = 'R%02d.BMP' % index
            off_bits = 14 + dib_size
            header = b'BM' + (14 + len(payload)).to_bytes(4, 'little') + b'\0\0\0\0' + off_bits.to_bytes(4, 'little')
            (payload_dir / name).write_bytes(header + payload)
            lines.append('%s BITMAP %s "%s"' % (_rc_id(row['identity']), ' '.join(_mem_options(row['flags'])), 'payloads/' + name))
        elif type_id in (5, 9):
            raise AssertionError('text resource dispatch fell through')
        elif type_id is not None and type_id in KNOWN_TYPES:
            token = KNOWN_TYPES[type_id]
            if token == 'RCDATA':
                name = 'R%02d.BIN' % index
                (payload_dir / name).write_bytes(payloads[_resource_key(row)])
                lines.append('%s RCDATA %s "%s"' % (_rc_id(row['identity']), ' '.join(_mem_options(row['flags'])), 'payloads/' + name))
            elif token == 'FONT':
                name = 'R%02d.FNT' % index
                (payload_dir / name).write_bytes(payloads[_resource_key(row)])
                lines.append('%s FONT %s "%s"' % (_rc_id(row['identity']), ' '.join(_mem_options(row['flags'])), 'payloads/' + name))
            else:
                raise FormatError('text/binary resource type needs a dedicated decompiler: ' + token)
        else:
            name = 'R%02d.BIN' % index
            (payload_dir / name).write_bytes(payloads[_resource_key(row)])
            if 'name' in row['type']:
                typ = _quote(row['type']['name'])
            elif type_id is not None and type_id > 255:
                typ = str(type_id)
            else:
                raise FormatError('numeric predefined resource type needs a dedicated RC decompiler: %r' % (type_id,))
            lines.append('%s %s %s "%s"' % (_rc_id(row['identity']), typ,
                         ' '.join(_mem_options(row['flags'])), 'payloads/' + name))
    script = '\n\n'.join(lines) + '\n'
    script_path = output_dir / 'SIMANTW.RC'
    script_path.write_text(script, encoding='latin1', newline='\r\n')
    manifest = {'oracle': identity(ROOT / 'assets' / ORACLE), 'resource_count': len(resources),
                'resource_alignment_shift': image['resource_alignment_shift'], 'resources': inventory,
                'script': script_path.relative_to(ROOT).as_posix(), 'script_identity': identity(script_path),
                'payload_directory': payload_dir.relative_to(ROOT).as_posix()}
    write_json(output_dir / 'manifest.json', manifest)
    return manifest, script_path

def extract(output=None):
    output_dir = _repo_path(output, DEFAULT_EXTRACT)
    output_dir.mkdir(parents=True, exist_ok=True)
    raw = fixture(ORACLE)
    image = ne.parse(raw)
    manifest, script = build_script(image, raw, output_dir)
    return {'output': output_dir.relative_to(ROOT).as_posix(), 'script': script.relative_to(ROOT).as_posix(),
            'resources': manifest['resource_count'], 'alignment_shift': manifest['resource_alignment_shift']}


def _tool_files(tool_dir):
    path = ROOT / tool_dir
    if not (path / 'RC.EXE').is_file():
        raise FormatError('missing pinned RC executable: ' + str(path / 'RC.EXE'))
    sources = {'RC.EXE': path / 'RC.EXE'}
    for name in ('RCPP.EXE', 'RCPP.ERR'):
        candidate = path / name
        if candidate.is_file():
            sources[name] = candidate
    if 'RCPP.EXE' not in sources:
        raise FormatError('missing RCPP.EXE beside ' + str(path / 'RC.EXE'))
    # Do not cross-load another SDK's diagnostics catalogue: a matching version
    # is part of an authentic RC execution.
    if 'RCPP.ERR' not in sources:
        raise FormatError('missing RCPP.ERR beside ' + str(path / 'RC.EXE'))
    return {name: identity(source) for name, source in sources.items()}, sources


def _run_version(version, tool_dir, script, test_exe, work_root):
    tool_identities, tool_sources = _tool_files(tool_dir)
    run_dir = work_root / version
    run_dir.mkdir(parents=True, exist_ok=True)
    for name in tool_identities: shutil.copyfile(tool_sources[name], run_dir / name)
    shutil.copyfile(script, run_dir / 'SIMANT.RC')
    source_payloads = script.parent / 'payloads'
    if source_payloads.is_dir(): shutil.copytree(source_payloads, run_dir / 'payloads', dirs_exist_ok=True)
    shutil.copyfile(test_exe, run_dir / 'TEST.EXE')
    (run_dir / 'GO.BAT').write_text(
        '@echo off\nRC /r SIMANT.RC > COMPILE.LOG\nif errorlevel 1 goto failed\n'
        'RC SIMANT.RES TEST.EXE > BIND.LOG\nif errorlevel 1 goto failed\n'
        'echo finished > DONE.TXT\ngoto end\n:failed\necho failed > FAILED.TXT\n:end\nexit\n',
        encoding='ascii', newline='\r\n')
    config = ('[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n'
              '[dosbox]\nmemsize=32\n[cpu]\ncycles=max\n[autoexec]\nmount w "' +
              str(run_dir) + '"\nw:\nset PATH=W:\nGO.BAT\nexit\n')
    conf = run_dir / 'RUN.CONF'
    conf.write_text(config, encoding='ascii', newline='\r\n')
    runner = ROOT / 'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'
    if not runner.is_file(): raise FormatError('DOSBox-X runner is missing: ' + str(runner))
    command = [str(runner), '-conf', str(conf), '-fastlaunch', '-nogui', '-nomenu', '-noconsole']
    env = {k: v for k, v in os.environ.items() if k.upper() in ('SYSTEMROOT', 'WINDIR', 'COMSPEC')}
    env.update(SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy')
    process = subprocess.run(command, cwd=run_dir, env=env, capture_output=True, timeout=90)
    succeeded = (run_dir / 'DONE.TXT').is_file() and not (run_dir / 'FAILED.TXT').exists()
    logs = {}
    for name in ('COMPILE.LOG', 'BIND.LOG'):
        p = run_dir / name
        if p.is_file(): logs[name] = p.read_text(encoding='latin1')
    result = {'version': version, 'tool_directory': tool_dir, 'tools': tool_identities,
              'tool_sources': {name: source.relative_to(ROOT).as_posix() for name, source in tool_sources.items()},
              'command': command, 'exit_code': 0 if succeeded else (process.returncode or 1),
              'runner_return_code': process.returncode, 'logs': logs,
              'runner_stderr': process.stderr.decode('latin1'),
              'script': identity(script), 'test_input': identity(test_exe)}
    output = run_dir / 'TEST.EXE'
    if succeeded and output.is_file(): result['output'] = identity(output)
    return result, output if succeeded and output.is_file() else None


def _normalized_table(raw, image):
    header = image['header']
    start = header['file_offset'] + header['resource_table_offset']
    end = header['file_offset'] + header['resident_table_offset']
    if end < start: raise FormatError('bad NE resource table bounds')
    table = bytearray(raw[start:end])
    for row in image['resources']:
        pos = row['table_offset'] - start
        if pos < 0 or pos + 2 > len(table): raise FormatError('resource record outside resource table')
        table[pos:pos + 2] = b'\0\0'  # Absolute sector varies with the linked test image.
    return bytes(table)


def _type_key(resource):
    value = resource['type']
    return ('id', value['id']) if 'id' in value else ('name', value['name'])


def compare_resources(oracle_raw, oracle, candidate_raw, candidate):
    expected = oracle['resources']; actual = candidate['resources']
    actual_groups = {}
    for index, row in enumerate(actual):
        actual_groups.setdefault(_type_key(row), []).append((index, row))
    expected_rank = {}
    rows = []
    matched_actual = set()
    for oracle_index, left in enumerate(expected):
        kind = _type_key(left)
        rank = expected_rank.get(kind, 0); expected_rank[kind] = rank + 1
        bucket = actual_groups.get(kind, [])
        if rank >= len(bucket):
            rows.append({'index': oracle_index, 'oracle': _resource_key(left), 'candidate': None,
                         'candidate_mapping': 'same-type occurrence %d unavailable' % (rank + 1),
                         'status': 'missing', 'checks': {}})
            continue
        candidate_index, right = bucket[rank]
        matched_actual.add(candidate_index)
        left_bytes = oracle_raw[left['offset']:left['offset'] + left['size']]
        right_bytes = candidate_raw[right['offset']:right['offset'] + right['size']]
        checks = {'type_and_identity': _resource_key(left) == _resource_key(right),
                  'flags': left['flags'] == right['flags'],
                  'size': left['size'] == right['size'],
                  'bytes': left_bytes == right_bytes,
                  'handle': left['handle'] == right['handle'], 'usage': left['usage'] == right['usage']}
        rows.append({'index': oracle_index, 'oracle': _resource_key(left),
                     'candidate_index': candidate_index, 'candidate': _resource_key(right),
                     'candidate_mapping': 'same resource type, occurrence %d' % (rank + 1),
                     'status': 'exact' if all(checks.values()) else 'mismatch', 'checks': checks,
                     'oracle_offset': left['offset'], 'candidate_offset': right['offset'],
                     'oracle_size': left['size'], 'candidate_size': right['size'],
                     'oracle_sha256': left['sha256'], 'candidate_sha256': right['sha256']})
    extras = [{'index': i, 'resource': _resource_key(row), 'flags': row['flags'],
               'size': row['size'], 'sha256': row['sha256']}
              for i, row in enumerate(actual) if i not in matched_actual]
    shift_exact = oracle['resource_alignment_shift'] == candidate['resource_alignment_shift']
    order_exact = [_resource_key(x) for x in expected] == [_resource_key(x) for x in actual]
    table_exact = _normalized_table(oracle_raw, oracle) == _normalized_table(candidate_raw, candidate)
    oracle_base = min((r['offset'] for r in expected), default=0)
    actual_base = min((actual[r['candidate_index']]['offset'] for r in rows if r.get('candidate_index') is not None), default=0)
    # Compare relative resource positions by the same-type occurrence mapping.
    layout_expected = []
    layout_actual = []
    for row in rows:
        if row.get('candidate_index') is None: continue
        left = expected[row['index']]; right = actual[row['candidate_index']]
        layout_expected.append((left['offset'] - oracle_base, left['size']))
        layout_actual.append((right['offset'] - actual_base, right['size']))
    layout_exact = layout_expected == layout_actual and len(layout_expected) == len(expected)
    all_rows_exact = len(rows) == len(expected) and all(r.get('status') == 'exact' for r in rows)
    return {'exact': bool(expected) and len(expected) == len(actual) and not extras and shift_exact and order_exact and table_exact and layout_exact and all_rows_exact,
            'oracle_count': len(expected), 'candidate_count': len(actual),
            'alignment_shift': {'oracle': oracle['resource_alignment_shift'],
                                'candidate': candidate['resource_alignment_shift'], 'exact': shift_exact},
            'ordering_exact': order_exact, 'normalized_table_exact': table_exact,
            'relative_data_layout_exact': layout_exact,
            'resource_payloads_equal': sum(bool(r.get('checks', {}).get('bytes')) for r in rows),
            'resource_flags_equal': sum(bool(r.get('checks', {}).get('flags')) for r in rows),
            'resource_identities_equal': sum(bool(r.get('checks', {}).get('type_and_identity')) for r in rows),
            'extra_resources': extras, 'resources': rows}


def check(test_exe=None, output=None, version_names=None):
    extracted = ROOT / DEFAULT_EXTRACT
    extract()
    script = extracted / 'SIMANTW.RC'
    exe = _repo_path(test_exe, DEFAULT_TEST_EXE)
    if not exe.is_file():
        raise FormatError('test NE is missing; build a structural test with tools/partial_link.py first')
    test_identity = identity(exe)
    oracle_raw = fixture(ORACLE); oracle = ne.parse(oracle_raw)
    target_raw = exe.read_bytes(); target = ne.parse(target_raw)
    if target_identity_matches_oracle(test_identity, identity(ROOT / 'assets' / ORACLE)):
        raise FormatError('refusing to attach resources to the oracle executable')
    if target['resources']:
        raise FormatError('test executable already has resources; use an empty structural NE image')
    work = _repo_path(output, 'build/resources/check')
    work.mkdir(parents=True, exist_ok=True)
    # Keep each run in a fresh folder so reruns never remove or overwrite DOS
    # outputs from a previous attempt.
    run_root = Path(tempfile.mkdtemp(prefix='run-', dir=work))
    version_results = {}
    selected = {name: path for name, path in RC_CANDIDATES.items() if version_names is None or name in version_names}
    for name, tool_dir in selected.items():
        try:
            run, candidate_path = _run_version(name, tool_dir, script, exe, run_root)
            if candidate_path:
                candidate_raw = candidate_path.read_bytes()
                candidate = ne.parse(candidate_raw)
                run['comparison'] = compare_resources(oracle_raw, oracle, candidate_raw, candidate)
                run['candidate_ne'] = {'identity': identity(candidate_path),
                                       'resource_alignment_shift': candidate['resource_alignment_shift'],
                                       'resource_table_offset': candidate['header']['resource_table_offset'],
                                       'resident_table_offset': candidate['header']['resident_table_offset']}
            version_results[name] = run
        except (OSError, subprocess.SubprocessError, FormatError) as exc:
            path = ROOT / tool_dir
            available = {file: identity(path / file) for file in ('RC.EXE', 'RCPP.EXE', 'RCPP.ERR')
                         if (path / file).is_file()}
            version_results[name] = {'version': name, 'tool_directory': tool_dir,
                                     'available_tools': available, 'error': str(exc)}
    report = {'scope': 'AUTHENTIC_RC_RESOURCE_REPRODUCTION',
              'oracle': identity(ROOT / 'assets' / ORACLE), 'test_input': test_identity,
              'resource_count': len(oracle['resources']), 'oracle_alignment_shift': oracle['resource_alignment_shift'],
              'versions': version_results}
    write_json(work / 'results.json', report)
    exact = [name for name, result in version_results.items() if result.get('comparison', {}).get('exact')]
    return {'report': (work / 'results.json').relative_to(ROOT).as_posix(), 'exact_versions': exact,
            'versions': {name: (result.get('comparison') or {}).get('exact', False) for name, result in version_results.items()}}


def target_identity_matches_oracle(left, right):
    return left['size'] == right['size'] and left['sha256'] == right['sha256']


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest='command', required=True)
    ex = sub.add_parser('extract', help='decompile resources into build/resources')
    ex.add_argument('--out', help='output directory relative to repository root')
    ck = sub.add_parser('check', help='compile and bind through each pinned Microsoft RC')
    ck.add_argument('--exe', help='empty structural NE test executable, relative to root')
    ck.add_argument('--out', help='trial output directory relative to root')
    ck.add_argument('--version', choices=tuple(RC_CANDIDATES), action='append', help='check only this RC candidate (repeatable)')
    args = parser.parse_args()
    try:
        result = extract(args.out) if args.command == 'extract' else check(args.exe, args.out, args.version)
        print(json.dumps(result, indent=2))
        if args.command == 'check' and not result['exact_versions']:
            raise SystemExit(1)
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))


if __name__ == '__main__':
    main()

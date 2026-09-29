"""Unicorn emulator for the MSC C/C++ 7.00 DOSX32 pass executables (C23216, C33216, C13216).

The passes are flat 32-bit early-PE images importing about two dozen Win32
functions by ordinal from MS32KRNL.DLL (CreateFileA, ReadFile, VirtualAlloc,
...).  This module maps the image at its preferred base, resolves the ordinals
through MS32KRNL's own export table, and implements those functions in Python
over an in-memory file system.  No compiler binary is modified; the images are
read-only inputs.

Typical use::

    emu = PassEmulator('C23216.EXE', env={'MSC_CMD_FLAGS': flags},
                       files={'W:\\185436EX': b'...', ...})
    rc = emu.run()
    emu.files['W:\\185436PR']   # output bytes

Instrumentation hooks (`add_code_hook`) let callers trace compiler internals.
"""
from __future__ import annotations

import struct
from pathlib import Path

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_PROT_ALL, \
    UC_HOOK_MEM_UNMAPPED
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EBP,
                               UC_X86_REG_FS, UC_X86_REG_GDTR, UC_X86_REG_SS,
                               UC_X86_REG_DS, UC_X86_REG_ES)

ROOT = Path(__file__).resolve().parents[1]
BIN = ROOT / 'toolchain' / 'msc700' / 'BIN'

STUB_BASE = 0x00100000
STACK_BASE = 0x00200000
STACK_SIZE = 0x00100000
TIB_BASE = 0x00300000
GDT_BASE = 0x00301000
ENV_BASE = 0x00310000
VA_BASE = 0x01000000          # VirtualAlloc arena
VA_LIMIT = 0x40000000
PAGE = 0x1000


def _u32(b, o):
    return struct.unpack_from('<I', b, o)[0]


_EXPORTS = None


def krnl_exports(path=BIN / 'MS32KRNL.DLL'):
    """Map MS32KRNL ordinal -> export name (header-resident export directory)."""
    global _EXPORTS
    if _EXPORTS is not None:
        return _EXPORTS
    d = Path(path).read_bytes()
    h = _u32(d, 0x3C)
    exp = _u32(d, h + 0x70)
    base = _u32(d, exp + 0x10)
    nnames = _u32(d, exp + 0x18)
    names_rva = _u32(d, exp + 0x20)
    ords_rva = _u32(d, exp + 0x24)
    # The name/ordinal arrays and the name strings sit at RVA+0x200 in this file.
    bias = 0x200
    out = {}
    for i in range(nnames):
        np_ = _u32(d, names_rva + bias + 4 * i) + bias
        idx = struct.unpack_from('<H', d, ords_rva + bias + 2 * i)[0]
        out[idx + base] = d[np_:np_ + 64].split(b'\0')[0].decode('ascii')
    _EXPORTS = out
    return out


class Image:
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        d = self.data
        h = _u32(d, 0x3C)
        if d[h:h + 4] != b'PE\0\0':
            raise ValueError('not a DOSX32 PE image: %s' % path)
        self.entry_rva = _u32(d, h + 0x24)
        self.base = _u32(d, h + 0x28)
        nobj = _u32(d, h + 0x50)
        tab = _u32(d, h + 0x54)
        self.objects = [struct.unpack_from('<6I', d, tab + 24 * i) for i in range(nobj)]
        imp = _u32(d, h + 0x78)
        self.iat_rva = _u32(d, imp + 0x10)
        self.dll = d[imp + _u32(d, imp + 0x0C):].split(b'\0')[0].decode()


class VFile:
    def __init__(self, name, data=b'', writable=False):
        self.name = name
        self.data = bytearray(data)
        self.pos = 0
        self.writable = writable


class PassEmulator:
    STD = {0xFFFFFFF6: 'stdin', 0xFFFFFFF5: 'stdout', 0xFFFFFFF4: 'stderr'}

    def __init__(self, exe='C23216.EXE', *, env=None, files=None, cmdline=None, trace_api=False,
                 insn_limit=0, module_dir='T:\\BIN\\', cwd='W:\\'):
        self.cwd = cwd.upper()
        self.exe_name = exe
        self.module_dir = module_dir
        self.img = Image(BIN / exe)
        self.env = dict(env or {})
        self.files = {k.upper(): bytes(v) for k, v in (files or {}).items()}
        self.cmdline = cmdline if cmdline is not None else (module_dir + exe)
        self.trace_api = trace_api
        self.api_log = []
        self.stdout = bytearray()
        self.stderr = bytearray()
        self.handles = {}
        self.next_handle = 0x100
        self.last_error = 0
        self.exit_code = None
        self.insn_limit = insn_limit
        self.va_next = VA_BASE
        self.va_regions = {}
        self.fault = None
        self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
        self._load()

    # ------------------------------------------------------------------ setup
    def _map(self, addr, size):
        size = (size + PAGE - 1) & ~(PAGE - 1)
        self.uc.mem_map(addr, size, UC_PROT_ALL)

    def _load(self):
        uc, img = self.uc, self.img
        hdr_size = min(img.objects[0][0], 0x10000)
        self._map(img.base, hdr_size)
        uc.mem_write(img.base, img.data[:hdr_size])
        for (orva, vsize, seek, dsize, _flags, _r) in img.objects:
            size = max(vsize, dsize)
            self._map(img.base + orva, size)
            uc.mem_write(img.base + orva, img.data[seek:seek + dsize])
        exports = krnl_exports()
        self.stubs = {}
        iat = img.base + img.iat_rva
        stub_code = bytearray()
        k = 0
        while True:
            ordinal = struct.unpack('<I', uc.mem_read(iat + 4 * k, 4))[0]
            if ordinal == 0:
                break
            name = exports.get(ordinal & 0x7FFFFFFF, 'ord%d' % (ordinal & 0x7FFFFFFF))
            addr = STUB_BASE + 16 * k
            nbytes = int(name.split('@')[1]) if '@' in name else 0
            code = (b'\xC2' + struct.pack('<H', nbytes)) if nbytes else b'\xC3'
            stub_code += code.ljust(16, b'\xCC')
            uc.mem_write(iat + 4 * k, struct.pack('<I', addr))
            self.stubs[addr] = (name.lstrip('_').split('@')[0], nbytes)
            k += 1
        self._map(STUB_BASE, PAGE)
        uc.mem_write(STUB_BASE, bytes(stub_code))
        uc.hook_add(UC_HOOK_CODE, self._api_hook, begin=STUB_BASE, end=STUB_BASE + len(stub_code))
        self._map(STACK_BASE, STACK_SIZE)
        self._map(TIB_BASE, PAGE)
        tib = struct.pack('<III', 0xFFFFFFFF, STACK_BASE + STACK_SIZE, STACK_BASE) + b'\0' * 12
        tib += struct.pack('<I', TIB_BASE)
        uc.mem_write(TIB_BASE, tib)
        self._setup_gdt()
        self._map(ENV_BASE, 0x10000)
        envblock = b''.join(('%s=%s' % kv).encode('latin1') + b'\0' for kv in self.env.items()) + b'\0'
        self.env_addr = ENV_BASE
        uc.mem_write(ENV_BASE, envblock)
        self.cmd_addr = ENV_BASE + 0x8000
        uc.mem_write(self.cmd_addr, self.cmdline.encode('latin1') + b'\0')
        self.trap = STUB_BASE + 0xFF0
        uc.mem_write(self.trap, b'\xF4')
        esp = STACK_BASE + STACK_SIZE - 0x100
        uc.mem_write(esp, struct.pack('<I', self.trap))
        uc.reg_write(UC_X86_REG_ESP, esp)
        uc.reg_write(UC_X86_REG_EBP, 0)
        uc.hook_add(UC_HOOK_MEM_UNMAPPED, self._unmapped)

    def _setup_gdt(self):
        uc = self.uc
        self._map(GDT_BASE, PAGE)

        def desc(base, limit, access, flags=0xC):
            return struct.pack('<Q', (limit & 0xFFFF) | ((base & 0xFFFFFF) << 16) | (access << 40)
                               | (((limit >> 16) & 0xF) << 48) | (flags << 52) | ((base >> 24) << 56))
        gdt = desc(0, 0, 0) + desc(0, 0xFFFFF, 0x9B) + desc(0, 0xFFFFF, 0x93) \
            + desc(TIB_BASE, 0xFFF, 0x93, 0x4)
        uc.mem_write(GDT_BASE, gdt)
        uc.reg_write(UC_X86_REG_GDTR, (0, GDT_BASE, len(gdt) - 1, 0x0))
        uc.reg_write(UC_X86_REG_SS, 2 << 3)
        uc.reg_write(UC_X86_REG_DS, 2 << 3)
        uc.reg_write(UC_X86_REG_ES, 2 << 3)
        uc.reg_write(UC_X86_REG_FS, 3 << 3)

    def _unmapped(self, uc, access, address, size, value, data):
        self.fault = (access, hex(address), size, hex(uc.reg_read(UC_X86_REG_EIP)))
        return False

    # ------------------------------------------------------------------ helpers
    def rd32(self, a):
        return struct.unpack('<I', self.uc.mem_read(a, 4))[0]

    def rd16(self, a):
        return struct.unpack('<H', self.uc.mem_read(a, 2))[0]

    def rd8(self, a):
        return self.uc.mem_read(a, 1)[0]

    def wr32(self, a, v):
        self.uc.mem_write(a, struct.pack('<I', v & 0xFFFFFFFF))

    def cstr(self, a, maxlen=260):
        out = bytearray()
        while len(out) < maxlen:
            c = self.uc.mem_read(a + len(out), 1)[0]
            if not c:
                break
            out.append(c)
        return out.decode('latin1')

    def arg(self, i):
        return self.rd32(self.uc.reg_read(UC_X86_REG_ESP) + 4 + 4 * i)

    def _norm(self, path):
        p = path.upper().replace('/', '\\').strip('"')
        if len(p) >= 2 and p[1] == ':':
            return p
        if p.startswith('\\'):
            return self.cwd[:2] + p
        while p.startswith('.\\'):
            p = p[2:]
        return self.cwd + p

    def _new_handle(self, obj):
        h = self.next_handle
        self.next_handle += 4
        self.handles[h] = obj
        return h

    # ------------------------------------------------------------------ API
    def _api_hook(self, uc, address, size, user):
        entry = self.stubs.get(address)
        if entry is None:
            return
        name, _nbytes = entry
        fn = getattr(self, 'api_' + name, None)
        if fn is None:
            raise RuntimeError('unimplemented API %s' % name)
        args = [self.arg(i) for i in range(4)] if self.trace_api else None
        ret = fn()
        if self.trace_api:
            self.api_log.append((name, args, ret))
        if ret is not None:
            uc.reg_write(UC_X86_REG_EAX, ret & 0xFFFFFFFF)

    def api_GetVersion(self):
        return 0x80000A03

    def api_GetCommandLineA(self):
        return self.cmd_addr

    def api_GetEnvironmentStrings(self):
        return self.env_addr

    def api_GetStartupInfoA(self):
        # The DOSX32-era STARTUPINFO is 0x30 bytes (the CRT reserves exactly that).
        self.uc.mem_write(self.arg(0), struct.pack('<I', 0x30) + b'\0' * 0x2C)
        return None

    def api_GetModuleFileNameA(self):
        buf, n = self.arg(1), self.arg(2)
        s = (self.module_dir + self.exe_name).encode() + b'\0'
        s = s[:n]
        self.uc.mem_write(buf, s)
        return len(s) - 1

    def api_GetStdHandle(self):
        n = self.arg(0)
        return n if n in self.STD else 0xFFFFFFFF

    def api_SetStdHandle(self):
        return 1

    def api_GetFileType(self):
        return 2 if self.arg(0) in self.STD else 1

    def api_SetConsoleCtrlHandler(self):
        return 1

    def api_GetLastError(self):
        return self.last_error

    def api_GetSystemTime(self):
        self.uc.mem_write(self.arg(0), struct.pack('<8H', 1992, 3, 0, 1, 12, 0, 0, 0))
        return None

    def api_VirtualAlloc(self):
        addr, size, _typ, _prot = (self.arg(i) for i in range(4))
        size = (size + PAGE - 1) & ~(PAGE - 1)
        if addr:
            base = addr & ~(PAGE - 1)
            for rb, rs in self.va_regions.items():
                if rb <= base < rb + rs:
                    return base
            self.last_error = 487
            return 0
        base = self.va_next
        if base + size > VA_LIMIT:
            self.last_error = 8
            return 0
        self._map(base, size)
        self.va_regions[base] = size
        self.va_next = (base + size + 0xFFFF) & ~0xFFFF
        return base

    def api_VirtualFree(self):
        return 1

    def api_ExitProcess(self):
        self.exit_code = self.arg(0)
        self.uc.emu_stop()
        return None

    def api_RtlUnwind(self):
        return None

    def api_CreateFileA(self):
        name = self._norm(self.cstr(self.arg(0)))
        access, disp = self.arg(1), self.arg(4)
        exists = name in self.files
        if disp in (3, 5) and not exists:
            self.last_error = 2
            return 0xFFFFFFFF
        if disp == 1 and exists:
            self.last_error = 80
            return 0xFFFFFFFF
        if disp in (1, 2, 5) or not exists:
            self.files[name] = b''
        f = VFile(name, self.files[name], writable=bool(access & 0x40000000))
        return self._new_handle(f)

    def _flush(self, f):
        if isinstance(f, VFile) and f.writable:
            self.files[f.name] = bytes(f.data)

    def api_ReadFile(self):
        h, buf, n, pread = (self.arg(i) for i in range(4))
        f = self.handles.get(h)
        if f is None:
            if pread:
                self.wr32(pread, 0)
            return 1 if h in self.STD else 0
        chunk = bytes(f.data[f.pos:f.pos + n])
        f.pos += len(chunk)
        if chunk:
            self.uc.mem_write(buf, chunk)
        if pread:
            self.wr32(pread, len(chunk))
        return 1

    def api_WriteFile(self):
        h, buf, n, pw = (self.arg(i) for i in range(4))
        data = bytes(self.uc.mem_read(buf, n)) if n else b''
        if h == 0xFFFFFFF5:
            self.stdout += data
        elif h == 0xFFFFFFF4:
            self.stderr += data
        else:
            f = self.handles.get(h)
            if f is None:
                return 0
            end = f.pos + n
            if end > len(f.data):
                f.data.extend(b'\0' * (end - len(f.data)))
            f.data[f.pos:end] = data
            f.pos = end
        if pw:
            self.wr32(pw, n)
        return 1

    def api_SetFilePointer(self):
        h, dist, phigh, method = (self.arg(i) for i in range(4))
        f = self.handles.get(h)
        if f is None:
            return 0xFFFFFFFF
        if dist & 0x80000000:
            dist -= 1 << 32
        base = {0: 0, 1: f.pos, 2: len(f.data)}[method]
        f.pos = base + dist
        if phigh:
            self.wr32(phigh, 0)
        return f.pos

    def api_SetEndOfFile(self):
        f = self.handles.get(self.arg(0))
        if f is None:
            return 0
        del f.data[f.pos:]
        return 1

    def api_FlushFileBuffers(self):
        return 1

    def api_CloseHandle(self):
        f = self.handles.pop(self.arg(0), None)
        if f is not None:
            self._flush(f)
        return 1

    def api_GetFileAttributesA(self):
        name = self._norm(self.cstr(self.arg(0)))
        if name in self.files:
            return 0x20
        self.last_error = 2
        return 0xFFFFFFFF

    def api_DeleteFileA(self):
        name = self._norm(self.cstr(self.arg(0)))
        if name in self.files:
            del self.files[name]
            return 1
        self.last_error = 2
        return 0

    # ------------------------------------------------------------------ run
    def add_code_hook(self, addr, fn):
        """Call fn(emu) whenever execution reaches addr."""
        return self.uc.hook_add(UC_HOOK_CODE, lambda uc, a, s, u: fn(self), begin=addr, end=addr)

    def run(self):
        start = self.img.base + self.img.entry_rva
        try:
            self.uc.emu_start(start, self.trap, count=self.insn_limit)
        except UcError as e:
            if self.exit_code is None:
                eip = self.uc.reg_read(UC_X86_REG_EIP)
                raise RuntimeError('emulation error %s at eip=%#x fault=%r' % (e, eip, self.fault))
        if self.exit_code is None:
            self.exit_code = self.uc.reg_read(UC_X86_REG_EAX)
        for f in list(self.handles.values()):
            self._flush(f)
        return self.exit_code


# ---------------------------------------------------------------------- CL pipeline
IL_PREFIX = 'W:' + chr(92) + '185436'
C1_DEFINES = ('-D_M_I86 -D_MSDOS -D_M_I286 -D_M_I86LM -DM_I86 -DMSDOS -DM_I286 -DM_I86LM '
              '-D_MSC_VER=700')


class CLFlags:
    """Translate the project's CL flag lists (/AL /G2 /Gs /O... [/GA] /NTseg) to pass flags.

    Mirrors what CL 7.00 put into MSC_CMD_FLAGS for every catalogued profile
    (captured under DOSBox, build/workers/f-alloc-emu/capflags/flags.json).
    Only the flag vocabulary used by layout/compiler-profiles.json is accepted.
    """

    def __init__(self, flags):
        self.opt = ''
        self.ga = False
        self.nt = '_TEXT'
        for f in flags:
            u = f.upper()
            if u in ('/AL', '/G2', '/GS'):
                continue
            if u == '/GA':
                self.ga = True
            elif u.startswith('/NT'):
                self.nt = f[3:]
            elif u.startswith('/O'):
                self.opt = f[2:]
            else:
                raise ValueError('unsupported CL flag for emulation: %s' % f)
        letters = set(self.opt)
        if not letters <= set('egilw') or not {'e', 'l', 'w'} <= letters:
            raise ValueError('unsupported /O letters: %s' % self.opt)
        self.g = 'g' in letters
        self.i = 'i' in letters

    def c1(self, stem='input', obj='OUTPUT.OBJ'):
        b = chr(92)
        o = '-Ob 1 -Oc -Oe' + (' -Og' if self.g else '') + (' -Oi' if self.i else '') + ' -Ol -On -Oo -Ot -Ow'
        ga = ' -GA' if self.ga else ''
        win = ' -D_WINDOWS' if self.ga else ''
        return ('-ef "T:%sBIN%sc1.err" -il "%s" -f "%s.c" -pc %s:/ -Q 24242 -A lfd %s -Ze -G2%s -Gs -W 1 '
                '-c "%s" %s%s -I"./" ' % (b, b, IL_PREFIX, stem.lower(), b, o, ga, obj, C1_DEFINES, win))

    def c2(self):
        b = chr(92)
        o = '-Oc -Oe' + (' -Og' if self.g else '') + ' -Ol -On -Ot -Ow'
        ga = ' -GA' if self.ga else ''
        return ('-ef "T:%sBIN%sc23.err" -il "%s" -A lfd -Bm 2048 %s -G2%s -NT "%s" -W 1 '
                % (b, b, IL_PREFIX, o, ga, self.nt))

    def c3(self, stem='input', obj='OUTPUT.OBJ'):
        b = chr(92)
        ga = ' -GA' if self.ga else ''
        return ('-T 0 -ef "T:%sBIN%sc23.err" -il "%s" -lib "OLDNAMES.LIB" -A lfd -Ot%s -NM "%s" -NT "%s" -W 1 '
                '-dos -FPi -c "%s" -CC 2LO -v "7.00" ' % (b, b, IL_PREFIX, ga, stem.lower(), self.nt, obj))


BASE_ENV = (('NO87', ''), ('PATH', 'T:' + chr(92) + 'BIN;C:' + chr(92) + 'WINDOWS'))
IL_C1 = ('EX', 'GL', 'IN', 'ST', 'SY')
IL_C2 = ('GS', 'LS', 'PR')


def run_pass(exe, flags, files, **kw):
    env = {'MSC_CMD_FLAGS': flags}
    env.update(BASE_ENV)
    emu = PassEmulator(exe, env=env, files=files, **kw)
    return emu, emu.run()


def error_files():
    b = chr(92)
    return {'T:%sBIN%sC1.ERR' % (b, b): (BIN / 'C1.ERR').read_bytes(),
            'T:%sBIN%sC23.ERR' % (b, b): (BIN / 'C23.ERR').read_bytes()}


class CompileResult:
    def __init__(self):
        self.rc = {}
        self.il = {}
        self.obj = None
        self.messages = ''


def compile_c(source: bytes, flags, *, stem='INPUT', obj='OUTPUT.OBJ', c2_hooks=None, c2_extra=''):
    """Emulate CL /c for one source: C13216 -> C23216 -> C33216. Returns CompileResult.

    `c2_hooks(emu)` may install instrumentation on the C2 emulator before it runs.
    """
    cl = CLFlags(flags)
    b = chr(92)
    res = CompileResult()
    files = error_files()
    files['W:%s%s.C' % (b, stem.upper())] = source
    e1, rc1 = run_pass('C13216.EXE', cl.c1(stem, obj), files)
    res.rc['c1'] = rc1
    res.messages += (e1.stdout + e1.stderr).decode('latin1')
    if rc1:
        return res
    files = e1.files
    res.il.update({s: files.get(IL_PREFIX + s, b'') for s in IL_C1})
    env = {'MSC_CMD_FLAGS': (cl.c2() + c2_extra).rstrip() + ' '}
    env.update(BASE_ENV)
    e2 = PassEmulator('C23216.EXE', env=env, files=files)
    if c2_hooks:
        c2_hooks(e2)
    rc2 = e2.run()
    res.c2 = e2
    res.rc['c2'] = rc2
    res.messages += (e2.stdout + e2.stderr).decode('latin1')
    if rc2:
        return res
    files = e2.files
    res.il.update({s: files.get(IL_PREFIX + s, b'') for s in IL_C2})
    e3, rc3 = run_pass('C33216.EXE', cl.c3(stem, obj), files)
    res.rc['c3'] = rc3
    res.messages += (e3.stdout + e3.stderr).decode('latin1')
    res.obj = e3.files.get('W:%s%s' % (b, obj.upper()))
    return res


def main(argv=None):  # pragma: no cover - thin CLI
    """python tools/c2_emu.py SOURCE.c [CL flags...] [--symbol SYM] [-o OUT.OBJ]

    Diagnostic compile through the emulated passes (not admission evidence).
    """
    import argparse
    import hashlib
    ap = argparse.ArgumentParser(description=main.__doc__)
    ap.add_argument('source')
    ap.add_argument('flags', nargs='*')
    ap.add_argument('--symbol', help="use this symbol's assigned profile")
    ap.add_argument('-o', '--output')
    a = ap.parse_args(argv)
    flags = a.flags
    if a.symbol:
        from promote import function_flags
        flags = function_flags(a.symbol)[1]
    flags = flags or ['/AL', '/G2', '/Gs', '/Oelw', '/NT_TEXT']
    r = compile_c(Path(a.source).read_bytes(), flags)
    if r.messages:
        print(r.messages.rstrip())
    print('passes', r.rc, 'flags', ' '.join(flags))
    if r.obj:
        print('object', len(r.obj), 'bytes sha256', hashlib.sha256(r.obj).hexdigest())
        if a.output:
            Path(a.output).write_bytes(r.obj)
    return 0 if r.obj else 1


if __name__ == '__main__':  # pragma: no cover
    raise SystemExit(main())

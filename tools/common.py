"""Small, strict binary/evidence primitives; standard library only."""
import hashlib
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

class FormatError(ValueError):
    pass

class Reader:
    def __init__(self, data, pos=0):
        self.data, self.pos = data, pos

    def take(self, n):
        if n < 0 or self.pos < 0 or self.pos + n > len(self.data):
            raise FormatError(f"truncated range at {self.pos:#x}, length {n}")
        b = self.data[self.pos:self.pos+n]
        self.pos += n
        return b

    def unpack(self, fmt):
        return struct.unpack('<'+fmt, self.take(struct.calcsize('<'+fmt)))

    def u8(self): return self.unpack('B')[0]
    def u16(self): return self.unpack('H')[0]
    def u32(self): return self.unpack('I')[0]
    def name(self): return self.take(self.u8()).decode('latin1')
    def index(self):
        b = self.u8()
        return ((b & 127) << 8 | self.u8()) if b & 128 else b

def sha256(data): return hashlib.sha256(data).hexdigest()
def identity(path):
    b = Path(path).read_bytes()
    return {'size': len(b), 'sha256': sha256(b)}
def write_json(path, value):
    # Atomic replace so concurrent readers never see a partial file; Windows
    # may briefly refuse the replace while another process reads the target.
    import os, time
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + '.%d.tmp' % os.getpid())
    temporary.write_text(json.dumps(value, indent=2, ensure_ascii=True)+'\n', encoding='utf-8')
    deadline = time.monotonic() + 5
    while True:
        try:
            temporary.replace(path)
            return
        except PermissionError:
            if time.monotonic() >= deadline:
                raise
            time.sleep(0.01)
def read_json(path):
    import time
    deadline = time.monotonic() + 5
    while True:
        try:
            return json.loads(Path(path).read_text(encoding='utf-8'))
        except PermissionError:
            if time.monotonic() >= deadline:
                raise
            time.sleep(0.01)
def fixture(name):
    expected = read_json(ROOT/'layout/fixtures.json')['files'][name]
    b = (ROOT/'assets'/name).read_bytes()
    if len(b) != expected['size'] or sha256(b) != expected['sha256']:
        raise FormatError(f'fixture identity mismatch: {name}')
    return b

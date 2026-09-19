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
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2, ensure_ascii=True)+'\n', encoding='utf-8')
def read_json(path): return json.loads(Path(path).read_text(encoding='utf-8'))
def fixture(name):
    expected = read_json(ROOT/'layout/fixtures.json')['files'][name]
    b = (ROOT/'assets'/name).read_bytes()
    if len(b) != expected['size'] or sha256(b) != expected['sha256']:
        raise FormatError(f'fixture identity mismatch: {name}')
    return b

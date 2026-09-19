"""Verify the bounded game FP discriminator and independent LINK experiment.

This is an instruction-window fingerprint, NOT a complete function match.
Compiler inputs are synthetic and do not contain original executable bytes.
"""
from common import ROOT, read_json, write_json, fixture, identity, FormatError
from compiler import validate_receipt
import ne, mapsym


def check_fidr(raw, image, segment, offset, instruction):
    ss = image['segments'][segment-1]
    actual = raw[ss['file_offset']+offset:ss['file_offset']+offset+len(instruction)]
    sites = [r for r in ss['relocations'] if offset in r['sites']]
    return actual == instruction and len(sites) == 1 and all((
        sites[0]['source_type'] == 5, sites[0]['width'] == 2,
        sites[0]['flags'] == 7, sites[0]['additive'],
        sites[0]['target'] == {'kind': 'os_fixup', 'type': 5, 'reserved': 0}))


def main():
    base = ROOT/'evidence/experiments/toolchain'
    contrasts = read_json(base/'fp-mode-contrast.json')
    for row in contrasts['results']:
        validate_receipt(row['receipt'])
        if row['receipt']['unsupported_option']:
            raise FormatError('unsupported FP option is not a contrast')
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw)
    symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    owner = next(p for p in symbols['segments'][0]['symbols'] if p['name']=='_AdjustWndMinMax')
    observations = []
    for offset, ins in [(0x1b35, bytes.fromhex('9bdb46dc')), (0x1b39, bytes.fromhex('9bdd56d4'))]:
        if not check_fidr(raw, image, 1, offset, ins):
            raise FormatError('game floating-point fingerprint changed')
        observations.append({'segment':1, 'offset':offset, 'bytes':ins.hex(), 'ne_os_fixup_type':5})
    calls = []
    for offset, target, name in [(0x1b3d,0xac6,'__aFCIsqrt'),(0x1b42,0xacc,'__aFftol')]:
        start = image['segments'][0]['file_offset']+offset
        assert raw[start] == 0x9a and int.from_bytes(raw[start+1:start+3],'little') == target
        rel = next(r for r in image['segments'][0]['relocations'] if offset+3 in r['sites'])
        assert rel['source_type']==2 and rel['target']=={'kind':'internal','segment':4,'offset':0}
        assert any(p['name']==name and p['offset']==target for p in symbols['segments'][3]['symbols'])
        calls.append({'offset':offset,'target_segment':4,'target_offset':target,'symbol':name})
    receipt = read_json(base/'fp-link/receipt.json')
    validate_receipt(receipt['compile_receipt']); validate_receipt(receipt['stub_receipt'])
    linked = ROOT/'build/FPLINK/PROBE.EXE'
    assert identity(linked)==receipt['output'] and receipt['exit_code']==0
    linked_raw=linked.read_bytes(); linked_ne=ne.parse(linked_raw)
    # Retain and verify the original link inputs as well as its output.
    for name, expected in receipt['inputs'].items():
        if identity(ROOT/'build/FPLINK'/name)!=expected:
            raise FormatError('changed FP link input: '+name)
    if identity(ROOT/'toolchain/msc700/BIN/LINK.EXE')!=receipt['linker']:
        raise FormatError('changed calibration linker')
    calibration=read_json(base/'fp-link/fixup-calibration.json')
    kinds={'FIDRQQ':5,'FIERQQ':4,'FIWRQQ':6,'FICRQQ':3,'FJCRQQ':3}
    for row in calibration:
        offset=row['offset']; segment=linked_ne['segments'][row['segment']-1]
        actual=linked_raw[segment['file_offset']+offset:segment['file_offset']+offset+2].hex()
        if actual!=row['object_bytes'] or actual!=row['linked_bytes']:
            raise FormatError('FP calibration changed instruction bytes')
        site=offset-1 if row['symbol']=='FJCRQQ' else offset
        rel=[r for r in segment['relocations'] if site in r['sites']]
        if len(rel)!=1 or rel[0]['flags']!=7 or rel[0]['source_type']!=5 or rel[0]['target']!={'kind':'os_fixup','type':kinds[row['symbol']],'reserved':0}:
            raise FormatError('FP calibration changed loader obligation')
    # The first contribution is the independently compiled synthetic probe.
    candidate=next(r for r in contrasts['results'] if r.get('intrinsics') and r['mode']=='/FPi')
    code=bytes.fromhex(candidate['omf']['segments'][0]['data_hex'])
    f=next(f for f in candidate['omf']['fixups'] if f['target'].get('name')=='FIDRQQ')
    assert f['offset']==20 and f['frame_method']==5 and f['displacement']==0
    assert check_fidr(linked_raw,linked_ne,1,20,code[20:24])
    result={'scope':'Instruction window inside nineteenth selected game function; no whole-function match claimed',
        'exe_sha256':image['sha256'],'function':dict(owner,segment=1),
        'observations':observations,'calls':calls,
        'link_calibration':'C7 FIDRQQ at offset 20 becomes LINK5.30 additive NE OS fixup type5; all four instruction bytes unchanged',
        'status':'STRONGLY SUPPORTED','conclusion':'Inline emulator-compatible FP (/FPi or equivalent local control) in this game function; intrinsic sqrt entry point used',
        'ruled_out_scope':'Tested /FPi87 and /FPa alone do not produce this FP window and loader obligations. Not a global exclusion for other objects or explicit assembly.',
        'unresolved':['Exact command-line spelling versus pragmas','FP mode of other translation units','Reason for original FST temporary','Whole _AdjustWndMinMax source and contribution'],
        'intrinsic_scope':'/Oi or a function-specific intrinsic declaration is consistent; a uniform /Oi setting is not established',
        'source_reference':'https://www.pcjs.org/documents/books/mspl13/c/cadvprg/'}
    write_json(base/'fp-game-fingerprint.json',result)
    print(result['status']+': '+result['conclusion'])


if __name__=='__main__':main()

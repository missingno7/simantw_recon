"""Fresh LINK 5.30 proof for the complete file regions it can reproduce.

The partial image is structural scaffolding. Only five complete parser-derived
container regions are admitted; segment data and all remaining LINK bytes stay
debt.
"""
import json
import os
import re
import shutil
import subprocess
import tempfile
from collections import defaultdict
from pathlib import Path

from common import ROOT, FormatError, fixture, identity, read_json, sha256
import assembler
import compiler
import ne
import omf


ORACLE = 'SIMANTW.EXE'
DEF_SOURCE = 'src/link/SIMANTW.DEF'
STUB_SOURCE = 'src/link/SEGSTUB.ASM'
LINKER = 'toolchain/msc700/BIN/LINK.EXE'
WINSTUB = 'toolchain/sdk300/WINSTUB/WINSTUB.EXE'
WINSTUB_PIN = {'size': 610,
               'sha256': '7fb9c1c6a87ae28d4db1b7abb8b51a651221986cdb3de59cb3e153c3425e847a'}
LIBRARIES = {
    'CRT.LIB': 'toolchain/sdk300/CLIB/LLIBCW.LIB',
    'FP.LIB': 'toolchain/sdk300/CLIB/LLIBFPW.LIB',
    'HELPER.LIB': 'toolchain/sdk300/CLIB/LIBH.LIB',
    'WIN.LIB': 'toolchain/sdk300/WLIB/LIBW.LIB',
}
CLAIMED_REGION_KINDS = (
    'DOS_HEADER_AND_STUB',
    'RESIDENT_NAMES',
    'NONRESIDENT_NAMES',
    'IMPORTED_NAMES',
    'MODULE_REFERENCES',
)
LINK_ADMISSION_ROOT = ROOT / 'build/link/admissions'
STRUCTURAL_ROOT = ROOT / 'build/workers/w32-link/PARTLINK'
STRUCTURAL_RECEIPT = 'build/workers/w32-link/PARTLINK/receipt.json'
STRUCTURAL_RESPONSE = 'build/workers/w32-link/PARTLINK/PARTSTUB.RSP'
SCOPE = 'LINK 5.30 complete regions only; no segment, NE header/table field, relocation, chain, resource, or padding credit'


def _repo_file(value, label):
    path = Path(value)
    if not path.is_absolute():
        path = ROOT / path
    path = path.resolve()
    try:
        path.relative_to(ROOT.resolve())
    except ValueError as exc:
        raise FormatError(label + ' must stay inside the repository') from exc
    if not path.is_file():
        raise FormatError(label + ' is missing: ' + str(path))
    return path


def _repo_artifact(value, label):
    path = _repo_file(value, label)
    try:
        path.relative_to((ROOT / 'build/link').resolve())
    except ValueError as exc:
        raise FormatError(label + ' must be stored under build/link') from exc
    return path


def _json_digest(value):
    return sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode('utf-8'))


def source_identity():
    """Tracked LINK recipes plus the preserved structural input receipt and sources."""
    fixed = [DEF_SOURCE, STUB_SOURCE, STRUCTURAL_RECEIPT, STRUCTURAL_RESPONSE,
             'layout/toolchain.json', 'tools/link_lane.py', 'tools/ne.py',
             'tools/omf.py', 'tools/assembler.py', 'tools/compiler.py', 'tools/common.py']
    files = {name: identity(_repo_file(name, 'LINK source')) for name in fixed}
    receipt = read_json(ROOT / STRUCTURAL_RECEIPT)
    objects = _structural_object_names(receipt)
    object_rows = {}
    for name in objects:
        expected = receipt.get('inputs', {}).get(name)
        if not expected:
            raise FormatError('structural LINK receipt omits input identity: ' + name)
        actual = identity(_repo_file((STRUCTURAL_ROOT / name).relative_to(ROOT), 'structural LINK object'))
        if actual != expected:
            raise FormatError('structural LINK object identity changed: ' + name)
        object_rows[name] = actual
    source_rows = {}
    for row in receipt.get('stub_receipts', []):
        name = Path(row['source']).name
        source_path = STRUCTURAL_ROOT / name
        actual = identity(_repo_file(source_path.relative_to(ROOT), 'structural LINK C source'))
        if actual != row.get('source_identity'):
            raise FormatError('structural LINK C source identity changed: ' + name)
        source_rows[name] = actual
    files['structural_sources'] = {'count': len(source_rows), 'sha256': _json_digest(source_rows)}
    files['structural_objects'] = {'count': len(object_rows), 'sha256': _json_digest(object_rows)}
    return files


def _structural_object_names(receipt):
    """Read the preserved worker order while accepting only receipt-backed objects."""
    response = _repo_file(STRUCTURAL_RESPONSE, 'structural LINK response file')
    names = []
    for line in response.read_text(encoding='ascii').splitlines():
        match = re.fullmatch(r'\s*([RS]\d{4}\.OBJ)[+,]?\s*', line, re.I)
        if match:
            name = match.group(1).upper()
            if name in names:
                raise FormatError('duplicate object in structural LINK response: ' + name)
            names.append(name)
    if not names or not any(name.startswith('R') for name in names) or sum(name.startswith('S') for name in names) != 10:
        raise FormatError('structural LINK response has unexpected input set')
    if any(name not in receipt.get('inputs', {}) for name in names):
        raise FormatError('structural LINK response names an unreceipted object')
    return names


def require_source_identity(expected, current=None):
    if not isinstance(expected, dict) or (current or source_identity()) != expected:
        raise FormatError('LINK source identity changed since admission')


def toolchain_identity():
    """Current pinned tools and libraries used to regenerate the LINK input."""
    lock_path = ROOT / 'layout/toolchain.json'
    lock = read_json(lock_path)
    selected = [lock['runner'], LINKER, 'toolchain/masm/masm500/MASM.EXE',
                'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe', WINSTUB,
                *LIBRARIES.values()]
    # MSC 7.00 runs through the Win3.x host and its compiler directory. Keep all
    # those pinned identities, plus the DOSBox-X runner, in the receipt.
    selected.extend(path for path in lock['files']
                    if path.startswith('toolchain/msc700/BIN/') or
                    path.startswith('toolchain/win31/'))
    selected = sorted(set(selected))
    actual = {}
    for name in selected:
        path = _repo_file(name, 'LINK toolchain input')
        ident = identity(path)
        expected = lock['files'].get(name)
        if expected is not None and ident != expected:
            raise FormatError('LINK toolchain identity mismatch: ' + name)
        actual[name] = ident
    if actual[WINSTUB] != WINSTUB_PIN:
        raise FormatError('pinned WINSTUB identity mismatch')
    return {'toolchain_lock': identity(lock_path), 'files': actual,
            'winstub_pin': WINSTUB_PIN}


def require_toolchain_identity(expected, current=None):
    if not isinstance(expected, dict) or (current or toolchain_identity()) != expected:
        raise FormatError('LINK toolchain identity changed since admission')


def _region(image, kind):
    rows = [row for row in image['file_regions'] if row['kind'] == kind]
    if len(rows) != 1:
        raise FormatError('LINK input must contain exactly one %s region' % kind)
    row = rows[0]
    if not isinstance(row.get('start'), int) or not isinstance(row.get('end'), int) or row['end'] <= row['start']:
        raise FormatError('LINK %s region has invalid parser boundaries' % kind)
    return row


def _range(row):
    return {'start': row['start'], 'end': row['end'], 'size': row['end'] - row['start']}


def prove_regions(oracle_raw, candidate_raw):
    """Return the only complete parser-derived ranges this lane can credit."""
    oracle = ne.parse(oracle_raw)
    candidate = ne.parse(candidate_raw)
    claims = []
    for kind in CLAIMED_REGION_KINDS:
        oracle_region = _region(oracle, kind)
        candidate_region = _region(candidate, kind)
        oracle_range, candidate_range = _range(oracle_region), _range(candidate_region)
        if oracle_range['size'] != candidate_range['size']:
            raise FormatError('fresh LINK %s region has a different size' % kind)
        expected = oracle_raw[oracle_range['start']:oracle_range['end']]
        actual = candidate_raw[candidate_range['start']:candidate_range['end']]
        if actual != expected:
            raise FormatError('fresh LINK %s region differs from the oracle' % kind)
        claims.append({'kind': kind, 'oracle_range': oracle_range,
                       'output_range': candidate_range, 'sha256': sha256(actual)})
    return claims


def validate_claims(proof, oracle_raw, candidate_raw):
    """Reparse both files; reject malformed, extra, shifted, or unequal claims."""
    if proof.get('scope') != SCOPE:
        raise FormatError('LINK proof scope is malformed')
    claims = proof.get('regions')
    if not isinstance(claims, list) or [row.get('kind') for row in claims] != list(CLAIMED_REGION_KINDS):
        raise FormatError('LINK proof claims a region outside the proven set')
    oracle, candidate = ne.parse(oracle_raw), ne.parse(candidate_raw)
    for row, kind in zip(claims, CLAIMED_REGION_KINDS):
        oracle_range = _range(_region(oracle, kind))
        output_range = _range(_region(candidate, kind))
        if row.get('oracle_range') != oracle_range or row.get('output_range') != output_range:
            raise FormatError('LINK %s range differs from parsed file regions' % kind)
        actual = candidate_raw[output_range['start']:output_range['end']]
        expected = oracle_raw[oracle_range['start']:oracle_range['end']]
        if (len(actual) != output_range['size'] or actual != expected or
                sha256(actual) != row.get('sha256')):
            raise FormatError('LINK %s bytes differ from the admitted oracle range' % kind)
    return claims


def _run_link(out):
    lock = read_json(ROOT / 'layout/toolchain.json')
    worker_receipt = read_json(ROOT / STRUCTURAL_RECEIPT)
    def_path = ROOT / DEF_SOURCE
    shutil.copyfile(def_path, out / 'SIMANTW.DEF')
    stub_obj, assembler_receipt = assembler.assemble_source(ROOT / STUB_SOURCE, 'masm500')
    shutil.copyfile(stub_obj, out / 'SEGSTUB.OBJ')
    structural = _structural_object_names(worker_receipt)
    input_identities = {}
    for name in structural:
        source = _repo_file((STRUCTURAL_ROOT / name).relative_to(ROOT), 'structural LINK object')
        expected = worker_receipt['inputs'].get(name)
        if identity(source) != expected:
            raise FormatError('structural LINK object identity changed: ' + name)
        shutil.copyfile(source, out / name)
        input_identities[name] = identity(out / name)
    objects = structural + ['SEGSTUB.OBJ']
    input_identities['SEGSTUB.OBJ'] = identity(out / 'SEGSTUB.OBJ')
    input_identities['SIMANTW.DEF'] = identity(out / 'SIMANTW.DEF')
    input_identities['SEGSTUB.ASM'] = identity(ROOT / STUB_SOURCE)
    for destination, source in LIBRARIES.items():
        expected = worker_receipt['inputs'].get(destination)
        pinned = _repo_file(source, 'pinned LINK library')
        if identity(pinned) != expected:
            raise FormatError('structural LINK library differs from its worker receipt: ' + source)
        shutil.copyfile(pinned, out / destination)
        input_identities[destination] = identity(out / destination)
    stub_source = _repo_file(WINSTUB, 'pinned WINSTUB')
    if identity(stub_source) != WINSTUB_PIN:
        raise FormatError('pinned WINSTUB identity mismatch')
    shutil.copyfile(stub_source, out / 'WINSTUB.EXE')
    input_identities['WINSTUB.EXE'] = identity(out / 'WINSTUB.EXE')
    response = ('+\n'.join(objects) + ',\nSIMANTW.EXE,\nSIMANTW.MAP,\n' +
                '+'.join(LIBRARIES) + ',\nSIMANTW.DEF /NOD /NOI /MAP /NOPACKCODE;\n')
    (out / 'SIMANTW.RSP').write_text(response, encoding='ascii', newline='\n')
    input_identities['SIMANTW.RSP'] = identity(out / 'SIMANTW.RSP')
    runner = _repo_file(lock['runner'], 'LINK DOS runner')
    linker = _repo_file(LINKER, 'LINK 5.30')
    command = [str(runner), '-d', str(linker), '@SIMANTW.RSP']
    try:
        result = subprocess.run(command, cwd=out, capture_output=True, timeout=300)
    except subprocess.TimeoutExpired as exc:
        raise FormatError('fresh LINK 5.30 run timed out') from exc
    log = (result.stdout + result.stderr).decode('latin1', errors='replace')
    (out / 'LINK.LOG').write_text(log, encoding='latin1')
    output = out / 'SIMANTW.EXE'
    if result.returncode != 0 or not output.is_file():
        raise FormatError('fresh LINK 5.30 run failed: ' + '\n'.join(log.splitlines()[-16:]))
    return output, {
        'command': command,
        'exit_code': result.returncode,
        'linker': identity(linker),
        'runner': identity(runner),
        'definition': identity(def_path),
        'stub_source': identity(ROOT / STUB_SOURCE),
        'stub_object': identity(out / 'SEGSTUB.OBJ'),
        'assembler': assembler_receipt,
        'worker_receipt': identity(ROOT / STRUCTURAL_RECEIPT),
        'worker_response': identity(ROOT / STRUCTURAL_RESPONSE),
        'structural_stub_receipts': worker_receipt.get('stub_receipts', []),
        'structural_stub_count': len(worker_receipt.get('stubs', [])),
        'object_count': len(objects),
        'input_identities': input_identities,
        'link_log_tail': '\n'.join(log.splitlines()[-20:]),
    }


def _copy_immutable(source, destination):
    destination.parent.mkdir(parents=True, exist_ok=True)
    if destination.exists():
        if identity(destination) != identity(source):
            raise FormatError('LINK admission artifact exists with different bytes: ' + str(destination))
    else:
        shutil.copyfile(source, destination)
        if identity(destination) != identity(source):
            raise FormatError('LINK admission artifact copy did not verify: ' + str(destination))


def compile_admission(work_root=None, store=True):
    """Regenerate the structural input and run the pinned LINK executable fresh."""
    sources = source_identity()
    tools = toolchain_identity()
    oracle_raw = fixture(ORACLE)
    oracle = ne.parse(oracle_raw)
    base = Path(work_root) if work_root is not None else ROOT / 'build/link/admission-runs'
    if not base.is_absolute():
        base = ROOT / base
    base = base.resolve()
    try:
        base.relative_to(ROOT.resolve())
    except ValueError as exc:
        raise FormatError('LINK admission work directory must stay inside the repository') from exc
    base.mkdir(parents=True, exist_ok=True)
    run_root = Path(tempfile.mkdtemp(prefix='fresh-', dir=base))
    candidate_path, run = _run_link(run_root)
    candidate_raw = candidate_path.read_bytes()
    candidate = ne.parse(candidate_raw)
    if candidate['resources']:
        raise FormatError('structural LINK input unexpectedly contains resources')
    if candidate['header']['segment_count'] != 10 or len(candidate['modules']) != 6:
        raise FormatError('fresh LINK output has unexpected segment or module geometry')
    regions = prove_regions(oracle_raw, candidate_raw)
    if len(regions) != 5:
        raise FormatError('LINK admission did not prove exactly five complete regions')
    output_ident = identity(candidate_path)
    token = _json_digest({'sources': sources, 'toolchain': tools, 'output': output_ident,
                           'regions': regions})
    admission_id = 'link-' + token[:16]
    artifact = LINK_ADMISSION_ROOT / admission_id / 'SIMANTW.EXE'
    if store:
        _copy_immutable(candidate_path, artifact)
        output_path = artifact
    else:
        output_path = candidate_path
    return {
        'id': admission_id,
        'scope': SCOPE,
        'sources': sources,
        'toolchain': tools,
        'output': {'path': output_path.relative_to(ROOT).as_posix(),
                   'identity': identity(output_path)},
        'regions': regions,
        'uncredited_region_kinds': sorted({row['kind'] for row in oracle['file_regions']} - set(CLAIMED_REGION_KINDS)),
        'fresh_run': run,
    }


def replay_admission(proof):
    """Freshly rerun LINK and require the admitted bytes, inputs, and claims."""
    require_source_identity(proof.get('sources'))
    require_toolchain_identity(proof.get('toolchain'))
    fresh = compile_admission(store=False)
    if fresh['id'] != proof.get('id'):
        raise FormatError('fresh LINK replay admission id differs')
    if fresh['output']['identity'] != proof.get('output', {}).get('identity'):
        raise FormatError('fresh LINK replay output identity differs')
    if fresh['regions'] != proof.get('regions'):
        raise FormatError('fresh LINK replay region proof differs')
    replay_path = _repo_file(fresh['output']['path'], 'fresh LINK output')
    artifact = _repo_artifact(proof.get('output', {}).get('path', ''), 'LINK admission output')
    _copy_immutable(replay_path, artifact)
    if identity(artifact) != proof['output']['identity']:
        raise FormatError('stored LINK replay artifact identity differs')
    return {'result': 'REPLAYED_EXACT', 'id': proof['id'],
            'output': proof['output']['identity'], 'regions': len(proof['regions'])}


def load_admission(record, require_artifacts=True):
    """Load the ledger-referenced proof and its immutable structural LINK output."""
    if not record:
        return None, None
    try:
        proof_path = _repo_file(record.get('promotion_evidence', ''), 'LINK promotion proof')
        if identity(proof_path) != record.get('proof_identity'):
            raise FormatError('LINK promotion proof identity differs from the recovery ledger')
        proof = read_json(proof_path)
        if proof.get('id') != record.get('id') or proof.get('scope') != SCOPE:
            raise FormatError('LINK promotion proof is malformed')
        if record.get('source_identity') != proof.get('sources') or record.get('toolchain_identity') != proof.get('toolchain'):
            raise FormatError('LINK recovery record disagrees with the promotion proof')
        require_source_identity(proof.get('sources'))
        require_toolchain_identity(proof.get('toolchain'))
        output_path = _repo_artifact(proof.get('output', {}).get('path', ''), 'LINK admission output')
        output = None
        if not output_path.is_file():
            if require_artifacts:
                raise FormatError('LINK admission output is missing: ' + str(output_path))
        else:
            if identity(output_path) != proof.get('output', {}).get('identity'):
                raise FormatError('LINK admission output identity changed since admission')
            output = output_path.read_bytes()
            oracle_raw = fixture(ORACLE)
            validate_claims(proof, oracle_raw, output)
        return proof, output
    except (FormatError, OSError, KeyError, TypeError, ValueError) as exc:
        return None, 'LINK admission invalid: ' + str(exc)

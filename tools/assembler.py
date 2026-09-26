"""Build an authentic Microsoft MASM OMF object from one readable .ASM source.

The MASM catalog is read from the accepted toolchain lock when integrated, or
from the assembler worker's review proposal while this lane is under review.
No downloaded archive is consulted during an assembly.
"""
import argparse
import os
import re
import shutil
import subprocess
import tempfile
import time
from datetime import datetime, timezone
from pathlib import Path

from common import ROOT, FormatError, identity, read_json, relative, sha256, write_json

PROPOSAL = ROOT / 'build/workers/masm/toolchain-lock-proposal.json'
DOSBOX = 'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'
WIN31 = 'toolchain/win31'

# These are ordinary assembler declarations which do not synthesize instruction
# bytes. Macro languages and opaque byte-producing forms are intentionally not
# admitted by the recovered-source lane.
DIRECTIVES = {
    'SEGMENT', 'ENDS', 'GROUP', 'ASSUME', 'PUBLIC', 'EXTRN', 'EXTERN',
    'EXTERNDEF', 'COMM', 'COMMON', 'PROC', 'ENDP', 'END', 'LABEL', 'EQU', 'LOCAL',
    'ORG', 'EVEN', 'ALIGN', 'PUSHCONTEXT', 'POPCONTEXT', 'ALIAS',
    'STRUCT', 'UNION', 'RECORD', 'TYPEDEF',
    'TITLE', 'SUBTITLE', 'PAGE', 'NAME', 'RADIX', 'OPTION', 'MODEL',
    'CODE', 'DATA', 'STACK', '186', '286', '286P', '386', '386P',
    '8086', '8087', '287', '387', 'FARDATA', 'FARDATA?', 'CONST', '=',
}
INSTRUCTIONS = set('''AAA AAD AAM AAS ADC ADD AND ARPL BOUND BSF BSR BSWAP BT BTC BTR BTS
CALL CBW CLC CLD CLI CLTS CMC CMP CMPS CMPSB CMPSW CMPXCHG CWD CWDE DAA DAS DEC DIV
ENTER HLT IDIV IMUL IN INC INS INSB INSW INT INTO INVD INVLPG IRET JAE JA JB JBE JCXZ
JE JG JGE JL JLE JMP JNA JNAE JNB JNBE JNC JNE JNG JNGE JNL JNLE JNO JNP JNS JNZ JO
JP JPE JPO JS JZ LAHF LDS LEA LEAVE LES LFS LGDT LGS LIDT LLDT LMSW LODS LODSB LODSW
LOOP LOOPE LOOPNE LOOPNZ LOOPZ LSL LSS LTR MOV MOVS MOVSB MOVSW MOVSX MOVZX MUL NEG
NOP NOT OR OUT OUTS OUTSB OUTSW POP POPA POPAD POPF POPFD PUSH PUSHA PUSHAD PUSHF
PUSHFD RCL RCR REP REPE REPNE REPNZ REPZ RET RETF ROL ROR SAHF SAL SAR SBB SCAS
SCASB SCASW SETA SETAE SETB SETBE SETC SETE SETG SETGE SETL SETLE SETNA SETNAE SETNB
SETNBE SETNC SETNE SETNG SETNGE SETNL SETNLE SETNO SETNP SETNS SETNZ SETO SETP SETPE
SETPO SETS SETZ SGDT SHL SHR SIDT SLDT SMSW STC STD STI STOS STOSB STOSW STR SUB TEST
VERR VERW WAIT WBINVD XADD XCHG XLAT XOR'''.split())
PSEUDO_LANGUAGE = re.compile(
    r'\b(?:MACRO|ENDM|INVOKE|INCBIN|INCLUDE|TEXTEQU|REPT|IRP|IRPC|WHILE|'
    r'EXITM|PURGE|ERR(?:NZ|DEF|NDEF|B)?|ERR1|ERR2|ERR3)\b', re.I)
DATA_DIRECTIVES = {'DB', 'DW', 'DD', 'DQ', 'DT', 'BYTE', 'WORD', 'DWORD', 'QWORD', 'TBYTE'}
DOTTED_DIRECTIVES = {'.CODE', '.DATA', '.DATA?', '.STACK', '.MODEL', '.186', '.286', '.286P',
                     '.386', '.386P', '.8086', '.8087', '.287', '.387', '.CONST', '.FARDATA', '.FARDATA?'}
LABEL_OPERAND = re.compile(r'(?:(?:OFFSET|SEG)\s+)?[A-Za-z_?$@.][A-Za-z0-9_?$@.]*\Z', re.I)
FLAG_RE = re.compile(r'/[A-Za-z0-9_:+.-]+\Z')
ABSOLUTE_MEMORY = re.compile(r'\b(?:DS|ES|CS|SS)\s*:\s*\[?\s*[0-9][0-9A-F]*H?\b|\[\s*[0-9][0-9A-F]*H?\s*\]', re.I)


def _strip_comment(line):
    quote = None
    i = 0
    while i < len(line):
        ch = line[i]
        if quote:
            if ch == quote:
                if i + 1 < len(line) and line[i + 1] == quote:
                    i += 1
                else:
                    quote = None
        elif ch in ('"', "'"):
            quote = ch
        elif ch == ';':
            return line[:i]
        i += 1
    return line


def _line_opcode(line):
    """Return the directive/mnemonic after a conventional optional label."""
    value = line.strip()
    if not value:
        return '', ''
    if ':' in value:
        before, after = value.split(':', 1)
        if re.fullmatch(r'[A-Za-z_?$@.][A-Za-z0-9_?$@.]*', before.strip()):
            value = after.strip()
    parts = value.split(None, 1)
    if not parts:
        return '', ''
    return parts[0].upper(), parts[1] if len(parts) > 1 else ''


def check_asm_source(source):
    """Fail closed on opaque bytes, includes, macros, and code-segment data.

    Word/dword tables in a code segment are accepted only when each element is
    a symbol or its OFFSET/SEG. Numeric literals and DB byte streams are not
    recoverable instruction source.
    """
    if isinstance(source, bytes):
        source = source.decode('latin1')
    if 'TODO' in source.upper():
        raise FormatError('unfinished assembly source')
    active_code = False
    seen_segment = False
    for number, original in enumerate(source.splitlines(), 1):
        line = _strip_comment(original).strip()
        if not line:
            continue
        if '/*' in line or '*/' in line:
            raise FormatError('MASM sources use ordinary semicolon comments, not embedded C comments')
        if PSEUDO_LANGUAGE.search(line):
            raise FormatError('assembly source contains a forbidden macro, include, or opaque byte directive (line %d)' % number)

        upper = line.upper()
        if re.match(r'^\.(?:CODE)\b', upper):
            active_code = True
            seen_segment = True
        elif re.match(r'^\.(?:DATA|STACK)\b', upper) or re.match(r'^\.DATA\?', upper):
            active_code = False
            seen_segment = True

        # MASM's named-segment syntax carries its class in the declaration.
        if re.search(r'\bSEGMENT\b', upper):
            seen_segment = True
            if re.search(r"(?:'|\")\s*(?:CODE|TEXT)\s*(?:'|\")", upper) or re.match(r'^(?:_?TEXT|CODE)\s+SEGMENT\b', upper):
                active_code = True
            elif re.search(r"(?:'|\")\s*(?:DATA|BSS|STACK|CONST)\s*(?:'|\")", upper):
                active_code = False
            else:
                # An unclassified segment is treated as code for this check.
                active_code = True
        if re.search(r'\bENDS\b', upper):
            active_code = False

        # Data declarations and ordinary directives often have a leading name
        # without a colon (``jump_table DW ...``, ``_f PROC FAR``).
        value = line
        leading, _ = _line_opcode(value)
        # Do not interpret instruction operands (for example, ``jmp word ptr
        # [bx]``) as an uncolonized label followed by a WORD declaration.
        if leading not in INSTRUCTIONS and leading not in DIRECTIVES and leading not in DATA_DIRECTIVES and leading not in DOTTED_DIRECTIVES:
            label = re.match(r'^([A-Za-z_?$@.][A-Za-z0-9_?$@.]*)\s+(.*)$', value)
            if label:
                rest = label.group(2).lstrip()
                following = rest.split(None, 1)[0].upper() if rest else ''
                if following in DATA_DIRECTIVES or following in DIRECTIVES or following in INSTRUCTIONS:
                    value = rest
        opcode, operands = _line_opcode(value)
        if opcode in DATA_DIRECTIVES and active_code:
            if opcode in ('DB', 'BYTE'):
                raise FormatError('byte data in a code segment is refused (line %d)' % number)
            entries = [part.strip() for part in operands.split(',')]
            if not entries or any(not LABEL_OPERAND.fullmatch(part) for part in entries):
                raise FormatError('code-segment data must be a label/offset jump table (line %d)' % number)
        # Explicitly reject data forms even when hidden behind a label token
        # (``name DB ...``), but not instruction operands such as ``mov BYTE PTR [bx], 0``.
        hidden = re.match(r'^([A-Za-z_?$@.][A-Za-z0-9_?$@.]*)\s+(?:DB|BYTE)\b', line, re.I)
        if active_code and hidden and hidden.group(1).upper() not in INSTRUCTIONS:
            raise FormatError('byte data in a code segment is refused (line %d)' % number)
        # Hard-coded linked addresses are the assembly form of a literal-address
        # cast: name the variable (EXTRN for a MAPSYM public, or this module's own
        # _DATA definition) so the object carries a real fixup.
        if opcode in INSTRUCTIONS and ABSOLUTE_MEMORY.search(operands):
            raise FormatError('absolute memory operand %r: reference a named variable instead (line %d)'
                              % (ABSOLUTE_MEMORY.search(operands).group(0), number))

        # This is a source-subset gate, not a complete MASM parser. Unknown
        # opcodes still go through the selected period assembler and OMF parser.
        if opcode in ('MACRO', 'ENDM', 'INVOKE', 'INCBIN', 'INCLUDE', 'TEXTEQU', 'REPT', 'IRP', 'IRPC', 'WHILE'):
            raise FormatError('non-instruction assembler language is refused (line %d)' % number)
        if opcode in ('COMMENT', 'NAME') and opcode == 'COMMENT':
            raise FormatError('assembler comment blocks are refused (line %d)' % number)
        normalized_opcode = opcode.lstrip('.')
        if normalized_opcode and normalized_opcode not in DIRECTIVES and normalized_opcode not in DATA_DIRECTIVES and \
                opcode not in INSTRUCTIONS and opcode not in DOTTED_DIRECTIVES:
            # Unknown tokens in instruction position can be undocumented
            # pseudo-ops; let only real instruction mnemonics or ordinary
            # directives reach the selected assembler.
            raise FormatError('unknown assembler directive or instruction %r (line %d)' % (opcode, number))
    if not seen_segment and not re.search(r'\bPROC\b', source, re.I):
        raise FormatError('assembly source has no code segment or procedure')
    return True


def _catalog():
    lock_path = ROOT / 'layout/toolchain.json'
    lock = read_json(lock_path)
    if lock.get('assemblers'):
        return lock, lock['assemblers'], lock.get('files', {}), lock_path
    if not PROPOSAL.exists():
        raise FormatError('no reviewed assembler entries in layout/toolchain.json or worker proposal')
    proposal = read_json(PROPOSAL)
    return lock, proposal.get('assemblers', {}), proposal.get('files', {}), PROPOSAL


def versions():
    _, catalog, _, _ = _catalog()
    return catalog


def _expected_identity(path, lock, proposal_files):
    return lock.get('files', {}).get(path) or proposal_files.get(path)


def _verify_path(path, expected, description):
    full = ROOT / path
    if not full.is_file():
        raise FormatError('missing %s: %s' % (description, path))
    actual = identity(full)
    if expected and actual != expected:
        raise FormatError('%s identity mismatch: %s' % (description, path))
    return actual


def _tree_identity(path):
    root = ROOT / path
    rows = []
    for item in sorted(p for p in root.rglob('*') if p.is_file()):
        ident = identity(item)
        rows.append((item.relative_to(root).as_posix(), ident['size'], ident['sha256']))
    payload = '\n'.join('%s\0%d\0%s' % row for row in rows).encode('utf-8')
    return {'files': len(rows), 'sha256': sha256(payload)}


def _runner_paths(runner, lock):
    if runner == 'msdos-player':
        return [lock['runner']]
    if runner == 'dosbox-x-win31':
        return [DOSBOX, WIN31]
    if runner == 'windows-native-x86':
        return []
    raise FormatError('unsupported MASM runner: ' + str(runner))


def _validate_flags(flags):
    if not isinstance(flags, (list, tuple)) or any(not isinstance(f, str) or not FLAG_RE.fullmatch(f) for f in flags):
        raise FormatError('unsafe assembler option')
    return list(flags)


def _command(version, spec, flags, work):
    driver = spec['driver']
    if driver == 'masm5':
        return ['MASM.EXE'] + flags + ['INPUT.ASM,OUTPUT.OBJ,NUL,NUL;']
    if driver in ('ml6', 'ml61', 'mlwin32'):
        return ['ML.EXE'] + flags + ['/c', '/FoOUTPUT.OBJ', 'INPUT.ASM']
    raise FormatError('unsupported MASM command driver for ' + version)


def _dosbox_assemble(spec, flags, work):
    host = work / 'HOST'
    shutil.copytree(ROOT / WIN31, host)
    batch = [
        '@echo off', 'set PATH=T:\\;C:\\WINDOWS', 'set TMP=W:\\', 'set TEMP=W:\\',
        'W:', 'T:\\ML.EXE ' + ' '.join(flags + ['/c', '/FoOUTPUT.OBJ', 'INPUT.ASM']) + ' > LOG.TXT',
        'if errorlevel 1 echo failed > W:\\FAIL.TXT', 'echo done > W:\\DONE.TXT', 'exit',
    ]
    (work / 'GO.BAT').write_text('\n'.join(batch) + '\n', encoding='ascii')
    conf = [
        '[sdl]', 'output=surface', 'showmenu=false', '[mixer]', 'nosound=true',
        '[dosbox]', 'memsize=128', 'machine=svga_s3', '[cpu]', 'core=normal',
        'cputype=486', 'cycles=200000', '[autoexec]',
        'mount c "%s"' % host, 'mount t "%s"' % (ROOT / spec['directory']),
        'mount w "%s" -nocachedir' % work, 'c:', 'set PATH=C:\\WINDOWS;T:\\',
        'C:\\WINDOWS\\WIN /3 W:\\GO.BAT', 'exit',
    ]
    conf_path = work / 'RUN.CONF'
    conf_path.write_text('\n'.join(conf) + '\n', encoding='ascii')
    runner = ROOT / DOSBOX
    command = [str(runner), '-conf', str(conf_path), '-fastlaunch', '-nogui', '-nomenu', '-noconsole']
    env = {k: v for k, v in os.environ.items() if k.upper() in ('SYSTEMROOT', 'WINDIR', 'COMSPEC')}
    env.update(SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy')
    started = time.perf_counter()
    process = subprocess.Popen(command, cwd=work, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    deadline = time.monotonic() + 75
    while time.monotonic() < deadline and process.poll() is None and not (work / 'DONE.TXT').exists():
        time.sleep(.02)
    if process.poll() is None:
        process.kill()
    process.wait()
    done = (work / 'DONE.TXT').exists()
    failed = (work / 'FAIL.TXT').exists() and (work / 'FAIL.TXT').stat().st_size > 0
    log = (work / 'LOG.TXT').read_bytes() if (work / 'LOG.TXT').exists() else b''
    receipt = dict(command=command, compile_command=' '.join(batch[5]), configuration=str(conf_path.relative_to(ROOT).as_posix()),
                   configuration_identity=identity(conf_path), host_tree_identity=_tree_identity(str(host.relative_to(ROOT))),
                   runner_startup_seconds=time.perf_counter() - started,
                   exit_code=0 if done and not failed else 1,
                   stdout=log.decode('latin1', 'replace'), stderr='')
    if not done:
        raise FormatError('DOSBox-X/Win3.1 MASM job did not complete')
    if failed:
        raise FormatError('DOSBox-X/Win3.1 MASM failed: ' + receipt['stdout'][-1500:])
    return receipt


def assemble_source(source, version, flags=None):
    """Assemble a source path to retained ``build/assembler/.../*.OBJ`` output."""
    lock, catalog, proposal_files, catalog_path = _catalog()
    if version not in catalog:
        raise FormatError('unknown or unprovisioned assembler version: ' + version)
    spec = catalog[version]
    source_path = Path(source).resolve()
    try:
        source_name = source_path.relative_to(ROOT).as_posix()
    except ValueError as exc:
        raise FormatError('assembly source must be inside the repository') from exc
    if not source_path.is_file():
        raise FormatError('assembly source does not exist: ' + source_name)
    source_bytes = source_path.read_bytes()
    check_asm_source(source_bytes)
    flags = _validate_flags(spec.get('default_flags', []) if flags is None else flags)
    if any(x.suffix.lower() != '.asm' for x in [source_path]):
        raise FormatError('MASM input must use the .asm suffix')

    tool_paths = [spec['executable']] + list(spec.get('support_files', []))
    tool_identities = {}
    for path in tool_paths:
        tool_identities[path] = _verify_path(path, _expected_identity(path, lock, proposal_files), 'assembler tool')
    runner_paths = _runner_paths(spec['runner'], lock)
    runner_identities = {}
    for path in runner_paths:
        if path == WIN31:
            runner_identities[path] = _tree_identity(path)
        else:
            runner_identities[path] = _verify_path(path, _expected_identity(path, lock, proposal_files), 'assembler runner')

    out_root = ROOT / 'build/assembler' / version
    out_root.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix='A', dir=out_root))
    (work / 'INPUT.ASM').write_bytes(source_bytes)
    for path in tool_paths:
        shutil.copyfile(ROOT / path, work / Path(path).name)

    run = None
    dos_command = _command(version, spec, flags, work)
    try:
        if spec['runner'] == 'msdos-player':
            command = [str(ROOT / lock['runner']), '-d', str(work / Path(spec['executable']).name)] + dos_command[1:]
            env = {k: v for k, v in os.environ.items() if k.upper() in ('SYSTEMROOT', 'WINDIR', 'COMSPEC')}
            started = time.perf_counter()
            result = subprocess.run(command, cwd=work, env=env, capture_output=True, timeout=60)
            run = dict(command=command, compile_command=' '.join(dos_command), exit_code=result.returncode,
                       stdout=result.stdout.decode('latin1', 'replace'), stderr=result.stderr.decode('latin1', 'replace'),
                       runner_seconds=time.perf_counter() - started)
        elif spec['runner'] == 'dosbox-x-win31':
            run = _dosbox_assemble(spec, flags, work)
        elif spec['runner'] == 'windows-native-x86':
            command = [str(work / Path(spec['executable']).name)] + flags + ['/c', '/FoOUTPUT.OBJ', 'INPUT.ASM']
            started = time.perf_counter()
            result = subprocess.run(command, cwd=work, capture_output=True, timeout=60)
            run = dict(command=command, compile_command=' '.join(command[1:]), exit_code=result.returncode,
                       stdout=result.stdout.decode('latin1', 'replace'), stderr=result.stderr.decode('latin1', 'replace'),
                       runner_seconds=time.perf_counter() - started)
        else:
            raise FormatError('unsupported MASM runner: ' + spec['runner'])

        obj = work / 'OUTPUT.OBJ'
        receipt = dict(source=source_name, source_identity=identity(source_path),
                       source_snapshot=relative(work / 'INPUT.ASM'), assembler=version,
                       assembler_version=spec['display_version'], flags=flags,
                       toolchain_lock_sha256=sha256((ROOT / 'layout/toolchain.json').read_bytes()),
                       assembler_catalog=catalog_path.relative_to(ROOT).as_posix(),
                       assembler_catalog_identity=identity(catalog_path), assembler_spec=spec, tool_identities=tool_identities,
                       runner=spec['runner'], runner_identities=runner_identities, **run,
                       object=obj.relative_to(ROOT).as_posix(), fixture_dependencies=[])
        if run['exit_code'] != 0 or not obj.is_file() or not obj.stat().st_size:
            write_json(work / 'receipt.json', receipt)
            raise FormatError('assembler failed: ' + receipt['stdout'][-1500:] + receipt['stderr'][-800:])
        # Validate OMF here so an executable that merely started never counts as
        # a successful assembler invocation.
        try:
            from omf import parse
            parse(obj.read_bytes())
        except (FormatError, ValueError) as exc:
            write_json(work / 'receipt.json', receipt)
            raise FormatError('assembler output is not valid OMF: ' + str(exc)) from exc
        receipt['object_identity'] = identity(obj)
        receipt['source_snapshot_identity'] = identity(work / 'INPUT.ASM')
        receipt['timing'] = dict(total_assemble_seconds=time.perf_counter() - started if 'started' in locals() else run.get('runner_startup_seconds'),
                                 runner=spec['runner'])
        write_json(work / 'receipt.json', receipt)
        return obj, receipt
    except subprocess.TimeoutExpired as exc:
        raise FormatError('assembler runner timed out') from exc


def validate_receipt(receipt):
    if receipt.get('exit_code') != 0 or receipt.get('unsupported_option'):
        raise FormatError('unsuccessful or unsupported assembler receipt')
    if identity(ROOT / receipt['source']) != receipt['source_identity']:
        raise FormatError('stale assembly source receipt')
    if identity(ROOT / receipt['source_snapshot']) != receipt.get('source_snapshot_identity'):
        raise FormatError('stale assembler input snapshot')
    if identity(ROOT / receipt['object']) != receipt['object_identity']:
        raise FormatError('stale assembler object receipt')
    lock, catalog, proposal_files, catalog_path = _catalog()
    version = receipt.get('assembler')
    if version not in catalog:
        raise FormatError('assembler version is no longer locked: ' + str(version))
    spec = catalog[version]
    for path, expected in receipt.get('tool_identities', {}).items():
        if _verify_path(path, _expected_identity(path, lock, proposal_files), 'assembler tool') != expected:
            raise FormatError('assembler tool differs from receipt: ' + path)
    for path, expected in receipt.get('runner_identities', {}).items():
        actual = _tree_identity(path) if path == WIN31 else _verify_path(path, _expected_identity(path, lock, proposal_files), 'assembler runner')
        if actual != expected:
            raise FormatError('assembler runner differs from receipt: ' + path)
    if receipt.get('runner') != spec['runner'] or receipt.get('assembler_version') != spec['display_version'] or receipt.get('assembler_spec') != spec:
        raise FormatError('assembler recipe differs from the current catalog')
    catalog_digest = receipt.get('assembler_catalog_identity')
    catalog_file = ROOT / receipt.get('assembler_catalog', '')
    if catalog_digest and catalog_file.exists() and identity(catalog_file) != catalog_digest:
        # A proposed record can be retired after the supervisor integrates its
        # exact spec into the canonical lock. The assembler_spec check above
        # preserves the same binding without requiring ignored scratch files.
        if receipt.get('assembler_catalog') != 'build/workers/masm/toolchain-lock-proposal.json' or not lock.get('assemblers', {}).get(version):
            raise FormatError('stale assembler catalog receipt')
    if spec['runner'] == 'dosbox-x-win31' and receipt.get('configuration_identity'):
        if identity(ROOT / receipt['configuration']) != receipt['configuration_identity']:
            raise FormatError('stale DOSBox-X assembler configuration')


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('version')
    ap.add_argument('source')
    ap.add_argument('--flag', action='append', default=None)
    args = ap.parse_args()
    obj, receipt = assemble_source(args.source, args.version, args.flag)
    print('OBJECT', obj.relative_to(ROOT).as_posix())
    print('RECEIPT', json.dumps(receipt, indent=2))


if __name__ == '__main__':
    import json
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))

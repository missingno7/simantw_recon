"""Publish the compact decision ledger from canonical experiments."""
from collections import Counter
import re
from common import ROOT,read_json,write_json,identity

def main():
 p=ROOT/'evidence/experiments/toolchain';canonical=read_json(p/'msc700-baseline-Oelw.json')
 good={'FUNCTION_MATCH','CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'}
 probes=[]
 for t,r in zip(canonical['probes'],canonical['results']):
  probes.append({'symbol':t['symbol'],'segment':t['segment'],'offset':t['offset'],'size':t['size'],'source':t['source'],
    'source_identity':t['source_identity'],'flags':r['flags'],'result':r['result'],'object_identity':r['receipt']['object_identity'],
    'status':'CONFIRMED' if r['result'] in ('FUNCTION_MATCH','CONFIRMED_MEMBER') else 'STRONGLY SUPPORTED' if r['result']=='STRONGLY_SUPPORTED_MEMBER' else 'POSSIBLE',
    'scope':'Frozen C hypothesis matches; not proof of historical source text or unique flag spelling'})
 decisions=[
  ('compiler','STRONGLY SUPPORTED','C 7.00 is the working optimizing compiler candidate','GPicSize/GImgSize signed division, WinAddr/SetWinDrawHook shifts, RallocFreed/IsValidSLoc zeroing differ from C 6.00A. Exact driver/front-end identity and untested compatible generations remain open.'),
  ('compiler_600a','RULED OUT','Uniform tested C 6.00A configurations for all frozen probes','None matches the discriminating division and shift probes; some complete larger functions also match C6, so do not assign every object a version from tiny functions.'),
  ('module_variation','POSSIBLE','Untested modules may differ; tested game code needs no split','One profile matches all six game code groups. SYM groups are not original translation units. CRT is independently an older Windows SDK generation.'),
  ('default_model','STRONGLY SUPPORTED','/AL with explicit near and huge declarations','Far pointer parameters and far returns; near RandTurn and near win_handles; far TurnTab and hook array. /AM with explicit far annotations cannot be excluded from bytes alone.'),
  ('unqualified_small_medium_compact','RULED OUT','Uniform unqualified small/medium/compact source defaults for the pointer probes','Small/compact change return addresses/calls; medium changes unqualified heap parameter width. This is conditional on the declared source types.'),
  ('huge_default','RULED OUT','/AH as a uniform profile for the frozen probes','Far array indexing differs for RandTurn/SetWinDrawHook. Explicit huge WindowsMemCpy is required under the matching large profile.'),
  ('optimization','STRONGLY SUPPORTED','/Oelw with speed preference','/Ol discriminated by MyPow and WindowsMemCpy, /Ow by SortRect plus ExtractWord, /Oe by RRand and other allocation-sensitive probes. /Os changes the switch and ExtractWord. Extra inert options are not excluded.'),
  ('alias_a','RULED OUT','/Oa as a uniform replacement for /Ow on the frozen sources','SortRect matches, but ExtractWord changes. Source-form alternatives and local pragmas remain possible.'),
  ('cpu','STRONGLY SUPPORTED','/G1 or /G2; /G2 used for reproducibility','186-class instruction forms and matcher contrasts rule out /G0 for these sources. /G1 and /G2 produce equal tested bytes; this is not proof of 286-only instructions.'),
  ('cpu_g3','RULED OUT','/G3 on the supplied 16-bit C7 compiler','D4022 invalid for 16-bit target; resulting fallback bytes are NOT a 386 experiment. C6 ignores /G3 with D4002.'),
  ('stack_check','STRONGLY SUPPORTED','/Gs or equivalent local suppression in sampled code','The final MyPow /Ge contrast inserts a prologue call to __aFchkstk and differs before any fixup; the matching /Gs profile starts with ENTER 12,0. Full CFG comparison of that losing candidate remains unsupported because of internal padding.'),
  ('calling_conventions','CONFIRMED','C stack arguments/caller cleanup for probes; Pascal imports; near/far both present','Far functions use BP+6 and RETF; near RandTurn uses BP+4 and RET. Explicit Windows API Pascal call in switch probe. This does not establish conventions for all callbacks.'),
  ('crt','STRONGLY SUPPORTED','Windows 3.0 SDK LLIBCW.LIB','64 whole members match, including startup and CRT initialization; 55 public-anchored and 9 with private placement constraints. Medium and Windows 3.1 variants fail discriminating members. Shared member bytes do not identify unique library packaging.'),
  ('fp_runtime','CONFIRMED','Microsoft FP runtime and WIN87EM loader import','Thirteen complete LLIBFPW members match, including sqrt implementation/table and float-to-long conversion. Calibrated FIDRQQ/FIERQQ/FIWRQQ and paired FICRQQ/FJCRQQ transformations preserve instruction bytes. Shared SDK3.0/3.1 members do not distinguish library packaging.'),
  ('fp_compile_mode','STRONGLY SUPPORTED','/FPi-style inline emulation in _AdjustWndMinMax','Nineteenth selected game function: FWAIT/FILD and FWAIT/FST at 1:1B35 and 1:1B39 own additive NE type5 fixups. Fresh C7 /FPi versus /FPi87 versus /FPa contrasts and a successful LINK5.30 calibration distinguish this window. Calls target __aFCIsqrt and __aFftol. This is not a complete function match, a uniform game-wide mode, or proof of global /Oi rather than local intrinsic control. See fp-game-fingerprint.json.'),
  ('linker','CONFIRMED','NE linker-version fields 5.30','Pinned LINK 5.30 executes and reproduces far-call translation in an independently linked two-object experiment. Exact linker binary/patch and option spelling remain unproven.'),
  ('resource_compiler','POSSIBLE','Windows SDK RC family; exact version unresolved','Final resource/fastload layout does not authenticate an RC executable. Candidate DOS-stub failures are host limitations, not exclusions.'),
  ('assembler','POSSIBLE','Microsoft-compatible assembler family; exact game assembler unresolved','Historical CRT object names identify ASM sources, not game assembler version. Host NASM builds only the diagnostic stderr launcher.'),
  ('mapsym','CONFIRMED','SYM format trailer 3.10','Generator executable version remains POSSIBLE/unknown. The acquired SDK 3.1 MAPSYM embeds version 4.11; do not conflate tool version with format version.')]
 ledger={'exe_sha256':canonical['exe_sha256'],'sym_sha256':canonical['sym_sha256'],'working_profile':['/AL','/G2','/Gs','/Oelw','/NT<group>'],
  'probes':probes,'matched':sum(r['result'] in good for r in canonical['results']),'selected':len(probes),'code_bytes':sum(t['size'] for t in canonical['probes']),
  'decisions':[{'question':q,'status':status,'conclusion':v,'evidence_and_limits':why} for q,status,v,why in decisions],
  'phase_gate':'Bounded profile established for these probes. No mass decompilation performed or authorized by this phase report. Exact historical uniqueness remains unresolved.'}
 write_json(p/'decisions.json',ledger)
 versions=[]
 for group,files in [('msc600a',['CL.EXE','C1.EXE','C2.EXE','C3.EXE']),('msc700',['CL.EXE','C13216.EXE','C23216.EXE','C33216.EXE','LINK.EXE'])]:
  for f in files:
   path=ROOT/'toolchain'/group/'BIN'/f;b=path.read_bytes()
   strings=[t.decode('ascii') for t in re.findall(rb'[ -~]{8,}',b) if b'@(#)Microsoft C Compiler' in t or (b'Microsoft 7.00 ' in t) or (b'Optimizing Compiler Version' in t)]
   versions.append({'file':path.relative_to(ROOT).as_posix(),'identity':identity(path),'embedded_version_strings':strings})
 disks=[]
 for pattern,base in [('MSC600A*.json','https://miscdisks.pcjs.org/pcx86/lang/microsoft/c/6.00a/'),('MSC700*.json','https://miscdisks.pcjs.org/pcx86/lang/microsoft/c/7.00/'),('WIN30SDK*.json','https://diskettes.pcjs.org/pcx86/sdk/windows/3.00/'),('WIN31SDK*.json','https://diskettes.pcjs.org/pcx86/sdk/windows/3.10/')]:
  for path in (ROOT/'toolchain').glob(pattern):disks.append({'file':path.relative_to(ROOT).as_posix(),'url':base+path.name,'identity':identity(path),'extraction':'PCjs CHS + FAT12; extracted compressed file MD5 checked against disk fileTable'})
 write_json(p/'provenance.json',{'tools':versions,'distribution_images':disks,'runtime':{'msdos_player':'https://takeda-toshiya.my.coocan.jp/msdos/','dosbox_x':'https://github.com/joncampbell123/dosbox-x/releases/tag/dosbox-x-v2026.08.31','windows_host':'Local existing Windows installation copied into ignored toolchain/win31; VGA configuration and original C7 VPFD.386 added. Not an original SimAnt build input.'},'warnings':['Compiler archives and library members are not committed game source. Toolchain hashes describe the tested candidates, not recovered original build files.','6AX mixed archive installation was unsuitable; no compiler-generation exclusion follows from its runner failure.']})
 print('Canonical:',ledger['matched'],'/',ledger['selected'],'code bytes',ledger['code_bytes'])

if __name__=='__main__':main()

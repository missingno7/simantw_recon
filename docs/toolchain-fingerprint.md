# Win16 SimAnt toolchain fingerprint

Research date: 2026-09-19. Scope: historical tools, ABI, compiler settings and complete runtime contributions. No broad game decompilation was started.

## Result and limits

**A single reproducible C 7.00 profile matches all 18 selected game probes: 761 code bytes across the six game code groups.** This includes a 100-byte switch contribution, a 105-byte long-integer loop, an 81-byte huge-pointer copy, and a 68-byte pointer extraction routine.

```text
CL /c /AL /G2 /Gs /Oelw /NT<original_code_group> INPUT.C
```

Use the pinned DOS C/C++ 7.00 tools, with Windows 3.x providing 32-bit DPMI and the distribution's VPFD.386 driver. The generated objects are ordinary 16-bit OMF. The compiler's own 32-bit execution environment is unrelated to the game's pointer size or target CPU.

This is an evidence-backed working profile, **not a uniquely authenticated original command line**. `/G1` remains equivalent on tested code; inert optimizer options and equivalent source qualifiers remain possible. Exact CL driver/front-end patch identity, original translation-unit boundaries, RC/MASM/MAPSYM executable versions, and game floating-point options are not solved. The results do not require different compiler settings among the sampled game groups. They do independently distinguish older Windows SDK runtime objects from the matching C 7 game-code candidate.

Machine-readable records:

- [Decision ledger](../evidence/experiments/toolchain/decisions.json)
- [Tool identities and current hypotheses](../layout/toolchain.json)
- [Canonical 18-probe run](../evidence/experiments/toolchain/msc700-baseline-Oelw.json)
- [C 7 contrasts](../evidence/experiments/toolchain/msc700-matrix.json), [C 6.00A contrasts](../evidence/experiments/toolchain/msc600a-matrix.json), [final targeted contrasts](../evidence/experiments/toolchain/final-contrasts.json)
- [Complete library members](../evidence/experiments/toolchain/library-members.json)
- [Independent executable/ABI census](../evidence/experiments/toolchain/memory-model.json)

## Evidence vocabulary

| Status | Meaning here |
|---|---|
| CONFIRMED | A directly checked property or exact candidate contribution, including supported fixups. Does not imply unique historical provenance. |
| STRONGLY SUPPORTED | Several discriminating observations agree; an explicitly stated ambiguity remains. |
| POSSIBLE | Consistent with the evidence but not distinguished or not yet tested. |
| RULED OUT | Contradicted within the stated scope. A failed reconstructed source does not rule out every possible source compiled with that tool. |

`FUNCTION_MATCH`, `CONFIRMED_MEMBER`, and `STRONGLY_SUPPORTED_MEMBER` are verifier results. The last category uses consistent private-contribution placement constraints in addition to named publics. `VERIFIER_UNSUPPORTED` is a limitation, not a failed compiler experiment. `UNSUPPORTED_COMPILER_OPTION` means the requested configuration was never exercised.

## Original inputs

| Input | Size | SHA-256 |
|---|---:|---|
| SIMANTW.EXE | 516,096 | `538fed3f0fd60a6528a5e5b20990361ac4d274c58266a81e71c24f751612589d` |
| SIMANTW.SYM | 37,060 | `9d27f4d0872e483ddbf460bda8a2e34b7180f153c6d7c1a74d692720476c9a7f` |

The NE census expands 510 relocation records into 8,145 sites. On-disk chained relocation words are **chain links**, not executable addresses. Public names, segment identities, and entry/export addresses are cross-checked against MAPSYM. The final EXE is never an input to compilation or linking of the probes.

## Compiler generation, driver, and passes

**STRONGLY SUPPORTED:** Microsoft C/C++ 7.00 optimizing code generation is a suitable candidate for the sampled game code. Its case is independent of the final linker's version.

The following supplied compiler passes are pinned by file hash in the lock and [provenance record](../evidence/experiments/toolchain/provenance.json):

| Candidate | Driver / passes | Observed identity |
|---|---|---|
| Microsoft C 6.00A | CL.EXE, C1.EXE, C2.EXE, C3.EXE | Authentic DOS distribution; driver banner 6.00A |
| Microsoft C/C++ 7.00 | CL.EXE, C13216.EXE, C23216.EXE, C33216.EXE | Driver banner 7.00; embedded C1 string 7.00; CL date Mar 3 1992, C2 Mar 9, C3 Mar 10 |

C 6.00A produces `CWD; XOR AX,DX; SUB AX,DX; SAR AX,3; XOR AX,DX; SUB AX,DX` for the frozen signed-division probes under speed-oriented settings. C 7.00 produces the original `CWD; AND DX,7; ADD AX,DX; SAR AX,3`. C 6 also uses a CL-based shift for the shift-by-eight probes where C 7 reproduces the original immediate shift. `RallocFreed` and `IsValidSLoc` provide additional instruction-selection differences. These distinguish the tested compilers without relying on the linker's timestamp or the initial tiny matches.

**RULED OUT, scoped:** the tested uniform C 6.00A configurations do not reproduce the frozen discriminating probe set. C 6 does match several other routines, including the larger `MyPow` with loop optimization. Those individual matches cannot establish original compiler identity.

**POSSIBLE:** untested compatible compiler releases, patch levels, or a different driver invoking equivalent passes. Successful reproduction does not recover original CL/C1/C2 executable hashes. A mixed 6AX archive was unsuitable as installed; its execution failures do not exclude that compiler generation.

## Probe selection and outcomes

The source files are bounded reconstruction hypotheses under `evidence/experiments/toolchain/probes/`, not claims to have recovered historical source text, filenames, typedefs, or module boundaries. Source and object hashes, compiler flags, diagnostics, OMF records and comparison details are recorded per run.

All rows below match under the working profile. Sizes exclude ordinary trailing alignment except for the explicitly reviewed whole switch contribution.

| Probe | Original address | Bytes | Why selected |
|---|---|---:|---|
| ABS | 1:9714 | 20 | Signed comparison, return choice, register allocation; continuity control |
| GPicSize | 2:3DB2 | 36 | Signed division by constant, multiplication, four parameters |
| GImgSize | 2:3DD6 | 35 | Independent signed-division variant |
| BitmapImageSize | 2:1B80 | 49 | Signed long arithmetic and two CRT far calls |
| RRand | 5:156E | 28 | Far call, saved register, signed division/remainder |
| RallocType | 2:59A4 | 12 | Heap-like pointer width and struct offset |
| RallocSize | 2:59B0 | 16 | Four-byte field through a far pointer |
| RallocFreed | 2:59CC | 24 | Two-word null test and boolean return selection |
| RallocSetType | 2:5994 | 15 | Far-pointer write and parameter placement |
| win_SortRect | 7:E3AE | 50 | Two signed comparisons, struct stores, alias assumptions |
| win_WinAddr | 7:C3CE | 22 | Near global array of far pointers, signed shift, stride four |
| WindowsMemCpy | 2:150E | 81 | Long counted loop, registers, huge-pointer carry, imported constant |
| ExtractWord | 2:83F6 | 68 | Pointer-to-pointer, far loads/stores, external call, alias boundary |
| MyPow | 1:48D4 | 105 | Multiple long locals, long multiply helper, optimized counted loop |
| RandTurn | 6:2A22 | 30 | Explicit near function, far call, far array and signed char |
| win_SetWinDrawHook | 7:D59C | 34 | Four-byte function-pointer store into far array, signed indexing |
| CreateMonoSolidBrush | 2:1902 | 100 | Reviewed seven-entry CS jump table, case folding, Pascal GDI call |
| IsValidSLoc | 3:8CA4 | 36 | Editor-group sample, signed bounds tests and register allocation |

`RandTurn` and `win_SetWinDrawHook` also match their complete two-byte CONST selector contributions. Their CONST placement is inferred from the code reference and then checked against the original DGROUP NE selector relocation and independently named far target. These are marked **STRONGLY SUPPORTED** rather than pretending the private pool slot had a public name.

The switch is compared as a complete OMF contribution, including its seven word entries, internal offsets, padding and import fixup. Its jump-table bytes are not decoded as x87 instructions. The routine ends at 2:1966, with RETF at 2:1965.

## Discriminating matrix

The experiment driver uses one-factor contrasts only on probes relevant to that factor. It does not enumerate the Cartesian product of models, optimizers, CPUs and conventions. The initial `/Oe` baseline deliberately leaves loop and alias settings open; the final combined profile is checked on every probe.

| Question | Principal discriminator | Outcome |
|---|---|---|
| 6.00A versus 7.00 backend | GPicSize/GImgSize; WinAddr/hook store | C 7 reproduces the original; tested C 6 settings differ |
| Loop optimization | MyPow, WindowsMemCpy | `/Ol` produces the original register-counted loops |
| Global register allocation | RRand and allocation-sensitive probes | `/Oe` supported; no-register baseline differs |
| Aliasing | SortRect **and** ExtractWord | `/Ow` matches both; `/Oa` changes ExtractWord; neither alone establishes original source alias guarantees |
| Size versus speed preference | Switch, ExtractWord | Tested size-oriented configurations change code; speed preference supported |
| CPU selection | Arithmetic, loops, prologues/epilogues | `/G0` differs; `/G1` and `/G2` remain equivalent on tested probes |
| `/G3` | Compiler diagnostic | C 7 D4022: invalid for 16-bit target. C 6 ignores it. **Not a successful 386-target experiment** |
| Default model | Unqualified Ralloc pointers; near/far returns | Large supported; small/medium/compact differ for frozen unqualified declarations |
| Huge default | Far arrays | `/AH` changes indexing; explicit huge copy pointers work under `/AL` |
| Windows entry code | ABS, RRand, RallocType, SortRect | Unqualified `/Gw`/`/GW` differ; callback-specific code remains a separate question |
| Stack checking | MyPow with loop optimization held fixed | `/Ge` inserts a prologue call to `__aFchkstk`; original and `/Gs` start with ENTER 12,0. Losing candidate's full CFG comparison is limited by padding, but its literal prefix already differs |
| Calling convention | ABS decoration/parameters/return | Global Pascal/fastcall differ; C convention supported for probes |

Not every enabled optimizer can be recovered from byte equality. `/Og`, `/Oi`, loop variants, defaults and local `#pragma optimize` settings may be inert for a particular routine. The working profile is a small sufficient set, not proof that the original command literally contained `/Oelw`.

Microsoft's contemporary documentation explains these options and specifically discusses Windows aliasing across external calls: [C 6 reference](https://www.pcjs.org/documents/books/mspl13/c/cref/) and [Microsoft's Windows compiler-options article](https://techshelps.github.io/MSDN/TECHART/html/msdn_optim.htm). The C 7 language reference identifies `/G3` as unavailable to compilers targeting 16-bit applications: [Microsoft C/C++ 7 language reference](https://bitsavers.trailing-edge.com/pdf/microsoft/msdos_c/Microsoft_C_7.0_1991/24772_C%2B%2B_Language_Reference_199111.pdf). Actual option support is also checked by the captured compiler diagnostic in `g3.txt`.

## Memory model, pointer widths and conventions

These observations were obtained from original instructions and NE relocations before relying on compiler output:

- Game code has both near RET and far RETF. Near and far are separate from C-versus-Pascal conventions.
- Far calls cross the original code groups. Many same-group calls have `NOP; PUSH CS; CALL near`, preserving a far return frame. They must not be counted as ordinary near-function calls.
- `RallocType`, `RallocSize` and `RallocSetType` load four-byte arguments through LES. `RallocFreed` tests both words of the stored pointer. Struct size and type fields are at offsets 6 and 14 in the tested layout.
- `win_WinAddr` accesses DGROUP offsets CE9A/CE9C and returns DX:AX, with a four-byte array stride. Its global array storage is near, while its elements are far pointers.
- `RandTurn` uses BP+4 and RET; its call to `SRand8` is far. The selector at DGROUP:C32E has an NE relocation to segment 8, containing `_TurnTab` at 0024.
- `win_SetWinDrawHook` stores two words at `_win_drawHooks` (9:77B2) with stride four. Its selector pool slot DGROUP:C6CC relocates to segment 9. Other original routines contain indirect far calls; these are separately counted in the census.
- `WindowsMemCpy` increments pointer offsets and adds imported KERNEL ordinal 114 on carry. SDK `LIBW.LIB` independently names that import `__AHINCR`. This distinguishes huge arithmetic from merely passing a four-byte far pointer.
- The switch's `CreateSolidBrush` call is Pascal and uses the GDI ordinal from the independent import library. Ordinary game calls show C stack argument order/caller cleanup.

**STRONGLY SUPPORTED:** large defaults plus explicit near functions/data and explicit huge pointers. **POSSIBLE:** medium defaults with enough explicit far qualifiers. This ambiguity is fundamental when historical declarations are unavailable. A four-byte heap pointer alone cannot prove `/AL`.

The conservative census covers only closed contiguous control-flow extents and deduplicates alias symbols. It is a lower bound, not a linear disassembly of every byte. `_TEXT` contains both runtime and other utilities, so no whole-segment ownership assumption is made. No 32-bit operand/address evidence was found in that restricted census; Capstone's misleading `CDQ`/`CWDE` spelling for unprefixed 99h/98h in 16-bit mode is explicitly excluded from 386 evidence.

## Complete runtime members

**STRONGLY SUPPORTED:** the large-model Windows 3.0 SDK `LLIBCW.LIB` is the principal CRT candidate. Of its anchored members, 64 match completely: 55 public-anchored matches and nine with validated private-placement constraints. Thirteen complete `LLIBFPW.LIB` members also match (eight public-anchored, five with validated private-placement constraints). The same members may exist in other distributions; an exact member match does not authenticate a unique `.LIB` container.

| Owner requested | Complete matched contribution | Status |
|---|---|---|
| `__astart` | `windows\winstart.asm`, `_TEXT` 4:0060, 131 bytes, plus initialized data contributions | CONFIRMED |
| `__cinit` | `dos\crt0dat.asm`, `_TEXT` 4:00E4, 407 bytes, plus initialized data | STRONGLY SUPPORTED |
| `_malloc` | `malloc.asm`, 4:027C, 5 bytes, resolved far-jump translation | CONFIRMED |
| `_free` | `free.asm`, 4:0282, 5 bytes, resolved far-jump translation | CONFIRMED |
| `_fopen` | Entire `fopen.c`, both `__fsopen` and `_fopen`, 4:39AE, 84 bytes | CONFIRMED |
| `_srand`, `_rand` | Entire `rand.c`, 4:06F6, 68 code bytes plus 4 seed-data bytes | STRONGLY SUPPORTED |
| `_sqrt` | Entire `87csqrt.ASM` wrapper member, both `_sqrt` and `__aFCIsqrt`, 4:0AC0, 12 bytes | CONFIRMED |

The tiny malloc/free/sqrt members are explicitly tiny complete contributions; they are not the main argument for CRT identity. Startup, initialization, file opening, stream handling, string routines and the multi-function rand member supply the broader evidence. The sqrt implementation and its complete dispatch table now match independently, in addition to the wrapper. Seven additional complete FP members were accepted after calibrating their loader fixups, adding 2,527 unique code bytes.

The Windows 3.0 and 3.1 `rand.c` contributions are identical and cannot distinguish SDK generations. Startup and other members do discriminate: the 3.0 large startup is 131 bytes, the 3.1 large startup 133 bytes, and the medium variants differ. C 7's Windows rand member is 76 bytes. DOS CRT variants share some assembly members but do not reproduce the complete Windows runtime composition.

[Runtime ownership ledger](../layout/runtime-ownership.json): **77 members, 12,960 unique code bytes** marked for reuse from historical objects and excluded from C reconstruction. Generated cards consume this ledger. Three anchored non-FP CRT members remain incomplete under current verification; unsupported overlapping OMF data, unplaced contributions and unresolved private symbols remain recorded rather than masked.

The checker compares every initialized byte of every placed contribution, all available public placements, all OMF fixups and all NE obligations owned by those initialized bytes. Uninitialized/common bytes may be initialized by another member and are not claimed as emitted zeroes. Private data placement must satisfy consistent relocation constraints and its initialized contents. Each unresolved contribution prevents a complete-member claim.

The FP calibration covers FIDRQQ (NE type 5), FIERQQ (type 4), FIWRQQ (type 6), and the overlapping FICRQQ/FJCRQQ pair (one type-3 obligation). The independent LINK output retains all affected instruction bytes. The verifier requires both members of the pair, valid frames and zero displacement, exact bytes and the matching loader obligation. See [calibration observations](../evidence/experiments/toolchain/fp-link/fixup-calibration.json). The matched FP contributions are shared by SDK 3.0 and 3.1; they do not independently distinguish those SDK packages.

## Floating point

**CONFIRMED:** the executable imports WIN87EM and contains the Microsoft FP runtime, including exact complete members shared by the SDK FP libraries. The original's absolute FI*QQ symbols and remaining floating-point fixups are preserved as evidence.

**STRONGLY SUPPORTED:** `/FPi`-style inline emulation in the game function `_AdjustWndMinMax` (segment 1, entry `1A6E`). Its `1B35` FWAIT/FILD and `1B39` FWAIT/FST instructions each own an additive NE type-5 fixup. The following far calls resolve independently through NE selector relocations and SYM to `__aFCIsqrt` and `__aFftol`.

Seven fresh C7 compiler contrasts compare `/FPi`, `/FPi87`, and `/FPa`, with and without intrinsic generation, plus a precision-control contrast. `/FPi` emits the FWAIT/x87 load and `FIDRQQ` OMF fixup; `/FPi87` lacks that emulator obligation; `/FPa` uses calls. A successful independent LINK 5.30 experiment converts the synthetic probe's `FIDRQQ` to exactly NE type 5 while preserving the instruction bytes. The minimal link harness is not executed; its no-stack warning is retained.

This is the **nineteenth selected game function**, but only an instruction window is fingerprinted: the complete-match count stays **18 functions / 761 bytes**. The original FST temporary is not reproduced by this synthetic source, and no complete `_AdjustWndMinMax` match is claimed. The intrinsic sqrt call supports `/Oi` or local intrinsic control; it does not establish a uniform `/Oi` command line. FP modes in other translation units remain **POSSIBLE / unresolved**. The tested `/FPi87` and `/FPa` settings alone are **RULED OUT for this window**, not globally for all objects or explicit assembly.

See [compiler contrasts](../evidence/experiments/toolchain/fp-mode-contrast.json), [game fingerprint](../evidence/experiments/toolchain/fp-game-fingerprint.json), and [independent link receipt](../evidence/experiments/toolchain/fp-link/receipt.json). `python tools/fp_fingerprint.py` revalidates the frozen receipts, original instructions, call targets and linked fixup. Microsoft's [C Advanced Programming Techniques, chapter 4](https://www.pcjs.org/documents/books/mspl13/c/cadvprg/) documents the distinction between inline emulation, coprocessor-only code and call-based math, and the option/local-pragma alternatives for intrinsic generation.

## Linker and ancillary tools

**CONFIRMED:** the NE header records linker version **5.30**. The acquired LINK.EXE runs and reports 5.30. A separate two-object link experiment toggles `/FARCALLTRANSLATION` and recreates the original five-byte `NOP; PUSH CS; CALL near` form versus an ordinary far call. See [link experiment](../evidence/experiments/toolchain/link-probe/). This supports the explicit transformation used in complete-member comparison, without deriving compiler version from LINK.

The final image directly records Windows 3.0 target, automatic data/stack segment 10, heap 4096, stack 8192, multi-instance data, and 512-byte sector alignment. Segment flags and fastload/resource metadata are retained in the census. These establish final properties; they do not uniquely recover a `.DEF`, switch spelling, library order, RC postprocessing commands or exact LINK patch executable.

**MAPSYM:** 3.10 is the **SYM format trailer**. The precise generator executable is unresolved. The acquired SDK 3.1 MAPSYM embeds a 4.11 tool banner, illustrating why these identities must be kept separate; no assertion is made here that its unexecuted output matches the supplied SYM.

**RC and assembler:** exact versions remain **POSSIBLE**, not identified. Resource shape and familiar ASM library module names are insufficient. Failed attempts to execute OS/2-form SDK utilities through a DOS runner are host failures and exclude no historical version. The modern NASM-built `CAPCL.COM` is only a host logging helper that duplicates stderr before executing authentic CL; it never contributes to game objects.

## Reproduction and verification

The ignored `toolchain/` tree contains the acquired historical binaries and runtime host. The lock verifies their identities; distribution URLs and compressed-image hashes are in `provenance.json`. `tools/unpack_tools.py` verifies FAT12 extracted-file hashes and supports the distribution compression formats. The existing local Windows installation was copied for the C 7 host; it is not evidence of the original developer's host OS.

```powershell
python tools/setup_toolchain.py
python tools/toolchain_probes.py --compiler msc700 --baseline --optimization /Oelw
python tools/toolchain_probes.py --compiler msc700
python tools/toolchain_probes.py --compiler msc600a
python tools/library_match.py
python tools/memory_model.py
python tools/toolchain_report.py
python -m unittest discover -s tests -v
```

Every compile uses a fresh directory, frozen source, explicit flags and verified tools. The C 7 runner mounts only source/build and tool directories, not original assets. A host-only launcher captures both CL output streams. Receipts include object/source identities and a hash of the tool lock; prior immutable lock snapshots allow historical experiment verification when research annotations evolve.

The test suite checks corrupted instructions, wrong targets/frames, missing loader fixups, changed private seed data, conflicting public placements, wrong import ordinals and changes in a member's second function. It also covers OMF backpatches and aliases. A successful first function cannot hide a mismatch elsewhere in the member.

The current phase has established a practical small profile. Remaining identity ambiguities are documented rather than converted into a claim that the entire historical build is solved. Broad matching/decompilation remains outside this work.

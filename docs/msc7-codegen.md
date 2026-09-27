# MSC 7.00 code-generation fact register

The knowledge base for how the locked Microsoft C/C++ 7.00 compiler turns source into the bytes we must reproduce. It is modelled on the useful parts of `../stunts_recon/docs/msc510-codegen.md`. Workflow advice stays in [grinder-lessons.md](grinder-lessons.md); this file holds only compiler behaviour.

**Rules of this register**
- Every claim has a stable ID, a status, a minimal reproducer, the exact profile/flags, evidence, the functions where it was observed, counterexamples, and the validation date/commit.
- Statuses:
  - **VERIFIED**: reproducer plus an admitted control or admission that depends on it.
  - **SUPPORTED**: reproducer or several real functions, but no decisive control yet.
  - **FALSIFIED**: tested and shown not to hold in our environment.
  - **OPEN**: a hypothesis under study.
- Negative results stay here so that nobody re-runs them.
- Evidence is produced with `tools/probe.py SPEC.json --record ID`, which enforces the function's assigned profile. It lands in `evidence/codegen-facts/ID/` (spec plus report: bytes, instructions, frame, homes, registers, fixups). A probe run with a profile other than the function's assigned one is not evidence.
- Only the supervisor changes a status. Workers propose entries in their REPORT.md.

Profiles: `baseline` = `/AL /G2 /Gs /Oelw`; `og` adds `/Og`; `ogi` = `/Oegilw`; `oi`/`-ga` variants per `layout/compiler-profiles.json`.

## Contents
1. Frame and locals: F1, L1, L6, L7
2. Registers: R1
3. Expressions and CSE: E15, E16, S1, S2
4. Control flow: C1, C12, C13
5. Far pointers: P1, P2
6. Data and literals: D1
7. Unexplained: U1 and later
8. Invalid evidence (must not be cited)

## 1. Frame and locals

**MSC7-F1: named locals are homed in first-use order, not declaration or name order. SUPPORTED.**
- Evidence:
  - `evidence/experiments/frame-model/` (415-function /Zi CodeView corpus; held-out exact order 42/73 for declaration order, pairwise 68.5% for loop-weighted use).
  - MSC7-L1 control: reordering first uses changes homes, while names and declarations do not.
- Scope: address-taken and plain memory locals under `baseline`. Frame-model rules for mixed frames remain uncertain.
- Counterexamples: none recorded.
- Validated 2026-09-27.

**MSC7-L1: local homes do not follow the identifier hash (stunts L1). FALSIFIED.**
- Hypothesis from MSC 5.10: bucket = sum of the name's bytes & 15, walked newest-first.
- Reproducer: `evidence/codegen-facts/MSC7-L1/l1-local-home-order`, profile `baseline`. 54 variants (two declaration orders × three names for each of three `long` locals, names chosen across buckets 0–15) all produce one identical object.
- Control `l1-control-first-use`: moving statements does change the code, so the probe is sensitive.
- Consequence: renaming or reordering declarations never moves an MSC 7.00 home. Do not spend search time on it.
- Validated 2026-09-27.

**MSC7-L6: unused locals do not keep a frame slot (stunts L6). FALSIFIED.**
- Reproducer: `evidence/codegen-facts/MSC7-L6/l6-unused-local`, `baseline`. An unused `int`, `long`, `int[4]`, two-member `struct` or `register int` all leave the object identical (frame 2).
- Consequence: an untouched hole in a target frame is not explained by a merely declared local. See L7.
- Validated 2026-09-27.

**MSC7-L7: a used automatic array keeps its full declared extent, including elements that are never referenced. VERIFIED.**
- Reproducer: `evidence/codegen-facts/MSC7-L7/l7-admitted-pct-array-tail`.
- Admitted control `_SetCasteProd` (`og`, `/Oeglw /NTSIMTWO_MODULE`): `pct[5]` gives frame 26 (exact member). Changing only the bound to `[4]` or `[6]` gives frame 24 or 28, with the same 74/74 opcodes.
- Toy (`og`): a volatile array whose elements 0..3 are used gives ENTER 10, 8 or 12 for bounds 5, 4 or 6.
- Consequence: an untouched word at the deep end of a target frame can be the tail of a used array.
- Validated 2026-09-27 (f-study-fhole).

**MSC7-L8: a used automatic struct keeps storage for members that are never referenced. VERIFIED.**
- Reproducer: `evidence/codegen-facts/MSC7-L8/l7-admitted-struct-unused-member`.
- Admitted control `_ConvertMonoBitmap` (`ogi`, `/Oegilw /NTGR_MODULE`): the exact source has `struct { int spare; int value; }` and uses only `value`, giving frame 16 (exact, 124/124 bytes). Removing `spare` gives frame 14 and fails strict on that byte.
- Toy (`ogi`): a three-word struct with only fields 2 and 3 used gives frame 6 with bp-6 untouched; two scalars give frame 4.
- Applied to `_MakeLint2`: a three-member struct reproduces the target ENTER 6 and its homes, but the body drops from 42/48 to 32/48. It explains the footprint, not the source.
- Together with L6 (FALSIFIED): an untouched target slot means a USED aggregate (array tail or unused member), never a merely declared local.
- Validated 2026-09-27 (f-study-fhole).

**Cluster note (F-HOLE, 17 functions, 2026-09-27):** in most of these the frame hole is not the earliest divergence. A branch destination (`_MakeOutletH/V`, `_Reproduce`, `_DoSow`, `_ProcModeEvent`), a register choice (`_FillMap`, `_CloseIndex`, `_DigTileB`, `_ch_DumpOldest`) or a home order (`_LoadStringAnt`, `_LoadMonoPats`, `_win_DrawTitle`, `_DrawMapFoot`) comes first. See build/workers/f-study-fhole/REPORT.md.

## 2. Registers

**MSC7-R1: SI/DI choice among two word register candidates. SUPPORTED.**
- The parameter with more static uses gets SI. On a tie, the one used last usually gets SI (6 of 7 straight-line probes). An `M[x][y]` index use moves y into SI.
- Probes: `build/supervisor/slotprobe.py` runs of 2026-09-27; not yet recorded with tools/probe.py.
- Observed as residues: `_DigTileR`, `_GetMowDir`, `_GetSmellT`, `_DoNestingR`, `_FloodNestB`.
- Counterexample: the `_DigTileR` draft stays swapped under goto, if-block and assignment-in-condition rewrites, so the weights are incomplete.
- Validated 2026-09-27 (probes only).

## 3. Expressions and CSE

**MSC7-E15: symbol-table pressure changes codegen (stunts E15/E17). FALSIFIED for the tested scope.**
- Reproducer: `evidence/codegen-facts/MSC7-E15/e15-pressure-mowerfall`, `_MowerFall` with its assigned profile `ogi` (`/Oegilw /NTSIMTWO_MODULE`). A preceding function referencing 0, 40, 120, 300 or 700 long-named externs leaves `_MowerFall`'s code identical modulo fixup fields. Only the selector-pool word addresses shift. The result against the original stays 53/54.
- MSC 7.00 is a protected-mode compiler; the MSC 5.10 memory budget does not bind here.
- Do not rename globals or add or drop declarations to steer CSE.
- Validated 2026-09-27.

**MSC7-E16: CSE only between identical folded expression trees (stunts E16). OPEN.**
- Study launched 2026-09-27 (worker f-study-e16).

**MSC7-S1: signed vs unsigned comparison follows the declared type of the compared variable (`jl`/`jg` vs `jb`/`ja`). VERIFIED.**
- Admission: `_MakeKitchenWall` (2026-09-27, commit e9852013). The target `jl` on the row loop required `int rowNumber`; the draft's `unsigned` gave `jb`.
- The `search.py` best.branch_destinations report shows these pairs.

**MSC7-S2: `add r, N*k` induction steps mean the original indexed inline, e.g. `M[row*64+col]`, with no temporary. VERIFIED.**
- Admission: `_MakeKitchenWall` (same commit). A separate `rowOffset = row*64` temporary instead produces `shl r,6` and an extra home.

## 4. Control flow

**MSC7-C1: an `or r,r` before the loop-exit `je`, after a decrement, marks a loop test reached from two paths. VERIFIED.**
- The source is a retry loop: `while (i) { ...; if (ok) { ...; --i; } }`.
- Admissions: `_InitSow`, `_InitPillar` (commit d1d933c9). The drafts decremented unconditionally, gave 47/48 and 81/82, and became strict on the first compile after the fix.
- Detected by `branch_destinations`.

**MSC7-C12: at a common tail that consumes several live word values, their register mapping follows the assignment order in the physically emitted predecessor block. SUPPORTED.**
- Reproducers: `evidence/codegen-facts/MSC7-C12/`:
  - `c12-which-arm-sets-join-registers` (`ogi`, `/Oegilw /NTANTEDIT_MODULE`) and `-baseline` (`/Oelw /NTSIMONE_MODULE`);
  - `c12-minimal-*`.
- Evidence: `p` and `q` meet at a tail computing `p + q*z`. Reversing the two assignments of the arm emitted directly before the tail swaps them (BX/DI); reversing the other arm changes that arm's order but not the mapping. Size and frame are unchanged.
- Admitted control `_AddMsgBalloon` (100/100): a goto form preserving the raw arm's order compiles identically. Reversing that arm's direct parameter copies changes code but keeps the register roles, so the rule applies when live values compete for roles, not to plain parameter copies.
- An early return or a duplicated tail removes the join (different schedule, no rule).
- Observed: no current residue depends on it. The WRONG_REGISTER cluster diverges at entry or before any join (R1 territory). `_MowerFall` (AL clear vs BH reuse) and `_DoNestFightR` (CL kept vs reload) are not join effects; they are E16 and assignment-scheduling cases.
- Validated 2026-09-27 (f-study-c12).

**MSC7-C13: loop-test placement follows the code after the loop (stunts C13). OPEN.**
- Candidate residues: `_MakeOutletH/V` (the post-tested fill loop improved alignment).
- Study launched 2026-09-27 (worker f-study-c13).

## 5. Far pointers

**MSC7-P1: copying a far parameter to a local alias before its null check emits one `LES` from `[bp+6]` and reuses `ES:BX`. SUPPORTED.**
- Control: admitted `_GRectOutline` (81/81, 186/186 bytes).
- Probes: `build/supervisor/slotprobe/f_farptr_shapes.*`.
- Counterexample: `_font_DumpFont` (`og` profile); the alias there adds a home instead.
- Validated 2026-09-27.

**MSC7-P2: a far call between testing a pointer and using it produces a BP home for the pointer, `LES`, and `push es:[bx]`; without the call, access folds to a direct global push. SUPPORTED.**
- Probes as P1.
- Unexplained: `_win_ModeControlClosed`/`_win_CasteControlClosed` push `es:[bx]` with no intervening call (U3).

## 6. Data and literals

**MSC7-D1: string literals are packed back to back in `_DATA`, while named `char` arrays of odd length are word-aligned. SUPPORTED.**
- `_SetPause`/`_PauseGame`: the target's two menu strings sit 17 bytes apart (0x900/0x911). Named arrays gave offsets 0/18; struct and single-array forms keep the spacing but change the code (build/workers/f-pauseunit/REPORT.md).
- Open question: how three functions share one copy.

## 7. Unexplained residuals

- **U1 `_WaitHundredths`**: 22/22 opcodes. The long add uses AX:DX where the target uses CX:BX.
- **U2 `_GtRegisterClass`**: the statement `wc.windowProc = GTCLIENTWNDPROC;` alone adds a 26-byte hidden temporary (ENTER 0x68 vs target 0x4E). Pascal prototypes, casts and a same-file definition do not remove it.
- **U3 `_win_ModeControlClosed`**: `push es:[bx]` through a just-tested pointer, with no intervening call.
- **U4 `_MowerFall`**: the target clears AL before two stores; the candidate reuses a known-zero BH (C12 candidate).

## 8. Invalid evidence (do not cite)

- **`_FillMap` `[bp-8]` experiment (2026-09-27)**: the probe was compiled with `baseline /NTSIMONE_MODULE` instead of the assigned `ogi`. It showed a "second register local gives ENTER 8" effect, whose extra slot was a used home, not an untouched one. It says nothing about L7.

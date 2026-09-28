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

**MSC7-F1: home assignment for named locals. SUPPORTED, refined by F1A–F1G.**
- The frame-model corpus (`evidence/experiments/frame-model/`) and f-study-forder (2026-09-27, `baseline` `/Oelw /NT_TEXT` toys, assigned-profile admitted controls) show the following.
- Names and declaration order do not decide homes for plain or address-taken locals (L1, F1G); volatile locals are the exception (F1D).

**MSC7-F1A: for same-width address-taken locals, static reference count ranks the homes (nearest BP first), and equal counts follow the first lexical reference. A later store order does not override it. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F1A/`.
- Controls: `_AnimYellowFight` and `_win_ClearGroupAreas` declaration permutations compile identically.

**MSC7-F1B: F1A holds when the first references sit inside a branch or a loop body; loop weight is not needed to explain the order. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F1B/`.

**MSC7-F1C: size classes in one small `baseline` frame put char at BP-1, word at BP-4, and long/far pointers in 4-byte homes (BP-8, BP-12). Equal-width 4-byte locals swap when their first-reference order swaps. SUPPORTED, one frame only.**
- `evidence/codegen-facts/MSC7-F1C/`.

**MSC7-F1D: volatile word locals follow declaration identity (the first declared is deeper: a at BP-4, b at BP-2); store order does not move them. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F1D/`.
- A distinct allocation class from address-taken locals.

**MSC7-F1E: two volatile word locals in disjoint sibling blocks do not share a home. SUPPORTED, narrow.**
- `evidence/codegen-facts/MSC7-F1E/`.
- The admitted `_MakePillFood` keeps block-local x,y in its exact frame.

**MSC7-F1F: static-use weight outranks first use. Extra static references move a local nearer BP even when its first reference is later. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F1F/`.
- This is the lever for WRONG_STACK_SLOT residues: an extra or missing use of one local, or a different allocation class (volatile, address-taken), swaps homes.

**MSC7-F1G: reordering declarations alone leaves an admitted function identical. SUPPORTED.**
- `_MakePillFood` (`og`, 219/219, 560 bytes).
- `evidence/codegen-facts/MSC7-F1G/`.

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

**MSC7-F2: at most two competing mutable word locals get SI/DI; a third equally used one gets a 2-byte BP home. `register` is only a hint. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F2/` (`baseline` and `ogi` toys).
- Admitted control `_FloorTiles` (`ogi`): changing `sum` to `register int` gives the identical object (80/80).
- Consequence: a draft frame one word LARGER than the target usually has one more competing local than the original. Remove a variable (reuse a parameter, merge temporaries) rather than rearranging.

**MSC7-F3: loop-weighted uses decide which of three competing locals gets SI/DI. The same number of uses after the loop does not. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F3/` (`baseline`).
- Agrees with docs/regalloc-lessons.md.

**MSC7-F4: a far call alone does not force a live scalar into a home; taking its address and passing it does. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F4/`.
- Consistent with the admitted `_win_YardClosed` and `_DoFastMonoBitmap`.

**MSC7-F5: a far pointer is one offset/segment object, not two word candidates. `T far * volatile p` forces a 4-byte home and an LES reload at every use. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F5/`.

**MSC7-F6: a word local copied once from a parameter can be register-held (SI) like the parameter itself. SUPPORTED.**
- `evidence/codegen-facts/MSC7-F6/`.

**MSC7-F7 / MSC7-F8: local declaration order and a `register` hint do not change home assignment in a crowded frame. FALSIFIED as causes.**
- Tested on `_AnimYellowFight` (24-byte frame, 185/185 opcodes, 15 home operands differ). Both variants compile to the identical object, and a 1,010-evaluation home-order permuter run found nothing.
- Home order there comes from something other than declaration order, e.g. the role or lifetime structure.
- Reproducers: `evidence/codegen-facts/MSC7-F7/`, `MSC7-F8/`.

## 2. Registers

**MSC7-R1: SI/DI choice among two word register candidates. SUPPORTED, refined by R2/R3.**
- The parameter with more static uses gets SI. On a tie, the one used last usually gets SI (6 of 7 straight-line probes). An `M[x][y]` index use moves y into SI.
- Probes: `build/supervisor/slotprobe.py` runs of 2026-09-27; not yet recorded with tools/probe.py.
- Observed as residues: `_DigTileR`, `_GetMowDir`, `_GetSmellT`, `_DoNestingR`, `_FloodNestB`.
- Counterexample: the `_DigTileR` draft stays swapped under goto, if-block and assignment-in-condition rewrites, so the weights are incomplete.
- Validated 2026-09-27 (probes only).

**MSC7-R2: refines R1. An extra static use moves a value into SI. With equal counts, final-use order sometimes decides, but not reliably. SUPPORTED, narrow.**
- Reproducers: `evidence/codegen-facts/MSC7-R7/` (`r1-straight-tie-and-count`), `MSC7-R10/` (`r1-tie-first-held-last-swapped`); `baseline`.
- Counterexample: R10 swaps the final two calls without changing the assignment.
- Observed as insufficient for `_GetSmellT`, `_AddRock3`, `_IsItYellow`, `_FloodNestB`.
- Validated 2026-09-27 (f-study-r1).

**MSC7-R3: in a row-major 2-D byte map `M[x][y]` with two equal-use word locals, the scaled first subscript gets SI and the second gets DI; transposing the subscripts swaps them, and one extra use of the second overrides it. SUPPORTED, narrow.**
- Reproducers: `evidence/codegen-facts/MSC7-R3/`, `MSC7-R2/`; `baseline`.
- Admitted control `_PlaceEggR` (`baseline /NTSIMONE_MODULE`): row in SI, column in DI.
- Counterexample: `_GetSmellT` stays swapped when its assignments are reordered.

**MSC7-R5: for `long d = GetTickCount() + word`, MSC keeps the call result in CX:BX and adds the sign-extended word into it; operand order does not matter. A split update (`d = call(); d += w;`) adds into the home through AX:DX. SUPPORTED, this shape only.**
- Admitted control `_ms_Delay` (`baseline /NTGR_MODULE`): both combined forms are strict (18/18).
- `evidence/codegen-facts/MSC7-R5/`.
- Does not solve `_WaitHundredths`: the split forms drop to 16/22, and the reversed split is identical to the combined form (`build/probes/r5-waithundredths-split`, 2026-09-27).

**MSC7-R6: loop repetition alone gives a value SI over an equally used value outside the loop. OPEN.**
- The probes could not separate loop weight from instruction constraints: `evidence/codegen-facts/MSC7-R6/`, `MSC7-R9/`.
- F3 (loop weight among three competitors for SI/DI) is the related SUPPORTED observation.

**MSC7-R13: declaration order or a `register` hint picks SI/DI for equally used integer values. FALSIFIED (narrow).**
- Reversing declarations or assignments, or adding `register`, left the object identical.
- What did move values: call order, which swaps the parameter-to-SI/DI loads, and 2-D index transposition, which swaps the scaled and base operands.
- Positive control MSC7-R14 (admitted `_PlaceEggR`); negative control MSC7-R15.
- Reproducer `evidence/codegen-facts/MSC7-R13/`.

**MSC7-R16: in a flat nested induction pair, the inner index gets DI and the outer CX; interchanging the nesting swaps them. SUPPORTED (narrow).**
- Seen in `_FloodNestB` (evidence/codegen-facts/MSC7-R16/).
- It is not the complete allocator: the target uses row DI and cell BX in row-outer order.
- Steering lever: loop structure and value roles, not declarations.

**MSC7-X2: rank word locals by lexical read count, tie-break by later last reference then name; SI, then DI, then homes. SUPPORTED for simple shapes; FALSIFIED as a general rule.**
- Lab: `tools/alloc_lab.py`, docs/msc7-allocator-lab.md. 555 controlled cases under baseline, og, oi and ogi gave 2,220 observations.
- The rule fits 5,872 of 5,928 placements (99.06%). Every miss is in the loop-depth family, and a loop-read multiplier did not help.
- On 30 admitted functions it gets only 45 of 90 named placements right (build/workers/sup-allocx/). Real code adds generated temporaries, pointer and addressing roles, 32-bit arithmetic, and call and branch lifetimes that source counts cannot see.
- Use the rule as a local clue for simple shapes only. The real allocator must be read from C23216 (f-study-c2).

## 3. Expressions and CSE

**MSC7-E15: symbol-table pressure changes codegen (stunts E15/E17). FALSIFIED for the tested scope.**
- Reproducer: `evidence/codegen-facts/MSC7-E15/e15-pressure-mowerfall`, `_MowerFall` with its assigned profile `ogi` (`/Oegilw /NTSIMTWO_MODULE`). A preceding function referencing 0, 40, 120, 300 or 700 long-named externs leaves `_MowerFall`'s code identical modulo fixup fields. Only the selector-pool word addresses shift. The result against the original stays 53/54.
- MSC 7.00 is a protected-mode compiler; the MSC 5.10 memory budget does not bind here.
- Do not rename globals or add or drop declarations to steer CSE.
- Validated 2026-09-27.

**Spellings that compile identically. Do not search among these (f-study-e16, 2026-09-27, all SUPPORTED):**

**MSC7-E16: CSE reuses expressions that fold to the same tree. SUPPORTED.**
- Admitted control `_AddBlackAnts` (`og`, `/Oeglw /NTSIMTWO_MODULE`): writing all three occurrences of `x * 64 + y` as `(x << 6) + y`, `y + x * 64` or `x * (32 + 32) + y` gives one identical object that stays an exact member.
- Reproducer: `evidence/codegen-facts/MSC7-E16/`.

**MSC7-E17: commuted addition, removal of a double negation, `*1` and cancelling `+1-1` fold before CSE; a bitwise identity stays distinct. SUPPORTED.**
- `evidence/codegen-facts/MSC7-E17/`.

**MSC7-E18: an explicit scalar temporary (`t = a+b; ... t ...`) disappears into the repeated expression. SUPPORTED.**
- `og` toy, same 26-byte object for all three forms.
- `evidence/codegen-facts/MSC7-E18/`.

**MSC7-E21: `(a+b)`, `(int)((long)(a+b))`, `(int)((long)a+b)`, `(int)((long)a+(long)b)` and `(int)a+(int)b` compile identically for a low-word result. SUPPORTED.**
- `ogi`.
- `evidence/codegen-facts/MSC7-E21/`.

**MSC7-E22: `p[i*8+j]`, `*(p+i*8+j)`, `*(p+j+i*8)`, `(p+i*8)[j]` and `p[(i<<3)+j]` give one address tree (one far load, one address calculation). SUPPORTED.**
- `ogi`.
- `evidence/codegen-facts/MSC7-E22/`.

**MSC7-E23: a selector returned in DX by a far call stays in DX (`mov es,dx`) until a later far call forces the compiler to home the pointer and reload ES from its home. SUPPORTED.**
- `ogi` toy; an alias does not change it.
- `evidence/codegen-facts/MSC7-E23/`.
- Relevant to `_DecodeString` (69/70: the target keeps `mov es,dx`, the draft reloads from a home), whose draft has a call or pointer lifetime the original does not.
- Related: MSC7-P2 (far pointers).

**MSC7-E20: `_MowerFall` clears AL afresh before two chained zero stores; the draft reuses a known-zero BH. OPEN.**
- Chained, separate, scoped-zero-local and read-back forms, plus bounded steering (dead guards, alias guard, zero temporary), all stay at 53/54 or regress.
- `evidence/codegen-facts/MSC7-E20/`, `MSC7-E26/`; `ogi`.

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

**MSC7-C13: the code physically after a loop decides its test placement (stunts C13). FALSIFIED.**
- Admitted control `_ClearBookmarks` (`oi-ga`, `/Oeilw /GA /NTSIMANT_MODULE`, 45/45): appending a call, or a two-armed conditional, after the loop leaves the loop bytes unchanged through `cmp si,0x46; jb`. The exit just falls through to the new tail.
- Reproducers: `evidence/codegen-facts/MSC7-C13/`, `MSC7-C21/`.
- The earlier `_MakeOutletH/V` loop observation is frame-confounded (ENTER 8 vs 6) and is not evidence.
- Validated 2026-09-27 (f-study-c13).

**MSC7-C15: a guarded `do` (`if (c) do ... while (c)`) and the equivalent `while` compile identically when an observable call keeps the loop. SUPPORTED, narrow.**
- Admitted control `_UpdateAllWindows` (`oi-ga`, 25/25).
- `evidence/codegen-facts/MSC7-C15/`, `MSC7-C17/`.
- An unguarded `do` has no preheader test.

**MSC7-C16: guarded `do` always equals `while`. FALSIFIED.**
- A scalar induction loop that the optimiser reduces to closed form differs: 18 vs 28 bytes.
- `evidence/codegen-facts/MSC7-C16/` (`oi-ga`).

**Control-flow spellings that compile identically. Do not search among these (SUPPORTED on admitted controls):**
- **MSC7-C18:** lexical order of switch arms. `_DoMenuEntry` (`oi-ga`) with case orders 4,5,6,8 / 8,6,5,4 / 4,6,5,8 gives one object. An if-chain form differs: 145/183.
- **MSC7-C19:** `break` to post-loop cleanup equals `goto` a label at the same point. `_ShowIntro` (`baseline`, 111/111).
- **MSC7-C20:** `continue` equals `goto` an empty label just before the `do` test. `_DrownBList` (`og`, 35/35).
- **MSC7-C23:** an early `return` carrying a duplicate of the cleanup tail merges into the shared tail. `_ShowIntro`.
- Evidence: `evidence/codegen-facts/MSC7-C18/`, `C19/`, `C20/`, `C23/`.

**MSC7-CFG2: for a two-arm conditional that assigns DIFFERENT values, inverting the predicate and swapping the arms changes the emitted branch and fall-through arm. Equal assignments collapse and polarity does not matter. SUPPORTED.**
- Admitted control `_MakeKitchenWall` (`ogi`): exact at 81/81; the inverted and swapped form gives 80/81.
- Toy (`ogi`): `if (c) a else b` and `if (!c) b else a` give different 26-byte objects.
- `evidence/codegen-facts/MSC7-CFG2/`.
- Unlike switch-arm order (C18), if/else polarity IS a search axis.
- Validated 2026-09-28 (f-cfg2-00).

**MSC7-CFG2 refinements (f-cfg2-01, 2026-09-28), all SUPPORTED, narrow:**
- **Complementary return arms:** a scalar zero test with complementary return arms (`x == 0 ? 1 : 0` vs `x != 0 ? 0 : 1`) compiles identically; only a changed truth table changes the result materialisation. `evidence/codegen-facts/MSC7-CFG2-TOY/` (`baseline`).
- **Abort/event guard:** `abort == 0 && events == 0` and the equivalent early-exit spellings canonicalise to one layout (_SpiderDialog; `MSC7-CFG2-SPIDER-01/`). An opposite branch orientation in the target is not by itself evidence of different runtime paths.
- **Guard polarity:** an early return versus a positive guard compiles identically in the admitted `_win_DrawBitMapAtObj` (`og`; `MSC7-CFG2-CTRL-GUARD/`). Guard polarity alone is not a lever; contrast CFG2, where the arms assign different values.
- **Predicate spelling:** for an unsigned value, `== 0` gives `cmp/sbb/neg` while `< 1` gives a branch plus `xor`. Admitted `_snd_IsSongDone` (`ogi`): `== 0` is exact 14/14, `< 1` is 12/14 (`MSC7-CFG2-CTRL-SONG/`). The spelling of an equivalent predicate can matter.

**MSC7-C22: in a `for` loop, `continue` reaches the increment and test while `break` leaves; a target branch into `inc si` is a `continue`. SUPPORTED.**
- `_FillHolesRN` (`baseline`): `continue` removes one of the two branch-destination mismatches.
- `evidence/codegen-facts/MSC7-C22/`.

**MSC7-C24: a dead `sizeof(action) != 16` guard before `_DoMenuEntry`'s switch steers its shared `SaveGame` tail. FALSIFIED.**
- The object is identical.
- `evidence/codegen-facts/MSC7-C24/`.
- `_DoMenuEntry` (181/183: branch-specific pushes before one shared call) stays open.

## 5. Far pointers

**MSC7-P1: copying a far parameter to a local alias before its null check emits one `LES` from `[bp+6]` and reuses `ES:BX`. SUPPORTED.**
- Control: admitted `_GRectOutline` (81/81, 186/186 bytes).
- Probes: `build/supervisor/slotprobe/f_farptr_shapes.*`.
- Counterexample: `_font_DumpFont` (`og` profile); the alias there adds a home instead.
- Validated 2026-09-27.

**MSC7-P2: a far call between testing a pointer and using it produces a BP home for the pointer, `LES`, and `push es:[bx]`; without the call, access folds to a direct global push. SUPPORTED.**
- Probes as P1.
- Unexplained: `_win_ModeControlClosed`/`_win_CasteControlClosed` push `es:[bx]` with no intervening call (U3).

**MSC7-P3: a LOCAL far-pointer alias of a far parameter, used for the null check and later dereferences, collapses the offset/selector pair into one `LES [BP+N]`. A macro alias that expands to the parameter behaves like direct use (separate MOVs). SUPPORTED on all four profiles (`baseline`, `og`, `ogi`, `oi-ga`).**
- Admitted control `_GRectOutline`: exact with the alias; direct parameter use gives 67/81 with split loads.
- Toys: struct and scalar pointee give direct/macro = 30 bytes, alias = 26 bytes with LES.
- Evidence: `evidence/codegen-facts/MSC7-P3*/`, build/workers/f-study-p3/REPORT.md.
- Tension observed in `_gr_BitMapSize` and `_SetDevicePalette`: the alias restores LES/LDS but adds a home (F2), so the target needs the alias AND one fewer other home-holding local.
- Validated 2026-09-28.

**MSC7-P4: a far-pointer field set to `&named_far_global` and tested before a far call gets a pointer home, an `ES:BX` compare and a post-call `LES`, but MSC 7.00 folds the call ARGUMENT to a direct `push ES:[global]`. SUPPORTED as a boundary.**
- Scalar, struct-member, `*p`/`p[0]`, macro, pointer-arithmetic, based and volatile-pointee forms did not produce the target's `push ES:[BX]` (_win_ModeControlClosed/_win_CasteControlClosed, U3).

**MSC7-P5: what triggers an early `LDS`. OPEN.**
- The admitted `_PointInRect` and `_FlipWords` use DIRECT far parameters and get `LDS`; adding an alias breaks them.
- A minimal far-source walk produced no `LDS` under any profile.

## 6. Data and literals

**MSC7-D1: string literals are packed back to back in `_DATA`, while named `char` arrays of odd length are word-aligned. SUPPORTED.**
- `_SetPause`/`_PauseGame`: the target's two menu strings sit 17 bytes apart (0x900/0x911). Named arrays gave offsets 0/18; struct and single-array forms keep the spacing but change the code (build/workers/f-pauseunit/REPORT.md).
- Open question: how three functions share one copy. Answered for `_SetPause`/`_PauseGame` by a steered label split (admitted EXACT_STEERED, 2026-09-28).

**LINK-D1: private far data in a packed data segment is file-backed zeros; communals are not. VERIFIED.**
- Setup: MSC 7.00 `/AL /G2 /Gs /Oelw` with LINK 5.30 `/PACKDATA` and the original SIMANTW.DEF segment order.
- Private `PACK FAR_DATA` contributions sit in the NE file as zero bytes inside the segment's file length. This holds for `__based(__segname("PACK"))` statics and commons, whether uninitialised or `= {0}`, placed in link input order with word alignment.
- COMDEF `FAR_BSS`, and default `static far`/`huge` data (`INPUT5_DATA`, paragraph-aligned), come after the file range. They add only to the minimum allocation.
- Reproducer: `evidence/experiments/commdata-layout/reproduce.py`, 8 variants with controls.
- Applied: the LZSS encoder state `lson[N+1]`, `rson[N+257]` and `dad[N+1]` (N=4096). These are private `PACK` arrays following `pack_buf` at `1016`/`3018`/`521A`, where the admitted `DeleteNode` indexes them. That data module owns 25,094 zero bytes.
- Zero content alone never establishes an owner: the offsets must come from code that indexes them.

## 6b. Steering

**MSC7-X1: code-free constructs the optimiser deletes steer home order or register choice. FALSIFIED.**
- Tried: a self-read `(void)x;`, a self-comparison, a discarded `&x`, and a compile-time or loop-invariant dead guard.
- Result: across `_AnimYellowFight`, `_CarpetFloorR`, `_win_ClearGroupAreas`, `_win_DrawGroupObjects`, `_DoToAlarm`, `_DoRandAntAA`, `_DoDigOutAntA`, `_YellowFight`, `_DoNestingR`, `_DrawCastePopUp` (f-slotsteer) and `_MowerFall` (f-study-e16), every such construct compiled to the IDENTICAL object, each with its assigned profile.
- MSC 7.00 allocates homes and registers after these constructs are gone.
- A construct that survives into the code, such as address-taking or `volatile`, changes the allocation but also the bytes, and in every case tried it lowered the match.
- Consequence: for allocation-only residues, EXACT_STEERED needs a construct that changes the compiler's intermediate state without surviving in code, and none of the tested kinds does. The allocation is decided by which live values exist and how they are used (F2, F3, F1F, R1–R3).
- Evidence: `evidence/codegen-facts/MSC7-X1/` (probe reports), build/workers/f-slotsteer/REPORT.md.
- Validated 2026-09-27.

**MSC7-X2: a named temporary for a subexpression in ONE branch (`value = mapX << 5; return T[value + mapY];` beside a sibling arm that indexes inline) can change the register schedule of the whole function, and it survives into code, unlike X1 constructs. SUPPORTED (one admission).**
- Found by tools/permuter.py on `_GetSmellT` (`baseline /NTSIMANT1_MODULE`). It took the draft from 45/46 to body-exact; admitted as EXACT_STEERED in `simant1_9612_scaffold` (2026-09-27).
- Contrast E18: in straight-line code a temporary disappears. Here it sits in one arm of a branch whose other arm computes the same subexpression inline.
- Consequence: allocation residues respond to the placement of temporaries and subexpressions, which the permuter's introduce/inline-temporary mutations explore.

## 6c. Toolchain and profile

**MSC7-T1: untested optimisation letters, or a different profile, explain the single-choice residues. FALSIFIED.**
- Sweep: the frontier drafts of 24 single-choice residues (register, home order, reload, expression, far pointer) were compiled with each function's assigned profile plus `/Oa`, `/Os`, `/Ot`, `/Oc`, `/Oo` or `/Oz`, and with `/Ow` removed.
- Result: none became exact or moved its earliest divergence later.
  - `/Os` changed 21 of 24 and made 20 worse; dropping `/Ow` changed 8 and made 5 worse.
  - `/Oa`, `/Ot`, `/Oc`, `/Oo` and `/Oz` changed nothing.
- Together with the MSC 6.00A generation sweep (evidence/experiments/compiler-generation: 0 of 186) and residues spread across profiles in proportion to the admitted functions (baseline 68/411, og 37/208, ogi 21/112), the locked toolchain and catalogued profiles are not the cause.
- Evidence: `evidence/codegen-facts/MSC7-T1/` (sweep script and per-variant results); the diagnostic compiles never entered the draft ledger.
- Validated 2026-09-28.

**MSC7-T2: CL passes pass-2 options to C23216 only through `MSC_CMD_FLAGS`, and `/d2...` debug options are not forwarded (D4002). SUPPORTED.**
- A real captured value: `-ef c23.err -il <tmp> -A lfd -Bm 2048 -Oc -Oe -Ol -On -Ot -Ow -G2 -NT _TEXT -W 1`.
- C23216's own option table (raw ~0x5863e) also lists `-db# -dt# -pr -nogen -pathgen`. These can only be reached by invoking C23216 directly.
- Allocator modules named by asserts: `globregs86.c`, `glregs86.c`, `reg86.c`, `regMD.c`.
- Evidence: f-study-c2 (worktree simantw_wt_c2). Direct invocation is being tested (f-study-c2b).

## 7. Unexplained residuals

- **U1 `_WaitHundredths`**: 22/22 opcodes. The long add uses AX:DX where the target uses CX:BX.
- **U2 `_GtRegisterClass`**: the statement `wc.windowProc = GTCLIENTWNDPROC;` alone adds a 26-byte hidden temporary (ENTER 0x68 vs target 0x4E). Pascal prototypes, casts and a same-file definition do not remove it.
- **U3 `_win_ModeControlClosed`**: the target is the P2 shape: the pointer is homed at the deepest slot, test and push use ES:BX, and LES happens after the call. A plain local folds to the constant address (51/54). `int far * volatile p` gives the target ENTER 0x10 but adds a reload before the push and homes p nearest to BP (49/53; `build/probes/f5-modecontrolclosed-volatile`). Open: the non-volatile form that stops constant folding.
- **U4 `_MowerFall`**: the target clears AL before two stores; the candidate reuses a known-zero BH (C12 candidate).

## 8. Invalid evidence (do not cite)

- **`_FillMap` `[bp-8]` experiment (2026-09-27)**: the probe was compiled with `baseline /NTSIMONE_MODULE` instead of the assigned `ogi`. It showed a "second register local gives ENTER 8" effect, whose extra slot was a used home, not an untouched one. It says nothing about L7.

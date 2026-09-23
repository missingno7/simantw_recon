# Supervisor lessons for bounded recovery

Use this checklist on a new MATCH_READY target before its first test. It does not authorize reopening parked jobs or changing the proof rules. Live queue, ledger and job evidence remain authoritative.

## Choose declarations before expression variants

1. Read `direct_data_bindings`. Use an exact MAPSYM name when available, checking the packet's DS-frame assumption. An unnamed operand is not evidence of an external symbol.
2. Identify what the accesses require: word, long, pointer, array, or separate objects. Check readers, writers and initialization where available. Distinguish a two-word long operation from two independent handles.
3. For apparently private state, consider a natural `static` declaration with the observed type and an evidence-backed initializer. State this as a hypothesis until complete-member proof succeeds. Do not fill address gaps with padding arrays, fabricate a public name, or use numeric address casts.
4. Keep named external state external. A nearby symbol is not permission to index into unrelated storage. A far offset requires selector evidence; equal offsets do not establish equal objects.
5. Explain the declaration in the candidate's semantic comment. The strict matcher must check the entire private contribution, including initial bytes, placement constraints and semantic fixups. A matching instruction body alone proves none of these.

Two fresh admissions illustrate the distinction:

| Target | Old draft | Successful declaration | Evidence |
| --- | --- | --- | --- |
| `_DrawForSale` | Invented `extern int near forSaleObject` | `static int near forSaleObject = -1;` represents the missing-object sentinel | [Source](../evidence/topology/supervisor-private-state/DrawForSale.c), [strict experiment](../evidence/recovery/workflow/jobs/DrawForSale-956dc12b43/attempt03/results.json), [fresh admission](../evidence/recovery/workflow/jobs/DrawForSale-956dc12b43/promotion.json) |
| `_MSClipEnd` | Invented external palette/object handles | Two private `static int near` handles, with the named window and DC still external | [Source](../evidence/topology/supervisor-private-state/MSClipEnd.c), [strict experiment](../evidence/recovery/workflow/jobs/MSClipEnd-48c3851864/attempt02/results.json), [fresh admission](../evidence/recovery/workflow/jobs/MSClipEnd-48c3851864/promotion.json) |

Each succeeded in one new supervisor experiment. These examples establish useful hypotheses for future targets, not historical TU boundaries or permission to copy their declarations indiscriminately.

## Let the mismatch select the next experiment

| Observed evidence | Useful next step |
| --- | --- |
| Wrong branch, constant, call or missing store | Trace the relevant target paths and correct semantics before searching compiler forms. `_GSetAttrib` needed its common store on both paths. |
| Register-only differences with correct fixups | Investigate pointer induction, live ranges and caller-supported types. State which instruction should change; do not repeat exhausted declaration-order matrices. |
| Wrong pointer loads, stack cleanup or segment use | Inspect caller argument layout and the actual imported ABI before changing prototypes. |
| `ESCALATED` / `BODY_MATCHED_BINDING_BLOCKED` | Preserve the body and move to `next`. Supply the data evidence to a supervisor; do not resume expression search or invoke expert reissue. |
| Unknown indirect CFG or ambiguous extent | Retain the structural blocker. Table bytes, guards, all targets and cross-entry evidence need independent review. |

Known negative results are in [stale-blocker-review.json](../evidence/topology/stale-blocker-review.json). In particular, SRand's shift/carry semantics, MemRChr's starting-pointer convention, and ClearBuffer's string ABI are unresolved research questions. Do not copy their old drafts as established semantic templates. Historical compiler patch identity alone is not a reason to stop.

## Make escalation actionable

In the blocker reason and next experiment, record:

- The best candidate and report paths, and the remaining attempt/candidate budget.
- Whether extent, ordinary instructions and fixups match; identify the first actual difference rather than only a similarity score.
- For data: exact operand locations, named bindings, selector evidence, observed widths and any known initializer or array bound. Mark unknown boundaries explicitly.
- One new experiment and the observation that would distinguish it from failed attempts. Link the old negative evidence so the next supervisor does not repeat it.

Continue ordinary grinding after parking the job. Only an expert with new evidence should use `topology_retest.py`, which preserves budgets and prior attempts; fresh independent admission is still required.

## Follow-up supervisor evidence

Three more private-state cases passed fresh admission: [RallocFree](../evidence/recovery/workflow/jobs/RallocFree-a82b13cb86/promotion.json), [Punt](../evidence/recovery/workflow/jobs/Punt-840c7657cd/promotion.json), and [printf](../evidence/recovery/workflow/jobs/printf-41e459f08e/promotion.json). The observed initialized data supports a zero-initialized unsigned long counter, the NUL-terminated caption `Fatal Error`, and the NUL-terminated format `%s`, respectively. [Operand evidence and hypotheses](../evidence/topology/supervisor-private-state/initialized-data-evidence.json) accompany the source. Each required one new compile experiment before fresh admission.

The [SRand audit](../evidence/topology/supervisor-srand/semantics.json) exhaustively checks all 65,536 seeds. A widened unsigned transition is equivalent to the observed carry-based transition; testing the post-shift sign instead is wrong for 32,768 seeds. The [single compiler probe](../evidence/topology/supervisor-srand/probe/results.json) does **not** match: it materializes the high word and uses a six-byte frame instead of two. [Review and next evidence needed](../evidence/topology/supervisor-srand/review.json). Do not expand that failed expression into a family-wide variant search. No SRand recovery credit was added.

## Far globals and selector pools

Inspection packets now include local ES operand hints inside `direct_data_bindings`: `addressed_segment`, `selector_slot`, `selector_load_instruction`, exact MAPSYM names, and index registers. The hint follows a direct ES load from a non-additive NE selector slot and stops at calls, branches, branch entries, gaps, interrupts, and writes to DS/ES. LES reads use the previous ES, then invalidate it. These are local observations with explicit DS/incoming-entry assumptions, not proof of whole-function segment liveness or object bounds.

The [named far-operand index](../evidence/topology/supervisor-far-names/named-far-operands.json) records this pass's observations. Prefer packet names over invented arrays or synthetic structs sized to absolute offsets. A recovered name may change the semantic interpretation: FollowCatDir reads DogPx, DogPy and YardCycle; its frozen names suggested unrelated cat state.

The [four controlled named-object probes](../evidence/topology/supervisor-far-names/bindings.json) resolved eleven object offsets but did not recover the complete members. FollowCatDir, SendBoyMsg, StartAttack and SetAntLion still have private CONST selector-placement conflicts. Complete contribution proof requires the actual selector ordering and spacing; equal target segments do not permit relocating, coalescing or padding the candidate's selector slots. Consult their latest job evidence before attempting TU reconstruction.

## Named private far data: multimedia result

The [multimedia supervisor pass](../evidence/topology/supervisor-mm-segment/review.json) independently admitted IsMMWaveAvail and IsMMMidiAvail. Both use a private initialized word declared with MSC's `__based(__segname("SIMANT_DATA_GROUP"))`; the segment is independently identified by the original NE selector. This expresses a real named segment without absolute array indices or padding. The complete initialized word and selector contribution are verified. This does not establish the whole sound-state object's boundary or original TU ownership.

The member matcher now supports OMF F5/T0 private offset constraints: F5 uses the target segment as its frame, equivalent here to an explicit F0 frame naming that same segment. See the [TIS OMF specification](https://refspecs.linuxfoundation.org/elf/TIS1.1.pdf), printed pages 44-45. A unique original MAPSYM segment name is still required. Wrong/ambiguous names, conflicting placements, wrong/missing/additive selectors, changed data/body bytes and out-of-bounds contributions remain rejected; eight new regression tests cover these obligations.

The later fourteen-member gr:7712 unit in `evidence/experiments/mm-state-structure/` matches a 22-byte shared state and three further sound routines, `_snd_IsSongDone`, `_MultiMediaSong`, and `_CheckMMWave`. It uses a const `__segment` selector and a based view of the same state object; the earlier scalar, aggregate and far-lvalue trials remain negative controls, not a general license to combine fields by offset. The four earlier PACK selector-pool placement conflicts also still reject under the updated matcher. Preserve those negative results. `_CheckMMWave`'s inline `strlen` comes from source-local `#pragma intrinsic(strlen)` under the baseline flags, not a unit-wide `/Oi` assignment. Its target import is KERNEL ordinal 134, `GetWindowsDirectory`. Four shared near strings and an odd-address `"MMSYSTEM.DLL"` literal are evidenced by the complete unit; combining them into one named string object caused a placement conflict.

## Supervisor review after tool changes

Doctor now reports stale tool context on active jobs. For an OPEN job with **zero attempts**, no pending attempt, unchanged fixtures and unchanged non-Python protected inputs, a supervisor may use:

```powershell
python tools/topology_retest.py JOB --refresh-unattempted --reason "Concrete reviewed tool changes and validation evidence"
```

This requires current successful handoff validation (including all current Python tools/tests) and independently verifies the existing complete manifest. It archives the previous job context and source/submission identities before refreshing computed tool fingerprints. It preserves source, status, attempt budget and recovery credit. It refuses attempted, running, exact-candidate or pending jobs. Ordinary grinders must not invoke this expert maintenance path or edit hashes themselves. Attempted jobs still require a new evidenced experiment through the existing expert reissue workflow.

The multimedia pass used this path to restore the previously OPEN PackMemoryToMemory job after the matcher change; its source and zero-attempt budget were preserved. Final handoff validation passed 138 tests and doctor returned READY_FOR_BOUNDED_HANDOFF.

## Whole-member diagnostics and named state

The [next supervisor pass](../evidence/topology/supervisor-preload/review.json) admitted DoPreLoadInits, IsItFood and YellowHelp. DoPreLoadInits needed three named 32-bit timing values in place of synthetic padded structs. IsItFood needed PACK's TERRAINset, not a large index into Dx8 in a different segment. YellowHelp needed the exact MeMode binding while preserving its already matching local-long expression shape.

Diagnostics now expose `unresolved_member_obligations`, including failing private contributions and original NE loader targets beside candidate targets. The compact text diff also starts with these whole-member failures. [IsItFood's preserved negative example](../evidence/topology/supervisor-preload/IsItFood-old-diagnostic.txt) has no instruction differences yet shows candidate selector segment 8 versus original segment 9. A resolved offset or clean body diff cannot establish the live segment or discharge private selector contributions; always read the complete-member result.

Preserve a matching body when correcting bindings. The YellowHelp inline-conditional probe added a stack temporary, whereas simply renaming the original declaration to MeMode produced exact admission. Declaration identity and expression shape are separate hypotheses.

The [segment-access and boolean scheduling review](../evidence/topology/supervisor-based-pack/review.md) preserves further negatives. Named PACK based externs do not reproduce ClrModePop's immediate selectors and DS restoration. InitSpider's nonzero expression produces CMP/SBB/INC, but scheduling and register use still differ despite equal contribution size. Neither is recovered; avoid repeating these declaration/type experiments without new evidence.

## Reconstruction rules from the build model

`layout/reconstruction-rules.json` is attached to every inspection packet (`reconstruction_rules`) by observed triggers. The rules in force:

- LINK may rewrite same-segment far calls (NOP; PUSH CS; CALL near); write ordinary far calls.
- Declaration order can determine DS versus ES code generation; the CONST selector pool follows first-reference order across the whole unit, so a function's pool conflicts in isolation are unit work, not body work.
- Named ant-list fields may share one segment-8 selector slot. That proves a shared segment selector in that function, not one `Dx8` array; preserve each observed field displacement and establish object identity from unit evidence.
- Parameters copied into locals can be required when the historical code holds values in SI/DI.
- Explicit result variables reproduce historical `MOV DX,1` return tails.
- Arrays are frequently word-indexed; preserve the observed element width.
- Never invent a convenient symbol when MAPSYM provides the real one: `win_hwnd[25]`, not a private `yardWindow`.
- A matching numeric offset does not establish object identity; far-object identity requires selector/segment evidence.
- Private state is natural `static` data with an evidence-backed size, type and initializer (a BSS word can only live in the original BSS region; `MakeClip`'s tile mask was initialised data, never an uninitialised array).
- Preserve an already matching body while solving its unit/data binding (`tools/tu_assembly.py`).
- The compiler profile belongs to the unit context; report a code shape that only `/Og` explains as unit evidence instead of trying switches.

Four earlier admissions (`DrawYard`, `UpdateYard`, `DoDebugWin`, `MakeClip`) had passed with a private BSS word bound into the win library's `win_hwnd[]` or an unchecked initialised mask; the BSS-region rule now rejects those drafts and they were re-admitted with the real declarations (`evidence/topology/supervisor-bss-region/`).

## Switch jump tables (2026-09-22)

`tools/cfg_solver.py` proves MSC 7 `switch` dispatch tables from the exact idiom only (`cmp ax,N ; ja default` or `cmp ; jbe shift ; jmp default`, `shl ax,1`, `xchg bx,ax`/`mov bx,ax`, `jmp word ptr cs:[bx+T]`, plus the strength-reduced `and ax,M ; shr ax,k` index when the mask proves every index even), with the table directly after the jump (up to two alignment NOPs), every entry inside the symbol and no loader obligation on table bytes. 40 functions moved from STRUCTURE_BLOCKED to MATCH_READY; only the interrupt code `_DoInt3`/`_NetBIOSPost` stays structurally blocked. Cards show the table words as `dw offset X` rows and `codegen_diff` compares them as case targets, so opcode counts are meaningful again for these bodies.

Lessons from the first switch-table admissions (`DoUserButtonUpdate`, `UpdateUserButtons`, `ProcEditEvent`, `SetUserButton`, `DoTool`, `DoAntSimY`, `DoNestFightB/R`): write the plain dense `switch` with exactly the table's case labels; holes are absent cases; an out-of-range value that shares the common tail is not an early `return`. `InitYelloAnt` (attempt 8) showed two further `/Og` facts: a far global read twice becomes a CSE temporary with a frame home below the declared locals (do not declare a local for it), and `je` over two stores means both belong to the branch.

Negative evidence from wave 2 (SIMANT1 colony objects, SIMONE dig/patch objects): the recurring residue "parameter kept in DI while the cell index gets a frame home" (`DoDrownB`, `DoDigInB/R`, `DoFoodInB/R`, `DoNestFightB/R`) and "dead frame write-through retained across a call" (`MakeSink`, `DigTileThemB`, `MakeNewHoleB`) is not a profile effect: raw probes under `/Oglw`, `/Olw`, `/Oel`, `/Oegl`, `/Oelws`, `/Oelwt`, `/Oael`, `/Ox` and without `/G2` all regress or leave the residue unchanged (`build/experiments/profile-*`). `register` parameters have no effect under `/Oe`. These remain source-shape questions; do not spend profile budget on them.

## Scaffolded units (2026-09-22)

Exact bodies no longer wait for every introducer of their object: `tu_assembly.py build C --members ... --scaffold --harmonize` reproduces the unclaimed members' selector-pool order with stand-ins in the reserved `POOLSTUB_TEXT` segment (never compared, never credited) and admits the claimed members on their own bytes. 31 parked exact bodies became admissions this way (417 -> 447), including whole colony objects (simant1:2D4E/5344/0000/75F4, simtwo:0000/1378/4CDC/3EF8, antedit:00F4/7022, simone:5AD2, simant:5530/6A38, gr:611C). Two admitted isolated recipes turned out to bind the wrong object and were superseded by the unit: `OverlayTileSet` addressed its private terrain-set state word (SIMANT_DATA_GROUP 0x8DF8, its own selector word) as `editBufInvalidFlag[1]`; the unit showed two pool words bound to one symbol. The `AddRandAntLion` candidate that swapped `Dx8`/`Dy8` is no longer counted as an exact body: `preserved_sources` accepts only bodies the binding classifier accepts (every differing literal an unresolved offset binding). For grinders this means: an exact body is now worth an admission even in a 40-public object, so `BODY_MATCHED_BINDING_BLOCKED` escalations are the goal, not a parking state.

`_DrawDog` showed that an indexed expression such as `dogRunX[DogFrame - 12]` can put a negative 16-bit addend in an OMF DATA fixup. That addend is not an offset near 65536 into the candidate DATA segment. The unit composer now accepts a placement only when initialized bytes uniquely cover each inferred piece and the entire contribution; ambiguous or all-zero cases fail closed. It also skips selector-pool stand-ins when the claimed member uses no pool slot and avoids classifying mixed static DATA as a literal solely because it ends in NUL. The admitted reviewed unit preserves five named dog statics; its measured intervening data spans remain noncredited context.

`_win_SetObjBitmap` is a different DATA case: its first `Punt` argument is DGROUP BD12, and target calls in `_win_ObjAddr` and several other window routines push the same offset. Its second message is at BDDA with unrelated initialized objects between. Authentic C7 duplicates identical function-local literals even within one translation unit. A named static keeps `_win_ObjAddr`'s complete member exact; referencing it externally in `_win_SetObjBitmap` leaves only that BD12 binding unresolved while its BDDA private message becomes exact. The shared declaration and full intervening DATA context still need a combined proof; see `evidence/experiments/window-string-identity/`.

For `_YardArea`, target DGROUP 18B6 is `patchRgn2[9]`: MAPSYM puts `patchRgn2` at 18A4, and admitted `_DrawYardCursor`/`_EraseYardCursor` already use that element. The parked draft's `yardPatchShown` external was a wrong object identity even though its code shape matched. A reviewed source with the shared field passed a complete selector-pool unit and then a combined three-member unit. The composer now takes its later member source from the current admitted unit's identity-checked source record, so a new composition cannot silently revert to the historical parked draft.

`_DrawYardData` shows why an overlapping private-DATA inference can be a source error. Its parked body had three `"%3d"` formats, while target call operands at DGROUP 18C2, 18C6, 18CA, 18CD and 18D0 address two `"%-d"` and three `"%d"` strings. The 18-byte candidate string pool could not fit the 17 target bytes; correcting the three literals alone made the whole code, DATA and CONST contributions exact. Inspect initialized bytes and every offset binding before treating a composer overlap as a missing object-boundary rule. The corrected source also passed a combined unit with `_YardArea`.

`_initControls` shows that a selector word numerically inside a claimed member's pool span can belong to an earlier public. `_ProcModeEvent` reads C142 and C144 at direct `MOV ES,word ptr` sites, and both words have NE selector relocations; `_initControls` reads C142 again but never C144. Because `_ProcModeEvent` had no topology size, the old composer attributed the gap to the later body. A reserved stand-in for the earlier public now allocates both words, and the complete `_initControls` member and CONST block match. The stand-in's segment-8 representative for C144 is not a recovered historical object identity.

## Declaration order, invented names and bogus offsets (2026-09-22, lane 1 continuation)

- **Commutative operand order is declaration order.** MSC 7 canonicalises `a * b`, `a + b` and `x < a + b` regardless of how the source spells them; which global becomes the memory operand (`imul word ptr [b]`, `add ax,[b]`) is decided by the order the two externs were declared. `PreDrawSpider` (`tileWidth * editWidth`), the four colony `EatFood/TryEatFood` members (`BpopT + CastePopB[2]`) and the antedit balloon members (`MapPnt.x + editWidth`) all needed a declaration swap and nothing else. Rewriting the expression does not help. In a unit the order is a TU-level fact: record the pair in `layout/declaration-order.json` (applied by `tu_assembly.compose`), never by hand-editing a unit source. Rule `commutative-operand-declaration-order`.
- **`Symbol[0xNNNN]` is not a binding.** A candidate that reaches the original bytes with `AlwaysHealthy[0x4530]` (adding the symbol's own MAPSYM offset to the symbol) or an invented name (`BalloonModeFlag` for `OptionStates[5]`) is not an exact body: the strict matcher flags every such fixup as wrongly resolved (`body_exact` rejects it) and a unit cannot resolve an invented name. Name the far scalar (`extern int far AlwaysHealthy;`) or the real MAPSYM owner and index (`OptionStates[5]`, `_OptionStates` 0x85F2 + 10).
- **`struct T { int x, y; }` and `struct T { int x; int y; }` are one tag.** The composer now compares struct layouts (`struct_key`), so a tag spelled differently by two exact sources no longer produces a `_2` rename plus a `(*(struct T far *)&Sym)` view macro, which changed the code of every member using the object.
- **A member calling an unnamed static helper cannot be claimed by a unit** until the helper is recovered as a static function of that unit (`UpdateEditIfBufInvalid` calls ANTEDIT_MODULE 0x16D4; the candidate's local `near DrawEdit` stub misbinds it). `scaffold_plan` drops such members (`helper_blocked`) instead of failing the unit.
- **simant1:0000 compiles under `og`** (`asg-simant1-0000-og`): `DoFightA` and `DoReturnFoodAnt` only approach the original under `/Oeglw`; the 15 parked members of the object were profile-reissued and are back in the ready pool with the agentOBJ idiom catalogue (return-block layout, duplicated tails, first-assigned local gets the register, the inline `IsItHole` chain, separate zero stores) in `docs/near-exact-lane.md`.

## LZSS selector object and private zero data (2026-09-23)

- In the SIMTWO tree routines, `unpackHandle` is a far pointer **stored in a near DGROUP object**. With `/AL`, `extern void far *unpackHandle` makes the pointer object far and C7 first fetches its selector through CONST. `extern void far * near unpackHandle` emits a direct read of its selector word at DGROUP 0xB8DE. The [small authentic probes](../evidence/experiments/lzss-segment/README.md) and `_InitTree` attempt 9 establish that declaration issue; they do not establish the original tree-field declarations. `_DeleteNode` attempt 7 shows that based C accesses still use ES, unlike the target's one-time DS switch. Resolve that context before tuning the long algorithm.
- An all-zero two-byte private `_DATA` piece may be a static word. The prior unit data classifier could call it a string literal and move it after another object's bytes. `_DebugWinPrintf`'s flag at DGROUP 0x8F2 exposed this: keep such ambiguous bytes static and determine neighbouring contribution order from code fixups and target data. Its two referenced strings at 0x8F8 and 0x8FA are both `CR`, as is the four-byte intervening unclaimed data at 0x8F4. The reviewed scaffolded unit now matches its full code, fixups, and private data; the scaffold function itself is noncredited.
- `_db_SetDataBase` gives a second confirmed data-order case: its initialized flag is at DGROUP B1EA, an earlier unclaimed `%s.dat` occupies B1EC–B1F2, and its own format and error literals begin at B1F3 and B1FA. A reviewed unit with only the prior seven-byte literal in reserved scaffold code matched the complete function, private DATA, and CONST. This supports measured stand-ins for actual unclaimed contributions, never arbitrary padding.
- Three pause-menu routines read exactly the same two strings at DGROUP 0900 and 0911. Simply combining their preserved literal-bearing C emits three copies. Two separate named statics insert a padding byte; one flat array or a two-field char struct keeps 32 data bytes but changes conditional pointer code. The [bounded C7 trials](../evidence/experiments/menu-string-identity/README.md) rule out those spellings under the assigned profile. Keep the body matches as hypotheses until shared string identity and the direct `mov ax,offset` source form agree together.

- The `_GSetSmallFont`/`_GSetBigFont` pair exposes a BSS boundary issue, not a long DATA gap. DGROUP CC54 lies above `_edata` CA60. The target shares a two-byte word at CC54 but uses separate byte scratches at CC56 and CC57. Explicit `= 0` definitions placed the candidate words in `_DATA`; tentative zero definitions placed them in `_BSS`. Splitting the byte scratch and restoring the target TEXTMETRIC field expressions matched the two complete members, 41 DATA bytes, two CONST bytes, four BSS bytes, two PACK bytes, and every fixup. The old reviewed unit had swapped the two calculations even though the preserved individual bodies had them right; read target stack offsets rather than trusting a reviewed comment. [Evidence](../evidence/experiments/font-bss-context/README.md).

## Bitmap row stride and far-pointer ABI (2026-09-23)

`_DoFastMonoBitmap` matched after its eight-attempt production budget through
one evidenced `SOURCE_LAYOUT` reissue. The decisive target signature was a
long division helper followed by long multiplication at the same two call
sites where the preserved draft emitted them in reverse. NE records relocate
only the far-call selector halves; inspect the ordinary offset words and
MAPSYM names before concluding both calls target segment offset zero. The
historical computation divides rounded row width before multiplying height.
Its source bitmap argument is one far pointer: the original pushes its two
stack words directly, whereas a source with separate offset/segment words
loaded AX/DX first. An explicit shared cleanup label reproduced the jump
past the handle check after `mem_Unlock`. The final object matched the whole
member, all 11 fixups and its private `bm` literal under fresh admission.
[Full experiment and negative controls](../evidence/experiments/fast-mono-helper-order/README.md).

When a future bitmap candidate has correct call sites but wrong arithmetic
helper order, compare the source operation order before changing compiler
profiles or treating a selector-only NE relocation as a missing helper.
Apply the far-pointer and cleanup observations only where the target's stack
and branch evidence agree.

The independent `_win_SetObjVisibleState` research confirmed the relocation
point in another group: call-offset bytes for `_GRectInv` (0x0EB2) and
`_GSetAttrib` (0x19B4) match MAPSYM even though their NE selector records
name segment 2 offset zero. A signed `char` local reproduced its `cwde`
dispatch sequence; the complete function remains blocked on other code and
selector differences. [Scoped evidence](../evidence/experiments/win-visible-state-call-offsets/README.md).

The next bitmap member, `_DoFastBitmap`, independently reproduced its target
long-division-then-multiplication helper sequence using the rounded row-stride
expression. It remains blocked later in its Dx8 conversion. An isolated
plain far-pointer alias still emitted seven `_Dx8` offset fixups, whereas the
target uses two selector loads and indexed ES reads. That negative applies to
the tested alias under this component's baseline profile, not to all pointer
representations. [Research note](../evidence/recovery/workflow/jobs/DoFastBitmap-e1a0ad76d1/isolated-research.md).

### Mine an admitted sequence in neighboring members

`_PrepareStrings` matched on one readable hypothesis: eighteen consecutive
`LoadStringAnt` calls assigned to named far string-table globals, including
all 90 fixups. The adjacent `_initStuff` packet began with the same eighteen
calls and stores; reusing those statements and reconstructing only the
startup tail matched its full 576-byte body and 109 fixups on its first test.
The latter target reads an unwritten stack local on its failure path, which
the source preserves explicitly. This is a local observed clone, not an
assumption that all startup functions share a translation unit. See the
[first source proof](../evidence/experiments/prepare-strings/README.md) and
[reuse proof](../evidence/experiments/init-stuff/README.md).

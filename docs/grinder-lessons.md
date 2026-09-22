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

Do not generalize this success to multi-field codegen automatically. MultiMediaSong's scalar, aggregate and far-lvalue forms all change selector loading and branches; its remaining blocker is recorded in the job. The four earlier PACK selector-pool placement conflicts also still reject under the updated matcher. Preserve those negative results.

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
- The ant lists derive from one real `Dx8` object where selector evidence establishes it.
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

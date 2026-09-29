# Recovery workflow

The everyday path is **context → search → promote**, with complete validation at acceptance or tooling boundaries. The working compiler is MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw /NT<original code group>` unless the symbol's object context has a catalogued, evidence-backed profile. Read [recovery lessons](grinder-lessons.md) before a new target's first search.

```powershell
python tools/context.py --list --open            # unrecovered functions, closest drafts first
python tools/context.py _Symbol                   # full working packet (--brief, --history)
python tools/search.py _Symbol build/workers/me/a.c build/workers/me/b.c [--meta round.json] [--note "..."]
python tools/search.py _Symbol build/workers/me/a.c --pool  # add supported component selector-pool context
python tools/promote.py _Symbol build/workers/me/b.c [--verify-only]
python tools/validate.py
```

Commands print JSON on stdout; compiler progress goes to stderr.

- **context** is read-only. The packet has masked disassembly with loader bindings, basic blocks, calls, globals, `direct_data_bindings` (exact MAPSYM names, selector slots, addressed segments and the DS-frame assumption), the compiler profile, `unit_context`, `unit_declaration_order`, relevant `reconstruction_rules`, similar admitted functions, the best preserved draft, notes and legacy job summaries. `structural_extent` reports whether the closed CFG extent is independently confirmed. That is informational: admission checks the complete original scope itself.
- **search** compiles any number of files in one round under the symbol's profile, runs the strict member matcher and the instruction diagnostic, and ranks the results. It has no budget, duplicate-experiment refusal, job state or eligibility gate, and old blocker labels never block it. Output goes to `build/search/SYMBOL/<run>/` (sources, `.diff.txt`, full `results.json`) and a per-symbol `history.jsonl`. When a candidate outranks the stored draft (strict, then exact body, then aligned opcodes, then size delta), it is copied into the durable ledger `evidence/recovery/drafts/`. `--template spec.json` runs a controlled equivalence-class batch (`codegen_grinder` template/axes). `source_warnings` lists anything promotion would reject.
- **parking** (`python tools/parking.py candidates`, `python tools/parking.py park SYMBOL --class CLASS --reason TEXT`, `python tools/parking.py reopen SYMBOL --because TEXT`, `python tools/parking.py list`, or `python tools/parking.py status`) is evidence-gated assignment metadata. A candidate needs a classifiable first divergence and either two latest readable search sessions, both newer than the stored frontier timestamp and neither exceeding its `drafts.frontier_rank`, or the configured number of notes recorded after that frontier (default 10). `context.py SYMBOL` displays the record. Fleet planning excludes active parked functions and reports them; `search.py` and `promote.py` remain available for any function regardless of parking. Reopening one symbol or a whole blocker class requires `--because` to record the new fact or tool.
- **permuter** (`python tools/permuter.py SOURCE.c --function _Symbol`) explores randomized semantics-preserving body mutations for a near-exact member. It compiles batches with the symbol's assigned profile, applies the strict member matcher and fixup-aware instruction diagnostic, and writes evidence under `build/permuter/`; it never changes the draft ledger or promotes a candidate. See [permuter details](permuter.md).
- `search.py --pool` is an optional C-search context for components with a reviewed map in `evidence/experiments/pool-maps/`. It places one `POOLSTUB_TEXT` stand-in before the candidate and gives it one distinct far reference for each earlier selector relocation in the dense component range. It uses the relocation inventory to skip ordinary `CONST` holes. Resolved words use their mapped far symbol; unresolved words use the same segment-correct distinct-name fallback as TU scaffolding, avoiding names already declared by that candidate. The candidate's own selector words must form one contiguous ascending block and be covered by the component map. The mode declines components without a map, missing relocation evidence, incomplete maps and candidates whose own words are split across blocks or out of order; use the whole-unit scaffold lane for those layouts. Each candidate in a multi-file search gets its own safe stand-in names. The strict matcher skips only `POOLSTUB_TEXT`, while candidate code, selector fixups and private contributions remain compared as usual. It does not synthesize or reposition `_DATA`/`_BSS`; those still appear as strict placement constraints. Derived sources stay under `build/search/`; the durable draft remains the original candidate source. Results say whether the prefix was applied and report the component, map, prefix words and unresolved words. Pool-aware results are diagnostic and do not change promotion rules.
- **promote** freezes the source into `src/recovered/`, compiles it fresh, and admits it only if full original/candidate scope, public placement, ordinary bytes, semantic fixups, private contributions and ownership all check out. It re-verifies the complete manifest before and after. Publication holds one OS lock and a journal (`build/publication.json`), and `--recover` rolls back an interrupted publication without overwriting later edits. The proof goes to `evidence/recovery/promotions/<id>.json` and records the proof-tool identities. `--verify-only` runs the whole gate, also for an already admitted control, without publishing.
- **unit compose** (`python tools/tu_assembly.py compose OBJECT --add SYMBOL=FILE.c`) extends the latest frozen admitted unit source at the member's original code position. It preserves admitted function bodies and tests a bounded set of placement-only arrangements for statics/literals, shared strings, member order, and existing `POOLSTUB_TEXT` stand-ins/fillers. Each trial records the strict unit comparison, placement diagnostics (including selector-pool slot names), and the selected source with provenance. Add `--persist` to keep a strictly passing arrangement as a unit record (`evidence/recovery/units/<component>_compose_<hash>`, an id that never collides with another worker's diagnostic unit); the result prints the `promote.py --unit` command that publishes it. A placement arrangement that exists to steer allocation, such as a label split, must be declared `EXACT_STEERED` with its construct named; see [build topology](build-topology.md).
- **validate** runs the unit/negative tests, independently re-verifies every admitted object (`build/recovery/verified-objects.json`, totals in [progress.json](progress.json)), checks the profile catalog, replays an exact control through the compiler cache and checks the persistent-service evidence.

Similarity scores, diagnostic ranks, structural certificates and scaffold stubs never grant credit.

## Whole binary: image ledger and lanes

`python tools/image.py` rebuilds all 516,096 bytes of SIMANTW.EXE, giving every byte exactly one owner:

- **C**: bytes regenerated from admitted game objects.
- **RUNTIME**: bytes regenerated from complete historical library members.
- **RESOURCES**: payload ranges regenerated by the pinned Microsoft RC 3.00 and matched to oracle resources.
- **LINK**: complete NE regions regenerated by pinned LINK 5.30 and matched to the oracle.
- **NE_CHAIN**: relocation-chain words taken from the loader metadata.
- **RAW**: explicit debt classified by lane.

A small binder regenerates object bytes: initialized data, the LINK far-call translation, and every fixup resolved by the same rules the strict matcher validates. The result must equal the oracle (`HYBRID_EXACT`). `validate.py` and every promotion enforce this and report the owned/debt delta. Totals go in [image.json](image.json), details in `build/image/ledger.json`, and `python tools/image.py --debt` lists every raw interval. `claim_conflicts` counts bytes proved by two admitted objects (a superseded unit still owning code, or one private literal declared twice). They must be merged into one unit before a real LINK. Scaffold data fillers (tu_assembly `SCAFFOLD, not recovered source ... (DGROUP LO-HI)`) may stand in only for unclaimed members of the same component, never over a MAPSYM public or another object's data; the ledger keeps their bytes as debt, not owned. Promotion refuses any admission that adds double-claimed bytes: a unit must supersede every member of an older unit it overlaps, and a function whose private data another object already claims needs that object reworked or merged first. When two components share unnamed private data, record joint-compile evidence (layout/translation-units.json) so they become one component.

| Lane | Work | Tools |
| --- | --- | --- |
| GAME_CODE | unrecovered game functions | `context.py --list --open`, `search.py`, `promote.py` |
| CODE_GAP | code bytes outside known extents | usually owned once the neighbouring function is admitted as a complete member |
| MERGE | double-claimed bytes | `tu_assembly.py build/test`, `promote.py --unit` |
| DATA | initialized public data | `context.py --list --data --open`, `context.py --data SYMBOL`, `promote.py --data FILE.c` |
| RUNTIME_CODE | `_TEXT` code not matched to a library member | ownership classification, library matching (`evidence/experiments/text-ownership/`) |
| GAME_ASM | hand-written assembly routines (reviewed class GAME_ASM in `layout/ownership-review.json`) | `search.py SYMBOL f.asm`, `promote.py SYMBOL f.asm` (pinned MASM, `tools/assembler.py`) |
| RESOURCES | resource table and any resource bytes not payload-proved | `python tools/promote.py --resources` |
| LINK | NE header/tables/relocation tables/chains/padding | `python tools/promote.py --link`; complete DOS header/stub and four name/reference regions only |

**Data modules** are data-only C files: `__based(__segname("SIMANT_DATA_GROUP"))` or `__based(__segname("PACK"))` for the far data segments, ordinary near data for DGROUP. Each public spans to the next public of the object (or the contribution end), and no other original public may lie inside that span. Every byte must be initialized, placed and compared, fixups and loader sites included. Code, BSS, the DGROUP selector pools (`BE6E`-`C6DF`, owned by code objects) and the linker BSS region `[_edata,_end)` are refused, as is any overlap with bytes an admitted object already owns. Zero-filled data modules need explicit initializers (`= {0}`) to emit checked bytes. The image binder also credits an admitted object's private `FAR_DATA` zero-fill ranges when its complete-member proof independently fixes their placement, the range is in a file-backed `PACK` or `SIMANT_DATA_GROUP` segment, every oracle byte is zero, and no original public or admitted owner intersects it. `FAR_BSS` COMDEFs are minimum-allocation-only in the tested LINK 5.30 model and cannot own bytes in the NE file image. Ambiguous placement, overlap, a public inside the span, or nonzero bytes leaves the range as DATA debt. Data recipes are counted separately (`game_data_symbols`, `game_data_bytes`).

**Assembly modules** are real MASM source for the 32 routines reviewed as GAME_ASM: instructions and ordinary directives only, and data directives in code segments only for label/offset dispatch tables. Byte dumps and INCBIN are refused. Seven pinned MASM versions (5.00–6.14) are locked in `layout/toolchain.json` (provenance `evidence/toolchain/masm-provenance.json`). They all reproduce the first admitted routine (`_exchange`) identically, so the historical assembler version is not identified by that routine (`evidence/experiments/assembler/identification.json`). The version is a per-module context backed by evidence: most modules need MASM 6.x ([cross-version.json](../evidence/experiments/assembler/cross-version.json)), while the LZSS tree module reproduces only under MASM 5.x because 6.00 rewrites direct-memory `LEA` to `MOV` ([lzss-tree-masm5x.json](../evidence/experiments/assembler/lzss-tree-masm5x.json)). Try the version a related admitted module uses first. The recipe records the version that was used. Admission uses the same complete-member and whole-image gates as C.

**Resource payloads** use the tracked RC source and image assets under `src/resources/`. `python tools/promote.py --resources` freshly runs the pinned Microsoft RC 3.00, binds it to an empty structural NE input, and admits only the 41 payload ranges whose type, identity/source name, occurrence order, size and bytes match the oracle. RC 3.00 adds an RT_NAMETABLE entry; that entry and the resource table are never credited. `image.py` copies admitted bytes from the recorded RC-bound NE output and leaves the table and all other unproved resource bytes in RESOURCES debt. Source, RC tool, `.RES` output and bound-output identities are recorded in the recovery ledger and promotion proof. `validate.py` replays the RC compile and bind against the preserved empty NE input.

**LINK regions** use tracked `src/link/SIMANTW.DEF` and the readable one-byte `src/link/SEGSTUB.ASM`, plus the preserved structural object inputs from the LINK investigation. `python tools/promote.py --link` freshly assembles the segment placeholder and runs pinned LINK 5.30 through the locked DOS runner. Admission compares parser-derived regions byte for byte and records the output under ignored `build/`: the 1,024-byte DOS header/stub, resident and nonresident names, imported names, and module references (1,195 bytes total). `image.py` copies those bytes from the recorded LINK output. The NE header, segment and entry tables, resource table, relocation tables, chain words, and padding remain LINK debt; partial field matches earn no credit. `validate.py` replays the admission and refuses changed sources, inputs, tools, output, or ranges.

The commdata layout probe (`evidence/experiments/commdata-layout/`) compiles uninitialized and explicitly initialized far arrays with MSC 7.00 and links them with LINK 5.30, the original `SIMANTW.DEF` segment order, and `/PACKDATA`. It establishes that initialized and uninitialized private `PACK FAR_DATA` contributions can occupy file-backed bytes in a packed data segment; LINK zero-fills the latter there. Uninitialized `FAR_BSS` COMDEFs follow FAR_DATA in minimum allocation and add no file bytes. Default `static far` / `huge` contributions use the compiler's `INPUT5_DATA FAR_DATA` segment, paragraph alignment, and minimum allocation after the explicit PACK file range; `/NOPACKDATA` keeps those logical segments separate. Input order changes public offsets and padding. The reproducer records the OMF, MAP, NE file length, and minimum allocation for each variant; see fact `LINK-D1` in the worker report.

## Worker prompt

A ready-to-paste brief for a subagent (any model):

```text
Work in D:\Prog\simantw_recon; run every command from there with python. Read AGENTS.md,
docs/factory.md and docs/grinder-lessons.md. Targets: <SYMBOLS> (or choose from
`python tools/context.py --list --open`). Use only build/workers/<NAME>/ for scratch files.
Per target: `context.py SYMBOL`, write readable C with a semantic block comment, then run
`search.py SYMBOL files...` (unnamed static helpers: `static_probe.py SEG:OFF file.c helper --like CALLER`; add `--frame` for the CodeView frame map when stack homes differ; `effective_output` in the result names candidates whose object repeats an earlier one) for as many rounds as are useful, reading the aligned diff and
adapting each time. Write sources as plain ASCII without a UTF-8 BOM (MSC 7.00 rejects
`0xEF 0xBB 0xBF`; PowerShell Set-Content/Out-File add one). There is no attempt limit. On a strict match run `promote.py SYMBOL file`. If the
body is exact but only private data/selector placement fails, say so (unit lane). Stop at a
match, a concrete missing dependency, or when no useful next investigation remains; then
record the finding with `search.py SYMBOL best.c --note "..."`. Do not hand-edit tools/,
layout/, src/recovery.json or evidence/, and do not run git. Report per target: result,
rounds, best opcodes/bytes, and the decisive idiom or remaining residue.
```

## Build model: units, profiles and lanes

`python tools/typedb.py build|check|resync` builds a program-wide database of declarations actually used by admitted member bodies, with source variants, majority consensus and NE/MAPSYM machine evidence. Scaffold references and `POOLSTUB_TEXT` stand-ins are excluded. Use `check` to spot draft declaration conflicts and `resync` to produce a declaration-corrected source while preserving function bodies; strict `search.py` remains the compiler proof.

The factory models the original build instead of one universal isolated-function experiment:

```
source translation unit -> declarations / private data / selector pool -> compiler profile -> object member -> LINK -> SIMANTW.EXE
```

- [build-topology.md](build-topology.md) reconstructs candidate units (objects) from the selector pools and private data the linker preserved. `python tools/build_topology.py` regenerates `evidence/topology/build-topology.json`.
- `layout/compiler-profiles.json` catalogs the admissible MSC 7.00 profiles. `baseline` (`/Oelw`) stays the default. `og`, `ogi`, `ga` and `og-ga` apply only through a reviewed assignment attached to a unit context with probe evidence (`python tools/compiler_profiles.py probe SYMBOL [--source PATH]`, `assign CONTEXT PROFILE --evidence ...`). For an unnamed static helper, `probe-helper SEG:OFF SOURCE.c --function NAME --like CALLER [--out DIR]` compares the helper body with `static_probe.py`'s fixup-bound, LINK-translated view under every catalog profile. `assign` accepts helper evidence only when its caller belongs to the context and MAPSYM plus build topology bound the helper extent to that same context; discrimination, minimality and intrinsic string-operation fingerprints remain required. Use `assign ... --dry-run` to validate without writing, and `--supersede ASSIGNMENT_ID` when a reviewed evidence-backed profile replaces an existing assignment for the same context. Every search, recipe and promotion proof records its profile, and `validate` fails closed on any recipe whose flags disagree with its declared profile.
- `python tools/tu_assembly.py propose | build | test` composes preserved exact-body sources of a unit component into one candidate translation unit (a contiguous run of publics, predicted contiguous selector block) and strict-tests all contributions. An exact unit is admitted with `python tools/promote.py --unit UNIT --reason "..."`, which may explicitly supersede isolated recipes of its members. Preserved sources come from admitted recipes, reviewed sources and the draft ledger.
- `python tools/private_placement_report.py evidence/recovery/units/UNIT/test/results.json` explains each private-segment placement constraint in a preserved test: source public, candidate and historical operands, implied base, and exact repeated-byte period. It is a read-only diagnostic. An implied base is not a proved object boundary or admission.
- **Scaffolded units** (`tu_assembly.py build COMPONENT --members ... --scaffold --harmonize`): when a unit's exact bodies are separated by members that are not recovered, the composer emits *stand-in functions* into the reserved code segment `POOLSTUB_TEXT`. They only reproduce the selector-pool allocation order of the unclaimed members: one far reference per original pool word, named through the claimed members' own slot symbols, an exact MAPSYM site name, or a representative public symbol of the addressed segment (based-segment words through an extern based reference). Later runs of claimed members are placed in `RUNk_TEXT` by `#pragma alloc_text`. The matcher skips only that reserved segment and records it (`scaffold_segments`). The pool words the stand-ins allocate are still validated through the CONST selector fixups, and every claimed member is anchored and compared byte for byte. Stand-ins are never compared, credited or treated as recovered source; recipes, promotion proofs and unit records carry the `scaffold` record. Controls: `evidence/topology/supervisor-scaffold/controls.json` (positive: simtwo:5AB0 without GenerateTutorial; negatives: wrong segment, missing word). Pool-word attribution follows the block: a function's words are one contiguous ascending range, introducer positions never decrease, and words that no visible ES site introduces (static helpers, other load forms) are attached to the preceding introducer or to a filler stand-in.
- A reviewed scaffold may record measured, unclaimed zero CONST words with `--private-zero-gap OFFSET:SCALAR,SCALAR:POOLSTUB`. The build gate requires separately declared zero `static const __segment near` scalars used by the named reserved-code stand-in. The unit test verifies that the interval is initialized zero OMF data without fixups. Promotion retains the native complete-member comparison of the whole CONST contribution. The unit and promotion proof label the interval `UNCLAIMED_LAYOUT_SCAFFOLD`; this does not identify its historical owner or recover those scalars.
- **Declaration harmonization** inside a unit works by verification, never by preference. `--harmonize` accepts a spelling for a conflicting name only if every claimed member that uses it keeps its exact body when recompiled in isolation with that spelling (trials are kept under the unit folder). Shape and element-type variants of one object become per-member view macros (`#define LifeB ((unsigned char near *)LifeB)`), conflicting macros and macros shadowing objects are scoped to their member, struct tags defined differently are renamed per source, and two symbols naming one original pool word are unified over the enclosing MAPSYM object (`#define AlistT ((unsigned char far *)((unsigned char far *)Dx8 + 0x3D18))`).
- `python tools/mirror_pairs.py` derives a black/red colony function from its admitted or exact mirror (MAPSYM twin identifiers and mirrored Dx8 field offsets swapped, structure unchanged) and runs it through `search`. `--all` records the derivation from both sides of still-open pairs as asymmetry evidence (`evidence/recovery/mirror-pairs/`).
- `python tools/declaration_order.py SYMBOL [--write]` derives private static declaration order from the original data word positions for an exact body. `--write` tests the rewritten source through `search`.
- `python tools/review_source.py SYMBOL PATH --note "..."` verifies a reviewed isolated source strictly under the symbol's object profile and records it in `evidence/topology/supervisor-unit-sources/reviewed.json`. Only an exact body (`tu_assembly.body_exact`) is offered to units, as basis `REVIEWED_EXACT_BODY`. `rebind_pack_index.py` and `rebind_based_fields.py` record their results the same way. The ledger keys on the file's identity, so an edited source must be re-verified.
- `layout/declaration-order.json` records object-level (before, after) declaration pairs with the evidence that established them, and `tu_assembly.compose` reorders unit declarations to satisfy them. MSC 7 decides the operand order of a commutative expression of two globals by declaration order, so this is a real TU-level fact rather than a formatting choice (rule `commutative-operand-declaration-order`).
- `body_exact` rejects a candidate whose differing immediate sits at a site with no fixup (a swapped switch case is not a binding), and one that references an external that neither MAPSYM nor the import library knows (an invented name can never be resolved by a unit).

Searches run in parallel: each run has its own directory, compilation goes through the shared persistent compiler service, and the draft ledger takes a short lock. Only publication is serialized.

## Proof rules added by the build model

- OMF LOC 5 offsets of far code symbols (statically linked, no NE obligation) are validated only together with a validated selector fixup to the same symbol (`tests/test_far_code_offsets.py`).
- A derived `_BSS` placement must lie in the original BSS region `[_edata, _end)`. A candidate static placed below `_edata` is initialized data or another object's public data in the original (`tests/test_bss_region.py`).
- A unit promotion commits all of its members in one journaled transaction. Superseded recipes are archived in the promotion proof.
- Structural confirmation is source-independent. It checks recursive closure, a second linear instruction-boundary pass, NOP-only gaps, entry/alias/incoming-branch evidence and relocation containment. It does not relabel the original CFG evidence as recovered source, establish an original OMF boundary, or substitute for admission.
- `BODY_MATCHED_BINDING_BLOCKED` (`topology_diagnostics.classify`) describes a body with known equal extents, layout/CFG/opcode agreement, no register/stack/branch differences, and literal differences covered entirely by unresolved two-byte offset fixups. It is diagnostic, not credit, and means the remaining work is data layout (usually the unit lane), not expression search.

## Measured runner decision

The repository has two execution paths: MSC 6.00A continues to use MS-DOS Player, and MSC 7.00 selects DOSBox-X and Windows 3.x through its explicit runner override.

Lighter-host screening is recorded under `evidence/experiments/runner/`. Direct CL and C13216 execution in MS-DOS Player fail with DOSX32 R6901 (required DPMI services), including the VCPI-enabled path. The available HDPMI32/CWSDPMI combinations in MS-DOS Player and bare DOSBox also produced no usable first-probe object. These are failures of those pinned configurations, not proof that every possible DOS host is incompatible. No alternative was adopted merely because its executable started. C7 does not support the attempted `/Bt` timing option; instrumentation uses external host timestamps and an empty-TU startup calibration instead.

| Measurement | Observed local result |
| --- | ---: |
| Start Win3.x/DOSBox-X | About 3.16-3.19 seconds |
| Execute C7, including internal pass startup | About 0.33-0.36 seconds |
| Parse OMF | About 0.3 milliseconds |
| Strict match/feature extraction | About 4-9 milliseconds |
| Warm persistent compile request | About 0.37 seconds |
| Cached search, still rematched | About 0.5 seconds |

## Persistent workers and reproducibility

`tools/compiler_service.py` implements the filesystem protocol under ignored `build/compiler-service/`: immutable source snapshots, pending/running/completed requests, request-batch records and receipts. Each worker has a separate Windows copy, scratch directory, temp files and DOSBox process. Only compiler/tool and construction directories are mounted; original game assets are never mounted.

Each accepted worker count has a separate `evidence/experiments/runner/worker-N.json` proof for exactly N hosts. The configured proof slots are 1, 4, 8, 12 and 16; the service accepts a count only when its exact proof passes and the recorded compiler, matcher, fixture, oracle, probe-source and OMF identities still match. Missing, wrong-count or stale proofs refuse startup. `compile_jobs()` and `start()` keep their four-worker default; a supervisor can select another proved count with `serve --workers N`. Sessions recycle after 96 jobs.

The inherited baseline first reproduced all 18 canonical probes twice with one worker and then four workers. Its previous 400-job service stress took 48.81 seconds (about 8.20 compiles/second); the earlier factory note recorded 50.53 seconds. Those measurements predate the current worker-count proof gate. Re-run the canonical validation after changing the service or worker. `worker_validate.py` reports per-job latency and per-host DOSBox CPU, peak working set and Windows process I/O transfer counters (logical bytes, not physical-device traffic). Oracle receipts pin each expected OMF by size and SHA-256; when a preserved expected OBJ is absent from an isolated worktree, validation checks the freshly compiled OMF against that complete recorded identity. Use `python tools/worker_validate.py --workers N` for the exact-count oracle and `python tools/worker_validate.py --workers N --service-stress --jobs 400` for the service path.

Idle DOSBox processes are suspended by the host. The service stops after two idle minutes and starts automatically on demand. Compiler caching keys on source, flags/code group, tool lock, worker implementation and profile, and matching always runs again.

At service start, completed response JSON files and terminal `jobs/` folders older than one day are pruned. Pending and running requests and job folders without a terminal marker are retained. The prune does not touch `build/compiler-jobs/`, `build/codegen-cache/`, compiler proofs or request-batch records.

```powershell
python tools/compiler_service.py status
python tools/compiler_service.py start --workers 4
python tools/compiler_service.py stop
python tools/worker_validate.py --workers 4
python tools/worker_validate.py --workers 8 --service-stress --jobs 400
```

When many workers run under `cx`, start the service from the supervisor's own session (`python tools/compiler_service.py serve --workers 4 --idle-seconds 86400`). Otherwise the first worker's compile request starts it as that worker's descendant, and `cx` stops it, and with it everyone's compiles, when that worker exits. `layout/compiler-service.json` records the production choice. `SIMANT_COMPILER_REFERENCE=1` retains the old reference path for controlled comparisons. After changing the service, worker, validator or wait helper, rerun one-worker validation before parallel validation, then `validate.py`. Do not edit recorded fingerprints to bypass them.

## Source provenance: EXACT_NATURAL and EXACT_STEERED

Binary proof and source provenance are recorded separately. Every admission passes the same strict gate. `evidence/recovery/provenance.json` lists the admissions whose source contains steering constructs (`EXACT_STEERED`, written by `promote.py --steered TEXT`); every other admission is `EXACT_NATURAL`. A steering construct is plain C that has no runtime effect but changes an MSC 7.00 decision:
- a dead compile-time guard;
- a redundant alias or temporary;
- an equivalent but differently shaped CFG;
- a statement the optimiser removes.

The TEXT names each construct and the decision it steers, e.g. "`register int upper` alias keeps `first` in DI across the loop test". Steering is the last step after natural hypotheses from docs/msc7-codegen.md have been tried. It is preferred over any toolchain change: one locked compiler model, never per-function flags. A later natural source replaces the steered record automatically.

Per-function `#pragma optimize("...", off|on)` is normally rejected. The only exception is an exact setting and `#pragma optimize("", on)` restore pair listed for that function in `layout/pragma-review.json`, with repository-local evidence paths. The pair must immediately bracket the function; every other pragma remains banned. The supervisor populates this review only after a strict complete-member proof. A reviewed pragma admission also requires `--steered TEXT`, so its provenance is always `EXACT_STEERED`; the review-map identity is captured in the promotion proof. The map starts empty.

## Search diagnostics versus proof

`tools/codegen_diff.py` aligns instructions and reports layout/CFG shape, opcode counts, register-only changes, immediates, memory operands, stack-local displacements, branch targets, instruction ordering and the first structural difference. Unknown indirect CFGs return an unknown shape result. The diagnostic view accounts for LINK transformations only when the strict matcher has independently validated them. It never modifies an object, and it never participates in admission.

`python tools/emu_diff.py SYMBOL DRAFT.c` compiles the draft with the symbol's assigned profile and runs the oracle function and candidate in Unicorn against shared synthetic NE data, seeded inputs and scripted call stubs. It reports the first differing write, call or return plus target basic-block coverage; unsupported runtime helpers, unresolved layout, invalid memory, or instruction-limit hits stop the comparison. This is a sampled diagnostic, not a proof or an admission check, and stack-frame write differences can reflect compiler layout rather than a source-level behavior change; see [emu-diff](emu-diff.md).

`codegen_grinder.py --evidence PATH` includes a compact `compiler_response` in its archived report that groups candidates by raw OMF identity. `search.py` reports each candidate's object hash for the same purpose: identical objects mean the next experiment needs a different analysis level.

## Symbolic lifting

`python tools/lift.py SYMBOL --out DIR` converts the inspection packet to a
readable C hypothesis by keeping register values as expressions until stores,
calls, branches, and other observable boundaries. `--open` and `--controls`
cover the open and admitted C sets. `--refine` searches bounded operand,
declaration-order, frame-home, temporary-order, and loop-form variants with
the compiler and aligned instruction diff as feedback. Run
`python tools/search.py SYMBOL candidate.c --frame` to inspect `ENTER` size and
CodeView homes. Lifted code is an authoring aid; use the normal complete-member
proof before treating a function as recovered. Architecture, known limits, and
control/open measurements are recorded in [lifter.md](lifter.md) and
`build/workers/f-infra-lift2/REPORT.md`.

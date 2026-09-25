# Recovery workflow

The everyday path is **context → search → promote**, with complete validation at acceptance or tooling boundaries. The working compiler is MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw /NT<original code group>` unless the symbol's object context has a catalogued, evidence-backed profile. Read [recovery lessons](grinder-lessons.md) before a new target's first search.

```powershell
python tools/context.py --list --open            # unrecovered functions, closest drafts first
python tools/context.py _Symbol                   # full working packet (--brief, --history)
python tools/search.py _Symbol build/workers/me/a.c build/workers/me/b.c [--meta round.json] [--note "..."]
python tools/promote.py _Symbol build/workers/me/b.c [--verify-only]
python tools/validate.py
```

Commands print JSON on stdout; compiler progress goes to stderr.

- **context** is read-only. The packet has masked disassembly with loader bindings, basic blocks, calls, globals, `direct_data_bindings` (exact MAPSYM names, selector slots, addressed segments and the DS-frame assumption), the compiler profile, `unit_context`, `unit_declaration_order`, relevant `reconstruction_rules`, similar admitted functions, the best preserved draft, notes and legacy job summaries. `structural_extent` reports whether the closed CFG extent is independently confirmed. That is informational: admission checks the complete original scope itself.
- **search** compiles any number of files in one round under the symbol's profile, runs the strict member matcher and the instruction diagnostic, and ranks the results. It has no budget, duplicate-experiment refusal, job state or eligibility gate, and old blocker labels never block it. Output goes to `build/search/SYMBOL/<run>/` (sources, `.diff.txt`, full `results.json`) and a per-symbol `history.jsonl`. When a candidate outranks the stored draft (strict, then exact body, then aligned opcodes, then size delta), it is copied into the durable ledger `evidence/recovery/drafts/`. `--template spec.json` runs a controlled equivalence-class batch (`codegen_grinder` template/axes). `source_warnings` lists anything promotion would reject.
- **promote** freezes the source into `src/recovered/`, compiles it fresh, and admits it only if full original/candidate scope, public placement, ordinary bytes, semantic fixups, private contributions and ownership all check out. It re-verifies the complete manifest before and after. Publication holds one OS lock and a journal (`build/publication.json`), and `--recover` rolls back an interrupted publication without overwriting later edits. The proof goes to `evidence/recovery/promotions/<id>.json` and records the proof-tool identities. `--verify-only` runs the whole gate, also for an already admitted control, without publishing.
- **validate** runs the unit/negative tests, independently re-verifies every admitted object (`build/recovery/verified-objects.json`, totals in [progress.json](progress.json)), checks the profile catalog, replays an exact control through the compiler cache and checks the persistent-service evidence.

Similarity scores, diagnostic ranks, structural certificates and scaffold stubs never grant credit.

## Whole binary: image ledger and lanes

`python tools/image.py` rebuilds all 516,096 bytes of SIMANTW.EXE, giving every byte exactly one owner:

- **C**: bytes regenerated from admitted game objects.
- **RUNTIME**: bytes regenerated from complete historical library members.
- **NE_CHAIN**: relocation-chain words taken from the loader metadata.
- **RAW**: explicit debt classified by lane.

A small binder regenerates object bytes: initialized data, the LINK far-call translation, and every fixup resolved by the same rules the strict matcher validates. The result must equal the oracle (`HYBRID_EXACT`). `validate.py` and every promotion enforce this and report the owned/debt delta. Totals go in [image.json](image.json), details in `build/image/ledger.json`, and `python tools/image.py --debt` lists every raw interval. `claim_conflicts` counts bytes proved by two admitted objects (a superseded unit still owning code, or one private literal declared twice). They must be merged into one unit before a real LINK.

| Lane | Work | Tools |
| --- | --- | --- |
| GAME_CODE | unrecovered game functions | `context.py --list --open`, `search.py`, `promote.py` |
| CODE_GAP | code bytes outside known extents | usually owned once the neighbouring function is admitted as a complete member |
| MERGE | double-claimed bytes | `tu_assembly.py build/test`, `promote.py --unit` |
| DATA | initialized public data | `context.py --list --data --open`, `context.py --data SYMBOL`, `promote.py --data FILE.c` |
| RUNTIME_CODE | `_TEXT` code not matched to a library member | ownership classification, library matching (`evidence/experiments/text-ownership/`) |
| GAME_ASM | hand-written assembly routines (reviewed class GAME_ASM in `layout/ownership-review.json`) | `search.py SYMBOL f.asm`, `promote.py SYMBOL f.asm` (pinned MASM, `tools/assembler.py`) |
| RESOURCES | resource table and data | authentic RC (`tools/resources.py`, in progress) |
| LINK | NE header/tables/relocation tables/chains/padding | authentic LINK 5.30 + DEF once all contributions exist |

**Data modules** are data-only C files: `__based(__segname("SIMANT_DATA_GROUP"))` or `__based(__segname("PACK"))` for the far data segments, ordinary near data for DGROUP. Each public spans to the next public of the object (or the contribution end), and no other original public may lie inside that span. Every byte must be initialized, placed and compared, fixups and loader sites included. Code, BSS, the DGROUP selector pools (`BE6E`-`C6DF`, owned by code objects) and the linker BSS region `[_edata,_end)` are refused, as is any overlap with bytes an admitted object already owns. Zero-filled arrays need explicit initializers (`= {0}`) to become initialized contributions. Whether the originals were initialized or communal remains an open LINK-lane question. Data recipes are counted separately (`game_data_symbols`, `game_data_bytes`).

**Assembly modules** are real MASM source for the 32 routines reviewed as GAME_ASM: instructions and ordinary directives only, and data directives in code segments only for label/offset dispatch tables. Byte dumps and INCBIN are refused. Seven pinned MASM versions (5.00�6.14) are locked in `layout/toolchain.json` (provenance `evidence/toolchain/masm-provenance.json`). They all reproduce the first admitted routine (`_exchange`) identically, so the historical assembler version is not yet identified (`evidence/experiments/assembler/identification.json`). The recipe records the version that was used. Admission uses the same complete-member and whole-image gates as C.

## Worker prompt

A ready-to-paste brief for a subagent (any model):

```text
Work in D:\Prog\simantw_recon; run every command from there with python. Read AGENTS.md,
docs/factory.md and docs/grinder-lessons.md. Targets: <SYMBOLS> (or choose from
`python tools/context.py --list --open`). Use only build/workers/<NAME>/ for scratch files.
Per target: `context.py SYMBOL`, write readable C with a semantic block comment, then run
`search.py SYMBOL files...` for as many rounds as are useful, reading the aligned diff and
adapting each time. There is no attempt limit. On a strict match run `promote.py SYMBOL file`. If the
body is exact but only private data/selector placement fails, say so (unit lane). Stop at a
match, a concrete missing dependency, or when no useful next investigation remains; then
record the finding with `search.py SYMBOL best.c --note "..."`. Do not hand-edit tools/,
layout/, src/recovery.json or evidence/, and do not run git. Report per target: result,
rounds, best opcodes/bytes, and the decisive idiom or remaining residue.
```

## Build model: units, profiles and lanes

The factory models the original build instead of one universal isolated-function experiment:

```
source translation unit -> declarations / private data / selector pool -> compiler profile -> object member -> LINK -> SIMANTW.EXE
```

- [build-topology.md](build-topology.md) reconstructs candidate units (objects) from the selector pools and private data the linker preserved. `python tools/build_topology.py` regenerates `evidence/topology/build-topology.json`.
- `layout/compiler-profiles.json` catalogs the admissible MSC 7.00 profiles. `baseline` (`/Oelw`) stays the default. `og`, `ogi`, `ga` and `og-ga` apply only through a reviewed assignment attached to a unit context with probe evidence (`python tools/compiler_profiles.py probe SYMBOL [--source PATH]`, `assign CONTEXT PROFILE --evidence ...`). Every search, recipe and promotion proof records its profile, and `validate` fails closed on any recipe whose flags disagree with its declared profile.
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

One persistent worker first reproduced all 18 canonical probes twice with identical raw OMF bytes and identical strict results. Only then were four workers enabled and checked against the same oracle. A complete client/server stress run compiled **400 canonical candidates in 50.53 seconds**, with all objects byte-identical and eight environment launches across four workers. Sessions recycle after 96 jobs.

Idle DOSBox processes are suspended by the host. The service stops after two idle minutes and starts automatically on demand. Compiler caching keys on source, flags/code group, tool lock, worker implementation and profile, and matching always runs again.

```powershell
python tools/compiler_service.py status
python tools/compiler_service.py start --workers 4
python tools/compiler_service.py stop
python tools/worker_validate.py --workers 4
```

`layout/compiler-service.json` records the production choice. `SIMANT_COMPILER_REFERENCE=1` retains the old reference path for controlled comparisons. After changing the worker or wait helper, rerun single-worker validation before parallel validation, then `validate.py`. Do not edit recorded fingerprints to bypass them.

## Search diagnostics versus proof

`tools/codegen_diff.py` aligns instructions and reports layout/CFG shape, opcode counts, register-only changes, immediates, memory operands, stack-local displacements, branch targets, instruction ordering and the first structural difference. Unknown indirect CFGs return an unknown shape result. The diagnostic view accounts for LINK transformations only when the strict matcher has independently validated them. It never modifies an object, and it never participates in admission.

`codegen_grinder.py --evidence PATH` includes a compact `compiler_response` in its archived report that groups candidates by raw OMF identity. `search.py` reports each candidate's object hash for the same purpose: identical objects mean the next experiment needs a different analysis level.

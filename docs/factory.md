# Matching-decompilation factory

Use [the grinding prompt](cheap-model-prompt.md) to hand this workspace to a cheaper model. The primary interface is `python tools/grind.py`; the model does not need to edit recovery manifests or understand worker internals. The working compiler remains MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw /NT<original code group>`.

Read [supervisor lessons](grinder-lessons.md) before a new target's first test: declaration choices, evidence-backed mismatch triage, admitted private-state examples and actionable escalation records. These lessons preserve automatic stop rules and strict proof requirements.

## Build model: units, profiles and lanes

The factory models the original build instead of one universal isolated-function experiment:

```
source translation unit -> declarations / private data / selector pool -> compiler profile -> object member -> LINK -> SIMANTW.EXE
```

- [build-topology.md](build-topology.md) reconstructs candidate units (objects) from the selector pools and private data the linker preserved; `python tools/build_topology.py` regenerates `evidence/topology/build-topology.json`.
- `layout/compiler-profiles.json` is the catalog of admissible MSC 7.00 profiles. `baseline` (`/Oelw`) stays the default; `og`, `ogi`, `ga`, `og-ga` apply only through a reviewed assignment attached to a unit context with probe evidence (`python tools/compiler_profiles.py probe JOB`, `assign CONTEXT PROFILE --evidence ...`). Every job, recipe and promotion proof records its profile; `validate` fails closed on any recipe whose flags disagree with its declared profile.
- `python tools/tu_assembly.py propose | build | test | job` composes preserved exact-body sources of a unit component into one candidate translation unit (contiguous run of publics, predicted contiguous selector block), strict-tests all contributions and issues a `TU_ASSEMBLY` job whose promotion may explicitly supersede isolated recipes of its members.
- `python tools/parked_review.py` reclassifies every parked job by root cause (`evidence/recovery/parked-reclassification.json`): A profile, B unit layout (with the assemblable group or the missing introducers / static helpers), C matcher tooling, D semantic, E ABI/type, F structural, G unknown.
- Expert replays: `tools/topology_retest.py JOB --profile-reissue` (assigned profile) and `--tool-replay` (validated proof-tool change) archive the previous job context and grant at most one recorded budget extension each.
- Worker packets carry `compiler_profile`, `unit_context` and the matching `reconstruction_rules` from `layout/reconstruction-rules.json`.

Grinders run in parallel: a short global lock covers queue allocation, shared evidence rebuilds and the core manifest transaction; each job has its own lock for attempts, deferral and promotion, and compilation runs outside the global lock. Interrupted attempts are detected by a free per-job lock, never by assuming a single process.

## Production loop

```powershell
python tools/recovery_workflow.py doctor
python tools/grind.py next
python tools/grind.py inspect _Symbol
python tools/grind.py test _Symbol candidate.c --summary "Concrete semantic hypothesis"
python tools/grind.py accept _Symbol candidate.c
python tools/grind.py block _Symbol "Observed mismatch and supporting evidence" --cause REGISTER_ALLOCATION --next-experiment "One discriminating experiment"
```

Commands return JSON on stdout; progress messages go to stderr. `next` resumes active work or selects a match-ready target. `inspect` includes the working packet inline and saves it to disk: target ASM/bytes, CFG scope and basic blocks, calls, globals, loader bindings, imported symbols, declaration examples, original code group, compiler profile, similar verified functions and known TU membership.

Put the semantic hypothesis in a C block comment or supply `--summary`. `test` compiles the source, parses OMF, invokes the existing strict member matcher and returns instruction diagnostics plus aligned ASM. It does not accept anything. Revisions can address ordinary C syntax failures without immediate expert escalation.

The budget is **eight attempts, at most 96 variants per attempt and 192 candidates total per target**. This permits several cheap single-source revisions or larger controlled variant batches without an endless search. Identical experiments are rejected even when their descriptions change. For explained equivalence-class batches, the lower-level `recovery_workflow.py` interface and template generators remain available; they share the same job and budget.

`accept` requires exactly the source identity of an exact tested candidate, then performs fresh compilation and the independent recovery admission procedure. It checks full original/candidate scope, public placement, ordinary bytes, semantic fixups, private contributions and the proposed complete manifest. Updates are transactional. Similarity scores, structural certificates and scaffold stubs never grant credit.

When the budget expires or a concrete blocker is established, preserve the candidate and use `block`. The ledger records sources, scores, logs, failed variants and the next experiment. Do not keep retrying the same blocked draft. Testing an unchanged already-matched source is allowed as a regression and grants zero credit.

## Proof rules added by the build model

- OMF LOC 5 offsets of far code symbols (statically linked, no NE obligation) are validated only together with a validated selector fixup to the same symbol (`tests/test_far_code_offsets.py`).
- A derived `_BSS` placement must lie in the original BSS region `[_edata, _end)`; a candidate static placed below `_edata` is initialised data or another object's public data in the original (`tests/test_bss_region.py`).
- Promotion of several exact unit jobs happens in one core transaction (`recovery_workflow.py promote JOB [JOB ...]`); superseded recipes are archived in the promotion proof.

## Production and research states

[production-queue.json](production-queue.json) currently contains:

| State | Functions | Meaning |
| --- | ---: | --- |
| MATCH_READY | 689 | Confirmed structural test extent, game ownership, available bytes/disassembly and contained evaluable relocation obligations. |
| MATCH_BLOCKED | 91 | Readable attempted drafts with specific matching blockers. |
| STRUCTURE_BLOCKED | 42 | Unclosed, ambiguous or otherwise unsupported structural scope. |
| MATCHED | 243 | Existing independently verified source recovery. |

Structural confirmation is source-independent. It checks recursive closure, a second linear instruction-boundary pass, NOP-only gaps, entry/alias/incoming-branch evidence and relocation containment. It does not relabel the original CFG evidence as recovered source, establish an original OMF boundary, or substitute for admission. Certificates retain the original CFG status and their scope explicitly. They are cached against fixture, extent and analysis-tool identities so each candidate test does not rerun the entire structural census.

The older READY/GUIDED/LARGE/EXPERT queue remains useful for estimating semantic effort. The four production states above are the factory routing interface. Unknown historical compiler patch identity is not a blanket blocker.

## Expert topology pass and automatic stop

The [expert pass](expert-blocker-pass.md) promoted 13 functions, reaching 243 functions / 6,950 bytes. Live machine-readable files remain authoritative. Three shared data families are solved, and two adjacent TUs have independent complete-member evidence. The strict matcher, admission gate, compiler profile and worker are unchanged.

`BODY_MATCHED_BINDING_BLOCKED` is a diagnostic substate of MATCH_BLOCKED, not recovery credit. It requires known equal extents, layout/CFG/opcode agreement, no register/stack/branch differences, and complete literal differences covered by unresolved two-byte offset fixups. The workflow automatically escalates such an attempt immediately. Preserve the source and move to the next target; do not reopen it with cosmetic C changes. Unknown CFGs, constant differences outside bindings, or wrong calls do not qualify.

`evidence/recovery/blocker-families.json`, `layout/private-data-topology.json` and [blocker-families.md](blocker-families.md) record shared operand evidence. `refresh` rebuilds these with the ledger and production queue. Family observations and stored body states do not authorize promotion. Family packets link preserved source identities; expert-only `tools/topology_retest.py JOB SPEC --reason REVIEW` reissues a parked job for an explicitly new experiment while preserving old context and budgets.

Inspection packets now expose exact MAPSYM names for direct DGROUP operands and NE selector-slot targets, with an explicit DS-frame assumption. This surfaces names such as `_MapA` instead of encouraging invented unresolved externs.

Size ordering is retained: this pass establishes a useful stop signal, but does not measure model effort well enough to justify new scheduling weights. Every ready target remains eligible; no hard target is hidden or removed by a heuristic.

## Measured runner decision

The repository has two distinct execution paths: MSC 6.00A continues to use MS-DOS Player; MSC 7.00 selects DOSBox-X and Windows 3.x through its explicit runner override.

Lighter-host screening is recorded under `evidence/experiments/runner/`. Direct CL and C13216 execution in MS-DOS Player fail with DOSX32 R6901 (required DPMI services), including the VCPI-enabled path. The available HDPMI32/CWSDPMI combinations in MS-DOS Player and bare DOSBox also produced no usable first-probe object. HDPMI32/Player reported insufficient memory; the DOSBox HDPMI32 trial timed out; CWSDPMI trials returned abnormal output without an object. These are failures of those pinned configurations, not a proof that every possible DOS host is incompatible. No alternative was adopted merely because its executable started.

C7 does not support the attempted `/Bt` timing option. The compiler wrapper now recognizes that unknown-option warning correctly. Instrumentation uses external host timestamps and an empty-TU startup calibration instead.

Representative reference measurements covered ABS, WindowsMemCpy, MyPow and CreateMonoSolidBrush:

| Measurement | Observed local result |
| --- | ---: |
| Start Win3.x/DOSBox-X | About 3.16-3.19 seconds |
| Execute C7, including internal pass startup | About 0.33-0.36 seconds |
| Parse OMF | About 0.3 milliseconds |
| Strict match/feature extraction | About 4-9 milliseconds |
| Total original candidate test | About 3.72-3.75 seconds |
| Warm persistent compile request | About 0.37 seconds |
| Warm uncached `grind test`, including inspection/diff | 1.12 seconds in the API regression |
| Cached `grind test`, still rematched | 0.81 seconds in the API regression |

Compiler startup and incremental compilation estimates are reported separately using the empty TU. They are estimates: external instrumentation cannot isolate initialization inside each authentic C7 pass. The receipt's measured compiler-execution time includes those phases. Cached receipts retain their historical compile timing; the API's cache fields and total-test time identify the current request. A cold worker also copies its private Windows environment, and the first structural queue build adds a one-time cost.

## Persistent workers and reproducibility

`tools/compiler_service.py` implements the filesystem protocol under ignored `build/compiler-service/`: immutable source snapshots, pending/running/completed requests, request-batch records and receipts. Each worker has a separate Windows copy, scratch directory, temp files and DOSBox process. Only compiler/tool and construction directories are mounted; original game assets are never mounted.

One persistent worker first reproduced all 18 canonical probes twice with identical raw OMF bytes and identical strict results. Only then were four workers enabled and checked against the same oracle. The 36-job runs took 17.69 seconds with one worker and 8.15 seconds with four. A subsequent complete client/server stress run compiled **400 canonical candidates in 50.53 seconds**, with all objects byte-identical and eight environment launches across four workers. Sessions recycle after 96 jobs. This is persistence across submissions with bounded recycling, not a claim of unlimited C7 process longevity.

Idle DOSBox processes are suspended by the host, avoiding busy CPU consumption. The service stops after two idle minutes and starts automatically on demand. The pinned historical tools remain unchanged. Source, object, helper, configuration and tool identities are retained. Compiler caching also includes source, flags/code group, tool lock, worker implementation and production profile.

```powershell
python tools/compiler_service.py status
python tools/compiler_service.py start --workers 4
python tools/compiler_service.py stop
```

`layout/compiler-service.json` records the production choice. `SIMANT_COMPILER_REFERENCE=1` retains the old reference path for controlled comparisons. The compiler worker uses DOS 8.3 names and disables directory caching for its exchange directory. DOS-side idle calls proved unreliable in this Win3.x environment; the host owns suspension/resumption instead. Windows rename/read sharing races are retried, with request identities retained, rather than causing silent recompilation.

The production service verifies unchanged worker/tool identities against its canonical oracle before starting. After changing the worker or wait helper, rerun single-worker validation before parallel validation. Then rerun the service workload and handoff checks. Do not edit recorded fingerprints to bypass them.

## Search diagnostics versus proof

`tools/codegen_diff.py` aligns instructions and reports layout/CFG shape, opcode counts, register-only changes, immediates, memory operands, stack-local displacements, branch targets, instruction ordering and the first structural difference. Unknown indirect CFGs return an unknown shape result. Per-candidate JSON and compact `.diff.txt` files accompany the strict matcher output.

For `_db_GetObjectSize`, the current candidate has **39/39 opcodes aligned, matching layout and CFG, seven register-only differences, no immediate/memory/branch differences, and 7/7 fixups correct**. It remains unaccepted. See `evidence/codegen/db-instruction-diff.json` and `.txt`.

The diagnostic view accounts for LINK transformations only when the strict matcher has independently validated them. It does not modify an object. This prevents a genuine linker far-call translation from being mistaken for an expression-shape error. Diagnostic scoring never participates in recovery admission.

## Validation and remaining work

```powershell
python tools/worker_validate.py
python tools/worker_validate.py --workers 4
python tools/handoff_validate.py
python tools/recovery_workflow.py doctor
```

The latest handoff validation passes **118 tests**. It runs parser/proof/failure-path tests, canonical cache replay and fresh pilot admission. It also checks the 400-job service evidence against current runner identities. [handoff-readiness.json](handoff-readiness.json) records the current result.

At the historical factory-infrastructure checkpoint, no manually matched functions had been added: recovery remains **208 game functions / 4,995 bytes** plus **77 historical runtime members / 12,960 bytes**. It has not benchmarked a particular cheap language model. The existing 38 matching blockers and 42 structural blockers remain explicit research work, and the whole reconstructed game remains unbuilt. LINK 5.30/RC outputs are structural scaffolding only.

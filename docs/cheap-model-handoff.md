# Cheap-model recovery handoff

The current primary interface is documented in [factory.md](factory.md). It adds a measured persistent MSC7 service, explicit production/research states and instruction-level diagnostics. The commands below describe the lower-level workflow.

Use the authentic MSC C/C++ 7.00 baseline `/AL /G2 /Gs /Oelw /NT<original group>`. Historical patch identity is not a generic blocker. Current recovery totals are in `docs/progress.json`; `docs/handoff-readiness.json` reports live workflow validation and production-state counts, while `docs/recovery-queue.json` partitions task effort. The checkpoint below is historical; run `python tools/recovery_workflow.py doctor` for the current state.

## Verified checkpoint

The earlier September 20 checkpoint passed 92 tests and independent verification of 208 game functions / 4,995 bytes, plus 77 runtime members / 12,960 bytes. The IsItWall pilot completed task selection, eight generated variants, fresh admission and transactional promotion. Replaying all eight candidates used zero compiler boots and reran every comparison. This validates the workflow; no particular cheap model has been benchmarked.

At that checkpoint, the queue had 515 READY, 88 GUIDED, 174 LARGE and 80 EXPERT targets. All 41 original readable drafts remained frozen; 38 still needed specialist work. Earlier infrastructure solved DoWinHelp, ProcMenuHelp and the SetMenuOptionState TU case, compiled 384 candidates in four boots, and reduced unknown game extents from 500 to 43 without granting source credit.

The admission audit corrected ten legacy recipes' code-group/MAPSYM metadata and rebuilt their objects without changing source logic. Another 97 existing member recipes had provisional extent metadata revalidated against original/candidate CFGs and complete matching members. See `evidence/recovery/handoff-code-groups.json` and `handoff-extents.json`. Neither operation adds recovery credit.

Authentic LINK 5.30 and RC 3.00 structural experiments succeed. The whole reconstructed game remains unbuilt; generated stubs and synthetic resources receive no source credit.

## Start and inspect

```powershell
python tools/recovery_workflow.py doctor
python tools/recovery_workflow.py next
```

`next` creates or resumes a job in `evidence/recovery/workflow/jobs/<job>/`. Read `packet.md`, then `packet.json` for instructions, loader bindings and CFG details. Consult the referenced declarations and callers as needed instead of loading the entire repository history. An active task resumes before a new task is issued.

The packet masks relocation-chain bytes as `??`. NE loader-chain words are not literal C addresses, segment constants or call targets. The next MAPSYM public is only an upper bound. DS global annotations and declarations from other recovered functions are hypotheses with stated limits.

## Submit semantics and controlled variants

Edit the job's `candidate.c` and `submission.json`. Write ordinary historical-style C. Fill `semantic_summary` with concrete behavior and `binding_evidence` with evidence for types, calls and globals. Keep the supplied symbol, publics, compiler and flags unchanged for isolated tasks.

Use either `source` (a repository-relative C file) or `template` (inline C with replacement markers). Empty `axes` means one candidate. Each axis needs a name, a marker occurring exactly once, a rationale and explicit values or an existing generator. Example:

```json
{
  "name": "increment_form",
  "marker": "@INCREMENT@",
  "rationale": "The increment value is discarded, making prefix and postfix equivalent here.",
  "values": ["++count;", "count++;"]
}
```

Existing generators include `u16_high_byte`, `local_order_register` and `signed_range_predicate`. Consult `tools/codegen_transforms.py`, `evidence/codegen/specs/` and the completed IsItWall job. Prototype/type alternatives require evidence; they are not automatically equivalent.

```powershell
python tools/recovery_workflow.py attempt <job>
```

The tool permits at most 96 candidates per attempt, eight attempts per target and 192 candidates total. It deduplicates sources, records compiler receipts and complete OMF comparisons, and rejects repeated experiments even if their descriptions change. Compiler caches validate source/object/tool identities; matching always runs again. The production service supports four isolated persistent workers, recycling sessions after 96 jobs; the original batch runner remains available for reference.

Read `attemptNN/results.json` for ordinary bytes, contribution size, semantic fixups, private data, frame features and first divergence. Similarity is diagnostic, never proof. Use the second attempt only for a new evidence-backed hypothesis.

## Promote or park the blocker

```powershell
python tools/recovery_workflow.py promote <job>
```

Only `EXACT_CANDIDATE` enters promotion. Promotion freshly compiles without the cache, checks original and candidate CFG scope, MAPSYM placement, cross-entry ambiguity and complete OMF contributions, then independently verifies the proposed full manifest. Recipes and recovery credit update transactionally. `--audit-only` grants no credit.

Never edit object bytes, proof tools, manifests, protected hashes or scope metadata to force admission. If admission fails, investigate or defer rather than bypassing it.

```powershell
python tools/recovery_workflow.py defer <job> --cause FAR_POINTER_TYPE --reason "Fixup agrees but typed assignment emits LDS where target uses LES" --next-experiment "Inspect caller argument layout and aggregate passing"
```

Choose the actual cause from the taxonomy in `evidence/recovery/blockers.json`. Preserve the best evidence and suggest a discriminating next experiment. Failed readable sources and receipts remain durable. Exhausting the attempt or total-candidate budget automatically parks the task. Workflow escalations are separate from the frozen draft corpus.

Continue with `next`; use `queue` for status and `doctor` at checkpoints. Semantic candidates, CFG estimates and scaffold stubs never receive recovery credit.

## Lanes

| Lane | Work |
| --- | --- |
| READY | Closed ordinary CFG, at most 384 bytes and 12 calls, no known specialist blocker. Default work. |
| GUIDED | String-instruction idioms; consult existing fingerprints first. |
| LARGE | More semantic analysis; same attempt/proof budgets. |
| EXPERT | Unresolved extents, FP, aliases/tails, old blocked drafts and exhausted attempts. |

After READY is exhausted, use `next --lane GUIDED`, then `next --lane LARGE`. Defer unknown semantics with `SEMANTICS_UNKNOWN`. Stop when only specialist work remains and report concrete blockers. Do not repeatedly reopen old drafts.

## Expert maintenance

This workspace has the original fixtures, pinned tools and built object manifest. For a new checkout, restore exact ignored assets/toolchain using the project's setup process, then run `python tools/build.py objects` and `python tools/verify_recovery.py`. Machine-local object caches are rebuilt; repository sources and evidence persist.

```powershell
python tools/recovery_workflow.py refresh
python tools/handoff_validate.py
python tools/recovery_workflow.py doctor
```

Validation runs all tests, an eight-candidate cache replay and pilot admission. Its receipt is `evidence/recovery/workflow/validation.json`; its test log is `build/handoff-validation/tests.log`. Readiness fails if validated tool/test inputs change.

Proof/toolchain changes deliberately invalidate active jobs. An expert must review and reissue their context; the cheap model must not rewrite protected hashes. Interrupted attempts are durably parked with pending output. Pending promotion transactions restore prior core files; committed promotions interrupted before bookkeeping are reconciled on restart. Preserve pending journals.

See [codegen-infrastructure.md](codegen-infrastructure.md) for TU, CFG, ABI, string and linker research, and [cheap-model-prompt.md](cheap-model-prompt.md) for a ready-to-paste work prompt.

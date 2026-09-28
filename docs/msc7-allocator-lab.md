# MSC 7.00 allocator lab

`tools/alloc_lab.py` builds and measures a one-factor source grid for register and home allocation. It uses the worktree's pinned MSC 7.00 compiler service and the four catalogued toy profiles `baseline`, `og`, `oi`, and `ogi`.

## Run

```powershell
python tools/compiler_service.py start
python tools/alloc_lab.py generate
python tools/alloc_lab.py run --chunk 256
python tools/alloc_lab.py summarize
```

The harness keeps generated sources and results under `build/alloc_lab/`. `generate` writes `manifest.json` and the C inputs. `run` compiles each input once normally and once with `/Zi`, pairs the plain/debug outputs, verifies that `/Zi` did not change the function bytes, and appends one allocation observation per case/profile to `observations.jsonl`. `summarize` fits the small rank rules and writes `model.json`, `counterexamples.jsonl`, and `home_counterexamples.jsonl`.

Each case changes one named factor from its controlled form. The present grid has 555 cases: 5 local counts; 160 static-use counts for each of three values; loop depths 0–2 for each value; all six declaration, first-use, and first-definition permutations; far-call lifetime; parameter forms and copy masks; pointer versus arithmetic use; constant and variable shifts; four scalar widths; address-taking; value reuse; CSE temporary form; and asymmetric branch-arm use counts. This yields 2,220 allocation observations (555 per profile) and 4,440 plain/debug compiler requests. The factor case counts are recorded in `model.json`.

An observation records profile flags, object hash and size, instructions, frame size, observed registers and homes, CodeView names, source-side lexical/loop features, and a transparent symbolic value-flow allocation map. `UNRESOLVED` and `AMBIGUOUS_HOME` are retained as such; the parser does not guess a variable assignment when CodeView or the supported instruction idioms do not establish one. `codeview_identical` is true for all 2,220 observations in this run.

## Measured rule and limits

The fitted rule is deliberately narrow: among the three or fewer ordinary mutable word values in the `competition` and `weight` controls, sort by descending source `lexical_reads`; break ties by descending last-reference line and then name; predict SI, then DI, then home. For this corpus, adding loop reads did not improve the score, so the smallest winning score is `lexical_reads + 0 * loop_reads`.

The fit correctly classified 5,872 of 5,928 value placements (99.06%). Per-profile accuracy is 98.92% for baseline and oi, and 99.19% for og and ogi. Its home-slot ordering extension correctly predicted 1,984 of 2,020 tested homes (98.22%). Every miss is serialized with its row, profile, predicted class, actual class, and source features. These rates describe the controlled grid only; they do not establish an MSC allocator algorithm for arbitrary C.

The independent admitted-source check is the guard against that overclaim. `build/alloc_lab/validate_admitted.py` invokes this worktree's `tools/search.py SYMBOL SOURCE --frame --full` on 30 admitted `src/recovered/` functions. All 30 members and frame maps check successfully. Of 90 named word-local placements that could be compared to the extrapolated SI/DI/home rule, 45 contradict it (50% accuracy). The broad rule is therefore falsified for admitted functions and must not be used to assign their registers. It misses interference from expression shape, liveness, pointer roles, parameters, compiler-generated temporaries, larger competing sets, and control-flow schedule.

The toy evidence was recorded as `MSC7-X2-ALLOC-WEIGHT` under `evidence/codegen-facts/`. `MSC7-X1` was already marked FALSIFIED in the code-generation register, so this study records a new ID rather than rerunning it. The register itself is unchanged; workers propose register edits in `build/workers/f-study-allocx/REPORT.md` for supervisor review.

## Useful adjacent outputs

`build/alloc_lab/target_searches.json` contains the current ledger-frontier replays, with `--frame` results, for the nominated public symbols. `target_hypotheses.json` contains source-form experiments, and `target_model_applications.json` records the rule's rank prediction for each current word-local source shape, including its out-of-scope variables. `target_static_hypotheses.json` records the unnamed helper diagnostic at `3:6250`; because a static helper has no public symbol, this uses `static_probe.py` rather than `search.py` and remains diagnostic evidence.

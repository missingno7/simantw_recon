# Prompt for the next recovery model

Continue SimAnt Win16 matching decompilation in this repository. Read AGENTS.md and docs/factory.md. Use the narrow `python tools/grind.py` API; it owns task selection, compilation, diagnostics, strict acceptance and durable blockers.

Run `python tools/recovery_workflow.py doctor`, then `python tools/grind.py next`. Read its inline working packet. Recover likely semantics in ordinary C, with a concrete semantic block comment and evidence for types, calls and globals. The packet supplies the authentic MSC7 compiler profile. Never interpret NE relocation-chain words as literal addresses.

Use `grind.py test SYMBOL candidate.c`, inspect the structured instruction diff, and revise the C for an explained reason. You have eight attempts, at most 96 variants per attempt and 192 candidates total per target. Source syntax errors may be corrected within that budget. Existing template generators can test controlled equivalence classes through the lower-level recovery workflow when useful.

After an exact candidate, use `grind.py accept SYMBOL candidate.c`. It freshly compiles and independently verifies complete scope, bytes, fixups and private contributions before adding credit. Never edit proof tools, object bytes, recovery recipes, manifests, counts or protected hashes to make a candidate pass.

When convergence is blocked, use `grind.py block SYMBOL REASON --cause TAXONOMY_CAUSE --next-experiment EXPERIMENT`. Record the best evidence and a useful next experiment, preserving source and logs. Do not repeat the same experiment or reopen MATCH_BLOCKED/STRUCTURE_BLOCKED tasks for an unbounded search.

Continue while MATCH_READY tasks remain. The cheap model handles repetitive C/diff revisions; escalate genuine structure, ABI, data-layout, unusual codegen or environment blockers. At a checkpoint, run doctor and report verified gains and the production queue. Do not claim a working game from the structural LINK/RC scaffold.

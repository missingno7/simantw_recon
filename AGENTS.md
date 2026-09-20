# Repository working instructions

This project reconstructs readable Win16 SimAnt C through authentic Microsoft-era tools and independent relocation-aware proof.

For ordinary source recovery, read `docs/factory.md` and use `tools/grind.py`: `next`, `inspect`, `test`, `accept` or `block`. The lower-level `tools/recovery_workflow.py` owns budgets and strict admission; use its `doctor` command for readiness. The task queue and durable blocker ledger are authoritative for which targets to attempt. Preserve failed readable drafts.

The operational baseline is MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw /NT<original code group>`. Historical patch identity is not a generic recovery blocker. Variant searches must be bounded and semantically motivated. Ordinary recovery must not alter proof tools, protected hashes, recipes, manifests or counts by hand.

Never patch candidate object bytes or treat copied machine-code blobs as recovered C. Exact proof includes the complete target extent, ordinary bytes, semantic fixups and all private contributions. A semantic match, CFG estimate or scaffold stub earns no recovery credit. NE relocation chains are loader metadata, not source constants or real branch targets.

Infrastructure work may change tools, but must retain fail-closed proof checks and rerun `python tools/handoff_validate.py` after changes. `python tools/recovery_workflow.py doctor` independently checks recovery and handoff readiness. Structural LINK/RC experiments are separate from a functional reconstructed executable.

# Repository working instructions

This project reconstructs readable Win16 SimAnt C through authentic Microsoft-era tools and independent relocation-aware proof. Read README.md and [docs/factory.md](docs/factory.md).

Everyday work is four commands:

1. `python tools/context.py SYMBOL` (`--brief`, `--history`; `--list --open` for targets): masked disassembly, loader/MAPSYM bindings, compiler profile, unit context, rules, similar admitted sources, best preserved draft and prior notes.
2. Write readable C in your own `build/workers/NAME/` directory. `python tools/search.py SYMBOL a.c [b.c ...]` compiles every hypothesis with MSC 7.00 under the symbol's profile and returns the strict member result and aligned instruction diff. `--meta round.json` records family/prediction/falsifier; `--note "..."` keeps a durable finding.
3. `python tools/promote.py SYMBOL candidate.c` (or `--unit UNIT --reason ...`) freshly compiles and admits an exact candidate. `--verify-only` runs the complete gate without publishing.
4. `python tools/validate.py` at acceptance or tooling boundaries, not for every hypothesis.

The goal is the whole executable. `python tools/image.py` rebuilds SIMANTW.EXE from admitted objects plus explicit raw debt and must stay `HYBRID_EXACT`. `--debt` lists what is missing, by lane (game code, data, runtime code, merges, resources, link); see "Whole binary" in docs/factory.md. Data symbols use `context.py --data SYMBOL` / `--list --data --open` and `promote.py --data FILE.c`.

Workers own their hypotheses, scratch directory and batch sizes. There are no attempt counts, candidate quotas, eligibility gates, parking states or reopening ceremonies: any unrecovered function may be investigated again at any time, and old blocker labels are hints, not verdicts. Choose individual experiments or useful batches, read the actual compiler feedback and adapt. Progress includes strict matches, narrowed mismatches, distinguished explanations and useful compiler/context facts; repeated output may answer a deliberate question. Stop at a solution, a concrete missing dependency (record it with `search.py --note`), or when no useful next investigation remains. After about ten genuinely stagnant rounds, change the hypothesis family or do a meta-analysis rather than guessing. Respect explicit user budgets and cancellation.

Searches run concurrently. Canonical publication is serialized by `promote.py`'s lock and journal and needs no further permission after strict acceptance; after an interruption use `promote.py --recover`. A body-exact candidate that fails only on private selector/data placement is admitted through the unit-assembly lane (`tools/tu_assembly.py build|test`, then `promote.py --unit`), described in docs/factory.md and docs/build-topology.md.

The operational baseline is MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw /NT<original code group>`; other catalogued profiles (`layout/compiler-profiles.json`) apply only to unit contexts with recorded evidence, never as a per-function flag search. Historical patch identity is not a generic recovery blocker.

Never patch candidate object bytes or treat copied machine-code blobs as recovered C. Exact proof includes the complete target extent, ordinary bytes, semantic fixups and all private contributions. A semantic match, CFG estimate, diagnostic rank or scaffold stub earns no recovery credit. NE relocation chains are loader metadata, not source constants or real branch targets. Do not invent names the packet already provides, and do not use asm, pragmas, includes or absolute-address casts to force bytes.

Never hand-edit `src/recovery.json`, the draft ledger, promotion proofs, fixtures, toolchain locks or recorded hashes. Infrastructure work may change tools but must keep fail-closed proof checks, add focused tests, and pass `python tools/validate.py`. Structural LINK/RC experiments are separate from a functional reconstructed executable. Keep generated detail under ignored `build/`; the pre-simplification workflow tree is in `build/archive/` and tag `checkpoint/pre-simplification-20260925` (see MIGRATION.md).

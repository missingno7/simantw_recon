# Repository working instructions

## Mission (changed 2026-09-30, overrides the goals below)

This project is no longer aiming for a complete byte-matching SIMANTW.EXE.
- The DOS reconstruction `D:\Prog\simant_recon` (github missingno7/simant_recon) is the behavioural and visual authority for the future portable SDL3 multi-window port. It is READ-ONLY for agents of this project; another agent works on it.
- This project recovers only the Windows-specific delta: how Maxis hosted the shared SimAnt window/object model (`win_*`) on native Windows. That covers HWND mapping and lifetimes, message-to-event translation, z-order and activation, invalidate/paint, geometry, focus/capture/cursor, the menus and application shell, the GDI boundary, and Windows-only services.
- The deliverable is `docs/portable-windows-reference.md`.
- `python tools/port_audit.py` classifies every function by its Windows API use and DOS pairing.

Byte matching is now a tool, not the goal. Reconstruct exactly only when one of these holds:
- exact code is needed to disambiguate Windows-specific behaviour;
- the function is genuinely Windows-only and important to the SDL3 architecture;
- it exposes a structure/API contract that cannot be established otherwise;
- it gives a native-window, event or state mapping.

Do not grind MSC 7.00 tails (SI/DI, stack homes, declaration order, selector pools, private DATA, expression shape) on functions that the DOS version already has. Existing drafts, evidence, tools and admissions stay as they are. The machinery described below still works and is still the way to prove anything exactly.

This project reconstructs readable Win16 SimAnt C through authentic Microsoft-era tools and independent relocation-aware proof. Read README.md and [docs/factory.md](docs/factory.md).

Everyday work is four commands:

1. `python tools/triage.py SYMBOL` and `python tools/context.py SYMBOL` (`--brief`, `--history`; `--list --open` for targets).
   - **triage** gives the blocker class and lane, the recommended next tool, the untried hypothesis families, the exhausted ones and the relevant facts.
   - **context** gives masked disassembly, loader/MAPSYM bindings, compiler profile, unit context, rules, similar admitted sources, the best preserved draft, the same triage summary, `already_tried` (the structured attempt history per family) and prior notes.
   - Begin with the recommended action and an untried family rather than re-deriving the mismatch.
2. Write readable C in your own `build/workers/NAME/` directory. `python tools/search.py SYMBOL a.c [b.c ...]` compiles every hypothesis with MSC 7.00 under the symbol's profile and returns the strict member result and aligned instruction diff. Every session appends a structured attempt record (`evidence/recovery/attempts/`).
   - Always name the round with `--family FAMILY` (controlled vocabulary: `python tools/attempts.py families`) and `--hypothesis "..."`; add `--prediction`/`--falsifier` when you have them. `--meta round.json` is still accepted.
   - Repeating a family that is already exhausted for the function needs `--why-repeat "new fact/tool/evidence"`. This is advice, never a gate.
   - `--note "..."` keeps a durable free-text finding.
   For sampled behavioral diagnostics, run `python tools/emu_diff.py SYMBOL DRAFT.c [--runs N] [--seed S] [--arg name=value]`; read [docs/emu-diff.md](docs/emu-diff.md) for scope and unsupported cases.
3. `python tools/promote.py SYMBOL candidate.c` (or `--unit UNIT --reason ...`) freshly compiles and admits an exact candidate. `--verify-only` runs the complete gate without publishing.
4. `python tools/validate.py` at acceptance or tooling boundaries, not for every hypothesis.

The goal is the whole executable. `python tools/image.py` rebuilds SIMANTW.EXE from admitted objects plus explicit raw debt and must stay `HYBRID_EXACT`. `--debt` lists what is missing, by lane (game code, data, runtime code, merges, resources, link); see "Whole binary" in docs/factory.md. Data symbols use `context.py --data SYMBOL` / `--list --data --open` and `promote.py --data FILE.c`. Reviewed GAME_ASM routines are recovered as real assembly (`.asm` files through the same `search.py`/`promote.py`), never as byte dumps.

MSC 7.00 behaviour is recorded in [docs/msc7-codegen.md](docs/msc7-codegen.md), a fact register with VERIFIED, SUPPORTED, FALSIFIED and OPEN rules plus reproducers; read it before testing a codegen hypothesis, and do not re-run FALSIFIED ones. Controlled compiler experiments go through `python tools/probe.py SPEC.json` (named source axes, the function's assigned profile enforced, and a per-variant report of bytes, frame, homes, registers and fixups); `--record ID` turns a run into reproducible evidence. Propose new rules or status changes in your REPORT.md; the supervisor changes the register. For a residue reduced to one register, home-order or load-shape choice, run `python tools/permuter.py DRAFT.c --function SYMBOL --time-limit N` (randomised semantics-preserving source mutations under the assigned profile, scored against the original; docs/permuter.md) instead of hand-writing more variants. Admit its exact winners with the provenance it reports (NATURAL or STEERED). Declarations (extern types, qualifiers, far/near, prototypes, struct shapes) are hypotheses too: `python tools/typedb.py check DRAFT.c` lists where a draft disagrees with the forms admitted, proven sources actually use (plus machine evidence for undeclared names), and `resync DRAFT.c -o OUT.c` rewrites only file-scope declarations (docs/typedb.md). A backlog-wide resync alone rarely finishes a function (0 of 173 became exact), so treat it as one axis to test, not an answer.

The supervisor layer is documented in [docs/orchestration.md](docs/orchestration.md):
- `sweep.py` re-evaluates every preserved draft after a shared change, and exact candidates still go through the fresh `promote.py` gate;
- `triage.py --open` gives lanes and value per agent-hour;
- `fleet_plan.py` gives small lane-based assignments;
- `permuter_queue.py` runs background permuter searches;
- `unit_owner.py` gives one owner per historical object for canonical unit composition. Set `SIMANTW_WORKER=NAME`; `compose --persist` and `promote.py --unit` refuse an object another worker owns.

Workers own their hypotheses, scratch directory and batch sizes. Parking is evidence-gated assignment metadata: `python tools/parking.py candidates` proposes an open function only when its two latest readable search sessions both fail to exceed the stored frontier rank, or at least 10 notes were recorded after that frontier; a proposal also needs a readable first causal divergence. The frontier rank uses `residue_clusters.classify` for the earliest meaningful divergence row, then `drafts.frontier_rank` (strict/body status, row, aligned opcode count). `park` records the blocker class, precise residue, frontier draft/opcodes, notes and probes; `reopen` requires a new fact or tool and records why. Parking never blocks `search.py` or `promote.py`. Workers do not re-attack a parked function unless it was reopened or they bring a genuinely new mechanism-level hypothesis, which they record with `search.py --note` before starting. There are no attempt quotas. Prefer depth over breadth: choose individual experiments or useful batches, read actual compiler feedback and adapt. Progress includes strict matches, narrowed mismatches, distinguished explanations and useful compiler/context facts; repeated output may answer a deliberate question. Stop at a solution, a concrete missing dependency (record it with `search.py --note`), or when no useful next investigation remains. After about ten genuinely stagnant rounds, change the hypothesis family or do a meta-analysis rather than guessing. Respect explicit user budgets and cancellation. Old blocker labels remain hints, not verdicts.

Searches run concurrently. Canonical publication is serialized by `promote.py`'s lock and journal and needs no further permission after strict acceptance; after an interruption use `promote.py --recover`. A body-exact candidate that fails only on private selector/data placement is admitted through the unit-assembly lane (`tools/tu_assembly.py compose OBJECT --add SYMBOL=FILE.c`, then `promote.py --unit`), described in docs/factory.md and docs/build-topology.md.

The operational baseline is MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw /NT<original code group>`; other catalogued profiles (`layout/compiler-profiles.json`) apply only to unit contexts with recorded evidence, never as a per-function flag search. Historical patch identity is not a generic recovery blocker.

Never patch candidate object bytes or treat copied machine-code blobs as recovered C. Exact proof includes the complete target extent, ordinary bytes, semantic fixups and all private contributions. A semantic match, CFG estimate, diagnostic rank or scaffold stub earns no recovery credit. NE relocation chains are loader metadata, not source constants or real branch targets. Do not invent names the packet already provides, and do not use asm, pragmas, includes or absolute-address casts to force bytes. The one exception is an original that itself used MSC 7.00 inline `_asm`: a hand-written idiom the compiler never generates (e.g. a dead `mov dx, 0`) inside a compiler-generated frame. Such a function is admitted only after the supervisor records it in `layout/inline-asm-review.json` with that signature instruction and evidence; `_emit`/data directives are never admissible. Workers propose these with `search.py --note`, they do not edit the review.

The goal is converging on exact binary matches, not a cosmetically plausible C version. Binary certainty and source-provenance certainty are separate: an exact binary match is exact even when the historical spelling is unknowable. Every admission carries one of two source provenance classes, and both count as binary matched:
- `EXACT_NATURAL` (the default): natural source, strongly supported as a plausible reconstruction.
- `EXACT_STEERED` (`promote.py ... --steered "TEXT"`): one or more C constructs exist mainly to steer MSC 7.00's optimisation or allocation decisions. Examples are a dead compile-time guard, a redundant alias, a harmless temporary, an alternate equivalent CFG form, or a construct that optimises away completely.

A steering construct must have no runtime effect, and TEXT must name every such construct and the decision it steers. The strict gates are unchanged: exact bytes, relocations, private contributions and layout; no regressions; `HYBRID_EXACT`. The ban on asm, pragmas, includes and absolute-address casts to force bytes stays. First test the natural causes that known MSC 7.00 rules suggest (docs/msc7-codegen.md). Once the residue is a single optimiser or allocation choice, plausible natural variants are exhausted and nothing distinguishes the historical spelling, admit a code-free steering form as EXACT_STEERED rather than searching without bound. A later natural source for the same symbol replaces the steered record.

Never hand-edit `src/recovery.json`, the draft ledger, promotion proofs, fixtures, toolchain locks or recorded hashes. Infrastructure work may change tools but must keep fail-closed proof checks, add focused tests, and pass `python tools/validate.py`. Structural LINK/RC experiments are separate from a functional reconstructed executable. Keep generated detail under ignored `build/`; the pre-simplification workflow tree is in `build/archive/` and tag `checkpoint/pre-simplification-20260925` (see MIGRATION.md).

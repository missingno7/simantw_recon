# Win16 SimAnt reconstruction research

Current scope: recover verified matching source and historical runtime objects, while keeping unresolved toolchain questions explicit.

Start with [the toolchain fingerprint](docs/toolchain-fingerprint.md). A pinned Microsoft C/C++ 7.00 candidate using `/AL /G2 /Gs /Oelw` reproduces 18 diagnostic game functions/contributions, 761 code bytes. The exact original command line and some tool versions remain unresolved. Complete historical runtime-member matches are tracked separately from game-source reconstruction.

For continued source recovery, use the [matching-decompilation factory](docs/factory.md) and [bounded model handoff](docs/cheap-model-handoff.md), [ready-to-use prompt](docs/cheap-model-prompt.md), and [current readiness report](docs/handoff-readiness.json). The workflow owns task selection, budgets, independent promotion, and durable escalation.

Key paths:

- `layout/toolchain.json`: tested tool identities and separately qualified historical hypotheses.
- `evidence/experiments/toolchain/decisions.json`: compact machine-readable findings.
- `evidence/experiments/toolchain/msc700-baseline-Oelw.json`: canonical diagnostic run.
- `layout/runtime-ownership.json`: historical object reuse and reconstruction exclusions.
- `tools/ne.py`, `mapsym.py`, `omf.py`, `matcher.py`: binary parsers and verifier.
- `tests/`: parser, compiler, relocation and complete-member negative tests.

Original assets and acquired tools remain local in ignored `assets/` and `toolchain/`. Compilation does not use the original executable as an input. There is no reconstructed standalone game EXE at this stage. An explicitly stubbed LINK 5.30 executable is available for structural research only.

The recovery build contains 208 C functions (4,995 code bytes) and extracts 77 complete historical runtime members (12,960 code bytes). Modern source files live in `src/recovered/`; the two earlier additional matches remain in `src/`. `src/recovery.json` records each compiler, flags, original placement and comparison scope. These are byte-matched reconstructions, not claims to the original source text or translation-unit boundaries. Runtime object extraction preserves complete historical OMF members rather than copying executable bytes.

Build and independently verify the recovered objects:

```powershell
python tools/build.py objects
python tools/verify_recovery.py
```

Objects and the construction manifest are written to `build/recovered/`. Verification writes `evidence/recovery/verified-objects.json`. Unresolved game code/data, original translation-unit grouping and final link/layout remain work before a standalone executable is possible.

```powershell
python tools/setup_toolchain.py
python tools/toolchain_probes.py --compiler msc700 --baseline --optimization /Oelw
python -m unittest discover -s tests -v
```

See the fingerprint for limitations, provenance and the discriminating matrix.

The [code-generation infrastructure phase](docs/codegen-infrastructure.md) adds controlled C-expression exploration, batched historical compilation, a frozen 41-draft regression corpus, candidate translation units, conservative CFG extent solving, compiler idiom probes, and a partial authentic linker/resource path. See [its machine-readable report](docs/codegen-progress.json) for results and remaining blockers.

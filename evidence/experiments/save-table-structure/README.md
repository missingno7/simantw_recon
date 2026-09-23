# Save table structure experiment

This isolated experiment extends the authoritative scan in `../savegame-table/README.md` and `provenance.json`. It reads the original NE image and MAPSYM, resolves each record pointer using semantic NE relocation targets, and compiles source-shaped declarations with MSC C/C++ 7.00 using the assigned `ANTEDIT_MODULE` profile (`/AL /G2 /Gs /Oeglw /NTANTEDIT_MODULE`). It does not use relocation-chain words as source values.

## Findings

The record table starts at `0x9570`. The first 50 rows end at `0x9700`, but that is only the root report's prefix boundary: the next row's count at `0x9702` is 1. The extended scan found 307 eight-byte records over `[0x9570,0x9F08)`, then a record with kind 0 and count 0 at `0x9F08`; no selector relocation is present at its pointer field. There are 257 records after the prefix. The records reference segment 8 73 times, segment 9 188 times, and segment 10 46 times, in 96 contiguous target-segment runs. Exact per-run boundaries and target counts are in `results.json`.

The inferred natural declaration is an 80-byte mutable filename buffer, followed by records shaped as `{kind/element width, count, far pointer}`, followed by a zero-count terminator. The consumers step records by eight bytes, multiply the first two fields for byte totals, and iterate per record for file I/O. `_SaveGame` has a preflight total-size pass followed by writes; `_LoadGame` has corresponding size accumulation and reads. These are disassembly-based semantic inferences, not recovered function matches.

Three sentinel candidates (mutable or const table, and `{0}` or `""` buffer initialization) produced the same object SHA-256 and OMF data hash. The table yielded 307 named width-four far-pointer fixups, matching every observed record, and the based data contribution measured 2544 bytes. This confirms that the natural C shape can express the observation under the assigned profile. It does not distinguish mutability or initializer spelling.

The no-sentinel variant measured 2536 bytes and omitted the observed count-zero terminator, so it is negative as a complete standalone table model. It does not rule out another object contributing the terminator.

## Provisional boundaries and limits

The 80 zero bytes at `0x9520..0x956F` are observed and referenced by filename routines. If the candidate buffer and table are placed contiguously starting at `0x9520`, their 2544-byte contribution ends at `0x9F10`; this placement and source object boundary remain hypotheses. `_yardBalloon` at `0x9F20` only bounds the modeled range, leaving `[0x9F10,0x9F20)` unassigned. No source declaration boundary is established by the experiment.

Source and object hashes, compiler receipt, OMF segment hashes, fixups, complete target-segment runs, and positive/negative checks are recorded in `results.json`. Candidate source and object files are retained alongside the probe. No strict function comparison or `grind.py` state change was made; this research earns no recovery credit and does not reopen `_SaveGame` or `_LoadGame`.

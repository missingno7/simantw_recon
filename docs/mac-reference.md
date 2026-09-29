# Macintosh SimAnt reference tool

`tools/mac_ref.py` reads the supplied hybrid CD without changing it. Extraction
outputs go under `build/mac/`; the Mac application is never run by this tool.

## Extract and index the disc

```powershell
python tools/mac_ref.py --extract-disc "D:\Games\DOS\dos_recosystem\simantmac_forged\assets\SimAnt_CD.iso" --mac-root build/mac
python tools/mac_ref.py --import-export-plan "D:\Games\DOS\dos_recosystem\simantmac_forged\artifacts\analysis\mac_static_lift_plan.json" --mac-root build/mac
python tools/mac_ref.py --rebuild-correspondence --mac-root build/mac
python tools/mac_ref.py --export-shapes --mac-root build/mac
```

The first command inventories the ISO 9660 tree, Apple Partition Map, classic
HFS catalog, and application resource fork. It writes the complete 81-file
size/hash table to `build/mac/iso-files.md` and the machine-readable inventory
to `build/mac/iso-files.json`. It extracts the full fork to `SimAnt.rsrc`,
`CODE` 0-12 to `code/`, `DATA`, `ZERO`, and `DREL` to `globals/`, and all `STR#`
and `STR ` resources to `strings/`. `asset-verification.json` records the
checks against the Mac project's asset inventory.

The lift-plan import copies only its 359 export boundaries, not its code or
application, into `mpw-export-boundaries.json`. `export-shapes.json` contains
one disassembly-derived shape summary per boundary. Both files stay under
`build/mac/`.

## Look up a function

```powershell
python tools/mac_ref.py _AnimYellowFight
python tools/mac_ref.py --mac-code 5:0x2054 --mac-root build/mac
```

The normal `SYMBOL` lookup reads `build/mac/correspondence.json`. For a
structurally matched Win16 function it prints the Mac `CODE` resource, offset,
confidence and evidence, disassembly, mapped callees/globals where available,
and a source-shape summary. If the matcher rejected or could not distinguish
the candidates, it reports that instead of naming a counterpart. `--mac-code`
inspects an MPW export by resource ID and hexadecimal entry offset.

## Structural correspondence

After importing the MPW export plan, build the feature index and correspondence:

```powershell
python tools/mac_ref.py --rebuild-correspondence --mac-root build/mac
python tools/mac_ref.py _YellowDeath --mac-root build/mac
```

`correspondence.json` stores per-function features on both sides, proposed
pairs and confidence evidence, unassigned exports, review candidates, held-out
anchor checks, and global-access summaries. Mac features include PC-relative
inline strings, referenced `STR#`/`STR ` text and IDs, numeric constants,
decoded Toolbox trap families, callers/callees, backward branches, computed
switch case counts, A5 displacements, operand widths, and register-relative
field offsets. Win16 features include literals from admitted C function bodies,
referenced NE string-resource text and IDs, constants, imported module/ordinal
calls, the named call graph and callers, CFG loop estimates, jump-table case
counts, and symbol-aware DGROUP access widths/counts.

The matcher first uses corpus-rare exact strings, constants, resource IDs, and
switch case counts. It requires reciprocal top ranking with a margin and a
one-to-one assignment. It then permits call-graph propagation only from pairs
with stable anchor evidence and at least two aligned caller/callee edges.
Boundaries whose case-count distribution conflicts or whose MPW span is at
least three times the Win16 body with only one anchor family remain review
candidates. The held-out check removes each accepted pair's individual anchors
in turn, reranks among all Win16 game functions using the remaining features,
and reports rank 1/rank 3 rates. This is a consistency check, not external
ground truth; the displayed confidence is a structural score, not a calibrated
probability.

The feature extractor uses decoded instruction boundaries for trap families.
Mac switch case counts are inferred from a bounded compare and an indexed jump;
they remain estimates if a span contains local routines or embedded data.
Win16 switch case counts come from the CFG solver's jump-table records. A5
offsets are signed displacements from a runtime A5 base that is not recovered.
The global map only promotes a name after two independent matched-function
votes and 70% vote share. Lower-support access-width/count candidates remain
tentative and are not declaration proof for `typedb.py`.

Source-shape estimates include observed positive A6 parameter slots and access
widths, `LINK A6` frame size, nonvolatile D/A register candidates, backward
branches, switch-dispatch patterns and inferred case counts, immediate constants, A5 offsets, and
register-relative field offsets. They are instruction-pattern evidence, not
recovered declarations: frame bytes are not a count of C locals, and saved
registers may be compiler temporaries. A5 call slots are reported as call
sites, separate from ordinary global offsets. An A5 offset is given a Win16
data name only when a direct cross-build mapping is available; the current
binary has no such proven mapping.

## Findings and limits

The Macintosh image is 68K, big-endian code. Its A6 frames, `MOVEM.L` saves,
A5-relative world, `CODE` resource headers, and segment jump table fit an
MPW-style build. The Mac project's lift plan also identifies the 359 boundaries
as MPW exports. MPW C uses 32-bit `int`; THINK C's usual 68K model uses 16-bit
`int`. The binary has no C type records, so individual `int` declarations
cannot be distinguished from `short`, pointers, or structure fields by width
alone. Treat the MPW identification as the best-supported compiler family,
not a compiler-version fingerprint.

The code-resource scan implements MacsBug's fixed 8/16-byte and variable
length name formats. The supplied application yields 359 unnamed MPW boundaries
and no MacsBug names matching the Win16 MAPSYM inventory. Structural matching
currently finds two medium-confidence open pairs, `_YellowCommand` and
`_YellowDeath`; both have exact switch case counts and retain rank 1 in all
accepted-anchor holdout trials. The current run covers 1,132 Win16 GAME
functions with a usable extent, 608 admitted and 524 open; 357 of the 359 Mac
exports remain unmatched. The recovery ledger's larger 1,543-target total
includes DATA targets, which are not function rows. No Mac A5-to-Win16 global
name has enough independent votes yet. These counts describe this evidence
set, not the amount of shared game source.

Mac and Windows builds use different compilers, pointer widths, integer widths,
calling conventions, endianness, and platform APIs. Use a Mac routine to reason
about likely source shape, control flow, constants, or field access only after
its correspondence is established. A Mac stack home or field offset is not a
Win16 stack home or layout proof.

The name-record rules are documented in [MacsBug 6.1 Reference, Appendix G](https://mirrors.apple2.org.za/www.bitsavers.org/pdf/apple/mac/developer/Macsbug/Macsbug_6.1_Reference_1989.pdf). The original [Apple MPW C language manual](https://oldcrap.org/wp-content/uploads/2023/04/apple-mac-mpw-doc-c-language.pdf) is useful when interpreting type widths. The extracted files, expected identities, and the current no-name result are recorded in `build/mac/` and `build/workers/f-study-mac/REPORT.md`.

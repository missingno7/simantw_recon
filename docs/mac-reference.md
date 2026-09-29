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

The normal `SYMBOL` lookup matches a Win16 MAPSYM function name to a MacsBug
name, ignoring case and one leading underscore. When a match exists it prints
the Mac `CODE` resource, entry offset and size, disassembly, known callees,
A5-relative references, and source-shape estimates. `--mac-code` inspects an
unnamed MPW export by resource ID and hexadecimal entry offset. The optional
shape catalog is useful when a worker has a candidate export but no name.

Source-shape estimates include observed positive A6 parameter slots and access
widths, `LINK A6` frame size, nonvolatile D/A register candidates, backward
branches, switch-dispatch patterns, immediate constants, A5 offsets, and
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
length name formats. The supplied application yields 359 MPW export boundaries
from the owner's lift plan but no validated name matching a Win16 MAPSYM C
function. The few name-shaped byte sequences in code do not match the Win16
function inventory. Thus `python tools/mac_ref.py SYMBOL` reports no named
counterpart for this disc. The `correspondence.json` coverage totals are zero
until a defensible name or other cross-build identity is found; this does not
mean the game functions are absent from the Mac binary.

Mac and Windows builds use different compilers, pointer widths, integer widths,
calling conventions, endianness, and platform APIs. Use a Mac routine to reason
about likely source shape, control flow, constants, or field access only after
its correspondence is established. A Mac stack home or field offset is not a
Win16 stack home or layout proof.

The name-record rules are documented in [MacsBug 6.1 Reference, Appendix G](https://mirrors.apple2.org.za/www.bitsavers.org/pdf/apple/mac/developer/Macsbug/Macsbug_6.1_Reference_1989.pdf). The original [Apple MPW C language manual](https://oldcrap.org/wp-content/uploads/2023/04/apple-mac-mpw-doc-c-language.pdf) is useful when interpreting type widths. The extracted files, expected identities, and the current no-name result are recorded in `build/mac/` and `build/workers/f-study-mac/REPORT.md`.

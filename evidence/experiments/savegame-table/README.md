# Save/Load data table provenance

`derive.py` reads the original NE image and MAPSYM and writes the reproducible
`provenance.json` report. This is research evidence, not a recovered declaration
or an admission receipt. The fixture SHA-256 values are in the report.

The initially scanned prefix of original DATA segment 8 contains 50
consecutive eight-byte records at `0x9570..0x96ff`. Each has a kind word, a
byte count, a pointer offset, and a segment relocation. Every pointer offset
plus relocation target in this prefix resolves to an exact MAPSYM name. The
observed prefix has 3 references to segment 10, 27 to segment 8, and 20 to
segment 9. Its kinds are 29 records of `1`, one of `2`, and 20 of `4`.
`_LoadGame` and `_SaveGame` reference `0x9570` directly. The full table extent
is not established: `_SaveGame` reads the next record's count, and the word at
`0x9702` is nonzero. The scan must continue beyond `0x96ff`.

The fourth word in each on-disk record is an NE loader-chain placeholder; its
raw value is not a source constant. The 80 zero bytes at `0x9520..0x956f`
are observed, and `_LoadGame`, `_SaveGame`, and `_ClearLastFileName` reference
that span. The observation does not establish whether it was one source
object or how MSC7 classified its contribution.

## Next discriminating experiment

Infer the record consumer's field widths and loop bounds from `_LoadGame` and
`_SaveGame` disassembly. Then compile a semantic C struct initializer using
named pointer owners and the assigned ANTEDIT profile in an isolated unit
fixture. Compare complete DATA bytes, semantic fixups, selector placement,
and member layout. Only a strict production proof can reopen or admit either
function; this report by itself earns no recovery credit.

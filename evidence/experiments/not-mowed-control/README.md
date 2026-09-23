# `_NotMowed` binding and register probe

The target is the 52-byte member at `SIMTWO_MODULE:203E` (segment 7,
offset 8254). Its only loader relocation is the PACK segment load at code
offset 0x06. The two indexed word accesses use a literal displacement
`0xA0B6`, which MAPSYM names `_GrassMap`. The older draft used
`match_position[position]`, an unrelated PACK object. Its authentic isolated
build added two offset fixups at code offsets 0x1C and 0x25 that the target
does not have (`candidate0000.diff.txt`).

`grassmap-far.c` changes only the object identity to `GrassMap`. An authentic
MSC 7.00 `/AL /G2 /Gs /Oelw /NTSIMTWO_MODULE` build is still 52 bytes and
26/26 opcodes, but all three semantic fixups now agree, with no unresolved
binding (`grassmap-far-trial/`). This supports the identity correction; it
does not prove the full source. `grassmap-based.c` also resolves the binding,
but its segment-load fixup differs in object form. The preserved working draft
now names `GrassMap`.

The component's recorded `og` profile (`/Oeglw`) was also tested with the
named far declaration. Its complete comparison is identical to the baseline
for this member (`grassmap-far-og-trial/`).

The remaining far-declaration mismatch is six register roles: target loads
position into BX and mask into DI, while the candidate uses DI and SI and
copies the index into BX. `register mask` and unsigned mask compile to the
same ordinary bytes; explicit local/register position moves its load later
and worsens the comparison to 30/46 ordinary bytes. Trial sources and full
reports are retained. A future experiment should explain the target's
position/mask lifetimes before changing source shape again. No admission was
made.

# 16-bit near-call IP wrap

The original NE contains direct near calls whose signed relative displacement crosses
`0x0000` or `0xffff`. Capstone 5, when decoding with an absolute segment offset,
can report a linear target outside the 16-bit IP range. The processor uses the
low 16 bits. For example, `ANTEDIT_MODULE:e61c` contains `E8 01 30`; its
computed `0x11620` is the MAPSYM public `_CenterEdit` at `0x1620`.

Before the `tools/analysis.py` correction, the generated cards contained 85
out-of-range direct near-call references across 31 callers and 50 distinct
raw targets. All 85 wrap to existing function cards in the same code group.
The corrected regeneration keeps 2,155 total near calls but changes the
unnamed count from 148 to 63, the out-of-range count from 85 to zero, and
incoming-reference edges from 6,099 to 6,184. The 1,319-card inventory and
complete source/object acceptance boundary are unchanged.

The change normalizes only direct near-call targets and their displayed operand
in the research disassembly. It does not alter original bytes, compiler output,
fixup comparison, matcher rules, or promotion. The synthetic regression covers
forward and backward IP wrap. `python tools/handoff_validate.py` passed 217
tests and the bounded compiler/cache replay; `recovery_workflow.py doctor`
remained `READY_FOR_BOUNDED_HANDOFF` with 518 verified game functions and 77
runtime members after regeneration.

The `_OpenMiniMapWin` and `_MapAreaEvent` packets had called `0x11620` and
`0x111e0` unnamed static helpers. Their normalized destinations are the
MAPSYM publics `_CenterEdit` and `_UpdateEdit`. `_MapAreaEvent` also reaches
`_OpenEditWindow` through `0x10e2c`, and `_ProcMapRibbonEvent` reaches
`_ForceUpdateEdit` through `0x10e50`. These correct false helper blockers,
but leave source-shape, private selector/data layout and historical TU
boundaries unproven. Reissue a production job only through the existing reviewed
retest/reissue path with the new named-call evidence; this note grants no
recovery credit.

The focused ANTEDIT ownership review is preserved in [open-minimap-audit.md](open-minimap-audit.md).

### Scope check: direct jumps

A read-only replay of every decoded instruction row in the regenerated
`evidence/disassembly/cards.jsonl` decoded 14,123 direct near jumps with
Capstone 5 in 16-bit mode. None reported an immediate destination outside
`[0, 0xffff]`. This negative result is scoped to the current card inventory
and does not establish a general MSC7 rule; it gives no reason to change the
separate jump-target handling in `extent()` for this fixture.

# Segment access and boolean scheduling review

No recovery credit was added. All failed readable sources and full comparison reports are retained beside this review.

## ClrModePop

Workflow job `ClrModePop-d8877e603b`, attempt06, tested exact MAPSYM PACK names TemRModePop (7BE4), TemBModePop (786A), FlyAwayB (7C44), FlyAwayR (8078) with named-segment based extern declarations. The original clears two 20-word buffers and decrements each nonzero counter.

The compiler emits a shared CONST selector and a 50-byte code contribution. The original is 67 bytes with repeated immediate segment loads, temporary DS use and DS restoration. Named-based extern declarations alone do not explain that pattern. The job was parked through `grind block`; two attempts remain. Require new declaration or translation-unit evidence before another experiment, not another padded array or equivalent based extern spelling.

## InitSpider

Two bounded research candidates outside workflow admission tested exact `Scycle2` spelling and an unsigned CurGameType comparison. The unsigned `>= 1` form still generates branches and a 162-byte contribution. The equivalent `!= 0` form generates CMP/SBB/INC and a 156-byte contribution, but moves the boolean assignment ahead of the zero stores and uses AX instead of the original CX. The equal contribution size is not a body match; instruction ordering, bindings and complete member proof still fail.

Reports: `InitSpider-probe/results.json` and `InitSpider-nonzero-probe/results.json`. Do not repeat the signedness/nonzero pair. Next research should explain preservation of the zero-store sequence and CX boolean live range using independently supported object qualifiers or TU evidence. No new workflow job or recovery recipe was manufactured for this frozen target.

Final doctor: READY_FOR_BOUNDED_HANDOFF, no problems, 257 verified game functions and 77 runtime members. Existing infrastructure validation remains current (142 tests); no tools or tests changed in this pass.

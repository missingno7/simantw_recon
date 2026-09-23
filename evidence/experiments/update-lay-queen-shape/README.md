# UpdateLayQueenModeDisplay body-shape probes

Diagnostic-only MSC 7.00 `/AL /G2 /Gs /Oelw /NTSIMANT_MODULE` research. The production job remains escalated; no workflow attempt, recipe, or manifest was changed.

## Result

The existing attempt02/03 source used `LayDownQueenMode < 1` in each branch. Fresh strict recompilation remained 120 bytes against a 108-byte target, with 29/39 aligned opcodes and three branch-target differences. Changing the source type to unsigned in attempt03 changed one conditional mnemonic but retained the same output class and size.

An eight-value controlled `index_expression` batch is in [variants.json](variants.json), with full per-candidate receipts, strict comparisons and diffs in [run01/results.json](run01/results.json). Its compiler-response summary is in [classes.json](classes.json): eight probes produced six effective objects. Three equivalent forms—`LayDownQueenMode == 0`, `!(LayDownQueenMode != 0)`, and `LayDownQueenMode ? 0 : 1`—compiled to the same object hash. They all yield a **108-byte body, 33/33 aligned opcodes, matching instruction layout/CFG, zero branch-target differences**, and `tu_assembly.body_exact(...) == true`. The winning readable source is [candidate-exact-body.c](candidate-exact-body.c).

This is new exact-body evidence for the private selector-pool introducer, but not a strict member match or recovery credit. The strict report still has 11/14 fixups and 70/76 ordinary bytes equal; its only remaining code-site differences are the candidate's external references to the private redraw flag and two private arrays. The target uses direct DS operands at `0xBCEC`, `0x1502`, and `0x1506`. Selector loads resolve to the expected segment 10 pool word at `0xC0D2`; private placement and complete unit context remain untested.

## Distinct negatives retained

- `< 1`, `<= 0`, and `!= 1` each remain the same wrong 120-byte class (29/39 opcodes, three branch-target differences).
- `(x < 1) ? 1 : 0` is a distinct 117-byte class (28/36 opcodes, three branch-target differences).
- `1 - (x != 0)` is a distinct 112-byte class (31/37 opcodes, three branch-target differences).
- The two additional exact-body expressions above deduplicate with the winning `== 0` class; the full run preserves all candidate-to-object identities.

## Interpretation and next step

For a 16-bit mode value, `mode == 0` reaches the target's carry-derived `mode < 1` selector: both are true only for zero. MSC7 lowers the equality spelling directly to the target's `CMP; SBB; NEG; SHL` sequence, while the relational spelling materializes branches. Treat this as body-shape evidence only. The next question is which source-level private declarations and surrounding TU order produce the direct flag/table operands and the `C0D2` selector binding together with the already exact neighboring bodies.

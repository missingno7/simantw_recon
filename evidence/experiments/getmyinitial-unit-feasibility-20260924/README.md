# GetMyInitialRandDir unit feasibility review

This is a read-only TU_ASSEMBLY feasibility review. No unit compile or TU job was created.

## Proposal and source identity

A fresh `python tools/tu_assembly.py propose --min 2 --limit 100` reports `simant1:75F4 unlock=0 usable=4/15 groups=[] blocked=3`. The promoted 3-member scaffold is `evidence/recovery/promotions/tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.json`: claimed runs are `_DoAntSimY`, `_EnterNest`, `_CheckMyBestDirs`; `_DoAntMoveY` is a pool-only stand-in. Its exact result is `STRONGLY_SUPPORTED_MEMBER`. The recovered unit source identity is recorded in `source-audit.json`.

The current `_GetMyInitialRandDir` attempt07 source is `evidence/recovery/workflow/jobs/GetMyInitialRandDir-72875fbed4/attempt07/candidate0000.c` (SHA `4f0c201e18a7a755d4e7821b6efc3ccff58608f3bbf55907b99d5a3fcd503908`). `tu_assembly.body_exact` returns true: 91/91 bytes, 36/36 opcodes, and instruction layout exact. Its isolated strict result is still `NO_COMPLETE_MATCH`, with 8/14 fixups; strict member proof would require every target byte and all 14 fixups resolved in the actual unit, plus the exact CONST contribution and placement.

Relevant preserved candidates and hashes, plus target topology data, are in `source-audit.json`. `_ExitNest` and `_GetMyDis` remain unadmitted; their current candidates do not pass the body gate. `_GetMyNextRandDirs` remains unadmitted with a calling-convention blocker. The target source for the real `_GetMyInitialRandDir` member is body-exact only; it is not promoted or credited.

## Required selector and CONST sequence

The existing contribution ends at C3E2. Between there and the target member's final words, the loader/pool evidence is:

1. C3E2, C3E4, C3E6: `_ExitNest` selectors, each relocated to segment 8.
2. C3E8, C3EA, C3EC: three zero words (six bytes), no loader relocations and no proven owner.
3. C3EE, C3F0, C3F2, C3F4: `_GetMyDis` selectors, each relocated to segment 8.
4. C3F6: `_GetMyNextRandDirs` selector, relocated to segment 9.
5. C3F8, C3FA: `_GetMyInitialRandDir` selectors, relocated to segment 9.

The byte and relocation audit is saved in `source-audit.json`. No owner is invented for the zero gap.

A scoped scan of the 423 recorded topology components found only two gaps between consecutive listed pool words: this six-byte interval and a two-byte interval at `antedit:C19C`/`C1FA`. Direct NE parsing shows `C1FA` **does** have a segment-9 selector relocation, so that second interval is an omitted topology listing entry, not the same zero-gap mechanism. This scan does not establish ownership or a general CONST-filler rule.

## Supported composer blocker

Current `tu_assembly.scaffold_plan` cannot represent this selector-free gap. `required_pool_block()` expands the interval word-by-word, including C3E8/C3EA/C3EC. The scaffold planner then calls its selector-reference builder for each word; `slot_segments()` has no relocation for the zero gap, so the builder rejects it as a pool word with no selector relocation. The lane has DATA/BSS fillers, but no input for a raw zero-filled CONST gap. With the current composer, the selector-only stand-ins plus exact-body member cannot form a valid complete candidate, so a strict exact-member proof is not presently reachable.

## Controls

No new positive/negative control was run because there is no composed candidate to test. Existing same-component positive evidence is the promoted 3-member scaffold above. Existing general scaffold controls in `evidence/topology/supervisor-scaffold/controls.json` include a positive `STRONGLY_SUPPORTED_MEMBER` result and negative wrong-segment and missing-word results (`NO_COMPLETE_MATCH`); these show the lane rejects incorrect selector inputs, but they do not exercise this unmodeled zero gap.

Conclusion: stop before compile. Supporting this group requires a reviewed composer input for the zero-filled CONST interval that remains fail-closed on all selector relocations. No production source, proof, manifest, ledger, or tool was edited, and there is no reissue or recovery credit.

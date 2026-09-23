# SIMANT `4C24` static pointer table trial

This bounded MSC 7.00 codegen experiment tested whether a file-scope `static char *const` table initialized with the two pause-menu strings could support the shared-literal hypothesis while preserving `_PauseGame`.

The strict comparison returned `NO_COMPLETE_MATCH`. The candidate code contribution is 374 bytes; the original `_PauseGame` member is 369 bytes. The candidate introduces `enter 4,0`, a four-byte frame absent from the target. The prior isolated-body classification for `_PauseGame` is `BODY_EXACT_LAYOUT_BLOCKED`; its remaining unit issue is private CONST/data placement and string-pool binding. The four-byte frame is an additional code-shape regression. The comparison also reports conflicting private placement constraints in `CONST` and `_DATA`, literal differences, unresolved fixups, and unplaced `_DATA`/`CONST` contributions.

This is research evidence only. It grants no recovery credit and does not justify a production reissue. No accepted source, production job, manifest, or proof tool was changed.

## Reproduction evidence

- `PauseGame_staticptr.c` is the exact tested source.
- `PauseGame_staticptr.spec.json` is the bounded one-candidate codegen spec.
- `results.json` preserves the compiler receipt and strict comparison.
- `candidate0000.diff.txt` preserves the instruction comparison.
- The build-local raw OMF was not copied. Receipt reference: `build/codegen-cache/e03f656ef5ce28b3d5d229749bb59671e402ab7aeef8d7b24e1fcb74b8a3fa62/OUTPUT.OBJ`, 1,143 bytes, SHA-256 `3c498136716fc089bdc1e74697a228d2a149b4cf23fcd947a6d7d9e35f04a784`.
- The C7 input snapshot is `build/codegen-cache/e03f656ef5ce28b3d5d229749bb59671e402ab7aeef8d7b24e1fcb74b8a3fa62/INPUT.C`, 3,466 bytes, SHA-256 `73fdafcdb7da746c01b0a64d3bf619af7431d8ed2ae61cfa7c451b14aab8b3fe`.

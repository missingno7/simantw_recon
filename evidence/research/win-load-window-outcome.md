# `_win_LoadWindow` bounded outcome

Job `win_LoadWindow-5ae5db540b` exhausted its eight-attempt budget and is `ESCALATED`; no candidate was accepted. Readable source and per-attempt receipts remain under the job directory.

## Effective output classes

- Attempt 1: 531-byte OMF, SHA-256 `8fc2d927a67475b2505c3cea2176b166f931315b07130d11ad7d36a90f0cce37`; partial 146-byte body, 48/177 opcodes and 2/9 fixups.
- Attempt 2: 916-byte OMF, SHA-256 `dd4319f4a5e23a4bdd34317fb5f7af9654cd4a1e07ba3862ff015cb23219b2a8`; 484 candidate bytes, 74/177 opcodes and 2/13 fixups.
- Attempts 3 and 8: same effective output (921-byte OMF, SHA-256 `df828dd2d980120391f9691a043d9d4d6abdcd076c90ea27ef573311e7907ac2`); 74/177 opcodes and 2/13 fixups. Attempt 3 added the exact message text but left generated code unchanged.
- Attempts 5 and 6: same effective output (921-byte OMF, SHA-256 `54cf406560803876e0d8ae75bbac8063e790d3275acfe469524f70354002e5e6`); 72/177 opcodes and 2/13 fixups.
- Attempts 4 and 7 are preserved compile-failed source drafts. The other tested drafts remain in their attempt folders.

## Established semantics and remaining question

`db_LoadObject((signed char)(objectNumber >> 8), 0, 1)` loads the selected resource. Its bucket count is at +0x0c and the far-pointer table starts at +0x2c. Target code constructs pointers into trailing variable-length records, advancing by each record's +0x22 word. Record type is at +0x21; type 4 clears 14 bytes from +0x2a, while other types clear words +0x2a and +0x2c.

The error string is `CANNOT LOAD WINDOW %03x` at DGROUP BD3C, immediately following `_win_ObjAddr`'s message at BD12, per `evidence/experiments/window-string-identity/target-crossrefs.json`. The exact literal in an isolated candidate did not establish its original DATA placement. Strict comparisons also retained a CONST selector placement failure and substantial body differences. The next discriminating question is whether reviewed unit/data-context evidence can account for the string contribution and selector ordering while a revised readable body reproduces the record traversal. Do not import/pad based on the adjacent offsets alone.

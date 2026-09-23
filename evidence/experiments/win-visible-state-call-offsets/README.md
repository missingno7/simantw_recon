# `_win_SetObjVisibleState` call and type evidence

This note records scoped evidence from job `win_SetObjVisibleState-ce8255970f`. It does not promote a source candidate.

## Ordinary call offsets

The target's far-call offset words agree with the MAPSYM publics. The `?? ??` bytes in the packet are the separately relocated selector words.

| Target site | Ordinary offset bytes / decoded target | MAPSYM public |
|---|---|---|
| `+0x74` clip start | `0x3DFA` | `_MSClipStart`, segment 2 offset 15866 |
| `+0xA2` rectangle invert | `0x0EB2` | `_GRectInv`, segment 2 offset 3762 |
| `+0xC7` set attributes | `0x19B4` | `_GSetAttrib`, segment 2 offset 6580 |
| `+0x10B` clip start | `0x3DFA` | `_MSClipStart`, segment 2 offset 15866 |
| `+0x12D` set attributes | `0x19B4` | `_GSetAttrib`, segment 2 offset 6580 |
| `+0x14F` clip end | `0x3E4C` | `_MSClipEnd`, segment 2 offset 15948 |

The near calls also decode to their MAPSYM publics: `_win_DrawObject` at `0xBB44` (segment 7 offset 47940) and `_win_DrawBitMap` at `0xBD5A` (segment 7 offset 48474). `_win_DrawBitMapAtObj` is at `0xBE30` (segment 7 offset 48688); the target calls it as a near call after `PUSH CS`.

Earlier attempt summaries treated the relocation record's `internal segment 2 / offset 0` as evidence that the helper target offset was wrong. That interpretation was incorrect: the NE relocation is on the selector half of the far pointer, while the ordinary offset word carries the public address. Do not use that record alone to reject these helper bindings.

## Type dispatch

Corrected attempt 08 candidate 0000 uses a signed `char` local for the fetched one-byte type, while keeping the object field one byte wide. Its output matches the target from `mov al, [type]` through `cwde`, `cmp ax, 17`, the branch checks, `dec al`, and the two `sub al` checks. The corresponding `int` local generated `sub ah, ah`; an earlier batch with a mistakenly widened struct field is invalid for field-layout conclusions.

This is a local code-shape result only. The whole candidate still fails strict admission: the remaining selector/index expression, bitmap-call argument shape, and surrounding call/return layout differ, and the complete member has unresolved fixup/private obligations. No production reissue follows from this note.

## Sources

- `evidence/recovery/workflow/jobs/win_SetObjVisibleState-ce8255970f/packet.json` (target bytes and decoded operands)
- `evidence/symbols/inventory.json` (MAPSYM segment and offsets)
- `evidence/recovery/workflow/jobs/win_SetObjVisibleState-ce8255970f/attempt08/candidate0000.diff.txt` (signed-type dispatch comparison)
- `evidence/recovery/workflow/jobs/win_SetObjVisibleState-ce8255970f/attempt08/results.json` (strict whole-member result)

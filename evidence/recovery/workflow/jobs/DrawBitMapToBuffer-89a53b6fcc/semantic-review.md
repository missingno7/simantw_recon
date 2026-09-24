# Semantic review: `_DrawBitMapToBuffer`

No candidate or strict test was made. The readable candidate remains the original TODO.

## Target-supported facts

- The target packet is the 1004-byte `GR_MODULE` extent. Its prologue and argument reads span `[bp+6]` through `[bp+0x18]`; the two output stores at `0x224-0x22d` write through far pointers. This is consistent with ten stack words (including far-pointer segments), but does not by itself establish named C parameter types.
- At `0x0006-0x0084`, the routine loads and locks a database object, tests the first word for `0xffff`, reads a data pointer from object offset `+2`, allocates/locks a temporary buffer, initializes unpack state with the object data at `+4`, and makes three `_Unpack` calls. One decoded word at local `-0x18` controls subsequent paths. The object and temporary-buffer branches converge on different bitmap metadata sources.
- At `0x00ee-0x0208` and `0x024a-0x03b4`, display type, metadata flags, and dimensions select among `_ConvertBitmap2`, `_CopyBitmap2`, `_CopyMonoBitmap`, `_ConvertMaskBitmap2`, `_CopyMaskBitmap2`, and `_CopyMonoMaskBitmap`. The common helper calls pass ten words, including far source/destination pointers and dimensions/cropping values. The second set also reads width/height at bitmap offsets `+8/+0xa` and uses source pixels at `+0xc`.
- The admitted `src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c` supports a 40-byte monochrome DIB header, one plane, one bit per pixel, and four-byte scanline alignment for that Windows API path. It does not establish the custom `_CopyMonoBitmap` contract or this routine's allocation/cropping geometry.

## Concrete blocker

`evidence/recovery/workflow/jobs/CopyMonoBitmap-13ceb70b88` and `evidence/recovery/workflow/jobs/Unpack-eb831e61b7` are `OPEN`, not admitted implementations; their readable candidates are TODOs. `_UnpackInit` also remains `ESCALATED`, and its job candidate is not in `src/recovered`. The admitted `UnpackSetBuf` source only stores a destination pointer and size in private state. Thus there is no admitted implementation establishing how the three unpack calls consume their packed input or lay out the decoded bitmap, and no admitted custom mono-copy source establishing the bit/row geometry and clipping behavior.

The call graph therefore establishes the broad decode-and-dispatch purpose but leaves central source semantics underdetermined. A plausible C draft would have to invent helper contracts, branch-specific metadata shape, and cropping/returned-dimension behavior across both branches. That does not justify a first candidate or strict compile/match attempt under the assignment's evidence limit.

## Exact next experiment

Admit or otherwise obtain readable, proof-backed `_Unpack` and `_CopyMonoBitmap` implementations first. Then map each of the ten pushed words at target offsets `0x00ee-0x0177` and `0x024a-0x02fb` against those helper declarations and their directly related bitmap callers. In particular, establish the object header's decoded fields and the source/destination row geometry before writing the target candidate.

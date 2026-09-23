# RallocFindMem: bounded ordinary trials

The target is 329 bytes at `GR_MODULE:56A8`. KERNEL ordinals 25, 15, 17 and 169 are `GlobalCompact`, `GlobalAlloc`, `GlobalFree` and `GetFreeSpace` in the factory packet. DGROUP 087C-0881 holds three zero words. The initialized strings start at 0882 (`Free: %lu Size: %ld\n`), 0897 (`Out of memory.  Terminating Program.`), and 08BC (`Running low on memory.  Pausing game.\nRefer to manual`). These are direct fixture observations; the names and common C object in the candidate are hypotheses.

| Attempt | Question and change | Authentic result |
| --- | --- | --- |
| 1 | First semantic draft, KERNEL calls and low-memory paths | 329 candidate bytes; 112/117 opcode diagnostic; target/candidate branch destinations differ because the reset and direct-return cases were wrong. Private strings emitted in warning-first order. |
| 2 | Put `lowMemoryReported = 0` inside reserve initialization and return directly when enough memory exists | Branch discrepancies fell from six to two; the candidate is still 329 bytes and differs first at offset C4. |
| 3 | Register-resident snapshot of the warning flag | Same assembly shape as attempt 2; C7 canonicalized it. |
| 4 | Explicit branch to the out-of-memory label | Same assembly shape as attempt 2; C7 canonicalized it. |
| 5 | Replace three separately emitted literals with a named contiguous three-field message object in target order | Candidate `_DATA` is now byte-identical to the 118 target bytes at 087C; code remains 330 bytes against 329. This is the preserved best source in `candidate.c` and `attempt05/candidate0000.c`. It is **not** an admitted body or proven historical object declaration. |
| 6 | Increment the flag under the proven zero branch instead of assigning one, to test the target DX load and OR | Worsened code shape to 327 bytes; this source is retained in the attempt record and rejected for continuation. |

The first structural residual is target `mov dx,[0880]; or dx,dx; jne` versus candidate `cmp word ptr [flag],0; jne` at C4. It shifts the first `_PopMsg` call by one byte, so its apparent far-call translation mismatch is not yet independent evidence of a call-ABI problem. The target and candidate disagree on private offset/fixup placement until complete code alignment is restored; no binding shortcut is justified. Compare an admitted analogue where a tested flag value remains live in DX, or find another semantic use of the value before spending the remaining two production attempts. Preserve attempt 5 as the current hypothesis.

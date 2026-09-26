# MSC 7.00 local allocation model

Measured with the catalogued compiler and flags through `search.py`. Full sources, compiler receipts, OMF disassembly, target diffs, and strict results are in [`../evidence/experiments/regalloc/README.md`](../evidence/experiments/regalloc/README.md) and [`results.json`](../evidence/experiments/regalloc/results.json). In the examples below, the result JSON has the complete emitted function.

## Register choice

**At most two eligible scalar word values are kept in SI/DI; frequency wins, declaration order breaks ties.** Minimal equal-use control [`r3_register_tie_ab.c`](../evidence/experiments/regalloc/sources/r3_register_tie_ab.c):

```c
register int a = a0, b = b0;
for (i = 0; i < n; ++i) { Touch(a); Touch(b); a += b0; b += a0; }
```

Observed: `mov si,[bp+6]` for first-declared `a`, `mov di,[bp+8]` for `b`; swapping declarations in `r3_register_tie_ba.c` swaps which argument initializes SI and DI. In [`r3_register_three.c`](../evidence/experiments/regalloc/sources/r3_register_three.c), the first two word values use SI/DI and the third is loaded to `[bp-2]`. In [`r2_loop_weight.c`](../evidence/experiments/regalloc/sources/r2_loop_weight.c), the twice-used and updated `looped` value is in SI while `once`, used only after the loop, stays at `[bp-4]`. In [`r2_register_ba.c`](../evidence/experiments/regalloc/sources/r2_register_ba.c), the hotter `hot` gets SI even though `mid` is declared first; putting a cold reference first in `r2_weight_reuse.c` does not beat repeated loop use. `r3_tie_ab.c` and `r3_register_tie_ab.c` compile to the same object hash, so `register` does not force a different allocation in that tie; it is a hint. This is an observed ordering, not a numerical cost formula.

**Type and observability affect eligibility.** [`r2_char_hot.c`](../evidence/experiments/regalloc/sources/r2_char_hot.c) keeps its byte value in a byte stack slot (`mov byte ptr [bp-3],al`) while word locals take SI/DI. [`types_char_int_nearptr.c`](../evidence/experiments/regalloc/sources/types_char_int_nearptr.c) uses BX/DI for a near pointer/index (`mov bx,cx; mov ax,[bx]`); an ordinary far pointer needs a segment:offset pair and is accessed with LES. An addressed scalar in [`r2_address_hot.c`](../evidence/experiments/regalloc/sources/r2_address_hot.c) is stored to `[bp-0xa]` before `&hot` is passed, while other eligible words remain register candidates. Volatile scalar controls likewise perform reads/writes through their stack slot.

## Homes and calls

**A far call alone does not spill live scalar registers.** [`r2_live_two_registers.c`](../evidence/experiments/regalloc/sources/r2_live_two_registers.c) has `push si; lcall ...` and later reuses SI. [`r2_setjmp.c`](../evidence/experiments/regalloc/sources/r2_setjmp.c) also keeps the live parameter in SI across setjmp/longjmp calls. When a scalar's address escapes, [`r3_delayed_address.c`](../evidence/experiments/regalloc/sources/r3_delayed_address.c) writes the local's BP home before the intervening call; it does not show a deferred post-call home. Probes of setjmp, `volatile`, address-taking, and post-call CFG shapes did not reproduce `_DoExpMenu`'s paired `mov [bp-4],di` / `mov [bp-2],si` after `SetPause(1)`. That specific trigger remains unresolved by these controls.

**Parameter copies are optimized according to use, not their spelling.** [`r4_direct_param.c`](../evidence/experiments/regalloc/sources/r4_direct_param.c) and [`r4_register_param.c`](../evidence/experiments/regalloc/sources/r4_register_param.c) emit identical code when the parameter itself is updated. [`r4_copy_param.c`](../evidence/experiments/regalloc/sources/r4_copy_param.c) uses a separate accumulator and produces a different setup (`mov si,[bp+6]`). A local copy can expose a distinct value, but a `register` declaration alone does not guarantee a distinct allocation.

## Frame layout and far pointers

**Declaration order changes stack operand identity; do not assume a universal reverse order.** [`frame_order.c`](../evidence/experiments/regalloc/sources/frame_order.c) and [`frame_order_reverse.c`](../evidence/experiments/regalloc/sources/frame_order_reverse.c) reserve the same `ENTER 0xa`, but reversing mixed char/int/long declarations changes the BP offsets used by each value. Scope is shape-dependent: [`r3_array_nested.c`](../evidence/experiments/regalloc/sources/r3_array_nested.c) and `r3_array_flat.c` happen to compile identically (`ENTER 0x10`), while the block-scope case documented for `_MakePillFood` in [`grinder-lessons.md`](grinder-lessons.md) grows its frame from `ENTER 8` to `ENTER 0xe`. Keep the target's declarations, lifetimes, and blocks when testing homes.

**A far-pointer object kept observable in memory is homed as four bytes and reloaded with LES.** In [`far_pointer_volatile.c`](../evidence/experiments/regalloc/sources/far_pointer_volatile.c), `int far * volatile p = input;` emits `ENTER 4`, stores the offset/selector to `[bp-4]`/`[bp-2]`, then emits `LES BX,[bp-4]`. The plain-pointer control uses the incoming far argument directly. `volatile` here qualifies the pointer object; it is different from `volatile int far *p`, which qualifies the pointee. The target-profile `_InitAntLions` and `_DrawSimKid` controls show the same stack-home/LES pattern when pointer objects are made volatile.

Under `/Oeglw`, [`og_pressure_home.c`](../evidence/experiments/regalloc/sources/og_pressure_home.c) keeps two local sums in SI/DI and homes further sums at `[bp-2]`/`[bp-4]`, including across a far call. [`og_cse_home.c`](../evidence/experiments/regalloc/sources/og_cse_home.c) reloads far globals after a call that may change them. These controls distinguish global `/Oe` allocation from the baseline selection effects.

## Target trials

The measured rules guided searches for `_GetMyBestDirs`, `_SimQueenR`, `_AnimYellowInsane`, `_DoExpMenu`, `_DrawSimKid`, `_InitAntLions`, and `_RallocFindMem`. Candidate sources and complete strict results are in the target rows of `results.json`; none of these allocation-only variants is a complete match, so none was promoted. The trials still narrow specific mismatches: volatile far-pointer objects reproduce LES homes, while declaration swaps alone do not repair the GetMyBestDirs/DoExpMenu registers, volatile struct-member qualifiers do not repair DrawSimKid frame layout, and snapshotting the RallocFindMem flag does not change its DX test scheduling.

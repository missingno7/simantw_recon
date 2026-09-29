# MSC 7.00 register and home allocation (recovered from C23216)

**Status: recovered and validated.** The global register allocator and the stack-home allocator of
`toolchain/msc700/BIN/C23216.EXE` were read out of the compiler itself by running the unmodified
pass under Unicorn and tracing it. The rules below are transcriptions of that code, validated against
the compiler on every admitted source. Worker `f-alloc-emu` (2026-09-29); evidence in
`evidence/codegen-facts/MSC7-A-emu/`.

## Tools

| Tool | What it does |
|---|---|
| `tools/c2_emu.py` | Runs C13216, C23216 and C33216 (unmodified DOSX32 images) under Unicorn with the ~24 MS32KRNL Win32 imports implemented in Python. `compile_c(source, flags)` returns the object; `python tools/c2_emu.py SRC.c --symbol _Sym`. **All 406 admitted sources give objects byte-identical to the DOSBox compiler service** (~0.2 s per compile, no DOSBox). Diagnostic only; admission still uses `search.py`/`promote.py`. |
| `tools/alloc_trace.py` | Per compiled function: every allocation candidate (live range) with name, class, block range, loop depth, uses, degree, weight, flags, colouring order, decision, picked register, re-pick, unassign, payoff drop and final register. `python tools/alloc_trace.py DRAFT.c --symbol _Sym [--events]`. |
| `tools/regalloc_model.py` | Executable Python model of the allocator (colouring, post-colouring passes, home colouring). `python tools/regalloc_model.py DRAFT.c --symbol _Sym` compares model and compiler; `--homes` prints the home (stack-slot) colouring with weights. |

`alloc_trace` legend in the `picked` column: `si>bx` = picked SI, re-picked to BX (0x442628);
`!` = unassigned by the boundary-cost check (0x442040); `$` = dropped by the payoff check (0x442fac).

## Pipeline (C23216 addresses, image base 0x400000)

`0x44dd80` (per function) calls `0x43edd4` when `/Oe` is on. `/Oe` reaches C2 inside the IL, not on
its command line: C1 sets bit 0x10 of the function header byte in the `EX` file.

1. **Candidates** (`0x43f09c`, walker `0x43f27c`, recorder `0x43fc18`). Blocks are walked in block-list
   (source) order, statements in order, each IL tree depth-first, left child first. Every reference to
   a register-eligible variable or compiler temporary adds to the `uses` of the variable's candidate
   ("range") for the current loop region, creating the range on first reference. Ranges of one variable
   are linked in a ring. Per-reference increments (IL level, after C1/C2 local folding):
   * read (LOAD of `&var`): 2; 1 when the node is a shared (already visited) subtree; 0 when it is the
     plain source of a copy assignment;
   * definition (ASSIGN to `&var`): 2 (+1 when the assignment is nested inside another address or
     assignment context);
   * compound assignment / `++` / `--`: 3 (+1 when nested);
   * address taken outside a LOAD/ASSIGN (`&var` as a value): 2 and the range becomes non-allocatable;
   * a use inside an address computation sets flag 0x40 ("index use"), which steers the register choice.
   Class: 1 byte, 2 word (int, near pointer), 3 segment part of far addresses.
2. **Interference** (`0x441020`): two ranges of the class interfere when their block-order intervals
   `[first, last]` overlap; `degree` = number of interfering ranges with `uses > 0`.
3. **Weight** (`0x440edc`):
   `weight = uses * 16 * 4**depth // (degree + 1) + 0x8000`, where `depth` is the loop nesting depth of
   the range's **last** block. A range with `uses == 0` gets
   `16 * 4**depth // ((degree + 1) * 2) + avg/2`, `avg` = mean of `weight - 0x8000` over the other
   ranges of the variable with weight >= 0x8000 (no 0x8000 bias, so zero-use ranges sort last). +1 for
   flag 0x10.
4. **Non-allocatable** ranges (flag byte 0x2e & 4: address taken, volatile, ...) go straight to the
   spill list (`0x440fe8`).
5. **Trivially colourable** pass (`0x441274`, list order): a range whose degree is below the number of
   free registers of its class in its own mask, and which finds a free register in every block of its
   range, is committed immediately.
6. **Sort** (`0x441330`): insertion sort by weight, descending. Equal weights: the element that comes
   **later** in the input list is placed first. The input list is in reverse creation order, so among
   equal weights **the earlier-created range (first referenced in the walk) comes first**.
7. **Selection** (`0x441404`): take the head; scan following ranges while `weight >= 80%` of the head's
   (on `weight - 0x8000`): a range with strictly more `uses` becomes the choice; at equal weight a range
   with a connected (copy-related) range already committed is preferred. The choice is committed if every
   block of its range has a free register of the class (`0x441658`), else spilled.
8. **Register choice** (`0x441a80` through `0x466a20`), over the committed list sorted by weight:
   first a same-weight range whose connected range or same-variable ring member already has a register
   is given that register if possible; otherwise the head gets, with its mask (registers already given
   to interfering ranges, plus the registers each block of the range needs or clobbers, e.g. CX/DX in
   blocks with calls, DI/CX around inline string instructions; the block masks are set by `0x467104`):
   * index-use ranges (flag 0x40): **SI**, then **DI**, then DX, CX;
   * other ranges: **DX**, then **CX**, then SI, DI.
   (SI is not taken when both DI and BX are busy, and symmetrically for DI.) The chosen register is then
   marked busy in the masks of every interfering range and every block of the range.
9. **Boundary cost check** (`0x4418c8` + `0x442040`): per variable, each register range is charged for
   the moves its edges need (8 per load/store from memory, 2 per register-register move, times the
   edge's loop frequency) against `benefit = 4**depth(first block) * uses * 4`; a range is unassigned
   when `(cost - saved) * 4 > benefit * 3`, when its benefit is 0 and nothing is saved, or when it is a
   pointer range with `uses <= 2`. The saving factor starts at 8 and drops by 4 while the variable's
   total `benefit * 3 < cost * 4`. (A rare range split, `0x441fdc`, is not modelled.)
10. **Whole-variable re-pick** (`0x442628`): for a variable in CX/SI/DI, recompute the union of the block
   masks of all its ranges; **if BX is free in all of them and not both SI and DI are busy, the whole
   variable moves to BX**; else an index-use variable may move between SI/DI, others to DX/CX.
11. **Payoff drop** (`0x442fac`): for SI, DI (and CX in one function kind), if the ranges holding the
   register need boundary moves and `moves + 1 > uses` summed over them, all of them lose it.
12. **Homes** (`0x445f14`): the spill list (spilled ranges plus register ranges that still need a memory
   copy) is merged per variable, re-weighted with the same formula over the spill set, averaged over the
   variable's ranges and divided by the variable's size; sorted with the same insertion sort; each home
   is then placed first-fit from BP downwards (`0x439628`, word alignment `0x467d38`), avoiding only the
   slots of interfering, already-placed homes. **The heaviest home is nearest BP; homes that do not
   interfere share a slot.** Offset = `-(slot + size)`.

## Operand order of commutative operators (sortnode, `0x432a74`/`0x432ce4`)

Before allocation C2 orders the children of commutative operators by a key: high word = cost class of
the subtree (leaf 0-1, load 2-3, binary op sum+2, call 7), low word = sum of the children's keys plus
the opcode, where a symbol leaf contributes its **symbol sequence number** (sym+6: the order in which the
symbol was declared in the translation unit; parameters, then locals in declaration order). The larger
key goes left. Consequences:
* declaration order can decide `a + b` versus `b + a` (and with it `mov bx,di / add bx,si` versus
  `mov bx,si / add bx,di`) when the cost classes tie;
* the number of symbols declared between two operands' symbols matters (low word is a sum);
* because the allocator's walk visits the left subtree first, the operand order also sets the creation
  order and so the tie-break of step 6.

## Validation (emulator vs model, all admitted msc700 sources)

| Stage | Result |
|---|---|
| Emulated objects vs DOSBox service | 406/406 byte-identical |
| Colouring (steps 4-8) | 781/781 function/class instances, 4,177/4,177 range registers |
| Final registers (steps 4-11) | 933/936 functions; the 3 misses all contain the unmodelled range split |
| Functions with SI/DI | 382/384 exact |
| Homes (step 12, from C2's spill list) | 482/482 functions, 849/849 slots (155 functions with >= 2 homes) |

By profile (final registers): baseline 468/469, og 276/278, ogi 129/129, oi-ga 58/58, ga 1/1, oi 1/1.

## Using it on a residue

1. `python tools/alloc_trace.py DRAFT.c --symbol _Sym` and the aligned diff (`search.py`) side by side.
2. SI/DI swapped between two ranges with **equal weight**: the earlier-created one got SI. Change which
   is referenced first (statement order, operand order), or give the intended one one more use / one
   less degree. Declaration order only matters through operand order (sortnode).
3. **Different weights**: count uses (read 2, write 2, compound 3), loop depth of the range's last
   block, and degree; the lever is an extra or missing reference, or a range that ends in a different
   loop.
4. **BX instead of SI/DI** (or the reverse): step 10 - BX was (not) free in every block of the
   variable's ranges.
5. **Home order**: `python tools/regalloc_model.py DRAFT.c --symbol _Sym --homes` lists the home
   weights; the heaviest (per byte) is nearest BP, ties go to the earlier list position.
6. Recompile variants with `tools/c2_emu.py` (0.2 s) before spending DOSBox time.

## Superseded

`tools/msc7_alloc.py` (source-level approximation with a guessed 4x loop factor, 40% SI/DI agreement)
and the MSC7-X2 read-count rule are superseded by the recovered rule above.

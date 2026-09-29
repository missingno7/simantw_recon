# MSC7-A5..A12: the allocator read out of C23216 (emulated passes)

Worker f-alloc-emu, 2026-09-29, worktree `D:\Prog\simantw_wt_c2`. Rule write-up: `docs/msc7-allocator.md`.

## Method

`tools/c2_emu.py` runs the unmodified C13216/C23216/C33216 DOSX32 images under Unicorn 2.1.4. The
passes import 24 Win32 functions by ordinal from MS32KRNL.DLL; the ordinals are resolved through the
DLL's own export table and implemented in Python over an in-memory file system. CL's pass flags were
captured under DOSBox for every catalogued profile (`cl_pass_flags.json`) and are reproduced by
`c2_emu.CLFlags`. The allocator was located by a differential trace (functions that run only when the
C1 IL carries `-Oe`) and read instruction by instruction; `tools/alloc_trace.py` hooks it and
`tools/regalloc_model.py` re-implements it.

## Results

| File | Content |
|---|---|
| `emulator_vs_dosbox.json` | 406/406 admitted sources: emulated object byte-identical to the DOSBox compiler service |
| `colouring_model_validation.json` | colouring model vs C2: 781/781 function/class instances, 4,177/4,177 ranges |
| `final_register_model_validation.json` | colouring + post passes vs C2's final registers: 933/936 functions (misses = unmodelled range split) |
| `home_model_validation.json` | home colouring vs C2: 482/482 functions, 849/849 slots |
| `og_simant_9D04/` | SubtractFood exact and XferPatch body-exact under `og`; profile invariance of the admitted simant:9D04 units |
| `scripts/` | the validation and sweep scripts (worker copies; run from the worktree root) |

## Proposed register entries

* **MSC7-A5 (VERIFIED)**: `tools/c2_emu.py` reproduces CL's objects byte for byte (406/406 admitted
  sources, all profiles) without DOSBox, ~0.2 s per compile.
* **MSC7-A6 (VERIFIED)**: range weight = `uses*16*4**depth(last block)//(degree+1) + 0x8000`;
  degree = overlapping ranges with uses; zero-use ranges `16*4**depth//((degree+1)*2) + avg/2`.
* **MSC7-A7 (SUPPORTED, RE + toys)**: use increments per IL reference: read 2 (shared node 1, copy
  source 0), definition 2, compound/`++` 3, +1 when nested in an address/assignment context; `&var`
  as a value makes the variable non-allocatable; a use inside an address sets the index flag 0x40.
* **MSC7-A8 (VERIFIED)**: equal weights are ordered by creation (first reference in the block /
  statement / left-subtree walk): the earlier-created range is coloured first and gets SI. An 80%
  weight window lets a range with more uses jump ahead.
* **MSC7-A9 (VERIFIED)**: register order: index-use ranges SI, DI, DX, CX; others DX, CX, SI, DI;
  then a whole-variable re-pick moves a variable to BX when BX is free in every block of its ranges
  (and not both SI and DI are busy), and SI/DI are dropped when their boundary moves outweigh uses.
* **MSC7-A10 (VERIFIED)**: homes are coloured like registers: per-variable averaged weight divided by
  size, sorted descending, first fit from BP; non-interfering homes share slots.
* **MSC7-A11 (SUPPORTED)**: commutative operands are ordered by a key whose low word sums symbol
  declaration sequence numbers; declaration order (and the number of symbols declared in between) can
  swap `a+b`. Exact case: `_SubtractFood` under og needs `int column, row;` (`row, column` gives the
  swapped `mov bx,si / add bx,di`).
* **MSC7-A12 (VERIFIED)**: `/Oe` reaches C2 in the IL (EX header bit 0x10), not in `MSC_CMD_FLAGS`.
* **Supersedes** MSC7-X2's read-count rule and tools/msc7_alloc.py; refines F1A/F1F (home order is
  weight order, with the loop and degree terms), F2/F3 (two index registers; loop factor 4 per level on
  the range's last block), R1-R3 (ties go to the earlier-created range), R13/F7/F8 (declaration order is
  irrelevant for the allocator itself, but can matter through operand order, A11).

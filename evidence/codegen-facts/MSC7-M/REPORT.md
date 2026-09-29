# MSC7-M: memory-dependent compilation study (2026-09-29, Opus 5.5 unblocking agent)

This study ran in the isolated worktree `D:\Prog\simantw_wt_c2`. The full raw results (14 MB) are in
`build/workers/f-study-bm/results/` there. This directory keeps the summary, the scripts, the C2 module
map and the text result tables.

## Question

Does memory-dependent compilation explain the allocation wall: about 58 near-exact functions whose last 1-10% is SI/DI/CX choice or
stack-home order? The leads were Microsoft's C7PATB note ("compiling the same source file twice may produce different size
.OBJ files when compiling under Windows") and an earlier finding that C2 output differs at `-Bm` 8/16.

## Verdict: FALSIFIED for the allocation wall

- **What `-Bm` is.** CL always passes `-Bm 2048`. The value is fixed in CL.EXE (VA 0x4205a4, set from its option table), not
  computed from free memory. An undocumented `/Bm<n>` overrides it. In C2 it is a KB cap on the pool heap, checked at 0x4231d8.
- **What happens when the heap runs out.** Whether the cap is hit or a real malloc fails, the outcome is binary.
  - The first time, C2 prints warning C4703 and recompiles the whole function without global optimisation. The result is
    byte-identical to `/Ow`.
  - The second time, it stops with fatal C1002.
  - There is no intermediate mode.
- **Payoff sweep.** 1,490 end-to-end compiles covered all 26 frontier/best drafts of the 15 parked functions, for every `/Bm`
  value from 1 to 128 KB and up to 2048. Each draft shows only three regimes: fatal, C4703-degraded, or normal. Normal starts
  at 7-120 KB, and every degraded object scored worse.
- **Reachability.** Compiling inside the admitted unit raises the threshold by only 0-6 KB, so 2048 KB is unreachable, and any
  shortfall would have printed a warning. DOSBox memory of 4-128 MB, with or without C7PATB, gave byte-identical objects.
  C7PATB flips one flag byte in CL.EXE and MS32KRNL.DLL ("DPMI virtual memory supported"); C1/C2/C3 are untouched.
- Nothing became exact.

## New effect: heap phase (MSC7-M5)

- C2 sometimes reserves an unused dead copy of a struct or array local in the frame. Whether it does depends on the 16-byte
  alignment phase of its heap.
- The phase is shifted by the length of the TMP path (period 16 characters) and by the functions compiled earlier in the same
  file. Replaying identical C1 output through C2 alone reproduces it.
- Only the ENTER size and BP offsets change, never registers.
- 9 of 333 open drafts vary with the phase: AddIndex, FileSelect, MakeBalloon, Mini_DrawMapI, ProcessPost, UpdateListBox,
  myBeginSong, EditToolsMenu, GtRegisterClass.
  - At some phases three reach the target frame: AddIndex 0x18, myBeginSong 0x150, GtRegisterClass 0x4e.
  - GtRegisterClass then reaches 32/32 opcodes with only its window-proc binding left. Its "hidden 26-byte temporary" is a
    heap-phase effect, not source.
  - AddIndex compiled inside its admitted unit, at the normal TMP, gets the target frame: stack differences drop from 27 to 13,
    and the unit's five admitted functions stay byte-identical.
- Controls:
  - All 406 admitted sources stay exact with TMP=`W:\`, which is what the compiler service uses.
  - Under the reference batch runner's `W:\B0000` (tools/compiler.py), two admitted `/Oegilw` units stop reproducing:
    tu_gr_7712_IsMMMidiAvail_21 and tu_text_7370_NbFinalStatus_14.
  - Across all 16 phases, all 23 admitted `/Oi` sources are exact only when TMP length mod 16 is in 2..5.

## Facts (recorded in docs/msc7-codegen.md)

| ID | Status | Rule |
|---|---|---|
| MSC7-M1 | VERIFIED | `-Bm` is a fixed KB cap on C2's pool heap. C7PATB does not change it. |
| MSC7-M2 | VERIFIED | Heap exhaustion gives C4703 plus code identical to `/Ow`, or fatal C1002. |
| MSC7-M3 | FALSIFIED | Memory limits explain the allocation residues. |
| MSC7-M4 | VERIFIED | C7PATB is a one-flag loader change with no code-generation effect. |
| MSC7-M5 | VERIFIED | A heap-phase dead-copy reservation changes the frame size and BP offsets only. |
| MSC7-M6 | SUPPORTED | The admitted phase window is TMP length mod 16 in {2..5}. |
| MSC7-M7 | SUPPORTED | Frame residues of phase-sensitive functions must be judged in unit context. |

## Recommended next steps (agent)

1. Tooling:
   - pin the heap phase, i.e. the TMP path length of every runner, and add a regression test on the two sensitive units;
   - never choose the phase per function; it comes from the real unit context.
2. Allocation wall: the allocation is deterministic given C2's input. Run C2 under Unicorn:
   - `c2_image.py` maps the executable; C2 reaches the DOS extender through about a dozen thunks that are easy to stub;
   - `c1cap.py`/`direct23.py` already reproduce CL's object from C2 plus C3;
   - instrument the register-allocation modules (`c2_function_modules.json`) to log SI/DI candidate weights and the actual
     tie-break rule.

# Differential emulation diagnostic

`tools/emu_diff.py` executes a function from the oracle NE image and a C candidate compiled under that symbol's assigned MSC 7.00 profile. OMF fixups map candidate references into the same synthetic selector space as the oracle. The compiler cache and the strict object matcher are used for staging, but this sampled behavioral diagnostic is not an admission proof.

```powershell
python tools/emu_diff.py _Symbol build/workers/me/candidate.c --runs 100 --seed 10
python tools/emu_diff.py _Symbol build/workers/me/candidate.c --arg count=4 --arg item=0xF000:0xA000 --stub USER!#125=0x1234:0
python tools/emu_diff.py _Symbol build/workers/me/candidate.c --strict --memory zeros --null-far-pointers keep
```

`--arg` overrides a named source parameter with a 16-bit word or a far pointer in `offset:selector` form. Unspecified arguments get deterministic values. Direct scalar globals discovered at reads vary on later samples. `--stub CALLEE=AX[:DX]` scripts an imported Windows/OS call's return. Calls retain raw pushed words and include MAPSYM symbol+offset labels for recognized near/far pointer candidates.

## Default comparison

The default `observable` mode filters local stack-frame writes. Writes to globals, far objects, and other mapped memory are compared by their final byte values, so harmless write-order differences do not diverge. Calls are compared as a multiset by callee, pushed argument values, recognized pointer labels, scripted result, and a hash of the observable memory state at the call. Reordered writes or calls are reported only when the final memory differs or the call sees a different memory state. Return comparison uses the candidate definition's declared 16-bit ABI width: `AX` for `int` and near pointers, `DX:AX` for `long` and far pointers, and no register value for `void`. For an unresolved return typedef, both registers are compared conservatively.

`--strict` includes all stack writes in addition to observable writes. The report gives the first differing target instruction offset and its target basic block when the difference comes from an instruction in the target function. If the candidate introduces a write or call with no target counterpart, the target offset is `null` and the candidate offset is provided.

Far call arguments that point into the current stack frame are identified as local pointers. Their raw frame offsets are normalized in the default comparison because MSC frame layout can move a local object while preserving the call's meaning; `--strict` retains stack writes for diagnosing those layout differences. Pointers into mapped globals and far objects retain their MAPSYM symbol+offset identity and are compared exactly.

## Executed code and synthesized memory

Calls into original game code and Microsoft runtime helper code execute from the oracle image on both sides. This includes helpers such as `__aFulmul`, `__aFlmul`, `__aFldiv`, `__aFlrem`, `__aFlshl`, and `__aFulshr` when their MAPSYM code is present. Only imported Windows/OS entries are stubbed. An unresolved candidate external is unsupported instead of receiving an invented stub.

An unmapped read, write, or fetch lazily maps a page filled with bytes derived from the sample seed and linear page address. `--memory zeros` selects zero-filled pages. The same seed and address produce identical contents on both sides. Unknown far selectors loaded through `LES` or `LDS` use a synthetic segment so their real-mode linear address cannot alias unrelated NE fixture data. By default, a null global far pointer used by `LES`/`LDS` is seeded with offset `0x0100` in that synthetic segment; `--null-far-pointers keep` preserves its zero offset and then maps the unknown selector synthetically. JSON records all pages, selector substitutions, and seeded global far pointers used by each run.

Calls into imports still have scripted or default-zero behavior; their real Windows side effects are outside this emulator. DOS/BIOS service interrupts `10h`, `13h`, `16h`, `1Ah`, `21h`, and `2Fh` are recorded as OS calls and preserve registers unless a matching `--stub DOS!INTvv_AH=AX[:DX]` overrides `AX:DX`. Other interrupts, unresolved indirect calls, instruction-limit hits, self-modifying code, or Unicorn execution faults remain `UNSUPPORTED`. `NO_DIVERGENCE` means the requested samples agreed under the chosen inputs, stubs, and synthesized memory; it does not prove general equivalence.

Reports default to `build/emu_diff/SYMBOL.json` (compiles under `build/emu_diff/compile/`). Focused implementation tests are in `tests/test_emu_diff.py` and run with:

```powershell
python -m unittest tests.test_emu_diff -v
```

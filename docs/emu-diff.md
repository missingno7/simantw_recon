# Differential emulation diagnostic

`tools/emu_diff.py` executes one function from the oracle NE image and a C candidate compiled under that symbol's assigned MSC 7.00 profile. Both sides use the same synthetic real-mode-style selectors, oracle-backed NE data, shaped arguments, seeded global variation and deterministic call stubs. The candidate goes through the same profile resolution and compiler cache as `search.py`; OMF fixups are mapped by MAPSYM name into the oracle's synthetic address space.

```powershell
python tools/emu_diff.py _Symbol build/workers/me/candidate.c --runs 100 --seed 10
python tools/emu_diff.py _Symbol build/workers/me/candidate.c --arg count=4 --arg item=0xF000:0xA000 --stub _Lookup=0x1234:0
```

`--arg` overrides a named source parameter with a 16-bit word or a far pointer in `offset:selector` form. Unspecified arguments receive deterministic sample values; direct scalar globals found at reads are varied on later runs. `--stub CALLEE=AX[:DX]` scripts a callee's return value. Calls are recorded with the normalized callee and inferred stack argument words. Unscripted calls return zero. Each run uses the same initial state on both sides and a seed incremented from `--seed`.

The text report names the first difference in the ordered write/call trace or the final `DX:AX` return, with the target instruction offset and candidate offset when present. Writes are labeled with an oracle symbol and offset when known; stack writes retain their synthetic stack offset. The JSON contains all sampled run results, the target blocks reached, observed global reads, compiler/cache identity, the first divergence and any unsupported reason. Use `--json PATH` to choose the JSON path; otherwise the report is saved as `build/workers/f-infra-emu/SYMBOL.json`.

`NO_DIVERGENCE` means only that every requested sampled execution completed and the recorded traces and returns matched under these stubs. It is not a proof of general equivalence. A stack-local write mismatch may arise from different frame layouts or write ordering even when externally visible state agrees, so inspect the reported event and later trace before treating it as a source logic error. `DIVERGED` reports an observed trace or return difference. `UNSUPPORTED` never means equivalence: it covers execution faults, unmapped memory, unresolved relocations/layout, instruction-limit hits, self-modifying code, and unsupported helpers or instructions.

Floating-point instructions and MSC runtime helpers such as `__aF*` / `__ftol` are not emulated. DOS/Windows interrupts, unresolved indirect calls, and ambiguous private data placement are also unsupported. Calls into game code and USER/GDI/KERNEL imports are intercepted rather than run; their behavior is only as faithful as the chosen stub script. This tool cannot model a full Windows 3.x process, asynchronous callbacks, or side effects behind unstubbed APIs.

The emulator is diagnostic only. It does not alter candidate objects, establish exact source reconstruction, or participate in promotion. Strict admission remains the complete object/member and whole-image proof enforced by `promote.py` and `validate.py`.

# `_TEXT` compiler context findings

## Result

There is no single compiler profile for the entire `_TEXT` candidate range. Topology describes `text:6C62-8380` as a 39-public candidate range with 34 components and several semantic clusters. The assignments below scope the two families supported by strict profile evidence.

- **Memory helpers (`Ma:10` family):** `og`, flags `/AL /G2 /Gs /Oeglw /NT_TEXT`, recorded as `asg-text-8252-og`. `_MaLock` is `CONFIRMED_MEMBER` only under `/Og`; the evidence is minimal over baseline. The admitted `_Ma*` controls are unchanged in the catalogued optimizer-invariance corpus. `_MaMemCpy` and `_MaMemMove` still have source/body mismatches after recompilation under `og`.
- **NetBIOS wrappers (13 `_Nb*` publics plus `_CopyName`):** `ogi`, flags `/AL /G2 /Gs /Oegilw /NT_TEXT`, recorded as `asg-text-7cfe-ogi`. A readable `memset(ncb, 0, 64)` form for `_NbCheck` reaches `STRONGLY_SUPPORTED_MEMBER` only under `ogi`. The preserved byte-loop draft does not distinguish catalogued profiles. Recompiling the family under `ogi` promoted `_NbCheck`; `_NbFinalStatus` remains blocked on private string/data placement. `_NbImmediateStatus` remains an exact admitted control under the assignment.

The two assignments are scoped to explicit family symbol lists attached to their representative `text:` component IDs. They do not assign one profile to the mixed candidate range or to the other game C functions there.

## Compiler idiom experiments

The 90-job matrix exercised MSC 7.00 under baseline, `/Os`, `/Ot`, `/Oi`, `/G0`, `/Gr`, `/Zp1`, `/Zp2`, `/AS`, `/AM`, and catalogued `og`/`ogi`, plus the MSC 6.00A baseline. Each source is a small semantic probe; source hashes, flags, object hashes, decoded idioms, and compiler receipts are in [`results.json`](results.json).

- The 64-byte loop emits `mov cx, 0x20; rep stosw` under every valid tested profile, including MSC 6.00A.
- A zero-initialized aggregate followed by a command-byte overwrite emits a zero store to that byte plus `mov cx, 0x3f; rep stosb`; this is not the target's full 64-byte fill.
- A standard `memset(ncb, 0, 64)` call emits the target `mov cx, 0x40; rep stosb` only with `/Oi` enabled. Catalog profile `ogi` includes `/Oi`; `/Oi` is its minimal distinction from `og` for the `_NbCheck` source hypothesis. Baseline and the tested size/speed, CPU, register-call, packing, and memory-model switches leave it as a call.
- None of the tested arithmetic, union-byte, or byte-pointer swap sources emitted `xchg ah, al` under the MSC 7.00 switch matrix or MSC 6.00A baseline. `_FlipWord` remains unresolved at source form.
- `/Oi-` is not accepted by pinned MSC 7.00 (`D4002: ignoring unknown option '-O-'`), so those six rows are marked unsupported. The valid “off” control is the baseline profile without `/Oi`.

## Other families

`_FlipWord` has no catalogued profile discriminator. The `_GtRegisterClass` probe in the shared `text:7D3E` gateway component also has no profile discriminator; its current exact-body candidate still fails strict member placement. `_CheatKeys` remains a larger source/body mismatch (372/436 aligned opcodes), so no profile assignment was made for it.

## Promotions

- `_MaLock` — [promotion proof](../../recovery/promotions/MaLock-a034587316.json), profile `og`.
- `_NbCheck` — [promotion proof](../../recovery/promotions/NbCheck-fd43ce5af5.json), profile `ogi`, with the `memset` source form.

The original `_NbCheck` byte-loop profile-probe record is preserved in `results.json` under `initial_nbcheck_best_loop_probe_snapshot`; the live optimizer-profile probe file now records the separate `memset` source hypothesis used by the family assignment. The alternate source text and hash are also embedded in `results.json`.

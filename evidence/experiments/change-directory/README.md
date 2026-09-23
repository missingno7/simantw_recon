# `_ChangeDirectory` bounded recovery notes

Target job `ChangeDirectory-b005f31f9a` used all eight production attempts with no exact candidate. The full candidate sources and strict diffs remain under `evidence/recovery/workflow/jobs/ChangeDirectory-b005f31f9a/attempt01` through `attempt08`.

## Context

- Closed extent: 364 bytes in `ANTEDIT_MODULE`; packet profile is baseline `/AL /G2 /Gs /Oelw /NTANTEDIT_MODULE`.
- Build topology places this public in its own component `antedit:90DC`, with no assigned selector-pool or private-DATA words. Its larger surrounding ANTEDIT unit is `antedit:67C6-E9E9` (102 publics); this is unit context, not a request to change the profile.
- Adjacent `_SeparateFile` is separately recovered in component `antedit:9024` under `/Oeglw`. Its signatures for `lstrlen`, `AnsiPrev`, and `lstrcpy` are useful API evidence; its body and profile are not evidence for this function's source.
- Packet imports: USER ordinals 93 (`GetDlgItemText`), 101 (`SendDlgItemMessage`), and 473 (`AnsiPrev`); KERNEL ordinals 90 (`lstrlen`) and 88 (`lstrcpy`). `_strchr` is internal segment 4. `_Dx8` is segment 8 offset 0, named `SIMANT_DATA_GROUP`.

## Bounded hypotheses and results

The drafts model reading the directory edit control, rejecting wildcard paths, recognizing `0xC010`, scanning a path with `AnsiPrev`, splitting at `:` or `\\`, and refreshing `_UpdateListBox`. Attempts 2–3 tested parameter-copy ordering; attempts 3–4 refined the separator path. Attempts 5–8 tested how to express the segment-8 path buffers at `Dx8:0x9F10` and `Dx8:0x94A0`. Across the 16 submitted candidates, object hashes show 14 unique compiler outputs: the plain and `register` parameter-copy spellings duplicated in both batches 2 and 3, so those are one effective output class per batch.

Attempt 08's based-pointer cast produces the target's segment-8 selector relocation followed by literal offset `0x9F10` at both `lstrcpy` branches. This supports the segment/offset interpretation; it does not recover the member. The whole candidate is still `NO_COMPLETE_MATCH`: 372 candidate bytes versus 364 target bytes, 106/147 opcodes aligned, and only 1/13 fixups equal. Attempt 08 still has literal and uncovered NE-relocation obligations.

No candidate is admitted. The best readable draft still differs in initial parameter register homes, the `strchr` branch layout, pointer/register lifetimes through `AnsiPrev`, the prefix/suffix mutation and final segment-8 copy sequence. The candidate's byte-at-a-time copy does not explain the target's `REPNE SCASB` / `REP MOVS` sequence. Do not repeat the tried parameter-order, separator, `Dx8+offset`, `MK_FP(FP_SEG(Dx8), offset)`, or based-pointer forms without new evidence that distinguishes another source idiom or translation-unit effect.

## Evidence paths

- `evidence/recovery/workflow/jobs/ChangeDirectory-b005f31f9a/packet.md` and `factory-packet.json`
- `evidence/topology/build-topology.json` (`antedit:90DC` and surrounding unit)
- `layout/compiler-profiles.json` (baseline assignment)
- `evidence/recovery/workflow/jobs/ChangeDirectory-b005f31f9a/attempt08/candidate0000.diff.txt` and `results.json`

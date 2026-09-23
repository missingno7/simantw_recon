# _Feedback isolated production experiments

Job: `Feedback-c97a1d616e`; component `simtwo:78CA`; profile baseline (`/AL /G2 /Gs /Oelw /NTSIMTWO_MODULE`). Six strict tests were run through `grind.py test`; no source was promoted. The job was blocked with `TRANSLATION_UNIT_CONTEXT_REQUIRED` after preserving all drafts and receipts.

## Distinct compiler outcomes

| Attempts | Object SHA-256 prefix | Body size | Opcode matches | Other response | Readout |
|---|---|---:|---:|---|---|
| 01, 02 | `7e05d71e09f6881f` / `fbabe26f55729e51` | 500 | 79/163 | 36 memory, 17 branch differences; 0/62 fixups | Far arrays vs `__based` declarations changed OMF records/object hash but collapsed to the same function bytes and diagnostics. Array-plus-constant far-pointer expressions kept segment+offset fixups where target has selector loads plus literal ES displacements. |
| 03 | `3055c04a0d51b3ee` | 496 | 76/160 | 37 memory, 16 branch differences; 0/62 fixups | Based-pointer lvalue spelling changed code shape slightly (including removal of one unconditional jump) but introduced no exact fixup match and lowered the diagnostic. |
| 04, 05 | `68b071875b3cbdfc` | 422 | 80/150 | 33 memory, 15 branch differences; 0/54 fixups | Corrected tutorial flow and forced two volatile far-pointer locals; attempt05's `AdviceStrs`/`EditMessage` prototype rewrite produced a byte-identical object, so the prototype-only change had no codegen effect in this body. |
| 06 | `764b9f908ff1b979` | 422 | 80/150 | 31 memory, 15 branch differences; 0/54 fixups | Corrected health/message branch and advice table index use; improved two memory comparisons, but still far from exact. |

All results remain under `attempt01`–`attempt06/results.json`, with candidate sources at the same attempt paths. Best readable source: `attempt06.c`.

## Blocker and next discriminating test

The packet groups `_Feedback`, `_RunTutor`, `_GiveLesson`, and `_LessonDone` in `simtwo:78CA`. Isolated tests continue to report conflicting private `CONST` placement and unresolved/mismatched offset fixups, even after the far-array/based spelling probes. The next test is a unit assembly using preserved exact bodies where available, then verify AdviceStrs/EditMessage declarations and selector-pool order in that unit context. Do not spend another batch on far-array declaration spellings: those tested forms either collapsed or left the same fixup family.

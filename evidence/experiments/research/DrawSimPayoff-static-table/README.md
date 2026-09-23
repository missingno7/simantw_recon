# Isolated `_DrawSimPayoff` static-table research

This research does not reopen or modify the capped production job at `evidence/recovery/workflow/jobs/DrawSimPayoff-5ee404e211`.

## Evidence and experiments

Authentic DGROUP segment 10 at `0x15D8..0x15EF` contains 24 initialized bytes encoding six word pairs: `(74,72),(66,87),(64,175),(66,191),(122,159),(124,179)`. The function sets `SI=0x15DA`, reads `[SI]` and `[SI-2]`, adds four, and loops while `SI < 0x15F2`.

`run01` uses a natural file-scope `static int payoffOffsets[6][2]` with those initializers and a six-element indexed loop. Its emitted `_DATA` is exactly 24 bytes:

`4a 00 48 00 42 00 57 00 40 00 af 00 42 00 bf 00 7a 00 9f 00 7c 00 b3 00`

This confirms the table content and type hypothesis. Strict member comparison is `NO_COMPLETE_MATCH`: the function extent is 402 bytes versus the target's 401; code shape/register allocation differ, with song in SI rather than target DI; the candidate `_DATA` contribution is unplaced and matcher reports `conflicting private placement constraints _DATA` / `unplaced contribution _DATA`.

`run02` uses the same table with a cursor starting at `&payoffOffsets[0][1]`, reading current and previous near words and stepping by four. It preserves the exact same table bytes but emits a 430-byte, CFG-uncertain member; it is less close to target. It independently reports the same private `_DATA` placement conflict.

## Preserved artifacts

- `candidate.c`, `cursor.c`: sources
- `spec.json`, `cursor-spec.json`: isolated grinder specs
- `run01/` and `run02/`: strict reports, diffs, receipts, and copied raw OMF objects

Object SHA-256: run01 `84b70a9a3f0748a84ddc225d821824468bf751b41bdcdfc2f4338c46f68cbce6`; run02 `3a6e3237a9e875d50aed37ee8324ebd9fec55e9b3c704428d07081e1a6b3e911`.

## Conclusion / next discriminator

The values and 16-bit near table shape are positively supported. Neither isolated source form proves that `_DrawSimPayoff` owns this static contribution in its original translation unit: candidate data is exact but cannot be placed at the observed DGROUP offset in isolation. Body source shape is also unresolved, especially cursor/register allocation and loop lowering.

The next defensible discriminator is an evidence-backed TU assembly or topology retest that puts the table contribution alongside the original neighboring DGROUP contributions and the target member, so its placement can be checked while compiling the function in the same unit. Do not treat table bytes alone as source recovery or promotion evidence.

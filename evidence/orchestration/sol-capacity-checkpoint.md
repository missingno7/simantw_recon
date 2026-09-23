# Sol capacity and recovery checkpoint

Observed 2026-09-23 23:20 UTC on `codex/simantw-recovery`.

- Active Codex configuration: `max_concurrent_threads_per_session = 16`; this session reports 17 total agent slots including root. The Luna/high foreman expanded to 11 simultaneously active Luna/high workers on disjoint assignments. The MSC7 compiler service remains capped at four workers.
- Latest completed doctor snapshot: `READY_FOR_BOUNDED_HANDOFF`, 518 strictly verified game functions, 77 runtime members, 78 `MATCH_READY`, 467 `MATCH_BLOCKED`, 2 `STRUCTURE_BLOCKED`, and no problems. `handoff_validate.py` passed 216 tests and the bounded cache replay.
- Foreman batch snapshot: 19 distinct production targets assigned/investigated plus four isolated research batches; 66 compiled candidates, 61 unique effective OMFs, zero strict promotions and zero newly recovered bytes. These are historical batch counters, not a claim about later worker activity. Routine assignments and statuses are in `luna-ownership.json` and the native job ledger.
- The first 50 Save/Load records reported in `../experiments/savegame-table/` are an observed prefix. Follow-up `../experiments/save-table-structure/` found 307 eight-byte records at segment 8 offsets `0x9570..0x9f07`, 307 named pointer relocations, and a zero record at `0x9f08`. An isolated MSC7 profile probe produced the natural 2544-byte buffer/table/sentinel contribution and all 307 named fixups; mutability and initializer spelling collapsed to one object. This is research evidence, not historical source admission. `_SaveGame` and `_LoadGame` remain reserved from routine production reissue pending semantic consumer and strict unit evidence.
- No proof rule, accepted source, protected manifest, production budget, or compiler profile was weakened. The user-requested push includes `57c751ee`, which corrects the original 50-record boundary claim.

The long-term goal remains active. Resume by reading live generated queue/readiness and native job records first; this checkpoint can become stale as workers continue.

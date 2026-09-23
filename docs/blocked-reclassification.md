# Fresh classification of the MATCH_BLOCKED population

Generated 2026-09-23T18:27:39.429252+00:00 from the current HEAD: every blocked function's best preserved candidate recompiled under the current object profile and compared strictly. Historical labels are shown only as `previous`.

## Counts by fresh root cause

- TRUE_SOURCE_SHAPE_MISMATCH: 399
- ABI_TYPE_INFERENCE: 20
- UNKNOWN: 13
- BODY_EXACT_LAYOUT_BLOCKED: 4
- PROFILE_CONTEXT_RETEST: 1
- MIRRORED_SOURCE_PAIR: 1

Historical labels that no longer describe the fresh result: 75

## By historical object / TU context

### simant:4C24 — 5 members, 2 matched, 2 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 2; mirrored blocked members: 0
- selector pool: 7/8 words introduced by admitted or exact members; private data words 1 (reproduced)
- likely next missing introducer: _ProcMenu
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 2
- fresh causes: BODY_EXACT_LAYOUT_BLOCKED 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _PauseGame | 369 | BODY_EXACT_LAYOUT_BLOCKED | exact body; only unresolved offset bindings (pool / private data / TU context) | DATA_LAYOUT |  |
| _SetPause | 369 | BODY_EXACT_LAYOUT_BLOCKED | exact body; only unresolved offset bindings (pool / private data / TU context) | DATA_LAYOUT |  |

### simant1:5344 — 28 members, 11 matched, 17 blocked, 0 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 17
- selector pool: 6/21 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoNestAntR
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 1
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 16, PROFILE_CONTEXT_RETEST 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _MakeNewTailR | 101 | PROFILE_CONTEXT_RETEST | parked under /AL /G2 /Gs /Oelw /NTSIMANT1_MODULE, context profile is now og (/AL /G2 /Gs /Oeglw /NTSIMANT1_MOD | PRIVATE_CONST_LAYOUT | _MakeNewTailB (MATCH_BLOCKED) |
| _DoDigInR | 798 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (225/285 opcodes | REGISTER_ALLOCATION | _DoDigInB (MATCH_BLOCKED) |
| _DoDigOutR | 656 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (173/247 opcodes | REGISTER_ALLOCATION | _DoDigOutB (MATCH_BLOCKED) |
| _DoDrownR | 210 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (63/71 opcodes, 202/210 bytes) | REGISTER_ALLOCATION | _DoDrownB (MATCH_BLOCKED) |
| _DoFoodInR | 640 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (180/229 opcodes | REGISTER_ALLOCATION | _DoFoodInB (MATCH_BLOCKED) |
| _DoNestAntR | 1925 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (374/684 opcodes | REGISTER_ALLOCATION | _DoNestAntB (MATCH_BLOCKED) |
| _DoNestFightR | 304 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (88/108 opcodes, 290/304 bytes) | REGISTER_ALLOCATION | _DoNestFightB (MATCH_BLOCKED) |
| _DoNestingR | 557 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (157/183 opcodes | REGISTER_ALLOCATION | _DoNestingB (MATCH_BLOCKED) |
| _DropFoodR | 100 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (27/37 opcodes,  | REGISTER_ALLOCATION | _DropFoodB (MATCH_BLOCKED) |
| _GetOutR | 314 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (100/117 opcodes, 307/314 byte | REGISTER_ALLOCATION | _GetOutB (MATCH_BLOCKED) |
| _KillTailR | 45 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (15/17 opcodes, 44/45 bytes) | REGISTER_ALLOCATION | _KillTailB (MATCH_BLOCKED) |
| _LostHeadR | 94 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (36/41 opcodes, 94/94 bytes) | REGISTER_ALLOCATION | _LostHeadB (MATCH_BLOCKED) |
| _LostTailR | 98 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (38/43 opcodes, 100/98 bytes) | REGISTER_ALLOCATION | _LostTailB (MATCH_BLOCKED) |
| _QueenMoveR | 246 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (81/95 opcodes,  | EXPRESSION_SHAPE | _QueenMoveB (MATCH_BLOCKED) |
| _SimQueenR | 639 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (195/223 opcodes | EXPRESSION_SHAPE | _SimQueenB (MATCH_BLOCKED) |
| _StealFoodR | 67 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (19/26 opcodes, 54/67 bytes) | REGISTER_ALLOCATION | _StealFoodB (MATCH_BLOCKED) |
| _TryMoveDirR | 186 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (62/73 opcodes, 195/186 bytes) | SEMANTICS_UNKNOWN | _TryMoveDirB (MATCH_BLOCKED) |

### simtwo:C806 — 24 members, 9 matched, 13 blocked, 2 ready; profile ga

- exact bodies awaiting admission: 1; mirrored blocked members: 0
- selector pool: 0/8 words introduced by admitted or exact members; private data words 1 (reproduced)
- likely next missing introducer: _win_LoadAllWindows
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 1
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 12, BODY_EXACT_LAYOUT_BLOCKED 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetObjBitmap | 123 | BODY_EXACT_LAYOUT_BLOCKED | exact body; only unresolved offset bindings (pool / private data / TU context) | DATA_LAYOUT |  |
| __win_SetProxItem | 197 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (74/75 opcodes, 197/197 bytes) | SEMANTICS_UNKNOWN |  |
| _win_ClearObjToEOL | 290 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (96/117 opcodes, | REGISTER_ALLOCATION |  |
| _win_Close | 168 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (61/66 opcodes, 166/168 bytes) | SEMANTICS_UNKNOWN |  |
| _win_DrawHBar | 192 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (80/81 opcodes, 192/192 bytes) | SOURCE_COMPILATION_ERROR |  |
| _win_DrawVBar | 194 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (81/82 opcodes, 194/194 bytes) | EXPRESSION_SHAPE |  |
| _win_Events | 112 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (46/47 opcodes, 112/112 bytes) | EXPRESSION_SHAPE |  |
| _win_FindObject | 101 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (43/46 opcodes, 103/101 bytes) | REGISTER_ALLOCATION |  |
| _win_GetEvent | 420 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (146/180 opcodes | REGISTER_ALLOCATION |  |
| _win_LoadAllWindows | 552 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (141/228 opcodes | EXPRESSION_SHAPE |  |
| _win_ObjFormatPrint | 552 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (124/226 opcodes | REGISTER_ALLOCATION |  |
| _win_SetObjFormatStr | 297 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (65/115 opcodes, | SEMANTICS_UNKNOWN |  |
| _win_Swap | 359 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (105/148 opcodes | REGISTER_ALLOCATION |  |

### simtwo:0000 — 21 members, 12 matched, 9 blocked, 0 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 1
- selector pool: 12/28 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _GetStrategy
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 1
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 8, MIRRORED_SOURCE_PAIR 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GstrR | 332 | MIRRORED_SOURCE_PAIR | counterpart matched is MATCHED; derive mechanically | REGISTER_ALLOCATION | _GstrB (MATCHED) |
| _ForceModeA | 210 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (61/74 opcodes, 197/210 bytes) | REGISTER_ALLOCATION |  |
| _ForceModeB | 176 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (54/65 opcodes, 158/176 bytes) | REGISTER_ALLOCATION |  |
| _GetAlarmDir | 286 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (111/121 opcodes | SEMANTICS_UNKNOWN |  |
| _GetForageDir | 384 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (156/161 opcodes, 386/384 bytes) | SEMANTICS_UNKNOWN |  |
| _GetNestDir | 547 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (155/211 opcodes | SEMANTICS_UNKNOWN |  |
| _GetNewMode | 192 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (55/68 opcodes, 192/192 bytes) | EXPRESSION_SHAPE |  |
| _GetStrategy | 460 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (141/151 opcodes, 454/460 bytes) | SEMANTICS_UNKNOWN |  |
| _SetCasteProd | 183 | TRUE_SOURCE_SHAPE_MISMATCH | frame layout under the current profile (74/74 opcodes, 183/183 bytes) | LOCAL_FRAME_LAYOUT |  |

### simant:8A76 — 6 members, 0 matched, 5 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/32 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _ProcHistoryEvent
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 1
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 4, BODY_EXACT_LAYOUT_BLOCKED 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ClearHistory | 299 | BODY_EXACT_LAYOUT_BLOCKED | exact body; private placement / contribution issues only | EXPRESSION_SHAPE |  |
| _HistUpdate | 317 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (84/93 opcodes, 322/317 bytes) | EXPRESSION_SHAPE |  |
| _ProcHistoryEvent | 245 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (67/96 opcodes, 248/245 bytes) | EXPRESSION_SHAPE |  |
| _ToggleHistButton | 400 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (93/138 opcodes, 341/400 bytes | SEMANTICS_UNKNOWN |  |
| _win_DrawHistoryWindow | 80 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (24/34 opcodes, 74/80 bytes) | PRIVATE_CONST_LAYOUT |  |

### simant1:2D4E — 30 members, 12 matched, 18 blocked, 0 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 17
- selector pool: 8/26 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoNestAntB
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 18

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DoDigInB | 735 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (218/252 opcodes | REGISTER_ALLOCATION | _DoDigInR (MATCH_BLOCKED) |
| _DoDigOutB | 686 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (201/240 opcodes | REGISTER_ALLOCATION | _DoDigOutR (MATCH_BLOCKED) |
| _DoDrownB | 210 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (68/72 opcodes, 210/210 bytes) | SEMANTICS_UNKNOWN | _DoDrownR (MATCH_BLOCKED) |
| _DoFoodInB | 678 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (209/238 opcodes | REGISTER_ALLOCATION | _DoFoodInR (MATCH_BLOCKED) |
| _DoNestAntB | 1909 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (264/686 opcodes | REGISTER_ALLOCATION | _DoNestAntR (MATCH_BLOCKED) |
| _DoNestFightB | 334 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (107/122 opcodes | REGISTER_ALLOCATION | _DoNestFightR (MATCH_BLOCKED) |
| _DoNestingB | 797 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (189/257 opcodes | LOCAL_FRAME_LAYOUT | _DoNestingR (MATCH_BLOCKED) |
| _DropFoodB | 100 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (27/37 opcodes,  | REGISTER_ALLOCATION | _DropFoodR (MATCH_BLOCKED) |
| _GetBestDir | 246 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (88/95 opcodes, 245/246 bytes) | EXPRESSION_SHAPE |  |
| _GetOutB | 314 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (100/117 opcodes, 307/314 byte | REGISTER_ALLOCATION | _GetOutR (MATCH_BLOCKED) |
| _KillTailB | 45 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (15/17 opcodes, 44/45 bytes) | REGISTER_ALLOCATION | _KillTailR (MATCH_BLOCKED) |
| _LostHeadB | 94 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (38/43 opcodes,  | REGISTER_ALLOCATION | _LostHeadR (MATCH_BLOCKED) |
| _LostTailB | 98 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (38/43 opcodes, 100/98 bytes) | REGISTER_ALLOCATION | _LostTailR (MATCH_BLOCKED) |
| _MakeNewTailB | 101 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (29/40 opcodes, 91/101 bytes) | EXPRESSION_SHAPE | _MakeNewTailR (MATCH_BLOCKED) |
| _QueenMoveB | 246 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (80/95 opcodes, 252/246 bytes) | SEMANTICS_UNKNOWN | _QueenMoveR (MATCH_BLOCKED) |
| _SimQueenB | 666 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (200/231 opcodes | EXPRESSION_SHAPE | _SimQueenR (MATCH_BLOCKED) |
| _StealFoodB | 67 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (19/26 opcodes, 60/67 bytes) | SEMANTICS_UNKNOWN | _StealFoodR (MATCH_BLOCKED) |
| _TryMoveDirB | 266 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (78/95 opcodes, 261/266 bytes) | EXPRESSION_SHAPE | _TryMoveDirR (MATCH_BLOCKED) |

### simant1:0000 — 31 members, 16 matched, 15 blocked, 0 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 13/40 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoAntSim
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 15

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DeadAntHere | 353 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (113/121 opcodes | SEMANTICS_UNKNOWN |  |
| _DoAntSim | 762 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (39/232 opcodes, 161/762 bytes | SEMANTICS_UNKNOWN |  |
| _DoAntSimA | 1348 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (258/447 opcodes | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |
| _DoAttackAnt | 640 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (200/230 opcodes | SEMANTICS_UNKNOWN |  |
| _DoDigOutAntA | 502 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (118/167 opcodes | SEMANTICS_UNKNOWN |  |
| _DoForageAnt | 1126 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (289/401 opcodes | SEMANTICS_UNKNOWN |  |
| _DoRandAntA | 974 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (278/344 opcodes | SEMANTICS_UNKNOWN |  |
| _DoRandAntAA | 588 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (195/215 opcodes | SEMANTICS_UNKNOWN |  |
| _DoRecruitAnt | 722 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (229/268 opcodes | SEMANTICS_UNKNOWN |  |
| _DoRepoExit | 208 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (64/72 opcodes, 220/208 bytes) | EXPRESSION_SHAPE |  |
| _DoRestAnt | 168 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (60/66 opcodes, 166/168 bytes) | EXPRESSION_SHAPE |  |
| _DoReturnFoodAnt | 398 | TRUE_SOURCE_SHAPE_MISMATCH | frame layout under the current profile (142/142 opcodes, 398/398 bytes) | SEMANTICS_UNKNOWN |  |
| _DoToAlarm | 682 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (227/248 opcodes | SEMANTICS_UNKNOWN |  |
| _DoToNestAnt | 915 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (258/325 opcodes | LOCAL_FRAME_LAYOUT |  |
| _SimQueenA | 169 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (51/66 opcodes,  | REGISTER_ALLOCATION |  |

### simone:5AD2 — 48 members, 25 matched, 15 blocked, 8 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 11/35 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoLifeExchange
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 15

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ClearLife | 258 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (62/103 opcodes, | REGISTER_ALLOCATION |  |
| _ClearMyLife | 465 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (151/190 opcodes | EXPRESSION_SHAPE |  |
| _EatMyFood | 443 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (121/156 opcodes, 428/443 byte | SEMANTICS_UNKNOWN |  |
| _FindEggAt | 499 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (37/199 opcodes, 98/499 bytes) | SEMANTICS_UNKNOWN |  |
| _FindLifeAt | 473 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (37/189 opcodes, 98/473 bytes) | SEMANTICS_UNKNOWN |  |
| _IsClearTile | 332 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (131/153 opcodes | SEMANTICS_UNKNOWN |  |
| _IsItDigable | 240 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (68/113 opcodes, 208/240 bytes | EXPRESSION_SHAPE |  |
| _IsItFoodAt | 193 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (78/88 opcodes, 200/193 bytes) | SEMANTICS_UNKNOWN |  |
| _IsItYellow | 206 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (65/90 opcodes, 188/206 bytes) | EXPRESSION_SHAPE |  |
| _IsNotObstacle | 255 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (77/108 opcodes, | REGISTER_ALLOCATION |  |
| _IsSamePlane | 32 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (12/18 opcodes, 34/32 bytes) | REGISTER_ALLOCATION |  |
| _IsThisPebble | 49 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (22/24 opcodes, 50/49 bytes) | REGISTER_ALLOCATION |  |
| _SetLife | 432 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (110/180 opcodes | EXPRESSION_SHAPE |  |
| _SetMyLife | 196 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (76/79 opcodes, 196/196 bytes) | EXPRESSION_SHAPE |  |
| _TileCanBeMovedOn | 349 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (119/143 opcodes | REGISTER_ALLOCATION |  |

### simant:B324 — 20 members, 6 matched, 14 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 10/24 words introduced by admitted or exact members; private data words 2 (reproduced)
- likely next missing introducer: _win_CasteControlChanged
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 14

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DrawControlLevels | 538 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (173/216 opcodes | SEMANTICS_UNKNOWN |  |
| _GetTriLatDist | 299 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (69/116 opcodes, | REGISTER_ALLOCATION |  |
| _IsPointInIsoTri | 188 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (84/89 opcodes, 190/188 bytes) | EXPRESSION_SHAPE |  |
| _ProcCasteEvent | 881 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (294/346 opcodes | REGISTER_ALLOCATION |  |
| _ProcModeEvent | 769 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (257/310 opcodes | SEMANTICS_UNKNOWN |  |
| _SetTriLatPoint | 221 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (67/84 opcodes,  | SEMANTICS_UNKNOWN |  |
| _UpdateCasteWindow | 547 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (116/188 opcodes | SEMANTICS_UNKNOWN |  |
| _UpdateModeWindow | 547 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (116/188 opcodes | SEMANTICS_UNKNOWN |  |
| _win_CasteControlChanged | 500 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (143/176 opcodes | REGISTER_ALLOCATION |  |
| _win_CasteControlClosed | 149 | TRUE_SOURCE_SHAPE_MISMATCH | operand/immediate differences under the current profile (53/53 opcodes, 151/149 bytes) | EXPRESSION_SHAPE |  |
| _win_DrawCasteWindow | 216 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (77/79 opcodes, 216/216 bytes) | EXPRESSION_SHAPE |  |
| _win_DrawModeWindow | 216 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (77/79 opcodes, 216/216 bytes) | EXPRESSION_SHAPE |  |
| _win_ModeControlChanged | 500 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (140/176 opcodes | REGISTER_ALLOCATION |  |
| _win_ModeControlClosed | 149 | TRUE_SOURCE_SHAPE_MISMATCH | operand/immediate differences under the current profile (53/53 opcodes, 151/149 bytes) | EXPRESSION_SHAPE |  |

### antedit:00F4 — 40 members, 19 matched, 12 blocked, 9 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 11/131 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _LoadTiles
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 11, ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SetEditWinTitle | 232 | ABI_TYPE_INFERENCE | call/pointer-shape differences (STRING_INTRINSIC_IDIOM) | STRING_INTRINSIC_IDIOM |  |
| _AddMsgBalloon | 276 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (92/114 opcodes, | SEMANTICS_UNKNOWN |  |
| _BoundEditPosition | 107 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (35/38 opcodes, 109/107 bytes) | EXPRESSION_SHAPE |  |
| _CenterEdit | 180 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (66/67 opcodes, 180/180 bytes) | SEMANTICS_UNKNOWN |  |
| _ClearEditDeltaTables | 247 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (69/89 opcodes,  | LOCAL_FRAME_LAYOUT |  |
| _DoEditScroll | 1047 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (312/353 opcodes, 1027/1047 bytes) | REGISTER_ALLOCATION |  |
| _DoEditScrollLine | 322 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (99/109 opcodes, 324/322 bytes) | REGISTER_ALLOCATION |  |
| _DrawEditGraphs | 379 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (74/138 opcodes, 256/379 bytes) | SEMANTICS_UNKNOWN |  |
| _ScrollEditWindow | 165 | TRUE_SOURCE_SHAPE_MISMATCH | exact body but wrong displacement/index for _editHeight, _editWidth, _tileHeight, _tileWidth (binding semantic | EXPRESSION_SHAPE |  |
| _UpdateEditIfBufInvalid | 82 | TRUE_SOURCE_SHAPE_MISMATCH | exact body but wrong displacement/index for _DrawEdit (binding semantics) | CALLING_CONVENTION |  |
| _win_DrawEditWindow | 195 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (57/69 opcodes,  | REGISTER_ALLOCATION |  |
| _win_EditChanged | 458 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (136/157 opcodes | LOCAL_FRAME_LAYOUT |  |

### simone:3120 — 19 members, 5 matched, 12 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/3 words introduced by admitted or exact members; private data words 5 (reproduced)
- likely next missing introducer: _MakeHousePatch
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 11, UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _CarpetFloorL | 181 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (45/74 opcodes, 187/181 bytes) | OPTIMIZER_VARIANT_REQUIRED |  |
| _FillMap | 85 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (33/44 opcodes,  | SEMANTICS_UNKNOWN |  |
| _FloorTiles | 188 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (62/84 opcodes, 201/188 bytes) | EXPRESSION_SHAPE |  |
| _MakeKitchenWall | 196 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (51/81 opcodes, 172/196 bytes) | OPTIMIZER_VARIANT_REQUIRED |  |
| _MakeLint2 | 105 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (40/48 opcodes,  | REGISTER_ALLOCATION |  |
| _MakeOutletH | 257 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (92/101 opcodes, | REGISTER_ALLOCATION |  |
| _MakeOutletV | 257 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (92/101 opcodes, | REGISTER_ALLOCATION |  |
| _MakeSink | 487 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (184/197 opcodes, 450/487 bytes) | REGISTER_ALLOCATION |  |
| _MakeYardPatch | 401 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (98/160 opcodes, | REGISTER_ALLOCATION |  |
| _TileFrame1 | 350 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (93/140 opcodes, | REGISTER_ALLOCATION |  |
| _TileFrame2 | 350 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (93/140 opcodes, | REGISTER_ALLOCATION |  |
| _CarpetFloorR | 182 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | OPTIMIZER_VARIANT_REQUIRED |  |

### simant1:75F4 — 15 members, 3 matched, 11 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 3/37 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoAntMoveY
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 10, ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GetMyNextRandDirs | 244 | ABI_TYPE_INFERENCE | call/pointer-shape differences (CALLING_CONVENTION) | CALLING_CONVENTION |  |
| _AnimYellowFight | 545 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (173/188 opcodes, 553/545 bytes) | REGISTER_ALLOCATION |  |
| _AnimYellowInsane | 454 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (143/161 opcodes | REGISTER_ALLOCATION |  |
| _ExitNest | 477 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (145/155 opcodes, 465/477 bytes) | EXPRESSION_SHAPE |  |
| _GetMyBestDir | 399 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (116/154 opcodes, 379/399 bytes) | REGISTER_ALLOCATION |  |
| _GetMyBestDirs | 256 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (76/98 opcodes,  | REGISTER_ALLOCATION |  |
| _GetMyDir | 788 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (66/296 opcodes, | EXPRESSION_SHAPE |  |
| _GetMyDis | 421 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (70/125 opcodes, | REGISTER_ALLOCATION |  |
| _GetMyInitialRandDir | 91 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (34/36 opcodes, 89/91 bytes) | TRANSLATION_UNIT_CONTEXT |  |
| _GetMyRandDirs | 536 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (143/192 opcodes | REGISTER_ALLOCATION |  |
| _YellowFight | 457 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (132/161 opcodes | EXPRESSION_SHAPE |  |

### simone:16AE — 11 members, 1 matched, 10 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 6
- selector pool: 0/19 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DigMyNewHole
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 10

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _CreateNewHole | 506 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (154/182 opcodes | REGISTER_ALLOCATION |  |
| _DigMyNewHole | 107 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (17/45 opcodes, 100/107 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |
| _DigMyTile | 498 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (160/195 opcodes, 488/498 bytes) | REGISTER_ALLOCATION |  |
| _DigTileB | 505 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (143/196 opcodes, 504/505 bytes) | REGISTER_ALLOCATION | _DigTileR (MATCH_BLOCKED) |
| _DigTileR | 245 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (68/98 opcodes,  | EXPRESSION_SHAPE | _DigTileB (MATCH_BLOCKED) |
| _DigTileThemB | 328 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (119/135 opcodes, 326/328 bytes) | REGISTER_ALLOCATION | _DigTileThemR (MATCH_BLOCKED) |
| _DigTileThemR | 318 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (117/133 opcodes, 315/318 byte | REGISTER_ALLOCATION | _DigTileThemB (MATCH_BLOCKED) |
| _HoleBorder | 86 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (34/37 opcodes, 87/86 bytes) | PRIVATE_CONST_LAYOUT |  |
| _MakeNewHoleB | 436 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (143/176 opcodes | REGISTER_ALLOCATION | _MakeNewHoleR (MATCH_BLOCKED) |
| _MakeNewHoleR | 650 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (207/254 opcodes | REGISTER_ALLOCATION | _MakeNewHoleB (MATCH_BLOCKED) |

### antedit:C19C — 15 members, 4 matched, 9 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 7/25 words introduced by admitted or exact members; private data words 1 (reproduced)
- likely next missing introducer: _DrawMapCursor
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 9

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DrawMap | 264 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (88/91 opcodes, 264/264 bytes) | SEMANTICS_UNKNOWN |  |
| _DrawMapCursor | 185 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (50/59 opcodes, 197/185 bytes) | OPTIMIZER_VARIANT_REQUIRED |  |
| _DrawMapFoot | 484 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (141/174 opcodes | REGISTER_ALLOCATION |  |
| _DrawMapSpider | 280 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (82/113 opcodes, | REGISTER_ALLOCATION |  |
| _EraseMapCursor | 66 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (16/25 opcodes, 72/66 bytes) | DATA_LAYOUT |  |
| _MapToYellowAnt | 105 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (40/46 opcodes, 110/105 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |
| _Mini_DrawMapI | 811 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (226/284 opcodes | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |
| _ProcMapEvent | 434 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (152/169 opcodes, 434/434 bytes) | REGISTER_ALLOCATION |  |
| _ToggleMapCursor | 261 | TRUE_SOURCE_SHAPE_MISMATCH | exact body but wrong displacement/index for _just, _mapTileRect (binding semantics) | PRIVATE_CONST_LAYOUT |  |

### gr:7712 — 28 members, 14 matched, 9 blocked, 5 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 1/3 words introduced by admitted or exact members; private data words 1 (reproduced)
- likely next missing introducer: _myBeginSong
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 8, UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ExtractVariableLen | 222 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (64/86 opcodes,  | REGISTER_ALLOCATION |  |
| _IsDLLAvail | 300 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (107/127 opcodes | EXPRESSION_SHAPE |  |
| _MciMessage | 295 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (60/95 opcodes,  | EXPRESSION_SHAPE |  |
| _StopSong | 272 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (81/95 opcodes, 274/272 bytes) | REGISTER_ALLOCATION |  |
| _musSoundBlasterClose | 100 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (25/27 opcodes, 97/100 bytes) | PRIVATE_CONST_LAYOUT |  |
| _myServiceSong | 78 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (26/29 opcodes, 80/78 bytes) | PRIVATE_CONST_LAYOUT |  |
| _mySongIsDone | 66 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (14/21 opcodes, 60/66 bytes) | DATA_LAYOUT |  |
| _vocSoundBlasterClose | 100 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (25/27 opcodes, 97/100 bytes) | PRIVATE_CONST_LAYOUT |  |
| _SoundBlasterMessage | 296 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | SEMANTICS_UNKNOWN |  |

### simant:01B6 — 29 members, 13 matched, 9 blocked, 6 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 8/36 words introduced by admitted or exact members; private data words 2 (reproduced)
- likely next missing introducer: _DoUserButton
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 8, ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| MYENUMFUNC | 48 | ABI_TYPE_INFERENCE | call/pointer-shape differences (CALLING_CONVENTION) | CALLING_CONVENTION |  |
| _AdjustWndMinMax | 457 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (126/204 opcodes | EXPRESSION_SHAPE |  |
| _DoBookMark | 513 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (137/183 opcodes, 497/513 bytes) | EXPRESSION_SHAPE |  |
| _DoMenuEntry | 503 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (137/183 opcodes, 436/503 bytes) | EXPRESSION_SHAPE |  |
| _DoMouse | 1077 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (187/394 opcodes | SEMANTICS_UNKNOWN |  |
| _DoUserButton | 994 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (291/377 opcodes | LOCAL_FRAME_LAYOUT |  |
| _InitApplication | 315 | TRUE_SOURCE_SHAPE_MISMATCH | frame layout under the current profile (90/90 opcodes, 315/315 bytes) | LOCAL_FRAME_LAYOUT |  |
| _NetworkSend | 451 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (138/183 opcodes, 431/451 bytes) | EXPRESSION_SHAPE |  |
| _UpdateWindows | 540 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (122/173 opcodes | SEMANTICS_UNKNOWN |  |

### simone:04DE — 15 members, 4 matched, 9 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 4
- selector pool: 0/17 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _CountAnts
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 7, ABI_TYPE_INFERENCE 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _PlaceEggB | 100 | ABI_TYPE_INFERENCE | call/pointer-shape differences (CALLING_CONVENTION) | CALLING_CONVENTION | _PlaceEggR (MATCH_BLOCKED) |
| _PlaceEggR | 100 | ABI_TYPE_INFERENCE | call/pointer-shape differences (CALLING_CONVENTION) | CALLING_CONVENTION | _PlaceEggB (MATCH_BLOCKED) |
| _DropFoodA | 292 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (48/112 opcodes, | SEMANTICS_UNKNOWN |  |
| _DropWater | 195 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (78/84 opcodes,  | REGISTER_ALLOCATION |  |
| _FoodFall | 150 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (55/57 opcodes, 154/150 bytes) | SEMANTICS_UNKNOWN |  |
| _PickupFoodA | 109 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (23/44 opcodes,  | PRIVATE_CONST_LAYOUT |  |
| _PickupFoodB | 98 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (27/41 opcodes, 78/98 bytes) | PRIVATE_CONST_LAYOUT | _PickupFoodR (MATCH_BLOCKED) |
| _PickupFoodR | 98 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (27/41 opcodes, 78/98 bytes) | PRIVATE_CONST_LAYOUT | _PickupFoodB (MATCH_BLOCKED) |
| _PlaceDrop | 170 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (52/58 opcodes, 168/170 bytes) | DATA_LAYOUT |  |

### antedit:A998 — 22 members, 13 matched, 7 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 7/33 words introduced by admitted or exact members; private data words 3 (reproduced)
- likely next missing introducer: _win_DrawYardWindow
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 6, UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DrawColonyBars | 253 | TRUE_SOURCE_SHAPE_MISMATCH | frame layout under the current profile (88/88 opcodes, 253/253 bytes) | SEMANTICS_UNKNOWN |  |
| _DrawMower | 229 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (55/90 opcodes, 256/229 bytes) | EXPRESSION_SHAPE |  |
| _DrawSimColonies | 247 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (62/86 opcodes,  | SEMANTICS_UNKNOWN |  |
| _DrawSimKid | 507 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (144/166 opcodes | LOCAL_FRAME_LAYOUT |  |
| _InvertPatch | 159 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (45/64 opcodes,  | REGISTER_ALLOCATION |  |
| _win_DrawYardWindow | 558 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (153/195 opcodes, 586/558 bytes) | EXPRESSION_SHAPE |  |
| _DrawSimCat | 132 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | DATA_LAYOUT |  |

### simant:9D04 — 18 members, 9 matched, 7 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 11/33 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _KillSomeAnts
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 7

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GotoBQueen | 205 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (67/69 opcodes, 205/205 bytes) | REGISTER_ALLOCATION |  |
| _GotoMyAnt | 224 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (69/73 opcodes, 221/224 bytes) | REGISTER_ALLOCATION |  |
| _KillSomeAnts | 198 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (58/71 opcodes, 187/198 bytes) | REGISTER_ALLOCATION |  |
| _MysteryButton | 616 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (186/240 opcodes, 602/616 byte | REGISTER_ALLOCATION |  |
| _SetMapPlaneLocation | 419 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (122/133 opcodes | REGISTER_ALLOCATION |  |
| _SubtractFood | 77 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (31/32 opcodes,  | LOCAL_FRAME_LAYOUT |  |
| _XferPatch | 385 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (124/137 opcodes, 385/385 byte | REGISTER_ALLOCATION |  |

### simone:2B42 — 14 members, 7 matched, 7 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 2/6 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _RemoveFromAList
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 7

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AddAntToAList | 89 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (30/33 opcodes, 86/89 bytes) | PRIVATE_CONST_LAYOUT |  |
| _BuildAntListA | 162 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (55/64 opcodes,  | EXPRESSION_SHAPE |  |
| _DrownBList | 79 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (27/35 opcodes, 79/79 bytes) | EXPRESSION_SHAPE |  |
| _DrownRList | 79 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (27/35 opcodes, 79/79 bytes) | EXPRESSION_SHAPE |  |
| _ExitHole | 313 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (92/116 opcodes, | SEMANTICS_UNKNOWN |  |
| _GetFromAlist | 72 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (26/38 opcodes, 69/72 bytes) | DATA_LAYOUT |  |
| _RemoveFromAList | 255 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (73/98 opcodes, 246/255 bytes) | REGISTER_ALLOCATION |  |

### simtwo:9A86 — 7 members, 0 matched, 7 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/2 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _OpenIndex
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 7

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AddIndex | 351 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (106/162 opcodes | REGISTER_ALLOCATION |  |
| _CloseIndex | 222 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (66/91 opcodes,  | REGISTER_ALLOCATION |  |
| _CreateIndex | 251 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (71/85 opcodes,  | REGISTER_ALLOCATION |  |
| _DeleteCurrentIndex | 259 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (81/109 opcodes, | EXPRESSION_SHAPE |  |
| _DeleteIndex | 245 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (72/106 opcodes, | REGISTER_ALLOCATION |  |
| _FindIndex | 237 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (62/88 opcodes, 224/237 bytes) | REGISTER_ALLOCATION |  |
| _OpenIndex | 194 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (64/75 opcodes,  | REGISTER_ALLOCATION |  |

### simant:6A38 — 15 members, 5 matched, 6 blocked, 4 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 14/55 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _processEdit
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 6

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _LionDialog | 449 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (132/156 opcodes, 453/449 bytes) | EXPRESSION_SHAPE |  |
| _SetGoalsY | 105 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (24/34 opcodes, 94/105 bytes) | PRIVATE_CONST_LAYOUT |  |
| _SpecialXfer | 490 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (135/175 opcodes | SEMANTICS_UNKNOWN |  |
| _YellowCommand | 625 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (195/227 opcodes, 606/625 bytes) | REGISTER_ALLOCATION |  |
| _YellowCommandKey | 600 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (180/231 opcodes, 536/600 bytes) | EXPRESSION_SHAPE |  |
| _YellowDialog | 523 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (134/175 opcodes | SEMANTICS_UNKNOWN |  |

### simtwo:1378 — 21 members, 12 matched, 6 blocked, 3 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 34/63 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _SimKidOutside
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 6

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _FootFall | 339 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (92/130 opcodes, | LOCAL_FRAME_LAYOUT |  |
| _GetMowDir | 225 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (90/92 opcodes,  | EXPRESSION_SHAPE |  |
| _MowerFall | 166 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (53/54 opcodes, 166/166 bytes) | EXPRESSION_SHAPE |  |
| _NotMowed | 52 | TRUE_SOURCE_SHAPE_MISMATCH | register allocation under the current profile (26/26 opcodes, 52/52 bytes) | REGISTER_ALLOCATION |  |
| _SimDog | 946 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (250/339 opcodes | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |
| _SimKidInside | 2036 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (385/645 opcodes | SEMANTICS_UNKNOWN |  |

### simtwo:3EF8 — 10 members, 3 matched, 6 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/19 words introduced by admitted or exact members; private data words 1 (reproduced)
- likely next missing introducer: _InitSow
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 6

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DoSow | 315 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (87/104 opcodes, | REGISTER_ALLOCATION |  |
| _FindInLionList | 69 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (25/34 opcodes, 61/69 bytes) | DATA_LAYOUT |  |
| _InitAntLions | 347 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (121/123 opcodes, 353/347 bytes) | LOCAL_FRAME_LAYOUT |  |
| _InitPillar | 228 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (76/82 opcodes,  | REGISTER_ALLOCATION |  |
| _InitSow | 146 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (45/48 opcodes,  | REGISTER_ALLOCATION |  |
| _KillAntLion | 160 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (52/59 opcodes, 170/160 bytes) | EXPRESSION_SHAPE |  |

### antedit:7022 — 23 members, 15 matched, 5 blocked, 3 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 1/19 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _processExp
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 5

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DropWall | 285 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (85/108 opcodes, | TRANSLATION_UNIT_CONTEXT |  |
| _ExpDig | 997 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (239/372 opcodes | TRANSLATION_UNIT_CONTEXT |  |
| _ExpIncSmell | 445 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (155/166 opcodes, 457/445 byte | TRANSLATION_UNIT_CONTEXT |  |
| _ExpKillAnts | 478 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (109/179 opcodes | TRANSLATION_UNIT_CONTEXT |  |
| _IncFoodHere | 287 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (86/102 opcodes, 273/287 bytes | TRANSLATION_UNIT_CONTEXT |  |

### gr:6410 — 10 members, 2 matched, 5 blocked, 3 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/2 words introduced by admitted or exact members; private data words 1 (reproduced)
- likely next missing introducer: _hanim_AddAnimObject
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 5

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _hanim_ActuallyRemoveAnimObjects | 248 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (65/105 opcodes, | EXPRESSION_SHAPE |  |
| _hanim_HideObject | 179 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (62/78 opcodes,  | SEMANTICS_UNKNOWN |  |
| _hanim_RemoveAllAnimObjects | 109 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (45/52 opcodes,  | SEMANTICS_UNKNOWN |  |
| _hanim_RemoveAnimObject | 260 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (70/107 opcodes, | EXPRESSION_SHAPE |  |
| _hanim_ShowObject | 179 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (70/78 opcodes,  | REGISTER_ALLOCATION |  |

### simant:5530 — 12 members, 5 matched, 5 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 1/20 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _CalcScore
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 5

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _EndGameDialog | 312 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (96/112 opcodes, 310/312 bytes) | REGISTER_ALLOCATION |  |
| _PictureDialog | 535 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (150/186 opcodes | SEMANTICS_UNKNOWN |  |
| _ScoreDialog | 244 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (71/85 opcodes, 238/244 bytes) | LOCAL_FRAME_LAYOUT |  |
| _win_DrawEndGameWindow | 301 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (100/115 opcodes, 318/301 bytes) | SEMANTICS_UNKNOWN |  |
| _win_DrawScoreWindow | 480 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (112/193 opcodes | SEMANTICS_UNKNOWN |  |

### simtwo:4CDC — 9 members, 4 matched, 5 blocked, 0 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/7 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoPillar
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 5

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DoPillar | 1576 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (403/607 opcodes | TRANSLATION_UNIT_CONTEXT |  |
| _MakeAPill | 767 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (221/325 opcodes, 888/767 byte | TRANSLATION_UNIT_CONTEXT |  |
| _MakePillFood | 560 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (203/223 opcodes | TRANSLATION_UNIT_CONTEXT |  |
| _PillFoodTile | 110 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (41/47 opcodes,  | REGISTER_ALLOCATION |  |
| _PlacePillTile | 40 | TRUE_SOURCE_SHAPE_MISMATCH | register allocation, frame layout under the current profile (20/20 opcodes, 40/40 bytes) | REGISTER_ALLOCATION,LOCAL_FRAME_LAYOUT |  |

### simone:4668 — 6 members, 1 matched, 4 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/21 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _InitSpider
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 4

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _InitSpider | 156 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (30/40 opcodes, 161/156 bytes) | TRANSLATION_UNIT_CONTEXT,PRIVATE_CONST_LAYOUT |  |
| _SFoundAnt | 319 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (51/132 opcodes, | LOCAL_FRAME_LAYOUT |  |
| _ScanForAnts | 113 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (45/46 opcodes, 111/113 bytes) | EXPRESSION_SHAPE |  |
| _SpiderScan | 387 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (124/160 opcodes | EXPRESSION_SHAPE |  |

### simtwo:858A — 5 members, 2 matched, 3 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DBAdd
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2, ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DBAdd | 327 | ABI_TYPE_INFERENCE | call/pointer-shape differences (CALLING_CONVENTION) | CALLING_CONVENTION |  |
| _DBPack | 547 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (129/192 opcodes | EXPRESSION_SHAPE |  |
| _DBRecall | 438 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (151/178 opcodes | REGISTER_ALLOCATION |  |

### simtwo:E4E8 — 3 members, 0 matched, 3 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _win_GetVal
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2, ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_GetArg | 60 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |
| __win_CalcObjElement | 307 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (58/139 opcodes, | EXPRESSION_SHAPE |  |
| _win_GetVal | 138 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (50/59 opcodes, 146/138 bytes) | REGISTER_ALLOCATION |  |

### antedit:67C6 — 5 members, 1 matched, 2 blocked, 2 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/11 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _EditToolsMenu
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AntMenu | 232 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (76/83 opcodes, 224/232 bytes) | SEMANTICS_UNKNOWN |  |
| _win_DrawExamineWindow | 395 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (101/179 opcodes | EXPRESSION_SHAPE |  |

### antedit:E100 — 6 members, 2 matched, 2 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/13 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _MapAreaEvent
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1, UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DrawMiniMapCursor | 155 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (37/43 opcodes, 167/155 bytes) | EXPRESSION_SHAPE |  |
| _ToggleMiniMapCursor | 203 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | EXPRESSION_SHAPE |  |

### simant1:96D4 — 3 members, 0 matched, 2 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/13 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoRedInitiator
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GetNewRedTask | 215 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (54/72 opcodes, 227/215 bytes) | SEMANTICS_UNKNOWN |  |
| _GetRedBestDirs | 220 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (62/89 opcodes, 219/220 bytes) | REGISTER_ALLOCATION |  |

### simant:94A4 — 26 members, 22 matched, 2 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 3/4 words introduced by admitted or exact members; private data words 1 (reproduced)
- likely next missing introducer: _UpdateLayQueenModeDisplay
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _TileIsVisible | 74 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (25/30 opcodes, 69/74 bytes) | DATA_LAYOUT |  |
| _UpdateLayQueenModeDisplay | 108 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (29/39 opcodes, 120/108 bytes) | PRIVATE_CONST_LAYOUT |  |

### simone:12E4 — 2 members, 0 matched, 2 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 2
- selector pool: 0/3 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _GetEnterDirB
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GetEnterDirB | 152 | TRUE_SOURCE_SHAPE_MISMATCH | frame layout under the current profile (60/60 opcodes, 152/152 bytes) | EXPRESSION_SHAPE | _GetEnterDirR (MATCH_BLOCKED) |
| _GetEnterDirR | 152 | TRUE_SOURCE_SHAPE_MISMATCH | frame layout under the current profile (60/60 opcodes, 152/152 bytes) | LOCAL_FRAME_LAYOUT | _GetEnterDirB (MATCH_BLOCKED) |

### simtwo:6C5A — 2 members, 0 matched, 2 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 2
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _AddBlackAnts
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AddBlackAnts | 163 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (51/60 opcodes, 166/163 bytes) | OPTIMIZER_VARIANT_REQUIRED | _AddRedAnts (MATCH_BLOCKED) |
| _AddRedAnts | 173 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (49/62 opcodes,  | OPTIMIZER_VARIANT_REQUIRED | _AddBlackAnts (MATCH_BLOCKED) |

### simtwo:78CA — 4 members, 0 matched, 2 blocked, 2 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/17 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _Feedback
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1, UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _RunTutor | 190 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (41/66 opcodes,  | OPTIMIZER_VARIANT_REQUIRED |  |
| _LessonDone | 627 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | DATA_LAYOUT |  |

### simtwo:81AC — 11 members, 9 matched, 2 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 1/1 words introduced by admitted or exact members; private data words 4 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 2

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _db_GetObjectSize | 84 | TRUE_SOURCE_SHAPE_MISMATCH | register allocation under the current profile (39/39 opcodes, 84/84 bytes) | REGISTER_ALLOCATION,LOCAL_FRAME_LAYOUT |  |
| _db_LoadObject | 188 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (73/81 opcodes, 192/188 bytes) | REGISTER_ALLOCATION |  |

### antedit:0000 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ZapEuMapAt | 76 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (30/33 opcodes,  | REGISTER_ALLOCATION |  |

### antedit:004C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _InvalEuMap | 168 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (52/67 opcodes,  | DATA_LAYOUT |  |

### antedit:6E1C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoWarnSetB
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DoWarnSetB | 86 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (25/35 opcodes,  | TRANSLATION_UNIT_CONTEXT |  |

### antedit:6E72 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoHealthSetY
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DoHealthSetY | 86 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (25/35 opcodes,  | TRANSLATION_UNIT_CONTEXT |  |

### antedit:6EE2 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/4 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _DoExpMenu
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DoExpMenu | 320 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (92/105 opcodes, 325/320 bytes) | SEMANTICS_UNKNOWN |  |

### antedit:8E56 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _UpdateListBox | 461 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (136/223 opcodes | EXPRESSION_SHAPE |  |

### antedit:90DC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ChangeDirectory | 364 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (106/147 opcodes | SEMANTICS_UNKNOWN |  |

### antedit:A51E — 2 members, 0 matched, 1 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/4 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _ProcYardEvent
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ProcYardEvent | 432 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (146/160 opcodes, 444/432 bytes) | REGISTER_ALLOCATION |  |

### gr:0000 — 4 members, 2 matched, 1 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/9 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _SetHelpCursor
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SetHelpCursor | 201 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (17/91 opcodes, 113/201 bytes) | OPTIMIZER_VARIANT_REQUIRED |  |

### gr:13EA — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GRectPartialMixedOutline | 291 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (85/119 opcodes, | EXPRESSION_SHAPE |  |

### gr:1792 — 1 members, 0 matched, 1 blocked, 0 ready; profile ogi

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _GPutStr
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GPutStr | 229 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (84/86 opcodes, 235/229 bytes) | SEMANTICS_UNKNOWN |  |

### gr:1966 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GInvBox | 78 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (19/32 opcodes,  | REGISTER_ALLOCATION |  |

### gr:19E6 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GBoxFill | 203 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (88/93 opcodes, 211/203 bytes) | SEMANTICS_UNKNOWN |  |

### gr:2A40 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _CopyBitmap2 | 370 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### gr:35D0 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ConvertMonoBitmap | 123 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (37/51 opcodes,  | OPTIMIZER_VARIANT_REQUIRED |  |

### gr:39B2 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DoFastBitmap | 405 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### gr:3D8A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GPutImgS | 39 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (9/16 opcodes, 33/39 bytes) | EXPRESSION_SHAPE |  |

### gr:3DFA — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _MSClipStart | 81 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (20/28 opcodes, 85/81 bytes) | PRIVATE_CONST_LAYOUT |  |

### gr:40D4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GUnpackPic | 186 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (51/79 opcodes, 175/186 bytes) | REGISTER_ALLOCATION |  |

### gr:457A — 3 members, 2 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/2 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _MySetCapture
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _MySetCapture | 88 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | PRIVATE_CONST_LAYOUT |  |

### gr:460A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _gr_FastMaskTileNoMask | 36 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (9/16 opcodes, 26/36 bytes) | REGISTER_ALLOCATION |  |

### gr:462E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ms_Delay | 46 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (12/18 opcodes, 45/46 bytes) | REGISTER_ALLOCATION,LOCAL_FRAME_LAYOUT |  |

### gr:465C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _gr_BitMapSize | 185 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (67/75 opcodes, 187/185 bytes) | EXPRESSION_SHAPE |  |

### gr:497A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _PointInRect | 106 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (22/55 opcodes, 150/106 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### gr:49E4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _WaitHundredths | 55 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (18/30 opcodes, 67/55 bytes) | REGISTER_ALLOCATION,LOCAL_FRAME_LAYOUT |  |

### gr:4C36 — 5 members, 3 matched, 1 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 1/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ms_LoadPopUpResource | 359 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (122/157 opcodes | EXPRESSION_SHAPE |  |

### gr:514C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _ms_PopUpMenuResource
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ms_PopUpMenuResource | 320 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (107/125 opcodes | SEMANTICS_UNKNOWN |  |

### gr:5492 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _mem_LockLevel | 41 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (13/23 opcodes, 41/41 bytes) | REGISTER_ALLOCATION |  |

### gr:55AA — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _mem_Size | 23 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (13/16 opcodes, 26/23 bytes) | REGISTER_ALLOCATION |  |

### gr:55D6 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _mem_SetType | 78 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (30/39 opcodes, 77/78 bytes) | EXPRESSION_SHAPE |  |

### gr:56A8 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _RallocFindMem | 329 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (112/117 opcodes, 329/329 bytes) | DATA_LAYOUT |  |

### gr:5E30 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ConvertMonoMaskToTandy | 221 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (71/94 opcodes,  | REGISTER_ALLOCATION |  |

### gr:5F0E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ConvertMonoMaskToColor | 379 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (104/201 opcodes | EXPRESSION_SHAPE |  |

### gr:60CE — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _font_StringWidth | 78 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | EXPRESSION_SHAPE |  |

### gr:611C — 3 members, 2 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 2/3 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _font_SetFont
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _font_SetFont | 80 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (18/38 opcodes, 75/80 bytes) | PRIVATE_CONST_LAYOUT |  |

### gr:73E0 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _gr_GetFromBuf | 342 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (106/147 opcodes | LOCAL_FRAME_LAYOUT |  |

### gr:7536 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _gr_PutToBuf | 342 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (107/142 opcodes | EXPRESSION_SHAPE |  |

### gr:768C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _UncompressDACInstrument | 133 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (53/60 opcodes,  | LOCAL_FRAME_LAYOUT |  |

### simant1:91DE — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _FillHolesBN | 102 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (34/40 opcodes, 100/102 bytes) | REGISTER_ALLOCATION |  |

### simant1:9244 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _FillHolesRN | 102 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (34/40 opcodes, 100/102 bytes) | REGISTER_ALLOCATION |  |

### simant1:92AA — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ColonySmellBN | 46 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simant1:92D8 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ColonySmellRN | 46 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simant1:9306 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ColonySmellBT | 62 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simant1:9344 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ColonySmellRT | 60 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simant1:9380 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SmoothAlarm | 187 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (69/79 opcodes, 173/187 bytes) | OPTIMIZER_VARIANT_REQUIRED |  |

### simant1:943C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AlarmHere | 65 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (27/31 opcodes, 75/65 bytes) | SEMANTICS_UNKNOWN |  |

### simant1:947E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AlarmHere2 | 56 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simant1:9612 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/3 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _GetSmellT
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GetSmellT | 106 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (34/46 opcodes, 108/106 bytes) | PRIVATE_CONST_LAYOUT |  |

### simant1:967C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/2 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _MakeRedInitiator
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _MakeRedInitiator | 88 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (20/31 opcodes, 102/88 bytes) | TRANSLATION_UNIT_CONTEXT,PRIVATE_CONST_LAYOUT |  |

### simant:0050 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _CleanUp | 186 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (56/65 opcodes, 205/186 bytes) | EXPRESSION_SHAPE |  |

### simant:010A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DecodeString | 172 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | OPTIMIZER_VARIANT_REQUIRED |  |

### simant:45E4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SetDevicePalette | 185 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (77/82 opcodes,  | EXPRESSION_SHAPE |  |

### simant:6954 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _CustomerIDDialog
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _CustomerIDDialog | 227 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (71/76 opcodes, 229/227 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### simant:92C0 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/5 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _EditMessage
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _EditMessage | 351 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (104/115 opcodes, 322/351 byte | PRIVATE_CONST_LAYOUT |  |

### simant:CDA8 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DrawSimPayoff | 401 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (139/156 opcodes | SEMANTICS_UNKNOWN |  |

### simant:D3E2 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _ShowIntro
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ShowIntro | 290 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### simant:D504 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _LoadMonoPats | 278 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (103/109 opcodes | SEMANTICS_UNKNOWN |  |

### simant:D628 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _MenuQuit | 66 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (24/29 opcodes, 68/66 bytes) | DATA_LAYOUT |  |

### simone:03F4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _LoadStringAnt | 231 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (84/95 opcodes,  | REGISTER_ALLOCATION |  |

### simone:10CC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GetDir | 86 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (45/49 opcodes, 93/86 bytes) | EXPRESSION_SHAPE |  |

### simone:1414 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/2 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _TryAntTheme
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _TryAntTheme | 104 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (27/34 opcodes, 111/104 bytes) | PRIVATE_CONST_LAYOUT |  |

### simone:147C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SGIRand | 39 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (17/22 opcodes, 36/39 bytes) | LOCAL_FRAME_LAYOUT |  |

### simone:14A4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SGRand | 39 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (17/22 opcodes, 38/39 bytes) | TOOLCHAIN_VARIANT_REQUIRED |  |

### simone:14CC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SGSRand | 57 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (21/32 opcodes, 47/57 bytes) | TOOLCHAIN_VARIANT_REQUIRED |  |

### simone:1536 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SeedRRand | 56 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (16/24 opcodes, 47/56 bytes) | TOOLCHAIN_VARIANT_REQUIRED |  |

### simone:158A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand1 | 35 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (7/21 opcodes, 43/35 bytes) | REGISTER_ALLOCATION,LOCAL_FRAME_LAYOUT |  |

### simone:15AE — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand2 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (6/15 opcodes, 35/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:15CE — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand4 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (3/12 opcodes, 22/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:15EE — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand8 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (3/12 opcodes, 22/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:160E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand16 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (3/12 opcodes, 22/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:162E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand32 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (3/12 opcodes, 22/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:164E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand64 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (3/12 opcodes, 22/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:166E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand128 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (3/12 opcodes, 22/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:168E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SRand256 | 31 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (2/12 opcodes, 21/31 bytes) | REGISTER_ALLOCATION,PRIVATE_CONST_LAYOUT |  |

### simone:255A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 1
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SmoothEdgesB | 362 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (113/152 opcodes | LOCAL_FRAME_LAYOUT | _SmoothEdgesR (MATCH_BLOCKED) |

### simone:26E4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 1
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _SmoothEdgesR | 362 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (113/152 opcodes | LOCAL_FRAME_LAYOUT | _SmoothEdgesB (MATCH_BLOCKED) |

### simone:29DA — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _FloodNestB | 60 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simone:3100 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _MakeMap | 32 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (12/18 opcodes, 32/32 bytes) | EXPRESSION_SHAPE |  |

### simone:44EC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AddRock5 | 191 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (60/79 opcodes,  | REGISTER_ALLOCATION |  |

### simone:45AC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AddRock3 | 188 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (69/77 opcodes,  | REGISTER_ALLOCATION |  |

### simone:59FC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _FindAntIndex | 213 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (79/86 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:3D4C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _Reproduce | 165 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (56/68 opcodes, 165/165 bytes) | REGISTER_ALLOCATION |  |

### simtwo:3DF2 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _StartMigrate | 121 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (42/45 opcodes, 119/121 bytes) | REGISTER_ALLOCATION |  |

### simtwo:3E6C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _EndMigrate | 139 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (54/62 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:5AB0 — 13 members, 12 matched, 1 blocked, 0 ready; profile og

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 59/60 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _AddFood
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _AddFood | 513 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (134/193 opcodes | REGISTER_ALLOCATION |  |

### simtwo:6DAC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GrabMap | 64 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (25/30 opcodes, 56/64 bytes) | DATA_LAYOUT |  |

### simtwo:6DEC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ClrArrays | 273 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (101/124 opcodes, 335/273 bytes) | SEMANTICS_UNKNOWN |  |

### simtwo:783E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _BlockMove | 33 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (12/24 opcodes, 45/33 bytes) | EXPRESSION_SHAPE |  |

### simtwo:7860 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _FlipHandleWords | 82 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (33/39 opcodes,  | LOCAL_FRAME_LAYOUT |  |

### simtwo:8BF0 — 3 members, 1 matched, 1 blocked, 1 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _OpenDB
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _CloseDB | 95 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (27/37 opcodes, 98/95 bytes) | PRIVATE_CONST_LAYOUT |  |

### simtwo:8E58 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _CopyRootName | 107 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (38/44 opcodes, 100/107 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### simtwo:8EC4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _GetFreeHandle | 72 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (24/30 opcodes, 73/72 bytes) | DATA_LAYOUT |  |

### simtwo:8F0C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DosPunt | 57 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (20/21 opcodes, 63/57 bytes) | EXPRESSION_SHAPE |  |

### simtwo:8F46 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_CreateTable | 265 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (88/114 opcodes, | SEMANTICS_UNKNOWN |  |

### simtwo:9050 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_RemoveEntry | 114 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (32/47 opcodes, 118/114 bytes) | DATA_LAYOUT |  |

### simtwo:90C2 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_PurgeCache | 128 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (47/48 opcodes, 128/128 bytes) | LOCAL_FRAME_LAYOUT |  |

### simtwo:9142 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_LookUpHandle | 163 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (68/70 opcodes, 167/163 bytes) | REGISTER_ALLOCATION |  |

### simtwo:9732 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_DeleteEntry | 114 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (36/47 opcodes, 110/114 bytes) | DATA_LAYOUT |  |

### simtwo:97A4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_CleanupTable | 226 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (56/81 opcodes,  | EXPRESSION_SHAPE |  |

### simtwo:9886 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_DumpOldest | 320 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (94/114 opcodes, | SEMANTICS_UNKNOWN |  |

### simtwo:99C6 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ch_GetPrime | 159 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (61/68 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:A201 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _PackWriteByte | 64 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (17/30 opcodes, 111/64 bytes) | DATA_LAYOUT |  |

### simtwo:A26A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _PackReadByte | 81 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (22/28 opcodes, 78/81 bytes) | PRIVATE_CONST_LAYOUT |  |

### simtwo:A325 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _PackFileToFile | 87 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | PRIVATE_CONST_LAYOUT |  |

### simtwo:A3BD — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _PackMemoryToMemory | 78 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (17/26 opcodes, 81/78 bytes) | PRIVATE_CONST_LAYOUT |  |

### simtwo:A62A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _UnpackInit | 62 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simtwo:A668 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _Unpack | 306 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, frame layout under the current profile (15/132 opcodes, 364/306 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### simtwo:A79A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _UnpackSetBuf | 22 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (7/10 opcodes, 24/22 bytes) | FAR_POINTER_TYPE |  |

### simtwo:A7B0 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _UnpackFileOpen | 57 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simtwo:A7E9 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _UnpackFileRead | 99 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simtwo:A84C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _UnpackFileClose | 11 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (3/4 opcodes, 10/11 bytes) | CALLING_CONVENTION |  |

### simtwo:A858 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _InitTree | 28 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (9/12 opcodes, 29/28 bytes) | EXPRESSION_SHAPE |  |

### simtwo:A874 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _InsertNode | 282 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (41/206 opcodes, | DATA_LAYOUT |  |

### simtwo:A98E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DeleteNode | 189 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (46/82 opcodes, 261/189 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### simtwo:AA4C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _font_ReadFont | 509 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simtwo:AC4A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _font_DumpFont | 123 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (39/43 opcodes, 126/123 bytes) | REGISTER_ALLOCATION |  |

### simtwo:ACC6 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| __font_StringWidth | 150 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (35/84 opcodes,  | OPTIMIZER_VARIANT_REQUIRED |  |

### simtwo:AD5C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: ABI_TYPE_INFERENCE 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| __font_CharWidth | 99 | ABI_TYPE_INFERENCE | call/pointer-shape differences (FAR_POINTER_TYPE) | FAR_POINTER_TYPE |  |

### simtwo:B033 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _DrawChar | 188 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (12/102 opcodes, 247/188 bytes | TOOLCHAIN_VARIANT_REQUIRED |  |

### simtwo:B0EF — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ClearBuffer | 32 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, frame layout under the current profile (6/20 opcodes, 32/32 bytes) | STRING_INTRINSIC_IDIOM,LOCAL_FRAME_LAYOUT |  |

### simtwo:B300 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _gr_JustifyStrInRect
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _gr_JustifyStrInRect | 234 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (91/96 opcodes, 229/234 bytes) | EXPRESSION_SHAPE |  |

### simtwo:B3EA — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetColorNum | 87 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (21/34 opcodes, 84/87 bytes) | PRIVATE_CONST_LAYOUT |  |

### simtwo:B4B2 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetColorFromObjNum | 152 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (53/62 opcodes, 147/152 bytes) | REGISTER_ALLOCATION |  |

### simtwo:B54A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _win_RectFill
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_RectFill | 264 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (93/97 opcodes, 256/264 bytes) | EXPRESSION_SHAPE |  |

### simtwo:B652 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_FillObjRect | 35 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape under the current profile (13/16 opcodes, 33/35 bytes) | EXPRESSION_SHAPE |  |

### simtwo:B676 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_RectFillOutline | 40 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (19/22 opcodes, 36/40 bytes) | EXPRESSION_SHAPE |  |

### simtwo:BB44 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_DrawObject | 32 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (13/17 opcodes, 30/32 bytes) | REGISTER_ALLOCATION |  |

### simtwo:BB96 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/1 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: _win_DrawWindow
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_DrawWindow | 256 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (42/99 opcodes,  | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### simtwo:BC98 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_DrawTitle | 193 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (60/78 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:BD5A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_DrawBitMap | 214 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout, frame layout under the current profile (74/91 opcodes, 209/214 bytes) | EXPRESSION_SHAPE |  |

### simtwo:C19E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_IsWinInFront | 107 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (44/50 opcodes, 99/107 bytes) | TRANSLATION_UNIT_CONTEXT_REQUIRED |  |

### simtwo:C256 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_IsWinOpen | 49 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (10/22 opcodes, 42/49 bytes) | EXPRESSION_SHAPE |  |

### simtwo:C288 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_IsWinZoomed | 49 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (10/22 opcodes, 42/49 bytes) | REGISTER_ALLOCATION |  |

### simtwo:C376 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_WinObjAddr | 87 | TRUE_SOURCE_SHAPE_MISMATCH | register allocation under the current profile (34/34 opcodes, 87/87 bytes) | REGISTER_ALLOCATION |  |

### simtwo:C606 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _RepointObjects | 91 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (37/39 opcodes, 87/91 bytes) | LOCAL_FRAME_LAYOUT |  |

### simtwo:E406 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_AutoSize | 225 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (51/87 opcodes, 185/225 bytes) | EXPRESSION_SHAPE |  |

### simtwo:E6E2 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_Recalc | 738 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | SEMANTICS_UNKNOWN |  |

### simtwo:EB96 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetGroupSelectableState | 118 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation under the current profile (44/51 opcodes, 121/118 bytes) | EXPRESSION_SHAPE |  |

### simtwo:EC0C — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeGroupSelectable | 125 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (34/52 opcodes, 112/125 bytes) | OPTIMIZER_VARIANT_REQUIRED |  |

### simtwo:EC8A — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeGroupUnselectable | 125 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (30/52 opcodes, 112/125 bytes) | OPTIMIZER_VARIANT_REQUIRED |  |

### simtwo:ED08 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetObjSelectedStateI | 331 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (105/128 opcodes, 328/331 byte | IMPORT_ORDINAL |  |

### simtwo:EE54 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetObjSelectedState | 195 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (60/85 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:EF18 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeObjSelected | 194 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (60/85 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:EFDC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeObjUnselected | 194 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (60/85 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F0A0 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetGroupSelectedState | 133 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (41/55 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F126 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetGroupSelectedObj | 141 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (48/60 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F1B4 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeGroupSelected | 132 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (41/55 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F238 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeGroupUnselected | 132 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (41/55 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F2BC — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetObjVisibleState | 344 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, branch layout under the current profile (120/132 opcodes, 341/344 bytes) | TRANSLATION_UNIT_CONTEXT |  |

### simtwo:F434 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_SetGroupVisibleState | 123 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (38/51 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F4B0 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeGroupVisible | 125 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (37/52 opcodes,  | OPTIMIZER_VARIANT_REQUIRED |  |

### simtwo:F52E — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_MakeGroupInvisible | 125 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (37/52 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F5FE — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_DrawGroupObjects | 134 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (42/55 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F684 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _win_ClearGroupAreas | 134 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout, frame layout under the current profile (42/55 opcodes,  | REGISTER_ALLOCATION |  |

### simtwo:F774 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: TRUE_SOURCE_SHAPE_MISMATCH 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _MemRChr | 33 | TRUE_SOURCE_SHAPE_MISMATCH | instruction shape, register allocation, branch layout under the current profile (10/29 opcodes, 49/33 bytes) | STRING_INTRINSIC_IDIOM |  |

### simtwo:F7CF — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _ConvertMonoToTandy | 119 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | TOOLCHAIN_VARIANT_REQUIRED |  |

### simtwo:F846 — 1 members, 0 matched, 1 blocked, 0 ready; profile baseline

- exact bodies awaiting admission: 0; mirrored blocked members: 0
- selector pool: 0/0 words introduced by admitted or exact members; private data words 0 (reproduced)
- likely next missing introducer: none (all introducers known)
- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): 0
- fresh causes: UNKNOWN 1

| symbol | size | fresh category | cause | previous | partner |
|---|---|---|---|---|---|
| _invert | 21 | UNKNOWN | no comparable candidate (compile failed or unmeasured) | STRING_INTRINSIC_IDIOM,REGISTER_ALLOCATION |  |


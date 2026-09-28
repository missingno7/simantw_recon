# Remaining near-exact blockers by compiler symptom

Generated 2026-09-28 by `python build/supervisor/residue_report.py` from `tools/residue_clusters.py --min 0.8`. It covers 174 open GAME functions whose frontier draft reaches at least 80% aligned opcodes. Each function is classified by its EARLIEST meaningful divergence in the draft-ledger FRONTIER, the draft that fixes the earliest compiler decision. Fixup-only placement rows and jumps that land on the same aligned instruction are skipped as downstream effects. Mechanisms refer to [msc7-codegen.md](msc7-codegen.md).

| Cluster | Functions | Mechanism |
|---|---:|---|
| EXPRESSION_SHAPE | 52 | Different instruction for the same operation |
| WRONG_STACK_SLOT | 29 | Home order of named locals |
| WRONG_REGISTER | 22 | Register targeting of a value |
| RELOAD_OR_SPILL | 22 | A value homed/reloaded on one side only |
| FRAME_SIZE | 21 | Frame size differs at ENTER |
| FAR_POINTER | 6 | Far-pointer load shape |
| CFG_DESTINATION | 6 | A branch lands on a different instruction |
| CALL_SEQUENCE | 5 | Argument pushes / call form |
| BLOCK_ORDER | 5 | Inserted/missing jump or block placement |
| RELOCATION_ONLY | 5 | All opcodes match; only placement/binding differs |
| FLAG_TEST | 1 | A flag test present on one side only |

## EXPRESSION_SHAPE: Different instruction for the same operation (52)

Known mechanism: E16-E22 (spellings that compile identically: do not search them), E23 (selector lifetime), S1/S2 (signedness, inline indexing). Most rows here are also register-targeting choices inside an expression (e.g. `mov di,[bp+8]` vs `mov ax,[bp+8]`); others are semantic draft errors (wrong constant/extent; _SmoothAlarm, _InitSow).

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_DecodeString` | 69/70 | `mov es, dx` | `mov es, word ptr [bp - 4]` |
| `_MowerFall` | 53/54 | `xor al, al` | `-` |
| `_ScanForAnts` | 45/46 | `mov ax, word ptr [bp - 6]` | `mov di, word ptr [bp - 6]` |
| `_RallocFindMem` | 114/117 | `mov dx, word ptr [0x880]` | `mov <resolved fixup> [{'kind': 'segment'` |
| `_DoRepoExit` | 66/68 | `mov <resolved fixup> [{'kind': 'internal` | `mov <resolved fixup> [{'kind': 'internal` |
| `_EatMyFood` | 151/156 | `sub ax, ax` | `mov di, 0x64` |
| `_win_GetArg` | 26/27 | `cmp <resolved fixup> [{'kind': 'internal` | `cmp <resolved fixup> [{'kind': 'internal` |
| `_ExitNest` | 149/155 | `mov bx, 0x9be0` | `mov <resolved fixup> [{'kind': 'internal` |
| `_TryMoveDirR` | 73/76 | `mov bx, dx` | `mov bx, ax` |
| `_AnimYellowInsane` | 151/158 | `mov di, word ptr [bp + 8]` | `mov ax, word ptr [bp + 8]` |
| `_StartMigrate` | 43/45 | `mov word ptr [bp - 2], es` | `mov word ptr es:[bx], ax` |
| `_ProcYardEvent` | 152/160 | `mov ax, es` | `-` |
| `_DeadAntHere` | 112/119 | `-` | `mov bx, word ptr es:[bx]` |
| `_DoToAlarm` | 235/250 | `xor cx, cx` | `mov byte ptr [bp - 2], 0` |
| `_MakeOutletH` | 94/101 | `mov bx, di` | `mov ax, di` |
| `_MakeOutletV` | 94/101 | `mov bx, di` | `mov ax, di` |
| `_DoAntSim` | 215/232 | `mov word ptr [0x9fb8], ax` | `-` |
| `_DoNestFightR` | 100/108 | `mov al, cl` | `mov <resolved fixup> [{'kind': 'internal` |
| `_win_Close` | 61/66 | `mov di, word ptr [bp + 6]` | `mov dx, word ptr [bp + 6]` |
| `_InitSpider` | 36/39 | `sbb cx, cx` | `jb 0x4f` |
| `_GetAlarmDir` | 115/125 | `mov di, si` | `mov word ptr [bp - 2], si` |
| `_SimQueenR` | 197/215 | `mov di, ax` | `-` |
| `_DrawMapSpider` | 98/108 | `mov di, word ptr [bp + 6]` | `mov si, word ptr [bp + 8]` |
| `_win_SetColorFromObjNum` | 56/62 | `mov es, dx` | `mov si, ax` |
| `_ButtonHeld` | 138/153 | `mov es, word ptr [0xc6bc]` | `mov <resolved fixup> [{'kind': 'internal` |
| `_UncompressDACInstrument` | 57/64 | `mov cx, 8` | `-` |
| `_DrawEditGraphs` | 129/145 | `mov word ptr [bp - 0xa], 0x8e00` | `mov <resolved fixup> [{'kind': 'internal` |
| `_StopSong` | 84/95 | `mov bx, 0x8d08` | `mov <resolved fixup> [{'kind': 'internal` |
| `_MakeHousePatch` | 293/332 | `mov word ptr [bp - 2], dx` | `mov word ptr [bp - 4], cx` |
| `_ColonySmellRT` | 29/33 | `add <resolved fixup> [{'kind': 'internal` | `-` |
| `_ch_DumpOldest` | 100/114 | `mov di, ax` | `mov di, bx` |
| `_DoNestFightB` | 105/121 | `mov al, cl` | `mov <resolved fixup> [{'kind': 'internal` |
| `_win_SetGroupSelectableState` | 44/51 | `mov ax, si` | `mov bx, si` |
| `_KillSomeAnts` | 61/71 | `mov bx, si` | `mov ax, si` |
| `_win_ObjFormatPrint` | 194/226 | `mov si, word ptr [bp + 6]` | `mov bx, word ptr [bp + 6]` |
| `_LessonDone` | 192/225 | `mov ax, 1` | `-` |
| `GTCLIENTWNDPROC` | 46/54 | `mov ax, ss` | `-` |
| `_CountAnts` | 199/235 | `-` | `mov <resolved fixup> [{'kind': 'segment'` |
| `_InitAntLions` | 111/131 | `xor ax, ax` | `lea ax, [bp - 0x10]` |
| `_SimQueenA` | 54/64 | `mov bl, byte ptr es:[bx + 0x23a4]` | `mov <resolved fixup> [{'kind': 'internal` |
| `_DrawCurBalloons` | 697/828 | `mov es, word ptr [0xbfb8]` | `mov <resolved fixup> [{'kind': 'internal` |
| `_TileCanBeMovedOn` | 120/143 | `mov cx, word ptr [bp + 6]` | `mov ax, word ptr [bp + 6]` |
| `_ForceModeA` | 62/74 | `enter 2, 0` | `-` |
| `_MakeLint2` | 40/48 | `cmp bx, dx` | `cmp dx, bx` |
| `_win_DrawExamineWindow` | 131/159 | `mov si, word ptr [0xcb70]` | `mov <resolved fixup> [{'kind': 'external` |
| `_FoodFall` | 51/62 | `mov di, word ptr [bp + 6]` | `mov cx, word ptr [bp + 8]` |
| `_SetLife` | 146/180 | `dec bx` | `or bx, bx` |
| `_TryAntTheme` | 29/36 | `mov bx, 0x80ba` | `mov <resolved fixup> [{'kind': 'internal` |
| `_win_FindObject` | 45/56 | `mov di, word ptr [bp + 6]` | `mov bx, word ptr [bp + 6]` |
| `_win_Swap` | 119/148 | `mov bx, word ptr [bp + 6]` | `mov al, byte ptr [bp + 7]` |
| `_Reproduce` | 53/66 | `mov <resolved fixup> [{'kind': 'internal` | `-` |
| `_snd_Install` | 233/291 | `-` | `mov <resolved fixup> [{'kind': 'segment'` |

## WRONG_STACK_SLOT: Home order of named locals (29)

Known mechanism: F1A-F1G (use-count rank, first reference, volatile by declaration, size classes); X1: dead constructs do not move homes; R-rules for register-vs-home. Remaining: which live use pattern the original had. Tool: tools/permuter.py.

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_UpdateEdit` | 235/235 | `mov word ptr [bp - 0xa], ax` | `mov word ptr [bp - 0xc], ax` |
| `_DrawCastePopUp` | 279/293 | `mov word ptr [bp - 2], 2` | `mov word ptr [bp - 0x16], 2` |
| `_LoadStringAnt` | 93/98 | `mov word ptr [bp - 6], dx` | `mov word ptr [bp - 8], dx` |
| `_SmoothAlarm` | 75/79 | `mov word ptr [bp - 6], dx` | `mov word ptr [bp - 8], dx` |
| `_DoRandAntAA` | 203/217 | `mov word ptr [bp - 0xc], ax` | `mov word ptr [bp - 0xa], ax` |
| `_AddIndex` | 136/146 | `mov word ptr [bp - 8], ax` | `mov word ptr [bp - 4], ax` |
| `_SimQueenB` | 206/221 | `mov word ptr [bp - 2], ax` | `mov word ptr [bp - 8], ax` |
| `_UpdateListBox` | 164/177 | `mov word ptr [bp - 0x106], bx` | `mov word ptr [bp - 0x108], bx` |
| `_win_ClearGroupAreas` | 51/55 | `mov word ptr [bp - 6], ax` | `mov word ptr [bp - 2], ax` |
| `_YellowFight` | 149/161 | `mov word ptr [bp - 4], cx` | `mov word ptr [bp - 8], cx` |
| `_PictureDialog` | 170/186 | `mov word ptr [bp - 8], ax` | `mov word ptr [bp - 6], ax` |
| `_SpecialXfer` | 157/175 | `mov ax, word ptr [bp - 8]` | `mov ax, word ptr [bp - 0xa]` |
| `_win_DrawTitle` | 70/78 | `mov word ptr [bp - 0xe], ax` | `mov word ptr [bp - 0xc], ax` |
| `_ProcModeEvent` | 277/310 | `mov word ptr [bp - 0xc], cx` | `mov word ptr [bp - 0xa], cx` |
| `_LoadMonoPats` | 101/114 | `mov word ptr [bp - 8], 0x18` | `mov word ptr [bp - 4], 0x18` |
| `_DBAdd` | 102/116 | `mov word ptr [bp - 6], ax` | `mov word ptr [bp - 4], ax` |
| `_CloseIndex` | 75/86 | `mov word ptr [bp - 0x66], ax` | `mov word ptr [bp - 0x6a], ax` |
| `_ReadConfig` | 191/219 | `mov word ptr [bp - 0xa], ax` | `mov word ptr [bp - 6], ax` |
| `_DoSow` | 91/105 | `mov word ptr [bp - 6], bx` | `mov word ptr [bp - 0xa], bx` |
| `_RibbonToolsMenu` | 209/243 | `lea ax, [bp - 0xc]` | `lea ax, [bp - 0x12]` |
| `_win_DrawGroupObjects` | 47/55 | `mov word ptr [bp - 6], ax` | `mov word ptr [bp - 2], ax` |
| `_DoRecruitAnt` | 229/268 | `mov word ptr [bp - 0xa], ax` | `mov word ptr [bp - 8], ax` |
| `_DoFoodInB` | 201/237 | `mov di, word ptr [bp + 8]` | `mov di, word ptr [bp + 6]` |
| `_SpiderScan` | 135/160 | `mov word ptr [bp - 0xa], ax` | `mov word ptr [bp - 0x12], ax` |
| `_DoAntMoveY` | 467/564 | `mov word ptr [bp - 6], 0` | `mov word ptr [bp - 0x12], 0` |
| `_win_MakeGroupSelected` | 45/55 | `mov word ptr [bp - 6], ax` | `mov word ptr [bp - 2], ax` |
| `_win_MakeGroupUnselected` | 45/55 | `mov word ptr [bp - 6], ax` | `mov word ptr [bp - 2], ax` |
| `_win_SetGroupSelectedState` | 45/55 | `mov word ptr [bp - 6], ax` | `mov word ptr [bp - 2], ax` |
| `_ms_LoadPopUpResource` | 126/157 | `mov word ptr [bp - 6], ax` | `mov word ptr [bp - 4], ax` |

## WRONG_REGISTER: Register targeting of a value (22)

Known mechanism: R1-R5 (SI/DI weights, scaled first subscript, long pair lifetime), F2/F3 (two-register pool, loop weight), C12 (join mapping), X2 (a branch-local temporary changes the schedule, _GetSmellT). Remaining: allocator choices with no source-level rule yet; the permuter finds some (_GetSmellT, _IsItYellow).

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_FloodNestB` | 27/27 | `xor di, di` | `xor cx, cx` |
| `_WaitHundredths` | 22/22 | `add ax, cx` | `add cx, ax` |
| `_AddRock3` | 76/77 | `mov di, word ptr [bp - 0xa]` | `mov ax, word ptr [bp - 0xa]` |
| `_DigTileR` | 96/98 | `mov bx, di` | `mov bx, si` |
| `_FillMap` | 37/38 | `mov di, word ptr [bp + 8]` | `mov bx, word ptr [bp + 8]` |
| `_SubtractFood` | 31/32 | `mov bx, di` | `mov ax, si` |
| `_AnimYellowFight` | 178/185 | `mov di, word ptr [bp + 0x10]` | `mov si, word ptr [bp + 0x10]` |
| `_PlaceDrop` | 55/59 | `mov bx, si` | `mov ax, si` |
| `_HistUpdate` | 87/94 | `xor di, di` | `xor si, si` |
| `_AddRock5` | 72/78 | `mov bx, word ptr [bp + 0xa]` | `mov ax, word ptr [bp + 0xa]` |
| `_HoleBorder` | 35/38 | `xor di, di` | `xor si, si` |
| `_FindAntIndex` | 79/86 | `mov <resolved fixup> [{'kind': 'internal` | `mov <resolved fixup> [{'kind': 'internal` |
| `_hanim_ShowObject` | 70/78 | `mov di, ax` | `mov si, ax` |
| `_CreateNewHole` | 161/182 | `mov di, ax` | `mov si, ax` |
| `_DigTileThemR` | 117/133 | `mov si, word ptr [bp + 8]` | `mov di, word ptr [bp + 8]` |
| `_FillHolesBN` | 35/40 | `mov <resolved fixup> [{'kind': 'internal` | `mov <resolved fixup> [{'kind': 'internal` |
| `_FillHolesRN` | 35/40 | `mov <resolved fixup> [{'kind': 'internal` | `mov <resolved fixup> [{'kind': 'internal` |
| `_DoNestingR` | 160/183 | `mov si, word ptr [bp + 6]` | `mov di, word ptr [bp + 6]` |
| `_PillFoodTile` | 41/47 | `push di` | `push si` |
| `_GrabMap` | 25/30 | `xor bx, bx` | `xor dx, dx` |
| `_MysteryButton` | 203/245 | `mov <resolved fixup> [{'kind': 'internal` | `mov <resolved fixup> [{'kind': 'internal` |
| `_win_DrawHistoryWindow` | 28/34 | `xor di, di` | `xor si, si` |

## RELOAD_OR_SPILL: A value homed/reloaded on one side only (22)

Known mechanism: F2 (third competitor gets a home), F4 (address-taking forces a home), E23 (far-return selector stays in DX until a call), P2 (a far call between test and use homes a pointer).

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_YellowCommand` | 223/228 | `mov word ptr [bp - 4], ax` | `-` |
| `_ch_LookUpHandle` | 68/70 | `-` | `mov word ptr [bp - 6], ax` |
| `_GtInitiateDDE` | 71/75 | `-` | `mov di, word ptr [bp + 6]` |
| `_GotoMyAnt` | 69/73 | `mov word ptr [bp - 2], si` | `-` |
| `_DoDrownB` | 68/72 | `mov si, word ptr [bp + 0xa]` | `-` |
| `_DoDrownR` | 68/72 | `mov si, word ptr [bp + 0xa]` | `-` |
| `_DoFoodInR` | 214/227 | `-` | `mov dx, word ptr [bp + 8]` |
| `_MakeSink` | 184/197 | `mov word ptr [bp - 2], di` | `-` |
| `_font_ReadFont` | 180/200 | `mov word ptr [bp - 4], si` | `-` |
| `_GotoBQueen` | 62/69 | `mov word ptr [bp - 2], si` | `-` |
| `_DigTileThemB` | 120/135 | `-` | `mov ax, word ptr [bp - 2]` |
| `_DoDigInB` | 218/252 | `mov si, word ptr [bp + 8]` | `-` |
| `_CopyRootName` | 38/44 | `mov ds, word ptr [bp + 8]` | `-` |
| `_IsClearTile` | 131/153 | `mov word ptr [bp - 2], cx` | `-` |
| `_ch_PurgeCache` | 46/54 | `-` | `mov word ptr [bp - 0xa], ax` |
| `_ForceModeB` | 54/65 | `-` | `mov si, word ptr [bp + 6]` |
| `_DigTileB` | 161/196 | `mov word ptr [bp - 4], ax` | `-` |
| `_DoNestingB` | 210/257 | `mov si, word ptr [bp + 0xc]` | `-` |
| `_CarpetFloorR` | 62/76 | `-` | `mov word ptr [bp - 2], 0` |
| `_win_MakeGroupInvisible` | 42/52 | `mov word ptr [bp - 6], si` | `-` |
| `_win_MakeGroupVisible` | 42/52 | `mov word ptr [bp - 6], si` | `-` |
| `_UpdateWindows` | 136/169 | `mov word ptr [bp - 4], bx` | `-` |

## FRAME_SIZE: Frame size differs at ENTER (21)

Known mechanism: F2/F6 (one competing local more or less), L7/L8 (used arrays/structs keep unused tails/members), L6 FALSIFIED (unused locals keep no slot), U2 (a function-pointer struct assignment adds a hidden 26-byte temporary).

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_GtRegisterClass` | 32/32 | `enter 0x4e, 0` | `enter 0x68, 0` |
| `_RepointObjects` | 37/39 | `enter 0x12, 0` | `enter 0xa, 0` |
| `_DoEditScroll` | 312/353 | `enter 6, 0` | `enter 0xa, 0` |
| `_EndMigrate` | 54/62 | `enter 8, 0` | `enter 2, 0` |
| `_win_DrawEndGameWindow` | 100/115 | `enter 0x1c, 0` | `enter 0x18, 0` |
| `_ms_PopUpMenuResource` | 107/125 | `enter 0x1a, 0` | `enter 0x16, 0` |
| `_DrawMapFoot` | 146/171 | `enter 0x1e, 0` | `enter 0x1c, 0` |
| `_CheatKeys` | 372/436 | `enter 6, 0` | `enter 4, 0` |
| `_FlipHandleWords` | 33/39 | `enter 0xa, 0` | `enter 6, 0` |
| `_DoWater` | 260/308 | `enter 0xc, 0` | `enter 8, 0` |
| `_DoDigOutB` | 201/240 | `enter 0x14, 0` | `enter 0x18, 0` |
| `_win_ClearObjToEOL` | 98/117 | `enter 0x16, 0` | `enter 0x14, 0` |
| `_win_CasteControlChanged` | 147/176 | `enter 0x16, 0` | `enter 0x18, 0` |
| `_DoAntLions` | 520/626 | `enter 0x2e, 0` | `enter 0x22, 0` |
| `_SimKidOutside` | 587/709 | `enter 0x22, 0` | `enter 0x26, 0` |
| `_win_GetEvent` | 148/180 | `enter 0x28, 0` | `enter 0x20, 0` |
| `_DigMyTile` | 160/195 | `enter 0xe, 0` | `enter 0xc, 0` |
| `_MakeNewHoleR` | 207/254 | `enter 0x12, 0` | `enter 0xc, 0` |
| `_LoadTiles` | 650/799 | `enter 0x38, 0` | `enter 0x2e, 0` |
| `_MakeNewHoleB` | 143/176 | `enter 0xa, 0` | `enter 8, 0` |
| `_ChangeDirectory` | 118/147 | `enter 0x10e, 0` | `enter 0x110, 0` |

## FAR_POINTER: Far-pointer load shape (6)

Known mechanism: P3 (a local alias of a far parameter gives LES), P4 (constant-address argument is folded to a direct push), P5 OPEN (early LDS). Tension with F2: the alias adds a home.

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_SetDevicePalette` | 76/80 | `lds si, ptr [bp + 0xc]` | `mov si, word ptr [bp + 0xc]` |
| `_font_DumpFont` | 41/44 | `les si, ptr [bp + 6]` | `mov si, word ptr [bp + 6]` |
| `_XferPatch` | 127/137 | `mov es, word ptr [0xc106]` | `-` |
| `_ClrArrays` | 97/105 | `mov es, cx` | `-` |
| `_gr_BitMapSize` | 69/75 | `les bx, ptr [bp + 6]` | `mov bx, word ptr [bp + 6]` |
| `_ch_GetPrime` | 59/68 | `mov es, dx` | `-` |

## CFG_DESTINATION: A branch lands on a different instruction (6)

Known mechanism: Control-flow semantics of the draft (retry loops C1, continue vs break C22, shared tails C23); usually a draft error, fixable by reading the target.

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_DrawControlLevels` | 198/227 | `jne 0x84` | `je 0x60` |
| `_MapToYellowAnt` | 39/45 | `jg 0x44` | `jg 0x46` |
| `_YellowDialog` | 145/175 | `jmp 0x207` | `jmp 0x1cd` |
| `_win_DrawBitMap` | 74/91 | `jmp 0xd0` | `jmp 0xcd` |
| `_mySongIsDone` | 17/21 | `je 0x32` | `jne 0x33` |
| `_SpiderDialog` | 159/197 | `jne 0x114` | `je 0x9d` |

## CALL_SEQUENCE: Argument pushes / call form (5)

Known mechanism: Branch-specific pushes before a shared call (_DoMenuEntry, C18/C24); ABI of callees.

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_DoMenuEntry` | 179/183 | `push 1` | `mov si, 1` |
| `_CleanUp` | 56/65 | `push di` | `-` |
| `_EndGameDialog` | 96/112 | `push 0` | `-` |
| `_ProcYardRibbonEvent` | 223/264 | `push 0x7e` | `push 1` |
| `_win_DrawEditWindow` | 57/69 | `push si` | `-` |

## BLOCK_ORDER: Inserted/missing jump or block placement (5)

Known mechanism: C13 FALSIFIED (tail does not decide test placement); C15/C19/C20/C23 equivalences.

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_TryMoveDirB` | 93/95 | `nop ` | `-` |
| `_DrawMap` | 88/91 | `nop ` | `lcall <resolved fixup> [{'kind': 'extern` |
| `_SimBird` | 188/200 | `jne 0x17f` | `je 0x17c` |
| `_DoEditScrollLine` | 101/109 | `nop ` | `-` |
| `_DoRestAnt` | 55/66 | `-` | `je 0x79` |

## RELOCATION_ONLY: All opcodes match; only placement/binding differs (5)

Known mechanism: Unit lane. The members listed have known non-placement blockers: shared string layout (D1: _SetPause/_PauseGame), unrecovered private helper chain 16D4/6250/63FE (_UpdateEditIfBufInvalid), argument folding P4 (_win_*ControlClosed).

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_PauseGame` | 129/129 | `-` | `-` |
| `_SetPause` | 129/129 | `-` | `-` |
| `_UpdateEditIfBufInvalid` | 26/26 | `-` | `-` |
| `_win_CasteControlClosed` | 53/53 | `-` | `-` |
| `_win_ModeControlClosed` | 53/53 | `-` | `-` |

## FLAG_TEST: A flag test present on one side only (1)

Known mechanism: C1 (loop test reached by two paths = retry loop).

| Function | Opcodes | Target | Candidate |
|---|---|---|---|
| `_GetMowDir` | 90/92 | `or si, si` | `js 0x3c` |

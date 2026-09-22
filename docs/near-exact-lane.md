# Near-exact source-shape lane (>= 95% opcode agreement)

Generated 2026-09-22T11:08:13.558068+00:00. 38 functions. Families: BINDING 7, BRANCH 1, FRAME 7, REGISTER 3, REGISTER_FRAME 2, NEAR_SHAPE 18

| symbol | context | family | opcodes | bytes | reg/br/stack | siblings | first residual |
|---|---|---|---|---|---|---|---|
| _DoTroph | simant:6A38 | BINDING | 37/37 | 93/93 | 0/0/0 |  | {'offset': 30, 'symbol': '_Dy8', 'resolved': {'kind': 'internal', 'segment': 8, 'offset': 16}} |
| _win_CasteControlClosed | simant:B324 | BINDING | 53/53 | 151/149 | 0/0/0 | _win_ModeControlClosed | {'offset': 27, 'target': "lcall <resolved fixup> [{'kind': 'internal', 'segment': 2, 'offset': 0}]", 'candidate': "lcall |
| _win_ModeControlClosed | simant:B324 | BINDING | 53/53 | 151/149 | 0/0/0 | _win_CasteControlClosed | {'offset': 27, 'target': "lcall <resolved fixup> [{'kind': 'internal', 'segment': 2, 'offset': 0}]", 'candidate': "lcall |
| _GetNearbyPatches | simtwo:1378 | BINDING | 39/39 | 103/103 | 0/0/0 |  | {'offset': 77, 'target': 'cmp byte ptr es:[bx + 0x164], 0', 'candidate': "cmp <resolved fixup> [{'kind': 'internal', 'se |
| _AddRandAntLion | simtwo:3EF8 | BINDING | 107/107 | 285/285 | 0/0/0 |  | {'offset': 150, 'symbol': '_Dy8', 'resolved': {'kind': 'internal', 'segment': 8, 'offset': 8}} |
| _DBDelete | simtwo:858A | BINDING | 62/62 | 153/153 | 0/0/0 |  | {'offset': 147, 'symbol': '_openDBData', 'resolved': {'kind': 'internal', 'segment': 9, 'offset': 29824}} |
| _DBReplace | simtwo:858A | BINDING | 64/64 | 169/169 | 0/0/0 |  | {'offset': 129, 'target': 'mov word ptr es:[si + 0x7482], 1', 'candidate': "mov <resolved fixup> [{'kind': 'internal', ' |
| _FeedAnts | simant1:0000 | BRANCH | 28/28 | 100/100 | 0/1/0 |  | {'offset': 4, 'target': 'cmp word ptr es:[0x8a60], 0', 'candidate': "cmp <resolved fixup> [{'kind': 'internal', 'segment |
| _PreDrawSpider | antedit:00F4 | FRAME | 116/116 | 337/337 | 0/0/4 |  | {'offset': 59, 'target': 'mov word ptr [bp - 6], ax', 'candidate': 'mov word ptr [bp - 8], ax', 'differences': ['memory_ |
| _DrawColonyBars | antedit:A998 | FRAME | 88/88 | 253/253 | 0/0/10 |  | {'offset': 0, 'target': 'enter 0x10, 0', 'candidate': 'enter 0xe, 0', 'differences': ['immediate_or_binding']} |
| _GSetBigFont | gr:1560 | FRAME | 90/90 | 259/259 | 0/0/4 | _GSetSmallFont | {'offset': 16, 'target': 'push 0xba48', 'candidate': "push <resolved fixup> [{'kind': 'segment', 'name': '_DATA'}]", 'di |
| _GSetSmallFont | gr:1560 | FRAME | 90/90 | 259/259 | 0/0/4 | _GSetBigFont | {'offset': 16, 'target': 'push 0xba34', 'candidate': "push <resolved fixup> [{'kind': 'segment', 'name': '_DATA'}]", 'di |
| _InitApplication | simant:01B6 | FRAME | 90/90 | 315/315 | 0/0/33 |  | {'offset': 0, 'target': 'enter 0x138, 0', 'candidate': 'enter 0x11e, 0', 'differences': ['immediate_or_binding']} |
| _GetEnterDirB | simone:12E4 | FRAME | 60/60 | 152/152 | 0/0/5 | _GetEnterDirR | {'offset': 11, 'target': 'mov word ptr [bp - 4], ax', 'candidate': 'mov word ptr [bp - 6], ax', 'differences': ['memory_ |
| _GetEnterDirR | simone:12E4 | FRAME | 60/60 | 152/152 | 0/0/5 | _GetEnterDirB | {'offset': 11, 'target': 'mov word ptr [bp - 4], ax', 'candidate': 'mov word ptr [bp - 6], ax', 'differences': ['memory_ |
| _NotMowed | simtwo:1378 | REGISTER | 26/26 | 52/52 | 6/0/0 |  | {'offset': 10, 'target': 'mov bx, word ptr [bp + 6]', 'candidate': 'mov di, word ptr [bp + 6]', 'differences': ['registe |
| _db_GetObjectSize | simtwo:81AC | REGISTER | 39/39 | 84/84 | 7/0/0 |  | {'offset': 6, 'target': 'xor si, si', 'candidate': 'xor di, di', 'differences': ['register_allocation']} |
| _win_WinObjAddr | simtwo:C376 | REGISTER | 34/34 | 87/87 | 3/0/0 |  | {'offset': 41, 'target': 'mov ax, si', 'candidate': 'mov cx, si', 'differences': ['register_allocation']} |
| _LostHeadA | simant1:0000 | REGISTER_FRAME | 39/39 | 87/87 | 4/0/2 |  | {'offset': 23, 'target': 'add si, word ptr [bp + 6]', 'candidate': 'add si, word ptr [bp + 4]', 'differences': ['memory_ |
| _PlacePillTile | simtwo:4CDC | REGISTER_FRAME | 20/20 | 40/40 | 4/0/2 |  | {'offset': 5, 'target': 'mov di, word ptr [bp + 6]', 'candidate': 'mov di, word ptr [bp + 8]', 'differences': ['memory_o |
| __win_SetProxItem | simtwo:C806 | NEAR_SHAPE | 74/75 | 197/197 | 0/0/0 |  | {'offset': 120, 'target': 'je 0xb3', 'candidate': 'jle 0xb3', 'differences': ['instruction_shape']} |
| _CenterEdit | antedit:00F4 | NEAR_SHAPE | 66/67 | 180/180 | 0/0/0 |  | {'offset': 46, 'target': 'call 0x4b4c', 'candidate': "call <resolved fixup> [{'kind': 'external', 'name': '_ScrollEditBy |
| _InitAntLions | simtwo:3EF8 | NEAR_SHAPE | 121/123 | 353/347 | 0/0/4 |  | {'offset': 0, 'target': 'enter 0x12, 0', 'candidate': 'enter 0xc, 0', 'differences': ['immediate_or_binding']} |
| _ScanForAnts | simone:4668 | NEAR_SHAPE | 45/46 | 111/113 | 2/6/0 |  | {'offset': 35, 'target': 'mov ax, word ptr [bp - 6]', 'candidate': 'mov di, word ptr [bp - 6]', 'differences': ['registe |
| _DecTSmell | simant1:95B6 | NEAR_SHAPE | 39/40 | 92/92 | 16/0/1 |  | {'offset': 5, 'target': 'mov bx, word ptr [bp + 4]', 'candidate': 'mov di, word ptr [bp + 6]', 'differences': ['memory_o |
| _win_DrawCasteWindow | simant:B324 | NEAR_SHAPE | 77/79 | 216/216 | 0/0/9 | _win_DrawModeWindow | {'offset': 11, 'target': 'and al, 1', 'candidate': 'test al, 1', 'differences': ['instruction_shape']} |
| _win_DrawModeWindow | simant:B324 | NEAR_SHAPE | 77/79 | 216/216 | 0/0/0 | _win_DrawCasteWindow | {'offset': 11, 'target': 'and al, 1', 'candidate': 'test al, 1', 'differences': ['instruction_shape']} |
| _ch_LookUpHandle | simtwo:9142 | NEAR_SHAPE | 68/70 | 167/163 | 1/4/1 |  | {'offset': None, 'target': '', 'candidate': 'mov word ptr [bp - 6], ax', 'differences': ['instruction_shape']} |
| _GotoBQueen | simant:9D04 | NEAR_SHAPE | 67/69 | 205/205 | 0/0/6 |  | {'offset': 0, 'target': 'enter 6, 0', 'candidate': 'enter 4, 0', 'differences': ['immediate_or_binding']} |
| _SubtractFood | simant:9D04 | NEAR_SHAPE | 31/32 | 79/77 | 2/1/2 |  | {'offset': 10, 'target': 'mov bx, di', 'candidate': 'mov ax, si', 'differences': ['register_allocation']} |
| _DrawMap | antedit:C19C | NEAR_SHAPE | 88/91 | 264/264 | 0/0/0 |  | {'offset': 33, 'target': 'nop ', 'candidate': "lcall <resolved fixup> [{'kind': 'external', 'name': '_CalcMapCursorRect' |
| _FoodFall | simone:04DE | NEAR_SHAPE | 55/57 | 154/150 | 0/6/0 |  | {'offset': 0, 'target': 'enter 0xa, 0', 'candidate': 'enter 8, 0', 'differences': ['immediate_or_binding']} |
| _win_RectFill | simtwo:B54A | NEAR_SHAPE | 93/97 | 256/264 | 0/0/0 |  | {'offset': 70, 'target': 'mov es, word ptr [0xc6c6]', 'candidate': '', 'differences': ['instruction_shape']} |
| _ch_PurgeCache | simtwo:90C2 | NEAR_SHAPE | 46/48 | 128/128 | 2/0/6 |  | {'offset': 0, 'target': 'enter 0x12, 0', 'candidate': 'enter 0xe, 0', 'differences': ['immediate_or_binding']} |
| MYENUMFUNC | simant:01B6 | NEAR_SHAPE | 22/23 | 49/48 | 0/0/0 |  | {'offset': 0, 'target': 'mov ax, ss', 'candidate': '', 'differences': ['instruction_shape']} |
| _ClearMapScentButtons | simant:94A4 | NEAR_SHAPE | 20/21 | 68/65 | 0/2/0 |  | {'offset': 13, 'target': 'je 0x1f', 'candidate': 'je 0x43', 'differences': ['branch_target']} |
| _DosPunt | simtwo:8F0C | NEAR_SHAPE | 20/21 | 63/57 | 0/0/0 |  | {'offset': 11, 'target': 'push 0xb4e4', 'candidate': "push <resolved fixup> [{'kind': 'segment', 'name': '_DATA'}]", 'di |
| _MyGetTopWindow | simtwo:C0B2 | NEAR_SHAPE | 38/40 | 83/79 | 0/2/0 |  | {'offset': 50, 'target': 'je 0x4a', 'candidate': 'je 0x12', 'differences': ['branch_target']} |

# Near-exact source-shape lane (>= 95% opcode agreement)

Generated 2026-09-23T01:41:08.737587+00:00. 37 functions. Families: BINDING 5, FRAME 6, REGISTER 3, REGISTER_FRAME 1, NEAR_SHAPE 22

| symbol | context | family | opcodes | bytes | reg/br/stack | siblings | first residual |
|---|---|---|---|---|---|---|---|
| _ScrollEditWindow | antedit:00F4 | BINDING | 57/57 | 165/165 | 0/0/0 |  | {'offset': 60, 'symbol': '_tileHeight', 'resolved': {'kind': 'internal', 'segment': 10, 'offset': 5180}} |
| _UpdateEditIfBufInvalid | antedit:00F4 | BINDING | 26/26 | 82/82 | 0/0/0 |  | {'offset': 71, 'target': 'call 0x238', 'candidate': "call <resolved fixup> [{'kind': 'internal', 'segment': 3, 'offset': |
| _ToggleMapCursor | antedit:C19C | BINDING | 85/85 | 261/261 | 0/0/0 |  | {'offset': 208, 'symbol': '_mapTileRect', 'resolved': {'kind': 'internal', 'segment': 9, 'offset': 33040}} |
| _win_CasteControlClosed | simant:B324 | BINDING | 53/53 | 151/149 | 0/0/0 | _win_ModeControlClosed | {'offset': 27, 'target': "lcall <resolved fixup> [{'kind': 'internal', 'segment': 2, 'offset': 0}]", 'candidate': "lcall |
| _win_ModeControlClosed | simant:B324 | BINDING | 53/53 | 151/149 | 0/0/0 | _win_CasteControlClosed | {'offset': 27, 'target': "lcall <resolved fixup> [{'kind': 'internal', 'segment': 2, 'offset': 0}]", 'candidate': "lcall |
| _DrawColonyBars | antedit:A998 | FRAME | 88/88 | 253/253 | 0/0/10 |  | {'offset': 0, 'target': 'enter 0x10, 0', 'candidate': 'enter 0xe, 0', 'differences': ['immediate_or_binding']} |
| _DoReturnFoodAnt | simant1:0000 | FRAME | 142/142 | 398/398 | 0/0/2 |  | {'offset': 275, 'target': 'mov al, byte ptr [bp - 4]', 'candidate': 'mov al, byte ptr [bp - 0xa]', 'differences': ['memo |
| _InitApplication | simant:01B6 | FRAME | 90/90 | 315/315 | 0/0/33 |  | {'offset': 0, 'target': 'enter 0x138, 0', 'candidate': 'enter 0x11e, 0', 'differences': ['immediate_or_binding']} |
| _GetEnterDirB | simone:12E4 | FRAME | 60/60 | 152/152 | 0/0/5 | _GetEnterDirR | {'offset': 11, 'target': 'mov word ptr [bp - 4], ax', 'candidate': 'mov word ptr [bp - 6], ax', 'differences': ['memory_ |
| _GetEnterDirR | simone:12E4 | FRAME | 60/60 | 152/152 | 0/0/5 | _GetEnterDirB | {'offset': 11, 'target': 'mov word ptr [bp - 4], ax', 'candidate': 'mov word ptr [bp - 6], ax', 'differences': ['memory_ |
| _SetCasteProd | simtwo:0000 | FRAME | 74/74 | 183/183 | 0/0/13 |  | {'offset': 0, 'target': 'enter 0x1a, 0', 'candidate': 'enter 0x16, 0', 'differences': ['immediate_or_binding']} |
| _NotMowed | simtwo:1378 | REGISTER | 26/26 | 52/52 | 6/0/0 |  | {'offset': 10, 'target': 'mov bx, word ptr [bp + 6]', 'candidate': 'mov di, word ptr [bp + 6]', 'differences': ['registe |
| _db_GetObjectSize | simtwo:81AC | REGISTER | 39/39 | 84/84 | 7/0/0 |  | {'offset': 6, 'target': 'xor si, si', 'candidate': 'xor di, di', 'differences': ['register_allocation']} |
| _win_WinObjAddr | simtwo:C376 | REGISTER | 34/34 | 87/87 | 3/0/0 |  | {'offset': 41, 'target': 'mov ax, si', 'candidate': 'mov cx, si', 'differences': ['register_allocation']} |
| _PlacePillTile | simtwo:4CDC | REGISTER_FRAME | 20/20 | 40/40 | 4/0/2 |  | {'offset': 5, 'target': 'mov di, word ptr [bp + 6]', 'candidate': 'mov di, word ptr [bp + 8]', 'differences': ['memory_o |
| _win_DrawVBar | simtwo:C806 | NEAR_SHAPE | 81/82 | 194/194 | 0/0/1 |  | {'offset': 96, 'target': 'mov si, word ptr [bp - 6]', 'candidate': '', 'differences': ['instruction_shape']} |
| _win_DrawHBar | simtwo:C806 | NEAR_SHAPE | 80/81 | 192/192 | 0/0/0 |  | {'offset': 96, 'target': 'mov si, word ptr [bp - 4]', 'candidate': '', 'differences': ['instruction_shape']} |
| __win_SetProxItem | simtwo:C806 | NEAR_SHAPE | 74/75 | 197/197 | 0/0/0 |  | {'offset': 120, 'target': 'je 0xb3', 'candidate': 'jle 0xb3', 'differences': ['instruction_shape']} |
| _CenterEdit | antedit:00F4 | NEAR_SHAPE | 66/67 | 180/180 | 0/0/0 |  | {'offset': 46, 'target': 'call 0x4b4c', 'candidate': "call <resolved fixup> [{'kind': 'external', 'name': '_ScrollEditBy |
| _InitAntLions | simtwo:3EF8 | NEAR_SHAPE | 121/123 | 353/347 | 0/0/4 |  | {'offset': 0, 'target': 'enter 0x12, 0', 'candidate': 'enter 0xc, 0', 'differences': ['immediate_or_binding']} |
| _MowerFall | simtwo:1378 | NEAR_SHAPE | 53/54 | 166/166 | 0/0/0 |  | {'offset': 84, 'target': 'xor al, al', 'candidate': '', 'differences': ['instruction_shape']} |
| _ch_PurgeCache | simtwo:90C2 | NEAR_SHAPE | 47/48 | 128/128 | 0/0/6 |  | {'offset': 0, 'target': 'enter 0x12, 0', 'candidate': 'enter 0xe, 0', 'differences': ['immediate_or_binding']} |
| _win_Events | simtwo:C806 | NEAR_SHAPE | 46/47 | 112/112 | 0/0/0 |  | {'offset': 5, 'target': 'xor si, si', 'candidate': '', 'differences': ['instruction_shape']} |
| _ScanForAnts | simone:4668 | NEAR_SHAPE | 45/46 | 111/113 | 2/6/0 |  | {'offset': 35, 'target': 'mov ax, word ptr [bp - 6]', 'candidate': 'mov di, word ptr [bp - 6]', 'differences': ['registe |
| _GetMowDir | simtwo:1378 | NEAR_SHAPE | 90/92 | 223/225 | 9/11/2 |  | {'offset': 26, 'target': 'add si, word ptr [bp + 6]', 'candidate': 'add si, word ptr [bp + 8]', 'differences': ['memory_ |
| _GPutStr | gr:1792 | NEAR_SHAPE | 84/86 | 235/229 | 0/4/0 |  | {'offset': 9, 'target': 'jne 0x32', 'candidate': 'jne 0x38', 'differences': ['branch_target']} |
| _win_DrawCasteWindow | simant:B324 | NEAR_SHAPE | 77/79 | 216/216 | 0/0/9 | _win_DrawModeWindow | {'offset': 11, 'target': 'and al, 1', 'candidate': 'test al, 1', 'differences': ['instruction_shape']} |
| _win_DrawModeWindow | simant:B324 | NEAR_SHAPE | 77/79 | 216/216 | 0/0/0 | _win_DrawCasteWindow | {'offset': 11, 'target': 'and al, 1', 'candidate': 'test al, 1', 'differences': ['instruction_shape']} |
| _ch_LookUpHandle | simtwo:9142 | NEAR_SHAPE | 68/70 | 167/163 | 1/4/1 |  | {'offset': None, 'target': '', 'candidate': 'mov word ptr [bp - 6], ax', 'differences': ['instruction_shape']} |
| _GotoBQueen | simant:9D04 | NEAR_SHAPE | 67/69 | 205/205 | 0/0/6 |  | {'offset': 0, 'target': 'enter 6, 0', 'candidate': 'enter 4, 0', 'differences': ['immediate_or_binding']} |
| _GetForageDir | simtwo:0000 | NEAR_SHAPE | 156/161 | 386/384 | 0/5/0 |  | {'offset': 23, 'target': 'jmp 0x17c', 'candidate': 'jmp 0x17e', 'differences': ['branch_target']} |
| _SubtractFood | simant:9D04 | NEAR_SHAPE | 31/32 | 79/77 | 2/1/2 |  | {'offset': 10, 'target': 'mov bx, di', 'candidate': 'mov ax, si', 'differences': ['register_allocation']} |
| _DrawMap | antedit:C19C | NEAR_SHAPE | 88/91 | 264/264 | 0/0/0 |  | {'offset': 33, 'target': 'nop ', 'candidate': "lcall <resolved fixup> [{'kind': 'external', 'name': '_CalcMapCursorRect' |
| _FoodFall | simone:04DE | NEAR_SHAPE | 55/57 | 154/150 | 0/6/0 |  | {'offset': 0, 'target': 'enter 0xa, 0', 'candidate': 'enter 8, 0', 'differences': ['immediate_or_binding']} |
| _SetMyLife | simone:5AD2 | NEAR_SHAPE | 76/79 | 196/196 | 0/0/0 |  | {'offset': 100, 'target': 'jne 0x6e', 'candidate': 'je 0x6c', 'differences': ['instruction_shape']} |
| _win_RectFill | simtwo:B54A | NEAR_SHAPE | 93/97 | 256/264 | 0/0/0 |  | {'offset': 70, 'target': 'mov es, word ptr [0xc6c6]', 'candidate': '', 'differences': ['instruction_shape']} |
| _DosPunt | simtwo:8F0C | NEAR_SHAPE | 20/21 | 63/57 | 0/0/0 |  | {'offset': 11, 'target': 'push 0xb4e4', 'candidate': "push <resolved fixup> [{'kind': 'segment', 'name': '_DATA'}]", 'di |

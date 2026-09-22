# Recovery task _DoBookMark

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 513 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 push 0x11
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
000d test ah, 0x80
0010 jne 0x8bb
0012 jmp 0x972
0015 mov si, word ptr [bp + 6]
0018 mov ax, word ptr [0xcc76] ; _MapPlane
001b mov es, word ptr [0xbe7a]
001f mov dx, si
0021 mov cx, si
0023 shl si, 2
0026 add si, cx
0028 shl si, 1
002a mov word ptr es:[si - 0x7560], ax
002f mov es, word ptr [0xbe7c]
0033 mov cx, word ptr es:[0x7d2e]
0038 mov ax, word ptr es:[0x7d30]
003c mov es, word ptr [0xbe7a]
0040 mov word ptr es:[si - 0x755e], cx
0045 mov word ptr es:[si - 0x755c], ax
004a mov es, word ptr [0xbe7e]
004e mov ax, word ptr es:[0x8610]
0052 mov es, word ptr [0xbe7a]
0056 mov word ptr es:[si - 0x755a], ax
005b mov ax, word ptr [0xce82] ; _YardMode
005e mov word ptr es:[si - 0x7558], ax
0063 mov ax, dx
0065 add dx, 0x38ab
0069 push dx
006a mov cx, ax
006c add ax, 0x38dd
006f push ax
0070 mov bx, cx
0072 add cx, 0x2218
0076 push cx
0077 mov si, ax
0079 mov di, cx
007b mov word ptr [bp - 2], dx
007e mov word ptr [bp - 4], bx
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
0086 add sp, 6
0089 push 0
008b push di
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0091 add sp, 4
0094 push word ptr [bp - 2]
0097 push si
0098 mov ax, word ptr [bp - 4]
009b add ax, 0x2313
009e push ax
009f mov si, ax
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
00a6 add sp, 6
00a9 push 0
00ab push si
00ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
00b1 add sp, 4
00b4 push 1
00b6 push 0
00b8 push 0xb4
00bb push ds
00bc push 0x1a2
00bf nop 
00c0 push cs
00c1 call 0xffff92c0
00c4 add sp, 0xa
00c7 pop si
00c8 pop di
00c9 leave 
00ca retf 
00cb nop 
00cc mov si, word ptr [bp + 6]
00cf mov es, word ptr [0xbe7a]
00d3 mov bx, si
00d5 shl bx, 2
00d8 add bx, si
00da shl bx, 1
00dc mov word ptr [bp - 6], bx
00df cmp word ptr es:[bx - 0x7560], -1
00e5 jne 0x9a8
00e7 push 0x7e
00e9 push 0
00eb push 1
00ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 240, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00f2 add sp, 6
00f5 push 1
00f7 push 0
00f9 push 0xb4
00fc push ds
00fd push 0x1bc
0100 jmp 0x965
0102 push 0
0104 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 263, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0109 add sp, 2
010c or ax, ax
010e jne 0x9bf
0110 push ax
0111 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 276, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0116 add sp, 2
0119 push word ptr [0xbca6] ; _win_hwnd
011d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 286, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
0122 push word ptr [0xbca6] ; _win_hwnd
0126 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
012b mov es, word ptr [0xbe7e]
012f mov ax, word ptr es:[0x8610]
0133 mov word ptr [bp - 8], ax
0136 or ax, ax
0138 jne 0x9ee
013a mov es, word ptr [0xbe7a]
013e mov bx, word ptr [bp - 6]
0141 cmp word ptr es:[bx - 0x755a], ax
0146 je 0xa08
0148 cmp word ptr [bp - 8], 0
014c je 0xa1c
014e mov es, word ptr [0xbe7a]
0152 mov bx, word ptr [bp - 6]
0155 cmp word ptr es:[bx - 0x755a], 0
015b jne 0xa1c
015d nop 
015e push cs
015f call 0xffff9918
0162 mov es, word ptr [0xbe7a]
0166 mov bx, word ptr [bp - 6]
0169 push word ptr es:[bx - 0x7558]
016e nop 
016f push cs
0170 call 0xffff9f94
0173 jmp 0xa47
0175 nop 
0176 cmp word ptr [bp - 8], 0
017a jne 0xa36
017c mov es, word ptr [0xbe7a]
0180 mov bx, word ptr [bp - 6]
0183 cmp word ptr es:[bx - 0x755a], 0
0189 je 0xa36
018b nop 
018c push cs
018d call 0xffff972a
0190 mov es, word ptr [0xbe7a]
0194 mov bx, word ptr [bp - 6]
0197 push word ptr es:[bx - 0x755a]
019c nop 
019d push cs
019e call 0xffff9e82
01a1 add sp, 2
01a4 mov ax, word ptr [0xcd7a] ; _editHeight
01a7 cdq 
01a8 sub ax, dx
01aa sar ax, 1
01ac mov es, word ptr [0xbe7a]
01b0 mov bx, word ptr [bp - 6]
01b3 add ax, word ptr es:[bx - 0x755c]
01b8 push ax
01b9 mov ax, word ptr [0xcc80] ; _editWidth
01bc cdq 
01bd sub ax, dx
01bf sar ax, 1
01c1 add ax, word ptr es:[bx - 0x755e]
01c6 push ax
01c7 push word ptr es:[bx - 0x7560]
01cc nop 
01cd push cs
01ce call 0xffffa52a
01d1 add sp, 6
01d4 push 0
01d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 473, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01db add sp, 2
01de or ax, ax
01e0 jne 0xa91
01e2 push ax
01e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 486, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
01e8 add sp, 2
01eb push word ptr [0xbca6] ; _win_hwnd
01ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 496, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
01f4 push word ptr [0xbca6] ; _win_hwnd
01f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 505, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
01fd pop si
01fe pop di
01ff leave 
0200 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near YardMode;` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenMapWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp, unsigned int bitmapDown);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_UpdateUserButtons-609b2b7960.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetUserButton', 'offset': 874, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 345}
- {'symbol': '_DoUserButton', 'offset': 1220, 'source': None, 'size': 994}
- {'symbol': '_ClearBookmarks', 'offset': 2728, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 125}
- {'symbol': '_DrawRibbonMessage', 'offset': 2854, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 156}

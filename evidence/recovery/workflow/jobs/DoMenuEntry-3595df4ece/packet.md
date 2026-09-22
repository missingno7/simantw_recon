# Recovery task _DoMenuEntry

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 503 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 cmp word ptr [0x10], 0 ; _bHelp
000b je 0x1898
000d mov word ptr [0x10], 0 ; _bHelp
0013 push word ptr [bp + 6]
0016 nop 
0017 push cs
0018 call 0x4fa6 ; _ProcMenuHelp
001b add sp, 2
001e pop si
001f pop di
0020 leave 
0021 retf 
0022 mov ax, word ptr [bp + 6]
0025 mov word ptr [bp - 4], ax
0028 lea ax, [bp - 0x10]
002b push ss
002c push ax
002d nop 
002e push cs
002f call 0x4fc2 ; _ProcMenu
0032 add sp, 4
0035 cmp word ptr [0x38], 0 ; _fileWaitFlag
003a jne 0x18b5
003c jmp 0x1a69
003f mov ax, word ptr [0x38] ; _fileWaitFlag
0042 sub ax, 4
0045 je 0x18d4
0047 dec ax
0048 jne 0x18c3
004a jmp 0x1a12
004d dec ax
004e jne 0x18c9
0050 jmp 0x1a22
0053 dec ax
0054 dec ax
0055 jne 0x18d0
0057 jmp 0x1a3a
005a jmp 0x1a63
005d nop 
005e push word ptr [0xcd78] ; _rootWnd
0062 push 0
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 12}}]
0069 push 0
006b push 0
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _LoadGame
0072 add sp, 4
0075 or ax, ax
0077 jne 0x18f2
0079 jmp 0x19f0
007c push word ptr [0xce80] ; _MePlane
0080 nop 
0081 push cs
0082 call 0xffffa5ca
0085 add sp, 2
0088 cmp word ptr [0xce80], 0 ; _MePlane
008d jne 0x1914
008f push word ptr [0xce82] ; _YardMode
0093 nop 
0094 push cs
0095 call 0xffff9f94
0098 add sp, 2
009b jmp 0x1928
009d nop 
009e push 0x100
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00a6 add sp, 2
00a9 or ax, ax
00ab jne 0x1928
00ad nop 
00ae push cs
00af call 0x972a ; _YardToMap
00b2 push word ptr [0xce7e] ; _MeLocY
00b6 push word ptr [0xcd88] ; _MeLocX
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
00bf add sp, 4
00c2 or ax, ax
00c4 je 0x1976
00c6 push 0x100
00c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00ce add sp, 2
00d1 or ax, ax
00d3 je 0x1966
00d5 push word ptr [0xbca8]
00d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 220, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00de add sp, 2
00e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 228, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapCursor
00eb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 238, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00f0 mov es, word ptr [0xbe8a]
00f4 mov word ptr es:[0x144e], 1
00fb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 254, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0100 xor di, di
0102 mov si, 0x8aa0
0105 mov es, word ptr [0xbe7a]
0109 mov word ptr es:[si], 0xffff
010e xor ax, ax
0110 mov word ptr es:[si + 2], ax
0114 xor cx, cx
0116 mov word ptr es:[si + 4], ax
011a mov word ptr es:[si + 6], cx
011e mov word ptr es:[si + 8], ax
0122 lea dx, [di + 0x3867]
0126 push dx
0127 lea bx, [di + 0x3899]
012b push bx
012c lea ax, [di + 0x2218]
0130 push ax
0131 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 308, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
0136 add sp, 6
0139 push 0
013b lea ax, [di + 0x2218]
013f push ax
0140 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 323, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0145 add sp, 4
0148 lea ax, [di + 0x3867]
014c push ax
014d lea ax, [di + 0x3899]
0151 push ax
0152 lea ax, [di + 0x2313]
0156 push ax
0157 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 346, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
015c add sp, 6
015f push 0
0161 lea ax, [di + 0x2313]
0165 push ax
0166 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 361, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
016b add sp, 4
016e inc di
016f add si, 0xa
0172 cmp si, 0x8ae6
0176 jb 0x197b
0178 jmp 0x1a4e
017a mov es, word ptr [0xbe8c]
017e cmp word ptr es:[0x80b4], -1
0184 jne 0x1a4e
0186 push 0
0188 nop 
0189 push cs
018a call 0xffffd6dc
018d add sp, 2
0190 or ax, ax
0192 jge 0x1a4e
0194 nop 
0195 push cs
0196 call 0x50 ; _CleanUp
0199 jmp 0x1a63
019b nop 
019c push word ptr [0xcd78] ; _rootWnd
01a0 push 0
01a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 419, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 12}}]
01a7 push 1
01a9 jmp 0x1a2f
01ab nop 
01ac push word ptr [0xcd78] ; _rootWnd
01b0 push 0
01b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 435, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 12}}]
01b7 push 0
01b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 444, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _SaveGame
01be add sp, 2
01c1 jmp 0x1a4e
01c3 nop 
01c4 push word ptr [0xcd78] ; _rootWnd
01c8 push 0
01ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 459, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 12}}]
01cf nop 
01d0 push cs
01d1 call 0xffffd628
01d4 or ax, ax
01d6 jne 0x1a0a
01d8 push word ptr [0xcd78] ; _rootWnd
01dc push 0
01de push 0x11
01e0 push word ptr [0x42]
01e4 push word ptr [0x40] ; _lpTimerFunc
01e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 489, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 10}}]
01ed mov word ptr [0x38], 0 ; _fileWaitFlag
01f3 pop si
01f4 pop di
01f5 leave 
01f6 retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near YardMode;` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far YardToMap(void);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far YardToMap(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near bHelp;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp, unsigned int bitmapDown);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_UpdateUserButtons-609b2b7960.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoMouse', 'offset': 5110, 'source': None, 'size': 1077}
- {'symbol': '_DoNextWindow', 'offset': 6188, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 74}
- {'symbol': '_AdjustWndMinMax', 'offset': 6766, 'source': None, 'size': 457}
- {'symbol': 'MYENUMFUNC', 'offset': 7224, 'source': None, 'size': 48}

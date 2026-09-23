# Recovery task _YardToMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 493 bytes.

```asm
0000 push si
0001 push 0x100
0004 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0009 add sp, 2
000c or ax, ax
000e je 0x974a
0010 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
0015 push 0x100
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
001d add sp, 2
0020 push 2
0022 push 0x100
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupUnselected
002a add sp, 4
002d push 0x100
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0035 add sp, 2
0038 or ax, ax
003a je 0x976b
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
0041 cmp word ptr [0xbca8], 0
0046 je 0x9775
0048 jmp 0x986c
004b cmp word ptr [0xbcd8], 0
0050 jne 0x977f
0052 jmp 0x986c
0055 mov ax, 1
0058 mov es, word ptr [0xc0d4]
005c mov word ptr es:[0x19a6], ax
0060 push ax
0061 nop 
0062 push cs
0063 call 0xa5ca ; _SetMapPlane
0066 add sp, 2
0069 push 0x100
006c push 0x1900
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Swap
0074 add sp, 4
0077 mov es, word ptr [0xc0d6]
007b mov bx, word ptr es:[0x8610]
0080 shl bx, 2
0083 mov es, word ptr [0xc0d8]
0087 les si, ptr es:[0x9be6]
008c push word ptr es:[bx + si + 2]
0090 push word ptr es:[bx + si]
0093 push 0x101
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
009b add sp, 6
009e mov bx, word ptr [0xce82] ; _YardMode
00a2 shl bx, 2
00a5 mov es, word ptr [0xc0d8]
00a9 les si, ptr es:[0x9be6]
00ae push word ptr es:[bx + si + 0x26]
00b2 push word ptr es:[bx + si + 0x24]
00b6 push 0x1901
00b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 188, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
00be add sp, 6
00c1 push 0x100
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00c9 add sp, 2
00cc or ax, ax
00ce je 0x9810
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
00d5 push 0x100
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 219, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
00dd add sp, 2
00e0 push 0x101
00e3 jmp 0x9832
00e5 nop 
00e6 push 0x1900
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00ee add sp, 2
00f1 or ax, ax
00f3 je 0x983f
00f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 248, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
00fa push 0x1900
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0102 add sp, 2
0105 push 0x1901
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawTitle
010d add sp, 2
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
0115 push 0x2300
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
011d add sp, 2
0120 or ax, ax
0122 je 0x9865
0124 push 0x2200
0127 push 0x2300
012a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 301, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Swap
012f add sp, 4
0132 push word ptr [0xbcea]
0136 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
013b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 318, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
0140 pop si
0141 retf 
0142 push 0x100
0145 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 328, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
014a add sp, 2
014d mov es, word ptr [0xc0d6]
0151 mov bx, word ptr es:[0x8610]
0156 shl bx, 2
0159 mov es, word ptr [0xc0d8]
015d les si, ptr es:[0x9be6]
0162 push word ptr es:[bx + si + 2]
0166 push word ptr es:[bx + si]
0169 push 0x101
016c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 367, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0171 add sp, 6
0174 mov bx, word ptr [0xce82] ; _YardMode
0178 shl bx, 2
017b mov es, word ptr [0xc0d8]
017f les si, ptr es:[0x9be6]
0184 push word ptr es:[bx + si + 0x26]
0188 push word ptr es:[bx + si + 0x24]
018c push 0x1901
018f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 402, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0194 add sp, 6
0197 push 0x100
019a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 413, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
019f add sp, 2
01a2 or ax, ax
01a4 je 0x98e6
01a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 425, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
01ab push 0x100
01ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 433, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
01b3 add sp, 2
01b6 push 0x101
01b9 jmp 0x9908
01bb nop 
01bc push 0x1900
01bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 450, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01c4 add sp, 2
01c7 or ax, ax
01c9 je 0x9915
01cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 462, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
01d0 push 0x1900
01d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 470, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
01d8 add sp, 2
01db push 0x1901
01de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 481, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawTitle
01e3 add sp, 2
01e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 489, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
01eb pop si
01ec retf 
```

## Known declaration examples

- `extern void far DrawMap(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int near YardMode;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far win_DrawTitle(int object);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far win_MakeGroupUnselected(int window, int group);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far win_MakeGroupUnselected(int id1, int id2);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far win_MakeGroupUnselected(int id1, int id2);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int flags);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far win_SetObjFormatStr(int object, char far *text);` — src/recovered/wf_SetMapTitle-b3c9718398.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ABS', 'offset': 38676, 'source': 'src/recovered/ABS.c', 'size': 20}
- {'symbol': '_ErrorLog', 'offset': 38696, 'source': 'src/recovered/ErrorLog.c', 'size': 1}
- {'symbol': '_MapToYard', 'offset': 39192, 'source': None, 'size': 529}
- {'symbol': '_OpenMapYard', 'offset': 39722, 'source': 'src/recovered/wf_OpenMapYard-118a20a584.c', 'size': 54}

# Recovery task _MapToYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 529 bytes.

```asm
0000 push si
0001 cmp word ptr [0xbcd8], 0
0006 je 0x9923
0008 jmp 0x9a7e
000b cmp word ptr [0xbca8], 0
0010 jne 0x992d
0012 jmp 0x9a7e
0015 push 0
0017 nop 
0018 push cs
0019 call 0xa5ca ; _SetMapPlane
001c add sp, 2
001f push 0x1900
0022 push 0x100
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Swap
002a add sp, 4
002d mov es, word ptr [0xc0d6]
0031 mov bx, word ptr es:[0x8610]
0036 shl bx, 2
0039 mov es, word ptr [0xc0d8]
003d les si, ptr es:[0x9be6]
0042 push word ptr es:[bx + si + 2]
0046 push word ptr es:[bx + si]
0049 push 0x101
004c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0051 add sp, 6
0054 mov bx, word ptr [0xce82] ; _YardMode
0058 shl bx, 2
005b mov es, word ptr [0xc0d8]
005f les si, ptr es:[0x9be6]
0064 push word ptr es:[bx + si + 0x26]
0068 push word ptr es:[bx + si + 0x24]
006c push 0x1901
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0074 add sp, 6
0077 push 0x100
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
007f add sp, 2
0082 or ax, ax
0084 je 0x99b4
0086 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 137, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
008b push 0x100
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0093 add sp, 2
0096 push 0x101
0099 jmp 0x99d6
009b nop 
009c push 0x1900
009f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 162, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00a4 add sp, 2
00a7 or ax, ax
00a9 je 0x99e3
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
00b0 push 0x1900
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
00b8 add sp, 2
00bb push 0x1901
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 193, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawTitle
00c3 add sp, 2
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
00cb push 0x2200
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00d3 add sp, 2
00d6 or ax, ax
00d8 jne 0x99f5
00da jmp 0x9a76
00dd push 0x2300
00e0 push 0x2200
00e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 230, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Swap
00e8 add sp, 4
00eb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 238, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
00f0 cmp word ptr [0xbcec], 0
00f5 je 0x9a32
00f7 mov es, word ptr [0xc0d2]
00fb cmp word ptr es:[0x836e], 1
0101 sbb bx, bx
0103 neg bx
0105 shl bx, 1
0107 push word ptr [bx + 0x1502]
010b push 3
010d push 0x2300
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetGroupSelectedObj
0115 add sp, 6
0118 jmp 0x9a68
011a push 0x1900
011d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 288, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0122 add sp, 2
0125 or ax, ax
0127 je 0x9a4c
0129 push 0x1900
012c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 303, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0131 add sp, 2
0134 mov es, word ptr [0xc0d2]
0138 cmp word ptr es:[0x836e], 1
013e sbb bx, bx
0140 neg bx
0142 shl bx, 1
0144 push word ptr [bx + 0x1506]
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
014d add sp, 2
0150 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 339, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
0155 push word ptr [0xbcec]
0159 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 346, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawYard
0163 pop si
0164 retf 
0165 nop 
0166 push 0x1900
0169 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 364, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
016e add sp, 2
0171 mov es, word ptr [0xc0d6]
0175 mov bx, word ptr es:[0x8610]
017a shl bx, 2
017d mov es, word ptr [0xc0d8]
0181 les si, ptr es:[0x9be6]
0186 push word ptr es:[bx + si + 2]
018a push word ptr es:[bx + si]
018d push 0x101
0190 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0195 add sp, 6
0198 mov bx, word ptr [0xce82] ; _YardMode
019c shl bx, 2
019f mov es, word ptr [0xc0d8]
01a3 les si, ptr es:[0x9be6]
01a8 push word ptr es:[bx + si + 0x26]
01ac push word ptr es:[bx + si + 0x24]
01b0 push 0x1901
01b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 438, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
01b8 add sp, 6
01bb push 0x100
01be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 449, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01c3 add sp, 2
01c6 or ax, ax
01c8 je 0x9af8
01ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 461, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
01cf push 0x100
01d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
01d7 add sp, 2
01da push 0x101
01dd jmp 0x9b1a
01df nop 
01e0 push 0x1900
01e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 486, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01e8 add sp, 2
01eb or ax, ax
01ed je 0x9b27
01ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 498, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
01f4 push 0x1900
01f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 506, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
01fc add sp, 2
01ff push 0x1901
0202 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 517, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawTitle
0207 add sp, 2
020a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 525, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
020f pop si
0210 retf 
```

## Known declaration examples

- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far win_DrawTitle(int object);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far win_DrawTitle(int object);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_MakeObjSelected(int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far win_MakeObjSelected(int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_SetGroupSelectedObj(int group, int selected, int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far win_SetGroupSelectedObj(int group, int selected, int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far win_SetObjFormatStr(int object, char far *text);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far win_SetObjFormatStr(int object, char far *text);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far win_Swap(int first, int second);` — src/recovered/wf_YardToMap-2e5b0deea5.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ErrorLog', 'offset': 38696, 'source': 'src/recovered/ErrorLog.c', 'size': 1}
- {'symbol': '_YardToMap', 'offset': 38698, 'source': 'src/recovered/wf_YardToMap-2e5b0deea5.c', 'size': 493}
- {'symbol': '_OpenMapYard', 'offset': 39722, 'source': 'src/recovered/wf_OpenMapYard-118a20a584.c', 'size': 54}
- {'symbol': '_UpdateEverything', 'offset': 39776, 'source': 'src/recovered/UpdateEverything.c', 'size': 11}

# Recovery task _MapToolsMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 600 bytes.

```asm
0000 enter 0x10, 0
0004 push si
0005 lea ax, [bp - 0xc]
0008 push ss
0009 push ax
000a push 0x117
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0012 add sp, 6
0015 mov bx, 0x80b4
0018 mov es, word ptr [0xc218]
001c mov word ptr [bp - 0x10], bx
001f mov word ptr [bp - 0xe], es
0022 mov ax, word ptr es:[bx]
0025 dec ax
0026 je 0xdc56
0028 dec ax
0029 jne 0xdc4c
002b jmp 0xdcfa
002e dec ax
002f jne 0xdc52
0031 jmp 0xdd34
0034 pop si
0035 leave 
0036 retf 
0037 nop 
0038 lea ax, [bp - 4]
003b push ss
003c push ax
003d push 0xa00
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjSize
0045 add sp, 6
0048 mov ax, word ptr [bp - 0xa]
004b sub ax, word ptr [bp - 2]
004e sub ax, 4
0051 push ax
0052 mov ax, word ptr [bp - 8]
0055 sub ax, word ptr [bp - 4]
0058 add ax, word ptr [bp - 0xc]
005b cdq 
005c sub ax, dx
005e sar ax, 1
0060 push ax
0061 push -1
0063 push 0xa00
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
006b add sp, 8
006e or ax, ax
0070 jge 0xdc93
0072 jmp 0xde73
0075 mov es, word ptr [0xc21a]
0079 push word ptr es:[0x79e2]
007e nop 
007f push cs
0080 call 0x6e0c ; _SetExpTool
0083 add sp, 2
0086 les bx, ptr [bp - 0x10]
0089 mov word ptr es:[bx], 3
008e push word ptr [0xcf50] ; _MeDir
0092 push word ptr [0xcc84] ; _MeType
0096 push word ptr [0xce7e] ; _MeLocY
009a push word ptr [0xcd88] ; _MeLocX
009e push word ptr [0xce80] ; _MePlane
00a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
00a7 add sp, 0xa
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitYelloAnt
00af mov es, word ptr [0xc21c]
00b3 mov word ptr es:[0x9fe8], 2
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InitSpider
00bf push 0
00c1 push 0
00c3 nop 
00c4 push cs
00c5 call 0x11b06
00c8 add sp, 4
00cb push 0x7e
00cd push 0
00cf push 2
00d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 212, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00d6 add sp, 6
00d9 pop si
00da leave 
00db retf 
00dc lea ax, [bp - 4]
00df push ss
00e0 push ax
00e1 push 0xb00
00e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjSize
00e9 add sp, 6
00ec mov ax, word ptr [bp - 0xa]
00ef sub ax, word ptr [bp - 2]
00f2 sub ax, 4
00f5 push ax
00f6 mov ax, word ptr [bp - 8]
00f9 sub ax, word ptr [bp - 4]
00fc add ax, word ptr [bp - 0xc]
00ff cdq 
0100 sub ax, dx
0102 sar ax, 1
0104 push ax
0105 push -1
0107 push 0xb00
010a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 269, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
010f add sp, 8
0112 pop si
0113 leave 
0114 retf 
0115 nop 
0116 lea ax, [bp - 4]
0119 push ss
011a push ax
011b push 0x900
011e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 289, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjSize
0123 add sp, 6
0126 mov ax, word ptr [bp - 0xa]
0129 sub ax, word ptr [bp - 2]
012c sub ax, 4
012f push ax
0130 mov ax, word ptr [bp - 8]
0133 sub ax, word ptr [bp - 4]
0136 add ax, word ptr [bp - 0xc]
0139 cdq 
013a sub ax, dx
013c sar ax, 1
013e push ax
013f nop 
0140 push cs
0141 call 0x6ee2 ; _DoExpMenu
0144 add sp, 4
0147 mov si, ax
0149 cmp si, -1
014c jne 0xdd6f
014e jmp 0xde73
0151 cmp si, 7
0154 jne 0xddc0
0156 les bx, ptr [bp - 0x10]
0159 mov word ptr es:[bx], 1
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitYelloAnt
0163 cmp word ptr [0xcc76], 1 ; _MapPlane
0168 jne 0xdda7
016a push 0xff
016d push word ptr [0xcf50] ; _MeDir
0171 push word ptr [0xcc84] ; _MeType
0175 push word ptr [0xce7e] ; _MeLocY
0179 push word ptr [0xcd88] ; _MeLocX
017d push word ptr [0xce80] ; _MePlane
0181 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 388, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0186 add sp, 0xc
0189 push 0
018b push 0
018d nop 
018e push cs
018f call 0x11b06
0192 add sp, 4
0195 push 0x7e
0197 push 0x2afb
019a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 413, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
019f add sp, 4
01a2 push si
01a3 nop 
01a4 push cs
01a5 call 0x6e0c ; _SetExpTool
01a8 add sp, 2
01ab push 0x100
01ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 433, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01b3 add sp, 2
01b6 or ax, ax
01b8 je 0xde20
01ba nop 
01bb push cs
01bc call 0x8e50 ; _clip_Push
01bf push 0x100
01c2 nop 
01c3 push cs
01c4 call 0x8e44 ; _clip_SetWin
01c7 add sp, 2
01ca push word ptr [0xbca8]
01ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 465, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
01d3 add sp, 2
01d6 push 0x117
01d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 476, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
01de add sp, 2
01e1 mov es, word ptr [0xc21a]
01e5 mov ax, word ptr es:[0x79e2]
01e9 add ax, 0x13ec
01ec push ax
01ed push 0x117
01f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 499, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMapAtObjNum
01f5 add sp, 4
01f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 507, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01fd nop 
01fe push cs
01ff call 0x8e4e ; _clip_Pop
0202 push 0
0204 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 519, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0209 add sp, 2
020c or ax, ax
020e je 0xde73
0210 nop 
0211 push cs
0212 call 0x8e50 ; _clip_Push
0215 push 0
0217 nop 
0218 push cs
0219 call 0x8e44 ; _clip_SetWin
021c add sp, 2
021f push word ptr [0xbca6] ; _win_hwnd
0223 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 550, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0228 add sp, 2
022b push 7
022d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 560, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
0232 add sp, 2
0235 mov es, word ptr [0xc21a]
0239 mov ax, word ptr es:[0x79e2]
023d add ax, 0x13ec
0240 push ax
0241 push 7
0243 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 582, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMapAtObjNum
0248 add sp, 4
024b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 590, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0250 nop 
0251 push cs
0252 call 0x8e4e ; _clip_Pop
0255 pop si
0256 leave 
0257 retf 
```

## Known declaration examples

- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far InitSpider(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far InitYelloAnt(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near MeDir;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far win_DoProxMenu(int menu, int layer, int x, int y);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MapToYellowAnt', 'offset': 54282, 'source': None, 'size': 105}
- {'symbol': '_Mini_DrawMapI', 'offset': 54388, 'source': None, 'size': 811}
- {'symbol': '_RibbonToolsMenu', 'offset': 56950, 'source': None, 'size': 649}
- {'symbol': '_MapAreaEvent', 'offset': 57600, 'source': None, 'size': 514}

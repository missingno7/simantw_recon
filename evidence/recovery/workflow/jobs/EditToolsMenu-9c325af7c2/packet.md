# Recovery task _EditToolsMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 506 bytes.

```asm
0000 enter 0x10, 0
0004 push si
0005 cmp byte ptr [0xcc7e], 0xa ; _displayType
000a je 0x67e2
000c cmp byte ptr [0xcc7e], 9 ; _displayType
0011 je 0x67e2
0013 lea ax, [bp - 8]
0016 push ss
0017 push ax
0018 push 7
001a jmp 0x67ea
001c lea ax, [bp - 8]
001f push ss
0020 push ax
0021 push 0x220a
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0029 add sp, 6
002c mov bx, 0x80b4
002f mov es, word ptr [0xc238]
0033 mov word ptr [bp - 0xc], bx
0036 mov word ptr [bp - 0xa], es
0039 mov ax, word ptr es:[bx]
003c dec ax
003d je 0x6812
003f dec ax
0040 je 0x6886
0042 dec ax
0043 jne 0x680e
0045 jmp 0x68a0
0048 pop si
0049 leave 
004a retf 
004b nop 
004c push word ptr [bp - 6]
004f mov ax, word ptr [bp - 4]
0052 add ax, 2
0055 push ax
0056 push -1
0058 push 0xa00
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
0060 add sp, 8
0063 or ax, ax
0065 jge 0x6830
0067 jmp 0x69bd
006a les bx, ptr [bp - 0xc]
006d mov word ptr es:[bx], 3
0072 push word ptr [0xcf50] ; _MeDir
0076 push word ptr [0xcc84] ; _MeType
007a push word ptr [0xce7e] ; _MeLocY
007e push word ptr [0xcd88] ; _MeLocX
0082 push word ptr [0xce80] ; _MePlane
0086 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 137, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
008b add sp, 0xa
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitYelloAnt
0093 mov es, word ptr [0xc23a]
0097 mov word ptr es:[0x9fe8], 2
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InitSpider
00a3 push 0
00a5 push 0
00a7 nop 
00a8 push cs
00a9 call 0x1b06 ; _SetEditWinTitle
00ac add sp, 4
00af push 0x7e
00b1 push 0
00b3 push 2
00b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00ba add sp, 6
00bd pop si
00be leave 
00bf retf 
00c0 push word ptr [bp - 6]
00c3 mov ax, word ptr [bp - 4]
00c6 add ax, 2
00c9 push ax
00ca push -1
00cc push 0xb00
00cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
00d4 add sp, 8
00d7 pop si
00d8 leave 
00d9 retf 
00da push 7
00dc push word ptr [bp - 6]
00df mov ax, word ptr [bp - 4]
00e2 add ax, 2
00e5 push ax
00e6 nop 
00e7 push cs
00e8 call 0x6ee2 ; _DoExpMenu
00eb add sp, 4
00ee mov si, ax
00f0 push si
00f1 push ds
00f2 push 0x1b8e
00f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 248, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
00fa add sp, 8
00fd mov ax, si
00ff inc ax
0100 jne 0x68cb
0102 jmp 0x69bd
0105 cmp si, 7
0108 jne 0x691c
010a les bx, ptr [bp - 0xc]
010d mov word ptr es:[bx], 1
0112 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 277, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitYelloAnt
0117 cmp word ptr [0xcc76], 1 ; _MapPlane
011c jne 0x6903
011e push 0xff
0121 push word ptr [0xcf50] ; _MeDir
0125 push word ptr [0xcc84] ; _MeType
0129 push word ptr [0xce7e] ; _MeLocY
012d push word ptr [0xcd88] ; _MeLocX
0131 push word ptr [0xce80] ; _MePlane
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 312, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
013a add sp, 0xc
013d push 0
013f push 0
0141 nop 
0142 push cs
0143 call 0x1b06 ; _SetEditWinTitle
0146 add sp, 4
0149 push 0x7e
014b push 0x2afb
014e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0153 add sp, 4
0156 mov bx, 0x79e2
0159 mov es, word ptr [0xc23c]
015d mov word ptr [bp - 0x10], bx
0160 mov word ptr [bp - 0xe], es
0163 mov word ptr es:[bx], si
0166 push 0
0168 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 363, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
016d add sp, 2
0170 or ax, ax
0172 je 0x6973
0174 nop 
0175 push cs
0176 call 0x8e50 ; _clip_Push
0179 push 0
017b nop 
017c push cs
017d call 0x8e44 ; _clip_SetWin
0180 add sp, 2
0183 push word ptr [0xbca6] ; _win_hwnd
0187 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 394, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
018c add sp, 2
018f les bx, ptr [bp - 0x10]
0192 mov ax, word ptr es:[bx]
0195 add ax, 0x13ec
0198 push ax
0199 push 7
019b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 414, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMapAtObjNum
01a0 add sp, 4
01a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 422, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01a8 nop 
01a9 push cs
01aa call 0x8e4e ; _clip_Pop
01ad push 0x100
01b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 435, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01b5 add sp, 2
01b8 or ax, ax
01ba je 0x69bd
01bc nop 
01bd push cs
01be call 0x8e50 ; _clip_Push
01c1 push 0x100
01c4 nop 
01c5 push cs
01c6 call 0x8e44 ; _clip_SetWin
01c9 add sp, 2
01cc push word ptr [0xbca8]
01d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 467, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
01d5 add sp, 2
01d8 les bx, ptr [bp - 0x10]
01db mov ax, word ptr es:[bx]
01de add ax, 0x13ec
01e1 push ax
01e2 push 0x117
01e5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 488, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMapAtObjNum
01ea add sp, 4
01ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 496, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01f2 nop 
01f3 push cs
01f4 call 0x8e4e ; _clip_Pop
01f7 pop si
01f8 leave 
01f9 retf 
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
- `extern void far SetEditWinTitle(char far *title);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
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
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ResetEditScrollRange', 'offset': 24710, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 230}
- {'symbol': '_EditScentMenu', 'offset': 26462, 'source': 'src/recovered/wf_EditScentMenu-abd185cb06.c', 'size': 103}
- {'symbol': '_win_DrawExamineWindow', 'offset': 27072, 'source': None, 'size': 395}
- {'symbol': '_MagnifyMenu', 'offset': 27468, 'source': 'src/recovered/wf_MagnifyMenu-51f69a1a04.c', 'size': 471}

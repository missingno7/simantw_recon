# Recovery task _RibbonToolsMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 649 bytes.

```asm
0000 enter 0x12, 0
0004 push si
0005 cmp byte ptr [0xcc7e], 0xa ; _displayType
000a je 0xde92
000c cmp byte ptr [0xcc7e], 9 ; _displayType
0011 je 0xde92
0013 lea ax, [bp - 0xc]
0016 push ss
0017 push ax
0018 push 7
001a jmp 0xde9a
001c lea ax, [bp - 0xc]
001f push ss
0020 push ax
0021 push 0x220a
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0029 add sp, 6
002c mov bx, 0x80b4
002f mov es, word ptr [0xc218]
0033 mov word ptr [bp - 0x10], bx
0036 mov word ptr [bp - 0xe], es
0039 mov ax, word ptr es:[bx]
003c dec ax
003d je 0xdec4
003f dec ax
0040 jne 0xdebb
0042 jmp 0xdf60
0045 dec ax
0046 jne 0xdec1
0048 jmp 0xdf92
004b pop si
004c leave 
004d retf 
004e lea ax, [bp - 4]
0051 push ss
0052 push ax
0053 push 0xa00
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjSize
005b add sp, 6
005e push 0
0060 mov ax, word ptr [bp - 8]
0063 sub ax, word ptr [bp - 4]
0066 add ax, word ptr [bp - 0xc]
0069 cdq 
006a sub ax, dx
006c sar ax, 1
006e push ax
006f push -2
0071 push 0xa00
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
0079 add sp, 8
007c or ax, ax
007e jge 0xdef9
0080 jmp 0xe0fc
0083 mov es, word ptr [0xc21a]
0087 push word ptr es:[0x79e2]
008c nop 
008d push cs
008e call 0x6e0c ; _SetExpTool
0091 add sp, 2
0094 les bx, ptr [bp - 0x10]
0097 mov word ptr es:[bx], 3
009c push word ptr [0xcf50] ; _MeDir
00a0 push word ptr [0xcc84] ; _MeType
00a4 push word ptr [0xce7e] ; _MeLocY
00a8 push word ptr [0xcd88] ; _MeLocX
00ac push word ptr [0xce80] ; _MePlane
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
00b5 add sp, 0xa
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitYelloAnt
00bd mov es, word ptr [0xc21c]
00c1 mov word ptr es:[0x9fe8], 2
00c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 203, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InitSpider
00cd push 0
00cf push 0
00d1 nop 
00d2 push cs
00d3 call 0x11b06
00d6 add sp, 4
00d9 push 0x7e
00db push 0
00dd push 2
00df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 226, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00e4 add sp, 6
00e7 pop si
00e8 leave 
00e9 retf 
00ea lea ax, [bp - 4]
00ed push ss
00ee push ax
00ef push 0xb00
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjSize
00f7 add sp, 6
00fa push 0
00fc mov ax, word ptr [bp - 8]
00ff sub ax, word ptr [bp - 4]
0102 add ax, word ptr [bp - 0xc]
0105 cdq 
0106 sub ax, dx
0108 sar ax, 1
010a push ax
010b push -2
010d push 0xb00
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
0115 add sp, 8
0118 pop si
0119 leave 
011a retf 
011b nop 
011c lea ax, [bp - 4]
011f push ss
0120 push ax
0121 push 0x900
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjSize
0129 add sp, 6
012c push 0
012e mov ax, word ptr [bp - 8]
0131 sub ax, word ptr [bp - 4]
0134 add ax, word ptr [bp - 0xc]
0137 cdq 
0138 sub ax, dx
013a sar ax, 1
013c push ax
013d nop 
013e push cs
013f call 0x6ee2 ; _DoExpMenu
0142 add sp, 4
0145 mov si, ax
0147 cmp si, -1
014a jne 0xdfc5
014c jmp 0xe0fc
014f cmp si, 7
0152 jne 0xe016
0154 les bx, ptr [bp - 0x10]
0157 mov word ptr es:[bx], 1
015c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitYelloAnt
0161 cmp word ptr [0xcc76], 1 ; _MapPlane
0166 jne 0xdffd
0168 push 0xff
016b push word ptr [0xcf50] ; _MeDir
016f push word ptr [0xcc84] ; _MeType
0173 push word ptr [0xce7e] ; _MeLocY
0177 push word ptr [0xcd88] ; _MeLocX
017b push word ptr [0xce80] ; _MePlane
017f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 386, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0184 add sp, 0xc
0187 push 0
0189 push 0
018b nop 
018c push cs
018d call 0x11b06
0190 add sp, 4
0193 push 0x7e
0195 push 0x2afb
0198 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 411, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
019d add sp, 4
01a0 push si
01a1 nop 
01a2 push cs
01a3 call 0x6e0c ; _SetExpTool
01a6 add sp, 2
01a9 push 0
01ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 430, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01b0 add sp, 2
01b3 or ax, ax
01b5 je 0xe068
01b7 nop 
01b8 push cs
01b9 call 0x8e50 ; _clip_Push
01bc push 0
01be nop 
01bf push cs
01c0 call 0x8e44 ; _clip_SetWin
01c3 add sp, 2
01c6 push word ptr [0xbca6] ; _win_hwnd
01ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 461, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
01cf add sp, 2
01d2 mov es, word ptr [0xc21a]
01d6 mov ax, word ptr es:[0x79e2]
01da add ax, 0x13ec
01dd push ax
01de push 7
01e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 483, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMapAtObjNum
01e5 add sp, 4
01e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 491, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01ed nop 
01ee push cs
01ef call 0x8e4e ; _clip_Pop
01f2 push 0x100
01f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 504, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01fa add sp, 2
01fd or ax, ax
01ff je 0xe0b4
0201 nop 
0202 push cs
0203 call 0x8e50 ; _clip_Push
0206 push 0x100
0209 nop 
020a push cs
020b call 0x8e44 ; _clip_SetWin
020e add sp, 2
0211 push word ptr [0xbca8]
0215 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 536, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
021a add sp, 2
021d mov es, word ptr [0xc21a]
0221 mov ax, word ptr es:[0x79e2]
0225 add ax, 0x13ec
0228 push ax
0229 push 0x117
022c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 559, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMapAtObjNum
0231 add sp, 4
0234 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 567, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0239 nop 
023a push cs
023b call 0x8e4e ; _clip_Pop
023e mov ax, word ptr [0xcf24]
0241 or ax, word ptr [0xcf22]
0245 je 0xe0fc
0247 mov es, word ptr [0xc21a]
024b mov ax, word ptr es:[0x79e2]
024f mov word ptr [bp - 0x12], ax
0252 cmp ax, 7
0255 jne 0xe0d6
0257 push 0x3856
025a push 0x3888
025d jmp 0xe0e4
025f nop 
0260 mov ax, word ptr [bp - 0x12]
0263 add ax, 0x38a4
0266 push ax
0267 mov ax, word ptr [bp - 0x12]
026a add ax, 0x38d6
026d push ax
026e push 0x220a
0271 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 628, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
0276 add sp, 6
0279 push 0
027b push 0x220a
027e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 641, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0283 add sp, 4
0286 pop si
0287 leave 
0288 retf 
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
- `extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp, unsigned int bitmapDown);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_UpdateUserButtons-609b2b7960.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Mini_DrawMapI', 'offset': 54388, 'source': None, 'size': 811}
- {'symbol': '_MapToolsMenu', 'offset': 56350, 'source': None, 'size': 600}
- {'symbol': '_MapAreaEvent', 'offset': 57600, 'source': None, 'size': 514}
- {'symbol': '_Mini_MakeTable', 'offset': 58114, 'source': 'src/recovered/wf_Mini_MakeTable-a03e1a6138.c', 'size': 114}

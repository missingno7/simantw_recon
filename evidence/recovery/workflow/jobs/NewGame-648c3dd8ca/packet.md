# Recovery task _NewGame

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 691 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc156]
000a mov di, word ptr es:[0x9c28]
000f mov es, word ptr [0xc158]
0013 mov word ptr es:[0x8370], 0
001a push 1
001c nop 
001d push cs
001e call 0x14e34
0021 add sp, 2
0024 push word ptr [bp + 6]
0027 nop 
0028 push cs
0029 call 0x5998 ; _DoScenario
002c add sp, 2
002f mov si, ax
0031 push di
0032 nop 
0033 push cs
0034 call 0x14e34
0037 add sp, 2
003a push 1
003c push -1
003e push -2
0040 push 0
0042 push 0
0044 nop 
0045 push cs
0046 call 0x92c0 ; _EditMessage
0049 add sp, 0xa
004c cmp si, 0x205
0050 je 0xd74a
0052 cmp si, 0x207
0056 jne 0xd752
0058 push 0
005a push 0
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _LoadGame
0061 add sp, 4
0064 or ax, ax
0066 je 0xd6f6
0068 mov si, 1
006b jmp 0xd866
006e mov ax, 0xffff
0071 pop si
0072 pop di
0073 leave 
0074 retf 
0075 nop 
0076 mov ax, si
0078 sub ax, 0x202
007b je 0xd766
007d dec ax
007e je 0xd76c
0080 dec ax
0081 je 0xd772
0083 dec ax
0084 dec ax
0085 je 0xd778
0087 jmp 0xd77a
0089 nop 
008a mov si, 1
008d jmp 0xd77a
008f nop 
0090 mov si, 2
0093 jmp 0xd77a
0095 nop 
0096 mov si, 3
0099 jmp 0xd77a
009b nop 
009c xor si, si
009e or si, si
00a0 jge 0xd781
00a2 jmp 0xd866
00a5 cmp si, 4
00a8 jl 0xd789
00aa jmp 0xd866
00ad mov bx, 0x80b4
00b0 mov es, word ptr [0xc15a]
00b4 mov word ptr [bp - 6], bx
00b7 mov word ptr [bp - 4], es
00ba mov word ptr es:[bx], si
00bd mov es, word ptr [0xc15c]
00c1 mov ax, word ptr es:[0x7c22]
00c5 mov word ptr [bp - 8], ax
00c8 cmp ax, 0xa
00cb jne 0xd7b0
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndLifeTransferMode
00d2 jmp 0xd7bb
00d4 cmp word ptr [bp - 8], 0xb
00d8 jne 0xd7bb
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndTargetMode
00df mov ax, word ptr [0xcf24]
00e2 or ax, word ptr [0xcf22]
00e6 je 0xd7fe
00e8 les bx, ptr [bp - 6]
00eb cmp word ptr es:[bx], 3
00ef jne 0xd7e0
00f1 mov es, word ptr [0xc15e]
00f5 mov word ptr es:[0x79e2], 0
00fc push 0x38a4
00ff push 0x38d6
0102 jmp 0xd7e6
0104 push 0x3856
0107 push 0x3888
010a push 0x220a
010d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 272, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
0112 add sp, 6
0115 push 0
0117 push 0x220a
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 285, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
011f add sp, 4
0122 push 1
0124 nop 
0125 push cs
0126 call 0x60cc ; _SetDefaultWindPrompt
0129 add sp, 2
012c push 0
012e push 0
0130 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 307, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _SetEditWinTitle
0135 add sp, 4
0138 mov word ptr [0xac8c], 0 ; _QueenStorageB
013e mov ax, 1
0141 mov es, word ptr [0xc160]
0145 mov word ptr es:[0x9c70], ax
0149 mov es, word ptr [0xc162]
014d mov word ptr es:[0x836e], ax
0151 nop 
0152 push cs
0153 call 0x94a4 ; _UpdateLayQueenModeDisplay
0156 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 345, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RandYard
015b les bx, ptr [bp - 6]
015e cmp word ptr es:[bx], 0
0162 jne 0xd866
0164 mov es, word ptr [0xc164]
0168 mov word ptr es:[0x85ee], 1
016f mov es, word ptr [0xc166]
0173 mov word ptr es:[0x85f0], 0
017a cmp word ptr [bp + 6], 0
017e jne 0xd866
0180 push 0
0182 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 389, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0187 add sp, 2
018a nop 
018b push cs
018c call 0xbbec ; _OpenCasteWindow
018f push word ptr [0xbccc]
0193 push 0
0195 push 0
0197 push 0
0199 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
019e nop 
019f push cs
01a0 call 0xbc7a ; _OpenModeWindow
01a3 push word ptr [0xbcca]
01a7 push 0
01a9 push 0
01ab push 0
01ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 430, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
01b2 push word ptr [0xcc76] ; _MapPlane
01b6 nop 
01b7 push cs
01b8 call 0xa5ca ; _SetMapPlane
01bb add sp, 2
01be cmp word ptr [0xcc76], 0 ; _MapPlane
01c3 je 0xd8b8
01c5 push 0x100
01c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 459, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01cd add sp, 2
01d0 or ax, ax
01d2 jne 0xd8cc
01d4 nop 
01d5 push cs
01d6 call 0x972a ; _YardToMap
01d9 jmp 0xd8cc
01db nop 
01dc push 0x1900
01df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 482, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01e4 add sp, 2
01e7 or ax, ax
01e9 jne 0xd8cc
01eb nop 
01ec push cs
01ed call 0x9918 ; _MapToYard
01f0 nop 
01f1 push cs
01f2 call 0x953c ; _SetMapTitle
01f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 504, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _OpenEditWindow
01fa push word ptr [0xce80] ; _MePlane
01fe nop 
01ff push cs
0200 call 0xa5ca ; _SetMapPlane
0203 add sp, 2
0206 cmp word ptr [0xce80], 0 ; _MePlane
020b jne 0xd8f8
020d push word ptr [0xce82] ; _YardMode
0211 nop 
0212 push cs
0213 call 0x9f94 ; _SetYardMode
0216 add sp, 2
0219 jmp 0xd90c
021b nop 
021c push 0x100
021f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 546, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0224 add sp, 2
0227 or ax, ax
0229 jne 0xd90c
022b nop 
022c push cs
022d call 0x972a ; _YardToMap
0230 or si, si
0232 jne 0xd926
0234 push si
0235 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 568, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinZoomed
023a add sp, 2
023d or ax, ax
023f jne 0xd926
0241 push ax
0242 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 581, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Zoom
0247 add sp, 2
024a push word ptr [0xce7e] ; _MeLocY
024e push word ptr [0xcd88] ; _MeLocX
0252 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 597, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
0257 add sp, 4
025a or ax, ax
025c je 0xd964
025e push 0x100
0261 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 612, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0266 add sp, 2
0269 or ax, ax
026b je 0xd964
026d push word ptr [0xbca8]
0271 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 628, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0276 add sp, 2
0279 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 636, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
027e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 641, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapCursor
0283 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 646, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0288 mov es, word ptr [0xc168]
028c mov word ptr es:[0x144e], 1
0293 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 662, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0298 nop 
0299 push cs
029a call 0x10aa8
029d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 672, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ClearLastFileName
02a2 mov es, word ptr [0xc158]
02a6 mov word ptr es:[0x8370], 0
02ad mov ax, si
02af pop si
02b0 pop di
02b1 leave 
02b2 retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_tu_simant_9D04_SetMapPlane_1_scaffold-47a07d4d6a.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far EndTargetMode(void);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far MapToYard(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far OpenCasteWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far OpenEditWindow(void);` — src/recovered/DoTab.c
- `extern void far OpenEditWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far OpenModeWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern void far RandYard(void);` — src/recovered/wf_DoPreLoadInits-ed37124107.c
- `extern void far RandYard(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SetEditWinTitle(char far *title);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far SetMapTitle(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapTitle(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetMapTitle(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far YardToMap(void);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far YardToMap(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
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

- {'symbol': '_MenuQuit', 'offset': 54824, 'source': None, 'size': 66}
- {'symbol': '_SetDefaultWindows', 'offset': 54890, 'source': 'src/recovered/wf_SetDefaultWindows-770f6186c6.c', 'size': 113}

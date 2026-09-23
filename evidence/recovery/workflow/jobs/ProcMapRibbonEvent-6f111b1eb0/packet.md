# Recovery task _ProcMapRibbonEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 626 bytes.

```asm
0000 enter 0x10, 0
0004 push si
0005 mov si, word ptr [bp + 6]
0008 mov es, word ptr [bp + 8]
000b mov ax, word ptr es:[si + 0xc]
000f sub ax, 0x2202
0012 cmp ax, 0x25
0015 jbe 0xc3ee
0017 jmp 0xc643
001a shl ax, 1
001c xchg bx, ax
001d jmp word ptr cs:[bx - 0x3c0a]
0022 dw offset 0xc442
0024 dw offset 0xc498
0026 dw offset 0xc4aa
0028 dw offset 0xc4b4
002a dw offset 0xc4be
002c dw offset 0xc502
002e dw offset 0xc50a
0030 dw offset 0xc520
0032 dw offset 0xc528
0034 dw offset 0xc530
0036 dw offset 0xc54c
0038 dw offset 0xc576
003a dw offset 0xc590
003c dw offset 0xc5ac
003e dw offset 0xc5c8
0040 dw offset 0xc5c8
0042 dw offset 0xc5c8
0044 dw offset 0xc5c8
0046 dw offset 0xc5c8
0048 dw offset 0xc5c8
004a dw offset 0xc5c8
004c dw offset 0xc5c8
004e dw offset 0xc5dc
0050 dw offset 0xc5dc
0052 dw offset 0xc5dc
0054 dw offset 0xc5dc
0056 dw offset 0xc5dc
0058 dw offset 0xc5dc
005a dw offset 0xc5dc
005c dw offset 0xc643
005e dw offset 0xc643
0060 dw offset 0xc643
0062 dw offset 0xc643
0064 dw offset 0xc643
0066 dw offset 0xc643
0068 dw offset 0xc643
006a dw offset 0xc643
006c dw offset 0xc5ec
006e push 0x100
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0076 add sp, 2
0079 or ax, ax
007b jne 0xc46b
007d push 0x1900
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0085 add sp, 2
0088 or ax, ax
008a jne 0xc46b
008c push 0x100
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0094 add sp, 2
0097 push 0x1900
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
009f add sp, 2
00a2 or ax, ax
00a4 je 0xc486
00a6 push word ptr [0xbcd8]
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 171, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
00af jmp 0xc643
00b2 push word ptr [0xbca8]
00b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MapToYard
00c0 jmp 0xc643
00c3 nop 
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearMapScentButtons
00c9 push 2
00cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapPlane
00d0 add sp, 2
00d3 jmp 0xc643
00d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearMapScentButtons
00db push 3
00dd jmp 0xc49f
00df nop 
00e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearMapScentButtons
00e5 push 1
00e7 jmp 0xc49f
00e9 nop 
00ea lea ax, [bp - 8]
00ed push ss
00ee push ax
00ef push word ptr es:[si + 0xc]
00f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
00f8 add sp, 6
00fb lea ax, [bp - 0x10]
00fe push ss
00ff push ax
0100 push 0x1400
0103 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 262, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0108 add sp, 6
010b push 0
010d mov ax, word ptr [bp - 4]
0110 sub ax, word ptr [bp - 8]
0113 sar ax, 1
0115 mov cx, word ptr [bp - 0xc]
0118 sub cx, word ptr [bp - 0x10]
011b sar cx, 1
011d sub ax, cx
011f add ax, word ptr [bp - 8]
0122 push ax
0123 nop 
0124 push cs
0125 call 0xe374 ; _OpenMiniMapWin
0128 add sp, 4
012b jmp 0xc643
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoSpider
0133 pop si
0134 leave 
0135 retf 
0136 mov es, word ptr [0xc1ec]
013a mov word ptr es:[0x9fb0], 1
0141 push 0x2208
0144 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoWinHelp
0149 jmp 0xc4a4
014b nop 
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScoreDialog
0151 pop si
0152 leave 
0153 retf 
0154 nop 
0155 push cs
0156 call 0xde76 ; _RibbonToolsMenu
0159 pop si
015a leave 
015b retf 
015c push 4
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapModeAnt
0163 add sp, 2
0166 mov es, word ptr [0xc1ee]
016a cmp word ptr es:[0x8610], 4
0170 jne 0xc568
0172 mov ax, 1
0175 jmp 0xc56b
0177 nop 
0178 push 5
017a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 381, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapModeAnt
017f add sp, 2
0182 mov es, word ptr [0xc1ee]
0186 cmp word ptr es:[0x8610], 5
018c jne 0xc568
018e mov ax, 2
0191 jmp 0xc56b
0193 nop 
0194 mov ax, 0xffff
0197 mov word ptr [0xac58], ax ; _ELayerMode
019a nop 
019b push cs
019c call 0x10e50
019f pop si
01a0 leave 
01a1 retf 
01a2 push 8
01a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapModeAnt
01a9 add sp, 2
01ac mov es, word ptr [0xc1ee]
01b0 cmp word ptr es:[0x8610], 8
01b6 jne 0xc568
01b8 xor ax, ax
01ba jmp 0xc56b
01bc push 6
01be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 449, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapModeAnt
01c3 add sp, 2
01c6 mov es, word ptr [0xc1ee]
01ca cmp word ptr es:[0x8610], 6
01d0 jne 0xc568
01d2 mov ax, 3
01d5 jmp 0xc56b
01d7 nop 
01d8 push 7
01da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 477, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapModeAnt
01df add sp, 2
01e2 mov es, word ptr [0xc1ee]
01e6 cmp word ptr es:[0x8610], 7
01ec jne 0xc568
01ee mov ax, 4
01f1 jmp 0xc56b
01f3 nop 
01f4 mov ax, word ptr es:[si + 0xc]
01f8 mov cx, ax
01fa sub ax, 0x2210
01fd push ax
01fe push cx
01ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 514, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoUserButton
0204 jmp 0xc4fc
0207 nop 
0208 mov ax, word ptr es:[si + 0xc]
020c sub ax, 0x2218
020f push ax
0210 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 531, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoBookMark
0215 jmp 0xc4a4
0218 push 0x2222
021b mov ax, si
021d mov dx, es
021f add ax, 8
0222 push dx
0223 push ax
0224 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 551, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsPointInObj
0229 add sp, 6
022c or ax, ax
022e je 0xc616
0230 push 0x231f
0233 push word ptr [bp + 8]
0236 push si
0237 nop 
0238 push cs
0239 call 0x6e72 ; _DoHealthSetY
023c add sp, 6
023f pop si
0240 leave 
0241 retf 
0242 push 0x2223
0245 mov ax, si
0247 mov dx, word ptr [bp + 8]
024a add ax, 8
024d push dx
024e push ax
024f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 594, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsPointInObj
0254 add sp, 6
0257 or ax, ax
0259 je 0xc63e
025b push 0x2320
025e mov ax, word ptr [bp + 8]
0261 push ax
0262 push si
0263 nop 
0264 push cs
0265 call 0x6e1c ; _DoWarnSetB
0268 jmp 0xc610
026a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 621, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DrawCastePopUp
026f pop si
0270 leave 
0271 retf 
```

## Known declaration examples

- `extern void far DoHealthSetY(struct EditEvent far *event, int mode);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far DoWarnSetB(struct EditEvent far *event, int mode);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far DoWinHelp(int mode);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near ELayerMode;` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int near ELayerMode;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near ELayerMode;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far GotoSpider(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far MapToYard(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapModeAnt(int mode);` — src/recovered/wf_tu_simant_9D04_SetMapPlane_1_scaffold-47a07d4d6a.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitMapFunctions', 'offset': 49564, 'source': 'src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c', 'size': 133}
- {'symbol': '_ProcMapEvent', 'offset': 49698, 'source': None, 'size': 434}
- {'symbol': '_OpenMapWindow', 'offset': 50758, 'source': 'src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c', 'size': 12}
- {'symbol': '_DrawMapCursor', 'offset': 50770, 'source': None, 'size': 185}

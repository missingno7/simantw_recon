# Recovery task _DrawEditGraphs

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 379 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 cmp byte ptr [0xcc7e], 0xa ; _displayType
000b jne 0x199a
000d jmp 0x1b01
0010 cmp byte ptr [0xcc7e], 9 ; _displayType
0015 jne 0x19a4
0017 jmp 0x1b01
001a mov word ptr [bp - 0xa], 0x8e00
001f mov si, 0x8dfa
0022 push 0
0024 push 0x64
0026 mov es, word ptr [0xbf96]
002a mov bx, word ptr [bp - 0xa]
002d les bx, ptr es:[bx]
0030 push word ptr es:[bx]
0033 push 0
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
003a mov word ptr [bp - 8], ax
003d mov word ptr [bp - 6], dx
0040 mov es, word ptr [0xbf98]
0044 mov di, word ptr es:[si]
0047 push di
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
004d add sp, 2
0050 lea ax, [bp - 0x14]
0053 push ss
0054 push ax
0055 push di
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
005b add sp, 6
005e mov ax, word ptr [bp - 0x12]
0061 mov word ptr [bp - 2], ax
0064 push 1
0066 push 0
0068 push word ptr [bp - 6]
006b push word ptr [bp - 8]
006e sub ax, word ptr [bp - 0xe]
0071 neg ax
0073 mov word ptr [bp - 4], ax
0076 cdq 
0077 push dx
0078 push ax
0079 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
007e push dx
007f push ax
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0085 sub ax, word ptr [bp - 0xe]
0088 neg ax
008a mov word ptr [bp - 0x12], ax
008d cmp ax, word ptr [bp - 0xe]
0090 jge 0x1a60
0092 push word ptr [0xcf4e] ; __foreColor
0096 lea ax, [bp - 0x14]
0099 push ss
009a push ax
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
00a0 add sp, 6
00a3 test byte ptr [0xcc7e], 1 ; _displayType
00a8 je 0x1a60
00aa cmp si, 0x8dfa
00ae jne 0x1a60
00b0 push 0
00b2 push 0
00b4 push 0
00b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
00bb add sp, 6
00be push 1
00c0 lea ax, [bp - 0x14]
00c3 push ss
00c4 push ax
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectOutline
00ca add sp, 6
00cd push di
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
00d3 add sp, 2
00d6 mov ax, word ptr [bp - 0x12]
00d9 cmp word ptr [bp - 2], ax
00dc jge 0x1a82
00de mov word ptr [bp - 0xe], ax
00e1 mov ax, word ptr [bp - 2]
00e4 mov word ptr [bp - 0x12], ax
00e7 push word ptr [0xce8a] ; __backColor
00eb lea ax, [bp - 0x14]
00ee push ss
00ef push ax
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
00f5 add sp, 6
00f8 cmp si, 0x8dfa
00fc jne 0x1abf
00fe mov ax, 0x64
0101 mov es, word ptr [0xbf9a]
0105 sub ax, word ptr es:[0x9bec]
010a imul word ptr [bp - 4]
010d mov cx, 0x64
0110 cdq 
0111 idiv cx
0113 add ax, word ptr [bp - 2]
0116 mov word ptr [bp - 0x12], ax
0119 inc ax
011a mov word ptr [bp - 0xe], ax
011d push 0xf
011f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 290, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0124 add sp, 2
0127 push ax
0128 lea ax, [bp - 0x14]
012b push ss
012c push ax
012d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
0132 add sp, 6
0135 cmp si, 0x8dfc
0139 jne 0x1af1
013b mov ax, 0x64
013e mov es, word ptr [0xbf9c]
0142 sub ax, word ptr es:[0x769c]
0147 imul word ptr [bp - 4]
014a mov cx, 0x64
014d cdq 
014e idiv cx
0150 add ax, word ptr [bp - 2]
0153 mov word ptr [bp - 0x12], ax
0156 inc ax
0157 mov word ptr [bp - 0xe], ax
015a lea ax, [bp - 0x14]
015d push ss
015e push ax
015f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 354, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
0164 add sp, 4
0167 add word ptr [bp - 0xa], 4
016b add si, 2
016e cmp si, 0x8e00
0172 jae 0x1b01
0174 jmp 0x19ac
0177 pop si
0178 pop di
0179 leave 
017a retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far GRectFill(struct BitmapObject far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern void far GRectFill(void far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far GRectInv(struct WinRect far *rect);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far GRectOutline(int first, int second, int third);` — src/recovered/win_RectOutline.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GRectFillOutline-24e4a6aa35.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_BoundEditPosition', 'offset': 5556, 'source': None, 'size': 107}
- {'symbol': '_CenterEdit', 'offset': 5664, 'source': None, 'size': 180}
- {'symbol': '_SetEditWinTitle', 'offset': 6918, 'source': None, 'size': 232}
- {'symbol': '_InvalidUpdateEdit', 'offset': 7150, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 41}

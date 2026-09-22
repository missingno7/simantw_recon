# Recovery task _HistUpdate

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 317 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov ax, word ptr [0xac82] ; _BpopT
0009 mov es, word ptr [0xc0a4]
000d mov bx, word ptr es:[0x9e6e]
0012 shl bx, 1
0014 mov es, word ptr [0xc098]
0018 mov word ptr es:[bx + 0x72fa], ax
001d mov es, word ptr [0xc096]
0021 mov ax, word ptr [0xac84] ; _RpopT
0024 mov word ptr es:[bx + 0x7608], ax
0029 mov es, word ptr [0xc0be]
002d mov ax, word ptr es:[0x9ea4]
0031 mov es, word ptr [0xc094]
0035 mov word ptr es:[bx + 0x7c98], ax
003a mov es, word ptr [0xc0c0]
003e mov ax, word ptr es:[0x72de]
0042 mov es, word ptr [0xc092]
0046 mov word ptr es:[bx + 0x7d76], ax
004b mov es, word ptr [0xc090]
004f mov ax, word ptr [0xac86] ; _HealthB
0052 mov word ptr es:[bx - 0x60d0], ax
0057 mov es, word ptr [0xc08e]
005b mov ax, word ptr [0xac88] ; _HealthR
005e mov word ptr es:[bx - 0x6010], ax
0063 mov es, word ptr [0xc0c2]
0067 mov ax, word ptr es:[0x9e84]
006b mov es, word ptr [0xc08c]
006f mov word ptr es:[bx + 0x7382], ax
0074 mov es, word ptr [0xc0aa]
0078 mov ax, word ptr es:[0x9b26]
007c mov es, word ptr [0xc08a]
0080 mov word ptr es:[bx - 0x630e], ax
0085 mov es, word ptr [0xc0a8]
0089 mov ax, word ptr es:[0x76a0]
008d mov es, word ptr [0xc088]
0091 mov word ptr es:[bx - 0x6154], ax
0096 mov es, word ptr [0xc0ac]
009a mov ax, word ptr es:[0x99e0]
009e mov es, word ptr [0xc086]
00a2 mov word ptr es:[bx - 0x6216], ax
00a7 mov es, word ptr [0xc0a6]
00ab cmp word ptr es:[0x8670], 0x3f
00b1 jge 0x923a
00b3 inc word ptr es:[0x8670]
00b8 mov es, word ptr [0xc0a4]
00bc mov al, byte ptr es:[0x9e6e]
00c0 inc al
00c2 and ax, 0x3f
00c5 mov word ptr es:[0x9e6e], ax
00c9 push 0x1500
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00d1 add sp, 2
00d4 or ax, ax
00d6 je 0x92bb
00d8 push 0x1500
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
00e0 add sp, 2
00e3 push word ptr [0xbcd0]
00e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00ec add sp, 2
00ef push 0
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00f6 add sp, 2
00f9 push ax
00fa push 0x150e
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
0102 add sp, 4
0105 xor di, di
0107 mov si, 0x8e54
010a mov es, word ptr [0xc084]
010e mov ax, word ptr es:[si]
0111 mov word ptr [bp - 2], ax
0114 cmp ax, 0x8000
0117 je 0x92a7
0119 push di
011a push 0
011c push ax
011d nop 
011e push cs
011f call 0x8e78 ; _drawHistGraph
0122 add sp, 6
0125 inc di
0126 add si, 2
0129 cmp si, 0x8e5c
012d jb 0x928c
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
0139 pop si
013a pop di
013b leave 
013c retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near BpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern int near HealthB;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near HealthR;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int near RpopT;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c
- `extern int near RpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawHistoryWindow', 'offset': 36392, 'source': None, 'size': 80}
- {'symbol': '_drawHistGraph', 'offset': 36472, 'source': None, 'size': 777}
- {'symbol': '_EditMessage', 'offset': 37568, 'source': None, 'size': 351}
- {'symbol': '_win_YardClosed', 'offset': 37920, 'source': 'src/recovered/wf_win_YardClosed-13af30aa32.c', 'size': 131}

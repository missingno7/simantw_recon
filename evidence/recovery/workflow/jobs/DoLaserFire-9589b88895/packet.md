# Recovery task _DoLaserFire

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 719 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 push 0x3f
0008 push 0x8265
000b push 0x37
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0012 add sp, 6
0015 cmp word ptr [0xcc76], 1 ; _MapPlane
001a je 0x6ee7
001c jmp 0x7193
001f cmp byte ptr [0xcc7e], 2 ; _displayType
0024 jne 0x6f42
0026 mov ax, word ptr [bp + 0xa]
0029 mov cx, ax
002b shl ax, 1
002d add ax, cx
002f cdq 
0030 and dx, 3
0033 add ax, dx
0035 sar ax, 2
0038 mov word ptr [bp + 0xa], ax
003b mov ax, word ptr [bp + 0xc]
003e mov cx, ax
0040 shl ax, 1
0042 add ax, cx
0044 cdq 
0045 and dx, 3
0048 add ax, dx
004a sar ax, 2
004d mov word ptr [bp + 0xc], ax
0050 mov ax, word ptr [bp + 6]
0053 mov cx, ax
0055 shl ax, 1
0057 add ax, cx
0059 cdq 
005a and dx, 3
005d add ax, dx
005f sar ax, 2
0062 mov word ptr [bp + 6], ax
0065 mov ax, word ptr [bp + 8]
0068 mov cx, ax
006a shl ax, 1
006c add ax, cx
006e cdq 
006f and dx, 3
0072 add ax, dx
0074 sar ax, 2
0077 mov word ptr [bp + 8], ax
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
007f push 0
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0086 add sp, 2
0089 or ax, ax
008b jne 0x6f58
008d jmp 0x7054
0090 push word ptr [0xbca6] ; _win_hwnd
0094 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 151, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0099 add sp, 2
009c mov es, word ptr [0xbf08]
00a0 mov ax, word ptr es:[0x7d2e]
00a4 imul word ptr [0x143a] ; _tileWidth
00a8 mov es, word ptr [0xbf06]
00ac sub ax, word ptr es:[0x9b08]
00b1 neg ax
00b3 mov cx, ax
00b5 add ax, word ptr [bp + 6]
00b8 mov word ptr [bp - 2], ax
00bb mov es, word ptr [0xbf08]
00bf mov ax, word ptr es:[0x7d30]
00c3 imul word ptr [0x143c] ; _tileHeight
00c7 mov es, word ptr [0xbf06]
00cb sub ax, word ptr es:[0x9b0a]
00d0 neg ax
00d2 mov dx, ax
00d4 add ax, word ptr [bp + 8]
00d7 mov word ptr [bp - 4], ax
00da mov si, cx
00dc add si, word ptr [bp + 0xa]
00df mov di, dx
00e1 add di, word ptr [bp + 0xc]
00e4 push 3
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00eb add sp, 2
00ee push ax
00ef push di
00f0 push si
00f1 push word ptr [bp - 4]
00f4 push word ptr [bp - 2]
00f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 250, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GLine
00fc add sp, 0xa
00ff push 3
0101 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 260, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0106 add sp, 2
0109 push ax
010a lea ax, [di + 1]
010d push ax
010e lea ax, [si + 1]
0111 push ax
0112 mov ax, word ptr [bp - 4]
0115 inc ax
0116 push ax
0117 mov ax, word ptr [bp - 2]
011a inc ax
011b push ax
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GLine
0121 add sp, 0xa
0124 push 2
0126 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 297, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
012b add sp, 2
012e push ax
012f lea ax, [di + 2]
0132 push ax
0133 lea ax, [si + 2]
0136 push ax
0137 push di
0138 push si
0139 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 316, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
013e add sp, 0xa
0141 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 324, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0146 mov ax, si
0148 cmp si, word ptr [bp - 2]
014b jle 0x7018
014d mov si, word ptr [bp - 2]
0150 mov word ptr [bp - 0xc], si
0153 mov cx, di
0155 cmp di, word ptr [bp - 4]
0158 jle 0x7025
015a mov di, word ptr [bp - 4]
015d mov word ptr [bp - 0xa], di
0160 cmp ax, word ptr [bp - 2]
0163 jge 0x7030
0165 mov ax, word ptr [bp - 2]
0168 add ax, 2
016b mov word ptr [bp - 8], ax
016e cmp cx, word ptr [bp - 4]
0171 jge 0x703e
0173 mov cx, word ptr [bp - 4]
0176 add cx, 2
0179 mov word ptr [bp - 6], cx
017c push word ptr [0xbca6] ; _win_hwnd
0180 lea ax, [bp - 0xc]
0183 push ss
0184 push ax
0185 push 0
0187 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 392, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
018c push 0x100
018f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 402, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0194 add sp, 2
0197 or ax, ax
0199 jne 0x7066
019b jmp 0x718e
019e push word ptr [0xbca8]
01a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
01a7 add sp, 2
01aa mov ax, word ptr [bp + 0xa]
01ad cdq 
01ae idiv word ptr [0x143a] ; _tileWidth
01b2 mov es, word ptr [0xbf24]
01b6 imul word ptr es:[0x807c]
01bb mov si, ax
01bd mov es, word ptr [0xbf26]
01c1 add si, word ptr es:[0x8110]
01c6 mov ax, word ptr [bp + 0xc]
01c9 cdq 
01ca idiv word ptr [0x143c] ; _tileHeight
01ce mov es, word ptr [0xbf28]
01d2 imul word ptr es:[0x8096]
01d7 mov di, ax
01d9 mov es, word ptr [0xbf26]
01dd add di, word ptr es:[0x8112]
01e2 mov ax, word ptr [bp + 6]
01e5 cdq 
01e6 idiv word ptr [0x143a] ; _tileWidth
01ea mov es, word ptr [0xbf24]
01ee imul word ptr es:[0x807c]
01f3 mov es, word ptr [0xbf26]
01f7 add ax, word ptr es:[0x8110]
01fc mov word ptr [bp - 2], ax
01ff mov ax, word ptr [bp + 8]
0202 cdq 
0203 idiv word ptr [0x143c] ; _tileHeight
0207 mov es, word ptr [0xbf28]
020b imul word ptr es:[0x8096]
0210 mov es, word ptr [0xbf26]
0214 add ax, word ptr es:[0x8112]
0219 mov word ptr [bp - 4], ax
021c push 3
021e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 545, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0223 add sp, 2
0226 push ax
0227 push di
0228 push si
0229 push word ptr [bp - 4]
022c push word ptr [bp - 2]
022f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 562, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GLine
0234 add sp, 0xa
0237 push 3
0239 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 572, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
023e add sp, 2
0241 push ax
0242 lea ax, [di + 1]
0245 push ax
0246 lea ax, [si + 1]
0249 push ax
024a mov ax, word ptr [bp - 4]
024d inc ax
024e push ax
024f mov ax, word ptr [bp - 2]
0252 inc ax
0253 push ax
0254 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 599, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GLine
0259 add sp, 0xa
025c push 1
025e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0263 add sp, 2
0266 or al, 0x20
0268 push ax
0269 lea ax, [di + 2]
026c push ax
026d lea ax, [si + 2]
0270 push ax
0271 push di
0272 push si
0273 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 630, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
0278 add sp, 0xa
027b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 638, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0280 mov ax, si
0282 cmp si, word ptr [bp - 2]
0285 jle 0x7152
0287 mov si, word ptr [bp - 2]
028a mov word ptr [bp - 0x14], si
028d mov cx, di
028f cmp di, word ptr [bp - 4]
0292 jle 0x715f
0294 mov di, word ptr [bp - 4]
0297 mov word ptr [bp - 0x12], di
029a cmp ax, word ptr [bp - 2]
029d jge 0x716a
029f mov ax, word ptr [bp - 2]
02a2 add ax, 2
02a5 mov word ptr [bp - 0x10], ax
02a8 cmp cx, word ptr [bp - 4]
02ab jge 0x7178
02ad mov cx, word ptr [bp - 4]
02b0 add cx, 2
02b3 mov word ptr [bp - 0xe], cx
02b6 push word ptr [0xbca8]
02ba lea ax, [bp - 0x14]
02bd push ss
02be push ax
02bf push 0
02c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 706, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
02c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 713, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
02cb pop si
02cc pop di
02cd leave 
02ce retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near tileHeight;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
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

- {'symbol': '_CustomerIDDialog', 'offset': 26964, 'source': None, 'size': 227}
- {'symbol': '_processEdit', 'offset': 27192, 'source': None, 'size': 1168}
- {'symbol': '_processSpider', 'offset': 29080, 'source': 'src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c', 'size': 290}
- {'symbol': '_ResetYellowVars', 'offset': 29370, 'source': 'src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c', 'size': 122}

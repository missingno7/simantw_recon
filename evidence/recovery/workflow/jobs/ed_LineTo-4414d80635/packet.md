# Recovery task _ed_LineTo

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 665 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov ax, word ptr [0x1452] ; _theEditBufPtr
0009 mov dx, word ptr [0x1454]
000d mov di, ax
000f mov word ptr [bp - 2], dx
0012 test byte ptr [0xcc7e], 1 ; _displayType
0017 je 0x2316
0019 jmp 0x2452
001c mov si, word ptr [bp + 6]
001f mov ax, word ptr [0xcad2]
0022 sub ax, word ptr [bp + 8]
0025 cdq 
0026 xor ax, dx
0028 sub ax, dx
002a mov bx, 0x8df0
002d mov es, word ptr [0xbf8a]
0031 mov word ptr [bp - 8], bx
0034 mov word ptr [bp - 6], es
0037 mov cx, ax
0039 mov ax, word ptr es:[bx]
003c sub ax, si
003e cdq 
003f xor ax, dx
0041 sub ax, dx
0043 cmp ax, cx
0045 jg 0x2344
0047 jmp 0x23c6
004a mov ax, word ptr [0x143a] ; _tileWidth
004d imul word ptr [0xcc80] ; _editWidth
0051 mov cx, ax
0053 shl ax, 2
0056 add ax, 0x1f
0059 cdq 
005a and dx, 0x1f
005d add ax, dx
005f sar ax, 5
0062 shl ax, 2
0065 push ax
0066 push cx
0067 mov ax, word ptr [0x143c] ; _tileHeight
006a imul word ptr [0xcd7a] ; _editHeight
006e push ax
006f push word ptr [bp - 2]
0072 push di
0073 push word ptr [0xcf4e] ; __foreColor
0077 push word ptr [bp + 8]
007a push si
007b push word ptr [0xcad2]
007f push word ptr es:[bx]
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _PlotLine
0087 add sp, 0x14
008a mov ax, word ptr [0x143a] ; _tileWidth
008d imul word ptr [0xcc80] ; _editWidth
0091 mov cx, ax
0093 shl ax, 2
0096 add ax, 0x1f
0099 cdq 
009a and dx, 0x1f
009d add ax, dx
009f sar ax, 5
00a2 shl ax, 2
00a5 push ax
00a6 push cx
00a7 mov ax, word ptr [0x143c] ; _tileHeight
00aa imul word ptr [0xcd7a] ; _editHeight
00ae push ax
00af push word ptr [bp - 2]
00b2 push di
00b3 push word ptr [0xcf4e] ; __foreColor
00b7 mov ax, word ptr [bp + 8]
00ba inc ax
00bb push ax
00bc push si
00bd mov ax, word ptr [0xcad2]
00c0 inc ax
00c1 push ax
00c2 les bx, ptr [bp - 8]
00c5 push word ptr es:[bx]
00c8 jmp 0x2449
00cb nop 
00cc mov ax, word ptr [0x143a] ; _tileWidth
00cf imul word ptr [0xcc80] ; _editWidth
00d3 mov cx, ax
00d5 shl ax, 2
00d8 add ax, 0x1f
00db cdq 
00dc and dx, 0x1f
00df add ax, dx
00e1 sar ax, 5
00e4 shl ax, 2
00e7 push ax
00e8 push cx
00e9 mov ax, word ptr [0x143c] ; _tileHeight
00ec imul word ptr [0xcd7a] ; _editHeight
00f0 push ax
00f1 push word ptr [bp - 2]
00f4 push di
00f5 push word ptr [0xcf4e] ; __foreColor
00f9 push word ptr [bp + 8]
00fc push si
00fd push word ptr [0xcad2]
0101 les bx, ptr [bp - 8]
0104 push word ptr es:[bx]
0107 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 266, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _PlotLine
010c add sp, 0x14
010f mov ax, word ptr [0x143a] ; _tileWidth
0112 imul word ptr [0xcc80] ; _editWidth
0116 mov cx, ax
0118 shl ax, 2
011b add ax, 0x1f
011e cdq 
011f and dx, 0x1f
0122 add ax, dx
0124 sar ax, 5
0127 shl ax, 2
012a push ax
012b push cx
012c mov ax, word ptr [0x143c] ; _tileHeight
012f imul word ptr [0xcd7a] ; _editHeight
0133 push ax
0134 push word ptr [bp - 2]
0137 push di
0138 push word ptr [0xcf4e] ; __foreColor
013c push word ptr [bp + 8]
013f lea ax, [si + 1]
0142 push ax
0143 push word ptr [0xcad2]
0147 les bx, ptr [bp - 8]
014a mov ax, word ptr es:[bx]
014d inc ax
014e push ax
014f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 338, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _PlotLine
0154 jmp 0x2580
0157 nop 
0158 mov si, word ptr [bp + 6]
015b mov ax, word ptr [0xcad2]
015e sub ax, word ptr [bp + 8]
0161 cdq 
0162 xor ax, dx
0164 sub ax, dx
0166 mov bx, 0x8df0
0169 mov es, word ptr [0xbf8a]
016d mov word ptr [bp - 8], bx
0170 mov word ptr [bp - 6], es
0173 mov cx, ax
0175 mov ax, word ptr es:[bx]
0178 sub ax, si
017a cdq 
017b xor ax, dx
017d sub ax, dx
017f cmp ax, cx
0181 jle 0x24fa
0183 mov ax, word ptr [0x143a] ; _tileWidth
0186 imul word ptr [0xcc80] ; _editWidth
018a mov cx, ax
018c add ax, 0x1f
018f cdq 
0190 and dx, 0x1f
0193 add ax, dx
0195 sar ax, 5
0198 shl ax, 2
019b push ax
019c push cx
019d mov ax, word ptr [0x143c] ; _tileHeight
01a0 imul word ptr [0xcd7a] ; _editHeight
01a4 push ax
01a5 push word ptr [bp - 2]
01a8 push di
01a9 push word ptr [0xcf4e] ; __foreColor
01ad push word ptr [bp + 8]
01b0 push si
01b1 push word ptr [0xcad2]
01b5 push word ptr es:[bx]
01b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 443, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _PlotMonoLine
01bd add sp, 0x14
01c0 mov ax, word ptr [0x143a] ; _tileWidth
01c3 imul word ptr [0xcc80] ; _editWidth
01c7 mov cx, ax
01c9 add ax, 0x1f
01cc cdq 
01cd and dx, 0x1f
01d0 add ax, dx
01d2 sar ax, 5
01d5 shl ax, 2
01d8 push ax
01d9 push cx
01da mov ax, word ptr [0x143c] ; _tileHeight
01dd imul word ptr [0xcd7a] ; _editHeight
01e1 push ax
01e2 push word ptr [bp - 2]
01e5 push di
01e6 push word ptr [0xcf4e] ; __foreColor
01ea mov ax, word ptr [bp + 8]
01ed inc ax
01ee push ax
01ef push si
01f0 mov ax, word ptr [0xcad2]
01f3 inc ax
01f4 push ax
01f5 les bx, ptr [bp - 8]
01f8 push word ptr es:[bx]
01fb jmp 0x257b
01fe nop 
01ff nop 
0200 mov ax, word ptr [0x143a] ; _tileWidth
0203 imul word ptr [0xcc80] ; _editWidth
0207 mov cx, ax
0209 add ax, 0x1f
020c cdq 
020d and dx, 0x1f
0210 add ax, dx
0212 sar ax, 5
0215 shl ax, 2
0218 push ax
0219 push cx
021a mov ax, word ptr [0x143c] ; _tileHeight
021d imul word ptr [0xcd7a] ; _editHeight
0221 push ax
0222 mov ax, word ptr [bp - 2]
0225 push ax
0226 push di
0227 push word ptr [0xcf4e] ; __foreColor
022b push word ptr [bp + 8]
022e push si
022f push word ptr [0xcad2]
0233 les bx, ptr [bp - 8]
0236 push word ptr es:[bx]
0239 mov word ptr [bp - 0xa], ax
023c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 575, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _PlotMonoLine
0241 add sp, 0x14
0244 mov ax, word ptr [0x143a] ; _tileWidth
0247 imul word ptr [0xcc80] ; _editWidth
024b mov cx, ax
024d add ax, 0x1f
0250 cdq 
0251 and dx, 0x1f
0254 add ax, dx
0256 sar ax, 5
0259 shl ax, 2
025c push ax
025d push cx
025e mov ax, word ptr [0x143c] ; _tileHeight
0261 imul word ptr [0xcd7a] ; _editHeight
0265 push ax
0266 push word ptr [bp - 0xa]
0269 push di
026a push word ptr [0xcf4e] ; __foreColor
026e push word ptr [bp + 8]
0271 lea ax, [si + 1]
0274 push ax
0275 push word ptr [0xcad2]
0279 les bx, ptr [bp - 8]
027c mov ax, word ptr es:[bx]
027f inc ax
0280 push ax
0281 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 644, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _PlotMonoLine
0286 add sp, 0x14
0289 les bx, ptr [bp - 8]
028c mov word ptr es:[bx], si
028f mov ax, word ptr [bp + 8]
0292 mov word ptr [0xcad2], ax
0295 pop si
0296 pop di
0297 leave 
0298 retf 
```

## Known declaration examples

- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileHeight;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawSpider', 'offset': 7530, 'source': None, 'size': 1402}
- {'symbol': '_ed_MoveTo', 'offset': 8932, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 22}
- {'symbol': '_DrawPalps', 'offset': 9620, 'source': None, 'size': 1611}
- {'symbol': '_DrawLegs', 'offset': 11232, 'source': None, 'size': 7368}

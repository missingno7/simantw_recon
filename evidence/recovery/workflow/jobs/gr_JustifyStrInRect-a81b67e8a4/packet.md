# Recovery task _gr_JustifyStrInRect

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 234 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 6]
0009 mov dx, word ptr [bp + 8]
000c push ds
000d lea di, [bp - 0xa]
0010 mov si, ax
0012 push ss
0013 pop es
0014 mov ds, dx
0016 movsw word ptr es:[di], word ptr [si]
0017 movsw word ptr es:[di], word ptr [si]
0018 movsw word ptr es:[di], word ptr [si]
0019 movsw word ptr es:[di], word ptr [si]
001a pop ds
001b mov ax, word ptr [bp + 0xe]
001e or ax, ax
0020 je 0xb330
0022 dec ax
0023 je 0xb350
0025 dec ax
0026 je 0xb358
0028 dec ax
0029 je 0xb330
002b mov si, word ptr [bp - 2]
002e jmp 0xb36e
0030 push word ptr [bp + 0xc]
0033 push word ptr [bp + 0xa]
0036 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_StringWidth
003b add sp, 4
003e sub ax, word ptr [bp - 6]
0041 neg ax
0043 add ax, word ptr [bp - 0xa]
0046 cdq 
0047 sub ax, dx
0049 sar ax, 1
004b mov si, ax
004d jmp 0xb36e
004f nop 
0050 mov si, word ptr [bp - 0xa]
0053 add si, 4
0056 jmp 0xb36e
0058 push word ptr [bp + 0xc]
005b push word ptr [bp + 0xa]
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_StringWidth
0063 add sp, 4
0066 mov si, word ptr [bp - 6]
0069 sub si, ax
006b sub si, 4
006e cmp word ptr [bp - 0xa], si
0071 jle 0xb376
0073 mov si, word ptr [bp - 0xa]
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
007b sub ax, word ptr [bp - 8]
007e neg ax
0080 add ax, word ptr [bp - 4]
0083 cdq 
0084 sub ax, dx
0086 sar ax, 1
0088 mov word ptr [bp - 8], ax
008b push word ptr [bp + 0xc]
008e push word ptr [bp + 0xa]
0091 push ax
0092 push si
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_PrintStr
0098 add sp, 8
009b cmp word ptr [bp + 0xe], 3
009f jne 0xb3e6
00a1 push word ptr [0xce8a] ; __backColor
00a5 mov al, byte ptr [0xce90] ; _fontHeight
00a8 cwde 
00a9 add ax, word ptr [bp - 8]
00ac push ax
00ad les bx, ptr [bp + 6]
00b0 push word ptr es:[bx + 4]
00b4 push word ptr [bp - 8]
00b7 mov es, word ptr [0xc6c4]
00bb push word ptr es:[0x7692]
00c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
00c5 add sp, 0xa
00c8 push word ptr [0xce8a] ; __backColor
00cc mov al, byte ptr [0xce90] ; _fontHeight
00cf cwde 
00d0 add ax, word ptr [bp - 8]
00d3 push ax
00d4 push si
00d5 push word ptr [bp - 8]
00d8 les bx, ptr [bp + 6]
00db push word ptr es:[bx]
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
00e3 add sp, 0xa
00e6 pop si
00e7 pop di
00e8 leave 
00e9 retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GRectFillOutline-24e4a6aa35.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern char near fontHeight;` — src/recovered/font_FontHeight.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_StringWidth(int first, int second);` — src/recovered/win_StringSize.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearBuffer', 'offset': 45295, 'source': None, 'size': 32}
- {'symbol': '_CopyMaskBitmap2', 'offset': 45328, 'source': None, 'size': 496}
- {'symbol': '_win_SetColorNum', 'offset': 46058, 'source': None, 'size': 87}
- {'symbol': '_win_SetColorFromObj', 'offset': 46146, 'source': 'src/recovered/wf_win_SetColorFromObj-7570e08dca.c', 'size': 111}

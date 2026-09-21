# Recovery task _GRectFillOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 220 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov ax, word ptr [bp + 8]
000c or ax, si
000e jne 0xfd9
0010 jmp 0x109e
0013 mov di, word ptr [bp + 0xa]
0016 push word ptr [0xce8a] ; __backColor
001a mov es, word ptr [bp + 8]
001d push word ptr es:[si + 6]
0021 push word ptr es:[si + 4]
0025 push word ptr es:[si + 2]
0029 push word ptr es:[si]
002c mov word ptr [bp - 0xc], si
002f mov word ptr [bp - 0xa], es
0032 nop 
0033 push cs
0034 call 0x19e6 ; _GBoxFill
0037 add sp, 0xa
003a les bx, ptr [bp - 0xc]
003d mov ax, word ptr es:[bx]
0040 mov word ptr [bp - 2], ax
0043 mov ax, word ptr es:[bx + 2]
0047 mov word ptr [bp - 4], ax
004a mov ax, word ptr es:[bx + 4]
004e mov word ptr [bp - 6], ax
0051 mov ax, word ptr es:[bx + 6]
0055 mov word ptr [bp - 8], ax
0058 or di, di
005a je 0x109e
005c push word ptr [0xcf4e] ; __foreColor
0060 push word ptr [bp - 4]
0063 mov ax, di
0065 sub di, word ptr [bp - 6]
0068 neg di
006a lea cx, [di - 1]
006d push cx
006e mov dx, ax
0070 add ax, word ptr [bp - 4]
0073 dec ax
0074 push ax
0075 mov ax, dx
0077 add dx, word ptr [bp - 2]
007a push dx
007b mov si, ax
007d mov word ptr [bp - 0xe], cx
0080 mov word ptr [bp - 0x10], dx
0083 nop 
0084 push cs
0085 call 0x19e6 ; _GBoxFill
0088 add sp, 0xa
008b push word ptr [0xcf4e] ; __foreColor
008f mov ax, word ptr [bp - 8]
0092 dec ax
0093 push ax
0094 push word ptr [bp - 0xe]
0097 sub si, word ptr [bp - 8]
009a neg si
009c push si
009d push word ptr [bp - 0x10]
00a0 mov si, ax
00a2 nop 
00a3 push cs
00a4 call 0x19e6 ; _GBoxFill
00a7 add sp, 0xa
00aa push word ptr [0xcf4e] ; __foreColor
00ae push si
00af push word ptr [bp - 2]
00b2 push word ptr [bp - 4]
00b5 mov ax, word ptr [bp - 0x10]
00b8 dec ax
00b9 push ax
00ba nop 
00bb push cs
00bc call 0x19e6 ; _GBoxFill
00bf add sp, 0xa
00c2 push word ptr [0xcf4e] ; __foreColor
00c6 push si
00c7 push di
00c8 push word ptr [bp - 4]
00cb mov ax, word ptr [bp - 6]
00ce dec ax
00cf push ax
00d0 nop 
00d1 push cs
00d2 call 0x19e6 ; _GBoxFill
00d5 add sp, 0xa
00d8 pop si
00d9 pop di
00da leave 
00db retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GRectOutline', 'offset': 3806, 'source': 'src/recovered/wf_GRectOutline-cbe72b492f.c', 'size': 186}
- {'symbol': '_GRectFill', 'offset': 3992, 'source': 'src/recovered/GRectFill.c', 'size': 46}
- {'symbol': '_GPutPacked', 'offset': 4258, 'source': None, 'size': 634}
- {'symbol': '_GMixedFill', 'offset': 4892, 'source': 'src/recovered/wf_GMixedFill-842c303c86.c', 'size': 130}

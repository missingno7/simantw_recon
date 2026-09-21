# Recovery task _GRectOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 186 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 les cx, ptr [bp + 6]
0009 mov ax, es
000b or ax, cx
000d jne 0xef0
000f jmp 0xf94
0012 mov si, word ptr [bp + 0xa]
0015 mov bx, cx
0017 mov di, word ptr es:[bx]
001a mov ax, word ptr es:[bx + 2]
001e mov word ptr [bp - 2], ax
0021 mov ax, word ptr es:[bx + 4]
0025 mov word ptr [bp - 4], ax
0028 mov ax, word ptr es:[bx + 6]
002c mov word ptr [bp - 6], ax
002f or si, si
0031 jne 0xf14
0033 jmp 0xf94
0036 push word ptr [0xcf4e] ; __foreColor
003a push word ptr [bp - 2]
003d mov ax, si
003f sub si, word ptr [bp - 4]
0042 neg si
0044 lea cx, [si - 1]
0047 push cx
0048 mov dx, ax
004a add ax, word ptr [bp - 2]
004d dec ax
004e push ax
004f mov ax, dx
0051 add dx, di
0053 push dx
0054 mov word ptr [bp - 8], ax
0057 mov word ptr [bp - 0xa], cx
005a mov word ptr [bp - 0xc], dx
005d nop 
005e push cs
005f call 0x19e6 ; _GBoxFill
0062 add sp, 0xa
0065 push word ptr [0xcf4e] ; __foreColor
0069 mov ax, word ptr [bp - 6]
006c dec ax
006d push ax
006e push word ptr [bp - 0xa]
0071 mov cx, word ptr [bp - 6]
0074 sub cx, word ptr [bp - 8]
0077 push cx
0078 push word ptr [bp - 0xc]
007b mov word ptr [bp - 0xe], ax
007e nop 
007f push cs
0080 call 0x19e6 ; _GBoxFill
0083 add sp, 0xa
0086 push word ptr [0xcf4e] ; __foreColor
008a push word ptr [bp - 0xe]
008d push di
008e push word ptr [bp - 2]
0091 mov ax, word ptr [bp - 0xc]
0094 dec ax
0095 push ax
0096 nop 
0097 push cs
0098 call 0x19e6 ; _GBoxFill
009b add sp, 0xa
009e push word ptr [0xcf4e] ; __foreColor
00a2 push word ptr [bp - 0xe]
00a5 push si
00a6 push word ptr [bp - 2]
00a9 mov ax, word ptr [bp - 4]
00ac dec ax
00ad push ax
00ae nop 
00af push cs
00b0 call 0x19e6 ; _GBoxFill
00b3 add sp, 0xa
00b6 pop si
00b7 pop di
00b8 leave 
00b9 retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GRectInvOutline', 'offset': 3594, 'source': 'src/recovered/wf_GRectInvOutline-81f8c3e9d1.c', 'size': 167}
- {'symbol': '_GRectInv', 'offset': 3762, 'source': 'src/recovered/GRectInv.c', 'size': 43}
- {'symbol': '_GRectFill', 'offset': 3992, 'source': 'src/recovered/GRectFill.c', 'size': 46}
- {'symbol': '_GRectFillOutline', 'offset': 4038, 'source': None, 'size': 220}

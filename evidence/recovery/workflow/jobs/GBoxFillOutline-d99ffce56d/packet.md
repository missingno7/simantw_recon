# Recovery task _GBoxFillOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 164 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xc]
0009 mov si, word ptr [bp + 0xe]
000c push word ptr [0xce8a] ; __backColor
0010 push di
0011 push word ptr [bp + 0xa]
0014 push word ptr [bp + 8]
0017 push word ptr [bp + 6]
001a nop 
001b push cs
001c call 0x19e6 ; _GBoxFill
001f add sp, 0xa
0022 or si, si
0024 je 0xbb8
0026 push word ptr [0xcf4e] ; __foreColor
002a push word ptr [bp + 8]
002d mov ax, si
002f sub si, word ptr [bp + 0xa]
0032 neg si
0034 lea cx, [si - 1]
0037 push cx
0038 mov dx, ax
003a add ax, word ptr [bp + 8]
003d dec ax
003e push ax
003f mov ax, dx
0041 add dx, word ptr [bp + 6]
0044 push dx
0045 mov word ptr [bp - 2], ax
0048 mov word ptr [bp - 4], cx
004b mov word ptr [bp - 6], dx
004e nop 
004f push cs
0050 call 0x19e6 ; _GBoxFill
0053 add sp, 0xa
0056 push word ptr [0xcf4e] ; __foreColor
005a lea ax, [di - 1]
005d push ax
005e push word ptr [bp - 4]
0061 sub di, word ptr [bp - 2]
0064 push di
0065 push word ptr [bp - 6]
0068 mov di, ax
006a nop 
006b push cs
006c call 0x19e6 ; _GBoxFill
006f add sp, 0xa
0072 push word ptr [0xcf4e] ; __foreColor
0076 push di
0077 push word ptr [bp + 6]
007a push word ptr [bp + 8]
007d mov ax, word ptr [bp - 6]
0080 dec ax
0081 push ax
0082 nop 
0083 push cs
0084 call 0x19e6 ; _GBoxFill
0087 add sp, 0xa
008a push word ptr [0xcf4e] ; __foreColor
008e push di
008f push si
0090 push word ptr [bp + 8]
0093 mov ax, word ptr [bp + 0xa]
0096 dec ax
0097 push ax
0098 nop 
0099 push cs
009a call 0x19e6 ; _GBoxFill
009d add sp, 0xa
00a0 pop si
00a1 pop di
00a2 leave 
00a3 retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxOutline-26008b9ec1.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxOutline-26008b9ec1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SkipWords', 'offset': 2162, 'source': 'src/recovered/wf_SkipWords-f10e7d71fd.c', 'size': 130}
- {'symbol': '_ReadConfig', 'offset': 2292, 'source': None, 'size': 548}
- {'symbol': '_GTextBox', 'offset': 3004, 'source': 'src/recovered/GTextBox.c', 'size': 35}
- {'symbol': '_GRectChecker', 'offset': 3040, 'source': 'src/recovered/GRectChecker.c', 'size': 48}

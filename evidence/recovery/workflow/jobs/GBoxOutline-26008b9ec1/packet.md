# Recovery task _GBoxOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 144 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xe]
0009 or si, si
000b je 0xcbe
000d mov di, word ptr [bp + 8]
0010 push word ptr [0xcf4e] ; __foreColor
0014 push di
0015 mov ax, si
0017 sub si, word ptr [bp + 0xa]
001a neg si
001c lea cx, [si - 1]
001f push cx
0020 mov dx, ax
0022 add ax, di
0024 dec ax
0025 push ax
0026 mov ax, dx
0028 add dx, word ptr [bp + 6]
002b push dx
002c mov word ptr [bp - 2], ax
002f mov word ptr [bp - 4], cx
0032 mov word ptr [bp - 6], dx
0035 nop 
0036 push cs
0037 call 0x19e6 ; _GBoxFill
003a add sp, 0xa
003d push word ptr [0xcf4e] ; __foreColor
0041 mov ax, word ptr [bp + 0xc]
0044 dec ax
0045 push ax
0046 push word ptr [bp - 4]
0049 mov cx, word ptr [bp + 0xc]
004c sub cx, word ptr [bp - 2]
004f push cx
0050 push word ptr [bp - 6]
0053 mov word ptr [bp - 8], ax
0056 nop 
0057 push cs
0058 call 0x19e6 ; _GBoxFill
005b add sp, 0xa
005e push word ptr [0xcf4e] ; __foreColor
0062 push word ptr [bp - 8]
0065 push word ptr [bp + 6]
0068 push di
0069 mov ax, word ptr [bp - 6]
006c dec ax
006d push ax
006e nop 
006f push cs
0070 call 0x19e6 ; _GBoxFill
0073 add sp, 0xa
0076 push word ptr [0xcf4e] ; __foreColor
007a push word ptr [bp - 8]
007d push si
007e push di
007f mov ax, word ptr [bp + 0xa]
0082 dec ax
0083 push ax
0084 nop 
0085 push cs
0086 call 0x19e6 ; _GBoxFill
0089 add sp, 0xa
008c pop si
008d pop di
008e leave 
008f retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GMixedFill-842c303c86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GRectChecker', 'offset': 3040, 'source': 'src/recovered/GRectChecker.c', 'size': 48}
- {'symbol': '_GCheckerBox', 'offset': 3088, 'source': 'src/recovered/GCheckerBox.c', 'size': 34}
- {'symbol': '_GRectPartialOutline', 'offset': 3266, 'source': None, 'size': 200}
- {'symbol': '_GInvOutline', 'offset': 3466, 'source': 'src/recovered/wf_GInvOutline-07520ef33f.c', 'size': 128}

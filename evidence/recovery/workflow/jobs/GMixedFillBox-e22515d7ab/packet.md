# Recovery task _GMixedFillBox

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 76 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov ax, word ptr [bp + 0xe]
0006 cmp word ptr [bp + 0x10], ax
0009 je 0x13d6
000b push 0x20
000d push word ptr [bp + 0x10]
0010 push ax
0011 nop 
0012 push cs
0013 call 0x19b4 ; _GSetAttrib
0016 mov sp, bp
0018 mov ah, byte ptr [0xcf4f]
001c add ah, 0x10
001f mov cl, 0x20
0021 mov ch, ah
0023 push cx
0024 push word ptr [bp + 0xc]
0027 push word ptr [bp + 0xa]
002a push word ptr [bp + 8]
002d push word ptr [bp + 6]
0030 nop 
0031 push cs
0032 call 0x1ab2 ; _GPatBox
0035 leave 
0036 retf 
0037 nop 
0038 push ax
0039 push word ptr [bp + 0xc]
003c push word ptr [bp + 0xa]
003f push word ptr [bp + 8]
0042 push word ptr [bp + 6]
0045 nop 
0046 push cs
0047 call 0x19e6 ; _GBoxFill
004a leave 
004b retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/GCheckerBox.c
- `extern void far GPatBox(int left, int top, int right, int bottom, int pattern);` — src/recovered/GRectChecker.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GPutPacked', 'offset': 4258, 'source': None, 'size': 634}
- {'symbol': '_GMixedFill', 'offset': 4892, 'source': None, 'size': 130}
- {'symbol': '_GRectPartialMixedOutline', 'offset': 5098, 'source': None, 'size': 291}
- {'symbol': '_WindowsMemCpy', 'offset': 5390, 'source': 'src/recovered/WindowsMemCpy.c', 'size': 81}

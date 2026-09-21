# Recovery task _GMixedFill

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 130 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 test byte ptr [0xcc7e], 1 ; _displayType
0009 je 0x1336
000b mov cx, word ptr [bp + 0xc]
000e mov al, byte ptr [bp + 0xa]
0011 xor al, cl
0013 test al, 0xf0
0015 jne 0x133e
0017 jmp 0x1374
0019 nop 
001a mov cx, word ptr [bp + 0xc]
001d cmp word ptr [bp + 0xa], cx
0020 je 0x1374
0022 mov si, word ptr [bp + 6]
0025 push 0x20
0027 push cx
0028 push word ptr [bp + 0xa]
002b nop 
002c push cs
002d call 0x19b4 ; _GSetAttrib
0030 add sp, 6
0033 mov ah, byte ptr [0xcf4f]
0037 add ah, 0x10
003a mov cl, 0x20
003c mov ch, ah
003e push cx
003f mov es, word ptr [bp + 8]
0042 push word ptr es:[si + 6]
0046 push word ptr es:[si + 4]
004a push word ptr es:[si + 2]
004e push word ptr es:[si]
0051 nop 
0052 push cs
0053 call 0x1ab2 ; _GPatBox
0056 jmp 0x1398
0058 mov si, word ptr [bp + 6]
005b mov ax, word ptr [bp + 8]
005e or ax, si
0060 je 0x139b
0062 push word ptr [bp + 0xa]
0065 mov es, word ptr [bp + 8]
0068 push word ptr es:[si + 6]
006c push word ptr es:[si + 4]
0070 push word ptr es:[si + 2]
0074 push word ptr es:[si]
0077 nop 
0078 push cs
0079 call 0x19e6 ; _GBoxFill
007c add sp, 0xa
007f pop si
0080 leave 
0081 retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/GCheckerBox.c
- `extern void far GPatBox(int left, int top, int right, int bottom, int pattern);` — src/recovered/GRectChecker.c
- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPic-08fc158e1c.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPicS-f46da1bb8a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GRectFillOutline', 'offset': 4038, 'source': None, 'size': 220}
- {'symbol': '_GPutPacked', 'offset': 4258, 'source': None, 'size': 634}
- {'symbol': '_GMixedFillBox', 'offset': 5022, 'source': 'src/recovered/wf_GMixedFillBox-e22515d7ab.c', 'size': 76}
- {'symbol': '_GRectPartialMixedOutline', 'offset': 5098, 'source': None, 'size': 291}

# Recovery task _GRectPartialMixedOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 291 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 cmp word ptr [bp + 0xa], 0
0008 jne 0x13f7
000a jmp 0x150a
000d mov cx, word ptr [bp + 0xe]
0010 mov si, word ptr [bp + 0x10]
0013 cmp si, cx
0015 jne 0x1404
0017 jmp 0x14f4
001a test byte ptr [0xcc7e], 1 ; _displayType
001f je 0x140e
0021 jmp 0x14f4
0024 push 0x20
0026 push si
0027 push cx
0028 nop 
0029 push cs
002a call 0x19b4 ; _GSetAttrib
002d add sp, 6
0030 test byte ptr [bp + 0xc], 2
0034 jne 0x1423
0036 jmp 0x14ee
0039 mov si, word ptr [bp + 6]
003c mov ah, byte ptr [0xcf4f]
0040 add ah, 0x10
0043 mov cl, 0x20
0045 mov ch, ah
0047 push cx
0048 mov es, word ptr [bp + 8]
004b push word ptr es:[si + 2]
004f mov ax, word ptr es:[si + 4]
0053 sub ax, word ptr [bp + 0xa]
0056 push ax
0057 mov ax, word ptr es:[si + 2]
005b add ax, word ptr [bp + 0xa]
005e push ax
005f mov ax, word ptr es:[si]
0062 add ax, word ptr [bp + 0xa]
0065 push ax
0066 nop 
0067 push cs
0068 call 0x1ab2 ; _GPatBox
006b add sp, 0xa
006e test byte ptr [bp + 0xc], 8
0072 je 0x1490
0074 mov ah, byte ptr [0xcf4f]
0078 add ah, 0x10
007b mov cl, 0x20
007d mov ch, ah
007f push cx
0080 mov es, word ptr [bp + 8]
0083 push word ptr es:[si + 6]
0087 mov ax, word ptr es:[si + 4]
008b sub ax, word ptr [bp + 0xa]
008e push ax
008f mov ax, word ptr es:[si + 6]
0093 sub ax, word ptr [bp + 0xa]
0096 push ax
0097 mov ax, word ptr es:[si]
009a add ax, word ptr [bp + 0xa]
009d push ax
009e nop 
009f push cs
00a0 call 0x1ab2 ; _GPatBox
00a3 add sp, 0xa
00a6 test byte ptr [bp + 0xc], 1
00aa je 0x14bf
00ac mov ah, byte ptr [0xcf4f]
00b0 add ah, 0x10
00b3 mov cl, 0x20
00b5 mov ch, ah
00b7 push cx
00b8 mov es, word ptr [bp + 8]
00bb push word ptr es:[si + 6]
00bf push word ptr es:[si]
00c2 push word ptr es:[si + 2]
00c6 mov ax, word ptr es:[si]
00c9 add ax, word ptr [bp + 0xa]
00cc push ax
00cd nop 
00ce push cs
00cf call 0x1ab2 ; _GPatBox
00d2 add sp, 0xa
00d5 test byte ptr [bp + 0xc], 4
00d9 je 0x150a
00db mov ah, byte ptr [0xcf4f]
00df add ah, 0x10
00e2 mov cl, 0x20
00e4 mov ch, ah
00e6 push cx
00e7 mov es, word ptr [bp + 8]
00ea push word ptr es:[si + 6]
00ee mov ax, word ptr es:[si + 4]
00f2 mov cx, ax
00f4 sub ax, word ptr [bp + 0xa]
00f7 push ax
00f8 push word ptr es:[si + 2]
00fc push cx
00fd nop 
00fe push cs
00ff call 0x1ab2 ; _GPatBox
0102 jmp 0x1507
0104 mov si, word ptr [bp + 6]
0107 jmp 0x1458
010a push cx
010b mov al, byte ptr [bp + 0xc]
010e push ax
010f push word ptr [bp + 0xa]
0112 push word ptr [bp + 8]
0115 push word ptr [bp + 6]
0118 nop 
0119 push cs
011a call 0xcc2 ; _GRectPartialOutline
011d add sp, 0xa
0120 pop si
0121 leave 
0122 retf 
```

## Known declaration examples

- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/GCheckerBox.c
- `extern void far GPatBox(int left, int top, int right, int bottom, int pattern);` — src/recovered/GRectChecker.c
- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GMixedFill', 'offset': 4892, 'source': 'src/recovered/wf_GMixedFill-842c303c86.c', 'size': 130}
- {'symbol': '_GMixedFillBox', 'offset': 5022, 'source': 'src/recovered/wf_GMixedFillBox-e22515d7ab.c', 'size': 76}
- {'symbol': '_WindowsMemCpy', 'offset': 5390, 'source': 'src/recovered/WindowsMemCpy.c', 'size': 81}
- {'symbol': '_GSetSmallFont', 'offset': 5472, 'source': None, 'size': 259}

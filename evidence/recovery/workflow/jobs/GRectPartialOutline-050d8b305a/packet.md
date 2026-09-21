# Recovery task _GRectPartialOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 200 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 cmp word ptr [bp + 0xa], 0
0008 jne 0xccf
000a jmp 0xd87
000d mov si, word ptr [bp + 6]
0010 mov ax, word ptr [bp + 8]
0013 or ax, si
0015 jne 0xcdc
0017 jmp 0xd87
001a test byte ptr [bp + 0xc], 2
001e je 0xd0b
0020 push word ptr [bp + 0xe]
0023 mov es, word ptr [bp + 8]
0026 push word ptr es:[si + 2]
002a mov ax, word ptr es:[si + 4]
002e sub ax, word ptr [bp + 0xa]
0031 push ax
0032 mov ax, word ptr es:[si + 2]
0036 add ax, word ptr [bp + 0xa]
0039 push ax
003a mov ax, word ptr es:[si]
003d add ax, word ptr [bp + 0xa]
0040 push ax
0041 nop 
0042 push cs
0043 call 0x19e6 ; _GBoxFill
0046 add sp, 0xa
0049 test byte ptr [bp + 0xc], 8
004d je 0xd3a
004f push word ptr [bp + 0xe]
0052 mov es, word ptr [bp + 8]
0055 push word ptr es:[si + 6]
0059 mov ax, word ptr es:[si + 4]
005d sub ax, word ptr [bp + 0xa]
0060 push ax
0061 mov ax, word ptr es:[si + 6]
0065 sub ax, word ptr [bp + 0xa]
0068 push ax
0069 mov ax, word ptr es:[si]
006c add ax, word ptr [bp + 0xa]
006f push ax
0070 nop 
0071 push cs
0072 call 0x19e6 ; _GBoxFill
0075 add sp, 0xa
0078 test byte ptr [bp + 0xc], 1
007c je 0xd60
007e push word ptr [bp + 0xe]
0081 mov es, word ptr [bp + 8]
0084 push word ptr es:[si + 6]
0088 push word ptr es:[si]
008b push word ptr es:[si + 2]
008f mov ax, word ptr es:[si]
0092 add ax, word ptr [bp + 0xa]
0095 push ax
0096 nop 
0097 push cs
0098 call 0x19e6 ; _GBoxFill
009b add sp, 0xa
009e test byte ptr [bp + 0xc], 4
00a2 je 0xd87
00a4 push word ptr [bp + 0xe]
00a7 mov es, word ptr [bp + 8]
00aa push word ptr es:[si + 6]
00ae mov ax, word ptr es:[si + 4]
00b2 mov cx, ax
00b4 sub ax, word ptr [bp + 0xa]
00b7 push ax
00b8 push word ptr es:[si + 2]
00bc push cx
00bd nop 
00be push cs
00bf call 0x19e6 ; _GBoxFill
00c2 add sp, 0xa
00c5 pop si
00c6 leave 
00c7 retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GCheckerBox', 'offset': 3088, 'source': 'src/recovered/GCheckerBox.c', 'size': 34}
- {'symbol': '_GBoxOutline', 'offset': 3122, 'source': 'src/recovered/wf_GBoxOutline-26008b9ec1.c', 'size': 144}
- {'symbol': '_GInvOutline', 'offset': 3466, 'source': 'src/recovered/wf_GInvOutline-07520ef33f.c', 'size': 128}
- {'symbol': '_GRectInvOutline', 'offset': 3594, 'source': 'src/recovered/wf_GRectInvOutline-81f8c3e9d1.c', 'size': 167}

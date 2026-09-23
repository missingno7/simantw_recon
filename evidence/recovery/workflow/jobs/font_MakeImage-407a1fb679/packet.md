# Recovery task _font_MakeImage

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 586 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xc]
0009 mov ax, word ptr [bp + 0xa]
000c mov word ptr [bp - 0xc], ax
000f mov es, word ptr [bp + 0xe]
0012 mov ax, word ptr es:[di + 6]
0016 mov word ptr [bp - 0xe], ax
0019 mov ax, word ptr [0xb8e0] ; _buffer_max_width
001c imul word ptr [0xb8e2] ; _buffer_max_height
0020 push ax
0021 mov es, word ptr [0xc696]
0025 push word ptr es:[0x7d22]
002a push word ptr es:[0x7d20]
002f nop 
0030 push cs
0031 call 0xb0ef ; _ClearBuffer
0034 add sp, 6
0037 mov es, word ptr [bp + 0xe]
003a mov ax, word ptr es:[di + 0x18]
003e shl ax, 1
0040 mov es, word ptr [0xc698]
0044 mov word ptr es:[0xb912], ax
0048 xor si, si
004a mov word ptr [bp - 4], si
004d mov es, word ptr [bp + 0xe]
0050 cmp word ptr es:[di + 0x26], si
0054 je 0xaeb4
0056 cmp word ptr es:[di + 8], si
005a jge 0xae42
005c mov ax, 1
005f jmp 0xae44
0061 nop 
0062 xor ax, ax
0064 mov word ptr [bp - 2], ax
0067 les bx, ptr [bp + 6]
006a cmp byte ptr es:[bx], 0
006e jne 0xae56
0070 mov si, word ptr [bp + 0xc]
0073 jmp 0xaed0
0075 nop 
0076 mov es, word ptr [bp + 0xe]
0079 mov bx, word ptr es:[di + 0x28]
007d shl bx, 1
007f mov ax, word ptr es:[di + 0x22]
0083 mov dx, word ptr es:[di + 0x24]
0087 mov es, dx
0089 add bx, ax
008b mov al, byte ptr es:[bx]
008e sub ah, ah
0090 mov word ptr [bp - 0x10], ax
0093 mov cx, word ptr [bp - 4]
0096 mov ds, word ptr [bp + 0xe]
0099 les bx, ptr [bp + 6]
009c mov bl, byte ptr es:[bx + si]
009f sub bh, bh
00a1 shl bx, 1
00a3 mov es, word ptr [di + 0x24]
00a6 add bx, word ptr [di + 0x22]
00a9 mov ax, word ptr es:[bx]
00ac mov word ptr [bp - 0x12], ax
00af inc ax
00b0 je 0xae9c
00b2 mov al, byte ptr [bp - 0x12]
00b5 sub ah, ah
00b7 add cx, ax
00b9 jmp 0xae9f
00bb nop 
00bc add cx, word ptr [bp - 0x10]
00bf inc si
00c0 add cx, word ptr [bp - 2]
00c3 les bx, ptr [bp + 6]
00c6 cmp byte ptr es:[bx + si], 0
00ca jne 0xae79
00cc mov word ptr [bp - 4], cx
00cf push ss
00d0 pop ds
00d1 jmp 0xae50
00d3 nop 
00d4 mov si, di
00d6 mov ax, word ptr es:[si + 6]
00da mov dx, ax
00dc les di, ptr [bp + 6]
00df mov cx, 0xffff
00e2 xor ax, ax
00e4 repne scasb al, byte ptr es:[di]
00e6 not cx
00e8 dec cx
00e9 mov ax, dx
00eb imul cx
00ed mov word ptr [bp - 4], ax
00f0 mov ax, word ptr [bp - 4]
00f3 add ax, word ptr [bp + 0xa]
00f6 add ax, 7
00f9 sar ax, 3
00fc mov es, word ptr [0xc69a]
0100 mov word ptr es:[0xb914], ax
0104 mov es, word ptr [bp + 0xe]
0107 mov ax, word ptr es:[si + 0xe]
010b mov es, word ptr [0xc696]
010f mov word ptr es:[0x7d1e], ax
0113 mov ax, word ptr [0xb8e0] ; _buffer_max_width
0116 shl ax, 3
0119 mov es, word ptr [bp + 0xe]
011c sub ax, word ptr es:[si + 0xc]
0120 mov word ptr [bp - 0xa], ax
0123 mov word ptr [bp - 8], 0
0128 les bx, ptr [bp + 6]
012b cmp byte ptr es:[bx], 0
012f jne 0xaf18
0131 mov si, word ptr [bp - 0xc]
0134 jmp 0xb013
0137 nop 
0138 mov di, si
013a mov si, word ptr [bp - 0xc]
013d cmp word ptr [bp - 0xa], si
0140 jg 0xaf25
0142 jmp 0xb013
0145 mov bx, word ptr [bp + 6]
0148 add bx, word ptr [bp - 8]
014b mov al, byte ptr es:[bx]
014e mov byte ptr [bp - 1], al
0151 mov es, word ptr [bp + 0xe]
0154 mov bl, al
0156 sub bh, bh
0158 shl bx, 1
015a mov ax, word ptr es:[di + 0x22]
015e mov dx, word ptr es:[di + 0x24]
0162 mov es, dx
0164 add bx, ax
0166 cmp word ptr es:[bx], -1
016a jne 0xaf56
016c mov es, word ptr [bp + 0xe]
016f mov al, byte ptr es:[di + 0x28]
0173 mov byte ptr [bp - 1], al
0176 mov es, word ptr [bp + 0xe]
0179 les bx, ptr es:[di + 0x22]
017d mov al, byte ptr [bp - 1]
0180 sub ah, ah
0182 shl ax, 1
0184 mov word ptr [bp - 0x14], ax
0187 add bx, ax
0189 mov al, byte ptr es:[bx + 1]
018d sub ah, ah
018f mov cx, ax
0191 mov es, word ptr [bp + 0xe]
0194 cmp word ptr es:[di + 0x26], 0
0199 je 0xaf88
019b les bx, ptr es:[di + 0x22]
019f add bx, word ptr [bp - 0x14]
01a2 mov al, byte ptr es:[bx]
01a5 mov word ptr [bp - 0xe], ax
01a8 mov es, word ptr [bp + 0xe]
01ab les bx, ptr es:[di + 0x1e]
01af add bx, word ptr [bp - 0x14]
01b2 mov ax, word ptr es:[bx]
01b5 mov word ptr [bp - 4], ax
01b8 sub ax, word ptr es:[bx + 2]
01bc neg ax
01be mov word ptr [bp - 6], ax
01c1 mov es, word ptr [bp + 0xe]
01c4 cmp word ptr es:[di + 8], 0
01c9 jge 0xafb6
01cb mov word ptr [bp - 2], 0
01d0 inc word ptr [bp - 0xe]
01d3 jmp 0xafbd
01d5 nop 
01d6 add cx, word ptr es:[di + 8]
01da mov word ptr [bp - 2], cx
01dd mov ax, word ptr [bp - 2]
01e0 add ax, si
01e2 push ax
01e3 push word ptr [bp - 4]
01e6 mov ax, word ptr es:[di + 0xe]
01ea dec ax
01eb push ax
01ec push word ptr [bp - 6]
01ef mov es, word ptr [0xc696]
01f3 push word ptr es:[0x7d22]
01f8 push word ptr es:[0x7d20]
01fd mov es, word ptr [bp + 0xe]
0200 mov ax, word ptr es:[di + 0x1a]
0204 mov dx, word ptr es:[di + 0x1c]
0208 mov es, word ptr [0xc698]
020c add ax, word ptr es:[0xb912]
0211 push dx
0212 push ax
0213 nop 
0214 push cs
0215 call 0xb033 ; _DrawChar
0218 add sp, 0x10
021b add si, word ptr [bp - 0xe]
021e inc word ptr [bp - 8]
0221 mov bx, word ptr [bp - 8]
0224 mov es, word ptr [bp + 8]
0227 add bx, word ptr [bp + 6]
022a cmp byte ptr es:[bx], 0
022e je 0xb013
0230 jmp 0xaf1d
0233 mov es, word ptr [0xc696]
0237 mov word ptr es:[0x7d1c], si
023c dec word ptr es:[0x7d1e]
0241 mov ax, 0x7d1c
0244 mov dx, es
0246 pop si
0247 pop di
0248 leave 
0249 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '__font_FontHeight', 'offset': 44480, 'source': 'src/recovered/font_FontHeightNative.c', 'size': 13}
- {'symbol': '__font_LineHeight', 'offset': 44494, 'source': 'src/recovered/font_LineHeight.c', 'size': 17}
- {'symbol': '_DrawChar', 'offset': 45107, 'source': None, 'size': 188}
- {'symbol': '_ClearBuffer', 'offset': 45295, 'source': None, 'size': 32}

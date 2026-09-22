# Recovery task _DoReturnFoodAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 398 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc318]
000a mov bx, word ptr [bp + 4]
000d mov si, word ptr es:[bx + 0x23a4]
0012 and si, 0xff
0016 mov al, byte ptr es:[bx + 0x278e]
001b sub ah, ah
001d mov di, ax
001f mov al, byte ptr es:[bx + 0x2f62]
0024 mov word ptr [bp - 2], ax
0027 push di
0028 push si
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
002e add sp, 4
0031 or ax, ax
0033 jne 0x1cee
0035 xor cx, cx
0037 jmp 0x1d22
0039 nop 
003a mov es, word ptr [0xc320]
003e cmp word ptr es:[0x9b6e], 0
0044 jne 0x1d08
0046 mov bx, si
0048 shl bx, 6
004b cmp byte ptr [bx + di + 0x28e8], 0x50
0050 jne 0x1ce9
0052 jmp 0x1d1f
0054 mov bx, si
0056 shl bx, 6
0059 mov dl, byte ptr [bx + di + 0x28e8]
005d sub dh, dh
005f cmp dx, 0x80
0063 jl 0x1ce9
0065 cmp dx, 0x8f
0069 jg 0x1ce9
006b mov cx, 1
006e or cx, cx
0070 je 0x1d32
0072 push word ptr [bp + 4]
0075 push di
0076 push si
0077 call 0x257a ; _GoInNest
007a jmp 0x1e3b
007d nop 
007e mov al, byte ptr [bp - 2]
0081 and ax, 0xf8
0084 mov word ptr [bp - 0xa], ax
0087 mov al, byte ptr [bp - 2]
008a push word ptr [bp - 2]
008d and ax, 7
0090 push ax
0091 push di
0092 push si
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNestDir
0098 add sp, 8
009b mov bx, ax
009d mov word ptr [bp - 4], bx
00a0 mov es, word ptr [0xc31e]
00a4 mov al, byte ptr es:[bx]
00a9 cwde 
00aa add ax, si
00ac mov word ptr [bp - 6], ax
00af mov es, word ptr [0xc31c]
00b3 mov cx, ax
00b5 mov al, byte ptr es:[bx + 8]
00ba cwde 
00bb add ax, di
00bd mov word ptr [bp - 8], ax
00c0 mov bx, cx
00c2 shl bx, 6
00c5 add bx, ax
00c7 mov al, byte ptr [bx + 0x28e8]
00cb sub ah, ah
00cd mov es, word ptr [0xc32c]
00d1 cmp ax, word ptr es:[0x7604]
00d6 jle 0x1dc2
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 219, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00dd mov bl, byte ptr [bp - 2]
00e0 and bx, 7
00e3 shl bx, 3
00e6 add bx, ax
00e8 mov es, word ptr [0xc32e]
00ec mov al, byte ptr es:[bx + 0x24]
00f1 or al, byte ptr [bp - 0xa]
00f4 mov es, word ptr [0xc318]
00f8 mov bx, word ptr [bp + 4]
00fb mov byte ptr es:[bx + 0x2f62], al
0100 mov bx, si
0102 shl bx, 6
0105 mov byte ptr [bx + di + 0x68e8], al
0109 pop si
010a pop di
010b leave 
010c ret 
010d nop 
010e mov <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0111 mov es, ax
0113 mov al, byte ptr [bp - 4]
0116 or al, byte ptr [bp - 0xa]
0119 mov bx, cx
011b shl bx, 6
011e add bx, word ptr [bp - 8]
0121 mov byte ptr [bx + 0x68e8], al
0125 mov bx, word ptr [bp + 4]
0128 mov byte ptr es:[bx + 0x2f62], al
012d mov bx, si
012f shl bx, 6
0132 mov byte ptr [bx + di + 0x68e8], 0
0137 mov al, byte ptr [bp - 6]
013a mov bx, word ptr [bp + 4]
013d mov byte ptr es:[bx + 0x23a4], al
0142 mov al, byte ptr [bp - 8]
0145 mov byte ptr es:[bx + 0x278e], al
014a cmp byte ptr es:[bx + 0x334c], 0
0150 je 0x1e3e
0152 dec byte ptr es:[bx + 0x334c]
0157 test byte ptr [bp - 2], 0x80
015b je 0x1e26
015d mov es, word ptr [0xc318]
0161 mov al, byte ptr es:[bx + 0x334c]
0166 sub ah, ah
0168 push ax
0169 push word ptr [bp - 8]
016c push cx
016d call 0x9576 ; _JamScentRT
0170 jmp 0x1e3b
0172 mov es, word ptr [0xc318]
0176 mov al, byte ptr es:[bx + 0x334c]
017b sub ah, ah
017d push ax
017e push word ptr [bp - 8]
0181 push cx
0182 nop 
0183 push cs
0184 call 0x9536 ; _JamScentBT
0187 add sp, 6
018a pop si
018b pop di
018c leave 
018d ret 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoToNestAnt', 'offset': 5750, 'source': None, 'size': 915}
- {'symbol': '_DoToAlarm', 'offset': 6666, 'source': None, 'size': 682}
- {'symbol': '_DoForageAnt', 'offset': 7746, 'source': None, 'size': 1126}
- {'symbol': '_DoRecruitAnt', 'offset': 8872, 'source': None, 'size': 722}

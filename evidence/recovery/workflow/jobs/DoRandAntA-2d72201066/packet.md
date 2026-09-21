# Recovery task _DoRandAntA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 974 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 4]
0009 mov es, word ptr [0xc318]
000d mov al, byte ptr es:[di + 0x23a4]
0012 sub ah, ah
0014 mov si, ax
0016 mov al, byte ptr es:[di + 0x278e]
001b mov word ptr [bp - 0xc], ax
001e mov al, byte ptr es:[di + 0x2f62]
0023 mov word ptr [bp - 2], ax
0026 push word ptr [bp - 0xc]
0029 push si
002a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
002f add sp, 4
0032 or ax, ax
0034 jne 0xea0
0036 xor cx, cx
0038 jmp 0xedb
003a mov es, word ptr [0xc320]
003e cmp word ptr es:[0x9b6e], 0
0044 jne 0xebe
0046 mov bx, si
0048 shl bx, 6
004b add bx, word ptr [bp - 0xc]
004e cmp byte ptr [bx + 0x28e8], 0x50
0053 jne 0xe9c
0055 jmp 0xed8
0057 nop 
0058 mov bx, si
005a shl bx, 6
005d add bx, word ptr [bp - 0xc]
0060 mov dl, byte ptr [bx + 0x28e8]
0064 sub dh, dh
0066 cmp dx, 0x80
006a jl 0xe9c
006c cmp dx, 0x8f
0070 jg 0xe9c
0072 mov cx, 1
0075 or cx, cx
0077 je 0xeea
0079 push di
007a push word ptr [bp - 0xc]
007d push si
007e call 0x257a ; _GoInNest
0081 jmp 0x122d
0084 mov al, byte ptr [bp - 2]
0087 and ax, 0xf8
008a mov word ptr [bp - 8], ax
008d mov al, byte ptr [bp - 2]
0090 and ax, 0x78
0093 sar ax, 3
0096 mov word ptr [bp - 0x12], ax
0099 mov al, byte ptr [bp - 2]
009c and ax, 7
009f mov word ptr [bp - 0x14], ax
00a2 push ax
00a3 push word ptr [bp - 0xc]
00a6 push si
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetRandDir
00ac add sp, 6
00af mov bx, ax
00b1 mov word ptr [bp - 0xa], bx
00b4 mov es, word ptr [0xc31e]
00b8 mov al, byte ptr es:[bx]
00bd cwde 
00be add ax, si
00c0 mov word ptr [bp - 0xe], ax
00c3 mov es, word ptr [0xc31c]
00c7 mov cx, ax
00c9 mov al, byte ptr es:[bx + 8]
00ce cwde 
00cf add ax, word ptr [bp - 0xc]
00d2 mov word ptr [bp - 0x10], ax
00d5 mov bx, cx
00d7 shl bx, 6
00da add bx, ax
00dc mov al, byte ptr [bx + 0x28e8]
00e0 sub ah, ah
00e2 mov word ptr [bp - 4], ax
00e5 mov es, word ptr [0xc320]
00e9 cmp word ptr es:[0x9b6e], 0
00ef jne 0xf66
00f1 cmp ax, 0x48
00f4 jl 0xf70
00f6 cmp ax, 0x4b
00f9 jg 0xf70
00fb mov dx, 1
00fe jmp 0xf72
0100 cmp ax, 0x18
0103 jl 0xf70
0105 cmp ax, 0x27
0108 jle 0xf61
010a xor dx, dx
010c dec dx
010d jne 0xfc0
010f cmp word ptr [bp - 0x12], 6
0113 je 0xf81
0115 cmp word ptr [bp - 0x12], 2
0119 jne 0x1000
011b mov al, byte ptr [bp - 0xa]
011e or al, byte ptr [bp - 8]
0121 or al, 8
0123 mov es, word ptr [0xc318]
0127 mov byte ptr es:[di + 0x2f62], al
012c mov bx, si
012e shl bx, 6
0131 add bx, word ptr [bp - 0xc]
0134 mov byte ptr [bx + 0x68e8], al
0138 mov byte ptr es:[di + 0x2b78], 3
013e push word ptr [bp - 0x10]
0141 push word ptr [bp - 0xe]
0144 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PickupFoodA
0149 add sp, 4
014c mov es, word ptr [0xc318]
0150 mov byte ptr es:[di + 0x334c], 0xc8
0156 jmp 0x1230
0159 nop 
015a mov ax, word ptr [bp - 4]
015d mov es, word ptr [0xc32c]
0161 cmp word ptr es:[0x7604], ax
0166 jge 0x1000
0168 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 363, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
016d mov bx, word ptr [bp - 0x14]
0170 shl bx, 3
0173 add bx, ax
0175 mov es, word ptr [0xc32e]
0179 mov al, byte ptr es:[bx + 0x24]
017e or al, byte ptr [bp - 8]
0181 mov es, word ptr [0xc318]
0185 mov byte ptr es:[di + 0x2f62], al
018a mov bx, si
018c shl bx, 6
018f add bx, word ptr [bp - 0xc]
0192 mov byte ptr [bx + 0x68e8], al
0196 pop si
0197 pop di
0198 leave 
0199 ret 
019a mov <resolved loader operand; see bindings> ; [{'operand_offset': 411, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
019d mov es, ax
019f mov bx, word ptr [bp - 0xe]
01a2 shl bx, 6
01a5 add bx, word ptr [bp - 0x10]
01a8 add bx, 0x68e8
01ac mov word ptr [bp - 0x16], bx
01af mov dl, byte ptr [bx]
01b1 sub dh, dh
01b3 or dx, dx
01b5 je 0x1020
01b7 jmp 0x10c4
01ba mov al, byte ptr [bp - 0xa]
01bd or al, byte ptr [bp - 8]
01c0 mov byte ptr [bx], al
01c2 mov byte ptr es:[di + 0x2f62], al
01c7 mov bx, word ptr [bp - 0xc]
01ca shl si, 6
01cd mov byte ptr [bx + si + 0x68e8], dh
01d1 mov al, byte ptr [bp - 0xe]
01d4 mov byte ptr es:[di + 0x23a4], al
01d9 mov al, byte ptr [bp - 0x10]
01dc mov byte ptr es:[di + 0x278e], al
01e1 cmp byte ptr es:[di + 0x334c], dh
01e6 je 0x1088
01e8 dec byte ptr es:[di + 0x334c]
01ed test byte ptr [bp - 2], 0x80
01f1 je 0x1070
01f3 mov es, word ptr [0xc318]
01f7 mov al, byte ptr es:[di + 0x334c]
01fc sub ah, ah
01fe push ax
01ff push word ptr [bp - 0x10]
0202 push word ptr [bp - 0xe]
0205 call 0xffff94f6
0208 jmp 0x1085
020a mov es, word ptr [0xc318]
020e mov al, byte ptr es:[di + 0x334c]
0213 sub ah, ah
0215 push ax
0216 push word ptr [bp - 0x10]
0219 push word ptr [bp - 0xe]
021c call 0xffff94b6
021f add sp, 6
0222 mov al, byte ptr [bp - 2]
0225 and ax, 0x80
0228 push ax
0229 push word ptr [bp - 0x10]
022c push word ptr [bp - 0xe]
022f call 0xffff95b6
0232 add sp, 6
0235 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 568, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
023a or ax, ax
023c je 0x10a7
023e jmp 0x1230
0241 cmp word ptr [bp - 0x12], 6
0245 je 0x10b6
0247 cmp word ptr [bp - 0x12], 2
024b je 0x10b6
024d jmp 0x1230
0250 mov es, word ptr [0xc318]
0254 mov byte ptr es:[di + 0x2b78], 2
025a pop si
025b pop di
025c leave 
025d ret 
025e mov word ptr [bp - 4], dx
0261 mov word ptr [bp - 6], si
0264 mov si, dx
0266 push si
0267 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 618, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
026c add sp, 2
026f dec ax
0270 je 0x10db
0272 jmp 0x115e
0275 mov al, byte ptr [bp - 2]
0278 xor al, byte ptr [0xce98] ; _MeColor
027c test al, 0x80
027e je 0x10f6
0280 push di
0281 push 1
0283 nop 
0284 push cs
0285 call 0x823e ; _YellowFight
0288 add sp, 4
028b pop si
028c pop di
028d leave 
028e ret 
028f nop 
0290 mov si, word ptr [bp - 0xc]
0293 mov es, word ptr [0xc330]
0297 cmp word ptr es:[0x9af2], 1
029d jne 0x112d
029f mov al, byte ptr [bp - 0xa]
02a2 or al, byte ptr [bp - 8]
02a5 mov es, word ptr [0xc318]
02a9 mov byte ptr es:[di + 0x2f62], al
02ae mov bx, word ptr [bp - 6]
02b1 shl bx, 6
02b4 mov byte ptr [bx + si + 0x68e8], al
02b8 push word ptr [bp - 0xa]
02bb push si
02bc push word ptr [bp - 6]
02bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 706, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoTroph
02c4 add sp, 6
02c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 714, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
02cc mov bx, word ptr [bp - 0x14]
02cf shl bx, 3
02d2 add bx, ax
02d4 mov es, word ptr [0xc32e]
02d8 mov al, byte ptr es:[bx + 0x24]
02dd or al, byte ptr [bp - 8]
02e0 mov es, word ptr [0xc318]
02e4 mov byte ptr es:[di + 0x2f62], al
02e9 mov bx, word ptr [bp - 6]
02ec shl bx, 6
02ef mov byte ptr [bx + si + 0x68e8], al
02f3 pop si
02f4 pop di
02f5 leave 
02f6 ret 
02f7 nop 
02f8 mov si, word ptr [bp - 2]
02fb mov dx, word ptr [bp - 4]
02fe mov ax, si
0300 xor dl, al
0302 test dl, 0x80
0305 jne 0x11b8
0307 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 778, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
030c mov bx, word ptr [bp - 0x14]
030f shl bx, 3
0312 add bx, ax
0314 mov es, word ptr [0xc32e]
0318 mov al, byte ptr es:[bx + 0x24]
031d or al, byte ptr [bp - 8]
0320 mov es, word ptr [0xc318]
0324 mov byte ptr es:[di + 0x2f62], al
0329 mov bx, word ptr [bp - 0xc]
032c mov cx, si
032e mov si, word ptr [bp - 6]
0331 shl si, 6
0334 mov byte ptr [bx + si + 0x68e8], al
0338 push cx
0339 push word ptr [bp - 0x12]
033c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 831, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
0341 add sp, 4
0344 mov es, word ptr [0xc318]
0348 mov byte ptr es:[di + 0x2b78], al
034d pop si
034e pop di
034f leave 
0350 ret 
0351 nop 
0352 mov es, word ptr [0xc318]
0356 mov al, byte ptr es:[di + 0x2f62]
035b sub ah, ah
035d mov word ptr [bp - 2], ax
0360 xor al, al
0362 mov byte ptr es:[di + 0x2f62], al
0367 mov si, word ptr [bp - 6]
036a shl si, 6
036d mov bx, word ptr [bp - 0xc]
0370 mov byte ptr [bx + si + 0x68e8], al
0374 push word ptr [bp - 0x10]
0377 push word ptr [bp - 0xe]
037a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 893, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
037f add sp, 4
0382 mov si, ax
0384 or si, si
0386 jl 0x1230
0388 push word ptr [bp - 2]
038b mov es, word ptr [0xc318]
038f mov al, byte ptr es:[si + 0x2f62]
0394 sub ah, ah
0396 push ax
0397 call 0x26f4 ; _GetWinner
039a add sp, 4
039d mov cx, ax
039f and al, 0x80
03a1 add al, 0x70
03a3 mov es, word ptr [0xc318]
03a7 mov byte ptr es:[si + 0x2f62], al
03ac mov bx, word ptr [bp - 0x16]
03af mov byte ptr [bx], al
03b1 mov byte ptr es:[si + 0x2b78], 0xa
03b7 mov byte ptr es:[si + 0x334c], cl
03bc push 0x28
03be push word ptr [bp - 0x10]
03c1 push word ptr [bp - 0xe]
03c4 call 0xffff947e
03c7 add sp, 6
03ca pop si
03cb pop di
03cc leave 
03cd ret 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeB-f9a6e1c57a.c
- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRepoFly', 'offset': 3402, 'source': None, 'size': 172}
- {'symbol': '_DoDefendNest', 'offset': 3574, 'source': None, 'size': 112}
- {'symbol': '_DoRandAntAA', 'offset': 4660, 'source': None, 'size': 588}
- {'symbol': '_DoDigOutAntA', 'offset': 5248, 'source': None, 'size': 502}

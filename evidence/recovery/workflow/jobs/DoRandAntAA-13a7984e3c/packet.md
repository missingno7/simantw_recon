# Recovery task _DoRandAntAA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 588 bytes.

```asm
0000 enter 0x14, 0
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
0024 mov word ptr [bp - 4], ax
0027 push di
0028 push si
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
002e add sp, 4
0031 or ax, ax
0033 jne 0x126e
0035 xor cx, cx
0037 jmp 0x12a2
0039 nop 
003a mov es, word ptr [0xc320]
003e cmp word ptr es:[0x9b6e], 0
0044 jne 0x1288
0046 mov bx, si
0048 shl bx, 6
004b cmp byte ptr [bx + di + 0x28e8], 0x50
0050 jne 0x1269
0052 jmp 0x129f
0054 mov bx, si
0056 shl bx, 6
0059 mov dl, byte ptr [bx + di + 0x28e8]
005d sub dh, dh
005f cmp dx, 0x80
0063 jl 0x1269
0065 cmp dx, 0x8f
0069 jg 0x1269
006b mov cx, 1
006e or cx, cx
0070 je 0x12b2
0072 push word ptr [bp + 4]
0075 push di
0076 push si
0077 call 0x257a ; _GoInNest
007a jmp 0x1479
007d nop 
007e mov al, byte ptr [bp - 4]
0081 and ax, 0xf8
0084 mov word ptr [bp - 0xc], ax
0087 mov al, byte ptr [bp - 4]
008a and ax, 7
008d mov word ptr [bp - 0x12], ax
0090 push ax
0091 push di
0092 push si
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetRandDir
0098 add sp, 6
009b mov bx, ax
009d mov word ptr [bp - 2], bx
00a0 mov es, word ptr [0xc31e]
00a4 mov al, byte ptr es:[bx]
00a9 cwde 
00aa add ax, si
00ac mov word ptr [bp - 0x10], ax
00af mov es, word ptr [0xc31c]
00b3 mov cx, ax
00b5 mov al, byte ptr es:[bx + 8]
00ba cwde 
00bb add ax, di
00bd mov word ptr [bp - 0xe], ax
00c0 mov bx, cx
00c2 shl bx, 6
00c5 add bx, ax
00c7 mov al, byte ptr [bx + 0x28e8]
00cb sub ah, ah
00cd mov es, word ptr [0xc32c]
00d1 cmp ax, word ptr es:[0x7604]
00d6 jle 0x133e
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 219, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00dd mov bx, word ptr [bp - 0x12]
00e0 shl bx, 3
00e3 add bx, ax
00e5 mov es, word ptr [0xc32e]
00e9 mov al, byte ptr es:[bx + 0x24]
00ee or al, byte ptr [bp - 0xc]
00f1 mov es, word ptr [0xc318]
00f5 mov bx, word ptr [bp + 4]
00f8 mov byte ptr es:[bx + 0x2f62], al
00fd mov bx, si
00ff shl bx, 6
0102 mov byte ptr [bx + di + 0x68e8], al
0106 pop si
0107 pop di
0108 leave 
0109 ret 
010a mov <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
010d mov es, ax
010f mov bx, cx
0111 shl bx, 6
0114 add bx, word ptr [bp - 0xe]
0117 add bx, 0x68e8
011b mov word ptr [bp - 0x14], bx
011e mov al, byte ptr [bx]
0120 sub ah, ah
0122 mov word ptr [bp - 6], ax
0125 or ax, ax
0127 jne 0x138e
0129 mov al, byte ptr [bp - 2]
012c or al, byte ptr [bp - 0xc]
012f mov byte ptr [bx], al
0131 mov bx, word ptr [bp + 4]
0134 mov byte ptr es:[bx + 0x2f62], al
0139 mov bx, si
013b shl bx, 6
013e mov byte ptr [bx + di + 0x68e8], ah
0142 mov bx, word ptr [bp + 4]
0145 mov al, byte ptr [bp - 0x10]
0148 mov byte ptr es:[bx + 0x23a4], al
014d mov al, byte ptr [bp - 0xe]
0150 mov byte ptr es:[bx + 0x278e], al
0155 pop si
0156 pop di
0157 leave 
0158 ret 
0159 nop 
015a mov word ptr [bp - 0xa], di
015d mov word ptr [bp - 8], si
0160 push ax
0161 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 356, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0166 add sp, 2
0169 dec ax
016a jne 0x13f4
016c mov al, byte ptr [bp - 4]
016f xor al, byte ptr [0xce98] ; _MeColor
0173 test al, 0x80
0175 je 0x13bc
0177 push word ptr [bp + 4]
017a push 1
017c nop 
017d push cs
017e call 0x823e ; _YellowFight
0181 add sp, 4
0184 pop si
0185 pop di
0186 leave 
0187 ret 
0188 mov di, word ptr [bp - 0xc]
018b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 398, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0190 mov bx, word ptr [bp - 0x12]
0193 shl bx, 3
0196 add bx, ax
0198 mov es, word ptr [0xc32e]
019c mov ax, di
019e or al, byte ptr es:[bx + 0x24]
01a3 mov es, word ptr [0xc318]
01a7 mov bx, word ptr [bp + 4]
01aa mov byte ptr es:[bx + 0x2f62], al
01af mov si, word ptr [bp - 8]
01b2 shl si, 6
01b5 mov bx, word ptr [bp - 0xa]
01b8 mov byte ptr [bx + si + 0x68e8], al
01bc pop si
01bd pop di
01be leave 
01bf ret 
01c0 mov si, word ptr [bp - 4]
01c3 mov al, byte ptr [bp - 6]
01c6 mov cx, si
01c8 xor al, cl
01ca test al, 0x80
01cc je 0x13bc
01ce mov di, word ptr [bp - 0x10]
01d1 mov es, word ptr [0xc318]
01d5 mov bx, word ptr [bp + 4]
01d8 mov al, byte ptr es:[bx + 0x2f62]
01dd sub ah, ah
01df mov word ptr [bp - 4], ax
01e2 xor al, al
01e4 mov byte ptr es:[bx + 0x2f62], al
01e9 mov bx, word ptr [bp - 0xa]
01ec mov si, word ptr [bp - 8]
01ef shl si, 6
01f2 mov byte ptr [bx + si + 0x68e8], al
01f6 push word ptr [bp - 0xe]
01f9 push di
01fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 509, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
01ff add sp, 4
0202 mov si, ax
0204 or si, si
0206 jl 0x147c
0208 push word ptr [bp - 4]
020b mov es, word ptr [0xc318]
020f mov al, byte ptr es:[si + 0x2f62]
0214 sub ah, ah
0216 push ax
0217 call 0x26f4 ; _GetWinner
021a add sp, 4
021d mov es, word ptr [0xc318]
0221 mov cx, ax
0223 and al, 0x80
0225 add al, 0x70
0227 mov byte ptr es:[si + 0x2f62], al
022c mov bx, word ptr [bp - 0x14]
022f mov byte ptr [bx], al
0231 mov byte ptr es:[si + 0x2b78], 0xa
0237 mov byte ptr es:[si + 0x334c], cl
023c push 0x28
023e push word ptr [bp - 0xe]
0241 push di
0242 call 0xffff947e
0245 add sp, 6
0248 pop si
0249 pop di
024a leave 
024b ret 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far FindInAList(int x, int y);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near MeColor;` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandR-fc777553ef.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoDefendNest', 'offset': 3574, 'source': 'src/recovered/wf_DoDefendNest-ed5a5a93f0.c', 'size': 112}
- {'symbol': '_DoRandAntA', 'offset': 3686, 'source': None, 'size': 974}
- {'symbol': '_DoDigOutAntA', 'offset': 5248, 'source': None, 'size': 502}
- {'symbol': '_DoToNestAnt', 'offset': 5750, 'source': None, 'size': 915}

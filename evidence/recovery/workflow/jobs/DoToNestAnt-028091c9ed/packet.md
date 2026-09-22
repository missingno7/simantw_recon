# Recovery task _DoToNestAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 915 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc318]
000a mov bx, word ptr [bp + 4]
000d mov di, word ptr es:[bx + 0x23a4]
0012 and di, 0xff
0016 mov al, byte ptr es:[bx + 0x278e]
001b sub ah, ah
001d mov word ptr [bp - 0x10], ax
0020 mov al, byte ptr es:[bx + 0x2f62]
0025 mov word ptr [bp - 6], ax
0028 push word ptr [bp - 0x10]
002b push di
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 47, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0031 add sp, 4
0034 or ax, ax
0036 jne 0x16b2
0038 xor cx, cx
003a jmp 0x16ed
003c mov es, word ptr [0xc320]
0040 cmp word ptr es:[0x9b6e], 0
0046 jne 0x16d0
0048 mov bx, word ptr [bp - 0x10]
004b mov si, di
004d shl si, 6
0050 cmp byte ptr [bx + si + 0x28e8], 0x50
0055 jne 0x16ae
0057 jmp 0x16ea
0059 nop 
005a mov bx, word ptr [bp - 0x10]
005d mov si, di
005f shl si, 6
0062 mov dl, byte ptr [bx + si + 0x28e8]
0066 sub dh, dh
0068 cmp dx, 0x80
006c jl 0x16ae
006e cmp dx, 0x8f
0072 jg 0x16ae
0074 mov cx, 1
0077 or cx, cx
0079 je 0x16fe
007b push word ptr [bp + 4]
007e push word ptr [bp - 0x10]
0081 push di
0082 call 0x257a ; _GoInNest
0085 jmp 0x1a02
0088 mov al, byte ptr [bp - 6]
008b and ax, 0xf8
008e mov word ptr [bp - 0xc], ax
0091 mov al, byte ptr [bp - 6]
0094 and ax, 0x78
0097 sar ax, 3
009a mov word ptr [bp - 2], ax
009d mov al, byte ptr [bp - 6]
00a0 push word ptr [bp - 6]
00a3 and ax, 7
00a6 mov word ptr [bp - 0x14], ax
00a9 push ax
00aa push word ptr [bp - 0x10]
00ad push di
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNestDir
00b3 add sp, 8
00b6 mov bx, ax
00b8 mov word ptr [bp - 0xe], bx
00bb mov es, word ptr [0xc31e]
00bf mov al, byte ptr es:[bx]
00c4 cwde 
00c5 add ax, di
00c7 mov word ptr [bp - 0x12], ax
00ca mov es, word ptr [0xc31c]
00ce mov cx, ax
00d0 mov al, byte ptr es:[bx + 8]
00d5 cwde 
00d6 add ax, word ptr [bp - 0x10]
00d9 mov word ptr [bp - 0xa], ax
00dc mov si, cx
00de shl si, 6
00e1 mov bx, ax
00e3 mov al, byte ptr [bx + si + 0x28e8]
00e7 sub ah, ah
00e9 mov word ptr [bp - 4], ax
00ec mov es, word ptr [0xc320]
00f0 cmp word ptr es:[0x9b6e], 0
00f6 jne 0x177e
00f8 cmp ax, 0x48
00fb jl 0x1788
00fd cmp ax, 0x4b
0100 jg 0x1788
0102 mov dx, 1
0105 jmp 0x178a
0107 nop 
0108 cmp ax, 0x18
010b jl 0x1788
010d cmp ax, 0x27
0110 jle 0x1778
0112 xor dx, dx
0114 dec dx
0115 jne 0x17e4
0117 cmp word ptr [bp - 2], 6
011b je 0x179c
011d cmp word ptr [bp - 2], 2
0121 je 0x179c
0123 jmp 0x1828
0126 mov si, di
0128 shl si, 6
012b mov al, byte ptr [bp - 0xe]
012e or al, byte ptr [bp - 0xc]
0131 or al, 8
0133 mov es, word ptr [0xc318]
0137 mov bx, word ptr [bp + 4]
013a mov byte ptr es:[bx + 0x2f62], al
013f mov bx, word ptr [bp - 0x10]
0142 mov byte ptr [bx + si + 0x68e8], al
0146 mov bx, word ptr [bp + 4]
0149 mov byte ptr es:[bx + 0x2b78], 3
014f push word ptr [bp - 0xa]
0152 push word ptr [bp - 0x12]
0155 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 344, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PickupFoodA
015a add sp, 4
015d mov es, word ptr [0xc318]
0161 mov bx, word ptr [bp + 4]
0164 mov byte ptr es:[bx + 0x334c], 0xc8
016a pop si
016b pop di
016c leave 
016d ret 
016e mov ax, word ptr [bp - 4]
0171 mov es, word ptr [0xc32c]
0175 cmp word ptr es:[0x7604], ax
017a jge 0x1828
017c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 383, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0181 mov bx, word ptr [bp - 0x14]
0184 shl bx, 3
0187 add bx, ax
0189 mov es, word ptr [0xc32e]
018d mov al, byte ptr es:[bx + 0x24]
0192 or al, byte ptr [bp - 0xc]
0195 mov es, word ptr [0xc318]
0199 mov bx, word ptr [bp + 4]
019c mov byte ptr es:[bx + 0x2f62], al
01a1 mov bx, word ptr [bp - 0x10]
01a4 mov si, di
01a6 shl si, 6
01a9 mov byte ptr [bx + si + 0x68e8], al
01ad pop si
01ae pop di
01af leave 
01b0 ret 
01b1 nop 
01b2 mov si, word ptr [bp - 0x12]
01b5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 438, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01b8 mov es, ax
01ba mov bx, si
01bc shl bx, 6
01bf add bx, word ptr [bp - 0xa]
01c2 add bx, 0x68e8
01c6 mov word ptr [bp - 0x16], bx
01c9 mov al, byte ptr [bx]
01cb sub ah, ah
01cd mov word ptr [bp - 2], ax
01d0 or ax, ax
01d2 jne 0x18b8
01d4 mov al, byte ptr [bp - 0xe]
01d7 or al, byte ptr [bp - 0xc]
01da mov byte ptr [bx], al
01dc mov bx, word ptr [bp + 4]
01df mov byte ptr es:[bx + 0x2f62], al
01e4 mov bx, word ptr [bp - 0x10]
01e7 shl di, 6
01ea mov byte ptr [bx + di + 0x68e8], ah
01ee mov ax, si
01f0 mov bx, word ptr [bp + 4]
01f3 mov byte ptr es:[bx + 0x23a4], al
01f8 mov al, byte ptr [bp - 0xa]
01fb mov byte ptr es:[bx + 0x278e], al
0200 cmp byte ptr es:[bx + 0x334c], 0
0206 jne 0x1881
0208 jmp 0x1a05
020b dec byte ptr es:[bx + 0x334c]
0210 test byte ptr [bp - 6], 0x80
0214 je 0x18a2
0216 mov es, word ptr [0xc318]
021a mov al, byte ptr es:[bx + 0x334c]
021f sub ah, ah
0221 push ax
0222 push word ptr [bp - 0xa]
0225 push si
0226 call 0x94f6 ; _JamScentRN
0229 jmp 0x1a02
022c mov es, word ptr [0xc318]
0230 mov al, byte ptr es:[bx + 0x334c]
0235 sub ah, ah
0237 push ax
0238 push word ptr [bp - 0xa]
023b push si
023c call 0x94b6 ; _JamScentBN
023f jmp 0x1a02
0242 mov word ptr [bp - 8], di
0245 push ax
0246 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 585, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
024b add sp, 2
024e dec ax
024f je 0x18ca
0251 jmp 0x194a
0254 mov al, byte ptr [bp - 6]
0257 xor al, byte ptr [0xce98] ; _MeColor
025b test al, 0x80
025d je 0x18e6
025f push word ptr [bp + 4]
0262 push 1
0264 nop 
0265 push cs
0266 call 0x823e ; _YellowFight
0269 add sp, 4
026c pop si
026d pop di
026e leave 
026f ret 
0270 mov si, word ptr [bp - 0x10]
0273 mov es, word ptr [0xc330]
0277 cmp word ptr es:[0x9af2], 1
027d jne 0x191d
027f mov al, byte ptr [bp - 0xe]
0282 or al, byte ptr [bp - 0xc]
0285 mov es, word ptr [0xc318]
0289 mov bx, word ptr [bp + 4]
028c mov byte ptr es:[bx + 0x2f62], al
0291 mov bx, di
0293 shl bx, 6
0296 mov byte ptr [bx + si + 0x68e8], al
029a push word ptr [bp - 0xe]
029d push si
029e push di
029f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 674, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoTroph
02a4 add sp, 6
02a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 682, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
02ac mov bx, word ptr [bp - 0x14]
02af shl bx, 3
02b2 add bx, ax
02b4 mov es, word ptr [0xc32e]
02b8 mov al, byte ptr es:[bx + 0x24]
02bd or al, byte ptr [bp - 0xc]
02c0 mov es, word ptr [0xc318]
02c4 mov bx, word ptr [bp + 4]
02c7 mov byte ptr es:[bx + 0x2f62], al
02cc mov bx, di
02ce shl bx, 6
02d1 jmp 0x181f
02d4 mov di, word ptr [bp - 6]
02d7 mov al, byte ptr [bp - 2]
02da mov cx, di
02dc xor al, cl
02de test al, 0x80
02e0 jne 0x198a
02e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 741, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
02e7 mov bx, word ptr [bp - 0x14]
02ea shl bx, 3
02ed add bx, ax
02ef mov es, word ptr [0xc32e]
02f3 mov al, byte ptr es:[bx + 0x24]
02f8 or al, byte ptr [bp - 0xc]
02fb mov es, word ptr [0xc318]
02ff mov bx, word ptr [bp + 4]
0302 mov byte ptr es:[bx + 0x2f62], al
0307 mov si, word ptr [bp - 8]
030a shl si, 6
030d mov bx, word ptr [bp - 0x10]
0310 jmp 0x181f
0313 nop 
0314 mov es, word ptr [0xc318]
0318 mov bx, word ptr [bp + 4]
031b mov al, byte ptr es:[bx + 0x2f62]
0320 sub ah, ah
0322 mov word ptr [bp - 2], ax
0325 xor al, al
0327 mov byte ptr es:[bx + 0x2f62], al
032c mov si, word ptr [bp - 8]
032f shl si, 6
0332 mov bx, word ptr [bp - 0x10]
0335 mov byte ptr [bx + si + 0x68e8], al
0339 push word ptr [bp - 0xa]
033c push word ptr [bp - 0x12]
033f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 834, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
0344 add sp, 4
0347 mov si, ax
0349 or si, si
034b jl 0x1a05
034d push word ptr [bp - 2]
0350 mov es, word ptr [0xc318]
0354 mov al, byte ptr es:[si + 0x2f62]
0359 sub ah, ah
035b push ax
035c call 0x26f4 ; _GetWinner
035f add sp, 4
0362 mov cx, ax
0364 and al, 0x80
0366 add al, 0x70
0368 mov es, word ptr [0xc318]
036c mov byte ptr es:[si + 0x2f62], al
0371 mov bx, word ptr [bp - 0x16]
0374 mov byte ptr [bx], al
0376 mov byte ptr es:[si + 0x2b78], 0xa
037c mov byte ptr es:[si + 0x334c], cl
0381 push 0x28
0383 push word ptr [bp - 0xa]
0386 push word ptr [bp - 0x12]
0389 call 0x947e ; _AlarmHere2
038c add sp, 6
038f pop si
0390 pop di
0391 leave 
0392 ret 
```

## Known declaration examples

- `extern void near AlarmHere2(int x, int y, int level);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
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

- {'symbol': '_DoRandAntAA', 'offset': 4660, 'source': None, 'size': 588}
- {'symbol': '_DoDigOutAntA', 'offset': 5248, 'source': None, 'size': 502}
- {'symbol': '_DoToAlarm', 'offset': 6666, 'source': None, 'size': 682}
- {'symbol': '_DoReturnFoodAnt', 'offset': 7348, 'source': None, 'size': 398}

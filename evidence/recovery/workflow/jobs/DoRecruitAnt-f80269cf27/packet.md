# Recovery task _DoRecruitAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 722 bytes.

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
0024 mov word ptr [bp - 0xa], ax
0027 push di
0028 push si
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
002e add sp, 4
0031 or ax, ax
0033 jne 0x22e2
0035 xor cx, cx
0037 jmp 0x2316
0039 nop 
003a mov es, word ptr [0xc320]
003e cmp word ptr es:[0x9b6e], 0
0044 jne 0x22fc
0046 mov bx, si
0048 shl bx, 6
004b cmp byte ptr [bx + di + 0x28e8], 0x50
0050 jne 0x22dd
0052 jmp 0x2313
0054 mov bx, si
0056 shl bx, 6
0059 mov dl, byte ptr [bx + di + 0x28e8]
005d sub dh, dh
005f cmp dx, 0x80
0063 jl 0x22dd
0065 cmp dx, 0x8f
0069 jg 0x22dd
006b mov cx, 1
006e or cx, cx
0070 je 0x2326
0072 push word ptr [bp + 4]
0075 push di
0076 push si
0077 call 0x257a ; _GoInNest
007a jmp 0x2573
007d nop 
007e mov al, byte ptr [bp - 0xa]
0081 and ax, 0xf8
0084 mov word ptr [bp - 0xc], ax
0087 mov es, word ptr [0xc318]
008b mov bx, si
008d and bl, 0xfe
0090 shl bx, 4
0093 mov ax, di
0095 sar ax, 1
0097 add bx, ax
0099 cmp byte ptr es:[bx + 0x52d2], 0
009f je 0x235c
00a1 mov al, byte ptr [bp - 0xa]
00a4 and ax, 7
00a7 mov word ptr [bp - 0x12], ax
00aa push ax
00ab push di
00ac push si
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetAlarmDir
00b2 jmp 0x2387
00b4 cmp word ptr [bp - 0xa], 0x7f
00b8 jle 0x2376
00ba mov al, byte ptr [bp - 0xa]
00bd and ax, 7
00c0 mov word ptr [bp - 0x12], ax
00c3 push ax
00c4 push di
00c5 push si
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetRedDefendDir
00cb jmp 0x2387
00cd nop 
00ce mov al, byte ptr [bp - 0xa]
00d1 and ax, 7
00d4 mov word ptr [bp - 0x12], ax
00d7 push ax
00d8 push di
00d9 push si
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetDefendDir
00df add sp, 6
00e2 mov word ptr [bp - 6], ax
00e5 mov es, word ptr [0xc31c]
00e9 mov bx, ax
00eb mov al, byte ptr es:[bx + 8]
00f0 cwde 
00f1 mov cx, ax
00f3 add cx, di
00f5 mov es, word ptr [0xc31e]
00f9 mov al, byte ptr es:[bx]
00fe cwde 
00ff mov bx, ax
0101 add bx, si
0103 mov word ptr [bp - 0x10], bx
0106 shl bx, 6
0109 add bx, cx
010b mov al, byte ptr [bx + 0x28e8]
010f sub ah, ah
0111 mov es, word ptr [0xc32c]
0115 cmp ax, word ptr es:[0x7604]
011a jle 0x23e6
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0121 or al, byte ptr [bp - 0xc]
0124 mov es, word ptr [0xc318]
0128 mov bx, word ptr [bp + 4]
012b mov byte ptr es:[bx + 0x2f62], al
0130 mov bx, si
0132 shl bx, 6
0135 mov byte ptr [bx + di + 0x68e8], al
0139 pop si
013a pop di
013b leave 
013c ret 
013d nop 
013e mov word ptr [bp - 0xe], cx
0141 mov <resolved loader operand; see bindings> ; [{'operand_offset': 322, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0144 mov es, ax
0146 mov bx, word ptr [bp - 0x10]
0149 shl bx, 6
014c add bx, cx
014e add bx, 0x68e8
0152 mov word ptr [bp - 0x14], bx
0155 mov al, byte ptr [bx]
0157 sub ah, ah
0159 mov word ptr [bp - 8], ax
015c or ax, ax
015e jne 0x2438
0160 mov al, byte ptr [bp - 6]
0163 or al, byte ptr [bp - 0xc]
0166 mov byte ptr [bx], al
0168 mov bx, word ptr [bp + 4]
016b mov byte ptr es:[bx + 0x2f62], al
0170 mov bx, si
0172 shl bx, 6
0175 mov byte ptr [bx + di + 0x68e8], ah
0179 mov bx, word ptr [bp + 4]
017c mov al, byte ptr [bp - 0x10]
017f mov byte ptr es:[bx + 0x23a4], al
0184 mov al, byte ptr [bp - 0xe]
0187 mov byte ptr es:[bx + 0x278e], al
018c pop si
018d pop di
018e leave 
018f ret 
0190 push ax
0191 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0196 add sp, 2
0199 or ax, ax
019b je 0x24b0
019d mov al, byte ptr [bp - 0xa]
01a0 xor al, byte ptr [0xce98] ; _MeColor
01a4 test al, 0x80
01a6 je 0x2462
01a8 push word ptr [bp + 4]
01ab push 1
01ad nop 
01ae push cs
01af call 0x823e ; _YellowFight
01b2 add sp, 4
01b5 pop si
01b6 pop di
01b7 leave 
01b8 ret 
01b9 nop 
01ba mov es, word ptr [0xc330]
01be cmp word ptr es:[0x9af2], 0
01c4 je 0x2496
01c6 mov al, byte ptr [bp - 6]
01c9 or al, byte ptr [bp - 0xc]
01cc mov es, word ptr [0xc318]
01d0 mov bx, word ptr [bp + 4]
01d3 mov byte ptr es:[bx + 0x2f62], al
01d8 mov bx, si
01da shl bx, 6
01dd mov byte ptr [bx + di + 0x68e8], al
01e1 push word ptr [bp - 6]
01e4 push di
01e5 push si
01e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 489, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoTroph
01eb add sp, 6
01ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 497, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01f3 mov bx, word ptr [bp - 0x12]
01f6 shl bx, 3
01f9 add bx, ax
01fb mov es, word ptr [0xc32e]
01ff mov al, byte ptr es:[bx + 0x24]
0204 jmp 0x23c9
0207 nop 
0208 mov word ptr [bp - 4], di
020b mov word ptr [bp - 2], si
020e mov si, word ptr [bp - 0xa]
0211 mov al, byte ptr [bp - 8]
0214 mov cx, si
0216 xor al, cl
0218 test al, 0x80
021a jne 0x24fc
021c mov di, word ptr [bp - 0xc]
021f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 546, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0224 mov bx, word ptr [bp - 0x12]
0227 shl bx, 3
022a add bx, ax
022c mov es, word ptr [0xc32e]
0230 mov ax, di
0232 or al, byte ptr es:[bx + 0x24]
0237 mov es, word ptr [0xc318]
023b mov bx, word ptr [bp + 4]
023e mov byte ptr es:[bx + 0x2f62], al
0243 mov si, word ptr [bp - 2]
0246 shl si, 6
0249 mov bx, word ptr [bp - 4]
024c mov byte ptr [bx + si + 0x68e8], al
0250 pop si
0251 pop di
0252 leave 
0253 ret 
0254 mov di, word ptr [bp - 0xe]
0257 mov es, word ptr [0xc318]
025b mov bx, word ptr [bp + 4]
025e mov al, byte ptr es:[bx + 0x2f62]
0263 sub ah, ah
0265 mov word ptr [bp - 6], ax
0268 xor al, al
026a mov byte ptr es:[bx + 0x2f62], al
026f mov bx, word ptr [bp - 4]
0272 mov si, word ptr [bp - 2]
0275 shl si, 6
0278 mov byte ptr [bx + si + 0x68e8], al
027c push di
027d push word ptr [bp - 0x10]
0280 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 643, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
0285 add sp, 4
0288 mov si, ax
028a or si, si
028c jl 0x2576
028e push word ptr [bp - 6]
0291 mov es, word ptr [0xc318]
0295 mov al, byte ptr es:[si + 0x2f62]
029a sub ah, ah
029c push ax
029d call 0x26f4 ; _GetWinner
02a0 add sp, 4
02a3 mov es, word ptr [0xc318]
02a7 mov cx, ax
02a9 and al, 0x80
02ab add al, 0x70
02ad mov byte ptr es:[si + 0x2f62], al
02b2 mov bx, word ptr [bp - 0x14]
02b5 mov byte ptr [bx], al
02b7 mov byte ptr es:[si + 0x2b78], 0xa
02bd mov byte ptr es:[si + 0x334c], cl
02c2 push 0x28
02c4 push di
02c5 push word ptr [bp - 0x10]
02c8 call 0x947e ; _AlarmHere2
02cb add sp, 6
02ce pop si
02cf pop di
02d0 leave 
02d1 ret 
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

- {'symbol': '_DoReturnFoodAnt', 'offset': 7348, 'source': None, 'size': 398}
- {'symbol': '_DoForageAnt', 'offset': 7746, 'source': None, 'size': 1126}
- {'symbol': '_GoInNest', 'offset': 9594, 'source': None, 'size': 240}
- {'symbol': '_StartFightA', 'offset': 9834, 'source': 'src/recovered/wf_StartFightA-b2f3e31b2f.c', 'size': 137}

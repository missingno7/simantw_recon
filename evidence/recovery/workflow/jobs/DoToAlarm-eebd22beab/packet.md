# Recovery task _DoToAlarm

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 682 bytes.

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
0033 jne 0x1a44
0035 xor cx, cx
0037 jmp 0x1a78
0039 nop 
003a mov es, word ptr [0xc320]
003e cmp word ptr es:[0x9b6e], 0
0044 jne 0x1a5e
0046 mov bx, si
0048 shl bx, 6
004b cmp byte ptr [bx + di + 0x28e8], 0x50
0050 jne 0x1a3f
0052 jmp 0x1a75
0054 mov bx, si
0056 shl bx, 6
0059 mov dl, byte ptr [bx + di + 0x28e8]
005d sub dh, dh
005f cmp dx, 0x80
0063 jl 0x1a3f
0065 cmp dx, 0x8f
0069 jg 0x1a3f
006b mov cx, 1
006e or cx, cx
0070 je 0x1a88
0072 push word ptr [bp + 4]
0075 push di
0076 push si
0077 call 0x257a ; _GoInNest
007a jmp 0x1cad
007d nop 
007e mov al, byte ptr [bp - 4]
0081 and ax, 0xf8
0084 mov word ptr [bp - 8], ax
0087 mov es, word ptr [0xc318]
008b mov bx, si
008d and bl, 0xfe
0090 shl bx, 4
0093 mov ax, di
0095 sar ax, 1
0097 add bx, ax
0099 cmp byte ptr es:[bx + 0x52d2], 0
009f jne 0x1aee
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
00a6 or ax, ax
00a8 jne 0x1aee
00aa mov es, word ptr [0xc318]
00ae mov bx, word ptr [bp + 4]
00b1 mov al, byte ptr es:[bx + 0x2f62]
00b6 mov bx, si
00b8 shl bx, 6
00bb mov byte ptr [bx + di + 0x68e8], al
00bf mov al, byte ptr [bp - 4]
00c2 push word ptr [bp - 4]
00c5 and ax, 0x78
00c8 sar ax, 3
00cb push ax
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
00d1 add sp, 4
00d4 mov bx, word ptr [bp + 4]
00d7 mov es, word ptr [0xc318]
00db mov byte ptr es:[bx + 0x2b78], al
00e0 pop si
00e1 pop di
00e2 leave 
00e3 ret 
00e4 mov al, byte ptr [bp - 4]
00e7 and ax, 7
00ea mov word ptr [bp - 0x12], ax
00ed push ax
00ee push di
00ef push si
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetAlarmDir
00f5 add sp, 6
00f8 mov bx, ax
00fa mov word ptr [bp - 2], bx
00fd mov es, word ptr [0xc31e]
0101 mov al, byte ptr es:[bx]
0106 cwde 
0107 add ax, si
0109 mov word ptr [bp - 0x10], ax
010c mov es, word ptr [0xc31c]
0110 mov cx, ax
0112 mov al, byte ptr es:[bx + 8]
0117 cwde 
0118 add ax, di
011a mov word ptr [bp - 0xe], ax
011d mov bx, cx
011f shl bx, 6
0122 add bx, ax
0124 mov al, byte ptr [bx + 0x28e8]
0128 sub ah, ah
012a mov es, word ptr [0xc32c]
012e cmp ax, word ptr es:[0x7604]
0133 jle 0x1b72
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 312, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
013a mov bx, word ptr [bp - 0x12]
013d shl bx, 3
0140 add bx, ax
0142 mov es, word ptr [0xc32e]
0146 mov al, byte ptr es:[bx + 0x24]
014b or al, byte ptr [bp - 8]
014e mov es, word ptr [0xc318]
0152 mov bx, word ptr [bp + 4]
0155 mov byte ptr es:[bx + 0x2f62], al
015a mov bx, si
015c shl bx, 6
015f mov byte ptr [bx + di + 0x68e8], al
0163 pop si
0164 pop di
0165 leave 
0166 ret 
0167 nop 
0168 mov <resolved loader operand; see bindings> ; [{'operand_offset': 361, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
016b mov es, ax
016d mov bx, cx
016f shl bx, 6
0172 add bx, word ptr [bp - 0xe]
0175 add bx, 0x68e8
0179 mov word ptr [bp - 0x14], bx
017c mov al, byte ptr [bx]
017e sub ah, ah
0180 mov word ptr [bp - 6], ax
0183 or ax, ax
0185 jne 0x1bc2
0187 mov al, byte ptr [bp - 2]
018a or al, byte ptr [bp - 8]
018d mov byte ptr [bx], al
018f mov bx, word ptr [bp + 4]
0192 mov byte ptr es:[bx + 0x2f62], al
0197 mov bx, si
0199 shl bx, 6
019c mov byte ptr [bx + di + 0x68e8], ah
01a0 mov bx, word ptr [bp + 4]
01a3 mov al, byte ptr [bp - 0x10]
01a6 mov byte ptr es:[bx + 0x23a4], al
01ab mov al, byte ptr [bp - 0xe]
01ae mov byte ptr es:[bx + 0x278e], al
01b3 pop si
01b4 pop di
01b5 leave 
01b6 ret 
01b7 nop 
01b8 mov word ptr [bp - 0xc], di
01bb mov word ptr [bp - 0xa], si
01be push ax
01bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 450, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
01c4 add sp, 2
01c7 dec ax
01c8 jne 0x1c28
01ca mov al, byte ptr [bp - 4]
01cd xor al, byte ptr [0xce98] ; _MeColor
01d1 test al, 0x80
01d3 je 0x1bf0
01d5 push word ptr [bp + 4]
01d8 push 1
01da nop 
01db push cs
01dc call 0x823e ; _YellowFight
01df add sp, 4
01e2 pop si
01e3 pop di
01e4 leave 
01e5 ret 
01e6 mov di, word ptr [bp - 8]
01e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 492, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01ee mov bx, word ptr [bp - 0x12]
01f1 shl bx, 3
01f4 add bx, ax
01f6 mov es, word ptr [0xc32e]
01fa mov ax, di
01fc or al, byte ptr es:[bx + 0x24]
0201 mov es, word ptr [0xc318]
0205 mov bx, word ptr [bp + 4]
0208 mov byte ptr es:[bx + 0x2f62], al
020d mov si, word ptr [bp - 0xa]
0210 shl si, 6
0213 mov bx, word ptr [bp - 0xc]
0216 mov byte ptr [bx + si + 0x68e8], al
021a pop si
021b pop di
021c leave 
021d ret 
021e mov si, word ptr [bp - 4]
0221 mov al, byte ptr [bp - 6]
0224 mov cx, si
0226 xor al, cl
0228 test al, 0x80
022a je 0x1bf0
022c mov di, word ptr [bp - 0x10]
022f mov es, word ptr [0xc318]
0233 mov bx, word ptr [bp + 4]
0236 mov al, byte ptr es:[bx + 0x2f62]
023b sub ah, ah
023d mov word ptr [bp - 4], ax
0240 xor al, al
0242 mov byte ptr es:[bx + 0x2f62], al
0247 mov bx, word ptr [bp - 0xc]
024a mov si, word ptr [bp - 0xa]
024d shl si, 6
0250 mov byte ptr [bx + si + 0x68e8], al
0254 push word ptr [bp - 0xe]
0257 push di
0258 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 603, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
025d add sp, 4
0260 mov si, ax
0262 or si, si
0264 jl 0x1cb0
0266 push word ptr [bp - 4]
0269 mov es, word ptr [0xc318]
026d mov al, byte ptr es:[si + 0x2f62]
0272 sub ah, ah
0274 push ax
0275 call 0x26f4 ; _GetWinner
0278 add sp, 4
027b mov es, word ptr [0xc318]
027f mov cx, ax
0281 and al, 0x80
0283 add al, 0x70
0285 mov byte ptr es:[si + 0x2f62], al
028a mov bx, word ptr [bp - 0x14]
028d mov byte ptr [bx], al
028f mov byte ptr es:[si + 0x2b78], 0xa
0295 mov byte ptr es:[si + 0x334c], cl
029a push 0x28
029c push word ptr [bp - 0xe]
029f push di
02a0 call 0x947e ; _AlarmHere2
02a3 add sp, 6
02a6 pop si
02a7 pop di
02a8 leave 
02a9 ret 
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
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
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

- {'symbol': '_DoDigOutAntA', 'offset': 5248, 'source': None, 'size': 502}
- {'symbol': '_DoToNestAnt', 'offset': 5750, 'source': None, 'size': 915}
- {'symbol': '_DoReturnFoodAnt', 'offset': 7348, 'source': None, 'size': 398}
- {'symbol': '_DoForageAnt', 'offset': 7746, 'source': None, 'size': 1126}

# Recovery task _DoAttackAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 640 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc318]
000a mov bx, word ptr [bp + 4]
000d mov al, byte ptr es:[bx + 0x23a4]
0012 sub ah, ah
0014 mov word ptr [bp - 2], ax
0017 mov al, byte ptr es:[bx + 0x278e]
001c mov word ptr [bp - 4], ax
001f mov di, word ptr es:[bx + 0x2f62]
0024 and di, 0xff
0028 push ax
0029 push word ptr [bp - 2]
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 47, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0031 add sp, 4
0034 or ax, ax
0036 jne 0x2a7c
0038 xor cx, cx
003a jmp 0x2ab8
003c mov es, word ptr [0xc320]
0040 cmp word ptr es:[0x9b6e], 0
0046 jne 0x2a9a
0048 mov bx, word ptr [bp - 4]
004b mov si, word ptr [bp - 2]
004e shl si, 6
0051 cmp byte ptr [bx + si + 0x28e8], 0x50
0056 jne 0x2a78
0058 jmp 0x2ab5
005a mov bx, word ptr [bp - 4]
005d mov si, word ptr [bp - 2]
0060 shl si, 6
0063 mov dl, byte ptr [bx + si + 0x28e8]
0067 sub dh, dh
0069 cmp dx, 0x80
006d jl 0x2a78
006f cmp dx, 0x8f
0073 jg 0x2a78
0075 mov cx, 1
0078 or cx, cx
007a je 0x2acc
007c push word ptr [bp + 4]
007f push word ptr [bp - 4]
0082 push word ptr [bp - 2]
0085 call 0x257a ; _GoInNest
0088 jmp 0x2cb9
008b nop 
008c mov es, word ptr [0xc34a]
0090 mov si, di
0092 and si, 0x78
0095 sar si, 3
0098 mov bx, si
009a shl bx, 1
009c cmp word ptr es:[bx + 0x74], 1
00a2 jne 0x2afb
00a4 mov es, word ptr [0xc34c]
00a8 mov al, byte ptr es:[si + 0x94]
00ad cwde 
00ae shl ax, 3
00b1 mov cx, di
00b3 and cx, 0x87
00b7 or ax, cx
00b9 mov di, ax
00bb mov ax, di
00bd and ax, 0xf8
00c0 mov word ptr [bp - 0xc], ax
00c3 mov ax, di
00c5 xor al, 0x80
00c7 push ax
00c8 mov ax, di
00ca and ax, 7
00cd mov word ptr [bp - 0x12], ax
00d0 push ax
00d1 push word ptr [bp - 4]
00d4 push word ptr [bp - 2]
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNestDir
00dc add sp, 8
00df mov si, ax
00e1 mov es, word ptr [0xc31e]
00e5 mov al, byte ptr es:[si]
00ea cwde 
00eb add ax, word ptr [bp - 2]
00ee mov word ptr [bp - 0xe], ax
00f1 mov es, word ptr [0xc31c]
00f5 mov cx, ax
00f7 mov al, byte ptr es:[si + 8]
00fc cwde 
00fd add ax, word ptr [bp - 4]
0100 mov word ptr [bp - 0x10], ax
0103 mov bx, cx
0105 shl bx, 6
0108 add bx, ax
010a mov al, byte ptr [bx + 0x28e8]
010e sub ah, ah
0110 mov es, word ptr [0xc32c]
0114 cmp ax, word ptr es:[0x7604]
0119 jle 0x2b92
011b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 286, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0120 mov bx, word ptr [bp - 0x12]
0123 shl bx, 3
0126 add bx, ax
0128 mov es, word ptr [0xc32e]
012c mov al, byte ptr es:[bx + 0x24]
0131 or al, byte ptr [bp - 0xc]
0134 mov es, word ptr [0xc318]
0138 mov bx, word ptr [bp + 4]
013b mov byte ptr es:[bx + 0x2f62], al
0140 mov si, word ptr [bp - 2]
0143 shl si, 6
0146 mov bx, word ptr [bp - 4]
0149 mov byte ptr [bx + si + 0x68e8], al
014d pop si
014e pop di
014f leave 
0150 ret 
0151 nop 
0152 mov word ptr [bp - 0xa], di
0155 mov word ptr [bp - 6], si
0158 mov si, word ptr [bp - 0x10]
015b mov cx, word ptr [bp - 6]
015e mov <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0161 mov es, ax
0163 mov bx, word ptr [bp - 0xe]
0166 shl bx, 6
0169 add bx, si
016b add bx, 0x68e8
016f mov word ptr [bp - 0x14], bx
0172 mov al, byte ptr [bx]
0174 sub ah, ah
0176 mov word ptr [bp - 8], ax
0179 or ax, ax
017b jne 0x2bee
017d or cl, byte ptr [bp - 0xc]
0180 mov byte ptr [bx], cl
0182 mov bx, word ptr [bp + 4]
0185 mov byte ptr es:[bx + 0x2f62], cl
018a mov bx, word ptr [bp - 4]
018d mov di, word ptr [bp - 2]
0190 shl di, 6
0193 mov byte ptr [bx + di + 0x68e8], ah
0197 mov bx, word ptr [bp + 4]
019a mov al, byte ptr [bp - 0xe]
019d mov byte ptr es:[bx + 0x23a4], al
01a2 mov ax, si
01a4 mov byte ptr es:[bx + 0x278e], al
01a9 pop si
01aa pop di
01ab leave 
01ac ret 
01ad nop 
01ae push ax
01af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 434, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
01b4 add sp, 2
01b7 dec ax
01b8 jne 0x2c34
01ba mov al, byte ptr [bp - 0xa]
01bd xor al, byte ptr [0xce98] ; _MeColor
01c1 test al, 0x80
01c3 je 0x2c16
01c5 push word ptr [bp + 4]
01c8 push 1
01ca nop 
01cb push cs
01cc call 0x823e ; _YellowFight
01cf add sp, 4
01d2 pop si
01d3 pop di
01d4 leave 
01d5 ret 
01d6 mov si, word ptr [bp - 0xc]
01d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 476, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01de mov bx, word ptr [bp - 0x12]
01e1 shl bx, 3
01e4 add bx, ax
01e6 mov es, word ptr [0xc32e]
01ea mov ax, si
01ec or al, byte ptr es:[bx + 0x24]
01f1 jmp 0x2b74
01f4 mov al, byte ptr [bp - 8]
01f7 mov cx, di
01f9 xor al, cl
01fb test al, 0x80
01fd je 0x2c16
01ff mov di, word ptr [bp - 0xe]
0202 mov es, word ptr [0xc318]
0206 mov bx, word ptr [bp + 4]
0209 mov al, byte ptr es:[bx + 0x2f62]
020e sub ah, ah
0210 mov word ptr [bp - 6], ax
0213 xor al, al
0215 mov byte ptr es:[bx + 0x2f62], al
021a mov bx, word ptr [bp - 4]
021d mov si, word ptr [bp - 2]
0220 shl si, 6
0223 mov byte ptr [bx + si + 0x68e8], al
0227 push word ptr [bp - 0x10]
022a push di
022b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 558, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
0230 add sp, 4
0233 mov si, ax
0235 or si, si
0237 jl 0x2cbc
0239 push word ptr [bp - 6]
023c mov es, word ptr [0xc318]
0240 mov al, byte ptr es:[si + 0x2f62]
0245 sub ah, ah
0247 push ax
0248 call 0x26f4 ; _GetWinner
024b add sp, 4
024e mov es, word ptr [0xc318]
0252 mov word ptr [bp - 2], ax
0255 mov cx, ax
0257 and al, 0x80
0259 add al, 0x70
025b mov byte ptr es:[si + 0x2f62], al
0260 mov bx, word ptr [bp - 0x14]
0263 mov byte ptr [bx], al
0265 mov byte ptr es:[si + 0x2b78], 0xa
026b mov byte ptr es:[si + 0x334c], cl
0270 push 0x28
0272 push word ptr [bp - 0x10]
0275 push di
0276 call 0x947e ; _AlarmHere2
0279 add sp, 6
027c pop si
027d pop di
027e leave 
027f ret 
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

- {'symbol': '_DeadAntHere', 'offset': 10432, 'source': None, 'size': 353}
- {'symbol': '_RandTurn', 'offset': 10786, 'source': 'src/recovered/RandTurn.c', 'size': 30}
- {'symbol': '_IsItHole', 'offset': 11456, 'source': None, 'size': 89}
- {'symbol': '_IsItFood', 'offset': 11546, 'source': 'src/recovered/wf_IsItFood-c02f58780a.c', 'size': 51}

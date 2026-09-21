# Recovery task _DoFoodInB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 678 bytes.

```asm
0000 enter 0x1c, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c mov al, byte ptr [bp + 0xa]
000f and ax, 7
0012 push ax
0013 push di
0014 push si
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirB
001a add sp, 6
001d mov word ptr [bp - 8], ax
0020 or ax, ax
0022 jge 0x4951
0024 jmp 0x4af0
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
002c or ax, ax
002e jne 0x495d
0030 jmp 0x4af0
0033 mov bx, si
0035 shl bx, 6
0038 mov al, byte ptr [bp + 0xa]
003b and ax, 0xf8
003e or ax, word ptr [bp - 8]
0041 mov word ptr [bp - 0xc], ax
0044 mov byte ptr [bx + di - 0x7718], al
0048 mov bx, 0x9b6a
004b mov es, word ptr [0xc350]
004f mov word ptr [bp - 0x10], bx
0052 mov word ptr [bp - 0xe], es
0055 mov bx, word ptr es:[bx]
0058 mov es, word ptr [0xc352]
005c mov byte ptr es:[bx + 0x3d18], al
0061 mov es, word ptr [0xc366]
0065 mov bx, word ptr [bp - 8]
0068 mov al, byte ptr es:[bx]
006d cwde 
006e add ax, si
0070 mov word ptr [bp - 4], ax
0073 mov es, word ptr [0xc364]
0077 mov al, byte ptr es:[bx + 8]
007c cwde 
007d mov cx, ax
007f add cx, di
0081 cmp word ptr [bp - 4], 0x3f
0085 jle 0x49b4
0087 jmp 0x4bcc
008a cmp word ptr [bp - 4], 0
008e jge 0x49bd
0090 jmp 0x4bcc
0093 cmp cx, 0x3f
0096 jle 0x49c5
0098 jmp 0x4bcc
009b cmp cx, 1
009e jge 0x49d8
00a0 push si
00a1 nop 
00a2 push cs
00a3 call 0x520a ; _GetOutB
00a6 add sp, 2
00a9 pop si
00aa pop di
00ab leave 
00ac retf 
00ad nop 
00ae mov word ptr [bp - 2], cx
00b1 mov di, word ptr [bp - 4]
00b4 mov dx, word ptr [bp + 8]
00b7 mov bx, di
00b9 shl bx, 6
00bc add bx, cx
00be mov word ptr [bp - 0x12], bx
00c1 cmp byte ptr [bx + 0x48e8], 0x30
00c6 jb 0x49f5
00c8 jmp 0x4bcc
00cb shl si, 6
00ce mov bx, dx
00d0 mov byte ptr [bx + si - 0x7718], 0
00d5 mov bx, word ptr [bp - 0x12]
00d8 test byte ptr [bx - 0x7718], 0x80
00dd jne 0x4a0c
00df jmp 0x4abb
00e2 mov al, byte ptr [bx - 0x7718]
00e6 sub ah, ah
00e8 push ax
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
00ee add sp, 2
00f1 or ax, ax
00f3 je 0x4a29
00f5 cmp word ptr [0xce98], 0 ; _MeColor
00fa jne 0x4a29
00fc jmp 0x4abb
00ff mov bx, word ptr [bp - 0x12]
0102 mov al, byte ptr [bx - 0x7718]
0106 sub ah, ah
0108 mov si, ax
010a push si
010b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0110 add sp, 2
0113 dec ax
0114 jne 0x4a5c
0116 cmp word ptr [0xce98], 0 ; _MeColor
011b je 0x4a5c
011d les bx, ptr [bp - 0x10]
0120 push word ptr es:[bx]
0123 push 2
0125 nop 
0126 push cs
0127 call 0x823e ; _YellowFight
012a add sp, 4
012d mov si, 1
0130 jmp 0x4ab4
0132 cmp si, 0x87
0136 jle 0x4ab2
0138 cmp si, 0xe8
013c jge 0x4ab2
013e push si
013f push word ptr [bp - 2]
0142 push di
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0148 add sp, 6
014b mov word ptr [bp - 6], ax
014e or ax, ax
0150 jl 0x4ab2
0152 push word ptr [bp - 0xc]
0155 push si
0156 call 0x26f4 ; _GetWinner
0159 add sp, 4
015c mov es, word ptr [0xc352]
0160 mov bx, word ptr [bp - 6]
0163 mov byte ptr es:[bx + 0x3f0e], al
0168 and al, 0x80
016a add al, 0x70
016c mov byte ptr es:[bx + 0x3d18], al
0171 mov si, word ptr [bp - 0x12]
0174 mov byte ptr [si - 0x7718], al
0178 mov byte ptr es:[bx + 0x3b22], 0xa
017e mov word ptr [bp - 0xa], 1
0183 mov si, word ptr [bp - 0xa]
0186 jmp 0x4ab4
0188 xor si, si
018a or si, si
018c je 0x4abb
018e jmp 0x4bcc
0191 les bx, ptr [bp - 0x10]
0194 mov bx, word ptr es:[bx]
0197 mov es, word ptr [0xc352]
019b mov cl, byte ptr es:[bx + 0x3d18]
01a0 and cx, 0xf8
01a4 or cx, word ptr [bp - 8]
01a7 mov byte ptr es:[bx + 0x3d18], cl
01ac mov si, word ptr [bp - 0x12]
01af mov byte ptr [si - 0x7718], cl
01b3 mov ax, di
01b5 mov byte ptr es:[bx + 0x3736], al
01ba mov al, byte ptr [bp - 2]
01bd mov byte ptr es:[bx + 0x392c], al
01c2 pop si
01c3 pop di
01c4 leave 
01c5 retf 
01c6 mov di, si
01c8 mov si, word ptr [bp + 8]
01cb mov bx, di
01cd shl bx, 6
01d0 add bx, si
01d2 add bx, 0x48e8
01d6 mov word ptr [bp - 0x14], bx
01d9 mov dl, byte ptr [bx]
01db sub dh, dh
01dd cmp dx, 0x10
01e0 jge 0x4b12
01e2 mov byte ptr [bx], 0x10
01e5 jmp 0x4b19
01e7 nop 
01e8 cmp dx, 0x13
01eb jge 0x4b19
01ed inc byte ptr [bx]
01ef mov bx, 0x9ea4
01f2 mov es, word ptr [0xc362]
01f6 mov word ptr [bp - 0x18], bx
01f9 mov word ptr [bp - 0x16], es
01fc inc word ptr es:[bx]
01ff mov bx, 0x9b6a
0202 mov es, word ptr [0xc350]
0206 mov word ptr [bp - 0x10], bx
0209 mov word ptr [bp - 0xe], es
020c mov bx, word ptr es:[bx]
020f add bx, 0x3d18
0213 mov es, word ptr [0xc352]
0217 test byte ptr es:[bx], 8
021b je 0x4b4b
021d sub byte ptr es:[bx], 8
0221 push 0x64
0223 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 550, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0228 add sp, 2
022b cmp ax, word ptr [0xac86] ; _HealthB
022f jle 0x4bab
0231 mov bx, word ptr [bp - 0x14]
0234 cmp byte ptr [bx], 0x10
0237 jne 0x4b70
0239 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 572, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
023e mov bx, word ptr [bp - 0x14]
0241 mov byte ptr [bx], al
0243 jmp 0x4b72
0245 nop 
0246 dec byte ptr [bx]
0248 les bx, ptr [bp - 0x18]
024b cmp word ptr es:[bx], 0
024f jle 0x4b7e
0251 dec word ptr es:[bx]
0254 mov ax, word ptr [0xac82] ; _BpopT
0257 add ax, word ptr [0xac98]
025b sar ax, 4
025e mov es, word ptr [0xc374]
0262 add word ptr es:[0x7402], 5
0268 cmp ax, word ptr es:[0x7402]
026d jge 0x4bab
026f mov word ptr es:[0x7402], 0
0276 cmp word ptr [0xac86], 0x64 ; _HealthB
027b jge 0x4bab
027d inc word ptr [0xac86] ; _HealthB
0281 mov al, byte ptr [bp + 0xa]
0284 and ax, 0x78
0287 sar ax, 3
028a push ax
028b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 654, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
0290 add sp, 2
0293 les bx, ptr [bp - 0x10]
0296 mov bx, word ptr es:[bx]
0299 mov es, word ptr [0xc352]
029d mov byte ptr es:[bx + 0x3b22], al
02a2 pop si
02a3 pop di
02a4 leave 
02a5 retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near BpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int far GetNewModeB(int mode);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near MeColor;` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
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

- {'symbol': '_StealFoodB', 'offset': 18612, 'source': None, 'size': 67}
- {'symbol': '_DecEatB', 'offset': 18680, 'source': 'src/recovered/DecEatB.c', 'size': 50}
- {'symbol': '_DoDigInB', 'offset': 19408, 'source': None, 'size': 735}
- {'symbol': '_DoDigOutB', 'offset': 20144, 'source': None, 'size': 686}

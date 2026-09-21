# Recovery task _DoDigOutB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 686 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov al, byte ptr [bp + 0xa]
0009 and ax, 7
000c push ax
000d push word ptr [bp + 8]
0010 push word ptr [bp + 6]
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirB
0018 add sp, 6
001b mov si, ax
001d or si, si
001f jle 0x4ed4
0021 dec si
0022 jmp 0x4ee3
0024 mov al, byte ptr [bp + 0xa]
0027 and ax, 7
002a push ax
002b call 0x2a22 ; _RandTurn
002e add sp, 2
0031 mov si, ax
0033 mov al, byte ptr [bp + 0xa]
0036 and ax, 0xf8
0039 or ax, si
003b mov word ptr [bp - 0xc], ax
003e mov bx, word ptr [bp + 6]
0041 shl bx, 6
0044 add bx, word ptr [bp + 8]
0047 mov word ptr [bp - 0xe], bx
004a mov byte ptr [bx - 0x7718], al
004e mov bx, 0x9b6a
0051 mov es, word ptr [0xc350]
0055 mov word ptr [bp - 0x12], bx
0058 mov word ptr [bp - 0x10], es
005b mov bx, word ptr es:[bx]
005e mov es, word ptr [0xc352]
0062 mov byte ptr es:[bx + 0x3d18], al
0067 mov es, word ptr [0xc366]
006b mov al, byte ptr es:[si]
0070 cwde 
0071 add ax, word ptr [bp + 6]
0074 mov word ptr [bp - 2], ax
0077 mov es, word ptr [0xc364]
007b mov al, byte ptr es:[si + 8]
0080 cwde 
0081 mov di, ax
0083 add di, word ptr [bp + 8]
0086 cmp word ptr [bp - 2], 0
008a jge 0x4f3f
008c jmp 0x515a
008f mov word ptr [bp - 0xa], si
0092 cmp word ptr [bp - 2], 0x3f
0096 jle 0x4f4b
0098 jmp 0x515a
009b cmp di, 0x3f
009e jle 0x4f53
00a0 jmp 0x515a
00a3 cmp di, 1
00a6 jge 0x4f68
00a8 push word ptr [bp + 6]
00ab nop 
00ac push cs
00ad call 0x520a ; _GetOutB
00b0 add sp, 2
00b3 pop si
00b4 pop di
00b5 leave 
00b6 retf 
00b7 nop 
00b8 mov si, word ptr [bp - 2]
00bb mov bx, si
00bd shl bx, 6
00c0 add bx, di
00c2 mov word ptr [bp - 0x14], bx
00c5 cmp byte ptr [bx + 0x48e8], 0x30
00ca jb 0x4fd2
00cc mov es, word ptr [0xc352]
00d0 mov bx, word ptr [bp - 0xe]
00d3 dec byte ptr es:[bx + 0x3a4]
00d8 mov cl, byte ptr [bp + 0xa]
00db and cx, 0x78
00de sar cx, 3
00e1 cmp cx, 5
00e4 je 0x4f9b
00e6 cmp cx, 9
00e9 jne 0x4fb1
00eb les bx, ptr [bp - 0x12]
00ee mov bx, word ptr es:[bx]
00f1 mov es, word ptr [0xc352]
00f5 sub byte ptr es:[bx + 0x3d18], 0x18
00fb mov byte ptr es:[bx + 0x3b22], 4
0101 cmp cx, 2
0104 je 0x4fbe
0106 cmp cx, 6
0109 je 0x4fbe
010b jmp 0x515a
010e les bx, ptr [bp - 0x12]
0111 mov bx, word ptr es:[bx]
0114 mov es, word ptr [0xc352]
0118 mov byte ptr es:[bx + 0x3b22], 4
011e pop si
011f pop di
0120 leave 
0121 retf 
0122 mov al, byte ptr [bx + 0x48e8]
0126 sub ah, ah
0128 push ax
0129 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 300, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDirt
012e add sp, 2
0131 or ax, ax
0133 je 0x4fe8
0135 jmp 0x515a
0138 mov bx, word ptr [bp - 0xe]
013b mov byte ptr [bx - 0x7718], 0
0140 mov bx, word ptr [bp - 0x14]
0143 test byte ptr [bx - 0x7718], 0x80
0148 jne 0x4ffd
014a jmp 0x50b4
014d mov al, byte ptr [bx - 0x7718]
0151 sub ah, ah
0153 push ax
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0159 add sp, 2
015c or ax, ax
015e je 0x501a
0160 cmp word ptr [0xce98], 0 ; _MeColor
0165 jne 0x501a
0167 jmp 0x50b4
016a mov bx, word ptr [bp - 0x14]
016d mov al, byte ptr [bx - 0x7718]
0171 sub ah, ah
0173 mov word ptr [bp - 4], ax
0176 push ax
0177 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 378, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
017c add sp, 2
017f dec ax
0180 jne 0x5050
0182 cmp word ptr [0xce98], 0 ; _MeColor
0187 je 0x5050
0189 les bx, ptr [bp - 0x12]
018c push word ptr es:[bx]
018f push 2
0191 nop 
0192 push cs
0193 call 0x823e ; _YellowFight
0196 add sp, 4
0199 mov word ptr [bp - 8], 1
019e jmp 0x50ab
01a0 cmp word ptr [bp - 4], 0x87
01a5 jle 0x50a6
01a7 cmp word ptr [bp - 4], 0xe8
01ac jge 0x50a6
01ae push word ptr [bp - 4]
01b1 push di
01b2 push si
01b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 438, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
01b8 add sp, 6
01bb mov word ptr [bp - 6], ax
01be or ax, ax
01c0 jl 0x50a6
01c2 push word ptr [bp - 0xc]
01c5 push word ptr [bp - 4]
01c8 call 0x26f4 ; _GetWinner
01cb add sp, 4
01ce mov es, word ptr [0xc352]
01d2 mov bx, word ptr [bp - 6]
01d5 mov byte ptr es:[bx + 0x3f0e], al
01da and al, 0x80
01dc add al, 0x70
01de mov byte ptr es:[bx + 0x3d18], al
01e3 mov bx, word ptr [bp - 0x14]
01e6 mov byte ptr [bx - 0x7718], al
01ea mov bx, word ptr [bp - 6]
01ed mov byte ptr es:[bx + 0x3b22], 0xa
01f3 jmp 0x5049
01f5 nop 
01f6 mov word ptr [bp - 8], 0
01fb cmp word ptr [bp - 8], 0
01ff je 0x50b4
0201 jmp 0x515a
0204 les bx, ptr [bp - 0x12]
0207 mov bx, word ptr es:[bx]
020a mov es, word ptr [0xc352]
020e mov al, byte ptr es:[bx + 0x3d18]
0213 mov cx, bx
0215 mov bx, word ptr [bp - 0x14]
0218 and al, 0xf8
021a or al, byte ptr [bp - 0xa]
021d mov byte ptr [bx - 0x7718], al
0221 mov bx, cx
0223 mov byte ptr es:[bx + 0x3d18], al
0228 mov ax, si
022a mov byte ptr es:[bx + 0x3736], al
022f mov ax, di
0231 mov byte ptr es:[bx + 0x392c], al
0236 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 569, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
023b cmp ax, word ptr [0xac86] ; _HealthB
023f jle 0x515a
0241 mov bx, word ptr [bp - 0x14]
0244 mov dl, byte ptr [bx + 0x48e8]
0248 sub dh, dh
024a cmp dx, 0x10
024d jl 0x515a
024f cmp dx, 0x13
0252 jg 0x515a
0254 cmp dx, 0x10
0257 jne 0x5118
0259 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 604, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
025e mov bx, word ptr [bp - 0x14]
0261 mov byte ptr [bx + 0x48e8], al
0265 jmp 0x511c
0267 nop 
0268 dec byte ptr [bx + 0x48e8]
026c mov es, word ptr [0xc362]
0270 cmp word ptr es:[0x9ea4], 0
0276 jle 0x512d
0278 dec word ptr es:[0x9ea4]
027d mov ax, word ptr [0xac82] ; _BpopT
0280 add ax, word ptr [0xac98]
0284 sar ax, 4
0287 mov es, word ptr [0xc374]
028b add word ptr es:[0x7402], 5
0291 cmp ax, word ptr es:[0x7402]
0296 jge 0x515a
0298 mov word ptr es:[0x7402], 0
029f cmp word ptr [0xac86], 0x64 ; _HealthB
02a4 jge 0x515a
02a6 inc word ptr [0xac86] ; _HealthB
02aa pop si
02ab pop di
02ac leave 
02ad retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near BpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int far GetExitDirB(int x, int y, int limit);` — src/recovered/wf_RaidOutB-794c50ee5a.c
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
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
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

- {'symbol': '_DoFoodInB', 'offset': 18730, 'source': None, 'size': 678}
- {'symbol': '_DoDigInB', 'offset': 19408, 'source': None, 'size': 735}
- {'symbol': '_LeaveNestB', 'offset': 20830, 'source': None, 'size': 172}
- {'symbol': '_GetOutB', 'offset': 21002, 'source': None, 'size': 314}

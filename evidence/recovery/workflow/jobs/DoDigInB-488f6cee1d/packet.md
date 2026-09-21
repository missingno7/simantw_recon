# Recovery task _DoDigInB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 735 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 0xc], 2
000a je 0x4c04
000c cmp word ptr [bp + 0xc], 6
0010 je 0x4c04
0012 push word ptr [bp + 0xc]
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
001a add sp, 2
001d mov es, word ptr [0xc350]
0021 mov bx, word ptr es:[0x9b6a]
0026 mov es, word ptr [0xc352]
002a mov byte ptr es:[bx + 0x3b22], al
002f pop si
0030 pop di
0031 leave 
0032 retf 
0033 nop 
0034 mov si, word ptr [bp + 8]
0037 mov al, byte ptr [bp + 0xa]
003a and ax, 7
003d push ax
003e push si
003f push word ptr [bp + 6]
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirB
0047 add sp, 6
004a mov di, ax
004c or di, di
004e jge 0x4c27
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0055 mov di, ax
0057 mov bx, word ptr [bp + 6]
005a shl bx, 6
005d mov al, byte ptr [bp + 0xa]
0060 and ax, 0xf8
0063 or ax, di
0065 mov word ptr [bp - 0xc], ax
0068 mov byte ptr [bx + si - 0x7718], al
006c mov bx, 0x9b6a
006f mov es, word ptr [0xc350]
0073 mov word ptr [bp - 0x10], bx
0076 mov word ptr [bp - 0xe], es
0079 mov bx, word ptr es:[bx]
007c mov es, word ptr [0xc352]
0080 mov byte ptr es:[bx + 0x3d18], al
0085 cmp si, 0x3f
0088 jne 0x4c6e
008a push word ptr [bp + 0xc]
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
0092 add sp, 2
0095 les bx, ptr [bp - 0x10]
0098 mov bx, word ptr es:[bx]
009b jmp 0x4bf6
009d nop 
009e mov word ptr [bp - 0xa], di
00a1 mov cx, di
00a3 mov es, word ptr [0xc364]
00a7 mov bx, di
00a9 mov al, byte ptr es:[bx + 8]
00ae cwde 
00af mov si, ax
00b1 add si, word ptr [bp + 8]
00b4 mov es, word ptr [0xc366]
00b8 mov al, byte ptr es:[bx]
00bd cwde 
00be mov di, ax
00c0 add di, word ptr [bp + 6]
00c3 cmp di, 0x3f
00c6 jle 0x4c9b
00c8 jmp 0x4eab
00cb or di, di
00cd jge 0x4ca2
00cf jmp 0x4eab
00d2 cmp si, 0x3f
00d5 jle 0x4caa
00d7 jmp 0x4eab
00da cmp si, 1
00dd jge 0x4cbe
00df push word ptr [bp + 6]
00e2 nop 
00e3 push cs
00e4 call 0x520a ; _GetOutB
00e7 add sp, 2
00ea pop si
00eb pop di
00ec leave 
00ed retf 
00ee mov bx, di
00f0 shl bx, 6
00f3 add bx, si
00f5 mov word ptr [bp - 0x12], bx
00f8 mov al, byte ptr [bx + 0x48e8]
00fc sub ah, ah
00fe mov word ptr [bp - 2], ax
0101 cmp ax, 0x30
0104 jl 0x4cd9
0106 jmp 0x4eab
0109 mov word ptr [bp - 6], si
010c mov word ptr [bp - 8], di
010f push ax
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDirt
0115 add sp, 2
0118 or ax, ax
011a je 0x4d21
011c push si
011d push di
011e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 289, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileThemB
0123 add sp, 4
0126 or ax, ax
0128 jne 0x4cfd
012a jmp 0x4c5a
012d les bx, ptr [bp - 0x10]
0130 mov bx, word ptr es:[bx]
0133 mov es, word ptr [0xc352]
0137 add byte ptr es:[bx + 0x3d18], 0x18
013d mov byte ptr es:[bx + 0x3b22], 5
0143 push 0
0145 push 0
0147 push 0x11
0149 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 332, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
014e add sp, 6
0151 mov si, word ptr [bp + 6]
0154 shl si, 6
0157 mov bx, word ptr [bp + 8]
015a mov byte ptr [bx + si - 0x7718], 0
015f mov bx, word ptr [bp - 0x12]
0162 test byte ptr [bx - 0x7718], 0x80
0167 jne 0x4d3c
0169 jmp 0x4ded
016c mov al, byte ptr [bx - 0x7718]
0170 sub ah, ah
0172 push ax
0173 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 374, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0178 add sp, 2
017b or ax, ax
017d je 0x4d59
017f cmp word ptr [0xce98], 0 ; _MeColor
0184 jne 0x4d59
0186 jmp 0x4ded
0189 mov bx, word ptr [bp - 0x12]
018c mov si, word ptr [bx - 0x7718]
0190 and si, 0xff
0194 push si
0195 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 408, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
019a add sp, 2
019d dec ax
019e jne 0x4d8c
01a0 cmp word ptr [0xce98], 0 ; _MeColor
01a5 je 0x4d8c
01a7 les bx, ptr [bp - 0x10]
01aa push word ptr es:[bx]
01ad push 2
01af nop 
01b0 push cs
01b1 call 0x823e ; _YellowFight
01b4 add sp, 4
01b7 mov si, 1
01ba jmp 0x4de6
01bc cmp si, 0x87
01c0 jle 0x4de4
01c2 cmp si, 0xe8
01c6 jge 0x4de4
01c8 push si
01c9 push word ptr [bp - 6]
01cc push di
01cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 464, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
01d2 add sp, 6
01d5 mov word ptr [bp - 2], ax
01d8 or ax, ax
01da jl 0x4de4
01dc mov di, word ptr [bp - 0xc]
01df push di
01e0 push si
01e1 call 0x26f4 ; _GetWinner
01e4 add sp, 4
01e7 mov es, word ptr [0xc352]
01eb mov bx, word ptr [bp - 2]
01ee mov byte ptr es:[bx + 0x3f0e], al
01f3 and al, 0x80
01f5 add al, 0x70
01f7 mov byte ptr es:[bx + 0x3d18], al
01fc mov si, word ptr [bp - 0x12]
01ff mov byte ptr [si - 0x7718], al
0203 mov byte ptr es:[bx + 0x3b22], 0xa
0209 mov word ptr [bp - 4], 1
020e mov si, word ptr [bp - 4]
0211 jmp 0x4de6
0213 nop 
0214 xor si, si
0216 or si, si
0218 je 0x4ded
021a jmp 0x4eab
021d les bx, ptr [bp - 0x10]
0220 mov bx, word ptr es:[bx]
0223 mov es, word ptr [0xc352]
0227 mov al, byte ptr es:[bx + 0x3d18]
022c and ax, 0xf8
022f mov si, ax
0231 or si, word ptr [bp - 0xa]
0234 mov ax, si
0236 mov byte ptr es:[bx + 0x3d18], al
023b mov si, word ptr [bp - 0x12]
023e mov byte ptr [si - 0x7718], al
0242 mov al, byte ptr [bp - 8]
0245 mov byte ptr es:[bx + 0x3736], al
024a mov al, byte ptr [bp - 6]
024d mov byte ptr es:[bx + 0x392c], al
0252 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 597, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
0257 cmp ax, word ptr [0xac86] ; _HealthB
025b jle 0x4e94
025d mov bx, si
025f mov dl, byte ptr [bx + 0x48e8]
0263 sub dh, dh
0265 cmp dx, 0x10
0268 jl 0x4e94
026a cmp dx, 0x13
026d jg 0x4e94
026f cmp dx, 0x10
0272 jne 0x4e52
0274 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 631, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0279 mov bx, si
027b mov byte ptr [bx + 0x48e8], al
027f jmp 0x4e56
0281 nop 
0282 dec byte ptr [bx + 0x48e8]
0286 mov es, word ptr [0xc362]
028a cmp word ptr es:[0x9ea4], 0
0290 jle 0x4e67
0292 dec word ptr es:[0x9ea4]
0297 mov ax, word ptr [0xac82] ; _BpopT
029a add ax, word ptr [0xac98]
029e sar ax, 4
02a1 mov es, word ptr [0xc374]
02a5 add word ptr es:[0x7402], 5
02ab cmp ax, word ptr es:[0x7402]
02b0 jge 0x4e94
02b2 mov word ptr es:[0x7402], 0
02b9 cmp word ptr [0xac86], 0x64 ; _HealthB
02be jge 0x4e94
02c0 inc word ptr [0xac86] ; _HealthB
02c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 711, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
02c9 or ax, ax
02cb jne 0x4eab
02cd push word ptr [bp - 6]
02d0 push word ptr [bp - 8]
02d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 726, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FixExitMapB
02d8 add sp, 4
02db pop si
02dc pop di
02dd leave 
02de retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near BpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far DigTileThemB(int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
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
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DecEatB', 'offset': 18680, 'source': 'src/recovered/DecEatB.c', 'size': 50}
- {'symbol': '_DoFoodInB', 'offset': 18730, 'source': None, 'size': 678}
- {'symbol': '_DoDigOutB', 'offset': 20144, 'source': None, 'size': 686}
- {'symbol': '_LeaveNestB', 'offset': 20830, 'source': None, 'size': 172}

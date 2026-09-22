# Recovery task _DoNestingB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 797 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xc]
0009 mov di, word ptr [bp + 6]
000c mov al, byte ptr [bp + 0xa]
000f and ax, 7
0012 mov word ptr [bp - 8], ax
0015 mov word ptr [bp - 2], ax
0018 mov es, word ptr [0xc350]
001c mov bx, word ptr es:[0x9b6a]
0021 mov es, word ptr [0xc352]
0025 mov al, byte ptr es:[bx + 0x3f0e]
002a mov cx, ax
002c and ax, 7
002f mov word ptr [bp - 6], ax
0032 mov bx, di
0034 shl bx, 6
0037 add bx, word ptr [bp + 8]
003a mov word ptr [bp - 0xa], bx
003d mov al, byte ptr [bx - 0x7718]
0041 mov byte ptr [bp - 4], al
0044 shr cl, 3
0047 mov byte ptr [bp - 3], cl
004a mov ax, si
004c dec ax
004d jne 0x44fa
004f jmp 0x45a2
0052 dec ax
0053 jne 0x4500
0055 jmp 0x4664
0058 push 0x64
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
005f add sp, 2
0062 cmp ax, word ptr [0xac86] ; _HealthB
0066 jle 0x4578
0068 mov bx, word ptr [bp - 0xa]
006b mov dl, byte ptr [bx + 0x48e8]
006f sub dh, dh
0071 cmp dx, 0x10
0074 jl 0x4578
0076 cmp dx, 0x13
0079 jg 0x4578
007b cmp dx, 0x10
007e jne 0x4536
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0085 mov bx, word ptr [bp - 0xa]
0088 mov byte ptr [bx + 0x48e8], al
008c jmp 0x453a
008e dec byte ptr [bx + 0x48e8]
0092 mov es, word ptr [0xc362]
0096 cmp word ptr es:[0x9ea4], 0
009c jle 0x454b
009e dec word ptr es:[0x9ea4]
00a3 mov ax, word ptr [0xac82] ; _BpopT
00a6 add ax, word ptr [0xac98]
00aa sar ax, 4
00ad mov es, word ptr [0xc374]
00b1 add word ptr es:[0x7402], 5
00b7 cmp ax, word ptr es:[0x7402]
00bc jge 0x4578
00be mov word ptr es:[0x7402], 0
00c5 cmp word ptr [0xac86], 0x64 ; _HealthB
00ca jge 0x4578
00cc inc word ptr [0xac86] ; _HealthB
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00d5 or ax, ax
00d7 je 0x4584
00d9 jmp 0x479c
00dc push si
00dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 224, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
00e2 add sp, 2
00e5 mov es, word ptr [0xc350]
00e9 mov bx, word ptr es:[0x9b6a]
00ee mov es, word ptr [0xc352]
00f2 mov byte ptr es:[bx + 0x3b22], al
00f7 jmp 0x479c
00fa cmp byte ptr [bp - 3], 0
00fe jne 0x45dc
0100 push word ptr [bp - 8]
0103 push word ptr [bp + 8]
0106 push di
0107 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 266, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirB
010c add sp, 6
010f mov word ptr [bp - 2], ax
0112 or ax, ax
0114 jl 0x45c1
0116 jmp 0x479c
0119 mov al, byte ptr [bp - 6]
011c or al, 8
011e mov es, word ptr [0xc350]
0122 mov bx, word ptr es:[0x9b6a]
0127 mov es, word ptr [0xc352]
012b mov byte ptr es:[bx + 0x3f0e], al
0130 jmp 0x479c
0133 nop 
0134 cmp byte ptr [bp - 4], 0
0138 je 0x45e8
013a cmp byte ptr [bp - 4], 8
013e jbe 0x4648
0140 mov es, word ptr [0xc350]
0144 mov bx, word ptr es:[0x9b6a]
0149 mov es, word ptr [0xc352]
014d add byte ptr es:[bx + 0x3d18], 8
0153 push word ptr [bp - 6]
0156 push word ptr [bp + 8]
0159 push di
015a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 349, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PlaceEggB
015f add sp, 6
0162 mov es, word ptr [0xc350]
0166 mov bx, word ptr es:[0x9b6a]
016b mov es, word ptr [0xc352]
016f mov al, byte ptr es:[bx + 0x3d18]
0174 mov cx, bx
0176 mov bx, word ptr [bp - 0xa]
0179 mov byte ptr [bx - 0x7718], al
017d mov bx, cx
017f mov byte ptr es:[bx + 0x3f0e], 8
0185 push si
0186 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 393, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
018b add sp, 2
018e mov es, word ptr [0xc350]
0192 mov bx, word ptr es:[0x9b6a]
0197 mov es, word ptr [0xc352]
019b mov byte ptr es:[bx + 0x3b22], al
01a0 push word ptr [bp - 8]
01a3 push word ptr [bp + 8]
01a6 push di
01a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 426, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirB
01ac add sp, 6
01af mov si, ax
01b1 or si, si
01b3 je 0x469b
01b5 dec si
01b6 mov word ptr [bp - 2], si
01b9 jmp 0x479c
01bc cmp byte ptr [bp - 3], 0
01c0 je 0x46a4
01c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 453, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01c7 or ax, ax
01c9 jne 0x4686
01cb mov es, word ptr [0xc350]
01cf mov bx, word ptr es:[0x9b6a]
01d4 mov es, word ptr [0xc352]
01d8 mov byte ptr es:[bx + 0x3f0e], 0
01de push word ptr [bp - 8]
01e1 push word ptr [bp + 8]
01e4 push di
01e5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 488, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirB
01ea add sp, 6
01ed mov si, ax
01ef or si, si
01f1 jne 0x465d
01f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 502, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01f8 jmp 0x4799
01fb nop 
01fc cmp byte ptr [bp - 4], 0
0200 je 0x46f4
0202 cmp byte ptr [bp - 4], 8
0206 jae 0x46f4
0208 mov al, byte ptr [bp - 4]
020b sub ah, ah
020d push ax
020e push word ptr [bp + 8]
0211 push di
0212 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 533, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0217 add sp, 6
021a mov si, ax
021c or si, si
021e jge 0x46cb
0220 jmp 0x4796
0223 mov <resolved loader operand; see bindings> ; [{'operand_offset': 548, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0226 mov es, ax
0228 mov byte ptr es:[si + 0x3d18], 0
022e mov <resolved loader operand; see bindings> ; [{'operand_offset': 559, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0231 mov ds, ax
0233 mov bx, word ptr [0x9b6a]
0237 sub byte ptr es:[bx + 0x3d18], 8
023d mov al, byte ptr [bp - 4]
0240 mov byte ptr es:[bx + 0x3f0e], al
0245 push ss
0246 pop ds
0247 pop si
0248 pop di
0249 leave 
024a retf 
024b nop 
024c push 0x64
024e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 593, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0253 add sp, 2
0256 cmp ax, word ptr [0xac86] ; _HealthB
025a jle 0x4772
025c mov bx, word ptr [bp - 0xa]
025f mov dl, byte ptr [bx + 0x48e8]
0263 sub dh, dh
0265 cmp dx, 0x10
0268 jge 0x4715
026a jmp 0x4796
026d cmp dx, 0x13
0270 jg 0x4796
0272 cmp dx, 0x10
0275 jne 0x472e
0277 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 634, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
027c mov bx, word ptr [bp - 0xa]
027f mov byte ptr [bx + 0x48e8], al
0283 jmp 0x4732
0285 nop 
0286 dec byte ptr [bx + 0x48e8]
028a mov es, word ptr [0xc362]
028e cmp word ptr es:[0x9ea4], 0
0294 jle 0x4743
0296 dec word ptr es:[0x9ea4]
029b mov ax, word ptr [0xac82] ; _BpopT
029e add ax, word ptr [0xac98]
02a2 sar ax, 4
02a5 mov es, word ptr [0xc374]
02a9 add word ptr es:[0x7402], 5
02af cmp ax, word ptr es:[0x7402]
02b4 jge 0x4796
02b6 mov word ptr es:[0x7402], 0
02bd cmp word ptr [0xac86], 0x64 ; _HealthB
02c2 jge 0x4796
02c4 inc word ptr [0xac86] ; _HealthB
02c8 jmp 0x4796
02ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 717, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
02cf or ax, ax
02d1 jne 0x4796
02d3 push si
02d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 727, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
02d9 add sp, 2
02dc mov es, word ptr [0xc350]
02e0 mov bx, word ptr es:[0x9b6a]
02e5 mov es, word ptr [0xc352]
02e9 mov byte ptr es:[bx + 0x3b22], al
02ee mov ax, word ptr [bp - 8]
02f1 mov word ptr [bp - 2], ax
02f4 push word ptr [bp - 2]
02f7 push word ptr [bp + 8]
02fa push di
02fb nop 
02fc push cs
02fd call 0x439e ; _TryMoveDirB
0300 add sp, 6
0303 or ax, ax
0305 jne 0x47c1
0307 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 778, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
030c push ax
030d push word ptr [bp + 8]
0310 push di
0311 nop 
0312 push cs
0313 call 0x439e ; _TryMoveDirB
0316 add sp, 6
0319 pop si
031a pop di
031b leave 
031c retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near BpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int far GetExitDirB(int x, int y, int limit);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far GetNewModeB(int mode);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LostTailB', 'offset': 17212, 'source': None, 'size': 98}
- {'symbol': '_TryMoveDirB', 'offset': 17310, 'source': None, 'size': 266}
- {'symbol': '_TryEatFoodB', 'offset': 18374, 'source': None, 'size': 126}
- {'symbol': '_EatFoodB', 'offset': 18500, 'source': None, 'size': 112}

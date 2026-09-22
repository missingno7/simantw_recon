# Recovery task _DoNestingR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 557 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov al, byte ptr [bp + 0xa]
0009 and ax, 7
000c mov word ptr [bp - 4], ax
000f mov word ptr [bp - 2], ax
0012 cmp word ptr [bp + 0xc], 1
0016 je 0x6925
0018 jmp 0x69d2
001b mov si, word ptr [bp + 6]
001e mov di, word ptr [bp + 8]
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0026 or ax, ax
0028 jne 0x69a6
002a mov bx, si
002c shl bx, 6
002f add bx, di
0031 mov word ptr [bp - 6], bx
0034 cmp byte ptr [bx + 0x58e8], 0x10
0039 jae 0x69a6
003b mov es, word ptr [0xc384]
003f mov bx, word ptr es:[0x9b6a]
0044 mov es, word ptr [0xc386]
0048 add byte ptr es:[bx + 0x46e6], 8
004e mov al, byte ptr es:[bx + 0x46e6]
0053 mov bx, word ptr [bp - 6]
0056 mov byte ptr [bx - 0x6718], al
005a push 0x82
005d push di
005e push si
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PlaceEggR
0064 add sp, 6
0067 mov es, word ptr [0xc384]
006b mov bx, word ptr es:[0x9b6a]
0070 mov es, word ptr [0xc386]
0074 mov byte ptr es:[bx + 0x48dc], 0
007a push word ptr [bp + 0xc]
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
0082 add sp, 2
0085 mov es, word ptr [0xc384]
0089 mov bx, word ptr es:[0x9b6a]
008e mov es, word ptr [0xc386]
0092 mov byte ptr es:[bx + 0x44f0], al
0097 pop si
0098 pop di
0099 leave 
009a retf 
009b nop 
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
00a1 or ax, ax
00a3 je 0x69c6
00a5 push word ptr [bp - 4]
00a8 push di
00a9 push si
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirR
00af add sp, 6
00b2 mov word ptr [bp - 2], ax
00b5 or ax, ax
00b7 jl 0x69c6
00b9 jmp 0x6b0e
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00c1 mov word ptr [bp - 2], ax
00c4 jmp 0x6b0e
00c7 nop 
00c8 cmp word ptr [bp + 0xc], 2
00cc je 0x69db
00ce jmp 0x6aee
00d1 mov si, word ptr [bp + 6]
00d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 215, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
00d9 or ax, ax
00db je 0x69ea
00dd jmp 0x6adb
00e0 mov bx, si
00e2 shl bx, 6
00e5 add bx, word ptr [bp + 8]
00e8 mov word ptr [bp - 6], bx
00eb mov al, byte ptr [bx - 0x6718]
00ef sub ah, ah
00f1 mov word ptr [bp - 2], ax
00f4 or ax, ax
00f6 je 0x6a44
00f8 mov al, byte ptr [bp - 2]
00fb and al, 0x7f
00fd cmp al, 8
00ff jge 0x6a44
0101 push word ptr [bp - 2]
0104 push word ptr [bp + 8]
0107 push si
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
010d add sp, 6
0110 mov di, ax
0112 or di, di
0114 jge 0x6a23
0116 jmp 0x6adb
0119 mov es, word ptr [0xc386]
011d mov byte ptr es:[di + 0x46e6], 0
0123 mov es, word ptr [0xc384]
0127 mov bx, word ptr es:[0x9b6a]
012c mov es, word ptr [0xc386]
0130 sub byte ptr es:[bx + 0x46e6], 8
0136 pop si
0137 pop di
0138 leave 
0139 retf 
013a push 0x64
013c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 319, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0141 add sp, 2
0144 cmp ax, word ptr [0xac88] ; _HealthR
0148 jle 0x6abe
014a mov bx, word ptr [bp - 6]
014d mov dl, byte ptr [bx + 0x58e8]
0151 sub dh, dh
0153 cmp dx, 0x10
0156 jl 0x6adb
0158 cmp dx, 0x13
015b jg 0x6adb
015d cmp dx, 0x10
0160 jne 0x6a7a
0162 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 357, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0167 mov bx, word ptr [bp - 6]
016a mov byte ptr [bx + 0x58e8], al
016e jmp 0x6a7e
0170 dec byte ptr [bx + 0x58e8]
0174 mov es, word ptr [0xc394]
0178 cmp word ptr es:[0x72de], 0
017e jle 0x6a8f
0180 dec word ptr es:[0x72de]
0185 mov ax, word ptr [0xac84] ; _RpopT
0188 add ax, word ptr [0xaca4]
018c sar ax, 4
018f mov es, word ptr [0xc3a4]
0193 add word ptr es:[0x7c8e], 5
0199 cmp ax, word ptr es:[0x7c8e]
019e jge 0x6adb
01a0 mov word ptr es:[0x7c8e], 0
01a7 cmp word ptr [0xac88], 0x64 ; _HealthR
01ac jge 0x6adb
01ae inc word ptr [0xac88] ; _HealthR
01b2 jmp 0x6adb
01b4 push word ptr [bp + 0xc]
01b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 442, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
01bc add sp, 2
01bf mov es, word ptr [0xc384]
01c3 mov bx, word ptr es:[0x9b6a]
01c8 mov es, word ptr [0xc386]
01cc mov byte ptr es:[bx + 0x44f0], al
01d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
01d6 or ax, ax
01d8 jne 0x6ae7
01da jmp 0x69c6
01dd mov ax, word ptr [bp - 4]
01e0 jmp 0x69cb
01e3 nop 
01e4 push word ptr [bp + 0xc]
01e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 490, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
01ec add sp, 2
01ef mov es, word ptr [0xc384]
01f3 mov bx, word ptr es:[0x9b6a]
01f8 mov es, word ptr [0xc386]
01fc mov byte ptr es:[bx + 0x44f0], al
0201 mov si, word ptr [bp + 6]
0204 push word ptr [bp - 2]
0207 push word ptr [bp + 8]
020a push si
020b nop 
020c push cs
020d call 0x6850 ; _TryMoveDirR
0210 add sp, 6
0213 or ax, ax
0215 jne 0x6b33
0217 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 538, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
021c push ax
021d push word ptr [bp + 8]
0220 push si
0221 nop 
0222 push cs
0223 call 0x6850 ; _TryMoveDirR
0226 add sp, 6
0229 pop si
022a pop di
022b leave 
022c retf 
```

## Known declaration examples

- `extern int far FindInRList(int x, int y, int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far GetNewModeR(int mode);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near HealthR;` — src/recovered/DecEatR.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near RpopT;` — src/recovered/DecEatR.c
- `extern int near RpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LostTailR', 'offset': 26606, 'source': None, 'size': 98}
- {'symbol': '_TryMoveDirR', 'offset': 26704, 'source': None, 'size': 186}
- {'symbol': '_TryEatFoodR', 'offset': 27448, 'source': None, 'size': 126}
- {'symbol': '_EatFoodR', 'offset': 27574, 'source': None, 'size': 112}

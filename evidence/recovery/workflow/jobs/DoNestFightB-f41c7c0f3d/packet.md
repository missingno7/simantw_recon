# Recovery task _DoNestFightB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 334 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c push 7
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0013 add sp, 2
0016 mov es, word ptr [0xc350]
001a mov bx, word ptr es:[0x9b6a]
001f mov es, word ptr [0xc352]
0023 mov cl, byte ptr es:[bx + 0x3d18]
0028 and cl, 0xf8
002b add cl, al
002d mov byte ptr es:[bx + 0x3d18], cl
0032 mov al, cl
0034 mov bx, di
0036 shl bx, 6
0039 add bx, si
003b add bx, 0x88e8
003f mov word ptr [bp - 2], bx
0042 mov byte ptr [bx], al
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0049 or ax, ax
004b je 0x3aa4
004d jmp 0x3b86
0050 mov <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0053 mov es, ax
0055 mov <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0058 mov ds, ax
005a mov bx, word ptr [0x9b6a]
005e mov al, byte ptr es:[bx + 0x3f0e]
0063 mov si, word ptr [bp - 2]
0066 mov byte ptr ss:[si], al
0069 mov byte ptr es:[bx + 0x3d18], al
006e and al, 0x78
0070 cmp al, 0x60
0072 jne 0x3b32
0074 push ss
0075 pop ds
0076 push 0
0078 push 9
007a mov es, word ptr [0xc350]
007e mov bx, word ptr es:[0x9b6a]
0083 mov es, word ptr [0xc352]
0087 mov al, byte ptr es:[bx + 0x3d18]
008c mov cx, ax
008e sub ah, ah
0090 add ax, 8
0093 push ax
0094 mov ax, bx
0096 mov bl, cl
0098 mov si, ax
009a mov cl, byte ptr es:[si + 0x392c]
009f and bl, 7
00a2 xor bl, 4
00a5 sub bh, bh
00a7 mov es, word ptr [0xc364]
00ab mov al, byte ptr es:[bx + 8]
00b0 cwde 
00b1 sub ch, ch
00b3 add ax, cx
00b5 push ax
00b6 mov es, word ptr [0xc366]
00ba mov al, byte ptr es:[bx]
00bf cwde 
00c0 mov es, word ptr [0xc352]
00c4 mov cl, byte ptr es:[si + 0x3736]
00c9 add ax, cx
00cb push ax
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
00d1 add sp, 0xa
00d4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00d7 mov es, ax
00d9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00dc mov ds, ax
00de mov bx, word ptr [0x9b6a]
00e2 test byte ptr es:[bx + 0x3d18], 0x80
00e8 je 0x3b4a
00ea mov byte ptr es:[bx + 0x3b22], 7
00f0 push ss
00f1 pop ds
00f2 pop si
00f3 pop di
00f4 leave 
00f5 retf 
00f6 push ss
00f7 pop ds
00f8 mov es, word ptr [0xc350]
00fc mov bx, word ptr es:[0x9b6a]
0101 mov es, word ptr [0xc352]
0105 mov al, byte ptr es:[bx + 0x3d18]
010a and al, 0x78
010c shr al, 3
010f sub ah, ah
0111 mov si, ax
0113 mov al, byte ptr es:[bx + 0x3d18]
0118 push ax
0119 push si
011a mov si, bx
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
0121 add sp, 4
0124 mov es, word ptr [0xc352]
0128 mov byte ptr es:[si + 0x3b22], al
012d pop si
012e pop di
012f leave 
0130 retf 
0131 nop 
0132 mov es, word ptr [0xc358]
0136 cmp word ptr es:[0x85fc], 1
013c jne 0x3b9e
013e push 2
0140 push si
0141 push di
0142 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 325, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _FightBalloons
0147 add sp, 6
014a pop si
014b pop di
014c leave 
014d retf 
```

## Known declaration examples

- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRandB', 'offset': 14454, 'source': 'src/recovered/wf_DoRandB-ce86a18bea.c', 'size': 246}
- {'symbol': '_DoRecruitN', 'offset': 14700, 'source': 'src/recovered/wf_DoRecruitN-cac1aa103b.c', 'size': 232}
- {'symbol': '_CheckNestFightB', 'offset': 15266, 'source': 'src/recovered/wf_CheckNestFightB-6daf29ea80.c', 'size': 154}
- {'symbol': '_DropFoodB', 'offset': 15420, 'source': None, 'size': 100}

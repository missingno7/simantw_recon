# Recovery task _DoNestFightR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 304 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c push 7
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0013 add sp, 2
0016 mov es, word ptr [0xc384]
001a mov bx, word ptr es:[0x9b6a]
001f mov es, word ptr [0xc386]
0023 mov cl, byte ptr es:[bx + 0x46e6]
0028 and cl, 0xf8
002b add cl, al
002d mov byte ptr es:[bx + 0x46e6], cl
0032 mov al, cl
0034 mov bx, di
0036 shl bx, 6
0039 add bx, si
003b add bx, 0x98e8
003f mov word ptr [bp - 2], bx
0042 mov byte ptr [bx], al
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0049 or ax, ax
004b je 0x60c2
004d jmp 0x6186
0050 mov <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0053 mov es, ax
0055 mov <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0058 mov ds, ax
005a mov bx, word ptr [0x9b6a]
005e mov al, byte ptr es:[bx + 0x48dc]
0063 mov si, word ptr [bp - 2]
0066 mov byte ptr ss:[si], al
0069 mov byte ptr es:[bx + 0x46e6], al
006e and al, 0x78
0070 cmp al, 0x60
0072 jne 0x6150
0074 push ss
0075 pop ds
0076 push 0
0078 push 9
007a mov es, word ptr [0xc384]
007e mov bx, word ptr es:[0x9b6a]
0083 mov es, word ptr [0xc386]
0087 mov al, byte ptr es:[bx + 0x46e6]
008c mov cx, ax
008e sub ah, ah
0090 add ax, 8
0093 push ax
0094 mov ax, bx
0096 mov bl, cl
0098 mov si, ax
009a mov cl, byte ptr es:[si + 0x42fa]
009f and bl, 7
00a2 xor bl, 4
00a5 sub bh, bh
00a7 mov es, word ptr [0xc396]
00ab mov al, byte ptr es:[bx + 8]
00b0 cwde 
00b1 sub ch, ch
00b3 add ax, cx
00b5 push ax
00b6 mov es, word ptr [0xc398]
00ba mov al, byte ptr es:[bx]
00bf cwde 
00c0 mov es, word ptr [0xc386]
00c4 mov cl, byte ptr es:[si + 0x4104]
00c9 add ax, cx
00cb push ax
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
00d1 add sp, 0xa
00d4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00d7 mov es, ax
00d9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00dc mov ds, ax
00de mov bx, word ptr [0x9b6a]
00e2 test byte ptr es:[bx + 0x46e6], 0x80
00e8 jne 0x6168
00ea mov byte ptr es:[bx + 0x44f0], 7
00f0 push ss
00f1 pop ds
00f2 pop si
00f3 pop di
00f4 leave 
00f5 retf 
00f6 mov ax, bx
00f8 mov bl, byte ptr es:[bx + 0x46e6]
00fd mov si, ax
00ff and bl, 0x78
0102 shr bl, 3
0105 sub bh, bh
0107 mov cl, byte ptr ss:[bx + 0x22e6]
010c mov byte ptr es:[si + 0x44f0], cl
0111 jmp 0x6162
0113 nop 
0114 mov es, word ptr [0xc38c]
0118 cmp word ptr es:[0x85fc], 0
011e je 0x619e
0120 push 3
0122 push si
0123 push di
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _FightBalloons
0129 add sp, 6
012c pop si
012d pop di
012e leave 
012f retf 
```

## Known declaration examples

- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoDrownR', 'offset': 24232, 'source': None, 'size': 210}
- {'symbol': '_DoRandR', 'offset': 24442, 'source': 'src/recovered/wf_DoRandR-fc777553ef.c', 'size': 248}
- {'symbol': '_CheckNestFightR', 'offset': 24994, 'source': None, 'size': 160}
- {'symbol': '_DropFoodR', 'offset': 25154, 'source': None, 'size': 100}

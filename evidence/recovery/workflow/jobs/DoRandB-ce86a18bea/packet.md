# Recovery task _DoRandB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 246 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
000b or ax, ax
000d jne 0x38a2
000f push word ptr [bp + 0xc]
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
0017 add sp, 2
001a mov es, word ptr [0xc350]
001e mov bx, word ptr es:[0x9b6a]
0023 mov es, word ptr [0xc352]
0027 mov byte ptr es:[bx + 0x3b22], al
002c mov di, word ptr [bp + 6]
002f mov bx, di
0031 shl bx, 6
0034 add bx, word ptr [bp + 8]
0037 add bx, 0x88e8
003b mov word ptr [bp - 6], bx
003e mov al, byte ptr [bx]
0040 sub ah, ah
0042 mov si, ax
0044 push si
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
004a add sp, 2
004d dec ax
004e jne 0x38e6
0050 cmp word ptr [0xce98], 0 ; _MeColor
0055 je 0x38e6
0057 mov es, word ptr [0xc350]
005b push word ptr es:[0x9b6a]
0060 push 2
0062 nop 
0063 push cs
0064 call 0x823e ; _YellowFight
0067 add sp, 4
006a mov si, 1
006d jmp 0x393c
006f nop 
0070 cmp si, 0x87
0074 jle 0x393a
0076 cmp si, 0xe8
007a jge 0x393a
007c push si
007d push word ptr [bp + 8]
0080 push di
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0086 add sp, 6
0089 mov word ptr [bp - 2], ax
008c or ax, ax
008e jl 0x393a
0090 push word ptr [bp + 0xa]
0093 push si
0094 call 0x26f4 ; _GetWinner
0097 add sp, 4
009a mov es, word ptr [0xc352]
009e mov bx, word ptr [bp - 2]
00a1 mov byte ptr es:[bx + 0x3f0e], al
00a6 and al, 0x80
00a8 add al, 0x70
00aa mov byte ptr es:[bx + 0x3d18], al
00af mov si, word ptr [bp - 6]
00b2 mov byte ptr [si], al
00b4 mov byte ptr es:[bx + 0x3b22], 0xa
00ba mov word ptr [bp - 4], 1
00bf mov si, word ptr [bp - 4]
00c2 jmp 0x393c
00c4 xor si, si
00c6 dec si
00c7 je 0x3968
00c9 mov al, byte ptr [bp + 0xa]
00cc and ax, 7
00cf push ax
00d0 push word ptr [bp + 8]
00d3 push di
00d4 nop 
00d5 push cs
00d6 call 0x439e ; _TryMoveDirB
00d9 add sp, 6
00dc or ax, ax
00de jne 0x3968
00e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00e5 push ax
00e6 push word ptr [bp + 8]
00e9 push di
00ea nop 
00eb push cs
00ec call 0x439e ; _TryMoveDirB
00ef add sp, 6
00f2 pop si
00f3 pop di
00f4 leave 
00f5 retf 
```

## Known declaration examples

- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRestB', 'offset': 13950, 'source': None, 'size': 294}
- {'symbol': '_DoDrownB', 'offset': 14244, 'source': None, 'size': 210}
- {'symbol': '_DoRecruitN', 'offset': 14700, 'source': None, 'size': 232}
- {'symbol': '_DoNestFightB', 'offset': 14932, 'source': None, 'size': 334}

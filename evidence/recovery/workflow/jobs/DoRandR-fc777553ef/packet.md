# Recovery task _DoRandR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 248 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
000b or ax, ax
000d jne 0x5fa6
000f push word ptr [bp + 0xc]
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
0017 add sp, 2
001a mov es, word ptr [0xc384]
001e mov bx, word ptr es:[0x9b6a]
0023 mov es, word ptr [0xc386]
0027 mov byte ptr es:[bx + 0x44f0], al
002c mov di, word ptr [bp + 8]
002f mov si, word ptr [bp + 6]
0032 mov bx, si
0034 shl bx, 6
0037 add bx, di
0039 add bx, 0x98e8
003d mov word ptr [bp - 8], bx
0040 mov al, byte ptr [bx]
0042 sub ah, ah
0044 mov word ptr [bp - 2], ax
0047 cmp ax, 7
004a jle 0x6014
004c cmp ax, 0x68
004f jge 0x6014
0051 push ax
0052 push di
0053 push si
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0059 add sp, 6
005c mov word ptr [bp - 6], ax
005f or ax, ax
0061 jl 0x603e
0063 push word ptr [bp + 0xa]
0066 push word ptr [bp - 2]
0069 call 0x26f4 ; _GetWinner
006c add sp, 4
006f mov es, word ptr [0xc386]
0073 mov bx, word ptr [bp - 6]
0076 mov byte ptr es:[bx + 0x48dc], al
007b and al, 0x80
007d add al, 0x70
007f mov byte ptr es:[bx + 0x46e6], al
0084 mov bx, word ptr [bp - 8]
0087 mov byte ptr [bx], al
0089 mov bx, word ptr [bp - 6]
008c mov byte ptr es:[bx + 0x44f0], 0xa
0092 mov word ptr [bp - 4], 1
0097 jmp 0x6043
0099 nop 
009a push ax
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
00a0 add sp, 2
00a3 or ax, ax
00a5 je 0x603e
00a7 cmp word ptr [0xce98], 0 ; _MeColor
00ac jne 0x603e
00ae mov es, word ptr [0xc384]
00b2 push word ptr es:[0x9b6a]
00b7 push 3
00b9 nop 
00ba push cs
00bb call 0x823e ; _YellowFight
00be add sp, 4
00c1 jmp 0x600c
00c3 nop 
00c4 mov word ptr [bp - 4], 0
00c9 cmp word ptr [bp - 4], 0
00cd jne 0x606e
00cf mov al, byte ptr [bp + 0xa]
00d2 and ax, 7
00d5 push ax
00d6 push di
00d7 push si
00d8 nop 
00d9 push cs
00da call 0x6850 ; _TryMoveDirR
00dd add sp, 6
00e0 or ax, ax
00e2 jne 0x606e
00e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00e9 push ax
00ea push di
00eb push si
00ec nop 
00ed push cs
00ee call 0x6850 ; _TryMoveDirR
00f1 add sp, 6
00f4 pop si
00f5 pop di
00f6 leave 
00f7 retf 
```

## Known declaration examples

- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_RaidOutR-a39ba19d03.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRestR', 'offset': 23934, 'source': None, 'size': 298}
- {'symbol': '_DoDrownR', 'offset': 24232, 'source': None, 'size': 210}
- {'symbol': '_DoNestFightR', 'offset': 24690, 'source': None, 'size': 304}
- {'symbol': '_CheckNestFightR', 'offset': 24994, 'source': None, 'size': 160}

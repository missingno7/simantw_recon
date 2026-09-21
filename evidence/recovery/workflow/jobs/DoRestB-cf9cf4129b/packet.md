# Recovery task _DoRestB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 294 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov bx, di
000b shl bx, 6
000e add bx, word ptr [bp + 8]
0011 add bx, 0x88e8
0015 mov word ptr [bp - 6], bx
0018 mov al, byte ptr [bx]
001a sub ah, ah
001c mov si, ax
001e push si
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0024 add sp, 2
0027 dec ax
0028 jne 0x36c8
002a cmp word ptr [0xce98], 0 ; _MeColor
002f je 0x36c8
0031 mov es, word ptr [0xc350]
0035 push word ptr es:[0x9b6a]
003a push 2
003c nop 
003d push cs
003e call 0x823e ; _YellowFight
0041 add sp, 4
0044 mov si, 1
0047 jmp 0x371e
0049 nop 
004a cmp si, 0x87
004e jle 0x371c
0050 cmp si, 0xe8
0054 jge 0x371c
0056 push si
0057 push word ptr [bp + 8]
005a push di
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0060 add sp, 6
0063 mov word ptr [bp - 2], ax
0066 or ax, ax
0068 jl 0x371c
006a push word ptr [bp + 0xa]
006d push si
006e call 0x26f4 ; _GetWinner
0071 add sp, 4
0074 mov es, word ptr [0xc352]
0078 mov bx, word ptr [bp - 2]
007b mov byte ptr es:[bx + 0x3f0e], al
0080 and al, 0x80
0082 add al, 0x70
0084 mov byte ptr es:[bx + 0x3d18], al
0089 mov si, word ptr [bp - 6]
008c mov byte ptr [si], al
008e mov byte ptr es:[bx + 0x3b22], 0xa
0094 mov word ptr [bp - 4], 1
0099 mov si, word ptr [bp - 4]
009c jmp 0x371e
009e xor si, si
00a0 dec si
00a1 je 0x37a0
00a3 mov bx, 0x9b6a
00a6 mov es, word ptr [0xc350]
00aa mov word ptr [bp - 0xa], bx
00ad mov word ptr [bp - 8], es
00b0 mov bx, word ptr es:[bx]
00b3 mov es, word ptr [0xc352]
00b7 mov al, byte ptr es:[bx + 0x3d18]
00bc mov bx, word ptr [bp - 6]
00bf mov byte ptr [bx], al
00c1 push 0x14
00c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 198, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00c8 add sp, 2
00cb or ax, ax
00cd jne 0x3786
00cf les bx, ptr [bp - 0xa]
00d2 mov si, word ptr es:[bx]
00d5 mov es, word ptr [0xc352]
00d9 mov al, byte ptr es:[si + 0x3d18]
00de sub ah, ah
00e0 mov di, ax
00e2 mov si, di
00e4 and si, 0x78
00e7 sar si, 3
00ea push di
00eb push si
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
00f1 add sp, 4
00f4 les bx, ptr [bp - 0xa]
00f7 mov bx, word ptr es:[bx]
00fa mov es, word ptr [0xc352]
00fe mov byte ptr es:[bx + 0x3b22], al
0103 pop si
0104 pop di
0105 leave 
0106 retf 
0107 nop 
0108 mov es, word ptr [0xc358]
010c cmp word ptr es:[0x85fc], 1
0112 jne 0x37a0
0114 push 2
0116 push word ptr [bp + 8]
0119 push di
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 285, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _RestBalloons
011f add sp, 6
0122 pop si
0123 pop di
0124 leave 
0125 retf 
```

## Known declaration examples

- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RaidInB', 'offset': 13604, 'source': None, 'size': 235}
- {'symbol': '_RaidOutB', 'offset': 13840, 'source': 'src/recovered/wf_RaidOutB-794c50ee5a.c', 'size': 110}
- {'symbol': '_DoDrownB', 'offset': 14244, 'source': None, 'size': 210}
- {'symbol': '_DoRandB', 'offset': 14454, 'source': None, 'size': 246}

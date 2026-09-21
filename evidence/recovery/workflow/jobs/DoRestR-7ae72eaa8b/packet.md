# Recovery task _DoRestR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 298 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 mov di, word ptr [bp + 6]
000c mov bx, di
000e shl bx, 6
0011 add bx, si
0013 add bx, 0x98e8
0017 mov word ptr [bp - 8], bx
001a mov al, byte ptr [bx]
001c sub ah, ah
001e mov word ptr [bp - 2], ax
0021 cmp ax, 7
0024 jle 0x5df2
0026 cmp ax, 0x68
0029 jge 0x5df2
002b push ax
002c push si
002d push di
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0033 add sp, 6
0036 mov word ptr [bp - 6], ax
0039 or ax, ax
003b jl 0x5e1c
003d push word ptr [bp + 0xa]
0040 push word ptr [bp - 2]
0043 call 0x26f4 ; _GetWinner
0046 add sp, 4
0049 mov es, word ptr [0xc386]
004d mov bx, word ptr [bp - 6]
0050 mov byte ptr es:[bx + 0x48dc], al
0055 and al, 0x80
0057 add al, 0x70
0059 mov byte ptr es:[bx + 0x46e6], al
005e mov bx, word ptr [bp - 8]
0061 mov byte ptr [bx], al
0063 mov bx, word ptr [bp - 6]
0066 mov byte ptr es:[bx + 0x44f0], 0xa
006c mov word ptr [bp - 4], 1
0071 jmp 0x5e21
0073 nop 
0074 push ax
0075 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 120, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
007a add sp, 2
007d or ax, ax
007f je 0x5e1c
0081 cmp word ptr [0xce98], 0 ; _MeColor
0086 jne 0x5e1c
0088 mov es, word ptr [0xc384]
008c push word ptr es:[0x9b6a]
0091 push 3
0093 nop 
0094 push cs
0095 call 0x823e ; _YellowFight
0098 add sp, 4
009b jmp 0x5dea
009d nop 
009e mov word ptr [bp - 4], 0
00a3 cmp word ptr [bp - 4], 0
00a7 jne 0x5ea4
00a9 mov bx, 0x9b6a
00ac mov es, word ptr [0xc384]
00b0 mov word ptr [bp - 0xc], bx
00b3 mov word ptr [bp - 0xa], es
00b6 mov bx, word ptr es:[bx]
00b9 mov es, word ptr [0xc386]
00bd mov al, byte ptr es:[bx + 0x46e6]
00c2 mov bx, word ptr [bp - 8]
00c5 mov byte ptr [bx], al
00c7 push 0x14
00c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00ce add sp, 2
00d1 or ax, ax
00d3 jne 0x5e8c
00d5 les bx, ptr [bp - 0xc]
00d8 mov si, word ptr es:[bx]
00db mov es, word ptr [0xc386]
00df mov al, byte ptr es:[si + 0x46e6]
00e4 sub ah, ah
00e6 mov di, ax
00e8 mov si, di
00ea and si, 0x78
00ed sar si, 3
00f0 push di
00f1 push si
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
00f7 add sp, 4
00fa les bx, ptr [bp - 0xc]
00fd mov bx, word ptr es:[bx]
0100 mov es, word ptr [0xc386]
0104 mov byte ptr es:[bx + 0x44f0], al
0109 pop si
010a pop di
010b leave 
010c retf 
010d nop 
010e mov es, word ptr [0xc38c]
0112 cmp word ptr es:[0x85fc], 0
0118 je 0x5ea4
011a push 3
011c push si
011d push di
011e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 289, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _RestBalloons
0123 add sp, 6
0126 pop si
0127 pop di
0128 leave 
0129 retf 
```

## Known declaration examples

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

- {'symbol': '_StayInR', 'offset': 23574, 'source': None, 'size': 249}
- {'symbol': '_RaidOutR', 'offset': 23824, 'source': 'src/recovered/wf_RaidOutR-a39ba19d03.c', 'size': 110}
- {'symbol': '_DoDrownR', 'offset': 24232, 'source': None, 'size': 210}
- {'symbol': '_DoRandR', 'offset': 24442, 'source': None, 'size': 248}

# Recovery task _ExitNest

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 477 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _TryAntTheme
000b push 0
000d push word ptr [0xcf50] ; _MeDir
0011 push word ptr [0xcc84] ; _MeType
0015 push word ptr [0xce7e] ; _MeLocY
0019 push word ptr [0xcd88] ; _MeLocX
001d push word ptr [0xce80] ; _MePlane
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0026 add sp, 0xc
0029 mov al, byte ptr [0xcd88] ; _MeLocX
002c and ax, 0x3f
002f mov word ptr [0xce7e], ax ; _MeLocY
0032 cmp word ptr [0xce80], 2 ; _MePlane
0037 jne 0x8506
0039 mov es, word ptr [0xc3e2]
003d mov bx, ax
003f cmp byte ptr es:[bx - 0x7d2e], 0
0045 jne 0x84f7
0047 push word ptr [0xcd88] ; _MeLocX
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleB
0050 add sp, 2
0053 mov es, word ptr [0xc3e2]
0057 mov bx, word ptr [0xce7e] ; _MeLocY
005b mov al, byte ptr es:[bx - 0x7d2e]
0060 jmp 0x852d
0062 mov es, word ptr [0xc3e4]
0066 mov bx, ax
0068 cmp byte ptr es:[bx - 0x7cee], 0
006e jne 0x8520
0070 push word ptr [0xcd88] ; _MeLocX
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleR
0079 add sp, 2
007c mov es, word ptr [0xc3e4]
0080 mov bx, word ptr [0xce7e] ; _MeLocY
0084 mov al, byte ptr es:[bx - 0x7cee]
0089 sub ah, ah
008b mov word ptr [0xcd88], ax ; _MeLocX
008e cmp word ptr [0xcc84], 0x60 ; _MeType
0093 jne 0x853e
0095 mov ax, 2
0098 jmp 0x8541
009a mov ax, 1
009d mov word ptr [bp - 0xa], ax
00a0 mov bx, 0x9be0
00a3 mov es, word ptr [0xc3be]
00a7 mov word ptr [bp - 0xe], bx
00aa mov word ptr [bp - 0xc], es
00ad cmp word ptr es:[bx], 1
00b1 jne 0x8586
00b3 mov es, word ptr [0xc3bc]
00b7 push word ptr es:[0x80d2]
00bc mov es, word ptr [0xc3b8]
00c0 push word ptr es:[0x80c6]
00c5 push word ptr [0xce7e] ; _MeLocY
00c9 push word ptr [0xcd88] ; _MeLocX
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
00d2 add sp, 8
00d5 mov word ptr [bp - 8], ax
00d8 or ax, ax
00da jle 0x85dd
00dc dec word ptr [bp - 8]
00df jmp 0x85dd
00e1 nop 
00e2 mov ax, word ptr [0xce80] ; _MePlane
00e5 les bx, ptr [bp - 0xe]
00e8 cmp word ptr es:[bx], ax
00eb jne 0x85a4
00ed cmp word ptr [0xcd88], 0x40 ; _MeLocX
00f2 jge 0x859e
00f4 mov ax, 2
00f7 jmp 0x85da
00f9 nop 
00fa mov ax, 6
00fd jmp 0x85da
00ff nop 
0100 mov es, word ptr [0xc3bc]
0104 push word ptr es:[0x80d2]
0109 mov es, word ptr [0xc3b8]
010d push word ptr es:[0x80c6]
0112 mov es, word ptr [bp - 0xc]
0115 push word ptr es:[bx]
0118 push word ptr [0xce7e] ; _MeLocY
011c push word ptr [0xcd88] ; _MeLocX
0120 push 1
0122 nop 
0123 push cs
0124 call 0x8eca ; _GetMyDir
0127 add sp, 0xc
012a mov word ptr [bp - 8], ax
012d or ax, ax
012f jge 0x85dd
0131 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 308, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0136 mov word ptr [bp - 8], ax
0139 xor si, si
013b mov es, word ptr [0xc3e6]
013f mov al, byte ptr es:[si + 0x6c]
0144 cwde 
0145 mov di, ax
0147 add di, word ptr [bp - 8]
014a and di, 7
014d mov es, word ptr [0xc3c4]
0151 mov al, byte ptr es:[di + 8]
0156 cwde 
0157 imul word ptr [bp - 0xa]
015a add ax, word ptr [0xce7e] ; _MeLocY
015e mov word ptr [bp - 4], ax
0161 push ax
0162 mov es, word ptr [0xc3ca]
0166 mov al, byte ptr es:[di]
016b cwde 
016c imul word ptr [bp - 0xa]
016f add ax, word ptr [0xcd88] ; _MeLocX
0173 mov word ptr [bp - 6], ax
0176 push ax
0177 push 1
0179 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 380, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsNotObstacle
017e add sp, 6
0181 or ax, ax
0183 jne 0x8632
0185 inc si
0186 cmp si, 8
0189 jl 0x85df
018b jmp 0x8643
018d nop 
018e mov ax, word ptr [bp - 6]
0191 mov word ptr [0xcd88], ax ; _MeLocX
0194 mov ax, word ptr [bp - 4]
0197 mov word ptr [0xce7e], ax ; _MeLocY
019a mov ax, di
019c mov word ptr [0xcf50], ax ; _MeDir
019f cmp si, 8
01a2 jne 0x865b
01a4 mov ax, word ptr [bp - 8]
01a7 mov word ptr [0xcf50], ax ; _MeDir
01aa mov al, byte ptr [bp - 0xa]
01ad add al, byte ptr [0xcd88] ; _MeLocX
01b1 and ax, 0x7f
01b4 mov word ptr [0xcd88], ax ; _MeLocX
01b7 push 0xff
01ba push word ptr [0xcf50] ; _MeDir
01be push word ptr [0xcc84] ; _MeType
01c2 push word ptr [0xce7e] ; _MeLocY
01c6 push word ptr [0xcd88] ; _MeLocX
01ca mov ax, 1
01cd mov word ptr [0xce80], ax ; _MePlane
01d0 push ax
01d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
01d6 add sp, 0xc
01d9 pop si
01da pop di
01db leave 
01dc retf 
```

## Known declaration examples

- `extern void far MakeNewHoleB(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far MakeNewHoleR(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near MeDir;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeDir;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_EnterNest-606488b329.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far TryAntTheme(void);` — src/recovered/wf_EnterNest-606488b329.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_YellowFight', 'offset': 33342, 'source': None, 'size': 457}
- {'symbol': '_EnterNest', 'offset': 33800, 'source': 'src/recovered/wf_EnterNest-606488b329.c', 'size': 155}
- {'symbol': '_GetMyDis', 'offset': 34434, 'source': None, 'size': 421}
- {'symbol': '_GetMyBestDirs', 'offset': 34856, 'source': None, 'size': 256}

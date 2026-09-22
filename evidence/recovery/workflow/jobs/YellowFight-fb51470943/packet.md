# Recovery task _YellowFight

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 457 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 6], 1
000a jg 0x8264
000c mov word ptr [bp - 0xa], 0x23a4
0011 mov <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0016 mov word ptr [bp - 0xe], 0x278e
001b mov <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0020 mov ax, 0x2f62
0023 jmp 0x829b
0025 nop 
0026 cmp word ptr [bp + 6], 2
002a jne 0x8284
002c mov word ptr [bp - 0xa], 0x3736
0031 mov <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0036 mov word ptr [bp - 0xe], 0x392c
003b mov <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0040 mov ax, 0x3d18
0043 jmp 0x829b
0045 nop 
0046 mov word ptr [bp - 0xa], 0x4104
004b mov <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0050 mov word ptr [bp - 0xe], 0x42fa
0055 mov <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
005a mov ax, 0x46e6
005d mov <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0060 mov di, ax
0062 mov word ptr [bp - 4], cx
0065 mov si, word ptr [bp + 8]
0068 mov es, cx
006a mov bx, di
006c add bx, si
006e mov al, byte ptr es:[bx]
0071 sub ah, ah
0073 push ax
0074 mov ax, bx
0076 les bx, ptr [bp - 0xe]
0079 add bx, si
007b mov word ptr [bp - 0x12], bx
007e mov word ptr [bp - 0x10], es
0081 mov cl, byte ptr es:[bx]
0084 sub ch, ch
0086 push cx
0087 les bx, ptr [bp - 0xa]
008a add bx, si
008c mov word ptr [bp - 0x16], bx
008f mov word ptr [bp - 0x14], es
0092 mov cl, byte ptr es:[bx]
0095 push cx
0096 push word ptr [bp + 6]
0099 mov word ptr [bp - 0x18], ax
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearLife
00a1 add sp, 8
00a4 mov es, word ptr [bp - 4]
00a7 mov bx, word ptr [bp - 0x18]
00aa mov al, byte ptr es:[bx]
00ad sub ah, ah
00af push ax
00b0 push word ptr [0xcc84] ; _MeType
00b4 call 0x26f4 ; _GetWinner
00b7 add sp, 4
00ba mov word ptr [bp - 2], ax
00bd mov ax, word ptr [0xcc84] ; _MeType
00c0 cmp word ptr [bp - 2], ax
00c3 je 0x8308
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
00ca push 0
00cc push 0x70
00ce push word ptr [0xcf50] ; _MeDir
00d2 push word ptr [0xce7e] ; _MeLocY
00d6 push word ptr [0xcd88] ; _MeLocX
00da push word ptr [0xce80] ; _MePlane
00de nop 
00df push cs
00e0 call 0x7e56 ; _AnimYellowFight
00e3 add sp, 0xc
00e6 mov ax, word ptr [0xcc84] ; _MeType
00e9 cmp word ptr [bp - 2], ax
00ec je 0x832f
00ee jmp 0x83ba
00f1 push 0xff
00f4 push word ptr [0xcf50] ; _MeDir
00f8 push ax
00f9 push word ptr [0xce7e] ; _MeLocY
00fd push word ptr [0xcd88] ; _MeLocX
0101 push word ptr [0xce80] ; _MePlane
0105 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 264, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
010a add sp, 0xc
010d cmp word ptr [bp + 6], 1
0111 jg 0x8377
0113 mov es, word ptr [bp - 4]
0116 mov bx, di
0118 add bx, si
011a mov al, byte ptr es:[bx]
011d and ax, 0x80
0120 push ax
0121 les bx, ptr [bp - 0x12]
0124 mov al, byte ptr es:[bx]
0127 sub ah, ah
0129 push ax
012a les bx, ptr [bp - 0x16]
012d mov al, byte ptr es:[bx]
0130 push ax
0131 nop 
0132 push cs
0133 call 0x28c0 ; _DeadAntHere
0136 add sp, 6
0139 mov es, word ptr [bp - 4]
013c add di, si
013e mov byte ptr es:[di], 0
0142 mov es, word ptr [0xc3ae]
0146 cmp word ptr es:[0x9bc4], 3
014c jne 0x8403
014e mov ax, word ptr [0xce80] ; _MePlane
0151 mov es, word ptr [0xc3b2]
0155 cmp word ptr es:[0x9c6c], ax
015a jne 0x8403
015c mov es, word ptr [0xc3b0]
0160 cmp word ptr es:[0x99e4], si
0165 jne 0x8403
0167 push word ptr [0xce7e] ; _MeLocY
016b push word ptr [0xcd88] ; _MeLocX
016f push ax
0170 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 371, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ResetYellowVars
0175 add sp, 6
0178 pop si
0179 pop di
017a leave 
017b retf 
017c mov word ptr [bp - 6], di
017f mov di, word ptr [bp + 6]
0182 les bx, ptr [bp - 6]
0185 mov al, byte ptr es:[bx + si]
0188 sub ah, ah
018a push ax
018b les bx, ptr [bp - 0x12]
018e mov al, byte ptr es:[bx]
0191 push ax
0192 les bx, ptr [bp - 0x16]
0195 mov al, byte ptr es:[bx]
0198 push ax
0199 push di
019a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 413, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetLife
019f add sp, 8
01a2 cmp di, 1
01a5 jg 0x83f9
01a7 push word ptr [0xce98] ; _MeColor
01ab push word ptr [0xce7e] ; _MeLocY
01af push word ptr [0xcd88] ; _MeLocX
01b3 nop 
01b4 push cs
01b5 call 0x28c0 ; _DeadAntHere
01b8 add sp, 6
01bb push 0
01bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 448, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
01c2 add sp, 2
01c5 pop si
01c6 pop di
01c7 leave 
01c8 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far GotoMyAnt(void);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near MeColor;` — src/recovered/wf_DoRandR-fc777553ef.c
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
- `extern void far ResetYellowVars(int plane, int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far SetLife(int plane, int x, int y, int code);` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_EnterNest-606488b329.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AnimYellowFight', 'offset': 32342, 'source': None, 'size': 545}
- {'symbol': '_AnimYellowInsane', 'offset': 32888, 'source': None, 'size': 454}
- {'symbol': '_EnterNest', 'offset': 33800, 'source': 'src/recovered/wf_EnterNest-606488b329.c', 'size': 155}
- {'symbol': '_ExitNest', 'offset': 33956, 'source': None, 'size': 477}

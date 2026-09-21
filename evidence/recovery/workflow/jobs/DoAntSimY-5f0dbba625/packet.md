# Recovery task _DoAntSimY

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 351 bytes.

```asm
0000 enter 6, 0
0004 push si
0005 mov es, word ptr [0xc3dc]
0009 cmp word ptr es:[0x9fe8], 0
000f je 0x7d0a
0011 jmp 0x7e52
0014 push 0xff
0017 push word ptr [0xcf50] ; _MeDir
001b push word ptr [0xcc84] ; _MeType
001f push word ptr [0xce7e] ; _MeLocY
0023 push word ptr [0xcd88] ; _MeLocX
0027 push word ptr [0xce80] ; _MePlane
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0030 add sp, 0xc
0033 mov es, word ptr [0xc3de]
0037 test byte ptr es:[0x75fc], 0x3f
003d jne 0x7d42
003f mov ax, word ptr [0xac8a] ; _MeHealth
0042 dec ax
0043 push ax
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyHealth
0049 add sp, 2
004c mov si, word ptr [bp - 6]
004f cmp word ptr [0xce80], 2 ; _MePlane
0054 jl 0x7d74
0056 push word ptr [0xce7e] ; _MeLocY
005a push word ptr [0xcd88] ; _MeLocX
005e push word ptr [0xce80] ; _MePlane
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0067 add sp, 6
006a mov si, ax
006c cmp si, 0x4e
006f jl 0x7d74
0071 mov ax, word ptr [0xac8a] ; _MeHealth
0074 dec ax
0075 push ax
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyHealth
007b add sp, 2
007e cmp word ptr [0xcc84], 0x60 ; _MeType
0083 je 0x7d7e
0085 jmp 0x7e20
0088 cmp word ptr [0xce80], 1 ; _MePlane
008d jg 0x7d88
008f jmp 0x7e20
0092 mov es, word ptr [0xc3de]
0096 test byte ptr es:[0x75fc], 0xf
009c je 0x7d97
009e jmp 0x7e20
00a1 mov es, word ptr [0xc3c4]
00a5 mov bx, word ptr [0xcf50] ; _MeDir
00a9 xor bl, 4
00ac mov al, byte ptr es:[bx + 8]
00b1 cwde 
00b2 shl ax, 1
00b4 add ax, word ptr [0xce7e] ; _MeLocY
00b8 mov word ptr [bp - 2], ax
00bb push ax
00bc mov es, word ptr [0xc3ca]
00c0 mov al, byte ptr es:[bx]
00c5 cwde 
00c6 shl ax, 1
00c8 add ax, word ptr [0xcd88] ; _MeLocX
00cc mov word ptr [bp - 4], ax
00cf push ax
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InNestBounds
00d5 add sp, 4
00d8 or ax, ax
00da je 0x7e20
00dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand128
00e1 cmp ax, word ptr [0xac8a] ; _MeHealth
00e5 jg 0x7e20
00e7 cmp word ptr [0xce98], 0 ; _MeColor
00ec jne 0x7dfc
00ee push 1
00f0 push word ptr [bp - 2]
00f3 push word ptr [bp - 4]
00f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 249, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PlaceEggB
00fb add sp, 6
00fe nop 
00ff push cs
0100 call 0x48f8 ; _DecEatB
0103 jmp 0x7e11
0105 nop 
0106 push 1
0108 push word ptr [bp - 2]
010b push word ptr [bp - 4]
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PlaceEggR
0113 add sp, 6
0116 nop 
0117 push cs
0118 call 0x6c6a ; _DecEatR
011b mov ax, word ptr [0xac8a] ; _MeHealth
011e sub ax, 5
0121 push ax
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyHealth
0127 add sp, 2
012a cmp word ptr [0xac8a], 0 ; _MeHealth
012f jg 0x7e52
0131 mov es, word ptr [0xc3e0]
0135 inc word ptr es:[0x9cf0]
013a cmp word ptr es:[0x9cf0], 0x64
0140 jl 0x7e52
0142 cmp word ptr [0xce80], 2 ; _MePlane
0147 jl 0x7e48
0149 cmp si, 0x4e
014c jl 0x7e48
014e push 7
0150 jmp 0x7e4a
0152 push 8
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
0159 add sp, 2
015c pop si
015d leave 
015e retf 
```

## Known declaration examples

- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_ConnectWall-bbdd72e7a8.c
- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_WallNeighbors-7ac5fa173f.c
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
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_EnterNest-606488b329.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetOutR', 'offset': 29882, 'source': None, 'size': 314}
- {'symbol': '_DoAntMoveY', 'offset': 30196, 'source': None, 'size': 1793}
- {'symbol': '_AnimYellowFight', 'offset': 32342, 'source': None, 'size': 545}
- {'symbol': '_AnimYellowInsane', 'offset': 32888, 'source': None, 'size': 454}

# Recovery task _InitYelloAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 315 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov word ptr [0xcf54], 0 ; _MeBase
000c mov es, word ptr [0xc61e]
0010 mov word ptr es:[0x8a6a], 0xfd
0017 mov es, word ptr [0xc620]
001b cmp word ptr es:[0x75fa], 0
0021 je 0x64c2
0023 mov word ptr es:[0x75fa], 0
002a mov word ptr [0xac58], 0xffff ; _ELayerMode
0030 push 0x64
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyHealth
0037 add sp, 2
003a mov es, word ptr [0xc5bc]
003e mov ax, word ptr es:[0x80b4]
0042 mov word ptr [bp - 8], ax
0045 cmp ax, 3
0048 jne 0x64df
004a jmp 0x658c
004d xor ax, ax
004f mov word ptr [0xce98], ax ; _MeColor
0052 mov es, word ptr [0xc622]
0056 mov word ptr es:[0x9fe8], ax
005a cmp word ptr [bp - 8], 2
005e jne 0x656e
0060 mov es, word ptr [0xc618]
0064 cmp word ptr es:[0x8a6c], ax
0069 jne 0x656e
006b mov word ptr [bp - 4], 0x40
0070 mov word ptr [bp - 6], 0x20
0075 xor di, di
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 122, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
007c mov si, ax
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0083 sub si, ax
0085 add si, 0x20
0088 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 139, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
008d mov bx, ax
008f mov word ptr [bp - 0xa], bx
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0097 mov bx, word ptr [bp - 0xa]
009a sub bx, ax
009c add bx, 0x20
009f mov word ptr [bp - 2], bx
00a2 mov ax, si
00a4 shl ax, 6
00a7 add bx, ax
00a9 cmp byte ptr [bx + 0x28e8], 0x10
00ae jb 0x654c
00b0 inc di
00b1 cmp di, 0x64
00b4 jl 0x6509
00b6 jmp 0x6555
00b8 nop 
00b9 nop 
00ba mov word ptr [bp - 4], si
00bd mov ax, word ptr [bp - 2]
00c0 mov word ptr [bp - 6], ax
00c3 push 0xff
00c6 push 2
00c8 push 0x40
00ca push word ptr [bp - 6]
00cd push word ptr [bp - 4]
00d0 push 1
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
00d7 add sp, 0xc
00da jmp 0x65b5
00dc push 0xff
00df push 2
00e1 push 0x10
00e3 mov es, word ptr [0xc624]
00e7 push word ptr es:[0x9fee]
00ec mov es, word ptr [0xc626]
00f0 push word ptr es:[0x9fec]
00f5 push 2
00f7 jmp 0x6564
00f9 nop 
00fa mov word ptr [0xce80], 1 ; _MePlane
0100 mov word ptr [0xce98], 0 ; _MeColor
0106 mov es, word ptr [0xc622]
010a mov word ptr es:[0x9fe8], 2
0111 mov word ptr [0xcd88], 0x40 ; _MeLocX
0117 mov word ptr [0xce7e], 0x20 ; _MeLocY
011d mov word ptr [0xcc84], 0x10 ; _MeType
0123 push word ptr [0xce7e] ; _MeLocY
0127 push word ptr [0xcd88] ; _MeLocX
012b push word ptr [0xce80] ; _MePlane
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ResetYellowVars
0134 add sp, 6
0137 pop si
0138 pop di
0139 leave 
013a retf 
```

## Known declaration examples

- `extern int near ELayerMode;` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near MeColor;` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_EnterNest-606488b329.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DigOutBNest', 'offset': 25310, 'source': 'src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c', 'size': 218}
- {'symbol': '_DigOutRNest', 'offset': 25528, 'source': 'src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c', 'size': 218}
- {'symbol': '_PlaceBlackQueen', 'offset': 26062, 'source': None, 'size': 332}
- {'symbol': '_MakeBlkQueen', 'offset': 26394, 'source': None, 'size': 192}

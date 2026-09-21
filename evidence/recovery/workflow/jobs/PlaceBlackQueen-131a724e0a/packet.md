# Recovery task _PlaceBlackQueen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 332 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 6], 0
000b mov si, 0x20
000e mov di, 1
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0016 add ax, 7
0019 mov word ptr [bp - 2], ax
001c cmp ax, di
001e jle 0x6634
0020 mov word ptr [bp - 4], di
0023 mov di, word ptr [bp - 6]
0026 push word ptr [bp - 4]
0029 push si
002a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
002f add sp, 4
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0037 or ax, ax
0039 jne 0x6616
003b push 3
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0042 add sp, 2
0045 mov di, ax
0047 dec di
0048 mov ax, di
004a add ax, si
004c cmp ax, 8
004f jl 0x6626
0051 cmp ax, 0x38
0054 jg 0x6626
0056 mov si, ax
0058 mov ax, word ptr [bp - 2]
005b inc word ptr [bp - 4]
005e cmp word ptr [bp - 4], ax
0061 jl 0x65f4
0063 mov di, word ptr [bp - 4]
0066 mov word ptr [bp - 2], 2
006b push di
006c push si
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
0072 add sp, 4
0075 inc si
0076 inc di
0077 dec word ptr [bp - 2]
007a jne 0x6639
007c push di
007d push si
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
0083 add sp, 4
0086 mov es, word ptr [0xc5d8]
008a mov word ptr es:[0x8362], si
008f mov word ptr es:[0x8364], di
0094 mov es, word ptr [0xc626]
0098 mov word ptr es:[0x9fec], si
009d mov es, word ptr [0xc624]
00a1 mov word ptr es:[0x9fee], di
00a6 push di
00a7 lea ax, [si + 2]
00aa push ax
00ab mov si, ax
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
00b2 add sp, 4
00b5 mov es, word ptr [0xc5dc]
00b9 mov al, byte ptr es:[0xe]
00bd cwde 
00be mov cx, di
00c0 add di, ax
00c2 push di
00c3 mov es, word ptr [0xc5de]
00c7 mov al, byte ptr es:[6]
00cb cwde 
00cc mov dx, si
00ce add si, ax
00d0 push si
00d1 mov si, cx
00d3 mov di, dx
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
00da add sp, 4
00dd mov es, word ptr [0xc5dc]
00e1 mov al, byte ptr es:[0xe]
00e5 cwde 
00e6 shl ax, 1
00e8 mov cx, si
00ea add si, ax
00ec push si
00ed mov es, word ptr [0xc5de]
00f1 mov al, byte ptr es:[6]
00f5 cwde 
00f6 shl ax, 1
00f8 mov dx, di
00fa add di, ax
00fc push di
00fd mov si, cx
00ff mov di, dx
0101 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 260, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
0106 add sp, 4
0109 push 0
010b push 9
010d push 0x62
010f push si
0110 push di
0111 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 276, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
0116 add sp, 0xa
0119 push 0
011b push 9
011d push 0x6a
011f mov es, word ptr [0xc5dc]
0123 mov al, byte ptr es:[0xe]
0127 cwde 
0128 add si, ax
012a push si
012b mov es, word ptr [0xc5de]
012f mov al, byte ptr es:[6]
0133 cwde 
0134 add di, ax
0136 push di
0137 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
013c add sp, 0xa
013f mov es, word ptr [0xc5d4]
0143 inc word ptr es:[0x78e8]
0148 pop si
0149 pop di
014a leave 
014b retf 
```

## Known declaration examples

- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DigOutRNest', 'offset': 25528, 'source': None, 'size': 218}
- {'symbol': '_InitYelloAnt', 'offset': 25746, 'source': None, 'size': 315}
- {'symbol': '_MakeBlkQueen', 'offset': 26394, 'source': None, 'size': 192}
- {'symbol': '_PlaceRedQueen', 'offset': 26586, 'source': None, 'size': 299}

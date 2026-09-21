# Recovery task _PlaceRedQueen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 299 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov si, 0x20
0009 mov di, 1
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0011 add ax, 7
0014 mov word ptr [bp - 2], ax
0017 cmp ax, di
0019 jle 0x682f
001b mov word ptr [bp - 4], di
001e push word ptr [bp - 4]
0021 push si
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
0027 add sp, 4
002a push 3
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 47, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0031 add sp, 2
0034 mov di, ax
0036 dec di
0037 mov ax, di
0039 add ax, si
003b cmp ax, 8
003e jl 0x6821
0040 cmp ax, 0x38
0043 jg 0x6821
0045 mov si, ax
0047 mov ax, word ptr [bp - 2]
004a inc word ptr [bp - 4]
004d cmp word ptr [bp - 4], ax
0050 jl 0x67f8
0052 mov di, word ptr [bp - 4]
0055 mov word ptr [bp - 2], 2
005a push di
005b push si
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
0061 add sp, 4
0064 inc si
0065 inc di
0066 dec word ptr [bp - 2]
0069 jne 0x6834
006b push di
006c push si
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
0072 add sp, 4
0075 mov es, word ptr [0xc5da]
0079 mov word ptr es:[0x8366], si
007e mov word ptr es:[0x8368], di
0083 push di
0084 lea ax, [si + 2]
0087 push ax
0088 mov si, ax
008a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
008f add sp, 4
0092 mov es, word ptr [0xc5dc]
0096 mov al, byte ptr es:[0xe]
009a cwde 
009b mov cx, di
009d add di, ax
009f push di
00a0 mov es, word ptr [0xc5de]
00a4 mov al, byte ptr es:[6]
00a8 cwde 
00a9 mov dx, si
00ab add si, ax
00ad push si
00ae mov si, cx
00b0 mov di, dx
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
00b7 add sp, 4
00ba mov es, word ptr [0xc5dc]
00be mov al, byte ptr es:[0xe]
00c2 cwde 
00c3 shl ax, 1
00c5 mov cx, si
00c7 add si, ax
00c9 push si
00ca mov es, word ptr [0xc5de]
00ce mov al, byte ptr es:[6]
00d2 cwde 
00d3 shl ax, 1
00d5 mov dx, di
00d7 add di, ax
00d9 push di
00da mov si, cx
00dc mov di, dx
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
00e3 add sp, 4
00e6 push 0
00e8 push 9
00ea push 0xe2
00ed push si
00ee push di
00ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 242, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
00f4 add sp, 0xa
00f7 push 0
00f9 push 9
00fb push 0xea
00fe mov es, word ptr [0xc5dc]
0102 mov al, byte ptr es:[0xe]
0106 cwde 
0107 add si, ax
0109 push si
010a mov es, word ptr [0xc5de]
010e mov al, byte ptr es:[6]
0112 cwde 
0113 add di, ax
0115 push di
0116 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 281, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
011b add sp, 0xa
011e mov es, word ptr [0xc5d6]
0122 inc word ptr es:[0x79dc]
0127 pop si
0128 pop di
0129 leave 
012a retf 
```

## Known declaration examples

- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far DigTileR(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PlaceBlackQueen', 'offset': 26062, 'source': None, 'size': 332}
- {'symbol': '_MakeBlkQueen', 'offset': 26394, 'source': None, 'size': 192}
- {'symbol': '_MakeRedQueen', 'offset': 26886, 'source': None, 'size': 194}
- {'symbol': '_fracSIN', 'offset': 27080, 'source': 'src/recovered/wf_fracSIN-85445ba91f.c', 'size': 70}

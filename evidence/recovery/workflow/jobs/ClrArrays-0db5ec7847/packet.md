# Recovery task _ClrArrays

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 273 bytes.

```asm
0000 push di
0001 push si
0002 xor di, di
0004 xor si, si
0006 xor al, al
0008 mov bx, di
000a add bx, si
000c mov byte ptr [bx + 0x28e8], al
0010 mov byte ptr [bx + 0x68e8], al
0014 inc si
0015 cmp si, 0x40
0018 jl 0x6df2
001a add di, 0x40
001d cmp di, 0x2000
0021 jl 0x6df0
0023 xor di, di
0025 mov <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0028 mov es, ax
002a xor si, si
002c xor al, al
002e mov bx, di
0030 add bx, si
0032 mov byte ptr [bx + 0x48e8], al
0036 mov byte ptr [bx + 0x58e8], al
003a mov byte ptr es:[bx + 0x3a4], al
003f mov byte ptr es:[bx + 0x13a4], al
0044 mov byte ptr [bx - 0x7718], al
0048 mov byte ptr [bx - 0x6718], al
004c inc si
004d cmp si, 0x40
0050 jl 0x6e18
0052 add di, 0x40
0055 cmp di, 0x1000
0059 jl 0x6e16
005b xor di, di
005d mov <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0060 mov ds, ax
0062 xor si, si
0064 xor al, al
0066 mov bx, di
0068 add bx, si
006a mov byte ptr [bx + 0x5ad2], al
006e mov byte ptr [bx + 0x52d2], al
0072 mov byte ptr [bx + 0x62d2], al
0076 mov byte ptr [bx + 0x6ad2], al
007a mov byte ptr [bx + 0x72d2], al
007e mov byte ptr [bx + 0x7ad2], al
0082 inc si
0083 cmp si, 0x20
0086 jl 0x6e50
0088 add di, 0x20
008b cmp di, 0x800
008f jl 0x6e4e
0091 xor ax, ax
0093 mov <resolved loader operand; see bindings> ; [{'operand_offset': 148, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0096 mov es, cx
0098 mov cx, 0x1f4
009b mov di, 0x334c
009e rep stosw word ptr es:[di], ax
00a0 mov cx, 0x1f4
00a3 mov di, 0x2b78
00a6 rep stosw word ptr es:[di], ax
00a8 mov cx, 0x1f4
00ab mov di, 0x2f62
00ae rep stosw word ptr es:[di], ax
00b0 mov cx, 0xfa
00b3 mov di, 0x48dc
00b6 rep stosw word ptr es:[di], ax
00b8 mov cx, 0xfa
00bb mov di, 0x44f0
00be rep stosw word ptr es:[di], ax
00c0 mov cx, 0xfa
00c3 mov di, 0x46e6
00c6 rep stosw word ptr es:[di], ax
00c8 mov cx, 0xfa
00cb mov di, 0x3f0e
00ce rep stosw word ptr es:[di], ax
00d0 mov cx, 0xfa
00d3 mov di, 0x3b22
00d6 rep stosw word ptr es:[di], ax
00d8 mov cx, 0xfa
00db mov di, 0x3d18
00de rep stosw word ptr es:[di], ax
00e0 xor di, di
00e2 xor si, si
00e4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 229, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00e7 mov ds, ax
00e9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ec mov es, ax
00ee xor al, al
00f0 mov bx, di
00f2 add bx, si
00f4 mov byte ptr es:[bx + 0xa4], al
00f9 mov byte ptr [bx + 0x164], al
00fd inc si
00fe cmp si, 0x10
0101 jl 0x6eda
0103 push ss
0104 pop ds
0105 add di, 0x10
0108 cmp di, 0xc0
010c jl 0x6ece
010e pop si
010f pop di
0110 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddRedAnts', 'offset': 27902, 'source': None, 'size': 173}
- {'symbol': '_GrabMap', 'offset': 28076, 'source': None, 'size': 64}
- {'symbol': '_goStepRight', 'offset': 28414, 'source': 'src/recovered/wf_tu_simtwo_6EFE-d6ff84e46b.c', 'size': 181}
- {'symbol': '_goStepLeft', 'offset': 28596, 'source': 'src/recovered/wf_tu_simtwo_6EFE-d6ff84e46b.c', 'size': 163}

# Recovery task _StartMigrate

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 121 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0008 mov ds, ax
000a mov ax, word ptr [bp + 8]
000d sub ax, 0x42
0010 mov cx, 0xa
0013 cdq 
0014 idiv cx
0016 mov bx, 0x9d72
0019 mov <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
001c mov es, cx
001e mov word ptr [bp - 4], bx
0021 mov word ptr [bp - 2], es
0024 mov word ptr es:[bx], ax
0027 mov ax, word ptr [bp + 8]
002a add ax, word ptr [bp + 6]
002d sub ax, 0xee
0030 mov cx, 0x1c
0033 cdq 
0034 idiv cx
0036 mov word ptr [0x9cee], ax
0039 or ax, ax
003b jl 0x3e40
003d cmp word ptr es:[bx], 0
0041 jl 0x3e40
0043 cmp ax, 0xb
0046 jg 0x3e40
0048 cmp word ptr es:[bx], 0xf
004c jle 0x3e46
004e mov word ptr [0x9cee], 0xffff
0054 mov bx, word ptr [0x9cee]
0058 shl bx, 4
005b mov si, word ptr [bp - 4]
005e add bx, word ptr es:[si]
0061 mov <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0064 mov es, ax
0066 cmp byte ptr es:[bx + 0xa4], 0
006c jne 0x3e66
006e mov word ptr [0x9cee], 0xffff
0074 push ss
0075 pop ds
0076 pop si
0077 leave 
0078 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeB-f9a6e1c57a.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetNearbyPatches', 'offset': 15588, 'source': None, 'size': 103}
- {'symbol': '_Reproduce', 'offset': 15692, 'source': None, 'size': 165}
- {'symbol': '_EndMigrate', 'offset': 15980, 'source': None, 'size': 139}
- {'symbol': '_InitSow', 'offset': 16120, 'source': None, 'size': 146}

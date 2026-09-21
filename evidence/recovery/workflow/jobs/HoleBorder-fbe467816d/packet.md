# Recovery task _HoleBorder

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 86 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 xor di, di
0008 mov es, word ptr [0xc3fe]
000c mov al, byte ptr es:[di + 8]
0011 cwde 
0012 mov si, ax
0014 add si, word ptr [bp + 8]
0017 mov es, word ptr [0xc400]
001b mov al, byte ptr es:[di]
0020 cwde 
0021 mov cx, ax
0023 add cx, word ptr [bp + 6]
0026 js 0x1fda
0028 cmp cx, 0x7f
002b jg 0x1fda
002d or si, si
002f jl 0x1fda
0031 cmp si, 0x3f
0034 jg 0x1fda
0036 mov bx, cx
0038 shl bx, 6
003b add bx, si
003d add bx, 0x28e8
0041 cmp byte ptr [bx], 0x50
0044 jae 0x1fda
0046 mov al, byte ptr [di + 0x230c]
004a mov byte ptr [bx], al
004c inc di
004d cmp di, 8
0050 jl 0x1f96
0052 pop si
0053 pop di
0054 leave 
0055 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CanBeHouseHole', 'offset': 7354, 'source': 'src/recovered/wf_CanBeHouseHole-987878d5ee.c', 'size': 72}
- {'symbol': '_MakeNewHoleR', 'offset': 7426, 'source': None, 'size': 650}
- {'symbol': '_DigTileB', 'offset': 8164, 'source': None, 'size': 505}
- {'symbol': '_DigTileR', 'offset': 8670, 'source': None, 'size': 245}

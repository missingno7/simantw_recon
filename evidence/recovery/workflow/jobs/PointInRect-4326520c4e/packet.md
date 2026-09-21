# Recovery task _PointInRect

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 106 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 10}}]
0007 mov es, ax
0009 cmp word ptr es:[0xbd0a], 0
000f je 0x49b8
0011 lds bx, ptr [bp + 6]
0014 les di, ptr [bp + 0xa]
0017 mov ax, word ptr [bx]
0019 cmp word ptr es:[di + 4], ax
001d jle 0x49dd
001f cmp word ptr es:[di], ax
0022 jg 0x49dd
0024 mov ax, word ptr [bx + 2]
0027 cmp word ptr es:[di + 2], ax
002b jg 0x49dd
002d mov ax, word ptr es:[di + 6]
0031 cmp word ptr [bx + 2], ax
0034 jge 0x49dd
0036 mov ax, 1
0039 push ss
003a pop ds
003b pop di
003c leave 
003d retf 
003e lds bx, ptr [bp + 6]
0041 les di, ptr [bp + 0xa]
0044 mov ax, word ptr [bx]
0046 cmp word ptr es:[di + 4], ax
004a jl 0x49dd
004c cmp word ptr es:[di], ax
004f jg 0x49dd
0051 mov ax, word ptr [bx + 2]
0054 cmp word ptr es:[di + 2], ax
0058 jg 0x49dd
005a mov ax, word ptr es:[di + 6]
005e cmp word ptr [bx + 2], ax
0061 jle 0x49b0
0063 xor ax, ax
0065 push ss
0066 pop ds
0067 pop di
0068 leave 
0069 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_gr_CenterStrInRectClear', 'offset': 18454, 'source': None, 'size': 217}
- {'symbol': '_gr_CenterStrInRect', 'offset': 18672, 'source': None, 'size': 137}
- {'symbol': '_WaitHundredths', 'offset': 18916, 'source': None, 'size': 55}
- {'symbol': '_GetMousePos', 'offset': 18972, 'source': 'src/recovered/GetMousePos.c', 'size': 16}

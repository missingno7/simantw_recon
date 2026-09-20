# Recovery task _IsThisFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 46 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 cmp word ptr [bp + 6], 1
0007 jg 0x5f1a
0009 push word ptr [bp + 8]
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
0011 mov sp, bp
0013 leave 
0014 retf 
0015 nop 
0016 mov dx, word ptr [bp + 8]
0019 cmp dx, 0x10
001c jl 0x5f2c
001e cmp dx, 0x13
0021 jg 0x5f2c
0023 mov dx, 1
0026 jmp 0x5f2e
0028 xor dx, dx
002a mov ax, dx
002c leave 
002d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsThisEgg', 'offset': 24264, 'source': 'src/recovered/IsThisEgg.c', 'size': 28}
- {'symbol': '_IsThisGrass', 'offset': 24292, 'source': 'src/recovered/wf_IsThisGrass-f06e1489c1.c', 'size': 32}
- {'symbol': '_IsThisPebble', 'offset': 24370, 'source': None, 'size': 49}
- {'symbol': '_IsItNFood', 'offset': 24420, 'source': 'src/recovered/wf_IsItNFood-b827504a64.c', 'size': 26}

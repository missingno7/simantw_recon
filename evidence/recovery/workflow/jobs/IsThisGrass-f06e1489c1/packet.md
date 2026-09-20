# Recovery task _IsThisGrass

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 32 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 cmp word ptr [bp + 6], 2
0007 jl 0x5f00
0009 mov dx, word ptr [bp + 8]
000c cmp dx, 0x1c
000f jl 0x5f00
0011 cmp dx, 0x1f
0014 jg 0x5f00
0016 mov ax, 1
0019 leave 
001a retf 
001b nop 
001c xor ax, ax
001e leave 
001f retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetLife', 'offset': 23832, 'source': None, 'size': 432}
- {'symbol': '_IsThisEgg', 'offset': 24264, 'source': 'src/recovered/IsThisEgg.c', 'size': 28}
- {'symbol': '_IsThisFood', 'offset': 24324, 'source': None, 'size': 46}
- {'symbol': '_IsThisPebble', 'offset': 24370, 'source': None, 'size': 49}

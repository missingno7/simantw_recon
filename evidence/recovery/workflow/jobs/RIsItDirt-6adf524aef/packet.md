# Recovery task _RIsItDirt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 31 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov dx, word ptr [bp + 6]
0006 cmp dx, 0x20
0009 jge 0x26d4
000b xor ax, ax
000d leave 
000e retf 
000f nop 
0010 cmp dx, 0x2f
0013 jle 0x26de
0015 cmp dx, 0x4f
0018 jl 0x26cf
001a mov ax, 1
001d leave 
001e retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DigTileThemR', 'offset': 9244, 'source': None, 'size': 318}
- {'symbol': '_SmoothEdgesB', 'offset': 9562, 'source': None, 'size': 362}
- {'symbol': '_SmoothEdgesR', 'offset': 9956, 'source': None, 'size': 362}
- {'symbol': '_FixExitMapB', 'offset': 10318, 'source': None, 'size': 198}

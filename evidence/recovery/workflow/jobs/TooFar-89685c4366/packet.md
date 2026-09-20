# Recovery task _TooFar

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 39 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov dx, word ptr [bp + 6]
0006 cmp dx, 0xf
0009 jg 0xbdfe
000b cmp dx, -0xf
000e jl 0xbdfe
0010 mov dx, word ptr [bp + 8]
0013 cmp dx, 0xf
0016 jg 0xbdfe
0018 cmp dx, -0xf
001b jl 0xbdfe
001d xor ax, ax
001f leave 
0020 retf 
0021 nop 
0022 mov ax, 1
0025 leave 
0026 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawRain', 'offset': 47774, 'source': None, 'size': 112}
- {'symbol': '_DrawSwarm', 'offset': 47886, 'source': None, 'size': 718}
- {'symbol': '_InvertPatch', 'offset': 48644, 'source': None, 'size': 159}
- {'symbol': '_DrawSimColonies', 'offset': 48804, 'source': None, 'size': 247}

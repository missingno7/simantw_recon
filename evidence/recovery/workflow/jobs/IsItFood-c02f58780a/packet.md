# Recovery task _IsItFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 51 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov es, word ptr [0xc320]
0007 cmp word ptr es:[0x9b6e], 0
000d jne 0x2d3c
000f mov dx, word ptr [bp + 6]
0012 cmp dx, 0x48
0015 jl 0x2d49
0017 cmp dx, 0x4b
001a jg 0x2d49
001c mov ax, 1
001f leave 
0020 retf 
0021 nop 
0022 mov dx, word ptr [bp + 6]
0025 cmp dx, 0x18
0028 jl 0x2d49
002a cmp dx, 0x27
002d jle 0x2d36
002f xor ax, ax
0031 leave 
0032 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAttackAnt', 'offset': 10816, 'source': None, 'size': 640}
- {'symbol': '_IsItHole', 'offset': 11456, 'source': None, 'size': 89}
- {'symbol': '_DoAntSimB', 'offset': 11598, 'source': None, 'size': 95}
- {'symbol': '_DoNestAntB', 'offset': 11694, 'source': None, 'size': None}

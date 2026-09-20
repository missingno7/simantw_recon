# Recovery task _IsItWall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 26 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov dx, word ptr [bp + 6]
0006 cmp dx, 0x60
0009 jl 0x8714
000b cmp dx, 0x67
000e jg 0x8714
0010 mov ax, 1
0013 leave 
0014 retf 
0015 nop 
0016 xor ax, ax
0018 leave 
0019 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ConnectWall', 'offset': 34126, 'source': None, 'size': 241}
- {'symbol': '_WallNeighbors', 'offset': 34368, 'source': None, 'size': 190}
- {'symbol': '_FillDirtB', 'offset': 34584, 'source': None, 'size': 193}
- {'symbol': '_FillDirtR', 'offset': 34778, 'source': None, 'size': 193}

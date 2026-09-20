# Recovery task _IsItDirt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 26 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov dx, word ptr [bp + 6]
0006 cmp dx, 0x20
0009 jl 0x1198
000b cmp dx, 0x2e
000e jg 0x1198
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

- {'symbol': '_GetDis', 'offset': 4386, 'source': 'src/recovered/GetDis.c', 'size': 57}
- {'symbol': '_InNestBounds', 'offset': 4444, 'source': None, 'size': 38}
- {'symbol': '_GetExitDirB', 'offset': 4508, 'source': None, 'size': 164}
- {'symbol': '_GetExitDirR', 'offset': 4672, 'source': None, 'size': 164}

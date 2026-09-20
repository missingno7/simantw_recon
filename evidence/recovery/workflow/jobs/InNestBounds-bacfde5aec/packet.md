# Recovery task _InNestBounds

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 38 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov dx, word ptr [bp + 6]
0006 or dx, dx
0008 jl 0x117e
000a cmp dx, 0x3f
000d jg 0x117e
000f mov dx, word ptr [bp + 8]
0012 cmp dx, 1
0015 jl 0x117e
0017 cmp dx, 0x3f
001a jg 0x117e
001c mov ax, 1
001f leave 
0020 retf 
0021 nop 
0022 xor ax, ax
0024 leave 
0025 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetDir', 'offset': 4300, 'source': None, 'size': 86}
- {'symbol': '_GetDis', 'offset': 4386, 'source': 'src/recovered/GetDis.c', 'size': 57}
- {'symbol': '_IsItDirt', 'offset': 4482, 'source': 'src/recovered/wf_IsItDirt-30ab0b6cc4.c', 'size': 26}
- {'symbol': '_GetExitDirB', 'offset': 4508, 'source': None, 'size': 164}

# Recovery task _SGRand

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 39 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push di
000a nop 
000b push cs
000c call 0x158a ; _SRand1
000f add sp, 2
0012 mov si, ax
0014 push di
0015 nop 
0016 push cs
0017 call 0x158a ; _SRand1
001a add sp, 2
001d cmp ax, si
001f jle 0x14c7
0021 mov ax, si
0023 pop si
0024 pop di
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

- {'symbol': '_TryAntTheme', 'offset': 5140, 'source': None, 'size': 104}
- {'symbol': '_SGIRand', 'offset': 5244, 'source': None, 'size': 39}
- {'symbol': '_SGSRand', 'offset': 5324, 'source': None, 'size': 57}
- {'symbol': '_SetSRandSeed', 'offset': 5382, 'source': 'src/recovered/SetSRandSeed.c', 'size': 11}

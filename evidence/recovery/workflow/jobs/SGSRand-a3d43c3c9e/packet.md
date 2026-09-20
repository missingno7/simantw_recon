# Recovery task _SGSRand

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 57 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push si
000a nop 
000b push cs
000c call 0x158a ; _SRand1
000f add sp, 2
0012 mov di, ax
0014 push si
0015 nop 
0016 push cs
0017 call 0x158a ; _SRand1
001a add sp, 2
001d cmp ax, di
001f jg 0x14f2
0021 mov si, ax
0023 jmp 0x14f4
0025 nop 
0026 mov si, di
0028 nop 
0029 push cs
002a call 0x15ae ; _SRand2
002d or ax, ax
002f je 0x14ff
0031 neg si
0033 mov ax, si
0035 pop si
0036 pop di
0037 leave 
0038 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SGIRand', 'offset': 5244, 'source': None, 'size': 39}
- {'symbol': '_SGRand', 'offset': 5284, 'source': None, 'size': 39}
- {'symbol': '_SetSRandSeed', 'offset': 5382, 'source': 'src/recovered/SetSRandSeed.c', 'size': 11}
- {'symbol': '_GetSRandSeed', 'offset': 5394, 'source': 'src/recovered/GetSRandSeed.c', 'size': 6}

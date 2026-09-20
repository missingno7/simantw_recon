# Recovery task _SeedRRand

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 56 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
000b xor ax, 0x3751
000e mov word ptr [0xcbf2], ax
0011 nop 
0012 push cs
0013 call 0x166e ; _SRand128
0016 mov di, ax
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
001d push ax
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _srand
0023 add sp, 2
0026 or di, di
0028 jle 0x156a
002a mov si, di
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 47, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _rand
0031 dec si
0032 jne 0x1562
0034 pop si
0035 pop di
0036 leave 
0037 retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int rand(void);` — src/recovered/RRand.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetRRandSeed', 'offset': 5402, 'source': 'src/recovered/GetRRandSeed.c', 'size': 15}
- {'symbol': '_SeedSRand', 'offset': 5418, 'source': 'src/recovered/SeedSRand.c', 'size': 12}
- {'symbol': '_RRand', 'offset': 5486, 'source': 'src/recovered/RRand.c', 'size': 28}
- {'symbol': '_SRand1', 'offset': 5514, 'source': None, 'size': 35}

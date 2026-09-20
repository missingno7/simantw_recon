# Recovery task _RallocFree

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 53 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov es, word ptr [bp + 8]
000b mov si, word ptr es:[di + 4]
000f sub word ptr [0x85c], 1
0014 sbb word ptr [0x85e], 0
0019 push si
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
001f push si
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0025 push -1
0027 push -1
0029 nop 
002a push cs
002b call 0x56a8 ; _RallocFindMem
002e add sp, 4
0031 pop si
0032 pop di
0033 leave 
0034 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Ralloc', 'offset': 22514, 'source': None, 'size': 160}
- {'symbol': '_RallocRealloc', 'offset': 22674, 'source': None, 'size': 163}
- {'symbol': '_RallocAge', 'offset': 22892, 'source': 'src/recovered/RallocAge.c', 'size': 18}
- {'symbol': '_RallocFreshen', 'offset': 22910, 'source': 'src/recovered/RallocFreshen.c', 'size': 21}

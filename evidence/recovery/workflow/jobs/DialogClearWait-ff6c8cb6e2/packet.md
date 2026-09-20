# Recovery task _DialogClearWait

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 46 bytes.

```asm
0000 mov bx, word ptr [0x150a]
0004 shl bx, 1
0006 cmp word ptr [bx - 0x350c], -1
000b je 0x9b99
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0012 mov bx, word ptr [0x150a]
0016 shl bx, 2
0019 mov word ptr [bx - 0x352c], ax
001d mov word ptr [bx - 0x352a], dx
0021 mov bx, word ptr [0x150a]
0025 shl bx, 1
0027 mov word ptr [bx - 0x350c], 0x1518
002d retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OpenMapYard', 'offset': 39722, 'source': None, 'size': 54}
- {'symbol': '_UpdateEverything', 'offset': 39776, 'source': 'src/recovered/UpdateEverything.c', 'size': 11}
- {'symbol': '_DialogClearWaitInit', 'offset': 39834, 'source': None, 'size': 70}
- {'symbol': '_DialogWait', 'offset': 39904, 'source': None, 'size': 30}

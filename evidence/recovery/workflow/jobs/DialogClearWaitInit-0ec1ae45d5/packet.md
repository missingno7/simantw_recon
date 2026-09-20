# Recovery task _DialogClearWaitInit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 70 bytes.

```asm
0000 inc word ptr [0x150a]
0004 cmp word ptr [0x150a], 8
0009 jl 0x9bbf
000b mov word ptr [0x150a], 0
0011 push word ptr [0xcd78] ; _rootWnd
0015 push ds
0016 push 0x1522
0019 push ds
001a push 0x150c
001d push 0x1010
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
002a mov bx, word ptr [0x150a]
002e shl bx, 2
0031 mov word ptr [bx - 0x352c], ax
0035 mov word ptr [bx - 0x352a], dx
0039 mov bx, word ptr [0x150a]
003d shl bx, 1
003f mov word ptr [bx - 0x350c], 0x1518
0045 retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateEverything', 'offset': 39776, 'source': 'src/recovered/UpdateEverything.c', 'size': 11}
- {'symbol': '_DialogClearWait', 'offset': 39788, 'source': None, 'size': 46}
- {'symbol': '_DialogWait', 'offset': 39904, 'source': None, 'size': 30}
- {'symbol': '_DialogWaitInit', 'offset': 39934, 'source': None, 'size': 104}

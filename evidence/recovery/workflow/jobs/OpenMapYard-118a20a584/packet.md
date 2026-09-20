# Recovery task _OpenMapYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 54 bytes.

```asm
0000 push 0x100
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0008 add sp, 2
000b or ax, ax
000d je 0x9b46
000f push 0x100
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ToTop
0017 add sp, 2
001a retf 
001b nop 
001c push 0x1900
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0024 add sp, 2
0027 or ax, ax
0029 je 0x9b5a
002b push 0x1900
002e jmp 0x9b3c
0030 nop 
0031 push cs
0032 call 0x972a ; _YardToMap
0035 retf 
```

## Known declaration examples

- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/win_MapChanged.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_YardToMap', 'offset': 38698, 'source': None, 'size': 493}
- {'symbol': '_MapToYard', 'offset': 39192, 'source': None, 'size': 529}
- {'symbol': '_UpdateEverything', 'offset': 39776, 'source': 'src/recovered/UpdateEverything.c', 'size': 11}
- {'symbol': '_DialogClearWait', 'offset': 39788, 'source': None, 'size': 46}

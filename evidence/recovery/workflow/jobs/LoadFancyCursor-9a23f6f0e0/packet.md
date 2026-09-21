# Recovery task _LoadFancyCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 113 bytes.

```asm
0000 push word ptr [0xcc7c] ; _hInst
0004 push ds
0005 push 0x32a
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
000d mov word ptr [0xcd82], ax ; _magCursor
0010 push word ptr [0xcc7c] ; _hInst
0014 push ds
0015 push 0x334
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
001d mov word ptr [0xcd80], ax ; _rockCursor
0020 push word ptr [0xcc7c] ; _hInst
0024 push ds
0025 push 0x33f
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
002d mov word ptr [0xce84], ax ; _digCursor
0030 push word ptr [0xcc7c] ; _hInst
0034 push ds
0035 push 0x349
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
003d mov word ptr [0xce94], ax ; _antCursor
0040 push word ptr [0xcc7c] ; _hInst
0044 push ds
0045 push 0x353
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
004d mov word ptr [0xcc82], ax ; _foodCursor
0050 push word ptr [0xcc7c] ; _hInst
0054 push ds
0055 push 0x35e
0058 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
005d mov word ptr [0xcd7c], ax ; _dropCursor
0060 push word ptr [0xcc7c] ; _hInst
0064 push ds
0065 push 0x369
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
006d mov word ptr [0xce8c], ax ; _sprayCursor
0070 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateWindows', 'offset': 8740, 'source': None, 'size': 540}
- {'symbol': 'MYTIMERFUNC', 'offset': 9280, 'source': None, 'size': 973}
- {'symbol': '_SetFancyCursor', 'offset': 10368, 'source': None, 'size': None}
- {'symbol': 'MAINWNDPROC', 'offset': 10544, 'source': None, 'size': None}

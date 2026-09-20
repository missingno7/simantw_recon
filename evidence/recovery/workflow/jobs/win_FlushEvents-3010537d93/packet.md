# Recovery task _win_FlushEvents

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 76 bytes.

```asm
0000 enter 0x12, 0
0004 lea ax, [bp - 0x12]
0007 push ss
0008 push ax
0009 push 0
000b push 0x200
000e push 0x209
0011 push 1
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0018 or ax, ax
001a jne 0xc20e
001c lea ax, [bp - 0x12]
001f push ss
0020 push ax
0021 push 0
0023 push 0x100
0026 push 0x108
0029 push 1
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0030 or ax, ax
0032 jne 0xc20e
0034 lea ax, [bp - 0x12]
0037 push ss
0038 push ax
0039 push 0
003b push 0x21
003d push 0x21
003f push 1
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0046 or ax, ax
0048 jne 0xc20e
004a leave 
004b retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_IsWinExposed', 'offset': 49410, 'source': None, 'size': 155}
- {'symbol': '_win_IsWinInFront', 'offset': 49566, 'source': None, 'size': 107}
- {'symbol': '_win_IsWinOpen', 'offset': 49750, 'source': None, 'size': 49}
- {'symbol': '_win_IsWinZoomed', 'offset': 49800, 'source': None, 'size': 49}

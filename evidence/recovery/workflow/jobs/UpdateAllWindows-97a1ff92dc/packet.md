# Recovery task _UpdateAllWindows

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 58 bytes.

```asm
0000 enter 0x12, 0
0004 lea ax, [bp - 0x12]
0007 push ss
0008 push ax
0009 push 0
000b push 0xf
000d push 0xf
000f push 1
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0016 or ax, ax
0018 je 0xd14e
001a push word ptr [bp - 0x12]
001d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0022 lea ax, [bp - 0x12]
0025 push ss
0026 push ax
0027 push 0
0029 push 0xf
002b push 0xf
002d push 1
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0034 or ax, ax
0036 jne 0xd130
0038 leave 
0039 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_Events', 'offset': 53312, 'source': None, 'size': 112}
- {'symbol': '_win_FindObject', 'offset': 53424, 'source': None, 'size': 101}
- {'symbol': '_win_GetEvent', 'offset': 53584, 'source': None, 'size': 420}
- {'symbol': '_win_SetObjFormatStr', 'offset': 54004, 'source': None, 'size': 297}

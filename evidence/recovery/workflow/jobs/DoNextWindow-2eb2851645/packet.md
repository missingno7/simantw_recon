# Recovery task _DoNextWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 74 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 6]
0008 or si, si
000a je 0x1872
000c jmp 0x183c
000e mov si, ax
0010 push si
0011 push 2
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
0018 mov di, ax
001a or di, di
001c jne 0x183a
001e push si
001f push 4
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
0026 or ax, ax
0028 jne 0x1860
002a push si
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0030 or ax, ax
0032 jne 0x186c
0034 push si
0035 push 3
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
003c mov si, ax
003e jmp 0x184a
0040 push si
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
0046 pop si
0047 pop di
0048 leave 
0049 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoKeyDown', 'offset': 3724, 'source': None, 'size': 1385}
- {'symbol': '_DoMouse', 'offset': 5110, 'source': None, 'size': None}
- {'symbol': '_DoMenuEntry', 'offset': 6262, 'source': None, 'size': 503}
- {'symbol': '_AdjustWndMinMax', 'offset': 6766, 'source': None, 'size': 457}

# Recovery task MYENUMFUNC

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 48 bytes.

```asm
0000 mov ax, ss
0002 push bp
0003 mov bp, sp
0005 push si
0006 push ds
0007 mov ds, ax
0009 mov si, word ptr [bp + 0xa]
000c cmp word ptr [bp + 6], si
000f je 0x1c5f
0011 push si
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0017 or ax, ax
0019 je 0x1c5f
001b push si
001c push 0
001e push 0
0020 push 0
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0027 mov ax, 1
002a pop ds
002b pop si
002c leave 
002d retf 6
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoMenuEntry', 'offset': 6262, 'source': None, 'size': 503}
- {'symbol': '_AdjustWndMinMax', 'offset': 6766, 'source': None, 'size': 457}
- {'symbol': '_RedrawWindows', 'offset': 7272, 'source': None, 'size': 86}
- {'symbol': '_DoDebugWin', 'offset': 7358, 'source': None, 'size': 179}

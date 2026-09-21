# Recovery task _MyGetTopWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 79 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 push word ptr [bp + 6]
0007 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 8, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 229}}]
000c mov si, ax
000e or si, si
0010 jne 0xc0ca
0012 xor ax, ax
0014 pop si
0015 leave 
0016 retf 
0017 nop 
0018 push si
0019 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
001e or ax, ax
0020 jne 0xc0e2
0022 push si
0023 push 2
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
002a mov si, ax
002c or si, si
002e jne 0xc0ca
0030 or si, si
0032 je 0xc0fc
0034 push si
0035 push 4
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
003c or ax, ax
003e je 0xc0fc
0040 push si
0041 push 4
0043 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
0048 mov si, ax
004a mov ax, si
004c pop si
004d leave 
004e retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_PrintTextInRect', 'offset': 48850, 'source': None, 'size': 438}
- {'symbol': '_win_PrintTextInObj', 'offset': 49288, 'source': 'src/recovered/win_PrintTextInObj.c', 'size': 41}
- {'symbol': '_win_IsWinExposed', 'offset': 49410, 'source': None, 'size': 155}
- {'symbol': '_win_IsWinInFront', 'offset': 49566, 'source': None, 'size': 107}

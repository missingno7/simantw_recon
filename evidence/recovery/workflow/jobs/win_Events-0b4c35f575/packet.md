# Recovery task _win_Events

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 112 bytes.

```asm
0000 enter 0x12, 0
0004 push si
0005 xor si, si
0007 lea ax, [bp - 0x12]
000a push ss
000b push ax
000c push si
000d push si
000e push si
000f push 1
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0016 or ax, ax
0018 je 0xd0ab
001a cmp word ptr [bp - 0x10], 0x201
001f je 0xd068
0021 cmp word ptr [bp - 0x10], 0x202
0026 jne 0xd06b
0028 mov si, 1
002b cmp word ptr [bp - 0x10], 0x100
0030 jne 0xd081
0032 cmp word ptr [bp - 0xe], 0x20
0036 je 0xd07e
0038 cmp word ptr [bp - 0xe], 0x2d
003c jne 0xd081
003e mov si, 1
0041 lea ax, [bp - 0x12]
0044 push ss
0045 push ax
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 113}}]
004b lea ax, [bp - 0x12]
004e push ss
004f push ax
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 114}}]
0055 lea ax, [bp - 0x12]
0058 push ss
0059 push ax
005a push 0
005c push 0
005e push 0
0060 push 1
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0067 or ax, ax
0069 jne 0xd05a
006b mov ax, si
006d pop si
006e leave 
006f retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_Open', 'offset': 51758, 'source': None, 'size': 1385}
- {'symbol': '_win_Close', 'offset': 53144, 'source': None, 'size': 168}
- {'symbol': '_win_FindObject', 'offset': 53424, 'source': None, 'size': 101}
- {'symbol': '_UpdateAllWindows', 'offset': 53526, 'source': 'src/recovered/wf_UpdateAllWindows-97a1ff92dc.c', 'size': 58}

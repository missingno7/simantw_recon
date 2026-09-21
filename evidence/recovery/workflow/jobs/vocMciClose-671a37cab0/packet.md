# Recovery task _vocMciClose

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 122 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 cmp word ptr [0xaf2], 0
000a je 0x7fd3
000c mov si, word ptr [bp + 8]
000f push si
0010 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
0015 push si
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
001b mov word ptr [0xaf2], 0
0021 cmp word ptr [0xaf0], 0
0026 je 0x7fef
0028 mov si, word ptr [bp + 6]
002b push si
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
0031 push si
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0037 mov word ptr [0xaf0], 0
003d mov es, word ptr [0xbf78]
0041 dec word ptr es:[0x8d1a]
0046 jne 0x8029
0048 push word ptr es:[0x8d08]
004d push ds
004e push 0xc6d
0051 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0056 mov word ptr [bp - 4], ax
0059 mov word ptr [bp - 2], dx
005c or dx, ax
005e je 0x801e
0060 mov es, word ptr [0xbf78]
0064 push word ptr es:[0x8d14]
0069 lcall [bp - 4]
006c mov es, word ptr [0xbf78]
0070 mov word ptr es:[0x8d14], 0
0077 pop si
0078 leave 
0079 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_musSoundBlasterClose', 'offset': 32490, 'source': None, 'size': 100}
- {'symbol': '_vocSoundBlasterClose', 'offset': 32590, 'source': None, 'size': 100}
- {'symbol': '_SoundBlasterMessage', 'offset': 32812, 'source': None, 'size': 296}
- {'symbol': '_MciMessage', 'offset': 33108, 'source': None, 'size': 295}

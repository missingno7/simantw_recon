# Recovery task _musSoundBlasterClose

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 100 bytes.

```asm
0000 enter 4, 0
0004 mov es, word ptr [0xbf78]
0008 push word ptr es:[0x8d08]
000d push ds
000e push 0xc4f
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0016 mov word ptr [bp - 4], ax
0019 mov word ptr [bp - 2], dx
001c or dx, ax
001e je 0x7f0d
0020 lcall [bp - 4]
0023 mov es, word ptr [0xbf78]
0027 push word ptr es:[0x8d20]
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
0031 mov es, word ptr [0xbf78]
0035 push word ptr es:[0x8d1c]
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
003f mov es, word ptr [0xbf78]
0043 push word ptr es:[0x8d1c]
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
004d mov es, word ptr [0xbf78]
0051 mov word ptr es:[0x8d1c], 0
0058 sub ax, ax
005a mov word ptr es:[0x8d20], ax
005e mov word ptr es:[0x8d1e], ax
0062 leave 
0063 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_snd_Deinstall', 'offset': 31838, 'source': None, 'size': 608}
- {'symbol': '_snd_IsSongDone', 'offset': 32446, 'source': None, 'size': 44}
- {'symbol': '_vocSoundBlasterClose', 'offset': 32590, 'source': None, 'size': 100}
- {'symbol': '_vocMciClose', 'offset': 32690, 'source': None, 'size': 122}

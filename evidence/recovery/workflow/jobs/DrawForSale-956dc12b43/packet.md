# Recovery task _DrawForSale

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 63 bytes.

```asm
0000 cmp word ptr [0x1892], -1
0005 je 0xb2a8
0007 push -1
0009 push word ptr [0x1892]
000d push word ptr [0x1886] ; _yardAnimHandle
0011 push 0x4ec
0014 push 0xba
0017 push 0xaa
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
001f add sp, 0xc
0022 retf 
0023 nop 
0024 push -1
0026 push 0x4ec
0029 push 0xba
002c push 0xaa
002f push word ptr [0x1886] ; _yardAnimHandle
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0038 add sp, 0xa
003b mov word ptr [0x1892], ax
003e retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawSimBird', 'offset': 45462, 'source': None, 'size': 105}
- {'symbol': '_DrawSimCat', 'offset': 45568, 'source': None, 'size': 132}
- {'symbol': '_DrawMower', 'offset': 45764, 'source': None, 'size': 229}
- {'symbol': '_DrawAnimYardMessage', 'offset': 45994, 'source': None, 'size': 184}

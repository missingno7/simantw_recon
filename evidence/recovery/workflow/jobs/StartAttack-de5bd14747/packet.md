# Recovery task _StartAttack

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 66 bytes.

```asm
0000 push 0x64
0002 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0007 add sp, 2
000a add ax, 0x1e
000d mov es, word ptr [0xc4d0]
0011 mov word ptr es:[0x78dc], ax
0015 push 0x3f
0017 push 0x2b0a
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
001f add sp, 4
0022 push 0
0024 push 0
0026 push 0x78
0028 mov es, word ptr [0xc4ce]
002c les bx, ptr es:[0x7c94]
0031 push word ptr es:[bx + 0x16]
0035 push word ptr es:[bx + 0x14]
0039 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
003e add sp, 0xa
0041 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetModeProd', 'offset': 806, 'source': None, 'size': 156}
- {'symbol': '_GstrR', 'offset': 962, 'source': None, 'size': 332}
- {'symbol': '_ForceModeA', 'offset': 1360, 'source': None, 'size': None}
- {'symbol': '_ForceModeB', 'offset': 1570, 'source': None, 'size': None}

# Recovery task _IsMMMidiAvail

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 42 bytes.

```asm
0000 enter 4, 0
0004 mov es, word ptr [0xbf78]
0008 push word ptr es:[0x8d08]
000d push ds
000e push 0xafa
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0016 mov word ptr [bp - 4], ax
0019 mov word ptr [bp - 2], dx
001c or dx, ax
001e je 0x7738
0020 lcall [bp - 4]
0023 leave 
0024 retf 
0025 nop 
0026 xor ax, ax
0028 leave 
0029 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_gr_PutToBuf', 'offset': 30006, 'source': None, 'size': 342}
- {'symbol': '_UncompressDACInstrument', 'offset': 30348, 'source': None, 'size': 133}
- {'symbol': '_IsMMWaveAvail', 'offset': 30524, 'source': None, 'size': 42}
- {'symbol': '_CheckMMWave', 'offset': 30566, 'source': None, 'size': 168}

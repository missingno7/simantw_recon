# Recovery task _DoPreLoadInits

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 58 bytes.

```asm
0000 mov es, word ptr [0xc174]
0004 mov word ptr es:[0x9c70], 1
000b mov es, word ptr [0xc176]
000f sub ax, ax
0011 mov word ptr es:[0x8070], ax
0015 mov word ptr es:[0x806e], ax
0019 mov es, word ptr [0xc178]
001d mov word ptr es:[0x9b10], 0x12c
0024 mov word ptr es:[0x9b12], ax
0028 mov es, word ptr [0xc17a]
002c mov word ptr es:[0x9ea0], ax
0030 mov word ptr es:[0x9e9e], ax
0034 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RandYard
0039 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FileSelect', 'offset': 39200, 'source': None, 'size': 970}
- {'symbol': '_SpecialTutorialInit', 'offset': 40170, 'source': None, 'size': 153}
- {'symbol': '_DoLoadInitializations', 'offset': 40382, 'source': None, 'size': 481}
- {'symbol': '_LoadGame', 'offset': 40864, 'source': None, 'size': 669}

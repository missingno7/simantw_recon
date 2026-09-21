# Recovery task _DoSmells

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 79 bytes.

```asm
0000 mov es, word ptr [0xc30c]
0004 mov al, byte ptr es:[0x75fc]
0008 and ax, 0x60
000b sar ax, 5
000e or ax, ax
0010 je 0x316
0012 dec ax
0013 je 0x32a
0015 dec ax
0016 je 0x31b
0018 dec ax
0019 je 0x33a
001b ret 
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListA
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _HistUpdate
002b call 0xffff9380
002e ret 
002f nop 
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListB
0035 call 0xffff91de
0038 call 0xffff92aa
003b call 0xffff9306
003e ret 
003f nop 
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListR
0045 call 0xffff9244
0048 call 0xffff92d8
004b call 0xffff9344
004e ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntSim', 'offset': 0, 'source': None, 'size': 762}
- {'symbol': '_ClrModePop', 'offset': 842, 'source': None, 'size': 67}
- {'symbol': '_TallyModePop', 'offset': 910, 'source': None, 'size': 230}

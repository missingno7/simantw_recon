# Recovery task _SendBoyMsg

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 59 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 cmp si, 0x16
000a jg 0x15e6
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0011 add ax, 0x12c
0014 adc dx, 0
0017 mov es, word ptr [0xc4f6]
001b mov word ptr es:[0x7d4a], ax
001f mov word ptr es:[0x7d4c], dx
0024 mov es, word ptr [0xc504]
0028 mov word ptr es:[0x99da], 1
002f mov es, word ptr [0xc52a]
0033 mov word ptr es:[0x72f2], si
0038 pop si
0039 leave 
003a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitSimYard', 'offset': 4984, 'source': None, 'size': 304}
- {'symbol': '_DoSimYard', 'offset': 5288, 'source': None, 'size': 262}
- {'symbol': '_SimRain', 'offset': 5610, 'source': None, 'size': 177}
- {'symbol': '_SimKidOutside', 'offset': 5788, 'source': None, 'size': 2240}

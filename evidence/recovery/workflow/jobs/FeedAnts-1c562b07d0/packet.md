# Recovery task _FeedAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 100 bytes.

```asm
0000 mov es, word ptr [0xc30e]
0004 cmp word ptr es:[0x8a60], 0
000a jne 0x48c
000c dec word ptr [0xac86] ; _HealthB
0010 jns 0x48c
0012 mov word ptr [0xac86], 0 ; _HealthB
0018 dec word ptr [0xac88] ; _HealthR
001c jns 0x498
001e mov word ptr [0xac88], 0 ; _HealthR
0024 mov es, word ptr [0xc310]
0028 cmp word ptr es:[0x80b4], 3
002e je 0x4d7
0030 mov es, word ptr [0xc2fe]
0034 mov ax, word ptr es:[0x8a62]
0038 mov es, word ptr [0xc312]
003c cmp word ptr es:[0x9e84], ax
0041 jge 0x4d7
0043 push 1
0045 push 0x96
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddFood
004d add sp, 4
0050 push 0x32
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0057 add sp, 2
005a inc ax
005b mov es, word ptr [0xc2fe]
005f mov word ptr es:[0x8a62], ax
0063 ret 
```

## Known declaration examples

- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthR;` — src/recovered/DecEatR.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClrModePop', 'offset': 842, 'source': None, 'size': 67}
- {'symbol': '_TallyModePop', 'offset': 910, 'source': None, 'size': 230}
- {'symbol': '_DoAntSimA', 'offset': 1240, 'source': None, 'size': None}
- {'symbol': '_SimEggA', 'offset': 2588, 'source': None, 'size': 88}

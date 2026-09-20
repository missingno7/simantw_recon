# Recovery task _ClrModePop

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 67 bytes.

```asm
0000 push di
0001 xor ax, ax
0003 mov <resolved loader operand; see bindings> ; [{'operand_offset': 4, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0006 mov es, cx
0008 mov cx, 0x14
000b mov di, 0x7be4
000e rep stosw word ptr es:[di], ax
0010 mov <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0013 mov es, cx
0015 mov cx, 0x14
0018 mov di, 0x786a
001b rep stosw word ptr es:[di], ax
001d mov <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0020 mov ds, ax
0022 cmp word ptr [0x7c44], 0
0027 je 0x377
0029 dec word ptr [0x7c44]
002d mov <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0030 mov es, ax
0032 cmp word ptr es:[0x8078], 0
0038 je 0x389
003a dec word ptr es:[0x8078]
003f push ss
0040 pop ds
0041 pop di
0042 ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntSim', 'offset': 0, 'source': None, 'size': 762}
- {'symbol': '_DoSmells', 'offset': 762, 'source': None, 'size': 79}
- {'symbol': '_TallyModePop', 'offset': 910, 'source': None, 'size': 230}
- {'symbol': '_FeedAnts', 'offset': 1140, 'source': None, 'size': 100}

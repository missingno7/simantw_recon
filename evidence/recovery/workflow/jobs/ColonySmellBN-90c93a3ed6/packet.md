# Recovery task _ColonySmellBN

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 46 bytes.

```asm
0000 push di
0001 push si
0002 xor di, di
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0007 mov ds, ax
0009 xor bx, bx
000b mov si, di
000d add si, bx
000f add si, 0x62d2
0013 cmp byte ptr [si], 0
0016 je 0x92c4
0018 dec byte ptr [si]
001a inc bx
001b cmp bx, 0x20
001e jl 0x92b5
0020 add di, 0x20
0023 cmp di, 0x800
0027 jl 0x92b3
0029 push ss
002a pop ds
002b pop si
002c pop di
002d ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FillHolesBN', 'offset': 37342, 'source': None, 'size': 102}
- {'symbol': '_FillHolesRN', 'offset': 37444, 'source': None, 'size': 102}
- {'symbol': '_ColonySmellRN', 'offset': 37592, 'source': None, 'size': 46}
- {'symbol': '_ColonySmellBT', 'offset': 37638, 'source': None, 'size': 62}

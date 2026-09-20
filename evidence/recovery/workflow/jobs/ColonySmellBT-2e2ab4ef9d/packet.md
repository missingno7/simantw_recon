# Recovery task _ColonySmellBT

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 62 bytes.

```asm
0000 push di
0001 push si
0002 xor di, di
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0007 mov ds, ax
0009 xor bx, bx
000b mov si, di
000d add si, bx
000f add si, 0x6ad2
0013 mov cl, byte ptr [si]
0015 sub ch, ch
0017 cmp cx, 8
001a jge 0x9326
001c mov byte ptr [si], ch
001e jmp 0x9330
0020 mov ax, cx
0022 sar ax, 1
0024 sub ch, ch
0026 sub cl, al
0028 mov byte ptr [si], cl
002a inc bx
002b cmp bx, 0x20
002e jl 0x9311
0030 add di, 0x20
0033 cmp di, 0x800
0037 jl 0x930f
0039 push ss
003a pop ds
003b pop si
003c pop di
003d ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ColonySmellBN', 'offset': 37546, 'source': None, 'size': 46}
- {'symbol': '_ColonySmellRN', 'offset': 37592, 'source': None, 'size': 46}
- {'symbol': '_ColonySmellRT', 'offset': 37700, 'source': None, 'size': 60}
- {'symbol': '_SmoothAlarm', 'offset': 37760, 'source': None, 'size': 187}

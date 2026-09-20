# Recovery task _ColonySmellRT

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 60 bytes.

```asm
0000 push di
0001 push si
0002 xor di, di
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0007 mov ds, ax
0009 xor bx, bx
000b mov si, di
000d add si, bx
000f add si, 0x7ad2
0013 mov cl, byte ptr [si]
0015 sub ch, ch
0017 or cx, cx
0019 jle 0x936c
001b cmp cx, 8
001e jge 0x9368
0020 mov byte ptr [si], ch
0022 jmp 0x936c
0024 sar cx, 1
0026 sub byte ptr [si], cl
0028 inc bx
0029 cmp bx, 0x20
002c jl 0x934f
002e add di, 0x20
0031 cmp di, 0x800
0035 jl 0x934d
0037 push ss
0038 pop ds
0039 pop si
003a pop di
003b ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ColonySmellRN', 'offset': 37592, 'source': None, 'size': 46}
- {'symbol': '_ColonySmellBT', 'offset': 37638, 'source': None, 'size': 62}
- {'symbol': '_SmoothAlarm', 'offset': 37760, 'source': None, 'size': 187}
- {'symbol': '_AlarmHere', 'offset': 37948, 'source': None, 'size': 65}

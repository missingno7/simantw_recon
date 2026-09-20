# Recovery task _UnRecruitRed

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 54 bytes.

```asm
0000 push si
0001 mov es, word ptr [0xc4d2]
0005 mov si, word ptr es:[0x80f0]
000a or si, si
000c jle 0x90e
000e mov <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0011 mov ds, ax
0013 dec si
0014 mov cl, byte ptr [si + 0x2f62]
0018 sub ch, ch
001a or cx, cx
001c je 0x908
001e cmp cx, 0x7f
0021 jle 0x908
0023 cmp byte ptr [si + 0x2b78], 6
0028 jne 0x908
002a mov byte ptr [si + 0x2b78], ch
002e or si, si
0030 jg 0x8ed
0032 push ss
0033 pop ds
0034 pop si
0035 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UnRecruit', 'offset': 1930, 'source': None, 'size': 220}
- {'symbol': '_RecruitRed', 'offset': 2150, 'source': None, 'size': 115}
- {'symbol': '_GetNewMode', 'offset': 2320, 'source': None, 'size': 192}
- {'symbol': '_GetNewModeB', 'offset': 2512, 'source': None, 'size': 127}

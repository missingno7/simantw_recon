# Recovery task _DrownRList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 79 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc42a]
0009 mov si, word ptr es:[0x72cc]
000e or si, si
0010 jle 0x2db1
0012 mov di, word ptr [bp + 6]
0015 mov <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0018 mov ds, ax
001a dec si
001b mov al, byte ptr [si + 0x42fa]
001f sub ah, ah
0021 cmp ax, di
0023 jne 0x2dab
0025 cmp byte ptr [si + 0x46e6], ah
0029 je 0x2dab
002b mov cl, byte ptr [si + 0x46e6]
002f and cl, 0x78
0032 shr cl, 3
0035 sub ch, ch
0037 or cx, cx
0039 jle 0x2dab
003b cmp cx, 0xc
003e jge 0x2dab
0040 mov byte ptr [si + 0x44f0], 0x11
0045 or si, si
0047 jg 0x2d80
0049 push ss
004a pop ds
004b pop si
004c pop di
004d leave 
004e retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_FindInBList-d950932078.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_FindInRList-130e8e266c.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentBN-cd34069882.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindInRList', 'offset': 11470, 'source': 'src/recovered/wf_FindInRList-130e8e266c.c', 'size': 72}
- {'symbol': '_DrownBList', 'offset': 11542, 'source': None, 'size': 79}
- {'symbol': '_ExitHole', 'offset': 11702, 'source': None, 'size': 313}
- {'symbol': '_AddAntToAList', 'offset': 12016, 'source': None, 'size': 89}

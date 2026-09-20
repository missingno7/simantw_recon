# Recovery task _FindInRList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 72 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 mov es, word ptr [0xc42a]
0008 mov bx, word ptr es:[0x72cc]
000d mov cx, word ptr [bp + 6]
0010 mov di, word ptr [bp + 8]
0013 mov <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0016 mov ds, ax
0018 or bx, bx
001a jle 0x2d0e
001c dec bx
001d mov al, byte ptr [bx + 0x4104]
0021 sub ah, ah
0023 cmp ax, cx
0025 jne 0x2ce6
0027 mov al, byte ptr [bx + 0x42fa]
002b cmp ax, di
002d jne 0x2ce6
002f mov al, byte ptr [bx + 0x46e6]
0033 cmp ax, word ptr [bp + 0xa]
0036 jne 0x2ce6
0038 push ss
0039 pop ds
003a mov ax, bx
003c pop di
003d leave 
003e retf 
003f nop 
0040 push ss
0041 pop ds
0042 mov ax, 0xffff
0045 pop di
0046 leave 
0047 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_FindInBList-d950932078.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentBN-cd34069882.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentBT-86d27c2a8a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindInAList', 'offset': 11330, 'source': None, 'size': 68}
- {'symbol': '_FindInBList', 'offset': 11398, 'source': 'src/recovered/wf_FindInBList-d950932078.c', 'size': 72}
- {'symbol': '_DrownBList', 'offset': 11542, 'source': None, 'size': 79}
- {'symbol': '_DrownRList', 'offset': 11622, 'source': None, 'size': 79}

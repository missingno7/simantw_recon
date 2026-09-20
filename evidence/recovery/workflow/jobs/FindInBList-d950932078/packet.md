# Recovery task _FindInBList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 72 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 mov es, word ptr [0xc428]
0008 mov bx, word ptr es:[0x99d4]
000d mov cx, word ptr [bp + 6]
0010 mov di, word ptr [bp + 8]
0013 mov <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0016 mov ds, ax
0018 or bx, bx
001a jle 0x2cc6
001c dec bx
001d mov al, byte ptr [bx + 0x3736]
0021 sub ah, ah
0023 cmp ax, cx
0025 jne 0x2c9e
0027 mov al, byte ptr [bx + 0x392c]
002b cmp ax, di
002d jne 0x2c9e
002f mov al, byte ptr [bx + 0x3d18]
0033 cmp ax, word ptr [bp + 0xa]
0036 jne 0x2c9e
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

- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentBN-cd34069882.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentBT-86d27c2a8a.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentRN-18f9c8a2bb.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RemoveFromAList', 'offset': 11074, 'source': None, 'size': 255}
- {'symbol': '_FindInAList', 'offset': 11330, 'source': None, 'size': 68}
- {'symbol': '_FindInRList', 'offset': 11470, 'source': None, 'size': 72}
- {'symbol': '_DrownBList', 'offset': 11542, 'source': None, 'size': 79}

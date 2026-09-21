# Recovery task _AddAntToAList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 89 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0008 mov es, ax
000a cmp word ptr es:[0x80f0], 0x3e8
0011 jge 0x2f43
0013 mov si, word ptr [bp + 6]
0016 mov <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0019 mov ds, ax
001b mov ax, si
001d mov bx, word ptr es:[0x80f0]
0022 mov byte ptr [bx + 0x23a4], al
0026 mov di, word ptr [bp + 8]
0029 mov ax, di
002b mov byte ptr [bx + 0x278e], al
002f mov al, byte ptr [bp + 0xc]
0032 mov byte ptr [bx + 0x2b78], al
0036 mov cx, word ptr [bp + 0xa]
0039 mov byte ptr [bx + 0x2f62], cl
003d mov al, byte ptr [bp + 0xe]
0040 mov byte ptr [bx + 0x334c], al
0044 shl si, 6
0047 add di, si
0049 mov byte ptr ss:[di + 0x68e8], cl
004e inc word ptr es:[0x80f0]
0053 push ss
0054 pop ds
0055 pop si
0056 pop di
0057 leave 
0058 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeB-f9a6e1c57a.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeR-d74962e731.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_FindInBList-d950932078.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrownRList', 'offset': 11622, 'source': None, 'size': 79}
- {'symbol': '_ExitHole', 'offset': 11702, 'source': None, 'size': 313}
- {'symbol': '_AddAntToBList', 'offset': 12106, 'source': None, 'size': 89}
- {'symbol': '_AddAntToRList', 'offset': 12196, 'source': None, 'size': 89}

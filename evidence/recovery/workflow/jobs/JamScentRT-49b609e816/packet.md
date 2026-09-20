# Recovery task _JamScentRT

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 63 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0008 mov es, ax
000a mov di, word ptr [bp + 4]
000d mov bx, word ptr [bp + 6]
0010 mov cx, word ptr [bp + 8]
0013 mov si, di
0015 and si, 0xfffe
0018 shl si, 4
001b mov ax, bx
001d sar ax, 1
001f add si, ax
0021 mov al, byte ptr es:[si + 0x7ad2]
0026 sub ah, ah
0028 cmp ax, cx
002a jge 0x95b1
002c and di, 0xfffe
002f shl di, 4
0032 sar bx, 1
0034 add di, bx
0036 mov byte ptr es:[di + 0x7ad2], cl
003b pop si
003c pop di
003d leave 
003e ret 
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

- {'symbol': '_JamScentRN', 'offset': 38134, 'source': 'src/recovered/wf_JamScentRN-18f9c8a2bb.c', 'size': 63}
- {'symbol': '_JamScentBT', 'offset': 38198, 'source': 'src/recovered/wf_JamScentBT-86d27c2a8a.c', 'size': 63}
- {'symbol': '_DecTSmell', 'offset': 38326, 'source': None, 'size': 92}
- {'symbol': '_GetSmellT', 'offset': 38418, 'source': None, 'size': 106}

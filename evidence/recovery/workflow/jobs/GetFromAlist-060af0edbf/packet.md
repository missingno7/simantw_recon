# Recovery task _GetFromAlist

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 72 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc426]
0009 mov si, word ptr es:[0x80f0]
000e mov di, word ptr [bp + 6]
0011 mov <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0014 mov ds, ax
0016 or si, si
0018 jle 0x302a
001a dec si
001b mov cl, byte ptr [si + 0x2f62]
001f sub ch, ch
0021 or cx, cx
0023 je 0x3014
0025 sar cx, 7
0028 cmp cx, di
002a jne 0x3014
002c push ss
002d pop ds
002e or si, si
0030 je 0x3040
0032 push si
0033 nop 
0034 push cs
0035 call 0x2b42 ; _RemoveFromAList
0038 add sp, 2
003b mov ax, 1
003e pop si
003f pop di
0040 leave 
0041 retf 
0042 xor ax, ax
0044 pop si
0045 pop di
0046 leave 
0047 retf 
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

- {'symbol': '_AddAntToBList', 'offset': 12106, 'source': None, 'size': 89}
- {'symbol': '_AddAntToRList', 'offset': 12196, 'source': None, 'size': 89}
- {'symbol': '_BuildAntListA', 'offset': 12358, 'source': None, 'size': 162}
- {'symbol': '_ClearListB', 'offset': 12520, 'source': 'src/recovered/ClearListB.c', 'size': 12}

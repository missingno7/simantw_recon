# Recovery task _RecruitRed

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 115 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 mov ax, word ptr [bp + 6]
0008 mov word ptr [bp - 4], ax
000b mov es, word ptr [0xc4d2]
000f mov si, word ptr es:[0x80f0]
0014 or si, si
0016 jle 0x8d6
0018 mov <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001b mov ds, ax
001d cmp word ptr [bp - 4], 0
0021 jg 0x88e
0023 push ss
0024 pop ds
0025 pop si
0026 leave 
0027 retf 
0028 dec si
0029 mov cl, byte ptr [si + 0x2f62]
002d sub ch, ch
002f or cx, cx
0031 je 0x8cf
0033 cmp cx, 0x7f
0036 jle 0x8cf
0038 mov bx, si
003a add bx, 0x2b78
003e mov bl, byte ptr [bx]
0040 sub bh, bh
0042 and cx, 0x78
0045 sar cx, 3
0048 cmp cx, 2
004b je 0x8b8
004d cmp cx, 6
0050 jne 0x8cf
0052 cmp bx, 0x13
0055 je 0x8cf
0057 cmp bx, 6
005a je 0x8cf
005c mov byte ptr [si + 0x2b78], 6
0061 mov byte ptr [si + 0x334c], 0
0066 dec word ptr [bp - 4]
0069 or si, si
006b jg 0x883
006d jmp 0x889
006f nop 
0070 pop si
0071 leave 
0072 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeB-f9a6e1c57a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Recruit', 'offset': 1746, 'source': None, 'size': 184}
- {'symbol': '_UnRecruit', 'offset': 1930, 'source': None, 'size': 220}
- {'symbol': '_UnRecruitRed', 'offset': 2266, 'source': None, 'size': 54}
- {'symbol': '_GetNewMode', 'offset': 2320, 'source': None, 'size': 192}

# Recovery task _DoRepoLoit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 91 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0009 or ax, ax
000b je 0xc34
000d mov si, word ptr [bp + 4]
0010 push si
0011 call 0x1234 ; _DoRandAntAA
0014 jmp 0xc3b
0016 mov si, word ptr [bp + 4]
0019 push si
001a call 0x1676 ; _DoToNestAnt
001d add sp, 2
0020 mov <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0023 mov ds, ax
0025 test byte ptr [si + 0x2f62], 0x80
002a je 0xc58
002c mov <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002f mov es, ax
0031 cmp word ptr es:[0x8078], 0x64
0037 jmp 0xc63
0039 nop 
003a mov <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
003d mov es, ax
003f cmp word ptr es:[0x7c44], 0x64
0045 jle 0xc74
0047 mov <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004a mov es, ax
004c mov bx, word ptr es:[0x9b6a]
0051 mov byte ptr [bx + 0x2b78], 0xf
0056 push ss
0057 pop ds
0058 pop si
0059 leave 
005a ret 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeB-f9a6e1c57a.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LostHeadA', 'offset': 2846, 'source': None, 'size': 87}
- {'symbol': '_DoRestAnt', 'offset': 2934, 'source': None, 'size': 168}
- {'symbol': '_DoRepoExit', 'offset': 3194, 'source': None, 'size': 208}
- {'symbol': '_DoRepoFly', 'offset': 3402, 'source': None, 'size': 172}

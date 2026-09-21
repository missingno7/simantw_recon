# Recovery task _DecTSmell

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 92 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov bx, word ptr [bp + 4]
0008 sar bx, 1
000a mov di, word ptr [bp + 6]
000d sar di, 1
000f cmp word ptr [bp + 8], 0
0013 je 0x95f0
0015 mov <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0018 mov es, ax
001a mov si, bx
001c shl si, 5
001f add si, di
0021 cmp byte ptr es:[si + 0x7ad2], 0
0027 je 0x960e
0029 mov si, bx
002b shl si, 5
002e add si, di
0030 dec byte ptr es:[si + 0x7ad2]
0035 pop si
0036 pop di
0037 leave 
0038 ret 
0039 nop 
003a mov <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003d mov es, ax
003f mov si, bx
0041 shl si, 5
0044 add si, di
0046 cmp byte ptr es:[si + 0x6ad2], 0
004c je 0x960e
004e shl bx, 5
0051 add bx, di
0053 dec byte ptr es:[bx + 0x6ad2]
0058 pop si
0059 pop di
005a leave 
005b ret 
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

- {'symbol': '_JamScentBT', 'offset': 38198, 'source': 'src/recovered/wf_JamScentBT-86d27c2a8a.c', 'size': 63}
- {'symbol': '_JamScentRT', 'offset': 38262, 'source': 'src/recovered/wf_JamScentRT-49b609e816.c', 'size': 63}
- {'symbol': '_GetSmellT', 'offset': 38418, 'source': None, 'size': 106}
- {'symbol': '_MakeRedInitiator', 'offset': 38524, 'source': None, 'size': 88}

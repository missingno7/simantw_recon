# Recovery task _FillHolesBN

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 102 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 xor si, si
0007 mov <resolved loader operand; see bindings> ; [{'operand_offset': 8, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
000a mov ds, ax
000c mov <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
000f mov es, ax
0011 cmp byte ptr [si - 0x7d2e], 0
0016 je 0x9239
0018 mov bl, byte ptr [si - 0x7d2e]
001c sub bh, bh
001e mov word ptr [bp - 2], bx
0021 shl bx, 6
0024 add bx, si
0026 cmp byte ptr ss:[bx + 0x28e8], 0x51
002c je 0x9224
002e mov bx, word ptr [bp - 2]
0031 and bl, 0xfe
0034 shl bx, 4
0037 mov ax, si
0039 sar ax, 1
003b add bx, ax
003d mov byte ptr es:[bx + 0x62d2], 0xff
0043 jmp 0x9239
0045 nop 
0046 mov bx, word ptr [bp - 2]
0049 and bl, 0xfe
004c shl bx, 4
004f mov ax, si
0051 sar ax, 1
0053 add bx, ax
0055 mov byte ptr es:[bx + 0x62d2], 0
005b inc si
005c cmp si, 0x40
005f jl 0x91ef
0061 push ss
0062 pop ds
0063 pop si
0064 leave 
0065 ret 
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

- {'symbol': '_GetMyBestDir', 'offset': 36154, 'source': None, 'size': 399}
- {'symbol': '_GetMyDir', 'offset': 36554, 'source': None, 'size': 788}
- {'symbol': '_FillHolesRN', 'offset': 37444, 'source': None, 'size': 102}
- {'symbol': '_ColonySmellBN', 'offset': 37546, 'source': None, 'size': 46}

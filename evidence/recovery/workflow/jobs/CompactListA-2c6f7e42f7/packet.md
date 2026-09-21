# Recovery task _CompactListA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 99 bytes.

```asm
0000 push di
0001 push si
0002 mov <resolved loader operand; see bindings> ; [{'operand_offset': 3, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0005 mov es, ax
0007 xor si, si
0009 mov di, si
000b cmp word ptr es:[0x80f0], si
0010 jle 0x2a71
0012 mov <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0015 mov ds, ax
0017 cmp byte ptr [si + 0x2f62], 0
001c je 0x2a66
001e or di, di
0020 je 0x2a67
0022 mov al, byte ptr [si + 0x2f62]
0026 mov bx, di
0028 add bx, si
002a mov byte ptr [bx + 0x2f62], al
002e mov al, byte ptr [si + 0x23a4]
0032 mov byte ptr [bx + 0x23a4], al
0036 mov al, byte ptr [si + 0x278e]
003a mov byte ptr [bx + 0x278e], al
003e mov al, byte ptr [si + 0x2b78]
0042 mov byte ptr [bx + 0x2b78], al
0046 mov al, byte ptr [si + 0x334c]
004a mov byte ptr [bx + 0x334c], al
004e jmp 0x2a67
0050 dec di
0051 inc si
0052 cmp word ptr es:[0x80f0], si
0057 jg 0x2a2d
0059 push ss
005a pop ds
005b add word ptr es:[0x80f0], di
0060 pop si
0061 pop di
0062 retf 
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

- {'symbol': '_FixExitMapR', 'offset': 10516, 'source': None, 'size': 198}
- {'symbol': '_FloodNestB', 'offset': 10714, 'source': None, 'size': 60}
- {'symbol': '_CompactListB', 'offset': 10874, 'source': None, 'size': 99}
- {'symbol': '_CompactListR', 'offset': 10974, 'source': None, 'size': 99}

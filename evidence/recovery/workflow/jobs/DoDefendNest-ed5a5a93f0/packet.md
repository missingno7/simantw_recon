# Recovery task _DoDefendNest

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 112 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0007 mov es, ax
0009 mov bx, word ptr [bp + 4]
000c test byte ptr es:[bx + 0x2f62], 0x80
0012 je 0xe2c
0014 mov bl, byte ptr es:[bx + 0x23a4]
0019 and bx, 0xfe
001d shl bx, 4
0020 mov si, word ptr [bp + 4]
0023 mov al, byte ptr es:[si + 0x278e]
0028 shr al, 1
002a sub ah, ah
002c add bx, ax
002e mov cl, byte ptr es:[bx + 0x72d2]
0033 jmp 0xe4b
0035 nop 
0036 mov bl, byte ptr es:[bx + 0x23a4]
003b and bx, 0xfe
003f shl bx, 4
0042 mov si, word ptr [bp + 4]
0045 mov al, byte ptr es:[si + 0x278e]
004a shr al, 1
004c sub ah, ah
004e add bx, ax
0050 mov cl, byte ptr es:[bx + 0x62d2]
0055 sub ch, ch
0057 cmp cx, 0x6e
005a jge 0xe5c
005c push si
005d call 0x1676 ; _DoToNestAnt
0060 add sp, 2
0063 pop si
0064 leave 
0065 ret 
0066 push si
0067 call 0x1234 ; _DoRandAntAA
006a add sp, 2
006d pop si
006e leave 
006f ret 
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

- {'symbol': '_DoRepoExit', 'offset': 3194, 'source': None, 'size': 208}
- {'symbol': '_DoRepoFly', 'offset': 3402, 'source': None, 'size': 172}
- {'symbol': '_DoRandAntA', 'offset': 3686, 'source': None, 'size': 974}
- {'symbol': '_DoRandAntAA', 'offset': 4660, 'source': None, 'size': 588}

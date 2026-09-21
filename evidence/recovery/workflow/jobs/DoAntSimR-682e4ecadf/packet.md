# Recovery task _DoAntSimR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 95 bytes.

```asm
0000 push si
0001 mov es, word ptr [0xc382]
0005 mov ax, word ptr es:[0x72cc]
0009 mov es, word ptr [0xc384]
000d mov word ptr es:[0x9b6a], ax
0011 or ax, ax
0013 jle 0x53a1
0015 mov <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0018 mov ds, ax
001a mov <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001d mov es, ax
001f dec word ptr [0x9b6a]
0023 mov bx, word ptr [0x9b6a]
0027 mov al, byte ptr es:[bx + 0x4104]
002c sub ah, ah
002e mov si, word ptr es:[bx + 0x42fa]
0033 and si, 0xff
0037 mov cl, byte ptr es:[bx + 0x46e6]
003c sub ch, ch
003e or cx, cx
0040 je 0x5398
0042 push ss
0043 pop ds
0044 push cx
0045 push si
0046 push ax
0047 nop 
0048 push cs
0049 call 0x53a4 ; _DoNestAntR
004c add sp, 6
004f mov <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0052 mov ds, ax
0054 cmp word ptr [0x9b6a], 0
0059 jg 0x535e
005b push ss
005c pop ds
005d pop si
005e retf 
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

- {'symbol': '_LeaveNestB', 'offset': 20830, 'source': None, 'size': 172}
- {'symbol': '_GetOutB', 'offset': 21002, 'source': None, 'size': 314}
- {'symbol': '_DoNestAntR', 'offset': 21412, 'source': None, 'size': None}
- {'symbol': '_RaidInR', 'offset': 23338, 'source': None, 'size': 235}

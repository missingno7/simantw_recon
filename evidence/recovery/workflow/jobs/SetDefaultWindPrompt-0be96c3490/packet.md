# Recovery task _SetDefaultWindPrompt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 141 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov es, word ptr [0xbef6]
0007 cmp word ptr es:[0x9c28], 0
000d jne 0x60e8
000f push word ptr [bp + 6]
0012 push -1
0014 push -2
0016 push 0
0018 push 0
001a jmp 0x6152
001c mov <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
001f mov es, ax
0021 cmp word ptr es:[0x7c22], -1
0027 jne 0x6110
0029 push word ptr [bp + 6]
002c push -1
002e push -2
0030 mov es, word ptr [0xbef4]
0034 les bx, ptr es:[0x737a]
0039 push word ptr es:[bx + 0xa]
003d push word ptr es:[bx + 8]
0041 jmp 0x6152
0043 nop 
0044 cmp word ptr es:[0x7c22], 0xa
004a jne 0x6132
004c push word ptr [bp + 6]
004f push -1
0051 push -2
0053 mov es, word ptr [0xbef4]
0057 les bx, ptr es:[0x737a]
005c push word ptr es:[bx + 0xe]
0060 push word ptr es:[bx + 0xc]
0064 jmp 0x6152
0066 cmp word ptr es:[0x7c22], 0xb
006c jne 0x6157
006e push word ptr [bp + 6]
0071 push -1
0073 push -2
0075 mov es, word ptr [0xbef4]
0079 les bx, ptr es:[0x737a]
007e push word ptr es:[bx + 0x46]
0082 push word ptr es:[bx + 0x44]
0086 nop 
0087 push cs
0088 call 0x92c0 ; _EditMessage
008b leave 
008c retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ScoreDialog', 'offset': 23722, 'source': None, 'size': 244}
- {'symbol': '_DrawCastePopUp', 'offset': 23966, 'source': None, 'size': 814}
- {'symbol': '_PictStrnDialog', 'offset': 24922, 'source': None, 'size': 155}
- {'symbol': '_win_DrawPictureWindow', 'offset': 25078, 'source': None, 'size': 198}

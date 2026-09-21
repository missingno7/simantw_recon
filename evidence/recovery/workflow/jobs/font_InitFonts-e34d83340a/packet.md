# Recovery task _font_InitFonts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 169 bytes.

```asm
0000 mov es, word ptr [0xc16c]
0004 mov word ptr es:[0x7d20], 0x8e88
000b mov <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0012 push ds
0013 push 0x168a
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_ReadFont
001b add sp, 4
001e mov es, word ptr [0xc16a]
0022 mov word ptr es:[0x8e60], ax
0026 mov word ptr es:[0x8e62], dx
002b push ds
002c push 0x1690
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_ReadFont
0034 add sp, 4
0037 mov es, word ptr [0xc16a]
003b mov word ptr es:[0x8e64], ax
003f mov word ptr es:[0x8e66], dx
0044 push ds
0045 push 0x1696
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_ReadFont
004d add sp, 4
0050 mov es, word ptr [0xc16a]
0054 mov word ptr es:[0x8e68], ax
0058 mov word ptr es:[0x8e6a], dx
005d push ds
005e push 0x169c
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_ReadFont
0066 add sp, 4
0069 mov es, word ptr [0xc16a]
006d mov word ptr es:[0x8e6c], ax
0071 mov word ptr es:[0x8e6e], dx
0076 push ds
0077 push 0x16a2
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_ReadFont
007f add sp, 4
0082 mov es, word ptr [0xc16a]
0086 mov word ptr es:[0x8e70], ax
008a mov word ptr es:[0x8e72], dx
008f push ds
0090 push 0x16a8
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_ReadFont
0098 add sp, 4
009b mov es, word ptr [0xc16a]
009f mov word ptr es:[0x8e74], ax
00a3 mov word ptr es:[0x8e76], dx
00a8 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_font_StringWidth', 'offset': 24782, 'source': None, 'size': 78}
- {'symbol': '_font_SetFont', 'offset': 24860, 'source': None, 'size': 80}
- {'symbol': '_font_PrintStr', 'offset': 25110, 'source': 'src/recovered/wf_font_PrintStr-23d609869e.c', 'size': 165}
- {'symbol': '_WinPrintf', 'offset': 25276, 'source': 'src/recovered/wf_WinPrintf-d81cd63317.c', 'size': 101}

# Recovery task _MSClipEnd

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 70 bytes.

```asm
0000 cmp word ptr [0xcc52], 0
0005 je 0x3e62
0007 push word ptr [0xcf52] ; _clipDC
000b push word ptr [0xcc52]
000f push 0
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 282}}]
0016 cmp word ptr [0xcc54], 0
001b je 0x3e7c
001d push word ptr [0xcf52] ; _clipDC
0021 push word ptr [0xcc54]
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
002a mov word ptr [0xcc54], 0
0030 push word ptr [0xce8e] ; _clipWind
0034 push word ptr [0xcf52] ; _clipDC
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
003d xor ax, ax
003f mov word ptr [0xce8e], ax ; _clipWind
0042 mov word ptr [0xcf52], ax ; _clipDC
0045 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GImgSize', 'offset': 15830, 'source': 'src/recovered/GImgSize.c', 'size': 35}
- {'symbol': '_MSClipStart', 'offset': 15866, 'source': None, 'size': 81}
- {'symbol': '_PaintStuff', 'offset': 16018, 'source': None, 'size': 290}
- {'symbol': '_GLine', 'offset': 16308, 'source': None, 'size': 132}

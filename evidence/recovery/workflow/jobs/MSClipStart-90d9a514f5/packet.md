# Recovery task _MSClipStart

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 81 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push 0
0005 push 0x4e20
0008 nop 
0009 push cs
000a call 0x56a8 ; _RallocFindMem
000d mov sp, bp
000f mov word ptr [0xcd84], 0 ; _updateRgn
0015 mov ax, word ptr [bp + 6]
0018 mov word ptr [0xce8e], ax ; _clipWind
001b push ax
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 66}}]
0021 mov word ptr [0xcf52], ax ; _clipDC
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InitPalette
0029 push word ptr [0xcf52] ; _clipDC
002d push word ptr [0x85a] ; _paletteH
0031 push 0
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 282}}]
0038 mov word ptr [0xcc52], ax
003b push word ptr [0xcf52] ; _clipDC
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 283}}]
0044 mov word ptr [0xcc54], 0
004a nop 
004b push cs
004c call 0x1664 ; _GSetBigFont
004f leave 
0050 retf 
```

## Known declaration examples

- `extern void far RallocFindMem(int low, int high);` — src/recovered/wf_RallocFree-a82b13cb86.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near clipWind;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near paletteH;` — src/recovered/ClosePalette.c
- `extern int near paletteH[];` — src/recovered/SetDebugFlag.c
- `extern int near paletteH[];` — src/recovered/mem_Debugging.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GPicSize', 'offset': 15794, 'source': 'src/recovered/GPicSize.c', 'size': 36}
- {'symbol': '_GImgSize', 'offset': 15830, 'source': 'src/recovered/GImgSize.c', 'size': 35}
- {'symbol': '_MSClipEnd', 'offset': 15948, 'source': 'src/recovered/wf_MSClipEnd-48c3851864.c', 'size': 70}
- {'symbol': '_PaintStuff', 'offset': 16018, 'source': None, 'size': 290}

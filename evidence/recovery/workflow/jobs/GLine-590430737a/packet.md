# Recovery task _GLine

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 132 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xe]
0009 test byte ptr [0xcc7e], 1 ; _displayType
000e jne 0x3fd6
0010 push 0
0012 push 1
0014 mov ax, di
0016 and ax, 0xf
0019 cdq 
001a or dh, 1
001d push dx
001e push ax
001f jmp 0x3ff0
0021 nop 
0022 test di, 0x40
0026 je 0x3fe8
0028 push 0
002a push 1
002c push 0xff
002f push -1
0031 jmp 0x3ff0
0033 nop 
0034 push 0
0036 push 1
0038 push 0
003a push 0
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 61}}]
0041 mov si, ax
0043 push word ptr [0xcf52] ; _clipDC
0047 push si
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
004d mov word ptr [bp - 2], ax
0050 push word ptr [0xcf52] ; _clipDC
0054 push word ptr [bp + 6]
0057 push word ptr [bp + 8]
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 91, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 20}}]
005f push word ptr [0xcf52] ; _clipDC
0063 push word ptr [bp + 0xa]
0066 push word ptr [bp + 0xc]
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 19}}]
006e push word ptr [0xcf52] ; _clipDC
0072 push word ptr [bp - 2]
0075 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
007a push si
007b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
0080 pop si
0081 pop di
0082 leave 
0083 retf 
```

## Known declaration examples

- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPic-08fc158e1c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MSClipEnd', 'offset': 15948, 'source': 'src/recovered/wf_MSClipEnd-48c3851864.c', 'size': 70}
- {'symbol': '_PaintStuff', 'offset': 16018, 'source': None, 'size': 290}
- {'symbol': '_RedrawScreen', 'offset': 16440, 'source': 'src/recovered/RedrawScreen.c', 'size': 25}
- {'symbol': '_GBoxMove', 'offset': 16466, 'source': 'src/recovered/wf_GBoxMove-31918745e5.c', 'size': 129}

# Recovery task _GBoxMove

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 129 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push 0
000b push 0
000d push 0xa
000f push 0xa
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
0016 mov si, ax
0018 mov word ptr [bp - 8], di
001b mov ax, word ptr [bp + 0xa]
001e mov word ptr [bp - 4], ax
0021 mov cx, word ptr [bp + 8]
0024 mov word ptr [bp - 6], cx
0027 mov dx, word ptr [bp + 0xc]
002a mov word ptr [bp - 2], dx
002d mov word ptr [bp - 0xe], cx
0030 mov word ptr [bp - 0xa], dx
0033 mov word ptr [bp - 0x10], di
0036 mov word ptr [bp - 0xc], ax
0039 push word ptr [0xce8e] ; _clipWind
003d sub di, word ptr [bp + 0xe]
0040 neg di
0042 push di
0043 sub cx, word ptr [bp + 0x10]
0046 neg cx
0048 push cx
0049 lea ax, [bp - 8]
004c push ss
004d push ax
004e lea ax, [bp - 0x10]
0051 push ss
0052 push ax
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 61}}]
0058 push word ptr [0xce8e] ; _clipWind
005c push si
005d push 0
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 237}}]
0064 push word ptr [0xce8e] ; _clipWind
0068 push si
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 128}}]
006e push word ptr [0xce8e] ; _clipWind
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 115, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0077 push si
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
007d pop si
007e pop di
007f leave 
0080 retf 
```

## Known declaration examples

- `extern int near clipWind;` — src/recovered/wf_MSClipEnd-48c3851864.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GLine', 'offset': 16308, 'source': None, 'size': 132}
- {'symbol': '_RedrawScreen', 'offset': 16440, 'source': 'src/recovered/RedrawScreen.c', 'size': 25}
- {'symbol': '_GUnpackPic', 'offset': 16596, 'source': None, 'size': 186}
- {'symbol': '_DrawBitMapToBuffer', 'offset': 16782, 'source': None, 'size': 1004}

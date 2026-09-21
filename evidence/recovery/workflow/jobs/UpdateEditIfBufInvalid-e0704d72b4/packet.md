# Recovery task _UpdateEditIfBufInvalid

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 82 bytes.

```asm
0000 push si
0001 mov es, word ptr [0xbf8a]
0005 cmp word ptr es:[0x8df6], 0
000b je 0x14ec
000d push 0
000f push 0
0011 push 0xa
0013 push 0xa
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
001a mov si, ax
001c push word ptr [0xbca6] ; _win_hwnd
0020 push si
0021 push 0
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 237}}]
0028 push word ptr [0xbca6] ; _win_hwnd
002c push si
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 128}}]
0032 push word ptr [0xbca6] ; _win_hwnd
0036 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
003b push si
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
0041 mov word ptr [0x144e], 1 ; _editForce
0047 call 0x16d4
004a mov word ptr [0x144e], 0 ; _editForce
0050 pop si
0051 retf 
```

## Known declaration examples

- `extern int near editForce;` — src/recovered/InvalidUpdateEdit.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd;` — src/recovered/InvalidUpdateEdit.c
- `extern int near win_hwnd[];` — src/recovered/win_ToTop.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateEdit', 'offset': 4576, 'source': None, 'size': 694}
- {'symbol': '_UpdateEditWindow', 'offset': 5270, 'source': 'src/recovered/UpdateEditWindow.c', 'size': 6}
- {'symbol': '_DrawEdit', 'offset': 5358, 'source': 'src/recovered/DrawEdit.c', 'size': 1}
- {'symbol': '_win_DrawEditWindow', 'offset': 5360, 'source': None, 'size': 195}

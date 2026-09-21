# Recovery task _ClearBookmarks

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 125 bytes.

```asm
0000 push di
0001 push si
0002 xor di, di
0004 mov si, 0x8aa0
0007 mov es, word ptr [0xbe7a]
000b mov word ptr es:[si], 0xffff
0010 xor ax, ax
0012 mov word ptr es:[si + 2], ax
0016 xor cx, cx
0018 mov word ptr es:[si + 4], ax
001c mov word ptr es:[si + 6], cx
0020 mov word ptr es:[si + 8], ax
0024 lea dx, [di + 0x3867]
0028 push dx
0029 lea bx, [di + 0x3899]
002d push bx
002e lea ax, [di + 0x2218]
0032 push ax
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
0038 add sp, 6
003b push 0
003d lea ax, [di + 0x2218]
0041 push ax
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0047 add sp, 4
004a lea ax, [di + 0x3867]
004e push ax
004f lea ax, [di + 0x3899]
0053 push ax
0054 lea ax, [di + 0x2313]
0058 push ax
0059 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
005e add sp, 6
0061 push 0
0063 lea ax, [di + 0x2313]
0067 push ax
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
006d add sp, 4
0070 inc di
0071 add si, 0xa
0074 cmp si, 0x8ae6
0078 jb 0xaaf
007a pop si
007b pop di
007c retf 
```

## Known declaration examples

- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoUserButton', 'offset': 1220, 'source': None, 'size': None}
- {'symbol': '_DoBookMark', 'offset': 2214, 'source': None, 'size': 513}
- {'symbol': '_DrawRibbonMessage', 'offset': 2854, 'source': None, 'size': 156}
- {'symbol': '_DoEvent', 'offset': 3010, 'source': None, 'size': 548}

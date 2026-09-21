# Recovery task _win_YardClosed

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 131 bytes.

```asm
0000 enter 4, 0
0004 mov bx, 0x1886
0007 mov es, word ptr [0xc0ce]
000b mov word ptr [bp - 4], bx
000e mov word ptr [bp - 2], es
0011 cmp word ptr es:[bx], 0
0015 je 0x94a1
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
001c push 0x1900
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0024 add sp, 2
0027 les bx, ptr [bp - 4]
002a push word ptr es:[bx]
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAllAnimObjects
0032 add sp, 2
0035 cmp word ptr [bp + 0xa], 0
0039 je 0x9486
003b push 0xe2
003e push 0x200
0041 push word ptr [bp + 8]
0044 push word ptr [bp + 6]
0047 mov es, word ptr [0xc0d0]
004b push word ptr es:[0x8112]
0050 push word ptr es:[0x8110]
0055 push 0x1900
0058 les bx, ptr [bp - 4]
005b push word ptr es:[bx]
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RenderAnimSet
0063 add sp, 0x10
0066 les bx, ptr [bp - 4]
0069 push word ptr es:[bx]
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimSet
0071 add sp, 2
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
0079 les bx, ptr [bp - 4]
007c mov word ptr es:[bx], 0
0081 leave 
0082 retf 
```

## Known declaration examples

- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_HistUpdate', 'offset': 37250, 'source': None, 'size': 317}
- {'symbol': '_EditMessage', 'offset': 37568, 'source': None, 'size': 351}
- {'symbol': '_UpdateLayQueenModeDisplay', 'offset': 38052, 'source': None, 'size': 108}
- {'symbol': '_win_MapChanged', 'offset': 38160, 'source': 'src/recovered/win_MapChanged.c', 'size': 44}

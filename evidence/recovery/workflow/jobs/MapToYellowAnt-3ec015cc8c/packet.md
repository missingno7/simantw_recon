# Recovery task _MapToYellowAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 105 bytes.

```asm
0000 enter 8, 0
0004 push 0x11
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
000b test ah, 0x80
000e je 0xd46c
0010 push 0x10
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0017 test ah, 0x80
001a je 0xd45c
001c lea ax, [bp - 8]
001f push ss
0020 push ax
0021 push 0x110
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0029 add sp, 6
002c mov ax, word ptr [bp - 4]
002f add ax, word ptr [bp - 8]
0032 cdq 
0033 sub ax, dx
0035 sar ax, 1
0037 les bx, ptr [bp + 6]
003a cmp ax, word ptr es:[bx + 8]
003e jg 0xd44e
0040 xor ax, ax
0042 jmp 0xd451
0044 mov ax, 1
0047 push ax
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _AddSomeAnts
004d add sp, 2
0050 leave 
0051 retf 
0052 push 1
0054 push 0x96
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddFood
005c add sp, 4
005f leave 
0060 retf 
0061 nop 
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
0067 leave 
0068 retf 
```

## Known declaration examples

- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/win_MapChanged.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawMapSpider', 'offset': 53518, 'source': None, 'size': 280}
- {'symbol': '_DrawMapFoot', 'offset': 53798, 'source': None, 'size': 484}
- {'symbol': '_Mini_DrawMapI', 'offset': 54388, 'source': None, 'size': 811}
- {'symbol': '_MapToolsMenu', 'offset': 56350, 'source': None, 'size': 600}

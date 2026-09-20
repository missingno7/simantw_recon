# Recovery task _EraseMapCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 66 bytes.

```asm
0000 push 0x100
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0008 add sp, 2
000b or ax, ax
000d je 0xc74d
000f cmp word ptr [0x1992], 1 ; _mapCursorState
0014 jne 0xc74d
0016 nop 
0017 push cs
0018 call 0x8e50 ; _clip_Push
001b push 0x100
001e nop 
001f push cs
0020 call 0x8e44 ; _clip_SetWin
0023 add sp, 2
0026 push 2
0028 push <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002b push 0x72ae
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
0033 add sp, 6
0036 mov word ptr [0x1992], 0 ; _mapCursorState
003c nop 
003d push cs
003e call 0x8e4e ; _clip_Pop
0041 retf 
```

## Known declaration examples

- `extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);` — src/recovered/EraseMiniMapCursor.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/win_MapChanged.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OpenMapWindow', 'offset': 50758, 'source': 'src/recovered/OpenMapWindow.c', 'size': 12}
- {'symbol': '_DrawMapCursor', 'offset': 50770, 'source': None, 'size': 185}
- {'symbol': '_ToggleMapCursor', 'offset': 51022, 'source': None, 'size': 261}
- {'symbol': '_DrawMapData', 'offset': 52064, 'source': None, 'size': 397}

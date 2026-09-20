# Recovery task _ClearMapScentButtons

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 65 bytes.

```asm
0000 push 0x100
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0008 add sp, 2
000b or ax, ax
000d je 0x95fd
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
0014 push 0x100
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
001c add sp, 2
001f push 2
0021 push 0x100
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupUnselected
0029 add sp, 4
002c push 0x100
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0034 add sp, 2
0037 or ax, ax
0039 je 0x961e
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
0040 retf 
```

## Known declaration examples

- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/win_MapChanged.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_MapChanged', 'offset': 38160, 'source': 'src/recovered/win_MapChanged.c', 'size': 44}
- {'symbol': '_SetMapTitle', 'offset': 38204, 'source': None, 'size': 161}
- {'symbol': '_myDelay', 'offset': 38432, 'source': None, 'size': 116}
- {'symbol': '_MacTickCount', 'offset': 38548, 'source': 'src/recovered/MacTickCount.c', 'size': 18}

# Recovery task _UpdateLayQueenModeDisplay

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 108 bytes.

```asm
0000 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
0005 cmp word ptr [0xbcec], 0
000a je 0x94d4
000c mov es, word ptr [0xc0d2]
0010 cmp word ptr es:[0x836e], 1
0016 sbb bx, bx
0018 neg bx
001a shl bx, 1
001c push word ptr [bx + 0x1502]
0020 push 3
0022 push 0x2300
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetGroupSelectedObj
002a add sp, 6
002d jmp 0x950a
002f nop 
0030 push 0x1900
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0038 add sp, 2
003b or ax, ax
003d je 0x94ee
003f push 0x1900
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0047 add sp, 2
004a mov es, word ptr [0xc0d2]
004e cmp word ptr es:[0x836e], 1
0054 sbb bx, bx
0056 neg bx
0058 shl bx, 1
005a push word ptr [bx + 0x1506]
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
0063 add sp, 2
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
006b retf 
```

## Known declaration examples

- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EditMessage', 'offset': 37568, 'source': None, 'size': 351}
- {'symbol': '_win_YardClosed', 'offset': 37920, 'source': None, 'size': 131}
- {'symbol': '_win_MapChanged', 'offset': 38160, 'source': 'src/recovered/win_MapChanged.c', 'size': 44}
- {'symbol': '_SetMapTitle', 'offset': 38204, 'source': None, 'size': 161}

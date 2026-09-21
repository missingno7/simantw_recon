# Recovery task _SetMapTitle

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 161 bytes.

```asm
0000 push si
0001 mov es, word ptr [0xc0d6]
0005 mov bx, word ptr es:[0x8610]
000a shl bx, 2
000d mov es, word ptr [0xc0d8]
0011 les si, ptr es:[0x9be6]
0016 push word ptr es:[bx + si + 2]
001a push word ptr es:[bx + si]
001d push 0x101
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0025 add sp, 6
0028 mov bx, word ptr [0xce82] ; _YardMode
002c shl bx, 2
002f mov es, word ptr [0xc0d8]
0033 les si, ptr es:[0x9be6]
0038 push word ptr es:[bx + si + 0x26]
003c push word ptr es:[bx + si + 0x24]
0040 push 0x1901
0043 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0048 add sp, 6
004b push 0x100
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0053 add sp, 2
0056 or ax, ax
0058 je 0x95ac
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
005f push 0x100
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0067 add sp, 2
006a push 0x101
006d jmp 0x95ce
006f nop 
0070 push 0x1900
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0078 add sp, 2
007b or ax, ax
007d je 0x95db
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
0084 push 0x1900
0087 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
008c add sp, 2
008f push 0x1901
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawTitle
0097 add sp, 2
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
009f pop si
00a0 retf 
```

## Known declaration examples

- `extern int near YardMode;` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern int near YardMode;` — src/recovered/wf_UpdateYard-32751811c5.c
- `extern void far clip_Pop(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far clip_Push(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawYard-bff77801c5.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateLayQueenModeDisplay', 'offset': 38052, 'source': None, 'size': 108}
- {'symbol': '_win_MapChanged', 'offset': 38160, 'source': 'src/recovered/win_MapChanged.c', 'size': 44}
- {'symbol': '_ClearMapScentButtons', 'offset': 38366, 'source': None, 'size': 65}
- {'symbol': '_myDelay', 'offset': 38432, 'source': 'src/recovered/wf_myDelay-ac936e115a.c', 'size': 116}

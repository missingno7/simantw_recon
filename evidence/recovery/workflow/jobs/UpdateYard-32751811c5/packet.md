# Recovery task _UpdateYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 56 bytes.

```asm
0000 push 0x1900
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0008 add sp, 2
000b or ax, ax
000d je 0xaf13
000f push 1
0011 push word ptr [0xce82] ; _YardMode
0015 nop 
0016 push cs
0017 call 0xb462 ; _Draw_SimYard
001a add sp, 4
001d mov word ptr [0x18b4], 0
0023 push word ptr [0xbcd8]
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
002c mov word ptr [0x18b4], 1
0032 nop 
0033 push cs
0034 call 0xacd8 ; _DrawYardData
0037 retf 
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

- {'symbol': '_DrawYardData', 'offset': 44248, 'source': None, 'size': 460}
- {'symbol': '_DrawYard', 'offset': 44708, 'source': None, 'size': 56}
- {'symbol': '_DrawSimKid', 'offset': 44820, 'source': None, 'size': 507}
- {'symbol': '_DrawDog', 'offset': 45328, 'source': None, 'size': 134}

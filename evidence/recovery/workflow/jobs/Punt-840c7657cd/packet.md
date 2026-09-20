# Recovery task _Punt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 67 bytes.

```asm
0000 enter 0x200, 0
0004 push word ptr [0xcd78] ; _rootWnd
0008 push 0
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 12}}]
000f lea cx, [bp - 0x200]
0013 push ss
0014 push cx
0015 push word ptr [bp + 8]
0018 push word ptr [bp + 6]
001b lea dx, [bp + 0xa]
001e push ss
001f push dx
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 421}}]
0025 push word ptr [0xcd78] ; _rootWnd
0029 lea ax, [bp - 0x200]
002d push ss
002e push ax
002f push ds
0030 push 0xba7f
0033 push 0x10
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
003a push 1
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _exit
0041 leave 
0042 retf 
```

## Known declaration examples

- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Error', 'offset': 6290, 'source': 'src/recovered/Error.c', 'size': 26}
- {'symbol': '_TickCount', 'offset': 6316, 'source': 'src/recovered/TickCount.c', 'size': 17}
- {'symbol': '_CreateMonoSolidBrush', 'offset': 6402, 'source': 'src/recovered/CreateMonoSolidBrush.c', 'size': None}
- {'symbol': '_GInvBox', 'offset': 6502, 'source': None, 'size': 78}

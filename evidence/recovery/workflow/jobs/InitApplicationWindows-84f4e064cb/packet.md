# Recovery task _InitApplicationWindows

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 197 bytes.

```asm
0000 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LoadAllWindows
0005 push <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0008 push 0x14f0
000b push 0
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0012 add sp, 6
0015 push <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0018 push 0xce46
001b push 0x100
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0023 add sp, 6
0026 push <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
0029 push 0x8e28
002c push 0x1500
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0034 add sp, 6
0037 push <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
003a push 0xc4e8
003d push 0x1200
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0045 add sp, 6
0048 push <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
004b push 0xc656
004e push 0x1300
0051 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0056 add sp, 6
0059 push <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
005c push 0xa9e0
005f push 0x1900
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0067 add sp, 6
006a push <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}]
006d push 0x534e
0070 push 0x500
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0078 add sp, 6
007b push <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
007e push 0x61f6
0081 push 0x1e00
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
0089 add sp, 6
008c push <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
008f push 0x64d4
0092 push 0x400
0095 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
009a add sp, 6
009d push <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
00a0 push 0x69c0
00a3 push 0x1d00
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
00ab add sp, 6
00ae push <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
00b1 push 0x5aca
00b4 push 0x1800
00b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetWinDrawHook
00bc add sp, 6
00bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InitMapFunctions
00c4 retf 
```

## Known declaration examples

- `extern void far StopSimulation(void);` — src/recovered/wf_PictStrnDialog-d2f52b0e98.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_SetMap-0b7117ef15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ProcMenuHelp', 'offset': 20390, 'source': 'src/recovered/ProcMenuHelp.c', 'size': 27}
- {'symbol': '_ProcMenu', 'offset': 20418, 'source': None, 'size': None}
- {'symbol': '_InitApplicationStuff', 'offset': 21802, 'source': 'src/initapp.c', 'size': 6}
- {'symbol': '_CalcScore', 'offset': 21808, 'source': None, 'size': 1127}

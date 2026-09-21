# Recovery task _RedrawWindows

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 86 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push <resolved loader operand; see bindings> ; [{'operand_offset': 10, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
000c push 0x1c38
000f push word ptr [0xcc7c] ; _hInst
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 51}}]
0018 mov si, ax
001a push word ptr [0xcd78] ; _rootWnd
001e mov ax, dx
0020 push ax
0021 push si
0022 push 0
0024 push di
0025 mov word ptr [bp - 6], ax
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 55}}]
002d push word ptr [bp - 6]
0030 push si
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 52}}]
0036 cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
003b je 0x1cba
003d cmp di, word ptr [0xcd76] ; _ribbonBarWnd
0041 je 0x1cba
0043 push word ptr [0xcd76] ; _ribbonBarWnd
0047 push 0
0049 push 0
004b push 0
004d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0052 pop si
0053 pop di
0054 leave 
0055 retf 
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

- {'symbol': '_AdjustWndMinMax', 'offset': 6766, 'source': None, 'size': 457}
- {'symbol': 'MYENUMFUNC', 'offset': 7224, 'source': None, 'size': 48}
- {'symbol': '_DoDebugWin', 'offset': 7358, 'source': None, 'size': 179}
- {'symbol': '_NetBIOSPost', 'offset': 7538, 'source': None, 'size': None}

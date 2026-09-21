# Recovery task _DialogWaitInit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 104 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _StillDown
0008 or ax, ax
000a je 0x9c18
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _StillDown
0016 or ax, ax
0018 jne 0x9c0a
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
001f inc word ptr [0x150a]
0023 cmp word ptr [0x150a], 8
0028 jl 0x9c42
002a mov word ptr [0x150a], 0
0030 push word ptr [0xcd78] ; _rootWnd
0034 push ds
0035 push 0x1557
0038 push ds
0039 push 0x1541
003c push 0x1010
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0049 mov bx, word ptr [0x150a]
004d shl bx, 2
0050 mov word ptr [bx - 0x352c], ax
0054 mov word ptr [bx - 0x352a], dx
0058 imul ax, word ptr [bp + 6], 0x12
005c mov bx, word ptr [0x150a]
0060 shl bx, 1
0062 mov word ptr [bx - 0x350c], ax
0066 leave 
0067 retf 
```

## Known declaration examples

- `extern int far StillDown(void);` — src/recovered/myButton.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DialogClearWaitInit', 'offset': 39834, 'source': 'src/recovered/wf_DialogClearWaitInit-0ec1ae45d5.c', 'size': 70}
- {'symbol': '_DialogWait', 'offset': 39904, 'source': 'src/recovered/wf_DialogWait-50782e4ed5.c', 'size': 30}
- {'symbol': '_DialogAbort', 'offset': 40038, 'source': 'src/recovered/wf_DialogAbort-1a41498b6d.c', 'size': 49}
- {'symbol': '_DialogAbortOrCont', 'offset': 40088, 'source': 'src/recovered/wf_DialogAbortOrCont-ea87855190.c', 'size': 59}

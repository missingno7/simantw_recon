# Recovery task _SetDefaultWindows

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 113 bytes.

```asm
0000 nop 
0001 push cs
0002 call 0xbbec ; _OpenCasteWindow
0005 push word ptr [0xbccc]
0009 push 0
000b push 0
000d push 0
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0014 nop 
0015 push cs
0016 call 0xbc7a ; _OpenModeWindow
0019 push word ptr [0xbcca]
001d push 0
001f push 0
0021 push 0
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0028 push word ptr [0xcc76] ; _MapPlane
002c nop 
002d push cs
002e call 0xa5ca ; _SetMapPlane
0031 add sp, 2
0034 cmp word ptr [0xcc76], 0 ; _MapPlane
0039 je 0xd6bc
003b push 0x100
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0043 add sp, 2
0046 or ax, ax
0048 jne 0xd6d0
004a nop 
004b push cs
004c call 0x972a ; _YardToMap
004f jmp 0xd6d0
0051 nop 
0052 push 0x1900
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
005a add sp, 2
005d or ax, ax
005f jne 0xd6d0
0061 nop 
0062 push cs
0063 call 0x9918 ; _MapToYard
0066 nop 
0067 push cs
0068 call 0x953c ; _SetMapTitle
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _OpenEditWindow
0070 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern void far OpenEditWindow(void);` — src/recovered/DoTab.c
- `extern void far YardToMap(void);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Quit', 'offset': 54810, 'source': 'src/recovered/Quit.c', 'size': 13}
- {'symbol': '_MenuQuit', 'offset': 54824, 'source': None, 'size': 66}
- {'symbol': '_NewGame', 'offset': 55004, 'source': None, 'size': 691}

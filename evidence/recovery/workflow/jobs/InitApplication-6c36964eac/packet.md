# Recovery task _InitApplication

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 315 bytes.

```asm
0000 enter 0x138, 0
0004 push si
0005 mov si, word ptr [bp + 6]
0008 mov word ptr [bp - 0x104], 0
000e mov word ptr [bp - 0x102], 0x2930
0014 mov <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
001a xor ax, ax
001c mov word ptr [bp - 0xfe], ax
0020 mov word ptr [bp - 0xfc], ax
0024 mov word ptr [bp - 0xfa], si
0028 push si
0029 push ds
002a push 0x675
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 174}}]
0032 mov word ptr [bp - 0xf8], ax
0036 push 0
0038 push 0
003a push 0x7f00
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
0042 mov word ptr [bp - 0xf6], ax
0046 mov word ptr [bp - 0xf4], 0xd
004c sub ax, ax
004e mov word ptr [bp - 0xf0], ax
0052 mov word ptr [bp - 0xf2], ax
0056 mov word ptr [bp - 0xee], 0x67c
005c mov word ptr [bp - 0xec], ds
0060 mov word ptr [bp - 0x11e], 0x1008
0066 mov word ptr [bp - 0x11c], 0x2930
006c mov <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
0072 mov word ptr [bp - 0x118], ax
0076 mov word ptr [bp - 0x116], ax
007a mov word ptr [bp - 0x114], si
007e push ax
007f push ax
0080 push 0x7f00
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 174}}]
0088 mov word ptr [bp - 0x112], ax
008c push 0
008e push 0
0090 push 0x7f00
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 148, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
0098 mov word ptr [bp - 0x110], ax
009c mov word ptr [bp - 0x10e], 6
00a2 sub ax, ax
00a4 mov word ptr [bp - 0x10a], ax
00a8 mov word ptr [bp - 0x10c], ax
00ac mov word ptr [bp - 0x108], 0x684
00b2 mov word ptr [bp - 0x106], ds
00b6 mov word ptr [bp - 0x138], 0x1008
00bc mov word ptr [bp - 0x136], 0x2930
00c2 mov <resolved loader operand; see bindings> ; [{'operand_offset': 198, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
00c8 mov word ptr [bp - 0x132], ax
00cc mov word ptr [bp - 0x130], ax
00d0 mov word ptr [bp - 0x12e], si
00d4 push ax
00d5 push ax
00d6 push 0x7f00
00d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 174}}]
00de mov word ptr [bp - 0x12c], ax
00e2 push 0
00e4 push 0
00e6 push 0x7f00
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
00ee mov word ptr [bp - 0x12a], ax
00f2 push 1
00f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 87}}]
00f9 mov word ptr [bp - 0x128], ax
00fd sub ax, ax
00ff mov word ptr [bp - 0x124], ax
0103 mov word ptr [bp - 0x126], ax
0107 mov word ptr [bp - 0x122], 0x692
010d mov word ptr [bp - 0x120], ds
0111 lea ax, [bp - 0x138]
0115 push ss
0116 push ax
0117 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 280, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 57}}]
011c lea cx, [bp - 0x11e]
0120 push ss
0121 push cx
0122 mov si, ax
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 57}}]
0129 or si, ax
012b lea ax, [bp - 0x104]
012f push ss
0130 push ax
0131 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 57}}]
0136 or ax, si
0138 pop si
0139 leave 
013a retf 
```

## Known declaration examples

- `extern void far StopSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': 'MAINWNDPROC', 'offset': 10544, 'source': None, 'size': 4953}
- {'symbol': '_InitInstance', 'offset': 15498, 'source': None, 'size': 325}
- {'symbol': '_PatchColorArrays', 'offset': 16140, 'source': 'src/recovered/wf_PatchColorArrays-a1dab56f48.c', 'size': 206}
- {'symbol': 'WINMAIN', 'offset': 16346, 'source': None, 'size': 1546}

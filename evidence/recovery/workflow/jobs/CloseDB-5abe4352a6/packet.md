# Recovery task _CloseDB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 95 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0009 mov es, ax
000b mov si, word ptr [bp + 6]
000e imul bx, si, 0x7c
0011 mov word ptr [bp - 2], bx
0014 mov di, word ptr es:[bx + 0x7480]
0019 cmp word ptr es:[bx + 0x7482], 0
001f je 0x8e37
0021 push di
0022 push 0
0024 push 0
0026 push 0
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 84}}]
002d push di
002e mov ax, word ptr [bp - 2]
0031 add ax, 0x7470
0034 push <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0037 push ax
0038 push 0xe
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
003f push di
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
0045 push si
0046 nop 
0047 push cs
0048 call 0x9c44 ; _CloseIndex
004b add sp, 2
004e mov es, word ptr [0xc68a]
0052 mov bx, word ptr [bp - 2]
0055 mov byte ptr es:[bx + 0x7408], 0
005b pop si
005c pop di
005d leave 
005e retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OpenDB', 'offset': 35824, 'source': None, 'size': 517}
- {'symbol': '_FlushDB', 'offset': 36342, 'source': 'src/recovered/FlushDB.c', 'size': 1}
- {'symbol': '_CopyRootName', 'offset': 36440, 'source': None, 'size': 107}
- {'symbol': '_GetFreeHandle', 'offset': 36548, 'source': None, 'size': 72}

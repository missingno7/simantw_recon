# Recovery task _GetFreeHandle

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 72 bytes.

```asm
0000 cmp word ptr [0xb4e2], 0
0005 jne 0x8ee5
0007 mov word ptr [0xb4e2], 1
000d mov bx, 0x7408
0010 mov <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0013 mov ds, ax
0015 mov byte ptr [bx], 0
0018 add bx, 0x7c
001b cmp bx, 0x75f8
001f jb 0x8ed9
0021 xor cx, cx
0023 mov bx, 0x7408
0026 mov <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0029 mov ds, ax
002b cmp byte ptr [bx], 0
002e je 0x8f02
0030 inc cx
0031 add bx, 0x7c
0034 cmp bx, 0x75f8
0038 jb 0x8eef
003a push ss
003b pop ds
003c jmp 0x8f08
003e push ss
003f pop ds
0040 mov ax, cx
0042 retf 
0043 nop 
0044 mov ax, 0xffff
0047 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CloseDB', 'offset': 36344, 'source': None, 'size': 95}
- {'symbol': '_CopyRootName', 'offset': 36440, 'source': None, 'size': 107}
- {'symbol': '_DosPunt', 'offset': 36620, 'source': None, 'size': 57}
- {'symbol': '_ch_CreateTable', 'offset': 36678, 'source': None, 'size': 265}

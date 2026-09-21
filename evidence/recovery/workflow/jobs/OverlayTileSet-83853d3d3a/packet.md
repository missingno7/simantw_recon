# Recovery task _OverlayTileSet

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 227 bytes.

```asm
0000 enter 4, 0
0004 cmp word ptr [bp + 6], 0
0008 je 0x101
000a jmp 0x1d5
000d mov dx, word ptr [bp + 8]
0010 cmp dx, 0x3e9
0014 jne 0x170
0016 mov es, word ptr [0xbf7e]
001a cmp word ptr es:[0x8df8], 1
0020 je 0x163
0022 mov ax, 1
0025 mov word ptr es:[0x8df8], ax
0029 mov es, word ptr [0xbf80]
002d mov word ptr es:[0x9b6e], ax
0031 mov bx, 0x9de0
0034 mov es, word ptr [0xbf82]
0038 mov word ptr [bp - 4], bx
003b mov word ptr [bp - 2], es
003e cmp word ptr es:[bx], 0
0042 je 0x143
0044 push word ptr es:[bx]
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
004c add sp, 2
004f push 1
0051 push 9
0053 push 9
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
005a add sp, 6
005d les bx, ptr [bp - 4]
0060 mov word ptr es:[bx], ax
0063 push 9
0065 push 9
0067 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_UnhookObject
006c add sp, 4
006f mov es, word ptr [0xbf84]
0073 mov word ptr es:[0x7604], 0x90
007a leave 
007b retf 
007c cmp dx, 0x3e8
0080 jne 0x1d5
0082 mov es, word ptr [0xbf7e]
0086 cmp word ptr es:[0x8df8], 0
008c je 0x1ca
008e xor ax, ax
0090 mov word ptr es:[0x8df8], ax
0094 mov es, word ptr [0xbf80]
0098 mov word ptr es:[0x9b6e], ax
009c mov bx, 0x9de0
009f mov es, word ptr [0xbf82]
00a3 mov word ptr [bp - 4], bx
00a6 mov word ptr [bp - 2], es
00a9 cmp word ptr es:[bx], ax
00ac je 0x1ad
00ae push word ptr es:[bx]
00b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 180, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
00b6 add sp, 2
00b9 push 1
00bb push 9
00bd push 0xa
00bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
00c4 add sp, 6
00c7 les bx, ptr [bp - 4]
00ca mov word ptr es:[bx], ax
00cd push 9
00cf push 0xa
00d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 212, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_UnhookObject
00d6 mov es, word ptr [0xbf84]
00da mov word ptr es:[0x7604], 0x50
00e1 leave 
00e2 retf 
```

## Known declaration examples

- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ZapEuMapAt', 'offset': 0, 'source': None, 'size': 76}
- {'symbol': '_InvalEuMap', 'offset': 76, 'source': None, 'size': 168}
- {'symbol': '_LoadTiles', 'offset': 472, 'source': None, 'size': 2218}
- {'symbol': '_ClearEditDeltaTables', 'offset': 2690, 'source': None, 'size': 247}

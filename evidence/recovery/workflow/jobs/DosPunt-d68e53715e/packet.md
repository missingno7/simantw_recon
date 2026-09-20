# Recovery task _DosPunt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 57 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 cmp word ptr [0xacf8], 0x18 ; _errno
0008 jne 0x8f21
000a push ds
000b push 0xb4e4
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0013 mov sp, bp
0015 mov bx, word ptr [0xacf8] ; _errno
0019 shl bx, 2
001c push word ptr [bx - 0x5092]
0020 push word ptr [bx - 0x5094]
0024 push word ptr [0xacf8] ; _errno
0028 push word ptr [bp + 8]
002b push word ptr [bp + 6]
002e push ds
002f push 0xb56a
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0037 leave 
0038 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CopyRootName', 'offset': 36440, 'source': None, 'size': 107}
- {'symbol': '_GetFreeHandle', 'offset': 36548, 'source': None, 'size': 72}
- {'symbol': '_ch_CreateTable', 'offset': 36678, 'source': None, 'size': 265}
- {'symbol': '_ch_RemoveEntry', 'offset': 36944, 'source': None, 'size': 114}

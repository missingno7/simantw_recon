# Recovery task _db_ReplaceObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 98 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov si, word ptr [bp + 8]
000b push si
000c push di
000d mov es, word ptr [0xc686]
0011 push word ptr es:[0x7ad6]
0016 nop 
0017 push cs
0018 call 0x8888 ; _DBDelete
001b add sp, 6
001e cmp word ptr [0xb1e6], 0 ; _db_numOfHandles
0023 jge 0x8511
0025 push ds
0026 push 0xb375
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
002e add sp, 4
0031 push word ptr [0xb1e8] ; _db_cacheTable
0035 push si
0036 push di
0037 nop 
0038 push cs
0039 call 0x9050 ; _ch_RemoveEntry
003c add sp, 6
003f push word ptr [bp + 0xa]
0042 push si
0043 push di
0044 push word ptr [bp + 0x10]
0047 push word ptr [bp + 0xe]
004a push word ptr [bp + 0xc]
004d mov es, word ptr [0xc686]
0051 push word ptr es:[0x7ad6]
0056 nop 
0057 push cs
0058 call 0x858a ; _DBAdd
005b add sp, 0xe
005e pop si
005f pop di
0060 leave 
0061 retf 
```

## Known declaration examples

- `extern void far DBAdd(int handle, int arg4, int arg5, int arg6, int object, int type, int arg3);` — src/recovered/db_SaveObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far ch_RemoveEntry(int object, int type, int cacheTable);` — src/recovered/db_SaveObject.c
- `extern void far ch_RemoveEntry(int object, int type, int cacheTable);` — src/recovered/db_UnhookObject.c
- `extern int near db_cacheTable;` — src/recovered/db_CloseDataBase.c
- `extern int near db_cacheTable;` — src/recovered/db_PurgeHandle.c
- `extern int near db_cacheTable;` — src/recovered/db_PurgeObject.c
- `extern int near db_numOfHandles;` — src/recovered/db_CloseDataBase.c
- `extern int near db_numOfHandles;` — src/recovered/db_PurgeHandle.c
- `extern int near db_numOfHandles;` — src/recovered/db_PurgeObject.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_db_UnhookObject', 'offset': 33918, 'source': 'src/recovered/db_UnhookObject.c', 'size': 38}
- {'symbol': '_db_CloseDataBase', 'offset': 33956, 'source': 'src/recovered/db_CloseDataBase.c', 'size': 60}
- {'symbol': '_db_SaveObject', 'offset': 34114, 'source': 'src/recovered/db_SaveObject.c', 'size': 72}
- {'symbol': '_DBAdd', 'offset': 34186, 'source': None, 'size': 327}

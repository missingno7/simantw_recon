# Recovery task _db_SetDataBase

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 146 bytes.

```asm
0000 enter 0x20, 0
0004 push si
0005 push word ptr [bp + 8]
0008 push word ptr [bp + 6]
000b push ds
000c push 0xb1f3
000f lea ax, [bp - 0x20]
0012 push ss
0013 push ax
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0019 add sp, 0xc
001c push 0
001e lea ax, [bp - 0x20]
0021 push ss
0022 push ax
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
0028 add sp, 6
002b or ax, ax
002d jne 0x8238
002f mov word ptr [0xb1ea], ax
0032 cmp word ptr [0xb1e8], ax ; _db_cacheTable
0036 jne 0x81f0
0038 push ax
0039 nop 
003a push cs
003b call 0x8f46 ; _ch_CreateTable
003e add sp, 2
0041 mov word ptr [0xb1e8], ax ; _db_cacheTable
0044 push word ptr [bp + 8]
0047 push word ptr [bp + 6]
004a nop 
004b push cs
004c call 0x8bf0 ; _OpenDB
004f add sp, 4
0052 mov es, word ptr [0xc686]
0056 mov bx, word ptr [0xb1e6] ; _db_numOfHandles
005a shl bx, 1
005c mov word ptr es:[bx + 0x7ad6], ax
0061 mov bx, word ptr [0xb1e6] ; _db_numOfHandles
0065 shl bx, 1
0067 mov si, word ptr es:[bx + 0x7ad6]
006c inc word ptr [0xb1e6] ; _db_numOfHandles
0070 or si, si
0072 jge 0x8232
0074 push word ptr [bp + 8]
0077 push word ptr [bp + 6]
007a push ds
007b push 0xb1fa
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0083 add sp, 8
0086 mov ax, si
0088 pop si
0089 leave 
008a retf 
008b nop 
008c mov ax, 0xffff
008f pop si
0090 leave 
0091 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern int far access(char far *path, int mode);` — src/recovered/db_Exists.c
- `extern int near db_cacheTable;` — src/recovered/db_CloseDataBase.c
- `extern int near db_cacheTable;` — src/recovered/db_PurgeHandle.c
- `extern int near db_cacheTable;` — src/recovered/db_PurgeObject.c
- `extern int near db_numOfHandles;` — src/recovered/db_CloseDataBase.c
- `extern int near db_numOfHandles;` — src/recovered/db_PurgeHandle.c
- `extern int near db_numOfHandles;` — src/recovered/db_PurgeObject.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LessonDone', 'offset': 32514, 'source': None, 'size': None}
- {'symbol': '_db_Exists', 'offset': 33142, 'source': 'src/recovered/db_Exists.c', 'size': 54}
- {'symbol': '_db_GetObjectSize', 'offset': 33342, 'source': None, 'size': 84}
- {'symbol': '_db_LoadObject', 'offset': 33426, 'source': None, 'size': 188}

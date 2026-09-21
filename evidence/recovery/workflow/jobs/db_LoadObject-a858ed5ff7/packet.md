# Recovery task _db_LoadObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 188 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 cmp word ptr [0xb1e6], 0 ; _db_numOfHandles
000b jg 0x82ab
000d push ds
000e push 0xb212
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0016 add sp, 4
0019 push word ptr [0xb1e8] ; _db_cacheTable
001d push word ptr [bp + 8]
0020 push word ptr [bp + 6]
0023 nop 
0024 push cs
0025 call 0x91e6 ; _ch_LookUpId
0028 add sp, 6
002b mov si, ax
002d or si, si
002f jne 0x833c
0031 xor di, di
0033 cmp word ptr [0xb1e6], si ; _db_numOfHandles
0037 jle 0x82f9
0039 mov si, 0x7ad6
003c lea ax, [bp - 4]
003f push ss
0040 push ax
0041 push word ptr [bp + 8]
0044 push word ptr [bp + 6]
0047 mov es, word ptr [0xc686]
004b push word ptr es:[si]
004e nop 
004f push cs
0050 call 0x86d2 ; _DBRecall
0053 add sp, 0xa
0056 mov word ptr [bp - 2], ax
0059 or ax, ax
005b jne 0x8312
005d add si, 2
0060 inc di
0061 cmp di, word ptr [0xb1e6] ; _db_numOfHandles
0065 jl 0x82ce
0067 push word ptr [bp + 8]
006a push word ptr [bp + 6]
006d push ds
006e push 0xb258
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0076 add sp, 8
0079 xor ax, ax
007b pop si
007c pop di
007d leave 
007e retf 
007f nop 
0080 push ax
0081 push word ptr [0xb1e8] ; _db_cacheTable
0085 push word ptr [bp + 8]
0088 push word ptr [bp + 6]
008b nop 
008c push cs
008d call 0x9470 ; _ch_AddEntry
0090 add sp, 8
0093 or ax, ax
0095 jne 0x8335
0097 push ds
0098 push 0xb234
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
00a0 add sp, 4
00a3 mov ax, word ptr [bp - 2]
00a6 pop si
00a7 pop di
00a8 leave 
00a9 retf 
00aa push word ptr [bp + 0xa]
00ad push si
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_SetType
00b3 add sp, 4
00b6 mov ax, si
00b8 pop si
00b9 pop di
00ba leave 
00bb retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern int far ch_LookUpId(int object, int type, int cacheTable);` — src/recovered/db_PurgeObject.c
- `extern int far ch_LookUpId(int object, int type, int cacheTable);` — src/recovered/db_ReleaseObject.c
- `extern int near db_cacheTable;` — src/recovered/db_CloseDataBase.c
- `extern int near db_cacheTable;` — src/recovered/db_PurgeHandle.c
- `extern int near db_cacheTable;` — src/recovered/db_PurgeObject.c
- `extern int near db_numOfHandles;` — src/recovered/db_CloseDataBase.c
- `extern int near db_numOfHandles;` — src/recovered/db_PurgeHandle.c
- `extern int near db_numOfHandles;` — src/recovered/db_PurgeObject.c
- `extern void far mem_SetType(unsigned int handle, unsigned int type);` — src/recovered/db_ReleaseHandle.c
- `extern void far mem_SetType(int handle, int type);` — src/recovered/db_ReleaseObject.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_db_SetDataBase', 'offset': 33196, 'source': None, 'size': 146}
- {'symbol': '_db_GetObjectSize', 'offset': 33342, 'source': None, 'size': 84}
- {'symbol': '_db_PurgeObject', 'offset': 33614, 'source': 'src/recovered/db_PurgeObject.c', 'size': 99}
- {'symbol': '_db_PurgeHandle', 'offset': 33714, 'source': 'src/recovered/db_PurgeHandle.c', 'size': 100}

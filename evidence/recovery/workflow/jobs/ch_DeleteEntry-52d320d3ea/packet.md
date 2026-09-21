# Recovery task _ch_DeleteEntry

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 114 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 push word ptr [bp + 0xa]
0009 push word ptr [bp + 8]
000c push word ptr [bp + 6]
000f nop 
0010 push cs
0011 call 0x91e6 ; _ch_LookUpId
0014 add sp, 6
0017 or ax, ax
0019 je 0x979e
001b push word ptr [bp + 0xa]
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0023 add sp, 2
0026 mov si, ax
0028 mov es, dx
002a mov bx, word ptr [0xb594]
002e shl bx, 2
0031 mov word ptr es:[bx + si + 4], 0xffff
0037 mov ax, dx
0039 mov bx, word ptr es:[si]
003c inc bx
003d shl bx, 2
0040 sub cx, cx
0042 add bx, si
0044 adc cx, ax
0046 mov es, cx
0048 mov di, word ptr [0xb594]
004c shl di, 1
004e mov word ptr es:[bx + di], 0
0053 mov es, ax
0055 dec word ptr es:[si + 2]
0059 push word ptr [bp + 0xa]
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0061 add sp, 2
0064 mov ax, 1
0067 pop si
0068 pop di
0069 leave 
006a retf 
006b nop 
006c xor ax, ax
006e pop si
006f pop di
0070 leave 
0071 retf 
```

## Known declaration examples

- `extern int far ch_LookUpId(int object, int type, int cacheTable);` — src/recovered/db_PurgeObject.c
- `extern int far ch_LookUpId(int object, int type, int cacheTable);` — src/recovered/db_ReleaseObject.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ch_LookUpId', 'offset': 37350, 'source': None, 'size': 649}
- {'symbol': '_ch_AddEntry', 'offset': 38000, 'source': None, 'size': 706}
- {'symbol': '_ch_CleanupTable', 'offset': 38820, 'source': None, 'size': 226}
- {'symbol': '_ch_DumpOldest', 'offset': 39046, 'source': None, 'size': 320}

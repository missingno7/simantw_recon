# Recovery task _ch_CleanupTable

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 226 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov di, ax
0017 mov word ptr [bp - 8], es
001a mov ax, word ptr es:[bx]
001d mov word ptr [bp - 6], ax
0020 inc ax
0021 shl ax, 2
0024 sub dx, dx
0026 mov cx, es
0028 add ax, bx
002a adc dx, cx
002c mov si, ax
002e mov word ptr [bp - 0xc], dx
0031 lea ax, [bx + 4]
0034 mov word ptr [bp - 2], es
0037 mov word ptr [bp - 0xa], di
003a mov di, ax
003c jmp 0x9858
003e nop 
003f nop 
0040 mov es, word ptr [bp - 2]
0043 cmp word ptr es:[di], -1
0047 je 0x9852
0049 mov es, word ptr [bp - 0xc]
004c cmp word ptr es:[si], 0
0050 je 0x9852
0052 push word ptr es:[si]
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Freed
005a add sp, 2
005d or ax, ax
005f je 0x9852
0061 mov es, word ptr [bp - 0xc]
0064 push word ptr es:[si]
0067 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_LockLevel
006c add sp, 2
006f or ax, ax
0071 jne 0x9852
0073 mov es, word ptr [bp - 2]
0076 push word ptr es:[di + 2]
007a push word ptr es:[di]
007d push ds
007e push 0xb618
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0086 add sp, 8
0089 mov es, word ptr [bp - 0xc]
008c push word ptr es:[si]
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0094 add sp, 2
0097 mov es, word ptr [bp - 0xc]
009a mov word ptr es:[si], 0
009f mov es, word ptr [bp - 2]
00a2 mov word ptr es:[di], 0xffff
00a7 les bx, ptr [bp - 0xa]
00aa dec word ptr es:[bx + 2]
00ae add di, 4
00b1 add si, 2
00b4 mov ax, word ptr [bp - 6]
00b7 dec word ptr [bp - 6]
00ba or ax, ax
00bc jne 0x97e4
00be push ds
00bf push 0xb623
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
00c7 add sp, 4
00ca les bx, ptr [bp - 0xa]
00cd mov si, word ptr es:[bx + 2]
00d1 push word ptr [bp + 6]
00d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 215, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00d9 add sp, 2
00dc mov ax, si
00de pop si
00df pop di
00e0 leave 
00e1 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ch_AddEntry', 'offset': 38000, 'source': None, 'size': 706}
- {'symbol': '_ch_DeleteEntry', 'offset': 38706, 'source': None, 'size': 114}
- {'symbol': '_ch_DumpOldest', 'offset': 39046, 'source': None, 'size': 320}
- {'symbol': '_ch_GetPrime', 'offset': 39366, 'source': None, 'size': 159}

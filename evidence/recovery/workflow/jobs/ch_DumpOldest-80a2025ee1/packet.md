# Recovery task _ch_DumpOldest

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 320 bytes.

```asm
0000 enter 0x26, 0
0004 push di
0005 push si
0006 sub ax, ax
0008 mov word ptr [bp - 0xa], ax
000b mov word ptr [bp - 0xc], ax
000e push word ptr [bp + 6]
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0016 add sp, 2
0019 mov es, dx
001b mov bx, ax
001d mov di, ax
001f mov ax, word ptr es:[bx]
0022 mov word ptr [bp - 0xe], ax
0025 inc ax
0026 shl ax, 2
0029 sub dx, dx
002b mov cx, es
002d add ax, bx
002f adc dx, cx
0031 mov si, ax
0033 mov word ptr [bp - 0x1c], dx
0036 lea ax, [bx + 4]
0039 mov word ptr [bp - 6], es
003c add bx, 2
003f mov word ptr [bp - 0x22], bx
0042 mov word ptr [bp - 0x20], es
0045 cmp word ptr es:[bx], 0
0049 jne 0x98d4
004b jmp 0x99b2
004e mov di, ax
0050 jmp 0x994e
0052 nop 
0053 nop 
0054 mov es, word ptr [bp - 6]
0057 cmp word ptr es:[di], -1
005b je 0x9948
005d mov es, word ptr [bp - 0x1c]
0060 push word ptr es:[si]
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 102, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Age
0068 add sp, 2
006b sub dx, dx
006d mov word ptr [bp - 4], ax
0070 mov word ptr [bp - 2], dx
0073 cmp dx, word ptr [bp - 0xa]
0076 jb 0x9948
0078 ja 0x9905
007a cmp ax, word ptr [bp - 0xc]
007d jbe 0x9948
007f mov es, word ptr [bp - 0x1c]
0082 push word ptr es:[si]
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Type
008a add sp, 2
008d cmp ax, 3
0090 jne 0x9948
0092 mov es, word ptr [bp - 0x1c]
0095 push word ptr es:[si]
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_LockLevel
009d add sp, 2
00a0 or ax, ax
00a2 jne 0x9948
00a4 mov ax, word ptr [bp - 4]
00a7 mov dx, word ptr [bp - 2]
00aa mov word ptr [bp - 0xc], ax
00ad mov word ptr [bp - 0xa], dx
00b0 mov ax, word ptr [bp - 0x1c]
00b3 mov word ptr [bp - 0x1a], si
00b6 mov word ptr [bp - 0x18], ax
00b9 mov ax, word ptr [bp - 6]
00bc mov word ptr [bp - 0x12], di
00bf mov word ptr [bp - 0x10], ax
00c2 add si, 2
00c5 add di, 4
00c8 mov ax, word ptr [bp - 0xe]
00cb dec word ptr [bp - 0xe]
00ce or ax, ax
00d0 jne 0x98da
00d2 mov ax, word ptr [bp - 0xa]
00d5 or ax, word ptr [bp - 0xc]
00d8 jne 0x996c
00da push ds
00db push 0xb625
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
00e3 add sp, 4
00e6 mov di, word ptr [bp - 0x1a]
00e9 mov si, word ptr [bp - 0x12]
00ec mov es, word ptr [bp - 0x18]
00ef push word ptr es:[di]
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
00f7 add sp, 2
00fa mov es, word ptr [bp - 0x10]
00fd push word ptr es:[si + 2]
0101 push word ptr es:[si]
0104 push ds
0105 push 0xb63e
0108 mov word ptr [bp - 0x26], si
010b mov word ptr [bp - 0x24], es
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0113 add sp, 8
0116 les bx, ptr [bp - 0x26]
0119 mov word ptr es:[bx], 0xffff
011e mov es, word ptr [bp - 0x18]
0121 mov word ptr es:[di], 0
0126 les bx, ptr [bp - 0x22]
0129 dec word ptr es:[bx]
012c mov si, word ptr es:[bx]
012f push word ptr [bp + 6]
0132 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 309, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0137 add sp, 2
013a mov ax, si
013c pop si
013d pop di
013e leave 
013f retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
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

- {'symbol': '_ch_DeleteEntry', 'offset': 38706, 'source': None, 'size': 114}
- {'symbol': '_ch_CleanupTable', 'offset': 38820, 'source': None, 'size': 226}
- {'symbol': '_ch_GetPrime', 'offset': 39366, 'source': None, 'size': 159}
- {'symbol': '_ch_SetCacheHooks', 'offset': 39526, 'source': 'src/recovered/ch_SetCacheHooks.c', 'size': 31}

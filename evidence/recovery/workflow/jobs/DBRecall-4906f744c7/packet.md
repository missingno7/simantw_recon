# Recovery task _DBRecall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 438 bytes.

```asm
0000 enter 0x34, 0
0004 push di
0005 push si
0006 les bx, ptr [bp + 0xc]
0009 mov word ptr es:[bx], 0
000e push word ptr [bp + 0xa]
0011 push word ptr [bp + 8]
0014 push word ptr [bp + 6]
0017 nop 
0018 push cs
0019 call 0x9d24 ; _FindIndex
001c add sp, 6
001f mov word ptr [bp - 0xa], ax
0022 mov word ptr [bp - 8], dx
0025 or dx, ax
0027 jne 0x8702
0029 xor ax, ax
002b pop si
002c pop di
002d leave 
002e retf 
002f nop 
0030 mov es, word ptr [0xc688]
0034 imul bx, word ptr [bp + 6], 0x7c
0038 mov ax, word ptr es:[bx + 0x7480]
003d mov word ptr [bp - 2], ax
0040 push ax
0041 les bx, ptr [bp - 0xa]
0044 mov ax, word ptr es:[bx]
0047 mov dx, word ptr es:[bx + 2]
004b add ax, 0xe
004e adc dx, 0
0051 push dx
0052 push ax
0053 push 0
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 84}}]
005a push word ptr [bp - 2]
005d lea ax, [bp - 0x14]
0060 push ss
0061 push ax
0062 push 0xa
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
0069 mov si, word ptr [bp - 0xe]
006c push word ptr [bp + 8]
006f mov ax, word ptr [bp + 0xa]
0072 add ax, 0x61
0075 push ax
0076 push ds
0077 push 0xb3a2
007a lea ax, [bp - 0x34]
007d push ss
007e push ax
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0084 add sp, 0xc
0087 lea ax, [bp - 0x34]
008a push ss
008b push ax
008c push 0
008e mov ax, si
0090 sub dx, dx
0092 add ax, 3
0095 adc dx, dx
0097 push dx
0098 push ax
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
009e add sp, 0xa
00a1 mov di, ax
00a3 or di, di
00a5 jne 0x8785
00a7 push ds
00a8 push 0xb3af
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
00b0 add sp, 4
00b3 push word ptr [bp - 2]
00b6 push di
00b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00bc add sp, 2
00bf mov word ptr [bp - 6], ax
00c2 mov word ptr [bp - 4], dx
00c5 push dx
00c6 push ax
00c7 push si
00c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
00cd les bx, ptr [bp - 0xa]
00d0 test byte ptr es:[bx + 7], 1
00d5 jne 0x87ac
00d7 jmp 0x8873
00da test byte ptr es:[bx + 7], 4
00df je 0x87da
00e1 push si
00e2 push word ptr [bp - 4]
00e5 mov ax, word ptr [bp - 6]
00e8 push ax
00e9 mov dx, word ptr [bp - 4]
00ec add ax, 2
00ef push dx
00f0 push ax
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
00f6 add sp, 0xa
00f9 les bx, ptr [bp - 6]
00fc mov word ptr es:[bx], 0xffff
0101 add si, 2
0104 jmp 0x8873
0107 nop 
0108 les bx, ptr [bp - 6]
010b mov ax, word ptr es:[bx]
010e mov word ptr [bp - 2], ax
0111 push word ptr [bp + 8]
0114 mov ax, word ptr [bp + 0xa]
0117 add ax, 0x61
011a push ax
011b push ds
011c push 0xb3d7
011f lea ax, [bp - 0x34]
0122 push ss
0123 push ax
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0129 add sp, 0xc
012c lea ax, [bp - 0x34]
012f push ss
0130 push ax
0131 push 0
0133 push 0
0135 push word ptr [bp - 2]
0138 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 315, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
013d add sp, 0xa
0140 mov word ptr [bp - 8], ax
0143 lea ax, [si - 2]
0146 push ax
0147 mov ax, word ptr [bp - 6]
014a mov dx, word ptr [bp - 4]
014d add ax, 2
0150 push dx
0151 push ax
0152 nop 
0153 push cs
0154 call 0xa62a ; _UnpackInit
0157 add sp, 6
015a push word ptr [bp - 2]
015d push word ptr [bp - 8]
0160 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 355, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0165 add sp, 2
0168 push dx
0169 push ax
016a nop 
016b push cs
016c call 0xa668 ; _Unpack
016f add sp, 6
0172 cmp ax, word ptr [bp - 2]
0175 je 0x885b
0177 push word ptr [bp + 0xa]
017a push word ptr [bp + 8]
017d push ds
017e push 0xb3e3
0181 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 388, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0186 add sp, 8
0189 push di
018a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 397, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
018f add sp, 2
0192 push di
0193 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 406, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0198 add sp, 2
019b mov di, word ptr [bp - 8]
019e mov si, word ptr [bp - 2]
01a1 push di
01a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01a7 add sp, 2
01aa les bx, ptr [bp + 0xc]
01ad mov word ptr es:[bx], si
01b0 mov ax, di
01b2 pop si
01b3 pop di
01b4 leave 
01b5 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_InitMapFunctions-70fb457ea5.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_db_SaveObject', 'offset': 34114, 'source': 'src/recovered/db_SaveObject.c', 'size': 72}
- {'symbol': '_DBAdd', 'offset': 34186, 'source': None, 'size': 327}
- {'symbol': '_DBDelete', 'offset': 34952, 'source': None, 'size': 153}
- {'symbol': '_DBPack', 'offset': 35106, 'source': None, 'size': 547}

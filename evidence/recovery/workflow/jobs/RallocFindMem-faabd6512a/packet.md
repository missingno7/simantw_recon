# Recovery task _RallocFindMem

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 329 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 cmp word ptr [0x87e], 0
0008 jne 0x56ca
000a push -1
000c push -1
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0013 push 2
0015 push 0
0017 push 0xc350
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
001f mov word ptr [0x87e], ax
0022 cmp word ptr [0x87c], 0
0027 jne 0x5704
0029 push 0
002b push 0
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0032 cmp dx, 1
0035 jb 0x5704
0037 ja 0x56e6
0039 cmp ax, 0x86a0
003c jbe 0x5704
003e push -1
0040 push -1
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0047 push 2
0049 push 1
004b push 0x86a0
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
0053 mov word ptr [0x87c], ax
0056 mov word ptr [0x880], 0
005c cmp word ptr [bp + 6], -1
0060 jne 0x5713
0062 cmp word ptr [bp + 8], -1
0066 jne 0x5713
0068 jmp 0x57ef
006b push 0
006d push 0
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0074 cmp dx, word ptr [bp + 8]
0077 jb 0x5741
0079 ja 0x5728
007b cmp ax, word ptr [bp + 6]
007e jb 0x5741
0080 push 0
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 169}}]
0087 cmp dx, word ptr [bp + 8]
008a jbe 0x5737
008c jmp 0x57ef
008f jb 0x5741
0091 cmp ax, word ptr [bp + 6]
0094 jb 0x5741
0096 jmp 0x57ef
0099 cmp word ptr [0x87c], 0
009e je 0x5757
00a0 push word ptr [0x87c]
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
00a9 mov word ptr [0x87c], 0
00af push -1
00b1 push -1
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 180, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
00b8 cmp dx, word ptr [bp + 8]
00bb jb 0x5790
00bd ja 0x576c
00bf cmp ax, word ptr [bp + 6]
00c2 jb 0x5790
00c4 mov dx, word ptr [0x880]
00c8 or dx, dx
00ca jne 0x5790
00cc push 1
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetPause
00d3 mov sp, bp
00d5 push ds
00d6 push 0x8bc
00d9 nop 
00da push cs
00db call 0x1878 ; _PopMsg
00de mov sp, bp
00e0 mov word ptr [0x880], 1
00e6 jmp 0x57e6
00e8 push word ptr [bp + 8]
00eb push word ptr [bp + 6]
00ee push 0
00f0 push 0
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
00f7 push dx
00f8 push ax
00f9 push ds
00fa push 0x882
00fd nop 
00fe push cs
00ff call 0x62bc ; _WinPrintf
0102 add sp, 0xc
0105 cmp word ptr [0x87e], 0
010a je 0x57bd
010c push word ptr [0x87e]
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0115 push -1
0117 push -1
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
011e push ds
011f push 0x897
0122 nop 
0123 push cs
0124 call 0x1878 ; _PopMsg
0127 mov sp, bp
0129 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 300, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _CleanUp
012e push 0
0130 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 6}}]
0135 push 0
0137 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _exit
013c mov sp, bp
013e push -1
0140 push -1
0142 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 323, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0147 leave 
0148 retf 
```

## Known declaration examples

- `extern void far SetPause(int pause);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far exit(int status);` — src/recovered/wf_Punt-840c7657cd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ralloc_CompressMemory', 'offset': 22148, 'source': 'src/recovered/ralloc_CompressMemory.c', 'size': 10}
- {'symbol': '_RallocInfo', 'offset': 22158, 'source': 'src/recovered/RallocInfo.c', 'size': 25}
- {'symbol': '_Ralloc', 'offset': 22514, 'source': 'src/recovered/wf_Ralloc-b43a5ad4e7.c', 'size': 160}
- {'symbol': '_RallocRealloc', 'offset': 22674, 'source': 'src/recovered/wf_RallocRealloc-d8db281862.c', 'size': 163}

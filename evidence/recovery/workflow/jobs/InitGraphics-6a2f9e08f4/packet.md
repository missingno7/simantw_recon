# Recovery task _InitGraphics

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 275 bytes.

```asm
0000 enter 0x248, 0
0004 push si
0005 mov word ptr [bp - 0x1e4], 0xb92b
000b mov word ptr [bp - 0x1e2], ds
000f mov word ptr [bp - 0x1e0], 0xb931
0015 mov word ptr [bp - 0x1de], ds
0019 mov word ptr [bp - 0x1dc], 0xb936
001f mov word ptr [bp - 0x1da], ds
0023 mov word ptr [bp - 0x1d8], 0xb93c
0029 mov word ptr [bp - 0x1d6], ds
002d mov word ptr [bp - 0x1d4], 0xb941
0033 mov word ptr [bp - 0x1d2], ds
0037 mov word ptr [bp - 0x1d0], 0xb947
003d mov word ptr [bp - 0x1ce], ds
0041 mov word ptr [bp - 0x1cc], 0xb94c
0047 mov word ptr [bp - 0x1ca], ds
004b mov word ptr [bp - 0x1c8], 0xb951
0051 mov word ptr [bp - 0x1c6], ds
0055 mov word ptr [bp - 0x1c4], 0xb956
005b mov word ptr [bp - 0x1c2], ds
005f mov word ptr [bp - 0x1c0], 0xb95c
0065 mov word ptr [bp - 0x1be], ds
0069 mov word ptr [bp - 0x1bc], 0xb961
006f mov word ptr [bp - 0x1ba], ds
0073 cmp byte ptr [0xcc7e], 0xff ; _displayType
0078 jne 0x1d3
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 286}}]
007f mov word ptr [bp - 4], ax
0082 push ax
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 66}}]
0088 mov word ptr [bp - 2], ax
008b push ax
008c push 0xc
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
0093 dec ax
0094 jne 0x1c0
0096 push word ptr [bp - 2]
0099 push 0xe
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
00a0 dec ax
00a1 jne 0x1c0
00a3 push word ptr [bp - 4]
00a6 push word ptr [bp - 2]
00a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
00ae mov si, 9
00b1 jmp 0x1ce
00b3 nop 
00b4 push word ptr [bp - 4]
00b7 push word ptr [bp - 2]
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
00bf mov si, 0xa
00c2 mov ax, si
00c4 mov byte ptr [0xcc7e], al ; _displayType
00c7 push word ptr [bp + 8]
00ca push word ptr [bp + 6]
00cd mov al, byte ptr [0xcc7e] ; _displayType
00d0 cwde 
00d1 mov si, ax
00d3 shl si, 2
00d6 push word ptr [bp + si - 0x1e2]
00da push word ptr [bp + si - 0x1e4]
00de push ds
00df push 0xb967
00e2 lea ax, [bp - 0x248]
00e6 push ss
00e7 push ax
00e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 235, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
00ed add sp, 0x10
00f0 lea ax, [bp - 0x248]
00f4 push ss
00f5 push ax
00f6 push ds
00f7 push 0xb96c
00fa nop 
00fb push cs
00fc call 0x62bc ; _WinPrintf
00ff add sp, 8
0102 lea ax, [bp - 0x248]
0106 push ss
0107 push ax
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_SetDataBase
010d add sp, 4
0110 pop si
0111 leave 
0112 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetHelpCursor', 'offset': 0, 'source': None, 'size': 201}
- {'symbol': '_DetectDisplay', 'offset': 202, 'source': 'src/recovered/DetectDisplay.c', 'size': 65}
- {'symbol': '_IBMInitStuff', 'offset': 544, 'source': None, 'size': 1507}
- {'symbol': '_ReadWord', 'offset': 2052, 'source': 'src/recovered/wf_ReadWord-e51efa9f2b.c', 'size': 109}

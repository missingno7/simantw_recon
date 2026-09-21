# Recovery task _win_SetObjFormatStr

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 297 bytes.

```asm
0000 enter 0x74, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0xe3a8 ; _win_LockWin
000e add sp, 2
0011 mov bx, word ptr [bp + 6]
0014 mov word ptr [bp - 2], bx
0017 sar bx, 8
001a shl bx, 2
001d mov ax, word ptr [bx - 0x3166]
0021 mov dx, word ptr [bx - 0x3164]
0025 mov word ptr [bp - 0x10], ax
0028 mov word ptr [bp - 0xe], dx
002b mov es, dx
002d mov bx, ax
002f mov al, byte ptr [bp + 6]
0032 sub ah, ah
0034 cmp word ptr es:[bx + 0xc], ax
0038 jg 0xd33a
003a push ds
003b push 0xbd12
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0043 add sp, 4
0046 lea ax, [bp + 8]
0049 push ss
004a push ax
004b mov si, word ptr [bp - 2]
004e and si, 0xff
0052 shl si, 2
0055 les bx, ptr [bp - 0x10]
0058 mov ax, word ptr es:[bx + si + 0x2c]
005c mov dx, word ptr es:[bx + si + 0x2e]
0060 mov di, ax
0062 mov word ptr [bp - 0xa], dx
0065 add ax, 0x2e
0068 push dx
0069 push ax
006a lea ax, [bp - 0x74]
006d push ss
006e push ax
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _vsprintf
0074 add sp, 0xc
0077 lea ax, [bp - 0x74]
007a push ss
007b push ax
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
0081 inc ax
0082 mov word ptr [bp - 8], ax
0085 mov es, word ptr [bp - 0xa]
0088 mov ax, word ptr es:[di + 0x2a]
008c mov dx, word ptr es:[di + 0x2c]
0090 mov si, ax
0092 mov word ptr [bp - 4], dx
0095 or dx, ax
0097 je 0xd3d2
0099 mov word ptr [bp - 6], si
009c mov es, word ptr [bp - 4]
009f push word ptr es:[si + 2]
00a3 push word ptr es:[si]
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
00ab inc ax
00ac cmp ax, word ptr [bp - 8]
00af jge 0xd3fa
00b1 push 1
00b3 mov ax, word ptr [bp - 8]
00b6 add ax, 4
00b9 cdq 
00ba push dx
00bb push ax
00bc push word ptr [bp - 4]
00bf push si
00c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _RallocRealloc
00c5 add sp, 0xa
00c8 mov si, ax
00ca mov word ptr [bp - 4], dx
00cd mov es, word ptr [bp - 0xa]
00d0 mov word ptr es:[di + 0x2a], ax
00d4 mov word ptr es:[di + 0x2c], dx
00d8 mov word ptr [bp - 6], si
00db jmp 0xd3fa
00dd nop 
00de push ds
00df push 0xbdca
00e2 push 1
00e4 mov ax, word ptr [bp - 8]
00e7 add ax, 8
00ea cdq 
00eb push dx
00ec push ax
00ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 240, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Ralloc
00f2 add sp, 0xa
00f5 mov word ptr [bp - 6], ax
00f8 mov word ptr [bp - 4], dx
00fb mov es, word ptr [bp - 0xa]
00fe mov word ptr es:[di + 0x2a], ax
0102 mov word ptr es:[di + 0x2c], dx
0106 les bx, ptr [bp - 6]
0109 push word ptr es:[bx + 2]
010d push word ptr es:[bx]
0110 lea ax, [bp - 0x74]
0113 push ss
0114 push ax
0115 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 278, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
011a push word ptr [bp + 6]
011d nop 
011e push cs
011f call 0xe3a4 ; _win_UnlockWin
0122 add sp, 2
0125 pop si
0126 pop di
0127 leave 
0128 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern int far vsprintf(char far *buffer, char far *format, char far *args);` — src/recovered/wf_win_PrintfAtObj-9e4b836702.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateAllWindows', 'offset': 53526, 'source': 'src/recovered/wf_UpdateAllWindows-97a1ff92dc.c', 'size': 58}
- {'symbol': '_win_GetEvent', 'offset': 53584, 'source': None, 'size': 420}
- {'symbol': '_win_ToTop', 'offset': 54302, 'source': 'src/recovered/win_ToTop.c', 'size': 22}
- {'symbol': '_win_Swap', 'offset': 54324, 'source': None, 'size': 359}

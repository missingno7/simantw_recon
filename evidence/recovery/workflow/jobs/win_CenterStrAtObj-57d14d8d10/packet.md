# Recovery task _win_CenterStrAtObj

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 160 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0xb4b2 ; _win_SetColorFromObjNum
000e add sp, 2
0011 push word ptr [bp + 6]
0014 nop 
0015 push cs
0016 call 0xe3a8 ; _win_LockWin
0019 add sp, 2
001c mov bl, byte ptr [bp + 6]
001f sub bh, bh
0021 shl bx, 2
0024 mov si, word ptr [bp + 6]
0027 sar si, 8
002a shl si, 2
002d les si, ptr [si - 0x3166]
0031 mov ax, word ptr es:[bx + si + 0x2c]
0035 mov dx, word ptr es:[bx + si + 0x2e]
0039 push ds
003a lea di, [bp - 8]
003d mov si, ax
003f push ss
0040 pop es
0041 mov ds, dx
0043 movsw word ptr es:[di], word ptr [si]
0044 movsw word ptr es:[di], word ptr [si]
0045 movsw word ptr es:[di], word ptr [si]
0046 movsw word ptr es:[di], word ptr [si]
0047 pop ds
0048 cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
004d je 0xd68f
004f inc word ptr [bp - 4]
0052 inc word ptr [bp - 2]
0055 push word ptr [bp + 6]
0058 nop 
0059 push cs
005a call 0xe3a4 ; _win_UnlockWin
005d add sp, 2
0060 push word ptr [0xcf52] ; _clipDC
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 30}}]
0069 push word ptr [0xcf52] ; _clipDC
006d push word ptr [bp - 8]
0070 push word ptr [bp - 6]
0073 push word ptr [bp - 4]
0076 push word ptr [bp - 2]
0079 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 122, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 22}}]
007e push word ptr [bp + 0xa]
0081 push word ptr [bp + 8]
0084 lea ax, [bp - 8]
0087 push ss
0088 push ax
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_CenterStrInRectClear
008e add sp, 8
0091 push word ptr [0xcf52] ; _clipDC
0095 push -1
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 39}}]
009c pop si
009d pop di
009e leave 
009f retf 
```

## Known declaration examples

- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_InvalidateObject-69cbeedc5b.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetWinDrawHook', 'offset': 54684, 'source': 'src/recovered/win_SetWinDrawHook.c', 'size': 34}
- {'symbol': '_win_SetObjBitmap', 'offset': 54718, 'source': None, 'size': 123}
- {'symbol': '_win_PrintfAtObj', 'offset': 55002, 'source': None, 'size': 183}
- {'symbol': '_win_ClearObjToEOL', 'offset': 55186, 'source': None, 'size': 290}

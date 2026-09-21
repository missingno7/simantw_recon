# Recovery task _win_PrintfAtObj

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 183 bytes.

```asm
0000 enter 0x6c, 0
0004 push di
0005 push si
0006 lea ax, [bp + 0xc]
0009 push ss
000a push ax
000b push word ptr [bp + 0xa]
000e push word ptr [bp + 8]
0011 lea ax, [bp - 0x6c]
0014 push ss
0015 push ax
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _vsprintf
001b add sp, 0xc
001e push word ptr [bp + 6]
0021 nop 
0022 push cs
0023 call 0xb4b2 ; _win_SetColorFromObjNum
0026 add sp, 2
0029 push word ptr [bp + 6]
002c nop 
002d push cs
002e call 0xe3a8 ; _win_LockWin
0031 add sp, 2
0034 mov bl, byte ptr [bp + 6]
0037 sub bh, bh
0039 shl bx, 2
003c mov si, word ptr [bp + 6]
003f sar si, 8
0042 shl si, 2
0045 les si, ptr [si - 0x3166]
0049 mov ax, word ptr es:[bx + si + 0x2c]
004d mov dx, word ptr es:[bx + si + 0x2e]
0051 push ds
0052 lea di, [bp - 8]
0055 mov si, ax
0057 push ss
0058 pop es
0059 mov ds, dx
005b movsw word ptr es:[di], word ptr [si]
005c movsw word ptr es:[di], word ptr [si]
005d movsw word ptr es:[di], word ptr [si]
005e movsw word ptr es:[di], word ptr [si]
005f pop ds
0060 cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
0065 je 0xd747
0067 inc word ptr [bp - 4]
006a inc word ptr [bp - 2]
006d push word ptr [bp + 6]
0070 nop 
0071 push cs
0072 call 0xe3a4 ; _win_UnlockWin
0075 add sp, 2
0078 push word ptr [0xcf52] ; _clipDC
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 30}}]
0081 push word ptr [0xcf52] ; _clipDC
0085 push word ptr [bp - 8]
0088 push word ptr [bp - 6]
008b push word ptr [bp - 4]
008e push word ptr [bp - 2]
0091 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 22}}]
0096 lea ax, [bp - 0x6c]
0099 push ss
009a push ax
009b lea ax, [bp - 8]
009e push ss
009f push ax
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_CenterStrInRectClear
00a5 add sp, 8
00a8 push word ptr [0xcf52] ; _clipDC
00ac push -1
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 39}}]
00b3 pop si
00b4 pop di
00b5 leave 
00b6 retf 
```

## Known declaration examples

- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near clipDC;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *text);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetObjBitmap', 'offset': 54718, 'source': None, 'size': 123}
- {'symbol': '_win_CenterStrAtObj', 'offset': 54842, 'source': 'src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c', 'size': 160}
- {'symbol': '_win_ClearObjToEOL', 'offset': 55186, 'source': None, 'size': 290}
- {'symbol': '_win_ObjFormatPrint', 'offset': 55476, 'source': None, 'size': 552}

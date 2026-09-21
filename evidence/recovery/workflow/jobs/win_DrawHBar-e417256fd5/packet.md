# Recovery task _win_DrawHBar

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 192 bytes.

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
004d je 0xdb31
004f inc word ptr [bp - 4]
0052 inc word ptr [bp - 2]
0055 push word ptr [bp + 6]
0058 nop 
0059 push cs
005a call 0xe3a4 ; _win_UnlockWin
005d add sp, 2
0060 mov si, word ptr [bp - 4]
0063 push 1
0065 push 0
0067 push word ptr [bp + 0xa]
006a push word ptr [bp + 8]
006d mov ax, si
006f sub ax, word ptr [bp - 8]
0072 cdq 
0073 push dx
0074 push ax
0075 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 120, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
007a push dx
007b push ax
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0081 add ax, word ptr [bp - 8]
0084 mov word ptr [bp - 4], ax
0087 cmp ax, word ptr [bp - 8]
008a jle 0xdb79
008c push word ptr [0xcf4e] ; __foreColor
0090 lea ax, [bp - 8]
0093 push ss
0094 push ax
0095 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
009a add sp, 6
009d cmp word ptr [bp - 4], si
00a0 jge 0xdb98
00a2 mov ax, word ptr [bp - 4]
00a5 mov word ptr [bp - 8], ax
00a8 mov word ptr [bp - 4], si
00ab push word ptr [0xce8a] ; __backColor
00af lea ax, [bp - 8]
00b2 push ss
00b3 push ax
00b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
00b9 add sp, 6
00bc pop si
00bd pop di
00be leave 
00bf retf 
```

## Known declaration examples

- `extern void far GRectFill(void far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_PrintfAtObj-9e4b836702.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_ClearObjToEOL', 'offset': 55186, 'source': None, 'size': 290}
- {'symbol': '_win_ObjFormatPrint', 'offset': 55476, 'source': None, 'size': 552}
- {'symbol': '_win_DrawVBar', 'offset': 56220, 'source': None, 'size': 194}
- {'symbol': '_win_GetObjSize', 'offset': 56414, 'source': 'src/recovered/wf_win_GetObjSize-35d87c4c75.c', 'size': 98}

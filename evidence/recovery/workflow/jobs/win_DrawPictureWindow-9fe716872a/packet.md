# Recovery task _win_DrawPictureWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 198 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 test byte ptr [bp + 6], 2
000a jne 0x6205
000c jmp 0x62b8
000f lea ax, [bp - 0x10]
0012 push ss
0013 push ax
0014 push 0x1e00
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
001c add sp, 6
001f cmp word ptr [0xcaba], 0
0024 jne 0x6222
0026 add word ptr [bp - 0xe], 2
002a jmp 0x625a
002c push word ptr [0xcaba]
0030 lea ax, [bp - 8]
0033 push ss
0034 push ax
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
003a add sp, 6
003d push word ptr [0xcaba]
0041 push word ptr [bp - 0xe]
0044 mov ax, word ptr [bp - 0xc]
0047 sub ax, word ptr [bp - 8]
004a add ax, word ptr [bp - 0x10]
004d cdq 
004e sub ax, dx
0050 sar ax, 1
0052 push ax
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMap
0058 add sp, 6
005b mov ax, word ptr [bp - 6]
005e add ax, 2
0061 add word ptr [bp - 0xe], ax
0064 push 4
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
006b add sp, 2
006e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
0073 mov di, ax
0075 push 0x1e01
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
007d add sp, 2
0080 mov word ptr [bp - 2], 0
0085 cmp word ptr [0xcab8], 0
008a jle 0x62b8
008c xor si, si
008e mov word ptr [bp - 4], di
0091 mov ax, word ptr [bp - 0xe]
0094 add ax, di
0096 mov word ptr [bp - 0xa], ax
0099 les bx, ptr [0xcab4]
009d push word ptr es:[bx + si + 2]
00a1 push word ptr es:[bx + si]
00a4 lea ax, [bp - 0x10]
00a7 push ss
00a8 push ax
00a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_CenterStrInRect
00ae add sp, 8
00b1 add word ptr [bp - 0xe], di
00b4 add si, 4
00b7 mov ax, word ptr [0xcab8]
00ba inc word ptr [bp - 2]
00bd cmp word ptr [bp - 2], ax
00c0 jl 0x6287
00c2 pop si
00c3 pop di
00c4 leave 
00c5 retf 
```

## Known declaration examples

- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/win_StringSize.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern int far win_DrawBitMap(unsigned int bitmap, unsigned int bitmapMask, int bitmapNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_PrintfAtObj-9e4b836702.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetDefaultWindPrompt', 'offset': 24780, 'source': None, 'size': 141}
- {'symbol': '_PictStrnDialog', 'offset': 24922, 'source': 'src/recovered/wf_PictStrnDialog-d2f52b0e98.c', 'size': 155}
- {'symbol': '_PictureDialog', 'offset': 25276, 'source': None, 'size': 535}
- {'symbol': '_win_DrawEndGameWindow', 'offset': 25812, 'source': None, 'size': 301}

# Recovery task _UpdateYardMessage

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 202 bytes.

```asm
0000 push 0x1900
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0008 add sp, 2
000b or ax, ax
000d jne 0xac20
000f jmp 0xacd7
0012 cmp word ptr [0xbcec], 0
0017 jne 0xac2a
0019 jmp 0xacd7
001c push 0x1900
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0024 add sp, 2
0027 or ax, ax
0029 jne 0xac3c
002b jmp 0xacd7
002e push word ptr [0xbcd8]
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0037 add sp, 2
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
003f mov es, word ptr [0xc1ac]
0043 cmp dx, word ptr es:[0x19a4]
0048 jl 0xac7e
004a jg 0xac61
004c cmp ax, word ptr es:[0x19a2]
0051 jbe 0xac7e
0053 mov es, word ptr [0xc1ae]
0057 sub ax, ax
0059 mov word ptr es:[0x1448], ax
005d mov word ptr es:[0x1446], ax
0061 mov es, word ptr [0xc1b0]
0065 mov word ptr es:[0x19a0], ax
0069 mov word ptr es:[0x199e], ax
006d jmp 0xacbc
006f nop 
0070 mov es, word ptr [0xc1b0]
0074 mov ax, word ptr es:[0x19a0]
0078 or ax, word ptr es:[0x199e]
007d je 0xacbc
007f push 2
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0086 add sp, 2
0089 mov es, word ptr [0xc1b0]
008d push word ptr es:[0x19a0]
0092 push word ptr es:[0x199e]
0097 push 0x1916
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
009f add sp, 6
00a2 push 0
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
00a9 add sp, 2
00ac jmp 0xacd2
00ae push 0xc
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00b5 add sp, 2
00b8 push ax
00b9 push 0x1916
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
00c1 add sp, 4
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00c9 retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, char far *format, ...);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EraseYardCursor', 'offset': 43452, 'source': 'src/recovered/EraseYardCursor.c', 'size': 36}
- {'symbol': '_win_DrawYardWindow', 'offset': 43488, 'source': None, 'size': 558}
- {'symbol': '_DrawYardData', 'offset': 44248, 'source': None, 'size': 460}
- {'symbol': '_DrawYard', 'offset': 44708, 'source': 'src/recovered/wf_DrawYard-bff77801c5.c', 'size': 56}

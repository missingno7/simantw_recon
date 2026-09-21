# Recovery task _DrawAnimYardMessage

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 184 bytes.

```asm
0000 cmp word ptr [0xbcec], 0
0005 jne 0xb3b4
0007 jmp 0xb461
000a push 0x1900
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0012 add sp, 2
0015 or ax, ax
0017 jne 0xb3c6
0019 jmp 0xb461
001c push word ptr [0xbcd8]
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0025 add sp, 2
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
002d mov es, word ptr [0xc1ac]
0031 cmp dx, word ptr es:[0x19a4]
0036 jl 0xb408
0038 jg 0xb3eb
003a cmp ax, word ptr es:[0x19a2]
003f jbe 0xb408
0041 mov es, word ptr [0xc1ae]
0045 sub ax, ax
0047 mov word ptr es:[0x1448], ax
004b mov word ptr es:[0x1446], ax
004f mov es, word ptr [0xc1b0]
0053 mov word ptr es:[0x19a0], ax
0057 mov word ptr es:[0x199e], ax
005b jmp 0xb446
005d nop 
005e mov es, word ptr [0xc1b0]
0062 mov ax, word ptr es:[0x19a0]
0066 or ax, word ptr es:[0x199e]
006b je 0xb446
006d push 2
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0074 add sp, 2
0077 mov es, word ptr [0xc1b0]
007b push word ptr es:[0x19a0]
0080 push word ptr es:[0x199e]
0085 push 0x1916
0088 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 139, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
008d add sp, 6
0090 push 0
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0097 add sp, 2
009a jmp 0xb45c
009c push 0xc
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00a3 add sp, 2
00a6 push ax
00a7 push 0x1916
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
00af add sp, 4
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00b7 retf 
```

## Known declaration examples

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
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern void far win_PrintfAtObj(int object, char far *format, ...);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawForSale', 'offset': 45700, 'source': 'src/recovered/wf_DrawForSale-956dc12b43.c', 'size': 63}
- {'symbol': '_DrawMower', 'offset': 45764, 'source': None, 'size': 229}
- {'symbol': '_Draw_SimYard', 'offset': 46178, 'source': None, 'size': 1595}
- {'symbol': '_DrawRain', 'offset': 47774, 'source': 'src/recovered/wf_DrawRain-d667f83eb1.c', 'size': 112}

# Recovery task _DoDebugWin

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 179 bytes.

```asm
0000 push di
0001 push si
0002 cmp word ptr [0x29c], -1
0007 jne 0x1cd1
0009 cmp word ptr [0x29e], -1
000e jne 0x1cd1
0010 jmp 0x1d62
0013 add word ptr [0x2a0], 1
0018 adc word ptr [0x2a2], 0
001d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 13}}]
0022 sub ax, word ptr [0x29c]
0026 sbb dx, word ptr [0x29e]
002a add word ptr [0x2a4], ax
002e adc word ptr [0x2a6], dx
0032 push 0
0034 push 5
0036 push word ptr [0x2a2]
003a push word ptr [0x2a0]
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFlrem
0043 or dx, ax
0045 jne 0x1d62
0047 push word ptr [0xbcde]
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0050 add sp, 2
0053 push 2
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
005a add sp, 2
005d push word ptr [0x2a2]
0061 push word ptr [0x2a0]
0065 push word ptr [0x2a6]
0069 push word ptr [0x2a4]
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0072 push dx
0073 push ax
0074 push 0
0076 push 0xea60
0079 mov si, ax
007b mov di, dx
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0082 push dx
0083 push ax
0084 push di
0085 push si
0086 push ds
0087 push 0x2a8
008a push 0x1c03
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
0092 add sp, 0xe
0095 push 0
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
009c add sp, 2
009f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 162, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 13}}]
00a9 mov word ptr [0x29c], ax
00ac mov word ptr [0x29e], dx
00b0 pop si
00b1 pop di
00b2 retf 
```

## Known declaration examples

- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': 'MYENUMFUNC', 'offset': 7224, 'source': None, 'size': 48}
- {'symbol': '_RedrawWindows', 'offset': 7272, 'source': None, 'size': 86}
- {'symbol': '_NetBIOSPost', 'offset': 7538, 'source': None, 'size': None}
- {'symbol': '_ProcessPost', 'offset': 7615, 'source': None, 'size': 672}

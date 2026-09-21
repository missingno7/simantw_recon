# Recovery task _DrawRibbonMessage

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 156 bytes.

```asm
0000 push word ptr [0xbcea]
0004 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0009 add sp, 2
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0011 mov es, word ptr [0xbe80]
0015 cmp dx, word ptr es:[0x19a4]
001a jl 0xb68
001c jg 0xb4b
001e cmp ax, word ptr es:[0x19a2]
0023 jbe 0xb68
0025 mov es, word ptr [0xbe82]
0029 sub ax, ax
002b mov word ptr es:[0x1448], ax
002f mov word ptr es:[0x1446], ax
0033 mov es, word ptr [0xbe84]
0037 mov word ptr es:[0x19a0], ax
003b mov word ptr es:[0x199e], ax
003f jmp 0xba6
0041 nop 
0042 mov es, word ptr [0xbe84]
0046 mov ax, word ptr es:[0x19a0]
004a or ax, word ptr es:[0x199e]
004f je 0xba6
0051 push 2
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0058 add sp, 2
005b mov es, word ptr [0xbe84]
005f push word ptr es:[0x19a0]
0064 push word ptr es:[0x199e]
0069 push 0x221f
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
0071 add sp, 6
0074 push 0
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
007b add sp, 2
007e jmp 0xbbc
0080 push 0xc
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0087 add sp, 2
008a push ax
008b push 0x221f
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
0093 add sp, 4
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
009b retf 
```

## Known declaration examples

- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoBookMark', 'offset': 2214, 'source': None, 'size': 513}
- {'symbol': '_ClearBookmarks', 'offset': 2728, 'source': 'src/recovered/wf_ClearBookmarks-ffba50efd3.c', 'size': 125}
- {'symbol': '_DoEvent', 'offset': 3010, 'source': None, 'size': 548}
- {'symbol': '_HelpKeyDown', 'offset': 3558, 'source': None, 'size': 166}

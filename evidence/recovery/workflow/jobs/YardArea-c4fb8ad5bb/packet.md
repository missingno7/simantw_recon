# Recovery task _YardArea

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 255 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov es, word ptr [bp + 8]
000c mov ax, word ptr es:[si + 0xa]
0010 mov es, word ptr [0xc1c4]
0014 sub ax, word ptr es:[0x8112]
0019 sub ax, word ptr [0x1896]
001d mov cx, 0xa
0020 cdq 
0021 idiv cx
0023 mov di, ax
0025 mov dx, di
0027 shl ax, 2
002a add ax, dx
002c shl ax, 1
002e mov es, word ptr [bp + 8]
0031 add ax, word ptr es:[si + 8]
0035 mov es, word ptr [0xc1c4]
0039 sub ax, word ptr es:[0x8110]
003e sub ax, word ptr [0x1894] ; _patchRgn
0042 mov dx, 0x1c
0045 mov bx, dx
0047 cdq 
0048 idiv bx
004a mov word ptr [bp - 2], ax
004d or ax, ax
004f jge 0xc0ee
0051 jmp 0xc195
0054 cmp ax, 0xc
0057 jl 0xc0f6
0059 jmp 0xc195
005c or di, di
005e jge 0xc0fd
0060 jmp 0xc195
0063 cmp di, 0x10
0066 jl 0xc105
0068 jmp 0xc195
006b push word ptr [0xbcd8]
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0074 push word ptr [0xbcd8]
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
007d add sp, 2
0080 cmp word ptr [0x18b6], 0
0085 je 0xc13d
0087 mov es, word ptr [0xc19e]
008b push word ptr es:[0x7a62]
0090 push word ptr es:[0x7a60]
0095 nop 
0096 push cs
0097 call 0xbe04 ; _InvertPatch
009a add sp, 4
009d mov word ptr [0x18b6], 0
00a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00a8 mov ax, word ptr [bp - 2]
00ab mov es, word ptr [0xc1de]
00af mov word ptr es:[0x789e], ax
00b3 mov word ptr es:[0x78a0], di
00b8 mov es, word ptr [bp + 8]
00bb test byte ptr es:[si + 7], 0x60
00c0 je 0xc161
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _XferPatch
00c7 push word ptr [0xbcd8]
00cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00d0 add sp, 2
00d3 cmp word ptr [0x18b6], 0
00d8 jne 0xc190
00da mov es, word ptr [0xc19e]
00de push word ptr es:[0x7a62]
00e3 push word ptr es:[0x7a60]
00e8 nop 
00e9 push cs
00ea call 0xbe04 ; _InvertPatch
00ed add sp, 4
00f0 mov word ptr [0x18b6], 1
00f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 249, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00fb pop si
00fc pop di
00fd leave 
00fe retf 
```

## Known declaration examples

- `extern void far InvertPatch(int x, int y);` — src/recovered/DrawYardCursor.c
- `extern void far InvertPatch(int x, int y);` — src/recovered/EraseYardCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawSimColonies', 'offset': 48804, 'source': None, 'size': 247}
- {'symbol': '_DrawColonyBars', 'offset': 49052, 'source': None, 'size': 253}
- {'symbol': '_DeinitMapFunctions', 'offset': 49562, 'source': 'src/recovered/DeinitMapFunctions.c', 'size': 1}
- {'symbol': '_InitMapFunctions', 'offset': 49564, 'source': 'src/recovered/wf_InitMapFunctions-70fb457ea5.c', 'size': 133}

# Recovery task _PaintStuff

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 290 bytes.

```asm
0000 enter 0x22, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 cmp word ptr [0xcd7e], si ; _mainRootWnd
000d jne 0x3ea4
000f jmp 0x3f9e
0012 cmp word ptr [0xcd78], si ; _rootWnd
0016 jne 0x3ead
0018 jmp 0x3f9e
001b push si
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0021 or ax, ax
0023 jne 0x3eba
0025 jmp 0x3f9e
0028 push si
0029 push ds
002a push 0xbabe
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
0032 mov di, ax
0034 push 0
0036 push 0x4e20
0039 nop 
003a push cs
003b call 0x56a8 ; _RallocFindMem
003e add sp, 4
0041 mov word ptr [0xce8e], si ; _clipWind
0045 push 0
0047 push 0
0049 push 0xa
004b push 0xa
004d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
0052 mov word ptr [0xcd84], ax ; _updateRgn
0055 push word ptr [0xce8e] ; _clipWind
0059 push ax
005a push 0
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 237}}]
0061 push word ptr [0xce8e] ; _clipWind
0065 lea ax, [bp - 0x22]
0068 push ss
0069 push ax
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 39}}]
006f mov word ptr [0xcf52], ax ; _clipDC
0072 or ax, ax
0074 je 0x3f83
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InitPalette
007b push word ptr [0xcf52] ; _clipDC
007f push word ptr [0x85a] ; _paletteH
0083 push 0
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 134, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 282}}]
008a mov word ptr [bp - 2], ax
008d push word ptr [0xcf52] ; _clipDC
0091 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 283}}]
0096 mov word ptr [0xcc54], 0
009c nop 
009d push cs
009e call 0x1664 ; _GSetBigFont
00a1 push di
00a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawWindow
00a7 add sp, 2
00aa mov ax, word ptr [bp + 0x12]
00ad or ax, word ptr [bp + 0x10]
00b0 je 0x3f47
00b2 lcall [bp + 0x10]
00b5 cmp word ptr [bp - 2], 0
00b9 je 0x3f5b
00bb push word ptr [0xcf52] ; _clipDC
00bf push word ptr [bp - 2]
00c2 push 0
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 282}}]
00c9 cmp word ptr [0xcc54], 0
00ce je 0x3f75
00d0 push word ptr [0xcf52] ; _clipDC
00d4 push word ptr [0xcc54]
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
00dd mov word ptr [0xcc54], 0
00e3 push word ptr [0xce8e] ; _clipWind
00e7 lea ax, [bp - 0x22]
00ea push ss
00eb push ax
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 237, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 40}}]
00f1 push word ptr [0xcd84] ; _updateRgn
00f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
00fa xor ax, ax
00fc mov word ptr [0xcd84], ax ; _updateRgn
00ff mov word ptr [0xce8e], ax ; _clipWind
0102 mov word ptr [0xcf52], ax ; _clipDC
0105 cdq 
0106 pop si
0107 pop di
0108 leave 
0109 retf 
010a nop 
010b nop 
010c push si
010d push word ptr [bp + 8]
0110 push word ptr [bp + 0xa]
0113 push word ptr [bp + 0xe]
0116 push word ptr [bp + 0xc]
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 107}}]
011e pop si
011f pop di
0120 leave 
0121 retf 
```

## Known declaration examples

- `extern void far RallocFindMem(long bytes);` — src/recovered/wf_Ralloc-b43a5ad4e7.c
- `extern void far RallocFindMem(int low, int high);` — src/recovered/wf_RallocFree-a82b13cb86.c
- `extern void far RallocFindMem(long bytes);` — src/recovered/wf_RallocRealloc-d8db281862.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near clipWind;` — src/recovered/wf_GBoxMove-31918745e5.c
- `extern int near clipWind;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near mainRootWnd;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near paletteH;` — src/recovered/ClosePalette.c
- `extern int near paletteH[];` — src/recovered/SetDebugFlag.c
- `extern int near paletteH[];` — src/recovered/mem_Debugging.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MSClipStart', 'offset': 15866, 'source': None, 'size': 81}
- {'symbol': '_MSClipEnd', 'offset': 15948, 'source': 'src/recovered/wf_MSClipEnd-48c3851864.c', 'size': 70}
- {'symbol': '_GLine', 'offset': 16308, 'source': 'src/recovered/wf_GLine-590430737a.c', 'size': 132}
- {'symbol': '_RedrawScreen', 'offset': 16440, 'source': 'src/recovered/RedrawScreen.c', 'size': 25}

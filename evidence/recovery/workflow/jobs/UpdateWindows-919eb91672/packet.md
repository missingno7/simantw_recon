# Recovery task _UpdateWindows

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 540 bytes.

```asm
0000 enter 8, 0
0004 mov bx, 0x8614
0007 mov es, word ptr [0xbe78]
000b mov word ptr [bp - 4], bx
000e mov word ptr [bp - 2], es
0011 cmp word ptr es:[bx], 0
0015 je 0x226e
0017 cmp word ptr es:[bx], 1
001b je 0x226e
001d cmp word ptr es:[bx], 2
0021 jne 0x2253
0023 mov es, word ptr [0xbe98]
0027 test byte ptr es:[0x9b00], 1
002d je 0x226e
002f les bx, ptr [bp - 4]
0032 cmp word ptr es:[bx], 3
0036 je 0x225f
0038 jmp 0x242d
003b mov es, word ptr [0xbe98]
003f test byte ptr es:[0x9b00], 3
0045 je 0x226e
0047 jmp 0x242d
004a push 0x100
004d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0052 add sp, 2
0055 or ax, ax
0057 je 0x22da
0059 mov bx, 0x72f0
005c mov es, word ptr [0xbe9a]
0060 mov word ptr [bp - 8], bx
0063 mov word ptr [bp - 6], es
0066 cmp word ptr es:[bx], 0
006a jl 0x22ca
006c push 0x100
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0074 add sp, 2
0077 or ax, ax
0079 jne 0x22ca
007b les bx, ptr [bp - 4]
007e cmp word ptr es:[bx], 3
0082 je 0x22ca
0084 les bx, ptr [bp - 8]
0087 mov al, byte ptr es:[bx]
008a and al, 1
008c cmp al, 1
008e jne 0x22bc
0090 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
0095 jmp 0x22c1
0097 nop 
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapData
009d les bx, ptr [bp - 8]
00a0 xor byte ptr es:[bx], 1
00a4 jmp 0x22df
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
00ab les bx, ptr [bp - 8]
00ae mov word ptr es:[bx], 0
00b3 jmp 0x22df
00b5 nop 
00b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapData
00bb push 0x1900
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 193, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00c3 add sp, 2
00c6 or ax, ax
00c8 je 0x2349
00ca push 0x48
00cc push ds
00cd push 0x2e6
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitedEnough
00d5 add sp, 6
00d8 or ax, ax
00da jne 0x231a
00dc cmp word ptr [0xce82], 2 ; _YardMode
00e1 jl 0x231a
00e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 230, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawYardData
00e8 cmp word ptr [0xce82], 1 ; _YardMode
00ed jle 0x2349
00ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 242, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateYardMessage
00f4 jmp 0x2349
00f6 push 0x1900
00f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 252, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
00fe add sp, 2
0101 or ax, ax
0103 jne 0x233e
0105 mov al, byte ptr [0x2ea]
0108 and al, 1
010a cmp al, 1
010c je 0x233e
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawYardData
0113 xor byte ptr [0x2ea], 1
0118 jmp 0x2349
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 285, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateYard
011f mov word ptr [0x2ea], 0
0125 push 0
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
012c add sp, 2
012f or ax, ax
0131 je 0x2381
0133 push 0
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 312, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
013a add sp, 2
013d or ax, ax
013f jne 0x2376
0141 mov al, byte ptr [0x2ec]
0144 and al, 1
0146 cmp al, 1
0148 je 0x2376
014a xor byte ptr [0x2ec], 1
014f jmp 0x2381
0151 nop 
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0157 mov word ptr [0x2ec], 0
015d push 0x2200
0160 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 355, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0165 add sp, 2
0168 or ax, ax
016a jne 0x2393
016c jmp 0x242d
016f push word ptr [0xbcea]
0173 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 374, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0178 add sp, 2
017b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 382, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0180 mov es, word ptr [0xbe80]
0184 cmp dx, word ptr es:[0x19a4]
0189 jl 0x23d4
018b jg 0x23b8
018d cmp ax, word ptr es:[0x19a2]
0192 jbe 0x23d4
0194 mov es, word ptr [0xbe82]
0198 sub ax, ax
019a mov word ptr es:[0x1448], ax
019e mov word ptr es:[0x1446], ax
01a2 mov es, word ptr [0xbe84]
01a6 mov word ptr es:[0x19a0], ax
01aa mov word ptr es:[0x199e], ax
01ae jmp 0x2412
01b0 mov es, word ptr [0xbe84]
01b4 mov ax, word ptr es:[0x19a0]
01b8 or ax, word ptr es:[0x199e]
01bd je 0x2412
01bf push 2
01c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 452, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
01c6 add sp, 2
01c9 mov es, word ptr [0xbe84]
01cd push word ptr es:[0x19a0]
01d2 push word ptr es:[0x199e]
01d7 push 0x221f
01da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 477, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
01df add sp, 6
01e2 push 0
01e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 487, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
01e9 add sp, 2
01ec jmp 0x2428
01ee push 0xc
01f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 499, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
01f5 add sp, 2
01f8 push ax
01f9 push 0x221f
01fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 511, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
0201 add sp, 4
0204 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 519, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0209 mov es, word ptr [0xbe98]
020d mov al, byte ptr es:[0x9b00]
0211 inc al
0213 and ax, 0x3f
0216 mov word ptr es:[0x9b00], ax
021a leave 
021b retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far DrawYardData(void);` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbort-1a41498b6d.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbortOrCont-ea87855190.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogWait-50782e4ed5.c
- `extern int near YardMode;` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ProcessPost', 'offset': 7615, 'source': None, 'size': 672}
- {'symbol': '_NetworkSend', 'offset': 8288, 'source': None, 'size': 451}
- {'symbol': 'MYTIMERFUNC', 'offset': 9280, 'source': None, 'size': 973}
- {'symbol': '_LoadFancyCursor', 'offset': 10254, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 113}

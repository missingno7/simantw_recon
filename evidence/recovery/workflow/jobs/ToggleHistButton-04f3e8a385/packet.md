# Recovery task _ToggleHistButton

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 400 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 push 0x1500
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
000e add sp, 2
0011 mov es, word ptr [0xc084]
0015 mov si, word ptr [bp + 6]
0018 sub si, 0x1503
001c cmp byte ptr es:[si - 0x71c8], 0
0022 je 0x8c0c
0024 xor di, di
0026 mov dx, 0x8e54
0029 mov word ptr [bp - 2], dx
002c mov word ptr [bp - 6], si
002f mov si, dx
0031 mov cx, word ptr [bp - 6]
0034 mov <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0037 mov ds, ax
0039 cmp word ptr [si], cx
003b je 0x8bb8
003d inc di
003e add si, 2
0041 cmp si, 0x8e5c
0045 jb 0x8ba5
0047 push ss
0048 pop ds
0049 jmp 0x8bea
004b nop 
004c push ss
004d pop ds
004e mov ax, di
0050 sub di, 4
0053 neg di
0055 shl di, 1
0057 push di
0058 shl ax, 1
005a mov cx, ax
005c add ax, 0x8e56
005f push <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0062 push ax
0063 add cx, 0x8e54
0067 push <resolved loader operand; see bindings> ; [{'operand_offset': 104, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
006a push cx
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
0070 add sp, 0xa
0073 mov es, word ptr [0xc084]
0077 mov word ptr es:[0x8e5a], 0x8000
007e mov es, word ptr [0xc084]
0082 mov bx, word ptr [bp - 6]
0085 mov byte ptr es:[bx - 0x71c8], 0
008b shl bx, 1
008d mov cl, byte ptr es:[bx - 0x71f0]
0092 mov ax, 1
0095 shl ax, cl
0097 or word ptr es:[0x8e5c], ax
009c jmp 0x8ca5
009f nop 
00a0 mov word ptr [bp - 6], si
00a3 mov di, si
00a5 mov byte ptr es:[di - 0x71c8], 1
00ab mov si, word ptr es:[0x8e5a]
00b0 cmp si, 0x8000
00b4 je 0x8c4a
00b6 mov byte ptr es:[si - 0x71c8], 0
00bc lea ax, [si + 0x1503]
00c0 push ax
00c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 196, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjUnselected
00c6 add sp, 2
00c9 mov es, word ptr [0xc084]
00cd shl si, 1
00cf mov cl, byte ptr es:[si - 0x71f0]
00d4 mov ax, 1
00d7 shl ax, cl
00d9 or word ptr es:[0x8e5c], ax
00de push 6
00e0 push <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00e3 push 0x8e54
00e6 push <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00e9 push 0x8e56
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
00f1 add sp, 0xa
00f4 mov es, word ptr [0xc084]
00f8 mov word ptr es:[0x8e54], di
00fd xor si, si
00ff mov word ptr [bp - 2], 1
0104 mov word ptr [bp - 4], si
0107 mov si, word ptr [bp - 2]
010a mov di, word ptr [bp - 4]
010d mov <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0110 mov es, ax
0112 test word ptr es:[0x8e5c], si
0117 jne 0x8c90
0119 shl si, 1
011b inc di
011c cmp di, 4
011f jl 0x8c7e
0121 jmp 0x8ca5
0123 nop 
0124 not si
0126 mov es, word ptr [0xc084]
012a and word ptr es:[0x8e5c], si
012f mov bx, word ptr [bp - 6]
0132 shl bx, 1
0134 mov word ptr es:[bx - 0x71f0], di
0139 push word ptr [0xbcd0]
013d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0142 add sp, 2
0145 push 0
0147 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 330, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
014c add sp, 2
014f push ax
0150 push 0x150e
0153 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 342, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
0158 add sp, 4
015b xor di, di
015d mov si, 0x8e54
0160 mov es, word ptr [0xc084]
0164 mov ax, word ptr es:[si]
0167 cmp ax, 0x8000
016a je 0x8ce4
016c push di
016d push 0
016f push ax
0170 nop 
0171 push cs
0172 call 0x8e78 ; _drawHistGraph
0175 add sp, 6
0178 inc di
0179 add si, 2
017c cmp si, 0x8e5c
0180 jb 0x8ccc
0182 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 389, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0187 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 394, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
018c pop si
018d pop di
018e leave 
018f retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OpenHistoryWindow', 'offset': 35434, 'source': 'src/recovered/OpenHistoryWindow.c', 'size': 12}
- {'symbol': '_ProcHistoryEvent', 'offset': 35446, 'source': None, 'size': 245}
- {'symbol': '_ClearHistory', 'offset': 36092, 'source': None, 'size': 299}
- {'symbol': '_win_DrawHistoryWindow', 'offset': 36392, 'source': None, 'size': 80}

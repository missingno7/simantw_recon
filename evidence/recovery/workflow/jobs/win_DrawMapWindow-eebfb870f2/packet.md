# Recovery task _win_DrawMapWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 712 bytes.

```asm
0000 enter 0xe, 0
0004 push si
0005 test byte ptr [bp + 6], 2
0009 jne 0xce54
000b jmp 0xd10b
000e mov bx, 0x8610
0011 mov es, word ptr [0xc1ee]
0015 mov word ptr [bp - 0xc], bx
0018 mov word ptr [bp - 0xa], es
001b cmp word ptr es:[bx], 0
001f jne 0xce70
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MapToYard
0026 pop si
0027 leave 
0028 retf 
0029 nop 
002a push 0x100
002d nop 
002e push cs
002f call 0x8e44 ; _clip_SetWin
0032 add sp, 2
0035 push 0x100
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
003d add sp, 2
0040 or ax, ax
0042 je 0xcebc
0044 cmp word ptr [0x1992], 1 ; _mapCursorState
0049 jne 0xcebc
004b nop 
004c push cs
004d call 0x8e50 ; _clip_Push
0050 push 0x100
0053 nop 
0054 push cs
0055 call 0x8e44 ; _clip_SetWin
0058 add sp, 2
005b push 2
005d push <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0060 push 0x72ae
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 102, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
0068 add sp, 6
006b mov word ptr [0x1992], 0 ; _mapCursorState
0071 nop 
0072 push cs
0073 call 0x8e4e ; _clip_Pop
0076 cmp word ptr [0x19aa], 0 ; _mapBuf
007b jne 0xcec6
007d jmp 0xd053
0080 cmp word ptr [0xcd84], 0 ; _updateRgn
0085 je 0xcee3
0087 push word ptr [0xcd84] ; _updateRgn
008b push <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
008e push 0x8110
0091 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 181}}]
0096 or ax, ax
0098 jne 0xcee3
009a jmp 0xd053
009d push word ptr [0x19aa] ; _mapBuf
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00a6 add sp, 2
00a9 mov si, ax
00ab mov word ptr [bp - 6], dx
00ae les bx, ptr [bp - 0xc]
00b1 cmp word ptr es:[bx], 2
00b5 je 0xcf66
00b7 cmp word ptr es:[bx], 3
00bb je 0xcf66
00bd mov es, word ptr [0xc1f2]
00c1 mov ax, word ptr es:[0x8110]
00c5 mov word ptr [bp - 4], ax
00c8 mov ax, word ptr es:[0x8112]
00cc mov word ptr [bp - 2], ax
00cf test byte ptr [0xcc7e], 1 ; _displayType
00d4 jne 0xcf4a
00d6 push 0
00d8 push dx
00d9 push si
00da mov es, word ptr [0xc1e2]
00de mov ax, word ptr es:[0x8096]
00e2 shl ax, 6
00e5 push ax
00e6 mov es, word ptr [0xc1e4]
00ea mov ax, word ptr es:[0x807c]
00ee shl ax, 7
00f1 push ax
00f2 push word ptr [bp - 2]
00f5 push word ptr [bp - 4]
00f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastBitmap
00fd add sp, 0xe
0100 jmp 0xd047
0103 nop 
0104 push dx
0105 push si
0106 mov es, word ptr [0xc1e2]
010a mov ax, word ptr es:[0x8096]
010e shl ax, 6
0111 push ax
0112 mov es, word ptr [0xc1e4]
0116 mov ax, word ptr es:[0x807c]
011a shl ax, 7
011d jmp 0xd038
0120 push 0xf
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0127 add sp, 2
012a push ax
012b mov es, word ptr [0xc1f2]
012f push word ptr es:[0x8116]
0134 mov es, word ptr [0xc1e4]
0138 mov ax, word ptr es:[0x807c]
013c shl ax, 5
013f mov es, word ptr [0xc1f2]
0143 add ax, word ptr es:[0x8110]
0148 dec ax
0149 push ax
014a push word ptr es:[0x8112]
014f push word ptr es:[0x8110]
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
0159 add sp, 0xa
015c push 0xf
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0163 add sp, 2
0166 push ax
0167 mov es, word ptr [0xc1f2]
016b push word ptr es:[0x8116]
0170 push word ptr es:[0x8114]
0175 push word ptr es:[0x8112]
017a mov es, word ptr [0xc1e4]
017e mov ax, word ptr es:[0x807c]
0182 shl ax, 5
0185 mov es, word ptr [0xc1f2]
0189 sub ax, word ptr es:[0x8114]
018e neg ax
0190 push ax
0191 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
0196 add sp, 0xa
0199 mov es, word ptr [0xc1e4]
019d mov ax, word ptr es:[0x807c]
01a1 mov word ptr [bp - 0xe], ax
01a4 shl ax, 5
01a7 mov es, word ptr [0xc1f2]
01ab add ax, word ptr es:[0x8110]
01b0 mov word ptr [bp - 4], ax
01b3 mov ax, word ptr es:[0x8112]
01b7 mov word ptr [bp - 2], ax
01ba test byte ptr [0xcc7e], 1 ; _displayType
01bf jne 0xd022
01c1 push 0
01c3 push word ptr [bp - 6]
01c6 push si
01c7 mov es, word ptr [0xc1e2]
01cb mov ax, word ptr es:[0x8096]
01cf shl ax, 6
01d2 push ax
01d3 mov ax, word ptr [bp - 0xe]
01d6 shl ax, 6
01d9 jmp 0xcf37
01dc push word ptr [bp - 6]
01df push si
01e0 mov es, word ptr [0xc1e2]
01e4 mov ax, word ptr es:[0x8096]
01e8 shl ax, 6
01eb push ax
01ec mov ax, word ptr [bp - 0xe]
01ef shl ax, 6
01f2 push ax
01f3 push word ptr [bp - 2]
01f6 push word ptr [bp - 4]
01f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 508, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastMonoBitmap
01fe add sp, 0xc
0201 push word ptr [0x19aa] ; _mapBuf
0205 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 520, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
020a add sp, 2
020d push 0x100
0210 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 531, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0215 add sp, 2
0218 or ax, ax
021a jne 0xd065
021c jmp 0xd10b
021f cmp word ptr [0x1992], 0 ; _mapCursorState
0224 je 0xd06f
0226 jmp 0xd10b
0229 nop 
022a push cs
022b call 0x8e50 ; _clip_Push
022e push 0x100
0231 nop 
0232 push cs
0233 call 0x8e44 ; _clip_SetWin
0236 add sp, 2
0239 mov es, word ptr [0xc1e2]
023d mov ax, word ptr es:[0x8096]
0241 mov es, word ptr [0xc1f0]
0245 mov cx, ax
0247 imul word ptr es:[0x7d30]
024c mov es, word ptr [0xc1f2]
0250 add ax, word ptr es:[0x8112]
0255 mov es, word ptr [0xc1f4]
0259 mov word ptr es:[0x72b0], ax
025d mov dx, ax
025f mov ax, cx
0261 mov bx, dx
0263 imul word ptr [0xcd7a] ; _editHeight
0267 add bx, ax
0269 mov word ptr es:[0x72b4], bx
026e mov es, word ptr [0xc1e4]
0272 mov ax, word ptr es:[0x807c]
0276 mov es, word ptr [0xc1f0]
027a mov cx, ax
027c imul word ptr es:[0x7d2e]
0281 mov es, word ptr [0xc1f2]
0285 add ax, word ptr es:[0x8110]
028a mov es, word ptr [0xc1f6]
028e add ax, word ptr es:[0x9bc6]
0293 mov es, word ptr [0xc1f4]
0297 mov word ptr es:[0x72ae], ax
029b mov dx, ax
029d mov ax, cx
029f mov bx, dx
02a1 imul word ptr [0xcc80] ; _editWidth
02a5 add bx, ax
02a7 mov word ptr es:[0x72b2], bx
02ac push 2
02ae push es
02af push 0x72ae
02b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 693, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
02b7 add sp, 6
02ba mov word ptr [0x1992], 1 ; _mapCursorState
02c0 nop 
02c1 push cs
02c2 call 0x8e4e ; _clip_Pop
02c5 pop si
02c6 leave 
02c7 retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MapToYard(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern unsigned int near mapBuf;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int far mapBuf;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int far mapBuf;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near updateRgn;` — src/recovered/wf_PaintStuff-4a441706dd.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AllocateMapBuffer', 'offset': 52462, 'source': 'src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c', 'size': 79}
- {'symbol': '_DrawMap', 'offset': 52542, 'source': None, 'size': 264}
- {'symbol': '_DrawMapSpider', 'offset': 53518, 'source': None, 'size': 280}
- {'symbol': '_DrawMapFoot', 'offset': 53798, 'source': None, 'size': 484}

# Recovery task _MapAreaEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 514 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov ax, 0x8110
000c mov <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000f mov word ptr [bp - 0xc], ax
0012 mov word ptr [bp - 0xa], cx
0015 push cx
0016 push ax
0017 mov ax, si
0019 mov dx, word ptr [bp + 8]
001c add ax, 8
001f push dx
0020 push ax
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PointInRect
0026 add sp, 8
0029 or ax, ax
002b jne 0xe130
002d jmp 0xe2fe
0030 mov word ptr [bp - 8], 0x8000
0035 push 0x10
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
003c test ah, 0x80
003f jne 0xe144
0041 jmp 0xe1ea
0044 mov es, word ptr [bp + 8]
0047 mov ax, word ptr es:[si + 8]
004b les bx, ptr [bp - 0xc]
004e sub ax, word ptr es:[bx]
0051 mov es, word ptr [0xc21e]
0055 cdq 
0056 idiv word ptr es:[0x807c]
005b mov word ptr [bp - 2], ax
005e mov es, word ptr [bp + 8]
0061 mov ax, word ptr es:[si + 0xa]
0065 mov es, word ptr [0xc220]
0069 sub ax, word ptr es:[0x8112]
006e mov es, word ptr [0xc222]
0072 cdq 
0073 idiv word ptr es:[0x8096]
0078 mov word ptr [bp - 4], ax
007b mov bx, word ptr [0xcc76] ; _MapPlane
007f cmp bx, 1
0082 jle 0xe19b
0084 cmp bx, 4
0087 jge 0xe19b
0089 sub word ptr [bp - 2], 0x20
008d jns 0xe192
008f jmp 0xe2fe
0092 cmp word ptr [bp - 2], 0x40
0096 jl 0xe19b
0098 jmp 0xe2fe
009b mov ax, word ptr [bp - 2]
009e mov es, word ptr [0xc224]
00a2 sub ax, word ptr es:[0x7d2e]
00a7 imul word ptr [0x143a] ; _tileWidth
00ab mov es, word ptr [0xc226]
00af add ax, word ptr es:[0x9b08]
00b4 mov es, word ptr [bp + 8]
00b7 mov word ptr es:[si + 8], ax
00bb mov ax, word ptr [bp - 4]
00be mov es, word ptr [0xc224]
00c2 sub ax, word ptr es:[0x7d30]
00c7 imul word ptr [0x143c] ; _tileHeight
00cb mov es, word ptr [0xc226]
00cf add ax, word ptr es:[0x9b0a]
00d4 mov es, word ptr [bp + 8]
00d7 mov word ptr es:[si + 0xa], ax
00db push es
00dc push si
00dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 224, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _processEdit
00e2 add sp, 4
00e5 pop si
00e6 pop di
00e7 leave 
00e8 retf 
00e9 nop 
00ea mov ax, word ptr [bp - 8]
00ed mov es, word ptr [bp + 8]
00f0 cmp word ptr es:[si + 8], ax
00f4 jne 0xe202
00f6 mov ax, word ptr [bp - 6]
00f9 cmp word ptr es:[si + 0xa], ax
00fd jne 0xe202
00ff jmp 0xe2a8
0102 mov ax, word ptr es:[si + 8]
0106 mov dx, word ptr es:[si + 0xa]
010a mov word ptr [bp - 8], ax
010d mov word ptr [bp - 6], dx
0110 les bx, ptr [bp - 0xc]
0113 sub ax, word ptr es:[bx]
0116 mov es, word ptr [0xc21e]
011a cdq 
011b idiv word ptr es:[0x807c]
0120 mov di, ax
0122 mov es, word ptr [0xc228]
0126 mov ax, word ptr es:[0x78ba]
012a mov word ptr [bp - 0xe], ax
012d cmp ax, 0x40
0130 jne 0xe235
0132 sub di, 0x20
0135 mov es, word ptr [bp + 8]
0138 mov ax, word ptr es:[si + 0xa]
013c mov es, word ptr [0xc220]
0140 sub ax, word ptr es:[0x8112]
0145 mov es, word ptr [0xc222]
0149 cdq 
014a idiv word ptr es:[0x8096]
014f mov word ptr [bp - 4], ax
0152 or di, di
0154 jl 0xe2a8
0156 cmp word ptr [bp - 0xe], di
0159 jle 0xe2a8
015b push word ptr [0xbca8]
015f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 354, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0164 add sp, 2
0167 nop 
0168 push cs
0169 call 0xc70c ; _EraseMapCursor
016c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 367, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0171 push word ptr [bp - 4]
0174 push di
0175 nop 
0176 push cs
0177 call 0x11620
017a add sp, 4
017d or ax, ax
017f je 0xe292
0181 mov es, word ptr [0xc22a]
0185 cmp word ptr es:[0x85f2], 0
018b je 0xe292
018d nop 
018e push cs
018f call 0x111e0
0192 push word ptr [0xbca8]
0196 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 409, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
019b add sp, 2
019e nop 
019f push cs
01a0 call 0xc652 ; _DrawMapCursor
01a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 422, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01a8 mov es, word ptr [bp + 8]
01ab test byte ptr es:[si + 7], 0x60
01b0 jne 0xe2e4
01b2 mov ax, si
01b4 mov dx, es
01b6 add ax, 8
01b9 push dx
01ba push ax
01bb mov di, ax
01bd mov word ptr [bp - 0x10], dx
01c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 451, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GetMousePos
01c5 add sp, 4
01c8 push word ptr [0xbca8]
01cc push word ptr [bp - 0x10]
01cf push di
01d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 465, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
01d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 472, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myButton
01da or ax, ax
01dc je 0xe2e1
01de jmp 0xe1ea
01e1 jmp 0xe2ee
01e3 nop 
01e4 nop 
01e5 push cs
01e6 call 0x10e2c
01e9 pop si
01ea pop di
01eb leave 
01ec retf 
01ed nop 
01ee mov es, word ptr [0xc22a]
01f2 cmp word ptr es:[0x85f2], ax
01f7 jne 0xe2fe
01f9 nop 
01fa push cs
01fb call 0x111e0
01fe pop si
01ff pop di
0200 leave 
0201 retf 
```

## Known declaration examples

- `extern void far DrawMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far GetMousePos(struct CursorPoint far *point);` — src/recovered/win_IsCursorInObj.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/wf_win_IsPointInObj-538ab6cada.c
- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far processEdit(struct EditEvent far *event);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near tileHeight;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MapToolsMenu', 'offset': 56350, 'source': None, 'size': 600}
- {'symbol': '_RibbonToolsMenu', 'offset': 56950, 'source': None, 'size': 649}
- {'symbol': '_Mini_MakeTable', 'offset': 58114, 'source': 'src/recovered/wf_Mini_MakeTable-a03e1a6138.c', 'size': 114}
- {'symbol': '_OpenMiniMapWin', 'offset': 58228, 'source': None, 'size': 1254}

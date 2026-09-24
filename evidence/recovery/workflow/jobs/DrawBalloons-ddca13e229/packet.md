# Recovery task _DrawBalloons

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 897 bytes.

```asm
0000 enter 0x48, 0
0004 push di
0005 push si
0006 mov ax, word ptr [0x1452] ; _theEditBufPtr
0009 mov dx, word ptr [0x1454]
000d mov word ptr [bp - 0x20], ax
0010 mov word ptr [bp - 0x1e], dx
0013 push 2
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
001a add sp, 2
001d mov word ptr [0xcaca], 0x1f4
0023 xor ax, ax
0025 mov word ptr [bp - 0x18], ax
0028 mov word ptr [bp - 0x22], ax
002b mov bx, 0x9fd0
002e mov es, word ptr [0xbfc8]
0032 mov word ptr [bp - 0x34], bx
0035 mov word ptr [bp - 0x32], es
0038 cmp word ptr es:[bx], ax
003b jg 0x57ea
003d jmp 0x5b15
0040 mov word ptr [bp - 0x16], ax
0043 mov word ptr [bp - 0x14], ax
0046 mov ax, 0x7d2e
0049 mov <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004c mov word ptr [bp - 0x38], ax
004f mov word ptr [bp - 0x36], cx
0052 mov ax, 0x7d30
0055 mov word ptr [bp - 0x3c], ax
0058 mov word ptr [bp - 0x3a], cx
005b cmp word ptr [bp - 0x22], 1
005f jl 0x580e
0061 jmp 0x5b15
0064 mov bx, word ptr [bp - 0x14]
0067 add bx, 0x7c24
006b mov es, word ptr [0xbfd0]
006f mov word ptr [bp - 0x40], bx
0072 mov word ptr [bp - 0x3e], es
0075 mov ax, word ptr es:[bx + 2]
0079 or ax, word ptr es:[bx]
007c jne 0x582b
007e jmp 0x5b15
0081 mov es, word ptr [0xbfcc]
0085 mov bx, word ptr [bp - 0x16]
0088 mov ax, word ptr es:[bx + 0x7d68]
008d mov word ptr [bp - 2], ax
0090 mov es, word ptr [0xbfca]
0094 mov bx, word ptr [bp - 0x14]
0097 mov ax, word ptr es:[bx - 0x7f2a]
009c mov dx, word ptr es:[bx - 0x7f28]
00a1 mov word ptr [bp - 0x28], ax
00a4 mov word ptr [bp - 0x26], dx
00a7 cdq 
00a8 idiv word ptr [0x143a] ; _tileWidth
00ac mov bx, ax
00ae mov ax, word ptr [bp - 0x26]
00b1 cdq 
00b2 idiv word ptr [0x143c] ; _tileHeight
00b6 mov di, ax
00b8 mov ax, word ptr [0xcc76] ; _MapPlane
00bb cmp word ptr [bp - 2], ax
00be jne 0x5898
00c0 les si, ptr [bp - 0x38]
00c3 cmp word ptr es:[si], bx
00c6 jg 0x5898
00c8 mov ax, word ptr es:[si]
00cb add ax, word ptr [0xcc80] ; _editWidth
00cf cmp ax, bx
00d1 jle 0x5898
00d3 lea ax, [di - 3]
00d6 les bx, ptr [bp - 0x3c]
00d9 cmp word ptr es:[bx], ax
00dc jg 0x5898
00de mov ax, word ptr es:[bx]
00e1 add ax, word ptr [0xcd7a] ; _editHeight
00e5 cmp ax, di
00e7 jle 0x5898
00e9 mov dx, 1
00ec jmp 0x589a
00ee xor dx, dx
00f0 or dx, dx
00f2 jne 0x58a1
00f4 jmp 0x5afc
00f7 inc word ptr [bp - 0x22]
00fa push 0
00fc les bx, ptr [bp - 0x40]
00ff push word ptr es:[bx + 2]
0103 push word ptr es:[bx]
0106 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MakeBalloon
010b add sp, 6
010e mov word ptr [bp - 0x1c], ax
0111 mov si, word ptr [bp - 0x16]
0114 mov word ptr [bp + si - 0x1a], ax
0117 push ax
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
011d add sp, 2
0120 mov si, ax
0122 mov word ptr [bp - 8], dx
0125 add word ptr [bp - 0x28], 4
0129 mov es, dx
012b mov ax, word ptr es:[si + 0xa]
012f add ax, 4
0132 sub word ptr [bp - 0x26], ax
0135 mov ax, word ptr [bp - 0x26]
0138 mov di, ax
013a mov cx, word ptr [bp - 0x28]
013d mov word ptr [bp - 0x10], cx
0140 les bx, ptr [bp - 0x38]
0143 mov ax, word ptr es:[bx]
0146 imul word ptr [0x143a] ; _tileWidth
014a sub word ptr [bp - 0x28], ax
014d les bx, ptr [bp - 0x3c]
0150 mov ax, word ptr es:[bx]
0153 imul word ptr [0x143c] ; _tileHeight
0157 sub ax, di
0159 neg ax
015b mov word ptr [bp - 0x26], ax
015e test byte ptr [0xcc7e], 1 ; _displayType
0163 je 0x5912
0165 jmp 0x599c
0168 mov es, word ptr [bp - 8]
016b test byte ptr es:[si + 2], 0x80
0170 jne 0x595c
0172 mov ax, word ptr [0x143c] ; _tileHeight
0175 imul word ptr [0xcd7a] ; _editHeight
0179 mov cx, word ptr es:[si + 0xa]
017d mov dx, ax
017f sub ax, cx
0181 sub ax, word ptr [bp - 0x26]
0184 push ax
0185 push word ptr [bp - 0x28]
0188 push word ptr es:[si + 8]
018c push cx
018d mov ax, word ptr [0x143a] ; _tileWidth
0190 mov cx, dx
0192 imul word ptr [0xcc80] ; _editWidth
0196 push ax
0197 push cx
0198 mov ax, si
019a mov dx, es
019c add ax, 0xc
019f adc dx, 0
01a2 push dx
01a3 push ax
01a4 push word ptr [bp - 0x1e]
01a7 push word ptr [bp - 0x20]
01aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 429, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap2
01af jmp 0x59dc
01b2 mov ax, word ptr [0x143c] ; _tileHeight
01b5 imul word ptr [0xcd7a] ; _editHeight
01b9 mov cx, word ptr es:[si + 0xa]
01bd mov dx, ax
01bf sub ax, cx
01c1 sub ax, word ptr [bp - 0x26]
01c4 push ax
01c5 push word ptr [bp - 0x28]
01c8 push word ptr es:[si + 8]
01cc push cx
01cd mov ax, word ptr [0x143a] ; _tileWidth
01d0 mov cx, dx
01d2 imul word ptr [0xcc80] ; _editWidth
01d6 push ax
01d7 push cx
01d8 mov ax, si
01da mov dx, es
01dc add ax, 0xc
01df adc dx, 0
01e2 push dx
01e3 push ax
01e4 push word ptr [bp - 0x1e]
01e7 push word ptr [bp - 0x20]
01ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 493, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _CopyMaskBitmap2
01ef jmp 0x59dc
01f1 nop 
01f2 mov ax, word ptr [0x143c] ; _tileHeight
01f5 imul word ptr [0xcd7a] ; _editHeight
01f9 mov es, word ptr [bp - 8]
01fc mov cx, word ptr es:[si + 0xa]
0200 mov dx, ax
0202 sub ax, cx
0204 sub ax, word ptr [bp - 0x26]
0207 push ax
0208 push word ptr [bp - 0x28]
020b push word ptr es:[si + 8]
020f push cx
0210 mov ax, word ptr [0x143a] ; _tileWidth
0213 mov cx, dx
0215 imul word ptr [0xcc80] ; _editWidth
0219 push ax
021a push cx
021b mov ax, si
021d mov dx, es
021f add ax, 0xc
0222 adc dx, 0
0225 push dx
0226 push ax
0227 push word ptr [bp - 0x1e]
022a push word ptr [bp - 0x20]
022d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 560, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _CopyMonoMaskBitmap
0232 add sp, 0x14
0235 mov es, word ptr [0xbf90]
0239 mov ax, word ptr es:[0x9b08]
023d add ax, word ptr [bp - 0x28]
0240 mov word ptr [bp - 0x30], ax
0243 mov cx, word ptr es:[0x9b0a]
0248 add cx, word ptr [bp - 0x26]
024b mov word ptr [bp - 0x2e], cx
024e mov es, word ptr [bp - 8]
0251 add ax, word ptr es:[si + 8]
0255 mov word ptr [bp - 0x2c], ax
0258 add cx, word ptr es:[si + 0xa]
025c mov word ptr [bp - 0x2a], cx
025f push word ptr [0xbca6] ; _win_hwnd
0263 lea ax, [bp - 0x30]
0266 push ss
0267 push ax
0268 push 0
026a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 619, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
026f mov word ptr [bp - 0x24], 0
0274 mov ax, di
0276 cdq 
0277 idiv word ptr [0x143c] ; _tileHeight
027b les bx, ptr [bp - 0x3c]
027e sub ax, word ptr es:[bx]
0281 mov word ptr [bp - 0x12], ax
0284 mov es, word ptr [bp - 8]
0287 mov ax, word ptr es:[si + 0xa]
028b mov cx, word ptr [0x143c] ; _tileHeight
028f add ax, cx
0291 dec ax
0292 sub dx, dx
0294 div cx
0296 or ax, ax
0298 jge 0x5a47
029a jmp 0x5ae6
029d mov ax, word ptr [bp - 0x12]
02a0 imul word ptr [0xcc80] ; _editWidth
02a4 mov word ptr [bp - 6], ax
02a7 mov bx, word ptr [0x143a] ; _tileWidth
02ab mov ax, word ptr [bp - 0x10]
02ae cdq 
02af idiv bx
02b1 mov word ptr [bp - 0x42], ax
02b4 mov ax, word ptr es:[si + 8]
02b8 add ax, bx
02ba dec ax
02bb sub dx, dx
02bd div bx
02bf mov cx, ax
02c1 mov word ptr [bp - 0x44], ax
02c4 mov ax, word ptr [0xcd7a] ; _editHeight
02c7 imul word ptr [0xcc80] ; _editWidth
02cb mov word ptr [bp - 0x46], ax
02ce inc cx
02cf mov word ptr [bp - 0x48], cx
02d2 mov ax, word ptr es:[si + 0xa]
02d6 mov cx, word ptr [0x143c] ; _tileHeight
02da add ax, cx
02dc dec ax
02dd sub dx, dx
02df div cx
02e1 inc ax
02e2 mov word ptr [bp - 0xc], ax
02e5 mov word ptr [bp - 0xa], si
02e8 mov ax, word ptr [bp - 0x42]
02eb les si, ptr [bp - 0x38]
02ee sub ax, word ptr es:[si]
02f1 add ax, word ptr [bp - 6]
02f4 mov word ptr [bp - 2], ax
02f7 mov word ptr [bp - 0xe], 0
02fc cmp word ptr [bp - 0x44], 0
0300 jl 0x5ad5
0302 mov ax, word ptr [bp - 0x48]
0305 mov word ptr [bp - 4], ax
0308 mov bx, word ptr [bp - 2]
030b mov di, ax
030d mov es, word ptr [0x1444]
0311 or bx, bx
0313 jl 0x5ad1
0315 cmp word ptr [bp - 0x46], bx
0318 jle 0x5ad1
031a mov si, bx
031c shl si, 1
031e add si, word ptr [0x1442]
0322 mov word ptr es:[si], 0xffff
0327 inc bx
0328 dec di
0329 jne 0x5abb
032b mov ax, word ptr [0xcc80] ; _editWidth
032e add word ptr [bp - 6], ax
0331 dec word ptr [bp - 0xc]
0334 je 0x5ae6
0336 mov bx, word ptr [0x143a] ; _tileWidth
033a jmp 0x5a92
033c push word ptr [bp - 0x1c]
033f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 834, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0344 add sp, 2
0347 push word ptr [bp - 0x1c]
034a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 845, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
034f add sp, 2
0352 add word ptr [bp - 0x16], 2
0356 add word ptr [bp - 0x14], 4
035a inc word ptr [bp - 0x18]
035d mov ax, word ptr [bp - 0x18]
0360 les bx, ptr [bp - 0x34]
0363 cmp word ptr es:[bx], ax
0366 jle 0x5b15
0368 jmp 0x5805
036b push 0
036d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 880, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0372 add sp, 2
0375 les bx, ptr [bp - 0x34]
0378 mov word ptr es:[bx], 0
037d pop si
037e pop di
037f leave 
0380 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near tileHeight;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EditMsgBalloon', 'offset': 22322, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 114}
- {'symbol': '_PreDrawBalloons', 'offset': 22436, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 6}
- {'symbol': '_DoEditScrollLine', 'offset': 23340, 'source': None, 'size': 322}
- {'symbol': '_DoEditScroll', 'offset': 23662, 'source': None, 'size': 1047}

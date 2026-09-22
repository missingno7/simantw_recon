# Recovery task _Mini_DrawMapI

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 811 bytes.

```asm
0000 enter 0x2a, 0
0004 push di
0005 push si
0006 mov ax, 0x7ef6
0009 mov <resolved loader operand; see bindings> ; [{'operand_offset': 10, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000c mov word ptr [bp - 0x16], ax
000f mov word ptr [bp - 0x14], cx
0012 push cx
0013 push ax
0014 push 0x1401
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
001c add sp, 6
001f mov bx, 0x78ba
0022 mov es, word ptr [0xc200]
0026 mov word ptr [bp - 0x1a], bx
0029 mov word ptr [bp - 0x18], es
002c mov word ptr es:[bx], 0x80
0031 mov bx, 0xa0b0
0034 mov es, word ptr [0xc20e]
0038 mov word ptr [bp - 0x1e], bx
003b mov word ptr [bp - 0x1c], es
003e mov word ptr es:[bx], 0
0043 cmp word ptr [0x199a], 0 ; _mapMem
0048 jne 0xd4f4
004a push ds
004b push 0x1a09
004e push 1
0050 push 0
0052 push 0x400
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
005a add sp, 0xa
005d mov es, word ptr [0xc210]
0061 mov word ptr es:[0x7d32], ax
0065 push ds
0066 push 0x1a1a
0069 push 1
006b push 0
006d push 0x2000
0070 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 115, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0075 add sp, 0xa
0078 mov es, word ptr [0xc1f8]
007c mov word ptr es:[0xa0de], ax
0080 cmp word ptr [0xcc76], 2 ; _MapPlane
0085 jge 0xd4fe
0087 call 0xc854
008a mov dx, word ptr [0xcc76] ; _MapPlane
008e cmp dx, 1
0091 jle 0xd52c
0093 cmp dx, 4
0096 jge 0xd52c
0098 call 0xca66
009b les bx, ptr [bp - 0x1a]
009e mov word ptr es:[bx], 0x40
00a3 mov es, word ptr [0xc212]
00a7 mov ax, word ptr es:[0x9b88]
00ab shl ax, 5
00ae les bx, ptr [bp - 0x1e]
00b1 mov word ptr es:[bx], ax
00b4 mov dx, word ptr [0xcc76] ; _MapPlane
00b8 cmp dx, 1
00bb jg 0xd534
00bd jmp 0xd5b4
00c0 cmp dx, 4
00c3 jge 0xd5b4
00c5 push word ptr [0xbcce]
00c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00ce add sp, 2
00d1 push 0xf
00d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00d8 add sp, 2
00db push ax
00dc mov es, word ptr [0xc214]
00e0 push word ptr es:[0x7efc]
00e5 les bx, ptr [bp - 0x1e]
00e8 mov ax, word ptr es:[bx]
00eb les si, ptr [bp - 0x16]
00ee add ax, word ptr es:[si]
00f1 push ax
00f2 mov es, word ptr [0xc214]
00f6 push word ptr es:[0x7ef8]
00fb les bx, ptr [bp - 0x16]
00fe push word ptr es:[bx]
0101 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 260, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
0106 add sp, 0xa
0109 push 0xf
010b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0110 add sp, 2
0113 push ax
0114 mov es, word ptr [0xc214]
0118 push word ptr es:[0x7efc]
011d push word ptr es:[0x7efa]
0122 push word ptr es:[0x7ef8]
0127 mov ax, word ptr es:[0x7efa]
012b les bx, ptr [bp - 0x1e]
012e sub ax, word ptr es:[bx]
0131 dec ax
0132 push ax
0133 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 310, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
0138 add sp, 0xa
013b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 318, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0140 mov bx, 0xa0de
0143 mov es, word ptr [0xc1f8]
0147 mov word ptr [bp - 0x22], bx
014a mov word ptr [bp - 0x20], es
014d push word ptr es:[bx]
0150 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 339, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0155 add sp, 2
0158 mov word ptr [bp - 4], ax
015b mov word ptr [bp - 2], dx
015e mov bx, 0x7d32
0161 mov es, word ptr [0xc210]
0165 mov word ptr [bp - 0x26], bx
0168 mov word ptr [bp - 0x24], es
016b push word ptr es:[bx]
016e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 369, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0173 add sp, 2
0176 mov es, word ptr [0xc214]
017a mov di, word ptr es:[0x7ef8]
017f push ds
0180 push 0x1a2f
0183 push 1
0185 mov al, byte ptr [0xcc7e] ; _displayType
0188 and al, 1
018a cmp al, 1
018c sbb ax, ax
018e and ax, 3
0191 inc ax
0192 push ax
0193 mov bx, 0x9be2
0196 mov es, word ptr [0xc216]
019a mov word ptr [bp - 0x2a], bx
019d mov word ptr [bp - 0x28], es
01a0 mov ax, word ptr es:[bx]
01a3 shl ax, 6
01a6 push ax
01a7 mov es, word ptr [0xc212]
01ab mov ax, word ptr es:[0x9b88]
01af les bx, ptr [bp - 0x1a]
01b2 imul word ptr es:[bx]
01b5 push ax
01b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 441, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _BitmapImageSize
01bb add sp, 6
01be add ax, 0x20
01c1 adc dx, 0
01c4 push dx
01c5 push ax
01c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 457, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
01cb add sp, 0xa
01ce mov word ptr [bp - 0xe], ax
01d1 push ax
01d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
01d7 add sp, 2
01da mov word ptr [bp - 0xc], ax
01dd mov word ptr [bp - 0xa], dx
01e0 mov al, byte ptr [0xcc7e] ; _displayType
01e3 and al, 1
01e5 cmp al, 1
01e7 sbb ax, ax
01e9 and ax, 3
01ec inc ax
01ed mov es, word ptr [0xc212]
01f1 imul word ptr es:[0x9b88]
01f6 les bx, ptr [bp - 0x1a]
01f9 imul word ptr es:[bx]
01fc add ax, 0x1f
01ff cdq 
0200 and dx, 0x1f
0203 add ax, dx
0205 sar ax, 5
0208 shl ax, 2
020b mov word ptr [bp - 6], ax
020e xor si, si
0210 push di
0211 mov cx, 0x3f
0214 sub cx, si
0216 les bx, ptr [bp - 0x2a]
0219 mov ax, word ptr es:[bx]
021c imul cx
021e imul word ptr [bp - 6]
0221 add ax, word ptr [bp - 0xc]
0224 mov dx, word ptr [bp - 0xa]
0227 push dx
0228 push ax
0229 les bx, ptr [bp - 0x1a]
022c mov ax, word ptr es:[bx]
022f imul si
0231 add ax, word ptr [bp - 4]
0234 mov dx, word ptr [bp - 2]
0237 push dx
0238 push ax
0239 nop 
023a push cs
023b call 0xe302 ; _Mini_MakeTable
023e add sp, 0xa
0241 les bx, ptr [bp - 0x2a]
0244 add di, word ptr es:[bx]
0247 inc si
0248 cmp si, 0x40
024b jl 0xd684
024d les bx, ptr [bp - 0x1e]
0250 mov ax, word ptr es:[bx]
0253 mov word ptr [bp - 0x12], ax
0256 mov word ptr [bp - 0x10], 0
025b push word ptr [0xbcce]
025f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 610, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0264 add sp, 2
0267 test byte ptr [0xcc7e], 1 ; _displayType
026c jne 0xd714
026e mov si, word ptr [bp - 0xc]
0271 push 0
0273 push word ptr [bp - 0xa]
0276 push si
0277 les bx, ptr [bp - 0x2a]
027a mov ax, word ptr es:[bx]
027d shl ax, 6
0280 push ax
0281 mov es, word ptr [0xc212]
0285 mov ax, word ptr es:[0x9b88]
0289 les bx, ptr [bp - 0x1a]
028c imul word ptr es:[bx]
028f push ax
0290 push word ptr [bp - 0x10]
0293 push word ptr [bp - 0x12]
0296 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 665, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastBitmap
029b add sp, 0xe
029e jmp 0xd742
02a0 mov si, word ptr [bp - 0xc]
02a3 push word ptr [bp - 0xa]
02a6 push si
02a7 les bx, ptr [bp - 0x2a]
02aa mov ax, word ptr es:[bx]
02ad shl ax, 6
02b0 push ax
02b1 mov es, word ptr [0xc212]
02b5 mov ax, word ptr es:[0x9b88]
02b9 les bx, ptr [bp - 0x1a]
02bc imul word ptr es:[bx]
02bf push ax
02c0 push word ptr [bp - 0x10]
02c3 push word ptr [bp - 0x12]
02c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 713, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastMonoBitmap
02cb add sp, 0xc
02ce mov di, word ptr [bp - 0xe]
02d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 724, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
02d6 push di
02d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 730, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
02dc add sp, 2
02df push di
02e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 739, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
02e5 add sp, 2
02e8 les bx, ptr [bp - 0x26]
02eb push word ptr es:[bx]
02ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 753, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
02f3 add sp, 2
02f6 les bx, ptr [bp - 0x22]
02f9 push word ptr es:[bx]
02fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 767, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0301 add sp, 2
0304 cmp word ptr [0x199a], 0 ; _mapMem
0309 jne 0xd79b
030b les bx, ptr [bp - 0x26]
030e push word ptr es:[bx]
0311 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 788, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0316 add sp, 2
0319 les bx, ptr [bp - 0x22]
031c push word ptr es:[bx]
031f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 802, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0324 add sp, 2
0327 pop si
0328 pop di
0329 leave 
032a retf 
```

## Known declaration examples

- `extern long far BitmapImageSize(int width, int height, int depth);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern long far BitmapImageSize(int width, int height, int depth);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_InitMapFunctions-70fb457ea5.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawMapFoot', 'offset': 53798, 'source': None, 'size': 484}
- {'symbol': '_MapToYellowAnt', 'offset': 54282, 'source': None, 'size': 105}
- {'symbol': '_MapToolsMenu', 'offset': 56350, 'source': None, 'size': 600}
- {'symbol': '_RibbonToolsMenu', 'offset': 56950, 'source': None, 'size': 649}

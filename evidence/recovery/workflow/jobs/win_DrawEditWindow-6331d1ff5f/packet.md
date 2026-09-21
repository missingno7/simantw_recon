# Recovery task _win_DrawEditWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 195 bytes.

```asm
0000 enter 0x10, 0
0004 push si
0005 test byte ptr [bp + 6], 2
0009 jne 0x14fe
000b jmp 0x15b0
000e cmp word ptr [0x1450], 0 ; _editBuf
0013 jne 0x1508
0015 jmp 0x159c
0018 cmp word ptr [0xcd84], 0 ; _updateRgn
001d je 0x1522
001f push word ptr [0xcd84] ; _updateRgn
0023 push <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0026 push 0x9b08
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 181}}]
002e or ax, ax
0030 je 0x159c
0032 push word ptr [0x1450] ; _editBuf
0036 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
003b add sp, 2
003e mov si, ax
0040 mov word ptr [bp - 2], dx
0043 mov es, word ptr [0xbf90]
0047 mov ax, word ptr es:[0x9b08]
004b mov word ptr [bp - 8], ax
004e mov ax, word ptr es:[0x9b0a]
0052 mov word ptr [bp - 6], ax
0055 test byte ptr [0xcc7e], 1 ; _displayType
005a jne 0x1570
005c push 0
005e push dx
005f push si
0060 mov ax, word ptr [0x143c] ; _tileHeight
0063 imul word ptr [0xcd7a] ; _editHeight
0067 push ax
0068 mov ax, word ptr [0x143a] ; _tileWidth
006b imul word ptr [0xcc80] ; _editWidth
006f push ax
0070 push word ptr [bp - 6]
0073 push word ptr [bp - 8]
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastBitmap
007b add sp, 0xe
007e jmp 0x1590
0080 push dx
0081 push si
0082 mov ax, word ptr [0x143c] ; _tileHeight
0085 imul word ptr [0xcd7a] ; _editHeight
0089 push ax
008a mov ax, word ptr [0x143a] ; _tileWidth
008d imul word ptr [0xcc80] ; _editWidth
0091 push ax
0092 push word ptr [bp - 6]
0095 push word ptr [bp - 8]
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastMonoBitmap
009d add sp, 0xc
00a0 push word ptr [0x1450] ; _editBuf
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00a9 add sp, 2
00ac nop 
00ad push cs
00ae call 0x198a ; _DrawEditGraphs
00b1 lea ax, [bp - 0x10]
00b4 push ss
00b5 push ax
00b6 push 7
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
00bd add sp, 6
00c0 pop si
00c1 leave 
00c2 retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editHeight;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateEditIfBufInvalid', 'offset': 5276, 'source': None, 'size': 82}
- {'symbol': '_DrawEdit', 'offset': 5358, 'source': 'src/recovered/DrawEdit.c', 'size': 1}
- {'symbol': '_BoundEditPosition', 'offset': 5556, 'source': None, 'size': 107}
- {'symbol': '_CenterEdit', 'offset': 5664, 'source': None, 'size': 180}

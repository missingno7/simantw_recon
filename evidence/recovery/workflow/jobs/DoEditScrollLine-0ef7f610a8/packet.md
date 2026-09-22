# Recovery task _DoEditScrollLine

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 322 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 test byte ptr [0xcc7e], 1 ; _displayType
000a je 0x5b3b
000c jmp 0x5c3c
000f push word ptr [0x1450] ; _editBuf
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0018 add sp, 2
001b mov si, ax
001d mov al, byte ptr [bp + 6]
0020 cwde 
0021 cmp ax, 0x75
0024 jne 0x5b55
0026 jmp 0x5be8
0029 jbe 0x5b5a
002b jmp 0x5c12
002e sub al, 0x64
0030 je 0x5b6a
0032 sub al, 8
0034 je 0x5b94
0036 sub al, 6
0038 je 0x5bbe
003a jmp 0x5c12
003d nop 
003e push word ptr [0x143a] ; _tileWidth
0042 push word ptr [0x143c] ; _tileHeight
0046 push word ptr [0xcc80] ; _editWidth
004a push word ptr [0xcd7a] ; _editHeight
004e push word ptr [0x1444]
0052 push word ptr [0x1442]
0056 push word ptr [0x1440]
005a push word ptr [0x143e]
005e push dx
005f push si
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollDownColor
0065 jmp 0x5c0f
0067 nop 
0068 push word ptr [0x143a] ; _tileWidth
006c push word ptr [0x143c] ; _tileHeight
0070 push word ptr [0xcc80] ; _editWidth
0074 push word ptr [0xcd7a] ; _editHeight
0078 push word ptr [0x1444]
007c push word ptr [0x1442]
0080 push word ptr [0x1440]
0084 push word ptr [0x143e]
0088 push dx
0089 push si
008a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollLeftColor
008f jmp 0x5c0f
0091 nop 
0092 push word ptr [0x143a] ; _tileWidth
0096 push word ptr [0x143c] ; _tileHeight
009a push word ptr [0xcc80] ; _editWidth
009e push word ptr [0xcd7a] ; _editHeight
00a2 push word ptr [0x1444]
00a6 push word ptr [0x1442]
00aa push word ptr [0x1440]
00ae push word ptr [0x143e]
00b2 push dx
00b3 push si
00b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollRightColor
00b9 jmp 0x5c0f
00bb nop 
00bc push word ptr [0x143a] ; _tileWidth
00c0 push word ptr [0x143c] ; _tileHeight
00c4 push word ptr [0xcc80] ; _editWidth
00c8 push word ptr [0xcd7a] ; _editHeight
00cc push word ptr [0x1444]
00d0 push word ptr [0x1442]
00d4 push word ptr [0x1440]
00d8 push word ptr [0x143e]
00dc push dx
00dd push si
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollUpColor
00e3 add sp, 0x14
00e6 push word ptr [0x1450] ; _editBuf
00ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 237, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00ef add sp, 2
00f2 call 0x16d4
00f5 push word ptr [0xbca6] ; _win_hwnd
00f9 push 0
00fb push 0
00fd push 0
00ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0104 push word ptr [0xbca6] ; _win_hwnd
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
010d jmp 0x5c41
010f nop 
0110 nop 
0111 push cs
0112 call 0x11e0 ; _UpdateEdit
0115 push 0x100
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
011d add sp, 2
0120 or ax, ax
0122 je 0x5c6b
0124 push word ptr [0xbca8]
0128 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 299, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
012d add sp, 2
0130 nop 
0131 push cs
0132 call 0xc70c ; _EraseMapCursor
0135 nop 
0136 push cs
0137 call 0xc652 ; _DrawMapCursor
013a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 317, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
013f pop si
0140 leave 
0141 retf 
```

## Known declaration examples

- `extern void far DrawMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PreDrawBalloons', 'offset': 22436, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 6}
- {'symbol': '_DrawBalloons', 'offset': 22442, 'source': None, 'size': 897}
- {'symbol': '_DoEditScroll', 'offset': 23662, 'source': None, 'size': 1047}
- {'symbol': '_ResetEditScrollRange', 'offset': 24710, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 230}

# Recovery task _ScrollEditWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 165 bytes.

```asm
0000 enter 8, 0
0004 push si
0005 push 0
0007 push 0
0009 push 1
000b push 1
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 14, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
0012 mov si, ax
0014 mov es, word ptr [0xbf90]
0018 mov ax, word ptr es:[0x9b08]
001c mov word ptr [bp - 8], ax
001f mov cx, word ptr es:[0x9b0a]
0024 mov word ptr [bp - 6], cx
0027 mov dx, ax
0029 mov ax, word ptr [0x143a] ; _tileWidth
002c mov bx, dx
002e imul word ptr [0xcc80] ; _editWidth
0032 add bx, ax
0034 mov word ptr [bp - 4], bx
0037 mov ax, word ptr [0x143c] ; _tileHeight
003a imul word ptr [0xcd7a] ; _editHeight
003e add cx, ax
0040 mov word ptr [bp - 2], cx
0043 push word ptr [0xbca6] ; _win_hwnd
0047 mov ax, word ptr [bp + 6]
004a mov es, word ptr [0xbf92]
004e sub ax, word ptr es:[0x7d2e]
0053 imul word ptr [0x143a] ; _tileWidth
0057 push ax
0058 mov ax, word ptr [bp + 8]
005b sub ax, word ptr es:[0x7d30]
0060 imul word ptr [0x143c] ; _tileHeight
0064 push ax
0065 lea ax, [bp - 8]
0068 push ss
0069 push ax
006a push ss
006b push ax
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 61}}]
0071 push word ptr [0xbca6] ; _win_hwnd
0075 push si
0076 push 0
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 237}}]
007d push word ptr [0xbca6] ; _win_hwnd
0081 push si
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 128}}]
0087 push word ptr [0xbca6] ; _win_hwnd
008b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0090 push word ptr [0xbca6] ; _win_hwnd
0094 push si
0095 push 0
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 126}}]
009c push si
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
00a2 pop si
00a3 leave 
00a4 retf 
```

## Known declaration examples

- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd;` — src/recovered/InvalidUpdateEdit.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoEditUpdateDraw', 'offset': 3670, 'source': 'src/recovered/DoEditUpdateDraw.c', 'size': 6}
- {'symbol': '_ScrollEditArrays', 'offset': 3676, 'source': None, 'size': 734}
- {'symbol': '_UpdateEdit', 'offset': 4576, 'source': None, 'size': 694}
- {'symbol': '_UpdateEditWindow', 'offset': 5270, 'source': 'src/recovered/UpdateEditWindow.c', 'size': 6}

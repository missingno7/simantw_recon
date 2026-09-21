# Recovery task _ResetEditScrollRange

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 230 bytes.

```asm
0000 enter 4, 0
0004 cmp word ptr [0xbca6], 0 ; _win_hwnd
0009 jne 0x6094
000b jmp 0x616a
000e mov ax, word ptr [0x14f8]
0011 mov bx, 0x8610
0014 mov es, word ptr [0xc082]
0018 mov word ptr [bp - 4], bx
001b mov word ptr [bp - 2], es
001e cmp word ptr es:[bx], ax
0021 jne 0x60bb
0023 mov ax, word ptr [0xcd7a] ; _editHeight
0026 cmp word ptr [0x14fa], ax
002a jne 0x60bb
002c mov ax, word ptr [0xcc80] ; _editWidth
002f cmp word ptr [0x14fc], ax
0033 je 0x611a
0035 push word ptr [0xbca6] ; _win_hwnd
0039 push 1
003b push 0
003d mov ax, 0x40
0040 sub ax, word ptr [0xcd7a] ; _editHeight
0044 push ax
0045 push 1
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 64}}]
004c les bx, ptr [bp - 4]
004f cmp word ptr es:[bx], 2
0053 je 0x60ee
0055 cmp word ptr es:[bx], 3
0059 je 0x60ee
005b push word ptr [0xbca6] ; _win_hwnd
005f push 0
0061 push 0
0063 mov ax, 0x80
0066 jmp 0x60f9
0068 push word ptr [0xbca6] ; _win_hwnd
006c push 0
006e push 0
0070 mov ax, 0x40
0073 sub ax, word ptr [0xcc80] ; _editWidth
0077 push ax
0078 push 1
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 64}}]
007f les bx, ptr [bp - 4]
0082 mov ax, word ptr es:[bx]
0085 mov word ptr [0x14f8], ax
0088 mov ax, word ptr [0xcd7a] ; _editHeight
008b mov word ptr [0x14fa], ax
008e mov ax, word ptr [0xcc80] ; _editWidth
0091 mov word ptr [0x14fc], ax
0094 push word ptr [0xbca6] ; _win_hwnd
0098 push 0
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 63}}]
009f mov es, word ptr [0xbf92]
00a3 cmp ax, word ptr es:[0x7d2e]
00a8 je 0x6142
00aa push word ptr [0xbca6] ; _win_hwnd
00ae push 0
00b0 push word ptr es:[0x7d2e]
00b5 push 1
00b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
00bc push word ptr [0xbca6] ; _win_hwnd
00c0 push 1
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 63}}]
00c7 mov es, word ptr [0xbf92]
00cb cmp ax, word ptr es:[0x7d30]
00d0 je 0x616a
00d2 push word ptr [0xbca6] ; _win_hwnd
00d6 push 1
00d8 push word ptr es:[0x7d30]
00dd push 1
00df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 224, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
00e4 leave 
00e5 retf 
```

## Known declaration examples

- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editHeight;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd;` — src/recovered/InvalidUpdateEdit.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoEditScrollLine', 'offset': 23340, 'source': None, 'size': 322}
- {'symbol': '_DoEditScroll', 'offset': 23662, 'source': None, 'size': None}
- {'symbol': '_EditScentMenu', 'offset': 26462, 'source': 'src/recovered/wf_EditScentMenu-abd185cb06.c', 'size': 103}
- {'symbol': '_EditToolsMenu', 'offset': 26566, 'source': None, 'size': 506}

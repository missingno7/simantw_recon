# Recovery task _PreDrawSpider

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 337 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbfa4]
000a mov word ptr es:[0x72d8], 0x8000
0011 mov ax, 0x1f4
0014 mov es, word ptr [0xbf94]
0018 mov word ptr es:[0x78a6], ax
001c mov es, word ptr [0xbfa6]
0020 mov word ptr es:[0x9fc4], ax
0024 mov es, word ptr [0xbfa8]
0028 cmp word ptr es:[0x9bd2], 0
002e jne 0x1c4b
0030 jmp 0x1d65
0033 mov es, word ptr [0xbf92]
0037 mov ax, word ptr es:[0x7d2e]
003b mov word ptr [bp - 6], ax
003e imul word ptr [0x143a] ; _tileWidth
0042 mov word ptr [bp - 2], ax
0045 mov ax, word ptr es:[0x7d30]
0049 mov word ptr [bp - 8], ax
004c imul word ptr [0x143c] ; _tileHeight
0050 mov word ptr [bp - 4], ax
0053 mov si, word ptr [0xac7c] ; _SpidX
0057 mov di, word ptr [0xac7e] ; _SpidY
005b cmp byte ptr [0xcc7e], 2 ; _displayType
0060 jne 0x1ca0
0062 mov ax, si
0064 mov cx, si
0066 shl ax, 1
0068 add ax, cx
006a cdq 
006b and dx, 3
006e add ax, dx
0070 sar ax, 2
0073 mov si, ax
0075 mov ax, di
0077 mov cx, di
0079 shl ax, 1
007b add ax, cx
007d cdq 
007e and dx, 3
0081 add ax, dx
0083 sar ax, 2
0086 mov di, ax
0088 cmp word ptr [0xcc76], 1 ; _MapPlane
008d je 0x1cb1
008f cmp word ptr [0xcc76], 0 ; _MapPlane
0094 je 0x1cb1
0096 jmp 0x1d65
0099 cmp word ptr [bp - 2], si
009c jle 0x1cb9
009e jmp 0x1d65
00a1 mov ax, word ptr [0x143a] ; _tileWidth
00a4 imul word ptr [0xcc80] ; _editWidth
00a8 add ax, word ptr [bp - 2]
00ab cmp ax, si
00ad jge 0x1cca
00af jmp 0x1d65
00b2 cmp word ptr [bp - 4], di
00b5 jle 0x1cd2
00b7 jmp 0x1d65
00ba mov ax, word ptr [0x143c] ; _tileHeight
00bd imul word ptr [0xcd7a] ; _editHeight
00c1 add ax, word ptr [bp - 4]
00c4 cmp ax, di
00c6 jge 0x1ce3
00c8 jmp 0x1d65
00cb mov ax, word ptr [0x143a] ; _tileWidth
00ce mov cx, ax
00d0 shl ax, 1
00d2 add ax, cx
00d4 shl ax, 1
00d6 add ax, cx
00d8 mov es, word ptr [0xbfaa]
00dc mov word ptr es:[0x8124], ax
00e0 mov ax, word ptr [0x143c] ; _tileHeight
00e3 mov cx, ax
00e5 shl ax, 1
00e7 add ax, cx
00e9 shl ax, 1
00eb add ax, cx
00ed mov word ptr es:[0x8126], ax
00f1 mov ax, word ptr [0xac7c] ; _SpidX
00f4 cdq 
00f5 and dx, 0xf
00f8 add ax, dx
00fa sar ax, 4
00fd sub ax, word ptr [bp - 6]
0100 sub ax, 3
0103 mov es, word ptr [0xbf94]
0107 mov word ptr es:[0x78a6], ax
010b mov ax, word ptr [0xac7e] ; _SpidY
010e cdq 
010f and dx, 0xf
0112 add ax, dx
0114 sar ax, 4
0117 sub ax, word ptr [bp - 8]
011a sub ax, 3
011d mov es, word ptr [0xbfa6]
0121 mov word ptr es:[0x9fc4], ax
0125 mov es, word ptr [0xbf8a]
0129 cmp word ptr es:[0x8df6], 0
012f je 0x1d65
0131 cmp word ptr [0x1456], 0 ; _scrollBarFlag
0136 jne 0x1d65
0138 mov word ptr [0x144e], 1 ; _editForce
013e push word ptr [0xbca6] ; _win_hwnd
0142 push 0
0144 push 0
0146 push 0
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 329, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
014d pop si
014e pop di
014f leave 
0150 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near editForce;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near scrollBarFlag;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetEditWinTitle', 'offset': 6918, 'source': None, 'size': 232}
- {'symbol': '_InvalidUpdateEdit', 'offset': 7150, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 41}
- {'symbol': '_DrawSpider', 'offset': 7530, 'source': None, 'size': 1402}
- {'symbol': '_ed_MoveTo', 'offset': 8932, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 22}

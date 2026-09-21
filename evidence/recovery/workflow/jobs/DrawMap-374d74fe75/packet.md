# Recovery task _DrawMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 264 bytes.

```asm
0000 enter 8, 0
0004 push 0x100
0007 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 10, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
000c add sp, 2
000f or ax, ax
0011 jne 0xcd54
0013 jmp 0xce44
0016 push 0x100
0019 nop 
001a push cs
001b call 0x8e44 ; _clip_SetWin
001e add sp, 2
0021 nop 
0022 push cs
0023 call 0xd7a0
0026 mov es, word ptr [0xc1f4]
002a mov ax, word ptr es:[0x72ae]
002e add ax, 2
0031 mov word ptr [bp - 8], ax
0034 mov ax, word ptr es:[0x72b0]
0038 mov word ptr [bp - 6], ax
003b mov cx, word ptr es:[0x72b2]
0040 sub cx, 2
0043 mov word ptr [bp - 4], cx
0046 add ax, 2
0049 mov word ptr [bp - 2], ax
004c push word ptr [0xbca8]
0050 lea ax, [bp - 8]
0053 push ss
0054 push ax
0055 push 0
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
005c mov es, word ptr [0xc1f4]
0060 mov ax, word ptr es:[0x72ae]
0064 add ax, 2
0067 mov word ptr [bp - 8], ax
006a mov ax, word ptr es:[0x72b4]
006e mov cx, ax
0070 sub ax, 2
0073 mov word ptr [bp - 6], ax
0076 mov ax, word ptr es:[0x72b2]
007a sub ax, 2
007d mov word ptr [bp - 4], ax
0080 mov word ptr [bp - 2], cx
0083 push word ptr [0xbca8]
0087 lea ax, [bp - 8]
008a push ss
008b push ax
008c push 0
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0093 mov es, word ptr [0xc1f4]
0097 mov ax, word ptr es:[0x72b0]
009b mov word ptr [bp - 6], ax
009e mov ax, word ptr es:[0x72ae]
00a2 mov word ptr [bp - 8], ax
00a5 add ax, 2
00a8 mov word ptr [bp - 4], ax
00ab mov ax, word ptr es:[0x72b4]
00af mov word ptr [bp - 2], ax
00b2 push word ptr [0xbca8]
00b6 lea ax, [bp - 8]
00b9 push ss
00ba push ax
00bb push 0
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
00c2 mov es, word ptr [0xc1f4]
00c6 mov ax, word ptr es:[0x72b2]
00ca mov cx, ax
00cc sub ax, 2
00cf mov word ptr [bp - 8], ax
00d2 mov ax, word ptr es:[0x72b0]
00d6 mov word ptr [bp - 6], ax
00d9 mov word ptr [bp - 4], cx
00dc mov ax, word ptr es:[0x72b4]
00e0 mov word ptr [bp - 2], ax
00e3 push word ptr [0xbca8]
00e7 lea ax, [bp - 8]
00ea push ss
00eb push ax
00ec push 0
00ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
00f3 push word ptr [0xbca8]
00f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 248, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
00fc nop 
00fd push cs
00fe call 0xcb60 ; _DrawMapData
0101 nop 
0102 push cs
0103 call 0x8e46 ; _clip_Off
0106 leave 
0107 retf 
```

## Known declaration examples

- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawMapData', 'offset': 52064, 'source': None, 'size': 397}
- {'symbol': '_AllocateMapBuffer', 'offset': 52462, 'source': None, 'size': 79}
- {'symbol': '_win_DrawMapWindow', 'offset': 52806, 'source': None, 'size': 712}
- {'symbol': '_DrawMapSpider', 'offset': 53518, 'source': None, 'size': 280}

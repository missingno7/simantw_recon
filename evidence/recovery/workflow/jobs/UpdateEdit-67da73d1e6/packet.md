# Recovery task _UpdateEdit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 694 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 push 0
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
000d add sp, 2
0010 or ax, ax
0012 jne 0x11f7
0014 jmp 0x1492
0017 cmp word ptr [0x1456], 0 ; _scrollBarFlag
001c jne 0x1201
001e jmp 0x12aa
0021 mov di, word ptr [0x14e0]
0025 mov ax, word ptr [0x14e2]
0028 mov word ptr [bp - 2], ax
002b push 0
002d push 0
002f push 1
0031 push 1
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
0038 mov si, ax
003a mov es, word ptr [0xbf90]
003e mov ax, word ptr es:[0x9b08]
0042 mov word ptr [bp - 0xa], ax
0045 mov cx, word ptr es:[0x9b0a]
004a mov word ptr [bp - 8], cx
004d mov dx, ax
004f mov ax, word ptr [0x143a] ; _tileWidth
0052 mov bx, dx
0054 imul word ptr [0xcc80] ; _editWidth
0058 add bx, ax
005a mov word ptr [bp - 6], bx
005d mov ax, word ptr [0x143c] ; _tileHeight
0060 imul word ptr [0xcd7a] ; _editHeight
0064 add cx, ax
0066 mov word ptr [bp - 4], cx
0069 push word ptr [0xbca6] ; _win_hwnd
006d mov ax, di
006f mov es, word ptr [0xbf92]
0073 sub ax, word ptr es:[0x7d2e]
0078 imul word ptr [0x143a] ; _tileWidth
007c push ax
007d mov ax, word ptr [bp - 2]
0080 sub ax, word ptr es:[0x7d30]
0085 imul word ptr [0x143c] ; _tileHeight
0089 push ax
008a lea ax, [bp - 0xa]
008d push ss
008e push ax
008f push ss
0090 push ax
0091 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 61}}]
0096 push word ptr [0xbca6] ; _win_hwnd
009a push si
009b push 0
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 237}}]
00a2 push word ptr [0xbca6] ; _win_hwnd
00a6 push si
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 128}}]
00ac push word ptr [0xbca6] ; _win_hwnd
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
00b5 push word ptr [0xbca6] ; _win_hwnd
00b9 push si
00ba push 0
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 126}}]
00c1 push si
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
00c7 jmp 0x1430
00ca mov bx, word ptr [0x14e0]
00ce cmp bx, -1
00d1 jne 0x12b6
00d3 jmp 0x1430
00d6 mov cx, word ptr [0x14e2]
00da cmp cx, -1
00dd jne 0x12c2
00df jmp 0x1430
00e2 mov si, 0x7d2e
00e5 mov es, word ptr [0xbf92]
00e9 mov word ptr [bp - 0xe], si
00ec mov word ptr [bp - 0xc], es
00ef cmp word ptr es:[si], bx
00f2 jne 0x12de
00f4 cmp word ptr es:[0x7d30], cx
00f9 jne 0x12de
00fb jmp 0x1430
00fe les si, ptr [bp - 0xe]
0101 mov ax, word ptr es:[si]
0104 sub ax, word ptr [0xcc80] ; _editWidth
0108 cmp ax, bx
010a jl 0x12ef
010c jmp 0x1430
010f mov ax, word ptr es:[si]
0112 add ax, word ptr [0xcc80] ; _editWidth
0116 cmp ax, bx
0118 jg 0x12fd
011a jmp 0x1430
011d mov bx, word ptr [0xcd7a] ; _editHeight
0121 mov si, 0x7d30
0124 mov es, word ptr [0xbf92]
0128 mov word ptr [bp - 0x12], si
012b mov word ptr [bp - 0x10], es
012e mov ax, word ptr es:[si]
0131 sub ax, bx
0133 cmp ax, cx
0135 jl 0x131a
0137 jmp 0x1430
013a mov ax, word ptr es:[si]
013d add ax, bx
013f cmp ax, cx
0141 jg 0x1326
0143 jmp 0x1430
0146 mov ax, word ptr [0xcc76] ; _MapPlane
0149 cmp word ptr [0x14e4], ax
014d je 0x1332
014f jmp 0x1430
0152 mov ax, word ptr [0x14e6]
0155 mov es, word ptr [0xbf80]
0159 cmp word ptr es:[0x9b6e], ax
015e je 0x1343
0160 jmp 0x1430
0163 push 0
0165 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 360, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
016a add sp, 2
016d or ax, ax
016f jne 0x1354
0171 jmp 0x1430
0174 push 0
0176 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 377, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinExposed
017b add sp, 2
017e or ax, ax
0180 jne 0x1365
0182 jmp 0x1430
0185 mov di, word ptr [0x14e0]
0189 mov ax, word ptr [0x14e2]
018c mov word ptr [bp - 2], ax
018f push 0
0191 push 0
0193 push 1
0195 push 1
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 408, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
019c mov si, ax
019e mov es, word ptr [0xbf90]
01a2 mov ax, word ptr es:[0x9b08]
01a6 mov word ptr [bp - 0xa], ax
01a9 mov cx, word ptr es:[0x9b0a]
01ae mov word ptr [bp - 8], cx
01b1 mov dx, ax
01b3 mov ax, word ptr [0x143a] ; _tileWidth
01b6 mov bx, dx
01b8 imul word ptr [0xcc80] ; _editWidth
01bc add bx, ax
01be mov word ptr [bp - 6], bx
01c1 mov ax, word ptr [0x143c] ; _tileHeight
01c4 imul word ptr [0xcd7a] ; _editHeight
01c8 add cx, ax
01ca mov word ptr [bp - 4], cx
01cd push word ptr [0xbca6] ; _win_hwnd
01d1 mov ax, di
01d3 les bx, ptr [bp - 0xe]
01d6 sub ax, word ptr es:[bx]
01d9 imul word ptr [0x143a] ; _tileWidth
01dd push ax
01de mov ax, word ptr [bp - 2]
01e1 les di, ptr [bp - 0x12]
01e4 sub ax, word ptr es:[di]
01e7 imul word ptr [0x143c] ; _tileHeight
01eb push ax
01ec lea ax, [bp - 0xa]
01ef push ss
01f0 push ax
01f1 push ss
01f2 push ax
01f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 500, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 61}}]
01f8 push word ptr [0xbca6] ; _win_hwnd
01fc push si
01fd push 0
01ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 512, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 237}}]
0204 push word ptr [0xbca6] ; _win_hwnd
0208 push si
0209 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 522, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 128}}]
020e push word ptr [0xbca6] ; _win_hwnd
0212 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 531, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0217 push word ptr [0xbca6] ; _win_hwnd
021b push si
021c push 0
021e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 543, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 126}}]
0223 push si
0224 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 549, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
0229 mov es, word ptr [0xbf8a]
022d mov word ptr es:[0x8df6], 1
0234 mov ax, word ptr [0x14e2]
0237 les bx, ptr [bp - 0x12]
023a sub ax, word ptr es:[bx]
023d push ax
023e mov ax, word ptr [0x14e0]
0241 les bx, ptr [bp - 0xe]
0244 sub ax, word ptr es:[bx]
0247 push ax
0248 nop 
0249 push cs
024a call 0xe5c ; _ScrollEditArrays
024d add sp, 4
0250 mov es, word ptr [0xbf80]
0254 mov ax, word ptr es:[0x9b6e]
0258 mov word ptr [bp - 0x14], ax
025b cmp ax, word ptr [0x14e6]
025f je 0x1447
0261 mov word ptr [0x144e], 1 ; _editForce
0267 mov es, word ptr [0xbf92]
026b mov ax, word ptr es:[0x7d2e]
026f mov word ptr [0x14e0], ax
0272 mov ax, word ptr es:[0x7d30]
0276 mov word ptr [0x14e2], ax
0279 mov ax, word ptr [0xcc76] ; _MapPlane
027c mov word ptr [0x14e4], ax
027f mov ax, word ptr [bp - 0x14]
0282 mov word ptr [0x14e6], ax
0285 call 0x16d4
0288 mov word ptr [0x144e], 0 ; _editForce
028e push word ptr [0xbca6] ; _win_hwnd
0292 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 659, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0297 nop 
0298 push cs
0299 call 0x6086 ; _ResetEditScrollRange
029c push word ptr [0xbca6] ; _win_hwnd
02a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 675, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
02a5 add sp, 2
02a8 nop 
02a9 push cs
02aa call 0x198a ; _DrawEditGraphs
02ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 688, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
02b2 pop si
02b3 pop di
02b4 leave 
02b5 retf 
```

## Known declaration examples

- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editForce;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editForce;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far editForce;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near scrollBarFlag;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near scrollBarFlag;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileHeight;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_ScrollEditArrays'], 'segment': 3, 'target_offset': 3676, 'caller_offsets': [586]}
- {'callee_names': ['_DrawEditGraphs'], 'segment': 3, 'target_offset': 6538, 'caller_offsets': [682]}
- {'callee_names': ['_ResetEditScrollRange'], 'segment': 3, 'target_offset': 24710, 'caller_offsets': [665]}

## Neighbors

- {'symbol': '_ScrollEditArrays', 'offset': 3676, 'source': None, 'size': 734}
- {'symbol': '_ScrollEditWindow', 'offset': 4410, 'source': None, 'size': 165}
- {'symbol': '_UpdateEditWindow', 'offset': 5270, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 6}
- {'symbol': '_UpdateEditIfBufInvalid', 'offset': 5276, 'source': None, 'size': 82}

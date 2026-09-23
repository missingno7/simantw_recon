# Recovery task _processExp

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 604 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c mov word ptr [bp - 6], 0
0011 mov es, word ptr [0xc25e]
0015 mov word ptr es:[0x7d46], di
001a mov word ptr es:[0x7d48], si
001f push si
0020 push di
0021 push word ptr [0xcc76] ; _MapPlane
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidLocation
002a add sp, 6
002d or ax, ax
002f je 0x705d
0031 push si
0032 push di
0033 nop 
0034 push cs
0035 call 0x727e ; _DoTool
0038 add sp, 4
003b push 0
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0042 add sp, 2
0045 or ax, ax
0047 je 0x7096
0049 nop 
004a push cs
004b call 0x11e0 ; _UpdateEdit
004e nop 
004f push cs
0050 call 0x14ee ; _DrawEdit
0053 push 0x100
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
005b add sp, 2
005e or ax, ax
0060 je 0x70bd
0062 push 1
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MakeDMap
0069 add sp, 2
006c nop 
006d push cs
006e call 0xcd3e ; _DrawMap
0071 jmp 0x70bd
0073 nop 
0074 push 1
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MakeDMap
007b add sp, 2
007e nop 
007f push cs
0080 call 0xcd3e ; _DrawMap
0083 push 0
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
008a add sp, 2
008d or ax, ax
008f je 0x70bd
0091 nop 
0092 push cs
0093 call 0x11e0 ; _UpdateEdit
0096 nop 
0097 push cs
0098 call 0x14ee ; _DrawEdit
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myButton
00a0 dec ax
00a1 je 0x70c8
00a3 jmp 0x727a
00a6 mov di, word ptr [bp - 6]
00a9 lea ax, [bp - 0xa]
00ac push ss
00ad push ax
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GetMousePos
00b3 add sp, 4
00b6 push word ptr [0xcd78] ; _rootWnd
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MyGetTopWindow
00bf add sp, 2
00c2 push ax
00c3 lea ax, [bp - 0xa]
00c6 push ss
00c7 push ax
00c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
00cd mov es, word ptr [0xc260]
00d1 inc word ptr es:[0x9b00]
00d6 push 0x100
00d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 220, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
00de add sp, 2
00e1 or ax, ax
00e3 je 0x7146
00e5 mov ax, word ptr [bp - 0xa]
00e8 mov es, word ptr [0xc262]
00ec sub ax, word ptr es:[0x8110]
00f1 mov es, word ptr [0xc264]
00f5 cdq 
00f6 idiv word ptr es:[0x807c]
00fb mov word ptr [bp - 2], ax
00fe mov ax, word ptr [bp - 8]
0101 mov es, word ptr [0xc262]
0105 sub ax, word ptr es:[0x8112]
010a mov es, word ptr [0xc266]
010e cdq 
010f idiv word ptr es:[0x8096]
0114 mov word ptr [bp - 4], ax
0117 cmp word ptr [0xcc76], 1 ; _MapPlane
011c jle 0x7180
011e sub word ptr [bp - 2], 0x20
0122 jmp 0x7180
0124 mov ax, word ptr [bp - 0xa]
0127 mov es, word ptr [0xc268]
012b sub ax, word ptr es:[0x9b08]
0130 cdq 
0131 idiv word ptr [0x143a] ; _tileWidth
0135 mov es, word ptr [0xc26a]
0139 add ax, word ptr es:[0x7d2e]
013e mov word ptr [bp - 2], ax
0141 mov ax, word ptr [bp - 8]
0144 mov es, word ptr [0xc268]
0148 sub ax, word ptr es:[0x9b0a]
014d cdq 
014e idiv word ptr [0x143c] ; _tileHeight
0152 mov es, word ptr [0xc26a]
0156 add ax, word ptr es:[0x7d30]
015b mov word ptr [bp - 4], ax
015e mov ax, word ptr [bp + 6]
0161 cmp word ptr [bp - 2], ax
0164 jne 0x718d
0166 cmp word ptr [bp - 4], si
0169 je 0x71c1
016b mov es, word ptr [0xc25e]
016f mov word ptr es:[0x7d46], ax
0173 mov word ptr es:[0x7d48], si
0178 mov ax, word ptr [bp - 2]
017b mov word ptr [bp + 6], ax
017e mov si, word ptr [bp - 4]
0181 push si
0182 push ax
0183 push word ptr [0xcc76] ; _MapPlane
0187 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 394, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidLocation
018c add sp, 6
018f or ax, ax
0191 je 0x71c1
0193 push si
0194 push word ptr [bp + 6]
0197 nop 
0198 push cs
0199 call 0x727e ; _DoTool
019c add sp, 4
019f mov es, word ptr [0xc26c]
01a3 cmp word ptr es:[0x79e2], 5
01a9 jl 0x71fb
01ab push word ptr [bp - 4]
01ae push word ptr [bp - 2]
01b1 push word ptr [0xcc76] ; _MapPlane
01b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 440, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidLocation
01ba add sp, 6
01bd or ax, ax
01bf je 0x71fb
01c1 push word ptr [bp - 4]
01c4 push word ptr [bp - 2]
01c7 nop 
01c8 push cs
01c9 call 0x727e ; _DoTool
01cc add sp, 4
01cf mov es, word ptr [0xc26e]
01d3 xor byte ptr es:[0x9af6], 1
01d9 mov ax, di
01db inc al
01dd and ax, 0x3f
01e0 mov di, ax
01e2 push 0
01e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 487, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
01e9 add sp, 2
01ec or ax, ax
01ee je 0x7242
01f0 nop 
01f1 push cs
01f2 call 0x11e0 ; _UpdateEdit
01f5 nop 
01f6 push cs
01f7 call 0x14ee ; _DrawEdit
01fa push 0x100
01fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 512, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0202 add sp, 2
0205 or ax, ax
0207 je 0x726f
0209 test di, 3
020d jne 0x726f
020f push 1
0211 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 532, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MakeDMap
0216 add sp, 2
0219 nop 
021a push cs
021b call 0xcd3e ; _DrawMap
021e jmp 0x726f
0220 push 1
0222 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 549, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MakeDMap
0227 add sp, 2
022a nop 
022b push cs
022c call 0xcd3e ; _DrawMap
022f push 0
0231 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 564, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0236 add sp, 2
0239 or ax, ax
023b je 0x726f
023d test di, 3
0241 jne 0x726f
0243 nop 
0244 push cs
0245 call 0x11e0 ; _UpdateEdit
0248 nop 
0249 push cs
024a call 0x14ee ; _DrawEdit
024d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 592, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myButton
0252 dec ax
0253 jne 0x727a
0255 jmp 0x70cb
0258 pop si
0259 pop di
025a leave 
025b retf 
```

## Known declaration examples

- `extern void far DrawEdit(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far DrawEdit(void);` — src/recovered/wf_tu_simtwo_6EFE-d6ff84e46b.c
- `extern void far DrawMap(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far GetMousePos(struct CursorPoint far *point);` — src/recovered/win_IsCursorInObj.c
- `extern int far IsValidLocation(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far MakeDMap(int mode);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
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

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoTab', 'offset': 28360, 'source': 'src/recovered/DoTab.c', 'size': 26}
- {'symbol': '_DoExpMenu', 'offset': 28386, 'source': None, 'size': 320}
- {'symbol': '_DoTool', 'offset': 29310, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 358}
- {'symbol': '_ReDrawMapEdit', 'offset': 29668, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 107}

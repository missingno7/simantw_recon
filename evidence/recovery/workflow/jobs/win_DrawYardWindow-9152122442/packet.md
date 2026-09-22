# Recovery task _win_DrawYardWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 558 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 test di, 1
000d jne 0xa9f2
000f jmp 0xaba7
0012 cmp word ptr [0x18b6], 0
0017 je 0xaa15
0019 mov es, word ptr [0xc19e]
001d push word ptr es:[0x7a62]
0022 push word ptr es:[0x7a60]
0027 nop 
0028 push cs
0029 call 0xbe04 ; _InvertPatch
002c add sp, 4
002f mov word ptr [0x18b6], 0
0035 mov es, word ptr [0xc1a0]
0039 mov word ptr es:[0x1994], 0
0040 nop 
0041 push cs
0042 call 0xccee ; _AllocateMapBuffer
0045 cmp word ptr [0x18b4], 0
004a jne 0xaa2f
004c jmp 0xaba7
004f mov es, word ptr [0xc1a2]
0053 push word ptr es:[0x19aa]
0058 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 91, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
005d add sp, 2
0060 mov word ptr [bp - 4], ax
0063 mov word ptr [bp - 2], dx
0066 cmp word ptr [0xce82], 0 ; _YardMode
006b jne 0xaa50
006d jmp 0xab28
0070 cmp word ptr [0xce82], 1 ; _YardMode
0075 jne 0xaa5a
0077 jmp 0xab28
007a lea ax, [bp - 0x14]
007d push ss
007e push ax
007f push 0x1914
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0087 add sp, 6
008a mov ax, word ptr [bp - 0x14]
008d mov word ptr [bp - 0xc], ax
0090 test byte ptr [0xcc7e], 1 ; _displayType
0095 je 0xaa7a
0097 jmp 0xab10
009a mov ax, word ptr [bp - 0xe]
009d inc ax
009e mov word ptr [bp - 0xa], ax
00a1 cmp byte ptr [0xcc7e], 0xa ; _displayType
00a6 jne 0xaa9a
00a8 push 0x1b6c
00ab lea ax, [bp - 8]
00ae push ss
00af push ax
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
00b5 add sp, 6
00b8 jmp 0xaad6
00ba push 0x1b6c
00bd lea ax, [bp - 8]
00c0 push ss
00c1 push ax
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
00c7 add sp, 6
00ca mov si, word ptr [bp - 6]
00cd push 0x1b6d
00d0 lea ax, [bp - 8]
00d3 push ss
00d4 push ax
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
00da add sp, 6
00dd add si, word ptr [bp - 6]
00e0 push 0x1b6e
00e3 lea ax, [bp - 8]
00e6 push ss
00e7 push ax
00e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 235, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
00ed add sp, 6
00f0 add si, word ptr [bp - 6]
00f3 mov word ptr [bp - 6], si
00f6 push 0
00f8 push word ptr [bp - 2]
00fb push word ptr [bp - 4]
00fe mov es, word ptr [0xc1a4]
0102 mov ax, word ptr es:[0x8096]
0106 shl ax, 6
0109 cmp ax, word ptr [bp - 6]
010c jle 0xaaf1
010e mov ax, word ptr [bp - 6]
0111 push ax
0112 mov es, word ptr [0xc1a6]
0116 mov ax, word ptr es:[0x807c]
011a shl ax, 7
011d push ax
011e push word ptr [bp - 0xa]
0121 push word ptr [bp - 0xc]
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastBitmap
0129 add sp, 0xe
012c jmp 0xab96
012f nop 
0130 mov ax, word ptr [bp - 0x12]
0133 mov word ptr [bp - 0xa], ax
0136 push 0x1b5a
0139 lea ax, [bp - 8]
013c push ss
013d push ax
013e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 321, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
0143 add sp, 6
0146 jmp 0xab62
0148 lea ax, [bp - 0x14]
014b push ss
014c push ax
014d push 0x1903
0150 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 339, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0155 add sp, 6
0158 mov ax, word ptr [bp - 0x14]
015b mov word ptr [bp - 0xc], ax
015e mov ax, word ptr [bp - 0x12]
0161 mov word ptr [bp - 0xa], ax
0164 mov ax, word ptr [0xce82] ; _YardMode
0167 add ax, 0x1b58
016a push ax
016b lea ax, [bp - 8]
016e push ss
016f push ax
0170 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 371, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
0175 add sp, 6
0178 test byte ptr [0xcc7e], 1 ; _displayType
017d jne 0xab62
017f jmp 0xaad6
0182 push word ptr [bp - 2]
0185 push word ptr [bp - 4]
0188 mov es, word ptr [0xc1a4]
018c mov ax, word ptr es:[0x8096]
0190 shl ax, 6
0193 cmp ax, word ptr [bp - 6]
0196 jle 0xab7b
0198 mov ax, word ptr [bp - 6]
019b push ax
019c mov es, word ptr [0xc1a6]
01a0 mov ax, word ptr es:[0x807c]
01a4 shl ax, 7
01a7 push ax
01a8 push word ptr [bp - 0xa]
01ab push word ptr [bp - 0xc]
01ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 433, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastMonoBitmap
01b3 add sp, 0xc
01b6 mov es, word ptr [0xc1a2]
01ba push word ptr es:[0x19aa]
01bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 450, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01c4 add sp, 2
01c7 mov ax, di
01c9 test al, 2
01cb je 0xac0a
01cd mov bx, word ptr [0xce82] ; _YardMode
01d1 cmp bx, 1
01d4 jle 0xabd7
01d6 mov es, word ptr [0xc1a8]
01da mov word ptr es:[0x8a68], 0
01e1 cmp bx, 2
01e4 jne 0xabce
01e6 push bx
01e7 nop 
01e8 push cs
01e9 call 0xbea4 ; _DrawSimColonies
01ec jmp 0xabd4
01ee push bx
01ef nop 
01f0 push cs
01f1 call 0xbf9c ; _DrawColonyBars
01f4 add sp, 2
01f7 mov es, word ptr [0xc1a0]
01fb mov ax, word ptr es:[0x1994]
01ff mov es, word ptr [0xc1aa]
0203 mov word ptr es:[0x19a6], ax
0207 cmp word ptr [0x18b6], 0
020c jne 0xac0a
020e mov es, word ptr [0xc19e]
0212 push word ptr es:[0x7a62]
0217 push word ptr es:[0x7a60]
021c nop 
021d push cs
021e call 0xbe04 ; _InvertPatch
0221 add sp, 4
0224 mov word ptr [0x18b6], 1
022a pop si
022b pop di
022c leave 
022d retf 
```

## Known declaration examples

- `extern void far InvertPatch(int x, int y);` — src/recovered/DrawYardCursor.c
- `extern void far InvertPatch(int x, int y);` — src/recovered/EraseYardCursor.c
- `extern int near YardMode;` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
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

- {'symbol': '_DrawYardCursor', 'offset': 43416, 'source': 'src/recovered/DrawYardCursor.c', 'size': 36}
- {'symbol': '_EraseYardCursor', 'offset': 43452, 'source': 'src/recovered/EraseYardCursor.c', 'size': 36}
- {'symbol': '_UpdateYardMessage', 'offset': 44046, 'source': 'src/recovered/wf_UpdateYardMessage-77b8db79c0.c', 'size': 202}
- {'symbol': '_DrawYardData', 'offset': 44248, 'source': None, 'size': 460}

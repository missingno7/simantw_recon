# Recovery task _win_DrawCasteWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 216 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov ax, di
000b and al, 1
000d je 0xc67c
000f mov es, word ptr [0xc12c]
0013 cmp word ptr es:[0x7c4a], 0
0019 jne 0xc67c
001b push 0x1300
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0023 add sp, 2
0026 mov ax, di
0028 and al, 1
002a jne 0xc685
002c jmp 0xc713
002f cmp word ptr [0x15b8], 0 ; _casteBitmap
0034 jne 0xc68f
0036 jmp 0xc713
0039 push word ptr [0x15b8] ; _casteBitmap
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0042 add sp, 2
0045 mov si, ax
0047 mov word ptr [bp - 2], dx
004a lea ax, [bp - 0x10]
004d push ss
004e push ax
004f push 0x1302
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0057 add sp, 6
005a mov ax, word ptr [bp - 0x10]
005d mov word ptr [bp - 8], ax
0060 mov ax, word ptr [bp - 0xe]
0063 mov word ptr [bp - 6], ax
0066 test byte ptr [0xcc7e], 1 ; _displayType
006b jne 0xc6e8
006d push 0
006f mov ax, si
0071 mov dx, word ptr [bp - 2]
0074 add ax, 4
0077 push dx
0078 push ax
0079 mov es, dx
007b push word ptr es:[si + 2]
007f push word ptr es:[si]
0082 push word ptr [bp - 6]
0085 push word ptr [bp - 8]
0088 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 139, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastBitmap
008d add sp, 0xe
0090 jmp 0xc707
0092 mov cx, word ptr [bp - 2]
0095 lea ax, [si + 4]
0098 push cx
0099 push ax
009a mov es, cx
009c push word ptr es:[si + 2]
00a0 push word ptr es:[si]
00a3 push word ptr [bp - 6]
00a6 push word ptr [bp - 8]
00a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DoFastMonoBitmap
00ae add sp, 0xc
00b1 push word ptr [0x15b8] ; _casteBitmap
00b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00ba add sp, 2
00bd mov ax, di
00bf test al, 2
00c1 je 0xc72a
00c3 push word ptr [0x15b4]
00c7 push 0
00c9 push 0x1300
00cc nop 
00cd push cs
00ce call 0xc7c4 ; _DrawControlLevels
00d1 add sp, 6
00d4 pop si
00d5 pop di
00d6 leave 
00d7 retf 
```

## Known declaration examples

- `extern unsigned int near casteBitmap;` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_win_DrawPictureWindow-9fe716872a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawModeWindow', 'offset': 50408, 'source': None, 'size': 216}
- {'symbol': '_win_ModeControlClosed', 'offset': 50624, 'source': None, 'size': 149}
- {'symbol': '_win_CasteControlClosed', 'offset': 50990, 'source': None, 'size': 149}
- {'symbol': '_DrawControlLevels', 'offset': 51140, 'source': None, 'size': 538}

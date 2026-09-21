# Recovery task _win_SetColorFromObjNum

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 152 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 push word ptr [bp + 6]
0008 nop 
0009 push cs
000a call 0xe3a8 ; _win_LockWin
000d add sp, 2
0010 push word ptr [bp + 6]
0013 nop 
0014 push cs
0015 call 0xc32e ; _win_ObjAddr
0018 add sp, 2
001b mov es, dx
001d mov bx, ax
001f mov si, bx
0021 mov word ptr [bp - 2], es
0024 test byte ptr es:[bx + 0x24], 4
0029 je 0xb4e4
002b mov al, byte ptr es:[si + 0x27]
002f jmp 0xb4e8
0031 nop 
0032 mov al, byte ptr es:[si + 0x26]
0036 cwde 
0037 mov cx, ax
0039 shl ax, 1
003b add ax, cx
003d shl ax, 1
003f add ax, 0x78ec
0042 mov word ptr [0xcc58], ax
0045 mov <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004b test byte ptr [0xcc7e], 1 ; _displayType
0050 jne 0xb51a
0052 les bx, ptr [0xcc58]
0056 mov al, byte ptr es:[bx]
0059 cwde 
005a imul ax, ax, 0x101
005e push ax
005f mov cx, ax
0061 mov al, byte ptr es:[bx + 2]
0065 jmp 0xb52d
0067 nop 
0068 les bx, ptr [0xcc58]
006c mov al, byte ptr es:[bx]
006f cwde 
0070 imul ax, ax, 0x101
0074 push ax
0075 mov cx, ax
0077 mov al, byte ptr es:[bx + 3]
007b cwde 
007c imul ax, ax, 0x101
0080 push ax
0081 push cx
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
0087 add sp, 6
008a push word ptr [bp + 6]
008d nop 
008e push cs
008f call 0xe3a4 ; _win_UnlockWin
0092 add sp, 2
0095 pop si
0096 leave 
0097 retf 
```

## Known declaration examples

- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far * far win_ObjAddr(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetColorNum', 'offset': 46058, 'source': None, 'size': 87}
- {'symbol': '_win_SetColorFromObj', 'offset': 46146, 'source': 'src/recovered/wf_win_SetColorFromObj-7570e08dca.c', 'size': 111}
- {'symbol': '_win_RectFill', 'offset': 46410, 'source': None, 'size': 264}
- {'symbol': '_win_FillObjRect', 'offset': 46674, 'source': None, 'size': 35}

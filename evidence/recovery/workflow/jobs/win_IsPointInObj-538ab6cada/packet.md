# Recovery task _win_IsPointInObj

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 108 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 push word ptr [bp + 0xa]
0009 nop 
000a push cs
000b call 0xe3a8 ; _win_LockWin
000e add sp, 2
0011 mov bl, byte ptr [bp + 0xa]
0014 sub bh, bh
0016 shl bx, 2
0019 mov si, word ptr [bp + 0xa]
001c sar si, 8
001f shl si, 2
0022 les si, ptr [si - 0x3166]
0026 mov ax, word ptr es:[bx + si + 0x2c]
002a mov dx, word ptr es:[bx + si + 0x2e]
002e push ds
002f lea di, [bp - 8]
0032 mov si, ax
0034 push ss
0035 pop es
0036 mov ds, dx
0038 movsw word ptr es:[di], word ptr [si]
0039 movsw word ptr es:[di], word ptr [si]
003a movsw word ptr es:[di], word ptr [si]
003b movsw word ptr es:[di], word ptr [si]
003c pop ds
003d cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
0042 je 0xe300
0044 inc word ptr [bp - 4]
0047 inc word ptr [bp - 2]
004a push word ptr [bp + 0xa]
004d nop 
004e push cs
004f call 0xe3a4 ; _win_UnlockWin
0052 add sp, 2
0055 lea ax, [bp - 8]
0058 push ss
0059 push ax
005a push word ptr [bp + 8]
005d push word ptr [bp + 6]
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PointInRect
0065 add sp, 8
0068 pop si
0069 pop di
006a leave 
006b retf 
```

## Known declaration examples

- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjSize-35d87c4c75.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjSize-35d87c4c75.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DoProxMenu', 'offset': 56930, 'source': None, 'size': 993}
- {'symbol': '_win_InvalidateObject', 'offset': 57924, 'source': None, 'size': 113}
- {'symbol': '_win_ClearObjArea', 'offset': 58146, 'source': None, 'size': 113}
- {'symbol': '_win_SetGaugeValue', 'offset': 58260, 'source': 'src/recovered/win_SetGaugeValue.c', 'size': 1}

# Recovery task _win_DrawBitMapAtObjNum

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 98 bytes.

```asm
0000 enter 4, 0
0004 push word ptr [bp + 6]
0007 nop 
0008 push cs
0009 call 0xe3a8 ; _win_LockWin
000c add sp, 2
000f push word ptr [bp + 6]
0012 nop 
0013 push cs
0014 call 0xc32e ; _win_ObjAddr
0017 add sp, 2
001a mov es, dx
001c mov bx, ax
001e mov word ptr [bp - 4], bx
0021 mov word ptr [bp - 2], es
0024 test byte ptr es:[bx + 0x24], 1
0029 je 0xbec8
002b push word ptr [bp + 8]
002e push word ptr es:[bx + 2]
0032 push word ptr es:[bx]
0035 nop 
0036 push cs
0037 call 0xbd5a ; _win_DrawBitMap
003a add sp, 6
003d or ax, ax
003f jne 0xbec8
0041 mov al, byte ptr [0xce97] ; _monoPat
0044 cwde 
0045 or ax, word ptr [0xcf4e] ; __foreColor
0049 push ax
004a push word ptr [bp - 2]
004d push word ptr [bp - 4]
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
0055 add sp, 6
0058 push word ptr [bp + 6]
005b nop 
005c push cs
005d call 0xe3a4 ; _win_UnlockWin
0060 leave 
0061 retf 
```

## Known declaration examples

- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern unsigned char near monoPat;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far * far win_ObjAddr(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern struct GameObjectSelection far * far win_ObjAddr(int objectNumber);` — src/recovered/win_IsObjSelected.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawBitMap', 'offset': 48474, 'source': None, 'size': 214}
- {'symbol': '_win_DrawBitMapAtObj', 'offset': 48688, 'source': None, 'size': 64}
- {'symbol': '_win_PrintTextInRect', 'offset': 48850, 'source': None, 'size': 438}
- {'symbol': '_win_PrintTextInObj', 'offset': 49288, 'source': 'src/recovered/win_PrintTextInObj.c', 'size': 41}

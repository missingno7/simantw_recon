# Recovery task _win_GetObjRect

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 91 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 push word ptr [bp + 6]
0008 nop 
0009 push cs
000a call 0xe3a8 ; _win_LockWin
000d add sp, 2
0010 mov bl, byte ptr [bp + 6]
0013 sub bh, bh
0015 shl bx, 2
0018 mov si, word ptr [bp + 6]
001b sar si, 8
001e shl si, 2
0021 les si, ptr [si - 0x3166]
0025 mov ax, word ptr es:[bx + si + 0x2c]
0029 mov dx, word ptr es:[bx + si + 0x2e]
002d push ds
002e mov si, ax
0030 mov ds, dx
0032 les di, ptr [bp + 8]
0035 movsw word ptr es:[di], word ptr [si]
0036 movsw word ptr es:[di], word ptr [si]
0037 movsw word ptr es:[di], word ptr [si]
0038 movsw word ptr es:[di], word ptr [si]
0039 pop ds
003a cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
003f je 0xc31e
0041 mov bx, word ptr [bp + 8]
0044 inc word ptr es:[bx + 4]
0048 inc word ptr es:[bx + 6]
004c push word ptr [bp + 6]
004f nop 
0050 push cs
0051 call 0xe3a4 ; _win_UnlockWin
0054 add sp, 2
0057 pop si
0058 pop di
0059 leave 
005a retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/win_DrawObjectNum.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_IsWinZoomed', 'offset': 49800, 'source': None, 'size': 49}
- {'symbol': '_win_Zoom', 'offset': 49850, 'source': 'src/recovered/win_Zoom.c', 'size': 24}
- {'symbol': '_win_ObjAddr', 'offset': 49966, 'source': 'src/recovered/wf_win_ObjAddr-54759b245b.c', 'size': 72}
- {'symbol': '_win_WinObjAddr', 'offset': 50038, 'source': None, 'size': 87}

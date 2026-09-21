# Recovery task _win_InvalidateObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 113 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0xe3a8 ; _win_LockWin
000e add sp, 2
0011 mov bl, byte ptr [bp + 6]
0014 sub bh, bh
0016 shl bx, 2
0019 mov si, word ptr [bp + 6]
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
0042 je 0xe28e
0044 inc word ptr [bp - 4]
0047 inc word ptr [bp - 2]
004a push word ptr [bp + 6]
004d nop 
004e push cs
004f call 0xe3a4 ; _win_UnlockWin
0052 add sp, 2
0055 mov bx, word ptr [bp + 6]
0058 sar bx, 8
005b shl bx, 1
005d push word ptr [bx - 0x435a]
0061 lea ax, [bp - 8]
0064 push ss
0065 push ax
0066 push 0
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
006d pop si
006e pop di
006f leave 
0070 retf 
```

## Known declaration examples

- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_IsPointInObj-538ab6cada.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': 'INDIRECTDLGPROC', 'offset': 56786, 'source': None, 'size': 143}
- {'symbol': '_win_DoProxMenu', 'offset': 56930, 'source': None, 'size': 993}
- {'symbol': '_win_IsPointInObj', 'offset': 58038, 'source': 'src/recovered/wf_win_IsPointInObj-538ab6cada.c', 'size': 108}
- {'symbol': '_win_ClearObjArea', 'offset': 58146, 'source': 'src/recovered/wf_win_ClearObjArea-a3b268354e.c', 'size': 113}

# Recovery task _win_ObjInv

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 71 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 6]
0008 push si
0009 nop 
000a push cs
000b call 0xe3a8 ; _win_LockWin
000e add sp, 2
0011 mov ax, si
0013 sar si, 8
0016 mov di, ax
0018 and di, 0xff
001c shl di, 2
001f shl si, 2
0022 les bx, ptr [si - 0x3166]
0026 add bx, 0x2c
0029 push word ptr es:[bx + di + 2]
002d push word ptr es:[bx + di]
0030 mov si, ax
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
0037 add sp, 4
003a push si
003b nop 
003c push cs
003d call 0xe3a4 ; _win_UnlockWin
0040 add sp, 2
0043 pop si
0044 pop di
0045 leave 
0046 retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/win_IsObjSelected.c
- `extern void far win_LockWin(int object);` — src/recovered/win_MakeObjAutoToggle.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/win_IsObjSelected.c
- `extern void far win_UnlockWin(int object);` — src/recovered/win_MakeObjAutoToggle.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawVBar', 'offset': 56220, 'source': None, 'size': 194}
- {'symbol': '_win_GetObjSize', 'offset': 56414, 'source': None, 'size': 98}
- {'symbol': '_win_GetProxEvent', 'offset': 56584, 'source': 'src/recovered/win_GetProxEvent.c', 'size': 4}
- {'symbol': '__win_SetProxItem', 'offset': 56588, 'source': None, 'size': 197}

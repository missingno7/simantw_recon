# Recovery task _win_SetButtonBitmaps

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 82 bytes.

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
0024 cmp byte ptr es:[bx + 0x21], 0xd
0029 je 0xf5e3
002b push ds
002c push 0xbe18
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0034 add sp, 4
0037 mov ax, word ptr [bp + 8]
003a les bx, ptr [bp - 4]
003d mov word ptr es:[bx + 0x28], ax
0041 mov ax, word ptr [bp + 0xa]
0044 mov word ptr es:[bx + 0x2a], ax
0048 push word ptr [bp + 6]
004b nop 
004c push cs
004d call 0xe3a4 ; _win_UnlockWin
0050 leave 
0051 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/win_IsObjSelected.c
- `extern void far * far win_ObjAddr(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern struct GameObjectSelection far * far win_ObjAddr(int objectNumber);` — src/recovered/win_IsObjSelected.c
- `extern struct WinObjectAutoToggle far *win_ObjAddr(int object);` — src/recovered/win_MakeObjAutoToggle.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/win_IsObjSelected.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_MakeGroupVisible', 'offset': 62640, 'source': None, 'size': 125}
- {'symbol': '_win_MakeGroupInvisible', 'offset': 62766, 'source': None, 'size': 125}
- {'symbol': '_win_DrawGroupObjects', 'offset': 62974, 'source': None, 'size': 134}
- {'symbol': '_win_ClearGroupAreas', 'offset': 63108, 'source': None, 'size': 134}

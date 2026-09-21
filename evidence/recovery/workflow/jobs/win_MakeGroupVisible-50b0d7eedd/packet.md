# Recovery task _win_MakeGroupVisible

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 125 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push si
000a nop 
000b push cs
000c call 0xe3a8 ; _win_LockWin
000f add sp, 2
0012 mov word ptr [bp - 6], si
0015 mov word ptr [bp - 8], 0
001a mov bx, si
001c sar bx, 8
001f shl bx, 2
0022 les bx, ptr [bx - 0x3166]
0026 mov di, bx
0028 mov word ptr [bp - 0xa], es
002b cmp word ptr es:[bx + 0xc], 0
0030 jle 0xf51e
0032 mov ax, di
0034 mov dx, es
0036 add ax, 0x2c
0039 mov word ptr [bp - 4], ax
003c mov word ptr [bp - 2], dx
003f mov word ptr [bp - 0xc], di
0042 mov di, word ptr [bp - 8]
0045 mov al, byte ptr [bp + 8]
0048 les bx, ptr [bp - 4]
004b les bx, ptr es:[bx]
004e cmp byte ptr es:[bx + 0x20], al
0052 jne 0xf50f
0054 push 1
0056 push si
0057 nop 
0058 push cs
0059 call 0xf2bc ; _win_SetObjVisibleState
005c add sp, 4
005f add word ptr [bp - 4], 4
0063 inc si
0064 inc di
0065 les bx, ptr [bp - 0xc]
0068 cmp word ptr es:[bx + 0xc], di
006c jg 0xf4f5
006e push word ptr [bp + 6]
0071 nop 
0072 push cs
0073 call 0xe3a4 ; _win_UnlockWin
0076 add sp, 2
0079 pop si
007a pop di
007b leave 
007c retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_SetObjVisibleState(int object, int visible);` — src/recovered/win_MakeObjInvisible.c
- `extern void far win_SetObjVisibleState(int object, int visible);` — src/recovered/win_MakeObjVisible.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_MakeObjInvisible', 'offset': 62500, 'source': 'src/recovered/win_MakeObjInvisible.c', 'size': 15}
- {'symbol': '_win_SetGroupVisibleState', 'offset': 62516, 'source': None, 'size': 123}
- {'symbol': '_win_MakeGroupInvisible', 'offset': 62766, 'source': None, 'size': 125}
- {'symbol': '_win_SetButtonBitmaps', 'offset': 62892, 'source': 'src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c', 'size': 82}

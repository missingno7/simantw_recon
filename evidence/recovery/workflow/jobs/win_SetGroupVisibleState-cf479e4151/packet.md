# Recovery task _win_SetGroupVisibleState

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 123 bytes.

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
0012 mov word ptr [bp - 8], 0
0017 mov bx, si
0019 sar bx, 8
001c shl bx, 2
001f les bx, ptr [bx - 0x3166]
0023 mov di, bx
0025 mov word ptr [bp - 0xa], es
0028 cmp word ptr es:[bx + 0xc], 0
002d jle 0xf4a0
002f mov ax, bx
0031 mov dx, es
0033 add ax, 0x2c
0036 mov word ptr [bp - 4], ax
0039 mov word ptr [bp - 2], dx
003c mov word ptr [bp - 0xc], di
003f mov di, word ptr [bp - 8]
0042 mov al, byte ptr [bp + 8]
0045 les bx, ptr [bp - 4]
0048 les bx, ptr es:[bx]
004b cmp byte ptr es:[bx + 0x20], al
004f jne 0xf491
0051 push word ptr [bp + 0xa]
0054 push si
0055 nop 
0056 push cs
0057 call 0xf2bc ; _win_SetObjVisibleState
005a add sp, 4
005d add word ptr [bp - 4], 4
0061 inc si
0062 inc di
0063 les bx, ptr [bp - 0xc]
0066 cmp word ptr es:[bx + 0xc], di
006a jg 0xf476
006c push word ptr [bp + 6]
006f nop 
0070 push cs
0071 call 0xe3a4 ; _win_UnlockWin
0074 add sp, 2
0077 pop si
0078 pop di
0079 leave 
007a retf 
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

- {'symbol': '_win_MakeObjVisible', 'offset': 62484, 'source': 'src/recovered/win_MakeObjVisible.c', 'size': 15}
- {'symbol': '_win_MakeObjInvisible', 'offset': 62500, 'source': 'src/recovered/win_MakeObjInvisible.c', 'size': 15}
- {'symbol': '_win_MakeGroupVisible', 'offset': 62640, 'source': None, 'size': 125}
- {'symbol': '_win_MakeGroupInvisible', 'offset': 62766, 'source': None, 'size': 125}

# Recovery task _win_GetObjSize

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 98 bytes.

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
003d mov ax, word ptr [bp - 4]
0040 sub ax, word ptr [bp - 8]
0043 les bx, ptr [bp + 8]
0046 mov word ptr es:[bx], ax
0049 mov ax, word ptr [bp - 2]
004c sub ax, word ptr [bp - 6]
004f mov word ptr es:[bx + 2], ax
0053 push word ptr [bp + 6]
0056 nop 
0057 push cs
0058 call 0xe3a4 ; _win_UnlockWin
005b add sp, 2
005e pop si
005f pop di
0060 leave 
0061 retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawHBar', 'offset': 56028, 'source': None, 'size': 192}
- {'symbol': '_win_DrawVBar', 'offset': 56220, 'source': None, 'size': 194}
- {'symbol': '_win_ObjInv', 'offset': 56512, 'source': 'src/recovered/wf_win_ObjInv-18e2e84ce2.c', 'size': 71}
- {'symbol': '_win_GetProxEvent', 'offset': 56584, 'source': 'src/recovered/win_GetProxEvent.c', 'size': 4}

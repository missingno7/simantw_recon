# Recovery task _win_SetGroupSelectableState

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 118 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push si
000a nop 
000b push cs
000c call 0xe3a8 ; _win_LockWin
000f add sp, 2
0012 mov ax, si
0014 sub al, al
0016 mov bx, si
0018 sar bx, 8
001b shl bx, 2
001e mov ax, word ptr [bx - 0x3166]
0022 mov dx, word ptr [bx - 0x3164]
0026 mov di, ax
0028 mov es, dx
002a mov bx, di
002c cmp word ptr es:[bx + 0xc], 0
0031 jle 0xebfd
0033 add ax, 0x2c
0036 mov cx, ax
0038 mov ds, dx
003a mov ax, word ptr es:[di + 0xc]
003e mov di, cx
0040 mov cx, ax
0042 mov al, byte ptr [bp + 8]
0045 les bx, ptr [di]
0047 cmp byte ptr es:[bx + 0x20], al
004b jne 0xebf5
004d mov al, byte ptr es:[bx + 0x24]
0051 mov dx, word ptr [bp + 0xa]
0054 shl dx, 1
0056 xor al, dl
0058 and ax, 2
005b xor word ptr es:[bx + 0x24], ax
005f add di, 4
0062 dec cx
0063 jne 0xebd8
0065 push ss
0066 pop ds
0067 push word ptr [bp + 6]
006a nop 
006b push cs
006c call 0xe3a4 ; _win_UnlockWin
006f add sp, 2
0072 pop si
0073 pop di
0074 leave 
0075 retf 
```

## Known declaration examples

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

- {'symbol': '_win_MakeObjSelFlash', 'offset': 60218, 'source': 'src/recovered/win_MakeObjSelFlash.c', 'size': 46}
- {'symbol': '_win_MakeObjUnSelFlash', 'offset': 60264, 'source': 'src/recovered/win_MakeObjUnSelFlash.c', 'size': 46}
- {'symbol': '_win_MakeGroupSelectable', 'offset': 60428, 'source': None, 'size': 125}
- {'symbol': '_win_MakeGroupUnselectable', 'offset': 60554, 'source': None, 'size': 125}

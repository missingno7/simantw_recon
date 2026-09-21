# Recovery task _win_MakeGroupUnselectable

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 125 bytes.

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
0016 mov word ptr [bp - 0xe], ax
0019 mov bx, si
001b sar bx, 8
001e shl bx, 2
0021 mov ax, word ptr [bx - 0x3166]
0025 mov dx, word ptr [bx - 0x3164]
0029 mov di, ax
002b mov word ptr [bp - 0xa], dx
002e mov word ptr [bp - 8], 0
0033 mov es, dx
0035 mov bx, ax
0037 cmp word ptr es:[bx + 0xc], 0
003c jle 0xecf8
003e add ax, 0x2c
0041 mov cx, ax
0043 mov ds, dx
0045 mov ax, word ptr es:[di + 0xc]
0049 mov word ptr [bp - 6], ax
004c mov word ptr [bp - 4], cx
004f mov word ptr [bp - 0xc], di
0052 mov si, cx
0054 mov cx, ax
0056 les bx, ptr [si]
0058 mov al, byte ptr [bp + 8]
005b cmp byte ptr es:[bx + 0x20], al
005f jne 0xecf0
0061 and byte ptr es:[bx + 0x24], 0xfd
0066 add si, 4
0069 dec cx
006a jne 0xece0
006c push ss
006d pop ds
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
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_GetObjRect-1895b30cfd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetGroupSelectableState', 'offset': 60310, 'source': None, 'size': 118}
- {'symbol': '_win_MakeGroupSelectable', 'offset': 60428, 'source': None, 'size': 125}
- {'symbol': '_win_SetObjSelectedStateI', 'offset': 60680, 'source': None, 'size': 331}
- {'symbol': '_win_SetObjSelectedState', 'offset': 61012, 'source': None, 'size': 195}

# Recovery task _win_ClearGroupAreas

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 134 bytes.

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
0012 mov ax, si
0014 sub al, al
0016 mov word ptr [bp - 6], ax
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
003c jle 0xf6fb
003e add ax, 0x2c
0041 mov word ptr [bp - 4], ax
0044 mov word ptr [bp - 2], dx
0047 mov si, word ptr [bp - 6]
004a mov word ptr [bp - 0xc], di
004d mov di, word ptr [bp - 8]
0050 mov al, byte ptr [bp + 8]
0053 les bx, ptr [bp - 4]
0056 les bx, ptr es:[bx]
0059 cmp byte ptr es:[bx + 0x20], al
005d jne 0xf6ec
005f push si
0060 nop 
0061 push cs
0062 call 0xe322 ; _win_ClearObjArea
0065 add sp, 2
0068 add word ptr [bp - 4], 4
006c inc si
006d inc di
006e les bx, ptr [bp - 0xc]
0071 cmp word ptr es:[bx + 0xc], di
0075 jg 0xf6d4
0077 push word ptr [bp + 6]
007a nop 
007b push cs
007c call 0xe3a4 ; _win_UnlockWin
007f add sp, 2
0082 pop si
0083 pop di
0084 leave 
0085 retf 
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

- {'symbol': '_win_SetButtonBitmaps', 'offset': 62892, 'source': 'src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c', 'size': 82}
- {'symbol': '_win_DrawGroupObjects', 'offset': 62974, 'source': None, 'size': 134}
- {'symbol': '_win_IsObjSelected', 'offset': 63242, 'source': 'src/recovered/win_IsObjSelected.c', 'size': 55}
- {'symbol': '_win_IsCursorInObj', 'offset': 63298, 'source': 'src/recovered/win_IsCursorInObj.c', 'size': 50}

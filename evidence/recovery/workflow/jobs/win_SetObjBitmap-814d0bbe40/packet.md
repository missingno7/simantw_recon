# Recovery task _win_SetObjBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 123 bytes.

```asm
0000 enter 8, 0
0004 push si
0005 push word ptr [bp + 6]
0008 nop 
0009 push cs
000a call 0xe3a8 ; _win_LockWin
000d add sp, 2
0010 mov al, byte ptr [bp + 6]
0013 sub ah, ah
0015 mov bx, word ptr [bp + 6]
0018 sar bx, 8
001b shl bx, 2
001e les bx, ptr [bx - 0x3166]
0022 mov si, bx
0024 mov word ptr [bp - 6], es
0027 cmp word ptr es:[bx + 0xc], ax
002b jg 0xd5f7
002d push ds
002e push 0xbd12
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0036 add sp, 4
0039 mov es, word ptr [bp - 6]
003c mov bl, byte ptr [bp + 6]
003f sub bh, bh
0041 shl bx, 2
0044 add bx, si
0046 les bx, ptr es:[bx + 0x2c]
004a mov word ptr [bp - 4], bx
004d mov word ptr [bp - 2], es
0050 cmp byte ptr es:[bx + 0x21], 6
0055 je 0xd621
0057 push ds
0058 push 0xbdda
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0060 add sp, 4
0063 mov ax, word ptr [bp + 8]
0066 les bx, ptr [bp - 4]
0069 mov word ptr es:[bx + 0x28], ax
006d push word ptr [bp + 6]
0070 nop 
0071 push cs
0072 call 0xe3a4 ; _win_UnlockWin
0075 add sp, 2
0078 pop si
0079 leave 
007a retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
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

- {'symbol': '_win_Swap', 'offset': 54324, 'source': None, 'size': 359}
- {'symbol': '_win_SetWinDrawHook', 'offset': 54684, 'source': 'src/recovered/win_SetWinDrawHook.c', 'size': 34}
- {'symbol': '_win_CenterStrAtObj', 'offset': 54842, 'source': None, 'size': 160}
- {'symbol': '_win_PrintfAtObj', 'offset': 55002, 'source': None, 'size': 183}

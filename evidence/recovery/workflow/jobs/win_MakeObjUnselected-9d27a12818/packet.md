# Recovery task _win_MakeObjUnselected

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 194 bytes.

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
0012 push si
0013 nop 
0014 push cs
0015 call 0xc32e ; _win_ObjAddr
0018 add sp, 2
001b mov es, dx
001d mov bx, ax
001f mov di, bx
0021 mov word ptr [bp - 2], es
0024 test byte ptr es:[bx + 0x24], 0x20
0029 je 0xf086
002b mov al, byte ptr es:[di + 0x20]
002f sub ah, ah
0031 mov word ptr [bp - 0xe], ax
0034 push si
0035 nop 
0036 push cs
0037 call 0xe3a8 ; _win_LockWin
003a add sp, 2
003d mov ax, si
003f sub al, al
0041 mov word ptr [bp - 6], ax
0044 mov word ptr [bp - 8], 0
0049 mov bx, si
004b sar bx, 8
004e shl bx, 2
0051 les bx, ptr [bx - 0x3166]
0055 mov word ptr [bp - 0xc], bx
0058 mov word ptr [bp - 0xa], es
005b cmp word ptr es:[bx + 0xc], 0
0060 jle 0xf07d
0062 mov ax, bx
0064 mov dx, es
0066 add ax, 0x2c
0069 mov word ptr [bp - 4], ax
006c mov word ptr [bp - 2], dx
006f mov di, word ptr [bp - 6]
0072 mov si, word ptr [bp - 8]
0075 mov al, byte ptr [bp - 0xe]
0078 les bx, ptr [bp - 4]
007b les bx, ptr es:[bx]
007e cmp byte ptr es:[bx + 0x20], al
0082 jne 0xf06b
0084 push 0
0086 push di
0087 nop 
0088 push cs
0089 call 0xed08 ; _win_SetObjSelectedStateI
008c add sp, 4
008f add word ptr [bp - 4], 4
0093 inc di
0094 inc si
0095 les bx, ptr [bp - 0xc]
0098 cmp word ptr es:[bx + 0xc], si
009c jg 0xf051
009e mov si, word ptr [bp + 6]
00a1 push si
00a2 nop 
00a3 push cs
00a4 call 0xe3a4 ; _win_UnlockWin
00a7 add sp, 2
00aa push 0
00ac push si
00ad nop 
00ae push cs
00af call 0xed08 ; _win_SetObjSelectedStateI
00b2 add sp, 4
00b5 push si
00b6 nop 
00b7 push cs
00b8 call 0xe3a4 ; _win_UnlockWin
00bb add sp, 2
00be pop si
00bf pop di
00c0 leave 
00c1 retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far * far win_ObjAddr(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetObjSelectedState', 'offset': 61012, 'source': None, 'size': 195}
- {'symbol': '_win_MakeObjSelected', 'offset': 61208, 'source': None, 'size': 194}
- {'symbol': '_win_SetGroupSelectedState', 'offset': 61600, 'source': None, 'size': 133}
- {'symbol': '_win_SetGroupSelectedObj', 'offset': 61734, 'source': None, 'size': 141}

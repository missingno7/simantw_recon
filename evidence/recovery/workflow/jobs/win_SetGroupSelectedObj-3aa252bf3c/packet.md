# Recovery task _win_SetGroupSelectedObj

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 141 bytes.

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
0016 mov word ptr [bp - 2], ax
0019 mov word ptr [bp - 8], 0
001e mov bx, si
0020 sar bx, 8
0023 shl bx, 2
0026 les bx, ptr [bx - 0x3166]
002a mov di, bx
002c mov word ptr [bp - 0xa], es
002f cmp word ptr es:[bx + 0xc], 0
0034 jle 0xf1a4
0036 mov ax, di
0038 mov dx, es
003a add ax, 0x2c
003d mov word ptr [bp - 6], ax
0040 mov word ptr [bp - 4], dx
0043 mov si, word ptr [bp - 2]
0046 mov word ptr [bp - 0xc], di
0049 mov di, word ptr [bp - 8]
004c mov al, byte ptr [bp + 8]
004f les bx, ptr [bp - 6]
0052 les bx, ptr es:[bx]
0055 cmp byte ptr es:[bx + 0x20], al
0059 jne 0xf195
005b cmp word ptr [bp + 0xa], si
005e jne 0xf18a
0060 push 1
0062 jmp 0xf18c
0064 push 0
0066 push si
0067 nop 
0068 push cs
0069 call 0xed08 ; _win_SetObjSelectedStateI
006c add sp, 4
006f add word ptr [bp - 6], 4
0073 inc si
0074 inc di
0075 les bx, ptr [bp - 0xc]
0078 cmp word ptr es:[bx + 0xc], di
007c jg 0xf172
007e push word ptr [bp + 6]
0081 nop 
0082 push cs
0083 call 0xe3a4 ; _win_UnlockWin
0086 add sp, 2
0089 pop si
008a pop di
008b leave 
008c retf 
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

- {'symbol': '_win_MakeObjUnselected', 'offset': 61404, 'source': None, 'size': 194}
- {'symbol': '_win_SetGroupSelectedState', 'offset': 61600, 'source': None, 'size': 133}
- {'symbol': '_win_MakeGroupSelected', 'offset': 61876, 'source': None, 'size': 132}
- {'symbol': '_win_MakeGroupUnselected', 'offset': 62008, 'source': None, 'size': 132}

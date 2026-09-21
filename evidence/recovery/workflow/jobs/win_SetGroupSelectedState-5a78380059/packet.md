# Recovery task _win_SetGroupSelectedState

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 133 bytes.

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
0019 mov word ptr [bp - 8], 0
001e mov bx, si
0020 sar bx, 8
0023 shl bx, 2
0026 les bx, ptr [bx - 0x3166]
002a mov di, bx
002c mov word ptr [bp - 0xa], es
002f cmp word ptr es:[bx + 0xc], 0
0034 jle 0xf116
0036 mov ax, di
0038 mov dx, es
003a add ax, 0x2c
003d mov word ptr [bp - 4], ax
0040 mov word ptr [bp - 2], dx
0043 mov si, word ptr [bp - 6]
0046 mov word ptr [bp - 0xc], di
0049 mov di, word ptr [bp - 8]
004c mov al, byte ptr [bp + 8]
004f les bx, ptr [bp - 4]
0052 les bx, ptr es:[bx]
0055 cmp byte ptr es:[bx + 0x20], al
0059 jne 0xf107
005b push word ptr [bp + 0xa]
005e push si
005f nop 
0060 push cs
0061 call 0xed08 ; _win_SetObjSelectedStateI
0064 add sp, 4
0067 add word ptr [bp - 4], 4
006b inc si
006c inc di
006d les bx, ptr [bp - 0xc]
0070 cmp word ptr es:[bx + 0xc], di
0074 jg 0xf0ec
0076 push word ptr [bp + 6]
0079 nop 
007a push cs
007b call 0xe3a4 ; _win_UnlockWin
007e add sp, 2
0081 pop si
0082 pop di
0083 leave 
0084 retf 
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

- {'symbol': '_win_MakeObjSelected', 'offset': 61208, 'source': None, 'size': 194}
- {'symbol': '_win_MakeObjUnselected', 'offset': 61404, 'source': None, 'size': 194}
- {'symbol': '_win_SetGroupSelectedObj', 'offset': 61734, 'source': None, 'size': 141}
- {'symbol': '_win_MakeGroupSelected', 'offset': 61876, 'source': None, 'size': 132}

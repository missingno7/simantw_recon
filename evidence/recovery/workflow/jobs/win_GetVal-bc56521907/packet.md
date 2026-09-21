# Recovery task _win_GetVal

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 138 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov ax, si
000b sub al, al
000d mov word ptr [bp - 2], ax
0010 mov al, ah
0012 cwde 
0013 mov es, word ptr [0xc6dc]
0017 cmp ax, word ptr es:[0x78de]
001c jl 0xe50d
001e cmp word ptr [bp - 2], 0x2800
0023 jl 0xe56b
0025 push word ptr [bp - 2]
0028 nop 
0029 push cs
002a call 0xe3a8 ; _win_LockWin
002d add sp, 2
0030 mov ax, si
0032 sub ah, ah
0034 mov bx, word ptr [bp - 2]
0037 sar bx, 8
003a shl bx, 2
003d les bx, ptr [bx - 0x3166]
0041 cmp word ptr es:[bx + 0xc], ax
0045 jle 0xe560
0047 add bx, 0x2c
004a mov di, ax
004c shl di, 2
004f mov ax, word ptr es:[bx + di]
0052 mov dx, word ptr es:[bx + di + 2]
0056 mov si, ax
0058 mov word ptr [bp - 0xa], dx
005b push word ptr [bp - 2]
005e nop 
005f push cs
0060 call 0xe3a4 ; _win_UnlockWin
0063 add sp, 2
0066 mov es, word ptr [bp - 0xa]
0069 mov bx, word ptr [bp + 8]
006c shl bx, 1
006e add bx, si
0070 mov ax, word ptr es:[bx]
0073 pop si
0074 pop di
0075 leave 
0076 retf 
0077 nop 
0078 push word ptr [bp - 2]
007b nop 
007c push cs
007d call 0xe3a4 ; _win_UnlockWin
0080 add sp, 2
0083 mov ax, 0x8000
0086 pop si
0087 pop di
0088 leave 
0089 retf 
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

- {'symbol': '_win_StringSize', 'offset': 58336, 'source': 'src/recovered/win_StringSize.c', 'size': 37}
- {'symbol': '_win_AutoSize', 'offset': 58374, 'source': None, 'size': None}
- {'symbol': '_win_GetArg', 'offset': 58738, 'source': None, 'size': 60}
- {'symbol': '__win_CalcObjElement', 'offset': 58798, 'source': None, 'size': None}

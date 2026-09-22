# Recovery task __win_CalcObjElement

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 307 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 les bx, ptr [bp + 6]
0009 add bx, 0x18
000c mov si, word ptr [bp + 0xa]
000f shl si, 1
0011 mov word ptr [bp - 0x12], si
0014 mov ax, word ptr es:[bx + si]
0017 cmp ax, 5
001a ja 0xe5de
001c shl ax, 1
001e xchg bx, ax
001f jmp word ptr cs:[bx - 0x1a2e]
0024 dw offset 0xe5e6
0026 dw offset 0xe5ec
0028 dw offset 0xe5f0
002a dw offset 0xe5f6
002c dw offset 0xe5fc
002e dw offset 0xe686
0030 mov ax, 1
0033 pop si
0034 pop di
0035 leave 
0036 retf 
0037 nop 
0038 xor bx, bx
003a jmp 0xe6c2
003d nop 
003e xor si, si
0040 jmp 0xe5ff
0042 mov si, 1
0045 jmp 0xe5ff
0047 nop 
0048 mov si, 2
004b jmp 0xe5ff
004d nop 
004e mov si, 3
0051 mov bx, word ptr [bp + 6]
0054 add bx, 0x10
0057 add bx, word ptr [bp - 0x12]
005a mov di, word ptr es:[bx]
005d mov ax, di
005f sub al, al
0061 mov word ptr [bp - 4], ax
0064 mov al, ah
0066 cwde 
0067 mov es, word ptr [0xc6dc]
006b cmp ax, word ptr es:[0x78de]
0070 jl 0xe627
0072 cmp word ptr [bp - 4], 0x2800
0077 jl 0xe681
0079 push word ptr [bp - 4]
007c nop 
007d push cs
007e call 0xe3a8 ; _win_LockWin
0081 add sp, 2
0084 mov ax, di
0086 sub ah, ah
0088 mov bx, word ptr [bp - 4]
008b sar bx, 8
008e shl bx, 2
0091 les bx, ptr [bx - 0x3166]
0095 cmp word ptr es:[bx + 0xc], ax
0099 jle 0xe676
009b shl ax, 2
009e add bx, 0x2c
00a1 add bx, ax
00a3 mov ax, word ptr es:[bx]
00a6 mov dx, word ptr es:[bx + 2]
00aa mov di, ax
00ac mov word ptr [bp - 0xe], dx
00af push word ptr [bp - 4]
00b2 nop 
00b3 push cs
00b4 call 0xe3a4 ; _win_UnlockWin
00b7 add sp, 2
00ba mov es, word ptr [bp - 0xe]
00bd shl si, 1
00bf add si, di
00c1 mov ax, word ptr es:[si]
00c4 mov bx, ax
00c6 jmp 0xe6c2
00c8 push word ptr [bp - 4]
00cb nop 
00cc push cs
00cd call 0xe3a4 ; _win_UnlockWin
00d0 add sp, 2
00d3 mov bx, 0x8000
00d6 jmp 0xe6c2
00d8 mov bx, word ptr [bp + 6]
00db add bx, 0x10
00de mov ax, word ptr es:[bx + si]
00e1 mov word ptr [bp - 6], ax
00e4 mov bx, word ptr [bp + 0xc]
00e7 mov ax, bx
00e9 mov al, ah
00eb cwde 
00ec mov es, word ptr [0xc6dc]
00f0 cmp word ptr es:[0x78de], ax
00f5 jg 0xe6ab
00f7 cmp bx, 0x2800
00fb jl 0xe681
00fd mov ax, word ptr [bp - 6]
0100 shl ax, 1
0102 sar bx, 8
0105 shl bx, 2
0108 les bx, ptr [bx - 0x3166]
010c add bx, 0x10
010f add bx, ax
0111 mov bx, word ptr es:[bx]
0114 cmp bx, 0x8000
0118 je 0xe6da
011a mov ax, bx
011c les bx, ptr [bp + 6]
011f add bx, 8
0122 mov si, word ptr [bp - 0x12]
0125 add ax, word ptr es:[bx + si]
0128 pop si
0129 pop di
012a leave 
012b retf 
012c mov ax, 0x8000
012f pop si
0130 pop di
0131 leave 
0132 retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_GetVal', 'offset': 58600, 'source': None, 'size': 138}
- {'symbol': '_win_GetArg', 'offset': 58738, 'source': None, 'size': 60}
- {'symbol': '_win_Recalc', 'offset': 59106, 'source': None, 'size': 738}
- {'symbol': '_win_SetObjSelectableState', 'offset': 59844, 'source': 'src/recovered/win_SetObjSelectableState.c', 'size': 62}

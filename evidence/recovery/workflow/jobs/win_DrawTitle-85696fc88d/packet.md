# Recovery task _win_DrawTitle

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 193 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 sub ax, ax
000b mov word ptr [bp - 0xe], ax
000e mov word ptr [bp - 0x10], ax
0011 push di
0012 nop 
0013 push cs
0014 call 0xe3a8 ; _win_LockWin
0017 add sp, 2
001a mov bx, di
001c sar bx, 8
001f shl bx, 2
0022 mov ax, word ptr [bx - 0x3166]
0026 mov dx, word ptr [bx - 0x3164]
002a mov si, ax
002c mov es, dx
002e mov bx, si
0030 cmp word ptr es:[bx + 0xc], 0
0035 jle 0xbd2d
0037 add ax, 0x2c
003a mov cx, ax
003c mov word ptr [bp - 6], dx
003f mov ax, word ptr es:[si + 0xc]
0043 mov word ptr [bp - 0xa], ax
0046 mov di, cx
0048 mov es, word ptr [bp - 6]
004b lds si, ptr es:[di]
004e mov al, byte ptr [si + 0x21]
0051 cwde 
0052 sub ax, 0xc
0055 je 0xbcf6
0057 sub ax, 6
005a je 0xbd02
005c jmp 0xbd23
005e lea ax, [si + 0x2a]
0061 mov word ptr [bp - 0x10], ax
0064 mov word ptr [bp - 0xe], ds
0067 jmp 0xbd23
0069 nop 
006a mov ax, word ptr [si + 0x2a]
006d mov dx, word ptr [si + 0x2c]
0070 mov cx, ax
0072 mov word ptr [bp - 2], dx
0075 or dx, ax
0077 je 0xbd23
0079 mov es, word ptr [bp - 2]
007c mov bx, ax
007e mov ax, word ptr es:[bx]
0081 mov dx, word ptr es:[bx + 2]
0085 mov word ptr [bp - 0x10], ax
0088 mov word ptr [bp - 0xe], dx
008b add di, 4
008e dec word ptr [bp - 0xa]
0091 jne 0xbce0
0093 push ss
0094 pop ds
0095 mov si, word ptr [bp + 6]
0098 push si
0099 nop 
009a push cs
009b call 0xe3a4 ; _win_UnlockWin
009e add sp, 2
00a1 mov ax, word ptr [bp - 0xe]
00a4 or ax, word ptr [bp - 0x10]
00a7 je 0xbd55
00a9 sar si, 8
00ac shl si, 1
00ae push word ptr [si - 0x435a]
00b2 push word ptr [bp - 0xe]
00b5 push word ptr [bp - 0x10]
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 37}}]
00bd pop si
00be pop di
00bf leave 
00c0 retf 
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

- {'symbol': '_win_DrawWinIcons', 'offset': 48020, 'source': 'src/recovered/win_DrawWinIcons.c', 'size': 1}
- {'symbol': '_win_DrawWindow', 'offset': 48022, 'source': None, 'size': 256}
- {'symbol': '_win_DrawBitMap', 'offset': 48474, 'source': None, 'size': 214}
- {'symbol': '_win_DrawBitMapAtObj', 'offset': 48688, 'source': None, 'size': 64}

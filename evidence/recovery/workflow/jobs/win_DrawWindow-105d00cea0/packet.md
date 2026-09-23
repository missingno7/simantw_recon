# Recovery task _win_DrawWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 256 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push si
000a nop 
000b push cs
000c call 0xe3a6 ; _win_LockWinHigh
000f add sp, 2
0012 mov bx, si
0014 sar bx, 8
0017 shl bx, 2
001a mov word ptr [bp - 0x12], bx
001d les bx, ptr [bx - 0x3166]
0021 mov di, bx
0023 mov word ptr [bp - 0xc], es
0026 test byte ptr es:[bx + 0x1c], 0x20
002b je 0xbbc6
002d jmp 0xbc89
0030 mov bx, word ptr [bp - 0x12]
0033 add bx, 0x77b2
0037 mov es, word ptr [0xc6ca]
003b mov word ptr [bp - 0x16], bx
003e mov word ptr [bp - 0x14], es
0041 mov ax, word ptr es:[bx + 2]
0045 or ax, word ptr es:[bx]
0048 je 0xbbe8
004a push 1
004c lcall es:[bx]
004f add sp, 2
0052 mov word ptr [bp - 6], 1
0057 mov es, word ptr [bp - 0xc]
005a mov ax, word ptr es:[di + 0xc]
005e mov word ptr [bp - 0x10], ax
0061 cmp ax, 1
0064 jle 0xbc75
0066 mov ax, di
0068 mov dx, es
006a add ax, 0x30
006d mov word ptr [bp - 0xa], ax
0070 mov word ptr [bp - 8], dx
0073 mov ax, di
0075 add ax, 0x2c
0078 mov word ptr [bp - 0xe], di
007b cmp word ptr [0xcd84], 0 ; _updateRgn
0080 je 0xbc2f
0082 push word ptr [0xcd84] ; _updateRgn
0086 les bx, ptr [bp - 0xa]
0089 push word ptr es:[bx + 2]
008d push word ptr es:[bx]
0090 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 181}}]
0095 or ax, ax
0097 je 0xbc46
0099 les bx, ptr [bp - 0xa]
009c les bx, ptr es:[bx]
009f test byte ptr es:[bx + 0x24], 1
00a4 je 0xbc46
00a6 push es
00a7 push bx
00a8 nop 
00a9 push cs
00aa call 0xb710 ; _win_DrawObjectI
00ad add sp, 4
00b0 cmp word ptr [bp - 6], 0
00b4 jne 0xbc63
00b6 les bx, ptr [bp - 0xe]
00b9 mov ax, word ptr es:[bx + 0x2c]
00bd mov dx, word ptr es:[bx + 0x2e]
00c1 push ds
00c2 mov di, bx
00c4 mov si, ax
00c6 mov ds, dx
00c8 movsw word ptr es:[di], word ptr [si]
00c9 movsw word ptr es:[di], word ptr [si]
00ca movsw word ptr es:[di], word ptr [si]
00cb movsw word ptr es:[di], word ptr [si]
00cc pop ds
00cd add word ptr [bp - 0xa], 4
00d1 mov ax, word ptr [bp - 0x10]
00d4 inc word ptr [bp - 6]
00d7 cmp word ptr [bp - 6], ax
00da jl 0xbc11
00dc mov si, word ptr [bp + 6]
00df les bx, ptr [bp - 0x16]
00e2 mov ax, word ptr es:[bx + 2]
00e6 or ax, word ptr es:[bx]
00e9 je 0xbc89
00eb push 2
00ed lcall es:[bx]
00f0 add sp, 2
00f3 push si
00f4 nop 
00f5 push cs
00f6 call 0xe3a4 ; _win_UnlockWin
00f9 add sp, 2
00fc pop si
00fd pop di
00fe leave 
00ff retf 
```

## Known declaration examples

- `extern void far win_DrawObjectI(void far *object);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawObjectNum', 'offset': 47972, 'source': 'src/recovered/win_DrawObjectNum.c', 'size': 47}
- {'symbol': '_win_DrawWinIcons', 'offset': 48020, 'source': 'src/recovered/win_DrawWinIcons.c', 'size': 1}
- {'symbol': '_win_DrawTitle', 'offset': 48280, 'source': None, 'size': 193}
- {'symbol': '_win_DrawBitMap', 'offset': 48474, 'source': None, 'size': 214}

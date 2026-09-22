# Recovery task _win_Swap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 359 bytes.

```asm
0000 enter 0x20, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 6]
0009 sar bx, 8
000c mov word ptr [bp - 0x20], bx
000f shl bx, 1
0011 add bx, 0xbca6
0015 mov word ptr [bp - 0x1e], bx
0018 cmp word ptr [bx], 0
001b jne 0xd454
001d jmp 0xd597
0020 push word ptr [bp + 6]
0023 nop 
0024 push cs
0025 call 0xe3a8 ; _win_LockWin
0028 add sp, 2
002b mov bx, word ptr [bp - 0x20]
002e shl bx, 2
0031 mov ax, word ptr [bx - 0x3166]
0035 mov dx, word ptr [bx - 0x3164]
0039 mov word ptr [bp - 8], ax
003c mov word ptr [bp - 6], dx
003f mov es, dx
0041 mov bx, ax
0043 mov ax, word ptr es:[bx + 0x2c]
0047 mov dx, word ptr es:[bx + 0x2e]
004b add ax, 8
004e push ds
004f lea di, [bp - 0x14]
0052 mov si, ax
0054 push ss
0055 pop es
0056 mov ds, dx
0058 movsw word ptr es:[di], word ptr [si]
0059 movsw word ptr es:[di], word ptr [si]
005a movsw word ptr es:[di], word ptr [si]
005b movsw word ptr es:[di], word ptr [si]
005c pop ds
005d mov ax, word ptr [bp - 8]
0060 mov dx, word ptr [bp - 6]
0063 push ds
0064 lea di, [bp - 0x1c]
0067 mov si, ax
0069 mov ds, dx
006b movsw word ptr es:[di], word ptr [si]
006c movsw word ptr es:[di], word ptr [si]
006d movsw word ptr es:[di], word ptr [si]
006e movsw word ptr es:[di], word ptr [si]
006f pop ds
0070 mov es, dx
0072 mov bx, ax
0074 and byte ptr es:[bx + 0x1d], 0xfd
0079 push word ptr [bp + 6]
007c nop 
007d push cs
007e call 0xe3a4 ; _win_UnlockWin
0081 add sp, 2
0084 push word ptr [bp + 8]
0087 nop 
0088 push cs
0089 call 0xe3a8 ; _win_LockWin
008c add sp, 2
008f mov bx, word ptr [bp + 8]
0092 sar bx, 8
0095 shl bx, 2
0098 les bx, ptr [bx - 0x3166]
009c mov word ptr [bp - 4], bx
009f mov word ptr [bp - 2], es
00a2 mov ax, word ptr es:[bx + 0x2c]
00a6 mov dx, word ptr es:[bx + 0x2e]
00aa mov word ptr [bp - 0xc], ax
00ad mov word ptr [bp - 0xa], dx
00b0 mov es, dx
00b2 mov bx, ax
00b4 mov ax, word ptr [bp - 0x14]
00b7 mov word ptr es:[bx + 8], ax
00bb mov ax, word ptr [bp - 0x12]
00be mov word ptr es:[bx + 0xa], ax
00c2 push es
00c3 lea si, [bp - 0x1c]
00c6 les di, ptr [bp - 4]
00c9 movsw word ptr es:[di], word ptr [si]
00ca movsw word ptr es:[di], word ptr [si]
00cb movsw word ptr es:[di], word ptr [si]
00cc movsw word ptr es:[di], word ptr [si]
00cd pop es
00ce mov ax, word ptr [bp - 4]
00d1 mov dx, word ptr [bp - 2]
00d4 push ds
00d5 mov di, bx
00d7 mov si, ax
00d9 mov ds, dx
00db movsw word ptr es:[di], word ptr [si]
00dc movsw word ptr es:[di], word ptr [si]
00dd movsw word ptr es:[di], word ptr [si]
00de movsw word ptr es:[di], word ptr [si]
00df pop ds
00e0 mov es, dx
00e2 mov bx, ax
00e4 mov cx, word ptr [bp + 0xc]
00e7 mov word ptr es:[bx + 0x10], cx
00eb mov cx, word ptr [bp + 0xe]
00ee mov word ptr es:[bx + 0x12], cx
00f2 mov cx, word ptr [bp + 0x10]
00f5 mov word ptr es:[bx + 0x14], cx
00f9 mov cx, word ptr [bp + 0x12]
00fc mov word ptr es:[bx + 0x16], cx
0100 push word ptr [bp + 8]
0103 nop 
0104 push cs
0105 call 0xe6e2 ; _win_Recalc
0108 add sp, 2
010b les bx, ptr [bp - 4]
010e or byte ptr es:[bx + 0x1d], 2
0113 push word ptr [bp + 8]
0116 nop 
0117 push cs
0118 call 0xe3a4 ; _win_UnlockWin
011b add sp, 2
011e mov bx, word ptr [bp - 0x1e]
0121 push word ptr [bx]
0123 push ds
0124 push 0xbdd4
0127 push word ptr [bp + 8]
012a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 299, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 26}}]
012f mov bx, word ptr [bp - 0x1e]
0132 mov ax, word ptr [bx]
0134 mov si, word ptr [bp + 8]
0137 sar si, 8
013a shl si, 1
013c mov word ptr [si - 0x435a], ax
0140 mov word ptr [bx], 0
0144 push ax
0145 push 5
0147 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 328, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 42}}]
014c mov bx, word ptr [bp + 8]
014f sar bx, 8
0152 shl bx, 1
0154 push word ptr [bx - 0x435a]
0158 push 0
015a push 0
015c push 1
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0163 pop si
0164 pop di
0165 leave 
0166 retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_Recalc(int window);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far win_Recalc(int window);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetObjFormatStr', 'offset': 54004, 'source': None, 'size': 297}
- {'symbol': '_win_ToTop', 'offset': 54302, 'source': 'src/recovered/win_ToTop.c', 'size': 22}
- {'symbol': '_win_SetWinDrawHook', 'offset': 54684, 'source': 'src/recovered/win_SetWinDrawHook.c', 'size': 34}
- {'symbol': '_win_SetObjBitmap', 'offset': 54718, 'source': None, 'size': 123}

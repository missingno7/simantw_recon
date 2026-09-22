# Recovery task _win_GetEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 420 bytes.

```asm
0000 enter 0x28, 0
0004 push di
0005 push si
0006 xor si, si
0008 lea ax, [bp - 0x24]
000b push ss
000c push ax
000d push si
000e push si
000f push si
0010 push 1
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0017 or ax, ax
0019 je 0xd1c0
001b or si, si
001d jne 0xd1c0
001f cmp word ptr [bp - 0x22], 0x201
0024 je 0xd17d
0026 cmp word ptr [bp - 0x22], 0x202
002b jne 0xd180
002d mov si, 1
0030 cmp word ptr [bp - 0x22], 0x100
0035 jne 0xd196
0037 cmp word ptr [bp - 0x20], 0x20
003b je 0xd193
003d cmp word ptr [bp - 0x20], 0x2d
0041 jne 0xd196
0043 mov si, 1
0046 lea ax, [bp - 0x24]
0049 push ss
004a push ax
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 113}}]
0050 lea ax, [bp - 0x24]
0053 push ss
0054 push ax
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 114}}]
005a lea ax, [bp - 0x24]
005d push ss
005e push ax
005f push 0
0061 push 0
0063 push 0
0065 push 1
0067 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 104, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
006c or ax, ax
006e jne 0xd16b
0070 mov word ptr [bp - 0xe], si
0073 or si, si
0075 jne 0xd1ca
0077 jmp 0xd2ed
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyGetCapture
007f mov di, ax
0081 les bx, ptr [bp + 6]
0084 mov word ptr es:[bx + 0xc], 0
008a or di, di
008c jne 0xd221
008e push word ptr [0xcd78] ; _rootWnd
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 229}}]
0097 mov si, ax
0099 or si, si
009b je 0xd221
009d push si
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
00a3 or ax, ax
00a5 jne 0xd205
00a7 push si
00a8 push 2
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 171, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
00af mov si, ax
00b1 or si, si
00b3 jne 0xd1ed
00b5 or si, si
00b7 je 0xd21f
00b9 push si
00ba push 4
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
00c1 or ax, ax
00c3 je 0xd21f
00c5 push si
00c6 push 4
00c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
00cd mov si, ax
00cf mov di, si
00d1 or di, di
00d3 jne 0xd228
00d5 jmp 0xd2ed
00d8 push di
00d9 push ds
00da push 0xbdc4
00dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
00e2 mov word ptr [bp - 0xc], ax
00e5 or ax, ax
00e7 jg 0xd23c
00e9 jmp 0xd2ed
00ec mov ax, word ptr [bp + 6]
00ef mov dx, word ptr [bp + 8]
00f2 add ax, 8
00f5 push dx
00f6 push ax
00f7 mov si, ax
00f9 mov word ptr [bp - 0x28], si
00fc mov word ptr [bp - 0x26], dx
00ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 17}}]
0104 push di
0105 push word ptr [bp - 0x26]
0108 push si
0109 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 266, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
010e mov bx, word ptr [bp - 0xc]
0111 sar bx, 8
0114 shl bx, 2
0117 les bx, ptr [bx - 0x3166]
011b mov si, bx
011d mov word ptr [bp - 0x10], es
0120 mov ax, word ptr es:[bx + 0xc]
0124 dec ax
0125 mov word ptr [bp - 0xa], ax
0128 or ax, ax
012a jl 0xd2d2
012c shl ax, 2
012f add ax, si
0131 add ax, 0x2c
0134 mov dx, es
0136 mov cx, ax
0138 mov word ptr [bp - 6], dx
013b mov word ptr [bp - 8], cx
013e mov word ptr [bp - 0x12], si
0141 mov di, word ptr [bp - 0xa]
0144 mov si, ax
0146 mov es, word ptr [bp - 6]
0149 les bx, ptr es:[si]
014c mov word ptr [bp - 4], bx
014f mov word ptr [bp - 2], es
0152 test byte ptr es:[bx + 0x24], 2
0157 je 0xd2c2
0159 push es
015a push bx
015b mov ax, word ptr [bp + 6]
015e mov dx, word ptr [bp + 8]
0161 add ax, 8
0164 push dx
0165 push ax
0166 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 361, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PointInRect
016b add sp, 8
016e or ax, ax
0170 jne 0xd2ca
0172 sub si, 4
0175 dec di
0176 jns 0xd296
0178 jmp 0xd2d2
017a mov bx, di
017c or bx, word ptr [bp - 0xc]
017f jmp 0xd2d5
0181 nop 
0182 mov bx, word ptr [bp - 0xc]
0185 les si, ptr [bp + 6]
0188 mov word ptr es:[si + 0xc], bx
018c or bx, bx
018e jne 0xd2ed
0190 mov al, byte ptr [bp - 0xb]
0193 cwde 
0194 or ah, 0xff
0197 mov bx, si
0199 mov word ptr es:[bx + 0xc], ax
019d mov ax, word ptr [bp - 0xe]
01a0 pop si
01a1 pop di
01a2 leave 
01a3 retf 
```

## Known declaration examples

- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/wf_win_IsPointInObj-538ab6cada.c
- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_FindObject', 'offset': 53424, 'source': None, 'size': 101}
- {'symbol': '_UpdateAllWindows', 'offset': 53526, 'source': 'src/recovered/wf_UpdateAllWindows-97a1ff92dc.c', 'size': 58}
- {'symbol': '_win_SetObjFormatStr', 'offset': 54004, 'source': None, 'size': 297}
- {'symbol': '_win_ToTop', 'offset': 54302, 'source': 'src/recovered/win_ToTop.c', 'size': 22}

# Recovery task _win_DrawExamineWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 395 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 test byte ptr [bp + 6], 2
000a jne 0x69cf
000c jmp 0x6b47
000f mov dx, word ptr [0xcb6c]
0013 mov cx, word ptr [0xcb6e]
0017 mov si, word ptr [0xcb70]
001b cmp si, 1
001e jg 0x69ee
0020 mov bx, dx
0022 shl bx, 6
0025 add bx, cx
0027 mov al, byte ptr [bx + 0x68e8]
002b jmp 0x6a0b
002d nop 
002e cmp si, 2
0031 jne 0x6a00
0033 mov bx, dx
0035 shl bx, 6
0038 add bx, cx
003a mov al, byte ptr [bx - 0x7718]
003e jmp 0x6a0b
0040 mov bx, dx
0042 shl bx, 6
0045 add bx, cx
0047 mov al, byte ptr [bx - 0x6718]
004b sub ah, ah
004d mov di, ax
004f and ax, 0x78
0052 sar ax, 3
0055 mov word ptr [bp - 4], ax
0058 or ax, ax
005a jne 0x6a30
005c mov bx, di
005e and bx, 7
0061 shl bx, 2
0064 mov es, word ptr [0xc23e]
0068 les di, ptr es:[0x8098]
006d jmp 0x6a3e
006f nop 
0070 mov es, word ptr [0xc240]
0074 les bx, ptr es:[0x8074]
0079 mov di, ax
007b shl di, 2
007e mov ax, word ptr es:[bx + di]
0081 mov dx, word ptr es:[bx + di + 2]
0085 mov si, ax
0087 mov word ptr [bp - 6], dx
008a push 2
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0091 add sp, 2
0094 push word ptr [bp - 6]
0097 push si
0098 push 0x1d02
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
00a0 add sp, 6
00a3 mov ax, word ptr [0xcb70]
00a6 dec ax
00a7 je 0x6a76
00a9 dec ax
00aa je 0x6a9c
00ac dec ax
00ad je 0x6acc
00af mov di, word ptr [bp - 2]
00b2 jmp 0x6afe
00b5 nop 
00b6 push word ptr [0xcb6e]
00ba push word ptr [0xcb6c]
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 193, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
00c3 add sp, 4
00c6 mov si, ax
00c8 or si, si
00ca jl 0x6afc
00cc mov es, word ptr [0xc242]
00d0 mov di, word ptr es:[si + 0x2b78]
00d5 and di, 0xff
00d9 jmp 0x6afe
00db nop 
00dc mov bx, word ptr [0xcb6e]
00e0 mov di, word ptr [0xcb6c]
00e4 shl di, 6
00e7 mov al, byte ptr [bx + di - 0x7718]
00eb sub ah, ah
00ed push ax
00ee push bx
00ef push word ptr [0xcb6c]
00f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
00f8 add sp, 6
00fb mov si, ax
00fd or si, si
00ff jl 0x6afc
0101 mov es, word ptr [0xc242]
0105 mov di, word ptr es:[si + 0x3b22]
010a jmp 0x6a95
010c mov bx, word ptr [0xcb6e]
0110 mov di, word ptr [0xcb6c]
0114 shl di, 6
0117 mov al, byte ptr [bx + di - 0x6718]
011b sub ah, ah
011d push ax
011e push bx
011f push word ptr [0xcb6c]
0123 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 294, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0128 add sp, 6
012b mov si, ax
012d or si, si
012f jl 0x6afc
0131 mov es, word ptr [0xc242]
0135 mov di, word ptr es:[si + 0x44f0]
013a jmp 0x6a95
013c xor di, di
013e mov es, word ptr [0xc244]
0142 les bx, ptr es:[0x78b2]
0147 shl di, 2
014a push word ptr es:[bx + di + 2]
014e push word ptr es:[bx + di]
0151 push 0x1d03
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
0159 add sp, 6
015c mov es, word ptr [0xc246]
0160 les bx, ptr es:[0x7892]
0165 mov si, word ptr [bp - 4]
0168 shl si, 2
016b push word ptr es:[bx + si + 2]
016f push word ptr es:[bx + si]
0172 push 0x1d04
0175 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 376, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
017a add sp, 6
017d push 0
017f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 386, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0184 add sp, 2
0187 pop si
0188 pop di
0189 leave 
018a retf 
```

## Known declaration examples

- `extern int far FindInAList(int x, int y);` — src/recovered/wf_tu_simant1_0000_DoSmells_10_scaffold-13ce956607.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int far FindInRList(int x, int y, int ant);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_9_scaffold-03367c8694.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_PrintfAtObj(int object, char far *format, ...);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EditScentMenu', 'offset': 26462, 'source': 'src/recovered/wf_EditScentMenu-abd185cb06.c', 'size': 103}
- {'symbol': '_EditToolsMenu', 'offset': 26566, 'source': None, 'size': 506}
- {'symbol': '_MagnifyMenu', 'offset': 27468, 'source': None, 'size': 471}
- {'symbol': '_AntMenu', 'offset': 27940, 'source': None, 'size': 232}

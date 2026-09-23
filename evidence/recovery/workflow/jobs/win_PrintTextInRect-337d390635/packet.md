# Recovery task _win_PrintTextInRect

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 438 bytes.

```asm
0000 enter 0xb0, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xa]
0009 mov es, word ptr [bp + 0xc]
000c mov di, word ptr es:[si + 4]
0010 sub di, word ptr es:[si]
0013 mov ax, word ptr es:[si + 2]
0017 mov word ptr [bp - 0x14], ax
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
001f mov word ptr [bp - 0x16], ax
0022 mov es, word ptr [bp + 0xc]
0025 mov ax, word ptr es:[si + 6]
0029 sub ax, word ptr es:[si + 2]
002d cdq 
002e idiv word ptr [bp - 0x16]
0031 mov word ptr [bp - 0x18], ax
0034 mov word ptr [bp - 0xe], 0
0039 les bx, ptr [bp + 6]
003c cmp byte ptr es:[bx], 0
0040 jne 0xbf17
0042 jmp 0xc084
0045 mov si, bx
0047 mov word ptr [bp - 0x12], di
004a mov ax, word ptr [bp - 0x18]
004d add ax, word ptr [bp + 0xe]
0050 cmp ax, word ptr [bp - 0xe]
0053 jg 0xbf2a
0055 jmp 0xc084
0058 mov ax, word ptr [bp + 8]
005b mov word ptr [bp - 0xa], si
005e mov word ptr [bp - 8], ax
0061 xor ax, ax
0063 mov word ptr [bp - 4], ax
0066 mov word ptr [bp - 0xc], ax
0069 mov word ptr [bp - 6], ax
006c mov word ptr [bp - 2], ax
006f mov word ptr [bp - 0x10], ax
0072 cmp word ptr [bp - 0x12], ax
0075 jle 0xbfbc
0077 mov word ptr [bp + 6], si
007a mov di, ax
007c mov si, ax
007e cmp word ptr [bp - 0x10], 0
0082 je 0xbf59
0084 jmp 0xc072
0087 les bx, ptr [bp - 0xa]
008a inc word ptr [bp - 0xa]
008d mov al, byte ptr es:[bx]
0090 cwde 
0091 mov word ptr [bp - 2], ax
0094 push ax
0095 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_CharWidth
009a add sp, 2
009d add si, ax
009f cmp si, word ptr [bp - 0x12]
00a2 jl 0xbf79
00a4 jmp 0xc069
00a7 mov ax, word ptr [bp - 2]
00aa cmp ax, 0x7d
00ad jne 0xbf84
00af jmp 0xc078
00b2 jbe 0xbf89
00b4 jmp 0xc069
00b7 cmp al, 0x28
00b9 jne 0xbf90
00bb jmp 0xc063
00be jle 0xbf95
00c0 jmp 0xc03c
00c3 or al, al
00c5 jne 0xbf9c
00c7 jmp 0xc05e
00ca sub al, 0xa
00cc jne 0xbfa3
00ce jmp 0xc05e
00d1 sub al, 3
00d3 jne 0xbfaa
00d5 jmp 0xc05e
00d8 sub al, 0x13
00da jne 0xbfb1
00dc jmp 0xc063
00df dec al
00e1 jne 0xbfb8
00e3 jmp 0xc078
00e6 jmp 0xc069
00e9 nop 
00ea mov di, word ptr [bp - 6]
00ed cmp word ptr [bp - 0xc], 0
00f1 jne 0xbfcb
00f3 lea ax, [di - 1]
00f6 mov word ptr [bp - 0xc], ax
00f9 mov ax, word ptr [bp + 0xe]
00fc cmp word ptr [bp - 0xe], ax
00ff jl 0xc00b
0101 mov ax, word ptr [bp - 0xc]
0104 inc ax
0105 mov word ptr [bp - 0x1a], ax
0108 push ax
0109 push word ptr [bp + 8]
010c push si
010d lea cx, [bp - 0xb0]
0111 push ss
0112 push cx
0113 mov di, ax
0115 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 280, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strncpy
011a add sp, 0xa
011d mov byte ptr [bp + di - 0xb0], 0
0122 lea ax, [bp - 0xb0]
0126 push ss
0127 push ax
0128 push word ptr [bp - 0x14]
012b les bx, ptr [bp + 0xa]
012e push word ptr es:[bx]
0131 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 308, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_PrintStr
0136 add sp, 8
0139 mov ds, word ptr [bp + 8]
013c add si, word ptr [bp - 0x1a]
013f cmp byte ptr [si], 0x20
0142 jne 0xc01c
0144 inc si
0145 cmp byte ptr [si], 0x20
0148 je 0xc016
014a cmp byte ptr [si], 0xa
014d je 0xc026
014f cmp byte ptr [si], 0xd
0152 jne 0xc027
0154 inc si
0155 mov ax, word ptr [bp - 0x16]
0158 add word ptr [bp - 0x14], ax
015b inc word ptr [bp - 0xe]
015e cmp byte ptr [si], 0
0161 jne 0xc07e
0163 push ss
0164 pop ds
0165 pop si
0166 pop di
0167 leave 
0168 retf 
0169 nop 
016a cmp al, 0x3f
016c je 0xc078
016e jg 0xc050
0170 sub al, 0x29
0172 je 0xc078
0174 sub al, 3
0176 jl 0xc069
0178 sub al, 2
017a jle 0xc078
017c jmp 0xc069
017e sub al, 0x5b
0180 je 0xc063
0182 sub al, 2
0184 je 0xc078
0186 sub al, 0x1e
0188 je 0xc063
018a jmp 0xc069
018c mov word ptr [bp - 0x10], 1
0191 lea ax, [di - 1]
0194 mov word ptr [bp - 0xc], ax
0197 inc di
0198 cmp word ptr [bp - 0x12], si
019b jle 0xc072
019d jmp 0xbf50
01a0 mov si, word ptr [bp + 6]
01a3 jmp 0xbfbf
01a6 mov word ptr [bp - 0xc], di
01a9 jmp 0xc069
01ab nop 
01ac push ss
01ad pop ds
01ae jmp 0xbf1c
01b1 nop 
01b2 pop si
01b3 pop di
01b4 leave 
01b5 retf 
```

## Known declaration examples

- `extern int far _font_CharWidth(int character, unsigned int lo, unsigned int hi);` — src/recovered/font_CharWidth.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawBitMapAtObj', 'offset': 48688, 'source': 'src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c', 'size': 64}
- {'symbol': '_win_DrawBitMapAtObjNum', 'offset': 48752, 'source': 'src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c', 'size': 98}
- {'symbol': '_win_PrintTextInObj', 'offset': 49288, 'source': 'src/recovered/win_PrintTextInObj.c', 'size': 41}
- {'symbol': '_MyGetTopWindow', 'offset': 49330, 'source': 'src/recovered/wf_MyGetTopWindow-8cee2c18ed.c', 'size': 79}

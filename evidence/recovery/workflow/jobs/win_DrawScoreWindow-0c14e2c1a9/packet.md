# Recovery task _win_DrawScoreWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 480 bytes.

```asm
0000 enter 0x68, 0
0004 push di
0005 push si
0006 test byte ptr [bp + 6], 2
000a jne 0x5ad9
000c jmp 0x5ca6
000f lea ax, [bp - 0x10]
0012 push ss
0013 push ax
0014 nop 
0015 push cs
0016 call 0x5530 ; _CalcScore
0019 add sp, 4
001c mov es, word ptr [0xbeee]
0020 mov word ptr es:[0x7898], ax
0024 mov word ptr es:[0x789a], dx
0029 push 4
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0030 add sp, 2
0033 mov bx, 0x80b4
0036 mov es, word ptr [0xbee6]
003a mov word ptr [bp - 0x64], bx
003d mov word ptr [bp - 0x62], es
0040 cmp word ptr es:[bx], 2
0044 jne 0x5b36
0046 mov di, 4
0049 lea si, [bp - 8]
004c push word ptr [si]
004e push ds
004f push 0x956
0052 lea ax, [di + 0x1802]
0056 push ax
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
005c add sp, 8
005f inc di
0060 add si, 2
0063 mov ax, bp
0065 cmp si, ax
0067 jb 0x5b16
0069 jmp 0x5b5d
006b nop 
006c mov si, 4
006f mov es, word ptr [0xbef0]
0073 les bx, ptr es:[0x7294]
0078 push word ptr es:[bx + 0x42]
007c push word ptr es:[bx + 0x40]
0080 lea ax, [si + 0x1802]
0084 push ax
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
008a add sp, 6
008d inc si
008e cmp si, 8
0091 jl 0x5b39
0093 push 4
0095 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
009a add sp, 2
009d les bx, ptr [bp - 0x64]
00a0 cmp word ptr es:[bx], 3
00a4 jne 0x5bac
00a6 mov es, word ptr [0xbef0]
00aa les bx, ptr es:[0x7294]
00af push word ptr es:[bx + 0x46]
00b3 push word ptr es:[bx + 0x44]
00b7 push 0x180a
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
00bf add sp, 6
00c2 mov es, word ptr [0xbef0]
00c6 les bx, ptr es:[0x7294]
00cb push word ptr es:[bx + 0x4a]
00cf push word ptr es:[bx + 0x48]
00d3 push 0x180b
00d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
00db add sp, 6
00de pop si
00df pop di
00e0 leave 
00e1 retf 
00e2 mov byte ptr [bp - 0x60], 0
00e6 mov es, word ptr [0xbef0]
00ea les bx, ptr es:[0x7294]
00ef mov si, word ptr es:[bx + 0x34]
00f3 mov cx, word ptr es:[bx + 0x36]
00f7 mov di, es
00f9 mov word ptr [bp - 0x68], si
00fc mov word ptr [bp - 0x66], cx
00ff push di
0100 lea si, [bp - 0x60]
0103 push ds
0104 les di, ptr [bp - 0x68]
0107 mov cx, 0xffff
010a xor ax, ax
010c repne scasb al, byte ptr es:[di]
010e not cx
0110 sub di, cx
0112 push cx
0113 xchg si, di
0115 push ds
0116 push es
0117 pop ds
0118 pop es
0119 mov cx, 0xffff
011c repne scasb al, byte ptr es:[di]
011e dec di
011f pop cx
0120 shr cx, 1
0122 rep movsw word ptr es:[di], word ptr [si]
0124 adc cx, cx
0126 rep movsb byte ptr es:[di], byte ptr [si]
0128 pop ds
0129 pop di
012a mov es, word ptr [0xbef2]
012e les si, ptr es:[0x7a4a]
0133 mov ax, bx
0135 mov cx, es
0137 les bx, ptr [bp - 0x64]
013a mov bx, word ptr es:[bx]
013d shl bx, 2
0140 mov es, cx
0142 mov cx, word ptr es:[bx + si]
0145 mov dx, word ptr es:[bx + si + 2]
0149 mov bx, ax
014b mov si, cx
014d push di
014e mov di, si
0150 lea si, [bp - 0x60]
0153 mov es, dx
0155 push ds
0156 mov cx, 0xffff
0159 xor ax, ax
015b repne scasb al, byte ptr es:[di]
015d not cx
015f sub di, cx
0161 push cx
0162 xchg si, di
0164 push ds
0165 push es
0166 pop ds
0167 pop es
0168 mov cx, 0xffff
016b repne scasb al, byte ptr es:[di]
016d dec di
016e pop cx
016f shr cx, 1
0171 rep movsw word ptr es:[di], word ptr [si]
0173 adc cx, cx
0175 rep movsb byte ptr es:[di], byte ptr [si]
0177 pop ds
0178 pop di
0179 mov es, di
017b mov si, word ptr es:[bx + 0x38]
017f mov cx, word ptr es:[bx + 0x3a]
0183 mov bx, cx
0185 mov di, si
0187 lea si, [bp - 0x60]
018a mov es, bx
018c push ds
018d mov cx, 0xffff
0190 repne scasb al, byte ptr es:[di]
0192 not cx
0194 sub di, cx
0196 mov bx, cx
0198 xchg si, di
019a push ds
019b push es
019c pop ds
019d pop es
019e mov cx, 0xffff
01a1 repne scasb al, byte ptr es:[di]
01a3 dec di
01a4 mov cx, bx
01a6 shr cx, 1
01a8 rep movsw word ptr es:[di], word ptr [si]
01aa adc cx, cx
01ac rep movsb byte ptr es:[di], byte ptr [si]
01ae pop ds
01af lea ax, [bp - 0x60]
01b2 push ss
01b3 push ax
01b4 push 0x180a
01b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 442, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
01bc add sp, 6
01bf mov es, word ptr [0xbeee]
01c3 push word ptr es:[0x789a]
01c8 push word ptr es:[0x7898]
01cd push ds
01ce push 0x95b
01d1 push 0x180b
01d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 471, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
01d9 add sp, 0xa
01dc pop si
01dd pop di
01de leave 
01df retf 
```

## Known declaration examples

- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoScenario', 'offset': 22936, 'source': 'src/recovered/wf_DoScenario-496dc7a0ac.c', 'size': 275}
- {'symbol': '_DoWinHelp', 'offset': 23212, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 30}
- {'symbol': '_ScoreDialog', 'offset': 23722, 'source': None, 'size': 244}
- {'symbol': '_DrawCastePopUp', 'offset': 23966, 'source': None, 'size': 814}

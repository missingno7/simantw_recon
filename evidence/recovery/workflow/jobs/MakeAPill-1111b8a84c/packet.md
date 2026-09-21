# Recovery task _MakeAPill

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 767 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 push 4
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
000d add sp, 2
0010 mov bx, 0x9b1e
0013 mov es, word ptr [0xc5a0]
0017 mov word ptr [bp - 4], bx
001a mov word ptr [bp - 2], es
001d mov word ptr es:[bx], ax
0020 or ax, ax
0022 je 0x5414
0024 dec ax
0025 jne 0x5404
0027 jmp 0x54c4
002a dec ax
002b jne 0x540a
002d jmp 0x5578
0030 dec ax
0031 jne 0x5410
0033 jmp 0x5628
0036 pop si
0037 pop di
0038 leave 
0039 retf 
003a push 0x80
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0042 add sp, 2
0045 mov es, word ptr [0xc5a4]
0049 mov word ptr es:[0x8a8c], ax
004d mov es, word ptr [0xc5a2]
0051 mov word ptr es:[0x8a8e], 0x3f
0058 mov di, word ptr es:[0x8a8e]
005d push di
005e mov si, ax
0060 push si
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0066 add sp, 4
0069 dec ax
006a jne 0x5494
006c les bx, ptr [bp - 4]
006f test byte ptr es:[bx], 1
0073 je 0x5470
0075 mov bx, si
0077 shl bx, 6
007a mov al, byte ptr [bx + di + 0x28e8]
007e sub ah, ah
0080 mov cx, ax
0082 mov ax, si
0084 mov dx, 6
0087 mov bx, dx
0089 cdq 
008a idiv bx
008c mov bx, dx
008e shl bx, 1
0090 mov es, word ptr [0xc5a6]
0094 jmp 0x548f
0096 mov bx, si
0098 shl bx, 6
009b mov al, byte ptr [bx + di + 0x28e8]
009f mov cx, ax
00a1 mov ax, di
00a3 mov dx, 6
00a6 mov bx, dx
00a8 cdq 
00a9 idiv bx
00ab mov bx, dx
00ad shl bx, 1
00af mov es, word ptr [0xc5a6]
00b3 sub ch, ch
00b5 mov word ptr es:[bx + 0x7c0e], cx
00ba mov es, word ptr [0xc5a2]
00be mov di, word ptr es:[0x8a8e]
00c3 push di
00c4 mov es, word ptr [0xc5a4]
00c8 mov si, word ptr es:[0x8a8c]
00cd push si
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
00d3 add sp, 4
00d6 dec ax
00d7 je 0x54b6
00d9 jmp 0x56d5
00dc mov bx, si
00de shl bx, 6
00e1 mov byte ptr [bx + di + 0x28e8], 0x6c
00e6 pop si
00e7 pop di
00e8 leave 
00e9 retf 
00ea mov es, word ptr [0xc5a4]
00ee mov word ptr es:[0x8a8c], 0
00f5 push 0x40
00f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 250, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00fc add sp, 2
00ff mov es, word ptr [0xc5a2]
0103 mov word ptr es:[0x8a8e], ax
0107 mov di, ax
0109 push di
010a mov es, word ptr [0xc5a4]
010e mov si, word ptr es:[0x8a8c]
0113 push si
0114 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 279, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0119 add sp, 4
011c dec ax
011d jne 0x5548
011f les bx, ptr [bp - 4]
0122 test byte ptr es:[bx], 1
0126 je 0x5524
0128 mov bx, si
012a shl bx, 6
012d mov al, byte ptr [bx + di + 0x28e8]
0131 sub ah, ah
0133 mov cx, ax
0135 mov ax, si
0137 mov dx, 6
013a mov bx, dx
013c cdq 
013d idiv bx
013f mov bx, dx
0141 shl bx, 1
0143 mov es, word ptr [0xc5a6]
0147 jmp 0x5543
0149 nop 
014a mov bx, si
014c shl bx, 6
014f mov al, byte ptr [bx + di + 0x28e8]
0153 mov cx, ax
0155 mov ax, di
0157 mov dx, 6
015a mov bx, dx
015c cdq 
015d idiv bx
015f mov bx, dx
0161 shl bx, 1
0163 mov es, word ptr [0xc5a6]
0167 sub ch, ch
0169 mov word ptr es:[bx + 0x7c0e], cx
016e mov es, word ptr [0xc5a2]
0172 mov di, word ptr es:[0x8a8e]
0177 push di
0178 mov es, word ptr [0xc5a4]
017c mov si, word ptr es:[0x8a8c]
0181 push si
0182 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 389, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0187 add sp, 4
018a dec ax
018b je 0x556a
018d jmp 0x56d5
0190 mov bx, si
0192 shl bx, 6
0195 mov byte ptr [bx + di + 0x28e8], 0x6b
019a pop si
019b pop di
019c leave 
019d retf 
019e push 0x80
01a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 420, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
01a6 add sp, 2
01a9 mov es, word ptr [0xc5a4]
01ad mov word ptr es:[0x8a8c], ax
01b1 mov es, word ptr [0xc5a2]
01b5 mov word ptr es:[0x8a8e], 0
01bc mov di, word ptr es:[0x8a8e]
01c1 push di
01c2 mov si, ax
01c4 push si
01c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 456, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
01ca add sp, 4
01cd dec ax
01ce jne 0x55f8
01d0 les bx, ptr [bp - 4]
01d3 test byte ptr es:[bx], 1
01d7 je 0x55d4
01d9 mov bx, si
01db shl bx, 6
01de mov al, byte ptr [bx + di + 0x28e8]
01e2 sub ah, ah
01e4 mov cx, ax
01e6 mov ax, si
01e8 mov dx, 6
01eb mov bx, dx
01ed cdq 
01ee idiv bx
01f0 mov bx, dx
01f2 shl bx, 1
01f4 mov es, word ptr [0xc5a6]
01f8 jmp 0x55f3
01fa mov bx, si
01fc shl bx, 6
01ff mov al, byte ptr [bx + di + 0x28e8]
0203 mov cx, ax
0205 mov ax, di
0207 mov dx, 6
020a mov bx, dx
020c cdq 
020d idiv bx
020f mov bx, dx
0211 shl bx, 1
0213 mov es, word ptr [0xc5a6]
0217 sub ch, ch
0219 mov word ptr es:[bx + 0x7c0e], cx
021e mov es, word ptr [0xc5a2]
0222 mov di, word ptr es:[0x8a8e]
0227 push di
0228 mov es, word ptr [0xc5a4]
022c mov si, word ptr es:[0x8a8c]
0231 push si
0232 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 565, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0237 add sp, 4
023a dec ax
023b je 0x561a
023d jmp 0x56d5
0240 mov bx, si
0242 shl bx, 6
0245 mov byte ptr [bx + di + 0x28e8], 0x6f
024a pop si
024b pop di
024c leave 
024d retf 
024e mov es, word ptr [0xc5a4]
0252 mov word ptr es:[0x8a8c], 0x7f
0259 push 0x40
025b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 606, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0260 add sp, 2
0263 mov es, word ptr [0xc5a2]
0267 mov word ptr es:[0x8a8e], ax
026b mov di, ax
026d push di
026e mov es, word ptr [0xc5a4]
0272 mov si, word ptr es:[0x8a8c]
0277 push si
0278 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 635, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
027d add sp, 4
0280 dec ax
0281 jne 0x56ac
0283 les bx, ptr [bp - 4]
0286 test byte ptr es:[bx], 1
028a je 0x5688
028c mov bx, si
028e shl bx, 6
0291 mov al, byte ptr [bx + di + 0x28e8]
0295 sub ah, ah
0297 mov cx, ax
0299 mov ax, si
029b mov dx, 6
029e mov bx, dx
02a0 cdq 
02a1 idiv bx
02a3 mov bx, dx
02a5 shl bx, 1
02a7 mov es, word ptr [0xc5a6]
02ab jmp 0x56a7
02ad nop 
02ae mov bx, si
02b0 shl bx, 6
02b3 mov al, byte ptr [bx + di + 0x28e8]
02b7 mov cx, ax
02b9 mov ax, di
02bb mov dx, 6
02be mov bx, dx
02c0 cdq 
02c1 idiv bx
02c3 mov bx, dx
02c5 shl bx, 1
02c7 mov es, word ptr [0xc5a6]
02cb sub ch, ch
02cd mov word ptr es:[bx + 0x7c0e], cx
02d2 mov es, word ptr [0xc5a2]
02d6 mov di, word ptr es:[0x8a8e]
02db push di
02dc mov es, word ptr [0xc5a4]
02e0 mov si, word ptr es:[0x8a8c]
02e5 push si
02e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 745, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
02eb add sp, 4
02ee dec ax
02ef jne 0x56d5
02f1 mov bx, si
02f3 shl bx, 6
02f6 mov byte ptr [bx + di + 0x28e8], 0x68
02fb pop si
02fc pop di
02fd leave 
02fe retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_StorePillarMap', 'offset': 21252, 'source': None, 'size': 110}
- {'symbol': '_ReplacePillarMap', 'offset': 21362, 'source': None, 'size': 104}
- {'symbol': '_PlacePillTile', 'offset': 22234, 'source': None, 'size': 40}
- {'symbol': '_PillGetLife', 'offset': 22274, 'source': 'src/recovered/PillGetLife.c', 'size': 40}

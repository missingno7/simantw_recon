# Recovery task _MakePillFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 560 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov bx, 0x9b1e
0009 mov es, word ptr [0xc5a0]
000d mov word ptr [bp - 6], bx
0010 mov word ptr [bp - 4], es
0013 mov ax, word ptr es:[bx]
0016 or ax, ax
0018 je 0x5802
001a dec ax
001b jne 0x57f2
001d jmp 0x5882
0020 dec ax
0021 jne 0x57f8
0023 jmp 0x5902
0026 dec ax
0027 jne 0x57fe
0029 jmp 0x5982
002c pop si
002d pop di
002e leave 
002f retf 
0030 mov word ptr [bp - 2], 0
0035 mov es, word ptr [0xc5a2]
0039 mov si, word ptr es:[0x8a8e]
003e add si, word ptr [bp - 2]
0041 push si
0042 mov es, word ptr [0xc5a4]
0046 mov di, word ptr es:[0x8a8c]
004b push di
004c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0051 add sp, 4
0054 dec ax
0055 jne 0x5875
0057 push si
0058 push di
0059 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
005e add sp, 4
0061 dec ax
0062 jne 0x5862
0064 les bx, ptr [bp - 6]
0067 test byte ptr es:[bx], 1
006b je 0x5844
006d mov ax, di
006f jmp 0x5846
0071 nop 
0072 mov ax, si
0074 mov cx, 6
0077 cdq 
0078 idiv cx
007a mov es, word ptr [0xc5a6]
007e mov bx, dx
0080 shl bx, 1
0082 mov al, byte ptr es:[bx + 0x7c0e]
0087 mov bx, di
0089 shl bx, 6
008c mov byte ptr [bx + si + 0x28e8], al
0090 mov bx, di
0092 shl bx, 6
0095 add bx, si
0097 add bx, 0x28e8
009b cmp byte ptr [bx], 0x18
009e jae 0x5875
00a0 mov byte ptr [bx], 0x4b
00a3 inc word ptr [bp - 2]
00a6 cmp word ptr [bp - 2], 6
00aa jl 0x5807
00ac pop si
00ad pop di
00ae leave 
00af retf 
00b0 mov word ptr [bp - 2], 0
00b5 mov es, word ptr [0xc5a2]
00b9 mov si, word ptr es:[0x8a8e]
00be push si
00bf mov es, word ptr [0xc5a4]
00c3 mov di, word ptr es:[0x8a8c]
00c8 sub di, word ptr [bp - 2]
00cb push di
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
00d1 add sp, 4
00d4 dec ax
00d5 jne 0x58f5
00d7 push si
00d8 push di
00d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 220, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
00de add sp, 4
00e1 dec ax
00e2 jne 0x58e2
00e4 les bx, ptr [bp - 6]
00e7 test byte ptr es:[bx], 1
00eb je 0x58c4
00ed mov ax, di
00ef jmp 0x58c6
00f1 nop 
00f2 mov ax, si
00f4 mov cx, 6
00f7 cdq 
00f8 idiv cx
00fa mov es, word ptr [0xc5a6]
00fe mov bx, dx
0100 shl bx, 1
0102 mov al, byte ptr es:[bx + 0x7c0e]
0107 mov bx, di
0109 shl bx, 6
010c mov byte ptr [bx + si + 0x28e8], al
0110 mov bx, di
0112 shl bx, 6
0115 add bx, si
0117 add bx, 0x28e8
011b cmp byte ptr [bx], 0x18
011e jae 0x58f5
0120 mov byte ptr [bx], 0x4b
0123 inc word ptr [bp - 2]
0126 cmp word ptr [bp - 2], 6
012a jl 0x5887
012c pop si
012d pop di
012e leave 
012f retf 
0130 mov word ptr [bp - 2], 0
0135 mov es, word ptr [0xc5a2]
0139 mov si, word ptr es:[0x8a8e]
013e sub si, word ptr [bp - 2]
0141 push si
0142 mov es, word ptr [0xc5a4]
0146 mov di, word ptr es:[0x8a8c]
014b push di
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0151 add sp, 4
0154 dec ax
0155 jne 0x5975
0157 push si
0158 push di
0159 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 348, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
015e add sp, 4
0161 dec ax
0162 jne 0x5962
0164 les bx, ptr [bp - 6]
0167 test byte ptr es:[bx], 1
016b je 0x5944
016d mov ax, di
016f jmp 0x5946
0171 nop 
0172 mov ax, si
0174 mov cx, 6
0177 cdq 
0178 idiv cx
017a mov es, word ptr [0xc5a6]
017e mov bx, dx
0180 shl bx, 1
0182 mov al, byte ptr es:[bx + 0x7c0e]
0187 mov bx, di
0189 shl bx, 6
018c mov byte ptr [bx + si + 0x28e8], al
0190 mov bx, di
0192 shl bx, 6
0195 add bx, si
0197 add bx, 0x28e8
019b cmp byte ptr [bx], 0x18
019e jae 0x5975
01a0 mov byte ptr [bx], 0x4b
01a3 inc word ptr [bp - 2]
01a6 cmp word ptr [bp - 2], 6
01aa jl 0x5907
01ac pop si
01ad pop di
01ae leave 
01af retf 
01b0 mov word ptr [bp - 2], 0
01b5 mov es, word ptr [0xc5a2]
01b9 mov si, word ptr es:[0x8a8e]
01be push si
01bf mov es, word ptr [0xc5a4]
01c3 mov di, word ptr es:[0x8a8c]
01c8 add di, word ptr [bp - 2]
01cb push di
01cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 463, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
01d1 add sp, 4
01d4 dec ax
01d5 jne 0x59f5
01d7 push si
01d8 push di
01d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 476, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
01de add sp, 4
01e1 dec ax
01e2 jne 0x59e2
01e4 les bx, ptr [bp - 6]
01e7 test byte ptr es:[bx], 1
01eb je 0x59c4
01ed mov ax, di
01ef jmp 0x59c6
01f1 nop 
01f2 mov ax, si
01f4 mov cx, 6
01f7 cdq 
01f8 idiv cx
01fa mov es, word ptr [0xc5a6]
01fe mov bx, dx
0200 shl bx, 1
0202 mov al, byte ptr es:[bx + 0x7c0e]
0207 mov bx, di
0209 shl bx, 6
020c mov byte ptr [bx + si + 0x28e8], al
0210 mov bx, di
0212 shl bx, 6
0215 add bx, si
0217 add bx, 0x28e8
021b cmp byte ptr [bx], 0x18
021e jae 0x59f5
0220 mov byte ptr [bx], 0x4b
0223 inc word ptr [bp - 2]
0226 cmp word ptr [bp - 2], 6
022a jl 0x5987
022c pop si
022d pop di
022e leave 
022f retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PillGetLife', 'offset': 22274, 'source': 'src/recovered/PillGetLife.c', 'size': 40}
- {'symbol': '_IsPillDead', 'offset': 22314, 'source': 'src/recovered/wf_IsPillDead-8cef0d554b.c', 'size': 168}
- {'symbol': '_PillFoodTile', 'offset': 23042, 'source': None, 'size': 110}
- {'symbol': '_InitSimVars', 'offset': 23152, 'source': 'src/recovered/InitSimVars.c', 'size': 63}

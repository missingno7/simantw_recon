# Recovery task _MakeNewHoleR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 650 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 push 0x1f
0008 nop 
0009 push cs
000a call 0x158a ; _SRand1
000d add sp, 2
0010 mov word ptr [bp - 4], ax
0013 mov es, word ptr [0xc3fc]
0017 cmp word ptr es:[0x9b6e], 0
001d jne 0x1d24
001f jmp 0x1de2
0022 xor di, di
0024 mov ax, word ptr [bp - 4]
0027 add ax, di
0029 mov cx, 0x20
002c cdq 
002d idiv cx
002f mov bx, 0x7e
0032 sub bx, dx
0034 mov word ptr [bp - 6], bx
0037 shl bx, 6
003a add bx, word ptr [bp + 6]
003d mov al, byte ptr [bx + 0x28e8]
0041 sub ah, ah
0043 mov si, ax
0045 or si, si
0047 jne 0x1d50
0049 mov dx, 0x86
004c jmp 0x1d66
004e cmp si, 2
0051 jne 0x1d5a
0053 mov dx, 0x8a
0056 jmp 0x1d66
0058 cmp si, 3
005b je 0x1d55
005d cmp si, 0x5e
0060 jge 0x1d78
0062 xor dx, dx
0064 or dx, dx
0066 jne 0x1d96
0068 inc di
0069 cmp di, 0x22
006c jl 0x1d26
006e mov word ptr [bp - 8], di
0071 mov di, word ptr [bp + 6]
0074 jmp 0x1dcf
0076 cmp si, 0x62
0079 jge 0x1d82
007b lea dx, [si + 0x22]
007e jmp 0x1d66
0080 cmp si, 0x66
0083 jne 0x1d8c
0085 mov dx, 0x85
0088 jmp 0x1d66
008a cmp si, 0x68
008d jne 0x1d64
008f mov dx, 0x84
0092 jmp 0x1d66
0094 mov word ptr [bp - 8], di
0097 mov word ptr [bp - 2], dx
009a mov di, word ptr [bp + 6]
009d mov al, byte ptr [bp - 2]
00a0 mov bx, word ptr [bp - 6]
00a3 shl bx, 6
00a6 add bx, di
00a8 mov byte ptr ss:[bx + 0x28e8], al
00ad mov <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00b0 mov ds, ax
00b2 mov ax, word ptr [bp - 6]
00b5 mov word ptr [0x835e], ax
00b8 mov word ptr [0x8360], di
00bc mov <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00bf mov es, ax
00c1 mov word ptr es:[0x8356], di
00c6 mov word ptr es:[0x8358], 0
00cd mov si, word ptr [bp - 8]
00d0 cmp si, 0x22
00d3 je 0x1ddc
00d5 push ss
00d6 pop ds
00d7 jmp 0x1ea4
00da push ss
00db pop ds
00dc pop si
00dd pop di
00de leave 
00df retf 
00e0 xor si, si
00e2 mov di, ax
00e4 push word ptr [bp + 6]
00e7 mov ax, di
00e9 add ax, si
00eb mov cx, 0x20
00ee cdq 
00ef idiv cx
00f1 sub dx, 0x7e
00f4 neg dx
00f6 mov word ptr [bp - 6], dx
00f9 push dx
00fa push 1
00fc nop 
00fd push cs
00fe call 0x5ad2 ; _IsClear3x3
0101 add sp, 6
0104 or ax, ax
0106 jne 0x1e14
0108 inc si
0109 cmp si, 0x22
010c jl 0x1de6
010e jmp 0x1e99
0111 nop 
0112 mov word ptr [bp - 8], si
0115 mov di, word ptr [bp + 6]
0118 mov cx, word ptr [bp - 6]
011b mov bx, cx
011d shl bx, 6
0120 add bx, di
0122 mov byte ptr ss:[bx + 0x28e8], 0x50
0128 mov <resolved loader operand; see bindings> ; [{'operand_offset': 297, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
012b mov ds, ax
012d mov word ptr [0x835e], cx
0131 mov word ptr [0x8360], di
0135 mov <resolved loader operand; see bindings> ; [{'operand_offset': 310, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0138 mov es, ax
013a mov word ptr es:[0x8356], di
013f xor si, si
0141 mov word ptr es:[0x8358], si
0146 mov di, si
0148 push ss
0149 pop ds
014a mov es, word ptr [0xc3fe]
014e mov al, byte ptr es:[di + 8]
0153 cwde 
0154 mov si, ax
0156 add si, word ptr [bp + 6]
0159 mov es, word ptr [0xc400]
015d mov al, byte ptr es:[di]
0162 cwde 
0163 mov cx, ax
0165 add cx, word ptr [bp - 6]
0168 js 0x1e90
016a cmp cx, 0x7f
016d jg 0x1e90
016f or si, si
0171 jl 0x1e90
0173 cmp si, 0x3f
0176 jg 0x1e90
0178 mov bx, cx
017a shl bx, 6
017d add bx, si
017f add bx, 0x28e8
0183 cmp byte ptr [bx], 0x50
0186 jae 0x1e90
0188 mov al, byte ptr [di + 0x230c]
018c mov byte ptr [bx], al
018e inc di
018f cmp di, 8
0192 jl 0x1e4c
0194 mov si, word ptr [bp - 8]
0197 cmp si, 0x22
019a jne 0x1ea1
019c jmp 0x1f88
019f mov di, word ptr [bp + 6]
01a2 mov al, byte ptr [bp - 6]
01a5 mov es, word ptr [0xc408]
01a9 mov byte ptr es:[di - 0x7cee], al
01ae mov bx, di
01b0 shl bx, 6
01b3 add bx, 0x58e9
01b7 mov word ptr [bp - 0xc], bx
01ba mov al, byte ptr [bx]
01bc sub ah, ah
01be push ax
01bf nop 
01c0 push cs
01c1 call 0x1182 ; _IsItDirt
01c4 add sp, 2
01c7 or ax, ax
01c9 je 0x1f4b
01cb nop 
01cc push cs
01cd call 0x15ee ; _SRand8
01d0 mov bx, word ptr [bp - 0xc]
01d3 mov byte ptr [bx], al
01d5 mov ax, di
01d7 cdq 
01d8 mov es, word ptr [0xc40a]
01dc add word ptr es:[0x9ddc], ax
01e1 adc word ptr es:[0x9dde], dx
01e6 mov es, word ptr [0xc40c]
01ea add word ptr es:[0x9de2], 1
01f0 adc word ptr es:[0x9de4], 0
01f6 mov es, word ptr [0xc40e]
01fa inc word ptr es:[0x7a56]
01ff mov ax, word ptr es:[0x7a56]
0203 or ax, ax
0205 jle 0x1f4b
0207 cdq 
0208 push dx
0209 push ax
020a mov es, word ptr [0xc40a]
020e push word ptr es:[0x9dde]
0213 push word ptr es:[0x9ddc]
0218 mov si, ax
021a mov word ptr [bp - 0x10], dx
021d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 544, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0222 mov es, word ptr [0xc410]
0226 mov word ptr es:[0x9fba], ax
022a push word ptr [bp - 0x10]
022d push si
022e mov es, word ptr [0xc40c]
0232 push word ptr es:[0x9de4]
0237 push word ptr es:[0x9de2]
023c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 575, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0241 mov es, word ptr [0xc412]
0245 mov word ptr es:[0x9fd2], ax
0249 push 0
024b push di
024c nop 
024d push cs
024e call 0x26e4 ; _SmoothEdgesR
0251 add sp, 4
0254 push 1
0256 lea ax, [di + 1]
0259 push ax
025a nop 
025b push cs
025c call 0x26e4 ; _SmoothEdgesR
025f add sp, 4
0262 push 2
0264 push di
0265 nop 
0266 push cs
0267 call 0x26e4 ; _SmoothEdgesR
026a add sp, 4
026d push 1
026f lea ax, [di - 1]
0272 push ax
0273 nop 
0274 push cs
0275 call 0x26e4 ; _SmoothEdgesR
0278 add sp, 4
027b push 1
027d push di
027e nop 
027f push cs
0280 call 0x2914 ; _FixExitMapR
0283 add sp, 4
0286 pop si
0287 pop di
0288 leave 
0289 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SmoothEdgesR(int x, int y);` — src/recovered/wf_FillDirtR-d16ac84868.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeNewHoleB', 'offset': 6918, 'source': None, 'size': 436}
- {'symbol': '_CanBeHouseHole', 'offset': 7354, 'source': 'src/recovered/wf_CanBeHouseHole-987878d5ee.c', 'size': 72}
- {'symbol': '_HoleBorder', 'offset': 8078, 'source': None, 'size': 86}
- {'symbol': '_DigTileB', 'offset': 8164, 'source': None, 'size': 505}

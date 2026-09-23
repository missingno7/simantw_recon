# Recovery task _FillMapLegs

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 503 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov dx, word ptr [bp + 8]
000c mov cx, di
000e cmp cx, dx
0010 jg 0x4009
0012 mov ax, di
0014 shl ax, 6
0017 mov word ptr [bp - 2], ax
001a mov bx, word ptr [bp + 0xa]
001d mov word ptr [bp - 4], bx
0020 mov ax, word ptr [bp + 0xc]
0023 sub ax, bx
0025 inc ax
0026 mov word ptr [bp - 0xa], ax
0029 mov ax, dx
002b sub ax, cx
002d inc ax
002e mov word ptr [bp - 6], ax
0031 mov bx, word ptr [bp - 2]
0034 mov ax, word ptr [bp + 0xa]
0037 cmp word ptr [bp + 0xc], ax
003a jl 0x3ffb
003c mov al, byte ptr [bp + 0xe]
003f sub ah, ah
0041 mov si, word ptr [bp - 4]
0044 add si, bx
0046 mov cx, word ptr [bp - 0xa]
0049 lea di, [si + 0x28e8]
004d push ds
004e pop es
004f rep stosb byte ptr es:[di], al
0051 add bx, 0x40
0054 dec word ptr [bp - 6]
0057 jne 0x3fde
0059 mov dx, word ptr [bp + 8]
005c mov di, word ptr [bp + 6]
005f mov bx, di
0061 cmp di, dx
0063 jg 0x405c
0065 mov ax, di
0067 shl ax, 6
006a mov word ptr [bp - 2], ax
006d mov ax, dx
006f sub ax, bx
0071 inc ax
0072 mov word ptr [bp - 4], ax
0075 mov word ptr [bp - 6], bx
0078 mov si, word ptr [bp + 0xa]
007b cmp si, word ptr [bp + 0xc]
007e jg 0x4053
0080 mov di, word ptr [bp + 0xc]
0083 push 0x14
0085 nop 
0086 push cs
0087 call 0x158a ; _SRand1
008a add sp, 2
008d or ax, ax
008f jne 0x404e
0091 push 5
0093 nop 
0094 push cs
0095 call 0x158a ; _SRand1
0098 add sp, 2
009b add al, 0x38
009d mov bx, word ptr [bp - 2]
00a0 mov byte ptr [bx + si + 0x28e8], al
00a4 inc si
00a5 cmp si, di
00a7 jle 0x402d
00a9 add word ptr [bp - 2], 0x40
00ad dec word ptr [bp - 4]
00b0 jne 0x4022
00b2 mov dx, word ptr [bp + 6]
00b5 mov cx, dx
00b7 mov bx, word ptr [bp + 0xa]
00ba mov ax, dx
00bc add ax, 3
00bf cmp ax, dx
00c1 jl 0x40ac
00c3 mov ax, dx
00c5 shl ax, 6
00c8 mov word ptr [bp - 2], ax
00cb mov word ptr [bp - 4], bx
00ce mov ax, 4
00d1 mov word ptr [bp - 0xc], ax
00d4 mov ax, dx
00d6 sub ax, cx
00d8 add ax, 4
00db mov word ptr [bp - 6], ax
00de lea ax, [bx + 3]
00e1 cmp ax, bx
00e3 jl 0x40a3
00e5 mov ax, 0xc0
00e8 mov si, word ptr [bp - 4]
00eb add si, word ptr [bp - 2]
00ee mov cx, word ptr [bp - 0xc]
00f1 lea di, [si + 0x28e8]
00f5 push ds
00f6 pop es
00f7 rep stosb byte ptr es:[di], al
00f9 add word ptr [bp - 2], 0x40
00fd dec word ptr [bp - 6]
0100 jne 0x4088
0102 mov dx, word ptr [bp + 8]
0105 sub dx, 3
0108 mov word ptr [bp - 0xe], dx
010b cmp dx, word ptr [bp + 8]
010e jg 0x40fc
0110 mov di, dx
0112 shl di, 6
0115 mov word ptr [bp - 4], bx
0118 mov ax, 4
011b mov word ptr [bp - 0x10], ax
011e mov ax, word ptr [bp + 8]
0121 sub ax, dx
0123 inc ax
0124 mov word ptr [bp - 6], ax
0127 mov word ptr [bp - 2], di
012a mov si, di
012c mov ax, word ptr [bp + 0xa]
012f add ax, 3
0132 cmp ax, word ptr [bp + 0xa]
0135 jl 0x40f4
0137 mov ax, 0xc0
013a mov bx, word ptr [bp - 4]
013d add bx, si
013f mov cx, word ptr [bp - 0x10]
0142 lea di, [bx + 0x28e8]
0146 push ds
0147 pop es
0148 rep stosb byte ptr es:[di], al
014a add si, 0x40
014d dec word ptr [bp - 6]
0150 jne 0x40d6
0152 mov dx, word ptr [bp + 6]
0155 mov bx, dx
0157 mov si, word ptr [bp + 0xc]
015a mov ax, dx
015c add ax, 3
015f cmp ax, dx
0161 jl 0x4151
0163 mov ax, dx
0165 shl ax, 6
0168 mov word ptr [bp - 2], ax
016b lea ax, [si - 3]
016e mov word ptr [bp - 4], ax
0171 mov cx, si
0173 sub cx, ax
0175 inc cx
0176 mov word ptr [bp - 0x12], cx
0179 mov ax, dx
017b sub ax, bx
017d add ax, 4
0180 mov word ptr [bp - 6], ax
0183 lea ax, [si - 3]
0186 cmp ax, si
0188 jg 0x4148
018a mov ax, 0xc0
018d mov bx, word ptr [bp - 4]
0190 add bx, word ptr [bp - 2]
0193 mov cx, word ptr [bp - 0x12]
0196 lea di, [bx + 0x28e8]
019a push ds
019b pop es
019c rep stosb byte ptr es:[di], al
019e add word ptr [bp - 2], 0x40
01a2 dec word ptr [bp - 6]
01a5 jne 0x412d
01a7 mov dx, word ptr [bp + 8]
01aa mov bx, word ptr [bp - 0xe]
01ad cmp bx, dx
01af jg 0x419d
01b1 mov ax, bx
01b3 shl ax, 6
01b6 mov word ptr [bp - 2], ax
01b9 lea ax, [si - 3]
01bc mov word ptr [bp - 4], ax
01bf mov cx, si
01c1 sub cx, ax
01c3 inc cx
01c4 mov word ptr [bp - 0x14], cx
01c7 mov ax, dx
01c9 sub ax, bx
01cb inc ax
01cc mov word ptr [bp - 6], ax
01cf lea ax, [si - 3]
01d2 cmp ax, si
01d4 jg 0x4194
01d6 mov ax, 0xc0
01d9 mov bx, word ptr [bp - 4]
01dc add bx, word ptr [bp - 2]
01df mov cx, word ptr [bp - 0x14]
01e2 lea di, [bx + 0x28e8]
01e6 push ds
01e7 pop es
01e8 rep stosb byte ptr es:[di], al
01ea add word ptr [bp - 2], 0x40
01ee dec word ptr [bp - 6]
01f1 jne 0x4179
01f3 pop si
01f4 pop di
01f5 leave 
01f6 retf 
```

## Known declaration examples

- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeClip', 'offset': 16140, 'source': 'src/recovered/wf_tu_simone_3120_MakeClip_1-2824680d4a.c', 'size': 71}
- {'symbol': '_FillMap', 'offset': 16212, 'source': None, 'size': 85}
- {'symbol': '_MakeYardPatch', 'offset': 16802, 'source': None, 'size': 401}
- {'symbol': '_AddRocks', 'offset': 17204, 'source': 'src/recovered/wf_AddRocks-01eddceee1.c', 'size': 440}

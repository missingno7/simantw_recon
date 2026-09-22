# Recovery task _FindLifeAt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 473 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 2], 0xffff
000b cmp word ptr [bp + 0xa], 1
000f jg 0x8ad2
0011 mov di, word ptr [bp + 0xc]
0014 or di, di
0016 jl 0x8ac4
0018 mov cx, word ptr [bp + 0xe]
001b cmp di, 0x7f
001e jg 0x8ac7
0020 or cx, cx
0022 jl 0x8ac7
0024 cmp cx, 0x3f
0027 jg 0x8ac7
0029 mov bx, 1
002c jmp 0x8ac9
002e mov cx, word ptr [bp + 0xe]
0031 xor bx, bx
0033 dec bx
0034 je 0x8ae2
0036 mov dx, word ptr [bp - 2]
0039 jmp 0x8b2a
003b nop 
003c mov di, word ptr [bp + 0xc]
003f or di, di
0041 jl 0x8ac4
0043 mov cx, word ptr [bp + 0xe]
0046 cmp di, 0x3f
0049 jmp 0x8ab4
004b nop 
004c mov ax, word ptr [bp + 0xa]
004f or ax, ax
0051 jl 0x8af4
0053 jo 0x8af4
0055 dec ax
0056 jle 0x8afa
0058 dec ax
0059 je 0x8b08
005b dec ax
005c je 0x8b16
005e mov dx, word ptr [bp - 2]
0061 jmp 0x8b23
0063 nop 
0064 mov si, di
0066 shl si, 6
0069 mov bx, cx
006b mov dl, byte ptr [bx + si + 0x68e8]
006f jmp 0x8b21
0071 nop 
0072 mov si, di
0074 shl si, 6
0077 mov bx, cx
0079 mov dl, byte ptr [bx + si - 0x7718]
007d jmp 0x8b21
007f nop 
0080 mov si, di
0082 shl si, 6
0085 mov bx, cx
0087 mov dl, byte ptr [bx + si - 0x6718]
008b sub dh, dh
008d or dx, dx
008f jne 0x8b2a
0091 mov dx, 0xffff
0094 mov word ptr [bp - 0x12], dx
0097 or dx, dx
0099 jge 0x8b34
009b jmp 0x8c12
009e cmp dx, 0xff
00a2 je 0x8b44
00a4 cmp dx, 0xfe
00a8 je 0x8b44
00aa xor dx, dx
00ac jmp 0x8b47
00ae mov dx, 1
00b1 or dx, dx
00b3 je 0x8b4e
00b5 jmp 0x8c12
00b8 mov ax, word ptr [bp - 0x12]
00bb mov word ptr [bp - 4], ax
00be cmp word ptr [bp + 0xa], 1
00c2 jg 0x8b7e
00c4 mov es, word ptr [0xc47c]
00c8 mov bx, word ptr es:[0x80f0]
00cd mov word ptr [bp - 8], 0x23a4
00d2 mov <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00d7 mov word ptr [bp - 0xc], 0x278e
00dc mov <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00e1 mov word ptr [bp - 0x10], 0x2f62
00e6 jmp 0x8bca
00e8 cmp word ptr [bp + 0xa], 2
00ec jne 0x8ba8
00ee mov es, word ptr [0xc47e]
00f2 mov bx, word ptr es:[0x99d4]
00f7 mov word ptr [bp - 8], 0x3736
00fc mov <resolved loader operand; see bindings> ; [{'operand_offset': 255, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0101 mov word ptr [bp - 0xc], 0x392c
0106 mov <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
010b mov word ptr [bp - 0x10], 0x3d18
0110 jmp 0x8bca
0112 mov es, word ptr [0xc480]
0116 mov bx, word ptr es:[0x72cc]
011b mov word ptr [bp - 8], 0x4104
0120 mov <resolved loader operand; see bindings> ; [{'operand_offset': 291, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0125 mov word ptr [bp - 0xc], 0x42fa
012a mov <resolved loader operand; see bindings> ; [{'operand_offset': 301, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
012f mov word ptr [bp - 0x10], 0x46e6
0134 mov <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0139 lea dx, [bx - 1]
013c mov word ptr [bp - 2], dx
013f or dx, dx
0141 jge 0x8bde
0143 mov si, dx
0145 jmp 0x8c54
0147 nop 
0148 mov word ptr [bp - 2], dx
014b mov si, dx
014d mov ds, word ptr [bp - 6]
0150 mov bx, word ptr [bp - 8]
0153 add bx, si
0155 mov al, byte ptr [bx]
0157 sub ah, ah
0159 cmp ax, di
015b jne 0x8c0c
015d les bx, ptr [bp - 0xc]
0160 mov al, byte ptr es:[bx + si]
0163 cmp ax, cx
0165 jne 0x8c0c
0167 les bx, ptr [bp - 0x10]
016a mov al, byte ptr es:[bx + si]
016d cmp ax, word ptr [bp - 4]
0170 jne 0x8c0c
0172 push ss
0173 pop ds
0174 jmp 0x8c54
0176 dec si
0177 jns 0x8be6
0179 jmp 0x8c08
017b nop 
017c push 0x7f
017e push 0x7f
0180 push 1
0182 push word ptr [bp + 0xe]
0185 push word ptr [bp + 0xc]
0188 push word ptr [bp + 0xa]
018b nop 
018c push cs
018d call 0x5922 ; _FindLifeIndex
0190 add sp, 0xc
0193 mov si, ax
0195 or si, si
0197 jl 0x8c62
0199 lea ax, [bp - 0x14]
019c push ss
019d push ax
019e lea ax, [bp - 0x16]
01a1 push ss
01a2 push ax
01a3 lea ax, [bp - 0x12]
01a6 push ss
01a7 push ax
01a8 lea cx, [bp - 0x18]
01ab push ss
01ac push cx
01ad lea cx, [bp - 0x1a]
01b0 push ss
01b1 push cx
01b2 push si
01b3 push word ptr [bp + 0xa]
01b6 nop 
01b7 push cs
01b8 call 0x573c ; _GetAntIndex
01bb add sp, 0x18
01be les bx, ptr [bp + 6]
01c1 mov word ptr es:[bx], si
01c4 mov ax, word ptr [bp - 0x12]
01c7 pop si
01c8 pop di
01c9 leave 
01ca retf 
01cb nop 
01cc mov ax, 0xffff
01cf les bx, ptr [bp + 6]
01d2 mov word ptr es:[bx], ax
01d5 pop si
01d6 pop di
01d7 leave 
01d8 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PickupMyRock', 'offset': 34286, 'source': None, 'size': 692}
- {'symbol': '_FindEggAt', 'offset': 34978, 'source': None, 'size': 499}
- {'symbol': '_SetMyHealth', 'offset': 35952, 'source': None, 'size': 105}
- {'symbol': '_EatMyFood', 'offset': 36058, 'source': None, 'size': 443}

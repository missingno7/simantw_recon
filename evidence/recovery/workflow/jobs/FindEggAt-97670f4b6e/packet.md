# Recovery task _FindEggAt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 499 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 2], 0xffff
000b cmp word ptr [bp + 0xa], 1
000f jg 0x88de
0011 mov di, word ptr [bp + 0xc]
0014 or di, di
0016 jl 0x88d0
0018 mov cx, word ptr [bp + 0xe]
001b cmp di, 0x7f
001e jg 0x88d3
0020 or cx, cx
0022 jl 0x88d3
0024 cmp cx, 0x3f
0027 jg 0x88d3
0029 mov bx, 1
002c jmp 0x88d5
002e mov cx, word ptr [bp + 0xe]
0031 xor bx, bx
0033 dec bx
0034 je 0x88ee
0036 mov dx, word ptr [bp - 2]
0039 jmp 0x8936
003b nop 
003c mov di, word ptr [bp + 0xc]
003f or di, di
0041 jl 0x88d0
0043 mov cx, word ptr [bp + 0xe]
0046 cmp di, 0x3f
0049 jmp 0x88c0
004b nop 
004c mov ax, word ptr [bp + 0xa]
004f or ax, ax
0051 jl 0x8900
0053 jo 0x8900
0055 dec ax
0056 jle 0x8906
0058 dec ax
0059 je 0x8914
005b dec ax
005c je 0x8922
005e mov dx, word ptr [bp - 2]
0061 jmp 0x892f
0063 nop 
0064 mov si, di
0066 shl si, 6
0069 mov bx, cx
006b mov dl, byte ptr [bx + si + 0x68e8]
006f jmp 0x892d
0071 nop 
0072 mov si, di
0074 shl si, 6
0077 mov bx, cx
0079 mov dl, byte ptr [bx + si - 0x7718]
007d jmp 0x892d
007f nop 
0080 mov si, di
0082 shl si, 6
0085 mov bx, cx
0087 mov dl, byte ptr [bx + si - 0x6718]
008b sub dh, dh
008d or dx, dx
008f jne 0x8936
0091 mov dx, 0xffff
0094 mov word ptr [bp - 0x12], dx
0097 mov dl, byte ptr [bp - 0x12]
009a and dx, 0x7f
009d cmp dx, 1
00a0 jl 0x894e
00a2 cmp dx, 7
00a5 jg 0x894e
00a7 mov dx, 1
00aa jmp 0x8950
00ac xor dx, dx
00ae or dx, dx
00b0 jne 0x8957
00b2 jmp 0x8a38
00b5 mov dx, word ptr [bp - 0x12]
00b8 cmp dx, 0xff
00bc je 0x896a
00be cmp dx, 0xfe
00c2 je 0x896a
00c4 xor dx, dx
00c6 jmp 0x896d
00c8 mov dx, 1
00cb or dx, dx
00cd je 0x8974
00cf jmp 0x8a38
00d2 mov ax, word ptr [bp - 0x12]
00d5 mov word ptr [bp - 4], ax
00d8 cmp word ptr [bp + 0xa], 1
00dc jg 0x89a4
00de mov es, word ptr [0xc47c]
00e2 mov bx, word ptr es:[0x80f0]
00e7 mov word ptr [bp - 8], 0x23a4
00ec mov <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00f1 mov word ptr [bp - 0xc], 0x278e
00f6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 249, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00fb mov word ptr [bp - 0x10], 0x2f62
0100 jmp 0x89f0
0102 cmp word ptr [bp + 0xa], 2
0106 jne 0x89ce
0108 mov es, word ptr [0xc47e]
010c mov bx, word ptr es:[0x99d4]
0111 mov word ptr [bp - 8], 0x3736
0116 mov <resolved loader operand; see bindings> ; [{'operand_offset': 281, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
011b mov word ptr [bp - 0xc], 0x392c
0120 mov <resolved loader operand; see bindings> ; [{'operand_offset': 291, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0125 mov word ptr [bp - 0x10], 0x3d18
012a jmp 0x89f0
012c mov es, word ptr [0xc480]
0130 mov bx, word ptr es:[0x72cc]
0135 mov word ptr [bp - 8], 0x4104
013a mov <resolved loader operand; see bindings> ; [{'operand_offset': 317, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
013f mov word ptr [bp - 0xc], 0x42fa
0144 mov <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0149 mov word ptr [bp - 0x10], 0x46e6
014e mov <resolved loader operand; see bindings> ; [{'operand_offset': 337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0153 lea dx, [bx - 1]
0156 mov word ptr [bp - 2], dx
0159 or dx, dx
015b jge 0x8a04
015d mov si, dx
015f jmp 0x8a7a
0161 nop 
0162 mov word ptr [bp - 2], dx
0165 mov si, dx
0167 mov ds, word ptr [bp - 6]
016a mov bx, word ptr [bp - 8]
016d add bx, si
016f mov al, byte ptr [bx]
0171 sub ah, ah
0173 cmp ax, di
0175 jne 0x8a32
0177 les bx, ptr [bp - 0xc]
017a mov al, byte ptr es:[bx + si]
017d cmp ax, cx
017f jne 0x8a32
0181 les bx, ptr [bp - 0x10]
0184 mov al, byte ptr es:[bx + si]
0187 cmp ax, word ptr [bp - 4]
018a jne 0x8a32
018c push ss
018d pop ds
018e jmp 0x8a7a
0190 dec si
0191 jns 0x8a0c
0193 jmp 0x8a2e
0195 nop 
0196 push 0x7f
0198 push 7
019a push 1
019c push word ptr [bp + 0xe]
019f push word ptr [bp + 0xc]
01a2 push word ptr [bp + 0xa]
01a5 nop 
01a6 push cs
01a7 call 0x5922 ; _FindLifeIndex
01aa add sp, 0xc
01ad mov si, ax
01af or si, si
01b1 jl 0x8a88
01b3 lea ax, [bp - 0x14]
01b6 push ss
01b7 push ax
01b8 lea ax, [bp - 0x16]
01bb push ss
01bc push ax
01bd lea ax, [bp - 0x12]
01c0 push ss
01c1 push ax
01c2 lea cx, [bp - 0x18]
01c5 push ss
01c6 push cx
01c7 lea cx, [bp - 0x1a]
01ca push ss
01cb push cx
01cc push si
01cd push word ptr [bp + 0xa]
01d0 nop 
01d1 push cs
01d2 call 0x573c ; _GetAntIndex
01d5 add sp, 0x18
01d8 les bx, ptr [bp + 6]
01db mov word ptr es:[bx], si
01de mov ax, word ptr [bp - 0x12]
01e1 pop si
01e2 pop di
01e3 leave 
01e4 retf 
01e5 nop 
01e6 mov ax, 0xffff
01e9 les bx, ptr [bp + 6]
01ec mov word ptr es:[bx], ax
01ef pop si
01f0 pop di
01f1 leave 
01f2 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DropMyEgg', 'offset': 33160, 'source': None, 'size': 1126}
- {'symbol': '_PickupMyRock', 'offset': 34286, 'source': None, 'size': 692}
- {'symbol': '_FindLifeAt', 'offset': 35478, 'source': None, 'size': 473}
- {'symbol': '_SetMyHealth', 'offset': 35952, 'source': None, 'size': 105}

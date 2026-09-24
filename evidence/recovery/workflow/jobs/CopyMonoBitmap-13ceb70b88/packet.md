# Recovery task _CopyMonoBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 801 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 0x10]
0009 add ax, 0x1f
000c cdq 
000d and dx, 0x1f
0010 add ax, dx
0012 sar ax, 5
0015 shl ax, 2
0018 mov word ptr [bp - 2], ax
001b mov ax, word ptr [bp + 0x14]
001e add ax, 7
0021 cdq 
0022 and dx, 7
0025 add ax, dx
0027 sar ax, 3
002a mov word ptr [bp - 4], ax
002d mov ax, word ptr [bp + 0x12]
0030 cmp ax, word ptr [bp + 0xe]
0033 jle 0x2bea
0035 mov ax, word ptr [bp + 0xe]
0038 mov word ptr [bp - 6], ax
003b mov al, byte ptr [bp + 0x16]
003e and ax, 7
0041 mov word ptr [bp - 0xc], ax
0044 or ax, ax
0046 jne 0x2bfd
0048 jmp 0x2e52
004b mov word ptr [bp - 8], 0
0050 jmp 0x2e3f
0053 nop 
0054 mov bx, word ptr [bp - 0xc]
0057 shl bx, 1
0059 mov al, byte ptr [bx - 0x4574]
005d and byte ptr [bp - 0xe], al
0060 mov ax, word ptr [bp - 8]
0063 add ax, word ptr [bp + 0x18]
0066 imul word ptr [bp - 2]
0069 mov cx, word ptr [bp + 0x16]
006c sar cx, 3
006f add ax, cx
0071 add ax, word ptr [bp - 0xa]
0074 inc ax
0075 cdq 
0076 add ax, word ptr [bp + 6]
0079 adc dx, 0
007c mov <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
007f shl dx, cl
0081 add dx, word ptr [bp + 8]
0084 mov es, dx
0086 mov bx, ax
0088 mov al, byte ptr [bp - 0xe]
008b xor byte ptr es:[bx], al
008e inc word ptr [bp - 0xa]
0091 mov ax, word ptr [bp - 4]
0094 dec ax
0095 cmp ax, word ptr [bp - 0xa]
0098 jg 0x2c4f
009a jmp 0x2d36
009d mov ax, word ptr [bp + 0x12]
00a0 sub ax, word ptr [bp - 8]
00a3 dec ax
00a4 imul word ptr [bp - 4]
00a7 add ax, word ptr [bp - 0xa]
00aa mov cx, ax
00ac inc ax
00ad cdq 
00ae mov bx, cx
00b0 add ax, word ptr [bp + 0xa]
00b3 adc dx, 0
00b6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
00b9 shl dx, cl
00bb add dx, word ptr [bp + 0xc]
00be mov es, dx
00c0 mov si, ax
00c2 mov al, byte ptr es:[si]
00c5 sub ah, ah
00c7 mov cx, ax
00c9 mov ax, bx
00cb cdq 
00cc mov bx, cx
00ce add ax, word ptr [bp + 0xa]
00d1 adc dx, 0
00d4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
00d7 shl dx, cl
00d9 add dx, word ptr [bp + 0xc]
00dc mov es, dx
00de mov si, ax
00e0 mov ah, byte ptr es:[si]
00e3 sub al, al
00e5 or bx, ax
00e7 mov cl, byte ptr [bp - 0xc]
00ea shr bx, cl
00ec mov ax, word ptr [bp - 8]
00ef add ax, word ptr [bp + 0x18]
00f2 imul word ptr [bp - 2]
00f5 mov dx, word ptr [bp + 0x16]
00f8 sar dx, 3
00fb add ax, dx
00fd add ax, word ptr [bp - 0xa]
0100 mov dx, ax
0102 mov si, ax
0104 cdq 
0105 mov word ptr [bp - 0x12], cx
0108 add ax, word ptr [bp + 6]
010b adc dx, 0
010e mov <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0111 shl dx, cl
0113 add dx, word ptr [bp + 8]
0116 mov es, dx
0118 mov di, ax
011a mov ax, bx
011c mov bl, bh
011e xor bl, byte ptr es:[di]
0121 mov byte ptr [bp - 0xe], bl
0124 mov bx, word ptr [bp - 0xc]
0127 shl bx, 1
0129 mov cl, byte ptr [bx - 0x4573]
012d and byte ptr [bp - 0xe], cl
0130 mov cl, byte ptr [bp - 0xe]
0133 xor byte ptr es:[di], cl
0136 mov cx, ax
0138 lea ax, [si + 1]
013b cdq 
013c mov si, cx
013e add ax, word ptr [bp + 6]
0141 adc dx, 0
0144 mov <resolved loader operand; see bindings> ; [{'operand_offset': 325, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0147 shl dx, cl
0149 add dx, word ptr [bp + 8]
014c mov es, dx
014e mov di, ax
0150 mov ax, si
0152 xor al, byte ptr es:[di]
0155 mov byte ptr [bp - 0xe], al
0158 mov ax, word ptr [bp - 0xa]
015b sub ax, word ptr [bp - 4]
015e inc ax
015f je 0x2d16
0161 jmp 0x2c06
0164 mov al, byte ptr [bp + 0x14]
0167 and ax, 7
016a jne 0x2d21
016c jmp 0x2c06
016f mov si, ax
0171 shl si, 1
0173 mov ax, word ptr [si - 0x4564]
0177 mov cl, byte ptr [bp - 0x12]
017a sar ax, cl
017c and al, byte ptr [bx - 0x4574]
0180 jmp 0x2c0f
0183 nop 
0184 mov ax, word ptr [bp + 0x12]
0187 sub ax, word ptr [bp - 8]
018a dec ax
018b imul word ptr [bp - 4]
018e add ax, word ptr [bp - 0xa]
0191 cdq 
0192 add ax, word ptr [bp + 0xa]
0195 adc dx, 0
0198 mov <resolved loader operand; see bindings> ; [{'operand_offset': 409, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
019b shl dx, cl
019d add dx, word ptr [bp + 0xc]
01a0 mov es, dx
01a2 mov bx, ax
01a4 mov al, byte ptr es:[bx]
01a7 sub ah, ah
01a9 mov cl, 8
01ab sub cl, byte ptr [bp - 0xc]
01ae shl ax, cl
01b0 mov word ptr [bp - 0x12], ax
01b3 cmp word ptr [bp - 4], 2
01b7 jge 0x2daa
01b9 mov cx, ax
01bb mov ax, word ptr [bp - 8]
01be add ax, word ptr [bp + 0x18]
01c1 imul word ptr [bp - 2]
01c4 mov dx, word ptr [bp + 0x16]
01c7 sar dx, 3
01ca add ax, dx
01cc add ax, word ptr [bp - 0xa]
01cf cdq 
01d0 mov bx, cx
01d2 add ax, word ptr [bp + 6]
01d5 adc dx, 0
01d8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 473, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01db shl dx, cl
01dd add dx, word ptr [bp + 8]
01e0 mov es, dx
01e2 mov si, ax
01e4 mov bl, bh
01e6 xor bl, byte ptr es:[si]
01e9 mov di, word ptr [bp - 0xc]
01ec shl di, 1
01ee and bl, byte ptr [di - 0x4573]
01f2 mov byte ptr [bp - 0xe], bl
01f5 xor byte ptr es:[si], bl
01f8 mov ax, word ptr [bp - 8]
01fb add ax, word ptr [bp + 0x18]
01fe imul word ptr [bp - 2]
0201 mov cx, word ptr [bp + 0x16]
0204 sar cx, 3
0207 add ax, cx
0209 add ax, word ptr [bp - 0xa]
020c inc ax
020d cdq 
020e add ax, word ptr [bp + 6]
0211 adc dx, 0
0214 mov <resolved loader operand; see bindings> ; [{'operand_offset': 533, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0217 shl dx, cl
0219 add dx, word ptr [bp + 8]
021c mov es, dx
021e mov bx, ax
0220 mov al, byte ptr es:[bx]
0223 xor al, byte ptr [bp - 0x12]
0226 mov byte ptr [bp - 0xe], al
0229 mov cl, byte ptr [bp + 0x14]
022c and cx, 7
022f je 0x2e02
0231 mov bx, cx
0233 shl bx, 1
0235 mov dl, byte ptr [bx - 0x4564]
0239 mov cl, 8
023b sub cl, byte ptr [bp - 0xc]
023e shl dl, cl
0240 and al, dl
0242 mov bx, word ptr [bp - 0xc]
0245 shl bx, 1
0247 and al, byte ptr [bx - 0x4574]
024b mov byte ptr [bp - 0xe], al
024e jmp 0x2e0e
0250 mov bx, word ptr [bp - 0xc]
0253 shl bx, 1
0255 mov al, byte ptr [bx - 0x4574]
0259 and byte ptr [bp - 0xe], al
025c mov ax, word ptr [bp - 8]
025f add ax, word ptr [bp + 0x18]
0262 imul word ptr [bp - 2]
0265 mov cx, word ptr [bp + 0x16]
0268 sar cx, 3
026b add ax, cx
026d add ax, word ptr [bp - 0xa]
0270 inc ax
0271 cdq 
0272 add ax, word ptr [bp + 6]
0275 adc dx, 0
0278 mov <resolved loader operand; see bindings> ; [{'operand_offset': 633, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
027b shl dx, cl
027d add dx, word ptr [bp + 8]
0280 mov es, dx
0282 mov bx, ax
0284 mov al, byte ptr [bp - 0xe]
0287 xor byte ptr es:[bx], al
028a inc word ptr [bp - 8]
028d mov ax, word ptr [bp - 6]
0290 cmp word ptr [bp - 8], ax
0293 jl 0x2e4a
0295 jmp 0x2ecf
0298 mov word ptr [bp - 0xa], 0
029d jmp 0x2c43
02a0 mov ax, word ptr [bp + 0x16]
02a3 sar ax, 3
02a6 sub ax, word ptr [bp - 2]
02a9 neg ax
02ab cmp ax, word ptr [bp - 4]
02ae jle 0x2e65
02b0 mov ax, word ptr [bp - 4]
02b3 mov word ptr [bp - 0x12], ax
02b6 mov word ptr [bp - 8], 0
02bb jmp 0x2ec7
02bd nop 
02be mov ax, word ptr [bp - 8]
02c1 add ax, word ptr [bp + 0x18]
02c4 imul word ptr [bp - 2]
02c7 mov cx, word ptr [bp + 0x16]
02ca sar cx, 3
02cd add ax, cx
02cf cdq 
02d0 add ax, word ptr [bp + 6]
02d3 adc dx, 0
02d6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 727, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
02d9 shl dx, cl
02db add dx, word ptr [bp + 8]
02de mov cx, ax
02e0 mov ax, word ptr [bp + 0x12]
02e3 sub ax, word ptr [bp - 8]
02e6 dec ax
02e7 mov bx, dx
02e9 imul word ptr [bp - 4]
02ec cdq 
02ed mov si, cx
02ef add ax, word ptr [bp + 0xa]
02f2 adc dx, 0
02f5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 758, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
02f8 shl dx, cl
02fa add dx, word ptr [bp + 0xc]
02fd mov cx, word ptr [bp - 0x12]
0300 push ds
0301 mov di, si
0303 mov si, ax
0305 mov es, bx
0307 mov ds, dx
0309 shr cx, 1
030b rep movsw word ptr es:[di], word ptr [si]
030d adc cx, cx
030f rep movsb byte ptr es:[di], byte ptr [si]
0311 pop ds
0312 inc word ptr [bp - 8]
0315 mov ax, word ptr [bp - 6]
0318 cmp word ptr [bp - 8], ax
031b jl 0x2e70
031d pop si
031e pop di
031f leave 
0320 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ConvertBitmap2', 'offset': 10000, 'source': None, 'size': 816}
- {'symbol': '_CopyBitmap2', 'offset': 10816, 'source': None, 'size': 370}
- {'symbol': '_CopyMonoMaskBitmap', 'offset': 11988, 'source': None, 'size': 1110}
- {'symbol': '_DoBitmap', 'offset': 13098, 'source': None, 'size': 678}

# Recovery task _ConvertMaskBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 703 bytes.

```asm
0000 enter 0x32, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 0x14]
0009 mov ax, bx
000b shl ax, 2
000e add ax, 0x1f
0011 cdq 
0012 and dx, 0x1f
0015 add ax, dx
0017 sar ax, 5
001a shl ax, 2
001d cdq 
001e mov word ptr [bp - 0x10], ax
0021 mov word ptr [bp - 0xe], dx
0024 mov ax, bx
0026 mov cx, 8
0029 cdq 
002a idiv cx
002c or dx, dx
002e jne 0x1bf0
0030 mov ax, bx
0032 cdq 
0033 and dx, 7
0036 add ax, dx
0038 sar ax, 3
003b cdq 
003c jmp 0x1c02
003e mov ax, bx
0040 cdq 
0041 and dx, 7
0044 add ax, dx
0046 sar ax, 3
0049 cdq 
004a add ax, 1
004d adc dx, 0
0050 mov word ptr [bp - 0xa], ax
0053 mov word ptr [bp - 8], dx
0056 xor di, di
0058 cmp word ptr [bp + 0x12], di
005b jg 0x1c12
005d jmp 0x1e6d
0060 mov cx, ax
0062 mov bx, dx
0064 shl ax, 1
0066 rcl dx, 1
0068 add ax, cx
006a adc dx, bx
006c mov word ptr [bp - 0x16], ax
006f mov word ptr [bp - 0x14], dx
0072 push word ptr [bp - 8]
0075 push word ptr [bp - 0xa]
0078 mov ax, word ptr [bp + 0x12]
007b sub ax, di
007d dec ax
007e cdq 
007f push dx
0080 push ax
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0086 mov word ptr [bp - 0x1a], ax
0089 mov word ptr [bp - 0x18], dx
008c mov cx, ax
008e mov bx, dx
0090 shl ax, 1
0092 rcl dx, 1
0094 shl ax, 1
0096 rcl dx, 1
0098 add ax, cx
009a adc dx, bx
009c mov word ptr [bp - 6], ax
009f mov word ptr [bp - 4], dx
00a2 mov word ptr [bp - 2], 0
00a7 cmp word ptr [bp - 8], 0
00ab jne 0x1c65
00ad cmp word ptr [bp - 0xa], 0
00b1 je 0x1cc7
00b3 mov si, word ptr [bp - 2]
00b6 mov ax, si
00b8 cdq 
00b9 mov cx, si
00bb mov bx, dx
00bd add ax, word ptr [bp - 6]
00c0 adc dx, word ptr [bp - 4]
00c3 mov word ptr [bp - 0x1e], cx
00c6 mov word ptr [bp - 0x1c], bx
00c9 add ax, word ptr [bp + 0xe]
00cc adc dx, 0
00cf mov <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
00d2 shl dx, cl
00d4 add dx, word ptr [bp + 0x10]
00d7 mov es, dx
00d9 mov bx, ax
00db mov al, byte ptr es:[bx]
00de mov cx, ax
00e0 mov ax, word ptr [bp - 0x1a]
00e3 mov dx, word ptr [bp - 0x18]
00e6 add ax, word ptr [bp - 0x1e]
00e9 adc dx, word ptr [bp - 0x1c]
00ec mov bx, cx
00ee add ax, word ptr [bp + 0xa]
00f1 adc dx, 0
00f4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
00f7 shl dx, cl
00f9 add dx, word ptr [bp + 0xc]
00fc mov es, dx
00fe mov cx, bx
0100 mov bx, ax
0102 mov byte ptr es:[bx], cl
0105 inc si
0106 mov ax, si
0108 cdq 
0109 cmp dx, word ptr [bp - 8]
010c jb 0x1c68
010e ja 0x1cc7
0110 cmp ax, word ptr [bp - 0xa]
0113 jb 0x1c68
0115 xor si, si
0117 cmp word ptr [bp - 0xe], si
011a jne 0x1cd6
011c cmp word ptr [bp - 0x10], si
011f jne 0x1cd6
0121 jmp 0x1e64
0124 mov ax, di
0126 cdq 
0127 push dx
0128 push ax
0129 push word ptr [bp - 0xe]
012c push word ptr [bp - 0x10]
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0134 mov word ptr [bp - 0x22], ax
0137 mov word ptr [bp - 0x20], dx
013a mov ax, si
013c cdq 
013d and dx, 3
0140 add ax, dx
0142 sar ax, 2
0145 cdq 
0146 add ax, word ptr [bp - 6]
0149 adc dx, word ptr [bp - 4]
014c add ax, word ptr [bp - 0xa]
014f adc dx, word ptr [bp - 8]
0152 mov word ptr [bp - 0x26], ax
0155 mov word ptr [bp - 0x24], dx
0158 add ax, word ptr [bp + 0xe]
015b adc dx, 0
015e mov <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0161 shl dx, cl
0163 add dx, word ptr [bp + 0x10]
0166 mov es, dx
0168 mov bx, ax
016a mov al, byte ptr es:[bx]
016d mov cx, ax
016f mov ax, si
0171 mov dx, 4
0174 mov bx, dx
0176 cdq 
0177 idiv bx
0179 shl dl, 1
017b sub dl, 7
017e neg dl
0180 mov ax, dx
0182 mov bx, cx
0184 xchg dl, cl
0186 shr dl, cl
0188 mov cx, ax
018a mov ax, dx
018c mov word ptr [bp - 0x28], ax
018f mov ax, word ptr [bp - 0x26]
0192 mov dx, word ptr [bp - 0x24]
0195 add ax, word ptr [bp - 0xa]
0198 adc dx, word ptr [bp - 8]
019b mov word ptr [bp - 0x2a], cx
019e add ax, word ptr [bp + 0xe]
01a1 adc dx, 0
01a4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01a7 shl dx, cl
01a9 add dx, word ptr [bp + 0x10]
01ac mov es, dx
01ae mov cx, bx
01b0 mov bx, ax
01b2 mov al, byte ptr es:[bx]
01b5 mov dx, cx
01b7 mov cl, byte ptr [bp - 0x2a]
01ba mov bx, ax
01bc shr al, cl
01be mov cx, ax
01c0 mov ax, dx
01c2 mov word ptr [bp - 0x2c], ax
01c5 mov ax, word ptr [bp - 0x26]
01c8 mov dx, word ptr [bp - 0x24]
01cb add ax, word ptr [bp - 0x16]
01ce adc dx, word ptr [bp - 0x14]
01d1 mov word ptr [bp - 0x2e], cx
01d4 add ax, word ptr [bp + 0xe]
01d7 adc dx, 0
01da mov <resolved loader operand; see bindings> ; [{'operand_offset': 475, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01dd shl dx, cl
01df add dx, word ptr [bp + 0x10]
01e2 mov es, dx
01e4 mov cx, bx
01e6 mov bx, ax
01e8 mov al, byte ptr es:[bx]
01eb mov dx, cx
01ed mov cl, byte ptr [bp - 0x2a]
01f0 mov bx, ax
01f2 shr al, cl
01f4 mov cx, ax
01f6 mov ax, dx
01f8 mov word ptr [bp - 0x30], ax
01fb mov ax, word ptr [bp - 0xa]
01fe mov dx, word ptr [bp - 8]
0201 shl ax, 1
0203 rcl dx, 1
0205 add ax, word ptr [bp - 0x26]
0208 adc dx, word ptr [bp - 0x24]
020b mov word ptr [bp - 0x32], cx
020e add ax, word ptr [bp + 0xe]
0211 adc dx, 0
0214 mov <resolved loader operand; see bindings> ; [{'operand_offset': 533, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0217 shl dx, cl
0219 add dx, word ptr [bp + 0x10]
021c mov es, dx
021e mov cx, bx
0220 mov bx, ax
0222 mov al, byte ptr es:[bx]
0225 mov dx, cx
0227 mov cl, byte ptr [bp - 0x2a]
022a mov bx, ax
022c shr al, cl
022e and al, 1
0230 mov cl, byte ptr [bp - 0x32]
0233 shl cl, 1
0235 or al, cl
0237 shl al, 1
0239 mov cl, byte ptr [bp - 0x2e]
023c and cl, 1
023f or al, cl
0241 shl al, 1
0243 mov cl, byte ptr [bp - 0x28]
0246 and cl, 1
0249 or al, cl
024b shl al, 1
024d mov cl, byte ptr [bp - 0x2a]
0250 dec cl
0252 shr dl, cl
0254 and dl, 1
0257 or dl, al
0259 shl dl, 1
025b shr bl, cl
025d and bl, 1
0260 or dl, bl
0262 shl dl, 1
0264 mov al, byte ptr [bp - 0x30]
0267 shr al, cl
0269 and al, 1
026b or dl, al
026d shl dl, 1
026f mov al, byte ptr [bp - 0x2c]
0272 shr al, cl
0274 and al, 1
0276 or dl, al
0278 mov ax, si
027a mov cx, dx
027c cdq 
027d add ax, word ptr [bp - 0x22]
0280 adc dx, word ptr [bp - 0x20]
0283 mov bx, cx
0285 add ax, word ptr [bp + 6]
0288 adc dx, 0
028b mov <resolved loader operand; see bindings> ; [{'operand_offset': 652, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
028e shl dx, cl
0290 add dx, word ptr [bp + 8]
0293 mov es, dx
0295 mov cx, bx
0297 mov bx, ax
0299 mov byte ptr es:[bx], cl
029c inc si
029d mov ax, si
029f cdq 
02a0 cmp dx, word ptr [bp - 0xe]
02a3 jae 0x1e5a
02a5 jmp 0x1cec
02a8 ja 0x1e64
02aa cmp ax, word ptr [bp - 0x10]
02ad jae 0x1e64
02af jmp 0x1cec
02b2 inc di
02b3 cmp di, word ptr [bp + 0x12]
02b6 jge 0x1e6d
02b8 jmp 0x1c24
02bb pop si
02bc pop di
02bd leave 
02be retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GPatBox', 'offset': 6834, 'source': 'src/recovered/wf_GPatBox-b326d1b571.c', 'size': 205}
- {'symbol': '_BitmapImageSize', 'offset': 7040, 'source': 'src/recovered/BitmapImageSize.c', 'size': 49}
- {'symbol': '_CalcBitmapStuff', 'offset': 7794, 'source': 'src/recovered/wf_CalcBitmapStuff-605c34021c.c', 'size': 146}
- {'symbol': '_ConvertMaskBitmap2', 'offset': 7940, 'source': None, 'size': 1385}

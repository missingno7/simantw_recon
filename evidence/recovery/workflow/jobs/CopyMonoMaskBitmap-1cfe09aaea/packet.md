# Recovery task _CopyMonoMaskBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 1110 bytes.

```asm
0000 enter 0x4e, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0x16]
0009 mov bx, word ptr [bp + 0x14]
000c mov ax, word ptr [bp + 0x10]
000f add ax, 0x1f
0012 cdq 
0013 and dx, 0x1f
0016 add ax, dx
0018 sar ax, 5
001b shl ax, 2
001e mov word ptr [bp - 0xa], ax
0021 lea ax, [bx + 7]
0024 cdq 
0025 and dx, 7
0028 add ax, dx
002a sar ax, 3
002d mov word ptr [bp - 0xe], ax
0030 mov ax, di
0032 and ax, 7
0035 mov word ptr [bp - 6], ax
0038 mov word ptr [bp - 0x10], 1
003d or di, di
003f jge 0x2f26
0041 mov ax, di
0043 neg ax
0045 mov word ptr [bp - 0x16], ax
0048 mov word ptr [bp - 8], bx
004b mov word ptr [bp - 6], 0
0050 jmp 0x2f45
0052 mov word ptr [bp - 0x16], 0
0057 mov dx, word ptr [bp + 0x10]
005a mov ax, di
005c add ax, bx
005e cmp ax, dx
0060 jle 0x2f42
0062 sub dx, di
0064 mov word ptr [bp - 8], dx
0067 mov word ptr [bp - 0x10], 0
006c jmp 0x2f45
006e mov word ptr [bp - 8], bx
0071 mov cx, word ptr [bp + 0x18]
0074 or cx, cx
0076 jl 0x2f4f
0078 jmp 0x321c
007b mov ax, cx
007d neg ax
007f mov word ptr [bp - 2], ax
0082 mov si, word ptr [bp + 0x12]
0085 cmp word ptr [bp - 6], 0
0089 jne 0x2f62
008b jmp 0x323a
008e mov ax, word ptr [bp - 2]
0091 mov word ptr [bp - 0xc], ax
0094 cmp ax, si
0096 jl 0x2f6f
0098 jmp 0x3326
009b mov word ptr [bp - 0x14], si
009e mov ax, word ptr [bp - 8]
00a1 add ax, 7
00a4 sar ax, 3
00a7 mov word ptr [bp - 0x1a], ax
00aa dec ax
00ab mov word ptr [bp - 0x18], ax
00ae mov ax, word ptr [bp - 0xe]
00b1 shl ax, 1
00b3 cdq 
00b4 mov word ptr [bp - 0x1e], ax
00b7 mov word ptr [bp - 0x1c], dx
00ba mov ax, di
00bc sar ax, 3
00bf cdq 
00c0 mov word ptr [bp - 0x22], ax
00c3 mov word ptr [bp - 0x20], dx
00c6 mov di, word ptr [bp - 0xc]
00c9 mov si, word ptr [bp - 0x16]
00cc sar si, 3
00cf cmp word ptr [bp - 0x18], si
00d2 jg 0x2fab
00d4 jmp 0x311a
00d7 push word ptr [bp - 0x1c]
00da push word ptr [bp - 0x1e]
00dd mov ax, word ptr [bp + 0x12]
00e0 sub ax, di
00e2 dec ax
00e3 cdq 
00e4 push dx
00e5 push ax
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00eb mov word ptr [bp - 0x26], ax
00ee mov word ptr [bp - 0x24], dx
00f1 mov ax, word ptr [bp + 0x18]
00f4 add ax, di
00f6 imul word ptr [bp - 0xa]
00f9 add ax, word ptr [bp - 0x22]
00fc adc dx, word ptr [bp - 0x20]
00ff mov word ptr [bp - 0x2a], ax
0102 mov word ptr [bp - 0x28], dx
0105 mov ax, si
0107 cdq 
0108 mov cx, si
010a mov bx, dx
010c add ax, word ptr [bp - 0x26]
010f adc dx, word ptr [bp - 0x24]
0112 mov word ptr [bp - 0x2e], ax
0115 mov word ptr [bp - 0x2c], dx
0118 mov ax, word ptr [bp - 0xe]
011b cdq 
011c add ax, word ptr [bp - 0x2e]
011f adc dx, word ptr [bp - 0x2c]
0122 mov word ptr [bp - 0x32], ax
0125 mov word ptr [bp - 0x30], dx
0128 add ax, 1
012b adc dx, 0
012e mov word ptr [bp - 0x36], cx
0131 mov word ptr [bp - 0x34], bx
0134 add ax, word ptr [bp + 0xa]
0137 adc dx, 0
013a mov <resolved loader operand; see bindings> ; [{'operand_offset': 315, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
013d shl dx, cl
013f add dx, word ptr [bp + 0xc]
0142 mov es, dx
0144 mov bx, ax
0146 mov al, byte ptr es:[bx]
0149 sub ah, ah
014b mov cx, ax
014d mov ax, word ptr [bp - 0x32]
0150 mov dx, word ptr [bp - 0x30]
0153 mov bx, cx
0155 add ax, word ptr [bp + 0xa]
0158 adc dx, 0
015b mov <resolved loader operand; see bindings> ; [{'operand_offset': 348, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
015e shl dx, cl
0160 add dx, word ptr [bp + 0xc]
0163 mov es, dx
0165 mov cx, bx
0167 mov bx, ax
0169 mov ah, byte ptr es:[bx]
016c sub al, al
016e or cx, ax
0170 mov ax, cx
0172 mov cl, byte ptr [bp - 6]
0175 shr ax, cl
0177 mov word ptr [bp - 2], ax
017a mov ax, word ptr [bp - 0x2a]
017d mov dx, word ptr [bp - 0x28]
0180 add ax, word ptr [bp - 0x36]
0183 adc dx, word ptr [bp - 0x34]
0186 mov word ptr [bp - 0x3a], ax
0189 mov word ptr [bp - 0x38], dx
018c add ax, word ptr [bp + 6]
018f adc dx, 0
0192 mov <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0195 shl dx, cl
0197 add dx, word ptr [bp + 8]
019a mov es, dx
019c mov bx, ax
019e mov al, byte ptr [bp - 1]
01a1 xor al, byte ptr es:[bx]
01a4 mov cx, ax
01a6 mov ax, word ptr [bp - 0x2e]
01a9 mov dx, word ptr [bp - 0x2c]
01ac add ax, 1
01af adc dx, 0
01b2 mov word ptr [bp - 0x3c], cx
01b5 add ax, word ptr [bp + 0xa]
01b8 adc dx, 0
01bb mov <resolved loader operand; see bindings> ; [{'operand_offset': 444, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01be shl dx, cl
01c0 add dx, word ptr [bp + 0xc]
01c3 mov cx, es
01c5 mov es, dx
01c7 mov dx, bx
01c9 mov bx, ax
01cb mov al, byte ptr es:[bx]
01ce sub ah, ah
01d0 mov bx, ax
01d2 mov word ptr [bp - 0x40], dx
01d5 mov word ptr [bp - 0x3e], cx
01d8 mov ax, word ptr [bp - 0x2e]
01db mov dx, word ptr [bp - 0x2c]
01de add ax, word ptr [bp + 0xa]
01e1 adc dx, 0
01e4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 485, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01e7 shl dx, cl
01e9 add dx, word ptr [bp + 0xc]
01ec mov es, dx
01ee mov cx, bx
01f0 mov bx, ax
01f2 mov ah, byte ptr es:[bx]
01f5 sub al, al
01f7 or cx, ax
01f9 mov ax, cx
01fb mov cl, byte ptr [bp - 6]
01fe shr ax, cl
0200 mov cx, ax
0202 mov al, ah
0204 and al, byte ptr [bp - 0x3c]
0207 mov byte ptr [bp - 3], al
020a les bx, ptr [bp - 0x40]
020d xor byte ptr es:[bx], al
0210 mov ax, word ptr [bp - 0x3a]
0213 mov dx, word ptr [bp - 0x38]
0216 add ax, 1
0219 adc dx, 0
021c mov bx, cx
021e add ax, word ptr [bp + 6]
0221 adc dx, 0
0224 mov <resolved loader operand; see bindings> ; [{'operand_offset': 549, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0227 shl dx, cl
0229 add dx, word ptr [bp + 8]
022c mov es, dx
022e mov cx, bx
0230 mov bx, ax
0232 mov al, byte ptr es:[bx]
0235 xor al, byte ptr [bp - 2]
0238 and cl, al
023a xor byte ptr es:[bx], cl
023d inc si
023e cmp word ptr [bp - 0x18], si
0241 jle 0x311a
0243 jmp 0x2fd9
0246 cmp word ptr [bp - 0x10], 0
024a jne 0x3123
024c jmp 0x320f
024f push word ptr [bp - 0x1c]
0252 push word ptr [bp - 0x1e]
0255 mov ax, word ptr [bp + 0x12]
0258 sub ax, di
025a dec ax
025b cdq 
025c push dx
025d push ax
025e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0263 mov cx, ax
0265 mov ax, si
0267 mov bx, dx
0269 cdq 
026a mov word ptr [bp - 0x44], ax
026d mov word ptr [bp - 0x42], dx
0270 mov ax, cx
0272 mov dx, bx
0274 add ax, word ptr [bp - 0x44]
0277 adc dx, word ptr [bp - 0x42]
027a mov word ptr [bp - 0x48], ax
027d mov word ptr [bp - 0x46], dx
0280 add ax, word ptr [bp + 0xa]
0283 adc dx, 0
0286 mov <resolved loader operand; see bindings> ; [{'operand_offset': 647, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0289 shl dx, cl
028b add dx, word ptr [bp + 0xc]
028e mov es, dx
0290 mov bx, ax
0292 mov al, byte ptr es:[bx]
0295 sub ah, ah
0297 mov cl, 8
0299 sub cl, byte ptr [bp - 6]
029c shl ax, cl
029e mov word ptr [bp - 2], ax
02a1 mov ax, word ptr [bp - 0xe]
02a4 cdq 
02a5 add ax, word ptr [bp - 0x48]
02a8 adc dx, word ptr [bp - 0x46]
02ab mov bx, cx
02ad add ax, word ptr [bp + 0xa]
02b0 adc dx, 0
02b3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 692, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
02b6 shl dx, cl
02b8 add dx, word ptr [bp + 0xc]
02bb mov es, dx
02bd mov cx, bx
02bf mov bx, ax
02c1 mov al, byte ptr es:[bx]
02c4 sub ah, ah
02c6 shl ax, cl
02c8 mov word ptr [bp - 4], ax
02cb cmp word ptr [bp - 0xe], 2
02cf jge 0x31d7
02d1 mov ax, word ptr [bp + 0x18]
02d4 add ax, di
02d6 imul word ptr [bp - 0xa]
02d9 add ax, word ptr [bp - 0x22]
02dc adc dx, word ptr [bp - 0x20]
02df add ax, word ptr [bp - 0x44]
02e2 adc dx, word ptr [bp - 0x42]
02e5 add ax, word ptr [bp + 6]
02e8 adc dx, 0
02eb mov <resolved loader operand; see bindings> ; [{'operand_offset': 748, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
02ee shl dx, cl
02f0 add dx, word ptr [bp + 8]
02f3 mov es, dx
02f5 mov bx, ax
02f7 mov al, byte ptr [bp - 3]
02fa xor al, byte ptr es:[bx]
02fd and al, byte ptr [bp - 1]
0300 xor byte ptr es:[bx], al
0303 mov ax, word ptr [bp + 0x18]
0306 add ax, di
0308 imul word ptr [bp - 0xa]
030b add ax, word ptr [bp - 0x22]
030e adc dx, word ptr [bp - 0x20]
0311 add ax, word ptr [bp - 0x44]
0314 adc dx, word ptr [bp - 0x42]
0317 add ax, 1
031a adc dx, 0
031d add ax, word ptr [bp + 6]
0320 adc dx, 0
0323 mov <resolved loader operand; see bindings> ; [{'operand_offset': 804, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0326 shl dx, cl
0328 add dx, word ptr [bp + 8]
032b mov es, dx
032d mov bx, ax
032f mov al, byte ptr es:[bx]
0332 xor al, byte ptr [bp - 4]
0335 and al, byte ptr [bp - 2]
0338 xor byte ptr es:[bx], al
033b inc di
033c cmp di, word ptr [bp - 0x14]
033f jge 0x3218
0341 jmp 0x2f9d
0344 pop si
0345 pop di
0346 leave 
0347 retf 
0348 mov word ptr [bp - 2], 0
034d mov dx, word ptr [bp + 0xe]
0350 mov ax, word ptr [bp + 0x12]
0353 add ax, cx
0355 cmp ax, dx
0357 jg 0x3230
0359 jmp 0x2f56
035c sub dx, cx
035e mov word ptr [bp - 0x14], dx
0361 mov si, dx
0363 jmp 0x2f59
0366 mov word ptr [bp - 0x14], si
0369 mov di, si
036b mov bx, word ptr [bp - 2]
036e cmp bx, di
0370 jl 0x3249
0372 jmp 0x3326
0375 mov ax, word ptr [bp + 0x12]
0378 sub ax, bx
037a mov cx, ax
037c shl ax, 1
037e dec ax
037f imul word ptr [bp - 0xe]
0382 mov word ptr [bp - 4], ax
0385 mov ax, word ptr [bp - 0xe]
0388 shl ax, 1
038a mov word ptr [bp - 0x10], ax
038d mov ax, word ptr [bp + 0x18]
0390 add ax, bx
0392 imul word ptr [bp - 0xa]
0395 mov dx, word ptr [bp + 0x16]
0398 sar dx, 3
039b add ax, dx
039d mov word ptr [bp - 2], ax
03a0 mov ax, cx
03a2 dec ax
03a3 imul word ptr [bp - 0xe]
03a6 shl ax, 1
03a8 mov word ptr [bp - 6], ax
03ab mov ax, word ptr [bp - 8]
03ae add ax, 7
03b1 sar ax, 3
03b4 mov word ptr [bp - 0x1a], ax
03b7 mov ax, si
03b9 sub ax, bx
03bb mov word ptr [bp - 0x12], ax
03be mov di, word ptr [bp - 2]
03c1 mov si, word ptr [bp - 0x16]
03c4 sar si, 3
03c7 cmp si, word ptr [bp - 0x1a]
03ca jge 0x3312
03cc mov word ptr [bp - 2], di
03cf mov ax, di
03d1 add ax, si
03d3 cdq 
03d4 add ax, word ptr [bp + 6]
03d7 adc dx, 0
03da mov <resolved loader operand; see bindings> ; [{'operand_offset': 987, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
03dd shl dx, cl
03df add dx, word ptr [bp + 8]
03e2 mov es, dx
03e4 mov bx, ax
03e6 mov ax, word ptr [bp - 4]
03e9 add ax, si
03eb cdq 
03ec add ax, word ptr [bp + 0xa]
03ef adc dx, 0
03f2 shl dx, cl
03f4 add dx, word ptr [bp + 0xc]
03f7 mov word ptr [bp - 0x4c], bx
03fa mov word ptr [bp - 0x4a], es
03fd mov es, dx
03ff mov bx, ax
0401 mov al, byte ptr es:[bx]
0404 les bx, ptr [bp - 0x4c]
0407 xor al, byte ptr es:[bx]
040a mov cx, ax
040c mov ax, word ptr [bp - 6]
040f add ax, si
0411 cdq 
0412 mov word ptr [bp - 0x4e], cx
0415 add ax, word ptr [bp + 0xa]
0418 adc dx, 0
041b mov <resolved loader operand; see bindings> ; [{'operand_offset': 1052, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
041e shl dx, cl
0420 add dx, word ptr [bp + 0xc]
0423 mov cx, es
0425 mov es, dx
0427 mov dx, bx
0429 mov bx, ax
042b mov al, byte ptr [bp - 0x4e]
042e and al, byte ptr es:[bx]
0431 mov es, cx
0433 mov bx, dx
0435 xor byte ptr es:[bx], al
0438 inc si
0439 cmp word ptr [bp - 0x1a], si
043c jg 0x32a3
043e mov ax, word ptr [bp - 0x10]
0441 sub word ptr [bp - 4], ax
0444 add di, word ptr [bp - 0xa]
0447 sub word ptr [bp - 6], ax
044a dec word ptr [bp - 0x12]
044d je 0x3326
044f jmp 0x3295
0452 pop si
0453 pop di
0454 leave 
0455 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CopyBitmap2', 'offset': 10816, 'source': None, 'size': 370}
- {'symbol': '_CopyMonoBitmap', 'offset': 11186, 'source': None, 'size': 801}
- {'symbol': '_DoBitmap', 'offset': 13098, 'source': None, 'size': 678}
- {'symbol': '_ConvertMonoBitmap', 'offset': 13776, 'source': None, 'size': 123}

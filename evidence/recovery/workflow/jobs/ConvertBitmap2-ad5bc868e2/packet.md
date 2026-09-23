# Recovery task _ConvertBitmap2

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 816 bytes.

```asm
0000 enter 0x44, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0x10]
0009 mov bx, word ptr [bp + 0x14]
000c mov ax, di
000e shl ax, 2
0011 add ax, 0x1f
0014 cdq 
0015 and dx, 0x1f
0018 add ax, dx
001a sar ax, 5
001d shl ax, 2
0020 cdq 
0021 mov word ptr [bp - 0x14], ax
0024 mov word ptr [bp - 0x12], dx
0027 mov ax, bx
0029 mov cx, 8
002c cdq 
002d idiv cx
002f or dx, dx
0031 jne 0x2752
0033 mov ax, bx
0035 cdq 
0036 and dx, 7
0039 add ax, dx
003b sar ax, 3
003e cdq 
003f jmp 0x2764
0041 nop 
0042 mov ax, bx
0044 cdq 
0045 and dx, 7
0048 add ax, dx
004a sar ax, 3
004d cdq 
004e add ax, 1
0051 adc dx, 0
0054 mov word ptr [bp - 0x10], ax
0057 mov word ptr [bp - 0xe], dx
005a cmp word ptr [bp + 0x16], 0
005e jge 0x278c
0060 mov ax, word ptr [bp + 0x16]
0063 neg ax
0065 mov word ptr [bp - 0x1a], ax
0068 mov word ptr [bp - 0x16], bx
006b mov si, word ptr [bp + 0x18]
006e or si, si
0070 jge 0x27a2
0072 mov ax, si
0074 neg ax
0076 mov word ptr [bp - 0x1c], ax
0079 jmp 0x27ba
007b nop 
007c mov word ptr [bp - 0x1a], 0
0081 mov ax, word ptr [bp + 0x16]
0084 add ax, bx
0086 cmp ax, di
0088 jle 0x2778
008a sub di, word ptr [bp + 0x16]
008d mov word ptr [bp - 0x16], di
0090 jmp 0x277b
0092 mov word ptr [bp - 0x1c], 0
0097 mov dx, word ptr [bp + 0xe]
009a mov ax, word ptr [bp + 0x12]
009d add ax, si
009f cmp ax, dx
00a1 jle 0x27ba
00a3 sub dx, si
00a5 mov word ptr [bp - 0x18], dx
00a8 jmp 0x27c0
00aa mov ax, word ptr [bp + 0x12]
00ad mov word ptr [bp - 0x18], ax
00b0 mov ax, word ptr [bp - 0x1c]
00b3 cdq 
00b4 mov word ptr [bp - 0xc], ax
00b7 mov word ptr [bp - 0xa], dx
00ba mov cx, ax
00bc mov ax, word ptr [bp - 0x18]
00bf mov bx, dx
00c1 cdq 
00c2 cmp bx, dx
00c4 jle 0x27d9
00c6 jmp 0x2a3c
00c9 jl 0x27e2
00cb cmp cx, ax
00cd jb 0x27e2
00cf jmp 0x2a3c
00d2 mov ax, word ptr [bp + 0x16]
00d5 sar ax, 1
00d7 cdq 
00d8 mov word ptr [bp - 0x22], ax
00db mov word ptr [bp - 0x20], dx
00de mov ax, word ptr [bp - 0x10]
00e1 mov dx, word ptr [bp - 0xe]
00e4 mov cx, ax
00e6 mov bx, dx
00e8 shl ax, 1
00ea rcl dx, 1
00ec add ax, cx
00ee adc dx, bx
00f0 mov word ptr [bp - 0x26], ax
00f3 mov word ptr [bp - 0x24], dx
00f6 mov di, word ptr [bp + 0x16]
00f9 push word ptr [bp - 0xe]
00fc push word ptr [bp - 0x10]
00ff mov ax, word ptr [bp + 0x12]
0102 cdq 
0103 sub ax, word ptr [bp - 0xc]
0106 sbb dx, word ptr [bp - 0xa]
0109 sub ax, 1
010c sbb dx, 0
010f push dx
0110 push ax
0111 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 276, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0116 shl ax, 1
0118 rcl dx, 1
011a shl ax, 1
011c rcl dx, 1
011e mov word ptr [bp - 8], ax
0121 mov word ptr [bp - 6], dx
0124 mov ax, word ptr [bp - 0x1a]
0127 sar ax, 1
0129 cdq 
012a mov word ptr [bp - 4], ax
012d mov word ptr [bp - 2], dx
0130 mov ax, word ptr [bp - 0x16]
0133 sar ax, 1
0135 cdq 
0136 cmp word ptr [bp - 2], dx
0139 jle 0x284e
013b jmp 0x2a1e
013e jl 0x2858
0140 cmp word ptr [bp - 4], ax
0143 jb 0x2858
0145 jmp 0x2a1e
0148 push word ptr [bp - 0x12]
014b push word ptr [bp - 0x14]
014e mov ax, si
0150 cdq 
0151 add ax, word ptr [bp - 0xc]
0154 adc dx, word ptr [bp - 0xa]
0157 push dx
0158 push ax
0159 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 348, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
015e add ax, word ptr [bp - 0x22]
0161 adc dx, word ptr [bp - 0x20]
0164 mov word ptr [bp - 0x2a], ax
0167 mov word ptr [bp - 0x28], dx
016a push 0
016c push 4
016e push word ptr [bp - 2]
0171 push word ptr [bp - 4]
0174 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 375, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0179 add ax, word ptr [bp - 8]
017c adc dx, word ptr [bp - 6]
017f push 0
0181 push 4
0183 push word ptr [bp - 2]
0186 push word ptr [bp - 4]
0189 mov word ptr [bp - 0x2e], ax
018c mov word ptr [bp - 0x2c], dx
018f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 402, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFlrem
0194 mov cx, ax
0196 mov ax, word ptr [bp - 0x2e]
0199 mov dx, word ptr [bp - 0x2c]
019c add ax, word ptr [bp - 0x26]
019f adc dx, word ptr [bp - 0x24]
01a2 mov word ptr [bp - 0x32], cx
01a5 add ax, word ptr [bp + 0xa]
01a8 adc dx, 0
01ab mov <resolved loader operand; see bindings> ; [{'operand_offset': 428, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01ae shl dx, cl
01b0 add dx, word ptr [bp + 0xc]
01b3 mov es, dx
01b5 mov bx, ax
01b7 mov al, byte ptr es:[bx]
01ba mov cx, ax
01bc mov ax, word ptr [bp - 0x2e]
01bf mov dx, word ptr [bp - 0x2c]
01c2 mov bx, cx
01c4 add ax, word ptr [bp + 0xa]
01c7 adc dx, 0
01ca mov <resolved loader operand; see bindings> ; [{'operand_offset': 459, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01cd shl dx, cl
01cf add dx, word ptr [bp + 0xc]
01d2 mov es, dx
01d4 mov cx, bx
01d6 mov bx, ax
01d8 mov al, byte ptr es:[bx]
01db mov dx, cx
01dd mov cl, 7
01df mov bl, byte ptr [bp - 0x32]
01e2 shl bl, 1
01e4 sub cl, bl
01e6 mov bx, cx
01e8 dec cl
01ea mov word ptr [bp - 0x34], dx
01ed shr dl, cl
01ef and dl, 1
01f2 mov word ptr [bp - 0x36], cx
01f5 mov cl, bl
01f7 mov bx, ax
01f9 shr al, cl
01fb mov word ptr [bp - 0x38], ax
01fe mov ax, dx
0200 mov word ptr [bp - 0x3a], ax
0203 mov ax, word ptr [bp - 0x2e]
0206 mov dx, word ptr [bp - 0x2c]
0209 add ax, word ptr [bp - 0x10]
020c adc dx, word ptr [bp - 0xe]
020f mov word ptr [bp - 0x3c], cx
0212 add ax, word ptr [bp + 0xa]
0215 adc dx, 0
0218 mov <resolved loader operand; see bindings> ; [{'operand_offset': 537, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
021b shl dx, cl
021d add dx, word ptr [bp + 0xc]
0220 mov es, dx
0222 mov cx, bx
0224 mov bx, ax
0226 mov al, byte ptr es:[bx]
0229 mov dx, cx
022b mov cl, byte ptr [bp - 0x3c]
022e mov bx, ax
0230 shr al, cl
0232 mov cx, ax
0234 mov ax, dx
0236 mov word ptr [bp - 0x3e], ax
0239 mov ax, word ptr [bp - 0x10]
023c mov dx, word ptr [bp - 0xe]
023f shl ax, 1
0241 rcl dx, 1
0243 add ax, word ptr [bp - 0x2e]
0246 adc dx, word ptr [bp - 0x2c]
0249 mov word ptr [bp - 0x40], cx
024c add ax, word ptr [bp + 0xa]
024f adc dx, 0
0252 mov <resolved loader operand; see bindings> ; [{'operand_offset': 595, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0255 shl dx, cl
0257 add dx, word ptr [bp + 0xc]
025a mov es, dx
025c mov cx, bx
025e mov dx, bx
0260 mov cl, byte ptr [bp - 0x3c]
0263 mov bx, ax
0265 mov al, byte ptr es:[bx]
0268 mov bx, ax
026a shr al, cl
026c and al, 1
026e mov cx, ax
0270 mov al, byte ptr [bp - 0x34]
0273 mov ax, cx
0275 mov cl, byte ptr [bp - 0x3c]
0278 mov word ptr [bp - 0x42], dx
027b mov dl, byte ptr [bp - 0x34]
027e shr dl, cl
0280 shl dl, 1
0282 or al, dl
0284 shl al, 1
0286 mov cl, byte ptr [bp - 0x40]
0289 and cl, 1
028c or al, cl
028e shl al, 1
0290 mov cl, byte ptr [bp - 0x38]
0293 and cl, 1
0296 or al, cl
0298 shl al, 1
029a or al, byte ptr [bp - 0x3a]
029d shl al, 1
029f mov byte ptr [bp - 0x1e], al
02a2 mov ax, word ptr [bp - 0x2a]
02a5 mov dx, word ptr [bp - 0x28]
02a8 add ax, word ptr [bp - 4]
02ab adc dx, word ptr [bp - 2]
02ae add ax, word ptr [bp + 6]
02b1 adc dx, 0
02b4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 693, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
02b7 shl dx, cl
02b9 add dx, word ptr [bp + 8]
02bc mov es, dx
02be mov cx, bx
02c0 mov bx, ax
02c2 mov al, byte ptr [bp - 0x36]
02c5 mov dx, cx
02c7 mov cl, al
02c9 mov al, byte ptr [bp - 0x3e]
02cc shr al, cl
02ce and al, 1
02d0 shr dl, cl
02d2 and dl, 1
02d5 or dl, byte ptr [bp - 0x1e]
02d8 shl dl, 1
02da mov word ptr [bp - 0x44], ax
02dd mov al, byte ptr [bp - 0x42]
02e0 shr al, cl
02e2 and al, 1
02e4 or dl, al
02e6 shl dl, 1
02e8 or dl, byte ptr [bp - 0x44]
02eb mov byte ptr es:[bx], dl
02ee mov ax, word ptr [bp - 0x16]
02f1 sar ax, 1
02f3 cdq 
02f4 add word ptr [bp - 4], 1
02f8 adc word ptr [bp - 2], 0
02fc cmp dx, word ptr [bp - 2]
02ff jle 0x2a14
0301 jmp 0x287a
0304 jl 0x2a1e
0306 cmp ax, word ptr [bp - 4]
0309 jbe 0x2a1e
030b jmp 0x287a
030e mov ax, word ptr [bp - 0x18]
0311 cdq 
0312 add word ptr [bp - 0xc], 1
0316 adc word ptr [bp - 0xa], 0
031a cmp dx, word ptr [bp - 0xa]
031d jle 0x2a32
031f jmp 0x2809
0322 jl 0x2a3c
0324 cmp ax, word ptr [bp - 0xc]
0327 jbe 0x2a3c
0329 jmp 0x2809
032c pop si
032d pop di
032e leave 
032f retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ConvertMaskBitmap2', 'offset': 7940, 'source': None, 'size': 1385}
- {'symbol': '_ConvertBitmap', 'offset': 9326, 'source': None, 'size': 674}
- {'symbol': '_CopyBitmap2', 'offset': 10816, 'source': None, 'size': 370}
- {'symbol': '_CopyMonoBitmap', 'offset': 11186, 'source': None, 'size': 801}

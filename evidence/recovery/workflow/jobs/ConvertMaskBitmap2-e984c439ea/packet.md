# Recovery task _ConvertMaskBitmap2

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 1385 bytes.

```asm
0000 enter 0x4e, 0
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
0021 mov word ptr [bp - 0x18], ax
0024 mov word ptr [bp - 0x16], dx
0027 mov ax, bx
0029 mov cx, 8
002c cdq 
002d idiv cx
002f or dx, dx
0031 jne 0x1f46
0033 mov ax, bx
0035 cdq 
0036 and dx, 7
0039 add ax, dx
003b sar ax, 3
003e cdq 
003f jmp 0x1f58
0041 nop 
0042 mov ax, bx
0044 cdq 
0045 and dx, 7
0048 add ax, dx
004a sar ax, 3
004d cdq 
004e add ax, 1
0051 adc dx, 0
0054 mov word ptr [bp - 0x14], ax
0057 mov word ptr [bp - 0x12], dx
005a cmp word ptr [bp + 0x16], 0
005e jl 0x1f67
0060 jmp 0x20d4
0063 mov ax, word ptr [bp + 0x16]
0066 neg ax
0068 mov word ptr [bp - 0x1e], ax
006b mov word ptr [bp - 0x1a], bx
006e mov bx, word ptr [bp + 0x18]
0071 or bx, bx
0073 jl 0x1f7c
0075 jmp 0x20ee
0078 mov ax, bx
007a neg ax
007c mov word ptr [bp - 0x20], ax
007f mov ax, word ptr [bp + 0x12]
0082 mov word ptr [bp - 0x1c], ax
0085 mov ax, word ptr [bp - 0x20]
0088 cdq 
0089 mov word ptr [bp - 0x10], ax
008c mov word ptr [bp - 0xe], dx
008f mov cx, ax
0091 mov ax, word ptr [bp - 0x1c]
0094 mov bx, dx
0096 cdq 
0097 cmp bx, dx
0099 jle 0x1fa2
009b jmp 0x2469
009e jl 0x1fab
00a0 cmp cx, ax
00a2 jb 0x1fab
00a4 jmp 0x2469
00a7 mov ax, word ptr [bp + 0x16]
00aa sar ax, 1
00ac cdq 
00ad mov word ptr [bp - 0x24], ax
00b0 mov word ptr [bp - 0x22], dx
00b3 mov ax, word ptr [bp - 0x14]
00b6 mov dx, word ptr [bp - 0x12]
00b9 mov cx, ax
00bb mov bx, dx
00bd shl ax, 1
00bf rcl dx, 1
00c1 add ax, cx
00c3 adc dx, bx
00c5 mov word ptr [bp - 0x28], ax
00c8 mov word ptr [bp - 0x26], dx
00cb mov di, word ptr [bp + 0x16]
00ce push word ptr [bp - 0x12]
00d1 push word ptr [bp - 0x14]
00d4 mov ax, word ptr [bp + 0x12]
00d7 cdq 
00d8 sub ax, word ptr [bp - 0x10]
00db sbb dx, word ptr [bp - 0xe]
00de sub ax, 1
00e1 sbb dx, 0
00e4 push dx
00e5 push ax
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00eb mov cx, ax
00ed mov bx, dx
00ef shl ax, 1
00f1 rcl dx, 1
00f3 shl ax, 1
00f5 rcl dx, 1
00f7 add ax, cx
00f9 adc dx, bx
00fb mov word ptr [bp - 0xc], ax
00fe mov word ptr [bp - 0xa], dx
0101 mov ax, word ptr [bp - 0x1e]
0104 sar ax, 1
0106 cdq 
0107 mov word ptr [bp - 8], ax
010a mov word ptr [bp - 6], dx
010d mov ax, word ptr [bp - 0x1a]
0110 sar ax, 1
0112 cdq 
0113 cmp word ptr [bp - 6], dx
0116 jle 0x201f
0118 jmp 0x244b
011b jl 0x2029
011d cmp word ptr [bp - 8], ax
0120 jb 0x2029
0122 jmp 0x244b
0125 push word ptr [bp - 0x16]
0128 push word ptr [bp - 0x18]
012b mov ax, word ptr [bp + 0x18]
012e cdq 
012f add ax, word ptr [bp - 0x10]
0132 adc dx, word ptr [bp - 0xe]
0135 push dx
0136 push ax
0137 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
013c add ax, word ptr [bp - 0x24]
013f adc dx, word ptr [bp - 0x22]
0142 mov word ptr [bp - 0x2c], ax
0145 mov word ptr [bp - 0x2a], dx
0148 push 0
014a push 4
014c push word ptr [bp - 6]
014f push word ptr [bp - 8]
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0157 add ax, word ptr [bp - 0xc]
015a adc dx, word ptr [bp - 0xa]
015d add ax, word ptr [bp - 0x14]
0160 adc dx, word ptr [bp - 0x12]
0163 mov word ptr [bp - 4], ax
0166 mov word ptr [bp - 2], dx
0169 push 0
016b push 4
016d push word ptr [bp - 6]
0170 push word ptr [bp - 8]
0173 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 374, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFlrem
0178 shl ax, 1
017a mov si, 7
017d sub si, ax
017f mov ax, word ptr [bp - 8]
0182 mov dx, word ptr [bp - 6]
0185 sar dx, 1
0187 rcr ax, 1
0189 sar dx, 1
018b rcr ax, 1
018d add ax, word ptr [bp - 0xc]
0190 adc dx, word ptr [bp - 0xa]
0193 add ax, word ptr [bp + 0xa]
0196 adc dx, 0
0199 mov <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
019c shl dx, cl
019e add dx, word ptr [bp + 0xc]
01a1 mov es, dx
01a3 mov bx, ax
01a5 mov al, byte ptr es:[bx]
01a8 sub ah, ah
01aa mov cl, byte ptr [bp - 8]
01ad and cl, 3
01b0 shl cl, 1
01b2 shl ax, cl
01b4 and ax, 0xc0
01b7 sub ax, 0x40
01ba je 0x210a
01bc sub ax, 0x40
01bf jne 0x20c8
01c1 jmp 0x2208
01c4 sub ax, 0x40
01c7 jne 0x20d0
01c9 jmp 0x22fc
01cc jmp 0x242b
01cf nop 
01d0 mov word ptr [bp - 0x1e], 0
01d5 mov ax, word ptr [bp + 0x16]
01d8 add ax, bx
01da cmp ax, di
01dc jg 0x20e5
01de jmp 0x1f6f
01e1 sub di, word ptr [bp + 0x16]
01e4 mov word ptr [bp - 0x1a], di
01e7 jmp 0x1f72
01ea mov word ptr [bp - 0x20], 0
01ef mov dx, word ptr [bp + 0xe]
01f2 mov ax, word ptr [bp + 0x12]
01f5 add ax, bx
01f7 cmp ax, dx
01f9 jg 0x2102
01fb jmp 0x1f83
01fe sub dx, bx
0200 mov word ptr [bp - 0x1c], dx
0203 jmp 0x1f89
0206 mov ax, word ptr [bp - 4]
0209 mov dx, word ptr [bp - 2]
020c add ax, word ptr [bp + 0xa]
020f adc dx, 0
0212 mov <resolved loader operand; see bindings> ; [{'operand_offset': 531, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0215 shl dx, cl
0217 add dx, word ptr [bp + 0xc]
021a mov es, dx
021c mov bx, ax
021e mov al, byte ptr es:[bx]
0221 lea cx, [si - 1]
0224 shr al, cl
0226 and al, 1
0228 mov bx, ax
022a mov ax, word ptr [bp - 0x2c]
022d mov dx, word ptr [bp - 0x2a]
0230 add ax, word ptr [bp - 8]
0233 adc dx, word ptr [bp - 6]
0236 mov word ptr [bp - 0x2e], cx
0239 add ax, word ptr [bp + 6]
023c adc dx, 0
023f mov <resolved loader operand; see bindings> ; [{'operand_offset': 576, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0242 shl dx, cl
0244 add dx, word ptr [bp + 8]
0247 mov es, dx
0249 mov cx, bx
024b mov bx, ax
024d mov ax, word ptr [bp - 4]
0250 mov dx, word ptr [bp - 2]
0253 add ax, word ptr [bp - 0x14]
0256 adc dx, word ptr [bp - 0x12]
0259 mov word ptr [bp - 0x30], cx
025c add ax, word ptr [bp + 0xa]
025f adc dx, 0
0262 mov <resolved loader operand; see bindings> ; [{'operand_offset': 611, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0265 shl dx, cl
0267 add dx, word ptr [bp + 0xc]
026a mov cx, es
026c mov word ptr [bp - 0x34], bx
026f mov word ptr [bp - 0x32], es
0272 mov es, dx
0274 mov bx, ax
0276 mov al, byte ptr es:[bx]
0279 mov cl, byte ptr [bp - 0x2e]
027c shr al, cl
027e and al, 1
0280 mov bx, ax
0282 mov ax, word ptr [bp - 0x14]
0285 mov dx, word ptr [bp - 0x12]
0288 shl ax, 1
028a rcl dx, 1
028c add ax, word ptr [bp - 4]
028f adc dx, word ptr [bp - 2]
0292 add ax, word ptr [bp + 0xa]
0295 adc dx, 0
0298 mov <resolved loader operand; see bindings> ; [{'operand_offset': 665, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
029b shl dx, cl
029d add dx, word ptr [bp + 0xc]
02a0 mov es, dx
02a2 mov cx, bx
02a4 mov bx, ax
02a6 mov al, byte ptr es:[bx]
02a9 mov dx, cx
02ab mov cl, byte ptr [bp - 0x2e]
02ae shr al, cl
02b0 and al, 1
02b2 mov bx, ax
02b4 mov cx, dx
02b6 mov ax, word ptr [bp - 0x28]
02b9 mov dx, word ptr [bp - 0x26]
02bc add ax, word ptr [bp - 4]
02bf adc dx, word ptr [bp - 2]
02c2 mov word ptr [bp - 0x36], cx
02c5 add ax, word ptr [bp + 0xa]
02c8 adc dx, 0
02cb mov <resolved loader operand; see bindings> ; [{'operand_offset': 716, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
02ce shl dx, cl
02d0 add dx, word ptr [bp + 0xc]
02d3 mov es, dx
02d5 mov cx, bx
02d7 mov bx, ax
02d9 mov al, byte ptr es:[bx]
02dc mov dx, cx
02de mov cl, byte ptr [bp - 0x2e]
02e1 shr al, cl
02e3 and al, 1
02e5 shl al, 1
02e7 or dl, al
02e9 shl dl, 1
02eb or dl, byte ptr [bp - 0x36]
02ee shl dl, 1
02f0 les bx, ptr [bp - 0x34]
02f3 mov al, byte ptr es:[bx]
02f6 and al, 0xf0
02f8 or dl, al
02fa or dl, byte ptr [bp - 0x30]
02fd mov byte ptr es:[bx], dl
0300 jmp 0x242b
0303 nop 
0304 mov ax, word ptr [bp - 0x2c]
0307 mov dx, word ptr [bp - 0x2a]
030a add ax, word ptr [bp - 8]
030d adc dx, word ptr [bp - 6]
0310 add ax, word ptr [bp + 6]
0313 adc dx, 0
0316 mov <resolved loader operand; see bindings> ; [{'operand_offset': 791, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0319 shl dx, cl
031b add dx, word ptr [bp + 8]
031e mov es, dx
0320 mov bx, ax
0322 mov ax, word ptr [bp - 4]
0325 mov dx, word ptr [bp - 2]
0328 add ax, word ptr [bp + 0xa]
032b adc dx, 0
032e shl dx, cl
0330 add dx, word ptr [bp + 0xc]
0333 mov word ptr [bp - 0x3a], bx
0336 mov word ptr [bp - 0x38], es
0339 mov es, dx
033b mov bx, ax
033d mov al, byte ptr es:[bx]
0340 mov cx, si
0342 shr al, cl
0344 and al, 1
0346 mov bx, ax
0348 mov ax, word ptr [bp - 4]
034b mov dx, word ptr [bp - 2]
034e add ax, word ptr [bp - 0x14]
0351 adc dx, word ptr [bp - 0x12]
0354 add ax, word ptr [bp + 0xa]
0357 adc dx, 0
035a mov <resolved loader operand; see bindings> ; [{'operand_offset': 859, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
035d shl dx, cl
035f add dx, word ptr [bp + 0xc]
0362 mov es, dx
0364 mov cx, bx
0366 mov bx, ax
0368 mov al, byte ptr es:[bx]
036b mov dx, cx
036d mov cx, si
036f shr al, cl
0371 and al, 1
0373 mov bx, ax
0375 mov cx, dx
0377 mov ax, word ptr [bp - 0x14]
037a mov dx, word ptr [bp - 0x12]
037d shl ax, 1
037f rcl dx, 1
0381 add ax, word ptr [bp - 4]
0384 adc dx, word ptr [bp - 2]
0387 mov word ptr [bp - 0x3c], cx
038a add ax, word ptr [bp + 0xa]
038d adc dx, 0
0390 mov <resolved loader operand; see bindings> ; [{'operand_offset': 913, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0393 shl dx, cl
0395 add dx, word ptr [bp + 0xc]
0398 mov es, dx
039a mov cx, bx
039c mov bx, ax
039e mov al, byte ptr es:[bx]
03a1 mov dx, cx
03a3 mov cx, ax
03a5 mov bx, dx
03a7 mov ax, word ptr [bp - 0x28]
03aa mov dx, word ptr [bp - 0x26]
03ad add ax, word ptr [bp - 4]
03b0 adc dx, word ptr [bp - 2]
03b3 mov word ptr [bp - 0x3e], cx
03b6 add ax, word ptr [bp + 0xa]
03b9 adc dx, 0
03bc mov <resolved loader operand; see bindings> ; [{'operand_offset': 957, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
03bf shl dx, cl
03c1 add dx, word ptr [bp + 0xc]
03c4 mov es, dx
03c6 mov word ptr [bp - 0x40], bx
03c9 mov bx, ax
03cb mov al, byte ptr es:[bx]
03ce mov cx, si
03d0 shr al, cl
03d2 shl al, 1
03d4 mov dl, byte ptr [bp - 0x3e]
03d7 shr dl, cl
03d9 and dl, 1
03dc or dl, al
03de shl dl, 1
03e0 or dl, byte ptr [bp - 0x40]
03e3 shl dl, 1
03e5 or dl, byte ptr [bp - 0x3c]
03e8 shl dl, 4
03eb les bx, ptr [bp - 0x3a]
03ee mov al, byte ptr es:[bx]
03f1 and al, 0xf
03f3 or dl, al
03f5 jmp 0x2201
03f8 mov ax, word ptr [bp - 4]
03fb mov dx, word ptr [bp - 2]
03fe add ax, word ptr [bp + 0xa]
0401 adc dx, 0
0404 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1029, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0407 shl dx, cl
0409 add dx, word ptr [bp + 0xc]
040c mov es, dx
040e mov bx, ax
0410 mov al, byte ptr es:[bx]
0413 mov cx, si
0415 dec cl
0417 mov bx, ax
0419 shr al, cl
041b mov word ptr [bp - 0x42], ax
041e mov dx, cx
0420 mov cx, si
0422 mov ax, dx
0424 mov word ptr [bp - 0x44], ax
0427 mov ax, word ptr [bp - 4]
042a mov dx, word ptr [bp - 2]
042d add ax, word ptr [bp - 0x14]
0430 adc dx, word ptr [bp - 0x12]
0433 mov word ptr [bp - 0x46], cx
0436 add ax, word ptr [bp + 0xa]
0439 adc dx, 0
043c mov <resolved loader operand; see bindings> ; [{'operand_offset': 1085, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
043f shl dx, cl
0441 add dx, word ptr [bp + 0xc]
0444 mov es, dx
0446 mov si, ax
0448 mov al, byte ptr es:[si]
044b mov cl, byte ptr [bp - 0x46]
044e mov dx, ax
0450 shr al, cl
0452 and al, 1
0454 mov cx, ax
0456 mov ax, dx
0458 mov word ptr [bp - 0x48], ax
045b mov ax, word ptr [bp - 0x28]
045e mov dx, word ptr [bp - 0x26]
0461 add ax, word ptr [bp - 4]
0464 adc dx, word ptr [bp - 2]
0467 mov word ptr [bp - 0x4a], cx
046a add ax, word ptr [bp + 0xa]
046d adc dx, 0
0470 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1137, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0473 shl dx, cl
0475 add dx, word ptr [bp + 0xc]
0478 mov es, dx
047a mov si, ax
047c mov al, byte ptr es:[si]
047f mov cl, byte ptr [bp - 0x46]
0482 mov dx, ax
0484 shr al, cl
0486 shl al, 1
0488 mov cx, ax
048a mov ax, dx
048c mov word ptr [bp - 0x4c], ax
048f mov ax, word ptr [bp - 0x14]
0492 mov dx, word ptr [bp - 0x12]
0495 shl ax, 1
0497 rcl dx, 1
0499 add ax, word ptr [bp - 4]
049c adc dx, word ptr [bp - 2]
049f mov word ptr [bp - 0x4e], cx
04a2 add ax, word ptr [bp + 0xa]
04a5 adc dx, 0
04a8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1193, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
04ab shl dx, cl
04ad add dx, word ptr [bp + 0xc]
04b0 mov es, dx
04b2 mov si, ax
04b4 mov al, byte ptr es:[si]
04b7 mov cl, byte ptr [bp - 0x44]
04ba mov dx, ax
04bc shr al, cl
04be and al, 1
04c0 mov cl, byte ptr [bp - 0x46]
04c3 shr dl, cl
04c5 and dl, 1
04c8 or dl, byte ptr [bp - 0x4e]
04cb shl dl, 1
04cd or dl, byte ptr [bp - 0x4a]
04d0 shl dl, 1
04d2 shr bl, cl
04d4 and bl, 1
04d7 or dl, bl
04d9 shl dl, 1
04db mov cl, byte ptr [bp - 0x44]
04de mov bl, byte ptr [bp - 0x4c]
04e1 shr bl, cl
04e3 and bl, 1
04e6 or dl, bl
04e8 shl dl, 1
04ea or al, dl
04ec shl al, 1
04ee mov dl, byte ptr [bp - 0x48]
04f1 shr dl, cl
04f3 and dl, 1
04f6 or al, dl
04f8 shl al, 1
04fa mov cl, byte ptr [bp - 0x42]
04fd and cl, 1
0500 or al, cl
0502 mov cx, ax
0504 mov ax, word ptr [bp - 0x2c]
0507 mov dx, word ptr [bp - 0x2a]
050a add ax, word ptr [bp - 8]
050d adc dx, word ptr [bp - 6]
0510 mov bx, cx
0512 add ax, word ptr [bp + 6]
0515 adc dx, 0
0518 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1305, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
051b shl dx, cl
051d add dx, word ptr [bp + 8]
0520 mov es, dx
0522 mov si, ax
0524 mov byte ptr es:[si], bl
0527 mov ax, word ptr [bp - 0x1a]
052a sar ax, 1
052c cdq 
052d add word ptr [bp - 8], 1
0531 adc word ptr [bp - 6], 0
0535 cmp dx, word ptr [bp - 6]
0538 jle 0x2441
053a jmp 0x204c
053d jl 0x244b
053f cmp ax, word ptr [bp - 8]
0542 jbe 0x244b
0544 jmp 0x204c
0547 mov ax, word ptr [bp - 0x1c]
054a cdq 
054b add word ptr [bp - 0x10], 1
054f adc word ptr [bp - 0xe], 0
0553 cmp dx, word ptr [bp - 0xe]
0556 jle 0x245f
0558 jmp 0x1fd2
055b jl 0x2469
055d cmp ax, word ptr [bp - 0x10]
0560 jbe 0x2469
0562 jmp 0x1fd2
0565 pop si
0566 pop di
0567 leave 
0568 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ConvertMaskBitmap', 'offset': 7090, 'source': None, 'size': 703}
- {'symbol': '_CalcBitmapStuff', 'offset': 7794, 'source': 'src/recovered/wf_CalcBitmapStuff-605c34021c.c', 'size': 146}
- {'symbol': '_ConvertBitmap', 'offset': 9326, 'source': None, 'size': 674}
- {'symbol': '_ConvertBitmap2', 'offset': 10000, 'source': None, 'size': 816}

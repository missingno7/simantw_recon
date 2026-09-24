# Recovery task _myBeginSound

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 2263 bytes.

```asm
0000 enter 0x5c, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbf78]
000a cmp word ptr es:[0x8d06], 0
0010 jne 0x98c5
0012 jmp 0xa183
0015 cmp word ptr [0xaf8], 0 ; _effectsOnFlag
001a jne 0x98cf
001c jmp 0xa183
001f mov si, word ptr [bp + 6]
0022 push 1
0024 mov bx, 0x8d28
0027 mov word ptr [bp - 0x48], bx
002a mov word ptr [bp - 0x46], es
002d cmp word ptr es:[bx], 1
0031 sbb ax, ax
0033 and al, 0xd2
0035 add ax, 0x33
0038 push ax
0039 push si
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
003f add sp, 6
0042 mov word ptr [bp - 0x1a], ax
0045 or ax, ax
0047 jne 0x98fc
0049 jmp 0xa176
004c push si
004d push ds
004e push 0x123c
0051 nop 
0052 push cs
0053 call 0x62bc ; _WinPrintf
0056 add sp, 6
0059 mov bx, 0x8d08
005c mov es, word ptr [0xbf78]
0060 mov word ptr [bp - 0x4c], bx
0063 mov word ptr [bp - 0x4a], es
0066 cmp word ptr es:[bx], 0
006a jne 0x991f
006c jmp 0x9fd6
006f cmp word ptr es:[0x8d0a], 0
0075 je 0x992a
0077 jmp 0x9b8c
007a push word ptr es:[bx]
007d push ds
007e push 0x1349
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0086 mov word ptr [bp - 0xa], ax
0089 mov word ptr [bp - 8], dx
008c mov bx, 0x8d22
008f mov es, word ptr [0xbf78]
0093 mov word ptr [bp - 0x50], bx
0096 mov word ptr [bp - 0x4e], es
0099 cmp word ptr es:[bx], 0
009d jne 0x9952
009f jmp 0x99d4
00a2 les bx, ptr [bp - 0x4c]
00a5 push word ptr es:[bx]
00a8 push ds
00a9 push 0x1357
00ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00b1 mov word ptr [bp - 0x52], dx
00b4 mov word ptr [bp - 0x54], ax
00b7 lcall [bp - 0x54]
00ba mov word ptr [bp - 6], ax
00bd or ax, ax
00bf je 0x997e
00c1 push ax
00c2 push ds
00c3 push 0x1364
00c6 nop 
00c7 push cs
00c8 call 0x62bc ; _WinPrintf
00cb add sp, 6
00ce les bx, ptr [bp - 0x4c]
00d1 push word ptr es:[bx]
00d4 push ds
00d5 push 0xc5e
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00dd mov word ptr [bp - 4], ax
00e0 mov word ptr [bp - 2], dx
00e3 or dx, ax
00e5 je 0x999a
00e7 lcall [bp - 4]
00ea mov es, word ptr [0xbf78]
00ee push word ptr es:[0x8d26]
00f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
00f8 les bx, ptr [bp - 0x50]
00fb push word ptr es:[bx]
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 255, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
0103 les bx, ptr [bp - 0x50]
0106 push word ptr es:[bx]
0109 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 266, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
010e les bx, ptr [bp - 0x50]
0111 mov word ptr es:[bx], 0
0116 mov es, word ptr [0xbf78]
011a sub ax, ax
011c mov word ptr es:[0x8d26], ax
0120 mov word ptr es:[0x8d24], ax
0124 push word ptr [0xcd78] ; _rootWnd
0128 lcall [bp - 0xa]
012b mov word ptr [bp - 6], ax
012e or ax, ax
0130 je 0x99f2
0132 push ax
0133 push ds
0134 push 0x1383
0137 nop 
0138 push cs
0139 call 0x62bc ; _WinPrintf
013c add sp, 6
013f jmp 0xa166
0142 les bx, ptr [bp - 0x4c]
0145 push word ptr es:[bx]
0148 push ds
0149 push 0x13a3
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 333, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0151 mov word ptr [bp - 0x12], ax
0154 mov word ptr [bp - 0x10], dx
0157 push word ptr [bp - 0x1a]
015a nop 
015b push cs
015c call 0x558e ; _mem_Lock
015f add sp, 2
0162 mov word ptr [bp - 0xc], ax
0165 mov word ptr [bp - 0xa], dx
0168 push 2
016a push 5
016c push si
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_GetObjectSize
0172 add sp, 4
0175 sub ax, 0x10
0178 shl ax, 1
017a mov word ptr [bp - 0xe], ax
017d push 0
017f push ax
0180 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 385, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
0185 les bx, ptr [bp - 0x50]
0188 mov word ptr es:[bx], ax
018b push ax
018c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 397, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 111}}]
0191 mov bx, 0x8d24
0194 mov es, word ptr [0xbf78]
0198 mov word ptr [bp - 0x58], bx
019b mov word ptr [bp - 0x56], es
019e mov word ptr es:[bx], ax
01a1 mov word ptr es:[bx + 2], dx
01a5 mov ax, word ptr [bp - 0xe]
01a8 mov word ptr [bp - 8], ax
01ab mov ax, word ptr es:[bx]
01ae mov word ptr [bp - 0x16], ax
01b1 mov word ptr [bp - 0x14], dx
01b4 mov byte ptr [bp - 1], 0x80
01b8 mov ax, word ptr [bp - 0xc]
01bb mov dx, word ptr [bp - 0xa]
01be mov cx, 8
01c1 push ds
01c2 lea di, [bp - 0x2a]
01c5 mov si, ax
01c7 push ss
01c8 pop es
01c9 mov ds, dx
01cb rep movsw word ptr es:[di], word ptr [si]
01cd pop ds
01ce add ax, 0x10
01d1 mov word ptr [bp - 6], ax
01d4 mov word ptr [bp - 4], dx
01d7 xor di, di
01d9 mov si, di
01db shr word ptr [bp - 8], 1
01de cmp word ptr [bp - 8], si
01e1 je 0x9adb
01e3 mov cx, ax
01e5 mov ds, dx
01e7 mov bx, cx
01e9 add bx, di
01eb mov bl, byte ptr [bx]
01ed mov ax, bx
01ef shr bl, 4
01f2 sub bh, bh
01f4 lea dx, [bp - 0x2a]
01f7 add bx, dx
01f9 mov dl, byte ptr ss:[bx]
01fc add byte ptr [bp - 1], dl
01ff les bx, ptr [bp - 0x16]
0202 mov dl, byte ptr [bp - 1]
0205 mov byte ptr es:[bx + si], dl
0208 mov bl, al
020a and bx, 0xf
020d lea ax, [bp - 0x2a]
0210 add bx, ax
0212 mov al, byte ptr ss:[bx]
0215 add byte ptr [bp - 1], al
0218 les bx, ptr [bp - 0x16]
021b inc si
021c mov al, byte ptr [bp - 1]
021f mov byte ptr es:[bx + si], al
0222 inc si
0223 inc di
0224 cmp di, word ptr [bp - 8]
0227 jb 0x9a97
0229 push ss
022a pop ds
022b les bx, ptr [bp - 0x58]
022e push word ptr es:[bx + 2]
0232 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 563, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 191}}]
0237 push word ptr [bp - 0xe]
023a push ds
023b push 0x13b6
023e nop 
023f push cs
0240 call 0x62bc ; _WinPrintf
0243 add sp, 6
0246 les bx, ptr [bp - 0x58]
0249 push word ptr es:[bx + 2]
024d push word ptr es:[bx]
0250 push 0x1000
0253 push 0
0255 push word ptr [bp - 0xe]
0258 lcall [bp - 0x12]
025b mov word ptr [bp - 6], ax
025e or ax, ax
0260 je 0x9b71
0262 push ax
0263 push ds
0264 push 0x13d6
0267 nop 
0268 push cs
0269 call 0x62bc ; _WinPrintf
026c add sp, 6
026f les bx, ptr [bp - 0x4c]
0272 push word ptr es:[bx]
0275 push ds
0276 push 0xc5e
0279 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 634, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
027e mov word ptr [bp - 4], ax
0281 mov word ptr [bp - 2], dx
0284 or dx, ax
0286 je 0x9b3b
0288 lcall [bp - 4]
028b les bx, ptr [bp - 0x58]
028e push word ptr es:[bx + 2]
0292 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 659, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
0297 les bx, ptr [bp - 0x50]
029a push word ptr es:[bx]
029d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 670, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
02a2 les bx, ptr [bp - 0x50]
02a5 push word ptr es:[bx]
02a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 681, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
02ad les bx, ptr [bp - 0x50]
02b0 mov word ptr es:[bx], 0
02b5 les bx, ptr [bp - 0x58]
02b8 sub ax, ax
02ba mov word ptr es:[bx + 2], ax
02be mov word ptr es:[bx], ax
02c1 push word ptr [bp - 0x1a]
02c4 nop 
02c5 push cs
02c6 call 0x559c ; _mem_Unlock
02c9 add sp, 2
02cc push ds
02cd push 0x13fb
02d0 nop 
02d1 push cs
02d2 call 0x62bc ; _WinPrintf
02d5 add sp, 4
02d8 jmp 0xa166
02db nop 
02dc lea ax, [bp - 0x44]
02df push ss
02e0 push ax
02e1 push 0
02e3 push 0x3bd
02e6 push 0x3bd
02e9 push 1
02eb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 748, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
02f0 or ax, ax
02f2 je 0x9bd0
02f4 lea ax, [bp - 0x44]
02f7 push ss
02f8 push ax
02f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 762, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 113}}]
02fe lea ax, [bp - 0x44]
0301 push ss
0302 push ax
0303 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 772, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 114}}]
0308 lea ax, [bp - 0x44]
030b push ss
030c push ax
030d push 0
030f push 0x3bd
0312 push 0x3bd
0315 push 1
0317 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 792, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
031c or ax, ax
031e jne 0x9ba4
0320 mov bx, 0x8d14
0323 mov es, word ptr [0xbf78]
0327 mov word ptr [bp - 0x5c], bx
032a mov word ptr [bp - 0x5a], es
032d cmp word ptr es:[bx], 0
0331 jne 0x9be6
0333 jmp 0x9d49
0336 cmp word ptr [0xaf0], 0
033b jne 0x9bf0
033d jmp 0x9d49
0340 cmp word ptr [0xaf2], 0
0345 jne 0x9bfa
0347 jmp 0x9d49
034a push ds
034b push 0x1257
034e nop 
034f push cs
0350 call 0x62bc ; _WinPrintf
0353 add sp, 4
0356 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 855, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 13}}]
035b cmp dx, word ptr [0x123a]
035f jge 0x9c14
0361 jmp 0xa183
0364 jg 0x9c1f
0366 cmp ax, word ptr [0x1238]
036a ja 0x9c1f
036c jmp 0xa183
036f les bx, ptr [bp - 0x4c]
0372 push word ptr es:[bx]
0375 push ds
0376 push 0x1272
0379 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 890, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
037e mov word ptr [bp - 0xc], ax
0381 mov word ptr [bp - 0xa], dx
0384 les bx, ptr [bp - 0x4c]
0387 push word ptr es:[bx]
038a push ds
038b push 0x127f
038e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 911, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0393 mov word ptr [bp - 8], ax
0396 mov word ptr [bp - 6], dx
0399 les bx, ptr [bp - 0x5c]
039c push word ptr es:[bx]
039f lcall [bp - 0xc]
03a2 push word ptr [0xaf0]
03a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 935, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 18}}]
03ab mov es, dx
03ad mov bx, ax
03af mov word ptr [bp - 4], bx
03b2 mov word ptr [bp - 2], es
03b5 push word ptr es:[bx + 0x12]
03b9 push word ptr es:[bx + 0x10]
03bd push ds
03be push 0x1296
03c1 nop 
03c2 push cs
03c3 call 0x62bc ; _WinPrintf
03c6 add sp, 8
03c9 les bx, ptr [bp - 4]
03cc mov ax, word ptr es:[bx + 0x10]
03d0 mov dx, word ptr es:[bx + 0x12]
03d4 and al, 0xe0
03d6 or dx, ax
03d8 jne 0x9cd2
03da les bx, ptr [bp - 0x5c]
03dd push word ptr es:[bx]
03e0 push word ptr [bp - 2]
03e3 push word ptr [bp - 4]
03e6 push 0x20
03e8 lcall [bp - 8]
03eb push word ptr [0xaf0]
03ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1008, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
03f4 mov di, word ptr [0xaf0]
03f8 mov si, word ptr [0xaf2]
03fc or si, si
03fe je 0x9cc2
0400 push si
0401 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1026, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
0406 push si
0407 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1032, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
040c mov word ptr [0xaf2], 0
0412 cmp word ptr [0xaf0], 0
0417 je 0x9d14
0419 push di
041a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1051, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
041f push di
0420 jmp 0x9d09
0422 push word ptr [0xaf0]
0426 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1063, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
042b xor ax, ax
042d mov word ptr [0xaf2], ax
0430 mov word ptr [0xaf0], ax
0433 mov si, ax
0435 mov di, ax
0437 cmp di, ax
0439 je 0x9cfb
043b push di
043c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1085, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
0441 push di
0442 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1091, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0447 mov word ptr [0xaf2], si
044b cmp word ptr [0xaf0], 0
0450 je 0x9d14
0452 push si
0453 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1108, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
0458 push si
0459 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1114, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
045e mov word ptr [0xaf0], 0
0464 mov es, word ptr [0xbf78]
0468 dec word ptr es:[0x8d1a]
046d jne 0x9d49
046f les bx, ptr [bp - 0x4c]
0472 push word ptr es:[bx]
0475 push ds
0476 push 0xc6d
0479 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1146, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
047e mov word ptr [bp - 4], ax
0481 mov word ptr [bp - 2], dx
0484 or dx, ax
0486 je 0x9d41
0488 les bx, ptr [bp - 0x5c]
048b push word ptr es:[bx]
048e lcall [bp - 4]
0491 les bx, ptr [bp - 0x5c]
0494 mov word ptr es:[bx], 0
0499 les bx, ptr [bp - 0x4c]
049c push word ptr es:[bx]
049f push ds
04a0 push 0x12b0
04a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1188, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
04a8 mov word ptr [bp - 4], ax
04ab mov word ptr [bp - 2], dx
04ae push 2
04b0 push 0x10
04b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1203, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 5}}]
04b7 mov word ptr [bp - 0x14], ax
04ba push ax
04bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1212, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 8}}]
04c0 mov bx, ax
04c2 mov word ptr [bx], 1
04c6 mov word ptr [bx + 2], 1
04cb mov word ptr [bx + 4], 0x1000
04d0 mov word ptr [bx + 6], 0
04d5 mov word ptr [bx + 8], 0x1000
04da mov word ptr [bx + 0xa], 0
04df mov word ptr [bx + 0xc], 1
04e4 mov word ptr [bx + 0xe], 8
04e9 push word ptr [bp - 0x5a]
04ec push word ptr [bp - 0x5c]
04ef push -1
04f1 push ds
04f2 push bx
04f3 push 0
04f5 push word ptr [0xcd78] ; _rootWnd
04f9 push 0
04fb push 0
04fd push 1
04ff push 0
0501 lcall [bp - 4]
0504 mov si, ax
0506 or si, si
0508 jne 0x9dc6
050a push word ptr [bp - 0x1a]
050d nop 
050e push cs
050f call 0x959c ; _MciOutWave
0512 jmp 0x9f78
0515 nop 
0516 les bx, ptr [bp - 0x4c]
0519 push word ptr es:[bx]
051c push ds
051d push 0x12bc
0520 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1313, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0525 mov word ptr [bp - 0x18], ax
0528 mov word ptr [bp - 0x16], dx
052b push si
052c push ds
052d push 0x12c9
0530 nop 
0531 push cs
0532 call 0x62bc ; _WinPrintf
0535 add sp, 6
0538 mov ax, word ptr [bp - 0x16]
053b or ax, word ptr [bp - 0x18]
053e jne 0x9df3
0540 jmp 0x9f7b
0543 push word ptr [bp - 0x1a]
0546 nop 
0547 push cs
0548 call 0x558e ; _mem_Lock
054b add sp, 2
054e mov word ptr [bp - 0x12], ax
0551 mov word ptr [bp - 0x10], dx
0554 push 0x2002
0557 push 5
0559 push word ptr [bp + 6]
055c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1375, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_GetObjectSize
0561 add sp, 4
0564 mov word ptr [bp - 0xe], ax
0567 sub ax, 0x10
056a shl ax, 1
056c mov word ptr [bp - 0xe], ax
056f add ax, 0x2c
0572 push 0
0574 push ax
0575 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1398, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
057a mov word ptr [0xaf2], ax
057d push ax
057e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1407, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 18}}]
0583 mov word ptr [bp - 6], ax
0586 mov word ptr [bp - 4], dx
0589 mov si, 0x12f8
058c les di, ptr [bp - 6]
058f movsw word ptr es:[di], word ptr [si]
0590 movsw word ptr es:[di], word ptr [si]
0591 movsb byte ptr es:[di], byte ptr [si]
0592 mov ax, word ptr [bp - 0xe]
0595 add ax, 8
0598 mov bx, word ptr [bp - 6]
059b mov word ptr es:[bx + 4], ax
059f mov word ptr es:[bx + 6], 0
05a5 push es
05a6 lea di, [bx + 8]
05a9 mov si, 0x12fd
05ac movsw word ptr es:[di], word ptr [si]
05ad movsw word ptr es:[di], word ptr [si]
05ae movsb byte ptr es:[di], byte ptr [si]
05af pop es
05b0 push es
05b1 lea di, [bx + 0xc]
05b4 mov si, 0x1302
05b7 movsw word ptr es:[di], word ptr [si]
05b8 movsw word ptr es:[di], word ptr [si]
05b9 movsb byte ptr es:[di], byte ptr [si]
05ba pop es
05bb mov word ptr es:[bx + 0x10], 0x10
05c1 mov word ptr es:[bx + 0x12], 0
05c7 mov ax, 0x1000
05ca cdq 
05cb lea si, [bx + 0x14]
05ce mov word ptr es:[si + 4], ax
05d2 mov word ptr es:[si + 6], dx
05d6 mov word ptr es:[si + 8], ax
05da mov word ptr es:[si + 0xa], 0
05e0 mov ax, 1
05e3 mov word ptr es:[si], ax
05e6 mov word ptr es:[si + 2], ax
05ea mov word ptr es:[si + 0xc], ax
05ee mov word ptr es:[si + 0xe], 8
05f4 push es
05f5 lea di, [bx + 0x24]
05f8 mov si, 0x1307
05fb movsw word ptr es:[di], word ptr [si]
05fc movsw word ptr es:[di], word ptr [si]
05fd movsb byte ptr es:[di], byte ptr [si]
05fe pop es
05ff mov ax, word ptr [bp - 0xe]
0602 mov word ptr es:[bx + 0x28], ax
0606 mov word ptr es:[bx + 0x2a], 0
060c mov word ptr [bp - 0xc], ax
060f mov byte ptr [bp - 1], 0x80
0613 mov ax, word ptr [bp - 0x12]
0616 mov dx, word ptr [bp - 0x10]
0619 mov cx, 8
061c push ds
061d lea di, [bp - 0x32]
0620 mov si, ax
0622 push ss
0623 pop es
0624 mov ds, dx
0626 rep movsw word ptr es:[di], word ptr [si]
0628 pop ds
0629 add ax, 0x10
062c mov word ptr [bp - 0xa], ax
062f mov word ptr [bp - 8], dx
0632 xor di, di
0634 mov si, di
0636 shr word ptr [bp - 0xc], 1
0639 cmp word ptr [bp - 0xc], si
063c je 0x9f37
063e mov cx, word ptr [bp - 6]
0641 mov ds, word ptr [bp - 4]
0644 mov es, dx
0646 mov bx, word ptr [bp - 0xa]
0649 add bx, di
064b mov bl, byte ptr es:[bx]
064e mov ax, bx
0650 shr bl, 4
0653 sub bh, bh
0655 lea dx, [bp - 0x32]
0658 add bx, dx
065a mov dl, byte ptr ss:[bx]
065d add byte ptr [bp - 1], dl
0660 mov dl, byte ptr [bp - 1]
0663 mov bx, cx
0665 mov byte ptr [bx + si + 0x2c], dl
0668 mov bl, al
066a and bx, 0xf
066d lea ax, [bp - 0x32]
0670 add bx, ax
0672 add dl, byte ptr ss:[bx]
0675 mov byte ptr [bp - 1], dl
0678 mov bx, cx
067a inc si
067b mov byte ptr [bx + si + 0x2c], dl
067e inc si
067f inc di
0680 cmp di, word ptr [bp - 0xc]
0683 jb 0x9ef6
0685 push ss
0686 pop ds
0687 push word ptr [bp - 4]
068a push word ptr [bp - 6]
068d push 0x14
068f lcall [bp - 0x18]
0692 or ax, ax
0694 je 0x9f4c
0696 push ds
0697 push 0x130c
069a jmp 0x9f50
069c push ds
069d push 0x1321
06a0 nop 
06a1 push cs
06a2 call 0x62bc ; _WinPrintf
06a5 add sp, 4
06a8 push word ptr [0xaf2]
06ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1709, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
06b1 push word ptr [0xaf2]
06b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1718, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
06ba mov word ptr [0xaf2], 0
06c0 push word ptr [bp - 0x1a]
06c3 nop 
06c4 push cs
06c5 call 0x559c ; _mem_Unlock
06c8 add sp, 2
06cb push word ptr [bp - 0x14]
06ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1743, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 9}}]
06d3 push word ptr [bp - 0x14]
06d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1751, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 7}}]
06db les bx, ptr [bp - 0x5c]
06de cmp word ptr es:[bx], 0
06e2 jne 0x9f97
06e4 jmp 0xa166
06e7 les bx, ptr [bp - 0x4c]
06ea push word ptr es:[bx]
06ed push ds
06ee push 0x1336
06f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1778, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
06f6 mov word ptr [bp - 4], ax
06f9 mov word ptr [bp - 2], dx
06fc mov word ptr [bp - 0x22], 1
0701 les bx, ptr [bp - 0x5c]
0704 push word ptr es:[bx]
0707 lea ax, [bp - 0x22]
070a push ss
070b push ax
070c push 8
070e lcall [bp - 4]
0711 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1810, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 13}}]
0716 add ax, word ptr [bp - 0x20]
0719 adc dx, word ptr [bp - 0x1e]
071c mov word ptr [0x1238], ax
071f mov word ptr [0x123a], dx
0723 jmp 0xa166
0726 les bx, ptr [bp - 0x48]
0729 cmp word ptr es:[bx], 0
072d jne 0x9fe2
072f jmp 0xa166
0732 push word ptr es:[bx]
0735 push ds
0736 push 0x1415
0739 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1850, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
073e mov word ptr [bp - 0xa], ax
0741 mov word ptr [bp - 8], dx
0744 or dx, ax
0746 jne 0x9ffb
0748 jmp 0xa166
074b push 0
074d push 0
074f push 0x7f02
0752 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1875, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
0757 push ax
0758 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1881, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 69}}]
075d mov si, ax
075f les bx, ptr [bp - 0x4c]
0762 cmp word ptr es:[bx], 0
0766 jne 0xa01b
0768 jmp 0xa110
076b mov es, word ptr [0xbf78]
076f cmp word ptr es:[0x8d0c], 0
0775 je 0xa02a
0777 jmp 0xa110
077a cmp word ptr es:[0x8d0a], 0
0780 je 0xa082
0782 mov es, word ptr [bp - 0x4a]
0785 push word ptr es:[bx]
0788 push ds
0789 push 0xcb6
078c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1933, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0791 mov word ptr [bp - 4], ax
0794 mov word ptr [bp - 2], dx
0797 push ds
0798 push 0xcc5
079b nop 
079c push cs
079d call 0x62bc ; _WinPrintf
07a0 add sp, 4
07a3 mov ax, word ptr [bp - 2]
07a6 or ax, word ptr [bp - 4]
07a9 je 0xa073
07ab mov es, word ptr [0xbf78]
07af push word ptr es:[0x8d0e]
07b4 push 0x804
07b7 push 0
07b9 push 0
07bb lea ax, [bp - 0xe]
07be push ss
07bf push ax
07c0 lcall [bp - 4]
07c3 mov es, word ptr [0xbf78]
07c7 mov word ptr es:[0x8d0e], 0
07ce jmp 0xa115
07d1 nop 
07d2 mov es, word ptr [bp - 0x4a]
07d5 push word ptr es:[bx]
07d8 push ds
07d9 push 0xcd9
07dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2013, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
07e1 mov word ptr [bp - 4], ax
07e4 mov word ptr [bp - 2], dx
07e7 or dx, ax
07e9 je 0xa0b2
07eb lcall [bp - 4]
07ee mov word ptr [bp - 6], ax
07f1 or ax, ax
07f3 je 0xa0b2
07f5 push ax
07f6 push ds
07f7 push 0xce6
07fa nop 
07fb push cs
07fc call 0x62bc ; _WinPrintf
07ff add sp, 6
0802 les bx, ptr [bp - 0x4c]
0805 push word ptr es:[bx]
0808 push ds
0809 push 0xc4f
080c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2061, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0811 mov word ptr [bp - 4], ax
0814 mov word ptr [bp - 2], dx
0817 or dx, ax
0819 je 0xa0ce
081b lcall [bp - 4]
081e mov es, word ptr [0xbf78]
0822 push word ptr es:[0x8d20]
0827 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2088, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
082c mov es, word ptr [0xbf78]
0830 push word ptr es:[0x8d1c]
0835 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2102, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
083a mov es, word ptr [0xbf78]
083e push word ptr es:[0x8d1c]
0843 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2116, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0848 mov es, word ptr [0xbf78]
084c mov word ptr es:[0x8d1c], 0
0853 sub ax, ax
0855 mov word ptr es:[0x8d20], ax
0859 mov word ptr es:[0x8d1e], ax
085d jmp 0xa115
085f nop 
0860 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2145, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 2}}]
0865 push word ptr [bp - 0x1a]
0868 nop 
0869 push cs
086a call 0x558e ; _mem_Lock
086d add sp, 2
0870 mov di, ax
0872 mov word ptr [bp - 2], dx
0875 push word ptr [bp - 0x1a]
0878 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2169, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 191}}]
087d push word ptr [bp - 2]
0880 push di
0881 push 0x33
0883 push word ptr [bp + 6]
0886 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_GetObjectSize
088b add sp, 4
088e push 0
0890 push ax
0891 push word ptr [bp + 8]
0894 push 0
0896 push 0x32
0898 push 4
089a lcall [bp - 0xa]
089d push word ptr [bp - 0x1a]
08a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2209, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
08a5 push word ptr [bp - 0x1a]
08a8 nop 
08a9 push cs
08aa call 0x559c ; _mem_Unlock
08ad add sp, 2
08b0 push si
08b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2226, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 69}}]
08b6 push word ptr [bp - 0x1a]
08b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_ReleaseHandle
08be add sp, 2
08c1 pop si
08c2 pop di
08c3 leave 
08c4 retf 
08c5 nop 
08c6 push si
08c7 push ds
08c8 push 0x141f
08cb nop 
08cc push cs
08cd call 0x62bc ; _WinPrintf
08d0 add sp, 6
08d3 pop si
08d4 pop di
08d5 leave 
08d6 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far effectsOnFlag;` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_ConvertMonoMaskToTandy-4e3e71229c.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_ConvertMonoMaskToTandy-4e3e71229c.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_mem_Lock'], 'segment': 2, 'target_offset': 21902, 'caller_offsets': [348, 1352, 2154]}
- {'callee_names': ['_mem_Unlock'], 'segment': 2, 'target_offset': 21916, 'caller_offsets': [710, 1733, 2218]}
- {'callee_names': ['_WinPrintf'], 'segment': 2, 'target_offset': 25276, 'caller_offsets': [83, 200, 313, 576, 617, 722, 848, 963, 1330, 1698, 1949, 2044, 2253]}
- {'callee_names': ['_MciOutWave'], 'segment': 2, 'target_offset': 38300, 'caller_offsets': [1295]}

## Neighbors

- {'symbol': '_myBeginSong', 'offset': 34190, 'source': None, 'size': 4110}
- {'symbol': '_MciOutWave', 'offset': 38300, 'source': None, 'size': 788}
- {'symbol': '_mySoundIsDone', 'offset': 41352, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 4}
- {'symbol': '_myBeginSoundReverse', 'offset': 41356, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 19}

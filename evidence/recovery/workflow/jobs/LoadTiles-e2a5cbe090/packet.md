# Recovery task _LoadTiles

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 2218 bytes.

```asm
0000 enter 0x38, 0
0004 push di
0005 push si
0006 xor ax, ax
0008 mov bx, 0x78b6
000b mov es, word ptr [0xbf86]
000f mov word ptr [bp - 0x20], bx
0012 mov word ptr [bp - 0x1e], es
0015 mov word ptr es:[bx], ax
0018 mov bx, 0x7d3e
001b mov es, word ptr [0xbf88]
001f mov word ptr [bp - 0x1c], bx
0022 mov word ptr [bp - 0x1a], es
0025 mov word ptr es:[bx], ax
0028 mov bx, 0x9de0
002b mov es, word ptr [0xbf82]
002f mov word ptr [bp - 0x18], bx
0032 mov word ptr [bp - 0x16], es
0035 mov word ptr es:[bx], ax
0038 mov es, word ptr [0xbf8a]
003c cmp word ptr es:[0x8df8], ax
0041 je 0x25a
0043 mov word ptr es:[0x8df8], ax
0047 mov es, word ptr [0xbf80]
004b mov word ptr es:[0x9b6e], ax
004f mov es, word ptr [bp - 0x16]
0052 cmp word ptr es:[bx], ax
0055 je 0x23a
0057 push word ptr es:[bx]
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
005f add sp, 2
0062 push 1
0064 push 9
0066 push 0xa
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
006d add sp, 6
0070 les bx, ptr [bp - 0x18]
0073 mov word ptr es:[bx], ax
0076 push 9
0078 push 0xa
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_UnhookObject
007f add sp, 4
0082 test byte ptr [0xcc7e], 1 ; _displayType
0087 je 0x264
0089 jmp 0x93e
008c mov es, word ptr [0xbf8c]
0090 mov word ptr es:[0xa080], 1
0097 cmp byte ptr [0xcc7e], 0xa ; _displayType
009c je 0x279
009e jmp 0x540
00a1 push ds
00a2 push 0x1458
00a5 push 1
00a7 push 0
00a9 push 0xf009
00ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
00b1 add sp, 0xa
00b4 les bx, ptr [bp - 0x1c]
00b7 mov word ptr es:[bx], ax
00ba push ax
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00c0 add sp, 2
00c3 mov word ptr [bp - 0xe], ax
00c6 mov word ptr [bp - 0xc], dx
00c9 push 1
00cb push 9
00cd push 0x12
00cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
00d4 add sp, 6
00d7 mov word ptr [bp - 0x14], ax
00da push ax
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
00e0 add sp, 2
00e3 mov word ptr [bp - 4], ax
00e6 push word ptr [bp - 0x14]
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00ee add sp, 2
00f1 mov cx, word ptr [bp - 4]
00f4 push ds
00f5 mov si, ax
00f7 mov ds, dx
00f9 les di, ptr [bp - 0xe]
00fc shr cx, 1
00fe rep movsw word ptr es:[di], word ptr [si]
0100 adc cx, cx
0102 rep movsb byte ptr es:[di], byte ptr [si]
0104 pop ds
0105 push word ptr [bp - 0x14]
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
010d add sp, 2
0110 push 9
0112 push 0x12
0114 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 279, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0119 add sp, 4
011c push 1
011e push 9
0120 push 0x13
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0127 add sp, 6
012a mov word ptr [bp - 0x14], ax
012d push ax
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
0133 add sp, 2
0136 mov word ptr [bp - 4], ax
0139 push word ptr [bp - 0x14]
013c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 319, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0141 add sp, 2
0144 mov word ptr [bp - 8], ax
0147 mov word ptr [bp - 6], dx
014a mov ax, word ptr [bp - 0xe]
014d mov dx, word ptr [bp - 0xc]
0150 add ah, 0x40
0153 adc dx, 0
0156 mov bx, word ptr [bp - 8]
0159 mov si, word ptr [bp - 6]
015c mov cx, word ptr [bp - 4]
015f push ds
0160 push si
0161 mov di, ax
0163 mov si, bx
0165 mov es, dx
0167 pop ds
0168 shr cx, 1
016a rep movsw word ptr es:[di], word ptr [si]
016c adc cx, cx
016e rep movsb byte ptr es:[di], byte ptr [si]
0170 pop ds
0171 push word ptr [bp - 0x14]
0174 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 375, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0179 add sp, 2
017c push 9
017e push 0x13
0180 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 387, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0185 add sp, 4
0188 push 1
018a push 9
018c push 0x14
018e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 401, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0193 add sp, 6
0196 mov word ptr [bp - 0x14], ax
0199 push ax
019a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 413, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
019f add sp, 2
01a2 mov word ptr [bp - 4], ax
01a5 push word ptr [bp - 0x14]
01a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 427, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
01ad add sp, 2
01b0 mov word ptr [bp - 8], ax
01b3 mov word ptr [bp - 6], dx
01b6 mov ax, word ptr [bp - 0xe]
01b9 mov dx, word ptr [bp - 0xc]
01bc add ah, 0x80
01bf adc dx, 0
01c2 mov bx, word ptr [bp - 8]
01c5 mov si, word ptr [bp - 6]
01c8 mov cx, word ptr [bp - 4]
01cb push ds
01cc push si
01cd mov di, ax
01cf mov si, bx
01d1 mov es, dx
01d3 pop ds
01d4 shr cx, 1
01d6 rep movsw word ptr es:[di], word ptr [si]
01d8 adc cx, cx
01da rep movsb byte ptr es:[di], byte ptr [si]
01dc pop ds
01dd push word ptr [bp - 0x14]
01e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 483, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01e5 add sp, 2
01e8 push 9
01ea push 0x14
01ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 495, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
01f1 add sp, 4
01f4 les bx, ptr [bp - 0x1c]
01f7 push word ptr es:[bx]
01fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 509, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01ff add sp, 2
0202 push ds
0203 push 0x1464
0206 push 1
0208 push 0
020a push 0xf009
020d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 528, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0212 add sp, 0xa
0215 les bx, ptr [bp - 0x20]
0218 mov word ptr es:[bx], ax
021b push ax
021c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 543, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0221 add sp, 2
0224 mov word ptr [bp - 0x12], ax
0227 mov word ptr [bp - 0x10], dx
022a push 1
022c push 9
022e push 0xf
0230 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 563, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0235 add sp, 6
0238 mov word ptr [bp - 0x14], ax
023b push ax
023c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 575, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
0241 add sp, 2
0244 mov word ptr [bp - 4], ax
0247 push word ptr [bp - 0x14]
024a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 589, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
024f add sp, 2
0252 mov cx, word ptr [bp - 4]
0255 push ds
0256 mov si, ax
0258 mov ds, dx
025a les di, ptr [bp - 0x12]
025d shr cx, 1
025f rep movsw word ptr es:[di], word ptr [si]
0261 adc cx, cx
0263 rep movsb byte ptr es:[di], byte ptr [si]
0265 pop ds
0266 push word ptr [bp - 0x14]
0269 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 620, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
026e add sp, 2
0271 push 9
0273 push 0xf
0275 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 632, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
027a add sp, 4
027d push 1
027f push 9
0281 push 0x10
0283 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 646, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0288 add sp, 6
028b mov word ptr [bp - 0x14], ax
028e push ax
028f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 658, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
0294 add sp, 2
0297 mov word ptr [bp - 4], ax
029a push word ptr [bp - 0x14]
029d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 672, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
02a2 add sp, 2
02a5 mov word ptr [bp - 8], ax
02a8 mov word ptr [bp - 6], dx
02ab mov ax, word ptr [bp - 0x12]
02ae mov dx, word ptr [bp - 0x10]
02b1 add ah, 0x40
02b4 adc dx, 0
02b7 mov bx, word ptr [bp - 8]
02ba mov si, word ptr [bp - 6]
02bd mov cx, word ptr [bp - 4]
02c0 push ds
02c1 push si
02c2 mov di, ax
02c4 mov si, bx
02c6 mov es, dx
02c8 pop ds
02c9 shr cx, 1
02cb rep movsw word ptr es:[di], word ptr [si]
02cd adc cx, cx
02cf rep movsb byte ptr es:[di], byte ptr [si]
02d1 pop ds
02d2 push word ptr [bp - 0x14]
02d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 728, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
02da add sp, 2
02dd push 9
02df push 0x10
02e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 740, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
02e6 add sp, 4
02e9 push 1
02eb push 9
02ed push 0x11
02ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 754, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
02f4 add sp, 6
02f7 push ax
02f8 mov si, ax
02fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 765, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
02ff add sp, 2
0302 mov word ptr [bp - 4], ax
0305 mov word ptr [bp - 2], dx
0308 push si
0309 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 780, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
030e add sp, 2
0311 mov word ptr [bp - 8], ax
0314 mov word ptr [bp - 6], dx
0317 mov ax, word ptr [bp - 0x12]
031a mov dx, word ptr [bp - 0x10]
031d add ah, 0x80
0320 adc dx, 0
0323 mov bx, word ptr [bp - 8]
0326 mov di, word ptr [bp - 6]
0329 mov cx, word ptr [bp - 4]
032c push si
032d push ds
032e push di
032f mov di, ax
0331 mov si, bx
0333 mov es, dx
0335 pop ds
0336 shr cx, 1
0338 rep movsw word ptr es:[di], word ptr [si]
033a adc cx, cx
033c rep movsb byte ptr es:[di], byte ptr [si]
033e pop ds
033f pop si
0340 push si
0341 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 836, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0346 add sp, 2
0349 push 9
034b push 0x11
034d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 848, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0352 add sp, 4
0355 les bx, ptr [bp - 0x20]
0358 push word ptr es:[bx]
035b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 862, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0360 add sp, 2
0363 pop si
0364 pop di
0365 leave 
0366 retf 
0367 nop 
0368 push ds
0369 push 0x1470
036c push 1
036e push 0
0370 push 0xf009
0373 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 886, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0378 add sp, 0xa
037b les bx, ptr [bp - 0x1c]
037e mov word ptr es:[bx], ax
0381 push ax
0382 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 901, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0387 add sp, 2
038a mov di, ax
038c mov word ptr [bp - 0xc], dx
038f push 1
0391 push 9
0393 push 0x12
0395 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 920, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
039a add sp, 6
039d mov si, ax
039f push si
03a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 931, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
03a5 add sp, 2
03a8 push si
03a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 940, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
03ae add sp, 2
03b1 mov word ptr [bp - 8], ax
03b4 mov word ptr [bp - 6], dx
03b7 sub ax, ax
03b9 mov word ptr [bp - 2], ax
03bc mov word ptr [bp - 4], ax
03bf mov word ptr [bp - 0xa], 0x80
03c4 mov word ptr [bp - 0x14], si
03c7 mov word ptr [bp - 0xe], di
03ca mov si, di
03cc mov di, word ptr [bp - 0xa]
03cf push 0x10
03d1 push 0x10
03d3 mov ax, word ptr [bp - 8]
03d6 mov dx, word ptr [bp - 6]
03d9 mov cx, word ptr [bp - 4]
03dc mov bx, word ptr [bp - 2]
03df add ax, cx
03e1 adc dx, bx
03e3 push dx
03e4 push ax
03e5 mov ax, word ptr [bp - 0xc]
03e8 add cx, si
03ea adc bx, ax
03ec mov word ptr [bp - 0x24], cx
03ef mov word ptr [bp - 0x22], bx
03f2 add cx, 0x80
03f6 adc bx, 0
03f9 push bx
03fa push cx
03fb push word ptr [bp - 0x22]
03fe push word ptr [bp - 0x24]
0401 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1028, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap
0406 add sp, 0x10
0409 add word ptr [bp - 4], 0xa0
040e adc word ptr [bp - 2], 0
0412 dec di
0413 jne 0x5a7
0415 push word ptr [bp - 0x14]
0418 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1051, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
041d add sp, 2
0420 push 9
0422 push 0x12
0424 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1063, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0429 add sp, 4
042c push 1
042e push 9
0430 push 0x13
0432 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1077, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0437 add sp, 6
043a mov word ptr [bp - 0x14], ax
043d push ax
043e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1089, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
0443 add sp, 2
0446 push word ptr [bp - 0x14]
0449 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
044e add sp, 2
0451 mov word ptr [bp - 8], ax
0454 mov word ptr [bp - 6], dx
0457 sub ax, ax
0459 mov word ptr [bp - 2], ax
045c mov word ptr [bp - 4], ax
045f mov di, 0x80
0462 mov si, word ptr [bp - 0xe]
0465 push 0x10
0467 push 0x10
0469 mov ax, word ptr [bp - 8]
046c mov dx, word ptr [bp - 6]
046f mov cx, word ptr [bp - 4]
0472 mov bx, word ptr [bp - 2]
0475 add ax, cx
0477 adc dx, bx
0479 push dx
047a push ax
047b mov ax, word ptr [bp - 0xc]
047e add cx, si
0480 adc bx, ax
0482 mov word ptr [bp - 0x28], cx
0485 mov word ptr [bp - 0x26], bx
0488 add cx, 0x5080
048c adc bx, 0
048f push bx
0490 push cx
0491 mov ax, word ptr [bp - 0x28]
0494 mov dx, word ptr [bp - 0x26]
0497 add ah, 0x50
049a adc dx, 0
049d push dx
049e push ax
049f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap
04a4 add sp, 0x10
04a7 add word ptr [bp - 4], 0xa0
04ac adc word ptr [bp - 2], 0
04b0 dec di
04b1 jne 0x63d
04b3 push word ptr [bp - 0x14]
04b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
04bb add sp, 2
04be push 9
04c0 push 0x13
04c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
04c7 add sp, 4
04ca push 1
04cc push 9
04ce push 0x14
04d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1235, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
04d5 add sp, 6
04d8 mov word ptr [bp - 0x14], ax
04db push ax
04dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
04e1 add sp, 2
04e4 push word ptr [bp - 0x14]
04e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1258, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
04ec add sp, 2
04ef mov word ptr [bp - 8], ax
04f2 mov word ptr [bp - 6], dx
04f5 sub ax, ax
04f7 mov word ptr [bp - 2], ax
04fa mov word ptr [bp - 4], ax
04fd mov di, 0x80
0500 mov si, word ptr [bp - 0xe]
0503 push 0x10
0505 push 0x10
0507 mov ax, word ptr [bp - 8]
050a mov dx, word ptr [bp - 6]
050d mov cx, word ptr [bp - 4]
0510 mov bx, word ptr [bp - 2]
0513 add ax, cx
0515 adc dx, bx
0517 push dx
0518 push ax
0519 mov ax, word ptr [bp - 0xc]
051c add cx, si
051e adc bx, ax
0520 mov word ptr [bp - 0x2c], cx
0523 mov word ptr [bp - 0x2a], bx
0526 add cx, 0xa080
052a adc bx, 0
052d push bx
052e push cx
052f mov ax, word ptr [bp - 0x2c]
0532 mov dx, word ptr [bp - 0x2a]
0535 add ah, 0xa0
0538 adc dx, 0
053b push dx
053c push ax
053d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1344, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap
0542 add sp, 0x10
0545 add word ptr [bp - 4], 0xa0
054a adc word ptr [bp - 2], 0
054e dec di
054f jne 0x6db
0551 push word ptr [bp - 0x14]
0554 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1367, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0559 add sp, 2
055c push 9
055e push 0x14
0560 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1379, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0565 add sp, 4
0568 les bx, ptr [bp - 0x1c]
056b push word ptr es:[bx]
056e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1393, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0573 add sp, 2
0576 push ds
0577 push 0x147c
057a push 1
057c push 0
057e push 0xf009
0581 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1412, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0586 add sp, 0xa
0589 les bx, ptr [bp - 0x20]
058c mov word ptr es:[bx], ax
058f push ax
0590 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1427, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0595 add sp, 2
0598 mov di, ax
059a mov word ptr [bp - 0x10], dx
059d push 1
059f push 9
05a1 push 0xf
05a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1446, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
05a8 add sp, 6
05ab mov word ptr [bp - 0x14], ax
05ae push ax
05af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1458, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
05b4 add sp, 2
05b7 push word ptr [bp - 0x14]
05ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
05bf add sp, 2
05c2 mov word ptr [bp - 8], ax
05c5 mov word ptr [bp - 6], dx
05c8 sub ax, ax
05ca mov word ptr [bp - 2], ax
05cd mov word ptr [bp - 4], ax
05d0 mov word ptr [bp - 0xa], 0x80
05d5 mov word ptr [bp - 0x12], di
05d8 mov si, di
05da mov di, word ptr [bp - 0xa]
05dd push 0x10
05df push 0x10
05e1 mov ax, word ptr [bp - 8]
05e4 mov dx, word ptr [bp - 6]
05e7 mov cx, word ptr [bp - 4]
05ea mov bx, word ptr [bp - 2]
05ed add ax, cx
05ef adc dx, bx
05f1 push dx
05f2 push ax
05f3 mov ax, word ptr [bp - 0x10]
05f6 add cx, si
05f8 adc bx, ax
05fa mov word ptr [bp - 0x30], cx
05fd mov word ptr [bp - 0x2e], bx
0600 add cx, 0x80
0604 adc bx, 0
0607 push bx
0608 push cx
0609 push word ptr [bp - 0x2e]
060c push word ptr [bp - 0x30]
060f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1554, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap
0614 add sp, 0x10
0617 add word ptr [bp - 4], 0xa0
061c adc word ptr [bp - 2], 0
0620 dec di
0621 jne 0x7b5
0623 push word ptr [bp - 0x14]
0626 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1577, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
062b add sp, 2
062e push 9
0630 push 0xf
0632 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1589, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0637 add sp, 4
063a push 1
063c push 9
063e push 0x10
0640 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1603, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0645 add sp, 6
0648 mov word ptr [bp - 0x14], ax
064b push ax
064c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1615, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
0651 add sp, 2
0654 push word ptr [bp - 0x14]
0657 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1626, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
065c add sp, 2
065f mov word ptr [bp - 8], ax
0662 mov word ptr [bp - 6], dx
0665 sub ax, ax
0667 mov word ptr [bp - 2], ax
066a mov word ptr [bp - 4], ax
066d mov di, 0x80
0670 mov si, word ptr [bp - 0x12]
0673 push 0x10
0675 push 0x10
0677 mov ax, word ptr [bp - 8]
067a mov dx, word ptr [bp - 6]
067d mov cx, word ptr [bp - 4]
0680 mov bx, word ptr [bp - 2]
0683 add ax, cx
0685 adc dx, bx
0687 push dx
0688 push ax
0689 mov ax, word ptr [bp - 0x10]
068c add cx, si
068e adc bx, ax
0690 mov word ptr [bp - 0x34], cx
0693 mov word ptr [bp - 0x32], bx
0696 add cx, 0x5080
069a adc bx, 0
069d push bx
069e push cx
069f mov ax, word ptr [bp - 0x34]
06a2 mov dx, word ptr [bp - 0x32]
06a5 add ah, 0x50
06a8 adc dx, 0
06ab push dx
06ac push ax
06ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1712, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap
06b2 add sp, 0x10
06b5 add word ptr [bp - 4], 0xa0
06ba adc word ptr [bp - 2], 0
06be dec di
06bf jne 0x84b
06c1 push word ptr [bp - 0x14]
06c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1735, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
06c9 add sp, 2
06cc push 9
06ce push 0x10
06d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1747, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
06d5 add sp, 4
06d8 push 1
06da push 9
06dc push 0x11
06de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1761, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
06e3 add sp, 6
06e6 mov word ptr [bp - 0x14], ax
06e9 push ax
06ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1773, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
06ef add sp, 2
06f2 push word ptr [bp - 0x14]
06f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1784, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
06fa add sp, 2
06fd mov word ptr [bp - 8], ax
0700 mov word ptr [bp - 6], dx
0703 sub ax, ax
0705 mov word ptr [bp - 2], ax
0708 mov word ptr [bp - 4], ax
070b mov di, 0x80
070e mov si, word ptr [bp - 0x12]
0711 push 0x10
0713 push 0x10
0715 mov ax, word ptr [bp - 8]
0718 mov dx, word ptr [bp - 6]
071b mov cx, word ptr [bp - 4]
071e mov bx, word ptr [bp - 2]
0721 add ax, cx
0723 adc dx, bx
0725 push dx
0726 push ax
0727 mov ax, word ptr [bp - 0x10]
072a add cx, si
072c adc bx, ax
072e mov word ptr [bp - 0x38], cx
0731 mov word ptr [bp - 0x36], bx
0734 add cx, 0xa080
0738 adc bx, 0
073b push bx
073c push cx
073d mov ax, word ptr [bp - 0x38]
0740 mov dx, word ptr [bp - 0x36]
0743 add ah, 0xa0
0746 adc dx, 0
0749 push dx
074a push ax
074b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1870, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap
0750 add sp, 0x10
0753 add word ptr [bp - 4], 0xa0
0758 adc word ptr [bp - 2], 0
075c dec di
075d jne 0x8e9
075f push word ptr [bp - 0x14]
0762 jmp 0x519
0765 nop 
0766 mov es, word ptr [0xbf8c]
076a mov word ptr es:[0xa080], 3
0771 push ds
0772 push 0x1488
0775 push 1
0777 push 1
0779 push 9
077b push 0xd
077d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1920, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0782 add sp, 6
0785 mov word ptr [bp - 0x14], ax
0788 push ax
0789 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1932, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
078e add sp, 2
0791 push dx
0792 push ax
0793 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1942, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0798 add sp, 0xa
079b les bx, ptr [bp - 0x1c]
079e mov word ptr es:[bx], ax
07a1 push ax
07a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1957, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
07a7 add sp, 2
07aa mov word ptr [bp - 0xe], ax
07ad mov word ptr [bp - 0xc], dx
07b0 push word ptr [bp - 0x14]
07b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1974, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
07b8 add sp, 2
07bb mov word ptr [bp - 8], ax
07be mov word ptr [bp - 6], dx
07c1 push word ptr [bp - 0x14]
07c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1991, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
07c9 add sp, 2
07cc mov word ptr [bp - 2], ax
07cf mov ax, word ptr [bp - 8]
07d2 mov dx, word ptr [bp - 6]
07d5 mov cx, word ptr [bp - 2]
07d8 push ds
07d9 mov si, ax
07db mov ds, dx
07dd les di, ptr [bp - 0xe]
07e0 shr cx, 1
07e2 rep movsw word ptr es:[di], word ptr [si]
07e4 adc cx, cx
07e6 rep movsb byte ptr es:[di], byte ptr [si]
07e8 pop ds
07e9 push word ptr [bp - 0x14]
07ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2031, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
07f1 add sp, 2
07f4 les bx, ptr [bp - 0x1c]
07f7 push word ptr es:[bx]
07fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2045, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
07ff add sp, 2
0802 push 9
0804 push 0xd
0806 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2057, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
080b add sp, 4
080e push ds
080f push 0x1494
0812 push 1
0814 push 1
0816 push 9
0818 push 0xe
081a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2077, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
081f add sp, 6
0822 push ax
0823 mov si, ax
0825 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2088, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
082a add sp, 2
082d push dx
082e push ax
082f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2098, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0834 add sp, 0xa
0837 les bx, ptr [bp - 0x20]
083a mov word ptr es:[bx], ax
083d push ax
083e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2113, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0843 add sp, 2
0846 mov word ptr [bp - 0x12], ax
0849 mov word ptr [bp - 0x10], dx
084c push si
084d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0852 add sp, 2
0855 mov word ptr [bp - 8], ax
0858 mov word ptr [bp - 6], dx
085b push si
085c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
0861 add sp, 2
0864 mov word ptr [bp - 4], ax
0867 mov ax, word ptr [bp - 8]
086a mov dx, word ptr [bp - 6]
086d mov cx, word ptr [bp - 4]
0870 push si
0871 push ds
0872 mov si, ax
0874 mov ds, dx
0876 les di, ptr [bp - 0x12]
0879 shr cx, 1
087b rep movsw word ptr es:[di], word ptr [si]
087d adc cx, cx
087f rep movsb byte ptr es:[di], byte ptr [si]
0881 pop ds
0882 pop si
0883 push si
0884 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2183, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0889 add sp, 2
088c les bx, ptr [bp - 0x20]
088f push word ptr es:[bx]
0892 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0897 add sp, 2
089a push 9
089c push 0xe
089e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
08a3 add sp, 4
08a6 pop si
08a7 pop di
08a8 leave 
08a9 retf 
```

## Known declaration examples

- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far db_PurgeObject(int object, int kind);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far db_UnhookObject(int object, int kind);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far db_UnhookObject(int object, int kind);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InvalEuMap', 'offset': 76, 'source': None, 'size': 168}
- {'symbol': '_OverlayTileSet', 'offset': 244, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 227}
- {'symbol': '_ClearEditDeltaTables', 'offset': 2690, 'source': None, 'size': 247}
- {'symbol': '_ProcEditEvent', 'offset': 2938, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 232}

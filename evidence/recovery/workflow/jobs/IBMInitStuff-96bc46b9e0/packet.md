# Recovery task _IBMInitStuff

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 1507 bytes.

```asm
0000 enter 0x276, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov word ptr [bp - 0x1de], 0x6d60
000f mov ax, 0x6d61
0012 mov word ptr [bp - 0x1da], ax
0016 mov word ptr [bp - 0x1d6], ax
001a xor ax, ax
001c mov word ptr [bp - 0x1dc], ax
0020 mov word ptr [bp - 0x1d2], ax
0024 mov ax, 0x6d62
0027 mov word ptr [bp - 0x1d8], ax
002b mov word ptr [bp - 0x1d4], ax
002f mov word ptr [bp - 0x1d0], ax
0033 mov word ptr [bp - 0x1cc], ax
0037 mov ax, 0x6d63
003a mov word ptr [bp - 0x1ce], ax
003e mov word ptr [bp - 0x1ca], ax
0042 mov word ptr [0xb91c], 0xffff ; _musicDevice
0048 nop 
0049 push cs
004a call 0x8f4 ; _ReadConfig
004d mov ax, word ptr [bp + 8]
0050 or ax, di
0052 jne 0x277
0054 jmp 0x407
0057 push word ptr [bp + 8]
005a push di
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
0060 or ax, ax
0062 jg 0x287
0064 jmp 0x407
0067 xor si, si
0069 mov es, word ptr [bp + 8]
006c cmp byte ptr es:[di], 0
0070 jne 0x295
0072 jmp 0x407
0075 mov bx, di
0077 mov cx, si
0079 add bx, cx
007b cmp byte ptr es:[bx], 0x20
007f jne 0x2a6
0081 mov ds, word ptr [bp + 8]
0084 jmp 0x2b9
0086 mov word ptr [bp - 6], cx
0089 mov ds, word ptr [bp + 8]
008c mov bx, di
008e cmp byte ptr [bx + si], 0
0091 je 0x2b9
0093 inc si
0094 cmp byte ptr [bx + si], 0x20
0097 jne 0x2ac
0099 mov bx, di
009b add bx, cx
009d cmp byte ptr [bx], 0x5c
00a0 je 0x2c8
00a2 push ss
00a3 pop ds
00a4 jmp 0x3f9
00a7 nop 
00a8 mov bx, di
00aa add bx, cx
00ac mov al, byte ptr [bx + 2]
00af cwde 
00b0 cdq 
00b1 mov word ptr [bp - 4], ax
00b4 mov word ptr [bp - 2], dx
00b7 mov al, byte ptr [bx + 1]
00ba cwde 
00bb cmp ax, 0x73
00be jne 0x2e3
00c0 jmp 0x3de
00c3 ja 0x2c2
00c5 sub al, 0x21
00c7 je 0x2f4
00c9 sub al, 0x41
00cb je 0x316
00cd sub al, 2
00cf je 0x320
00d1 jmp 0x2c2
00d3 nop 
00d4 push ss
00d5 pop ds
00d6 cmp word ptr [bp - 4], 0x2d
00da jne 0x300
00dc or dx, dx
00de je 0x304
00e0 mov al, 1
00e2 jmp 0x306
00e4 xor al, al
00e6 mov byte ptr [0xb91a], al ; _debugOn
00e9 cwde 
00ea push ax
00eb nop 
00ec push cs
00ed call 0x5486 ; _mem_Debugging
00f0 add sp, 2
00f3 jmp 0x3f9
00f6 push ss
00f7 pop ds
00f8 mov byte ptr [0xcd86], 1 ; _mouseBug
00fd jmp 0x3f9
0100 push ss
0101 pop ds
0102 mov ax, word ptr [bp - 4]
0105 or dx, dx
0107 jne 0x349
0109 cmp ax, 0x77
010c jne 0x331
010e jmp 0x3d6
0111 ja 0x349
0113 cmp al, 0x4d
0115 je 0x3a6
0117 ja 0x370
0119 sub al, 0x32
011b je 0x386
011d sub al, 0xd
011f je 0x38e
0121 sub al, 6
0123 je 0x396
0125 sub al, 3
0127 je 0x39e
0129 push word ptr [0xcd78] ; _rootWnd
012d mov es, word ptr [0xc6a2]
0131 push word ptr es:[0x8b30]
0136 push word ptr es:[0x8b2e]
013b push ds
013c push 0xb980
013f push 0x30
0141 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 322, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0146 push 4
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _exit
014d jmp 0x310
014f nop 
0150 sub al, 0x54
0152 je 0x3ae
0154 sub al, 2
0156 je 0x3b6
0158 dec al
015a je 0x3be
015c sub al, 0xe
015e je 0x3c6
0160 sub al, 8
0162 je 0x3ce
0164 jmp 0x349
0166 mov byte ptr [0xcc7e], 6 ; _displayType
016b jmp 0x3f9
016d nop 
016e mov byte ptr [0xcc7e], 0xff ; _displayType
0173 jmp 0x3f9
0175 nop 
0176 mov byte ptr [0xcc7e], 0 ; _displayType
017b jmp 0x3f9
017d nop 
017e mov byte ptr [0xcc7e], 3 ; _displayType
0183 jmp 0x3f9
0185 nop 
0186 mov byte ptr [0xcc7e], 5 ; _displayType
018b jmp 0x3f9
018d nop 
018e mov byte ptr [0xcc7e], 2 ; _displayType
0193 jmp 0x3f9
0195 nop 
0196 mov byte ptr [0xcc7e], 8 ; _displayType
019b jmp 0x3f9
019d nop 
019e mov byte ptr [0xcc7e], 0xa ; _displayType
01a3 jmp 0x3f9
01a5 nop 
01a6 mov byte ptr [0xcc7e], 4 ; _displayType
01ab jmp 0x3f9
01ad nop 
01ae mov byte ptr [0xcc7e], 7 ; _displayType
01b3 jmp 0x3f9
01b5 nop 
01b6 mov byte ptr [0xcc7e], 9 ; _displayType
01bb jmp 0x3f9
01bd nop 
01be push ss
01bf pop ds
01c0 push dx
01c1 push word ptr [bp - 4]
01c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 455, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isdigit
01c9 add sp, 4
01cc or ax, ax
01ce je 0x3f9
01d0 mov ax, word ptr [bp - 4]
01d3 sub ax, 0x30
01d6 mov word ptr [0xb91c], ax ; _musicDevice
01d9 mov bx, di
01db mov es, word ptr [bp + 8]
01de cmp byte ptr es:[bx + si], 0
01e2 je 0x407
01e4 jmp 0x295
01e7 push ds
01e8 push 0xb988
01eb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 494, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _getenv
01f0 add sp, 4
01f3 or dx, ax
01f5 je 0x43a
01f7 push ds
01f8 push 0xb98c
01fb push ds
01fc push 0xb994
01ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 514, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _getenv
0204 add sp, 4
0207 push dx
0208 push ax
0209 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 524, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _stricmp,_strcmpi
020e add sp, 8
0211 or ax, ax
0213 jne 0x43a
0215 mov byte ptr [0xcd86], 1 ; _mouseBug
021a nop 
021b push cs
021c call 0x59c0 ; _RallocMemoryFree
021f mov es, word ptr [0xc6a4]
0223 mov word ptr es:[0x9aee], ax
0227 mov word ptr es:[0x9af0], dx
022c cmp byte ptr [0xb91a], 0 ; _debugOn
0231 jne 0x486
0233 cmp dx, 0xf
0236 jg 0x486
0238 jl 0x45f
023a cmp ax, 0x4240
023d jae 0x486
023f push word ptr [0xcd78] ; _rootWnd
0243 mov es, word ptr [0xc6a6]
0247 push word ptr es:[0x8b2c]
024c push word ptr es:[0x8b2a]
0251 push ds
0252 push 0xb998
0255 push 0x30
0257 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 600, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
025c push 1
025e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _exit
0263 add sp, 2
0266 push 0
0268 push 0
026a push 0
026c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 623, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _getcwd
0271 add sp, 6
0274 mov es, word ptr [0xc6a8]
0278 mov word ptr es:[0xa0b2], ax
027c mov word ptr es:[0xa0b4], dx
0281 les bx, ptr es:[0xa0b2]
0286 mov al, byte ptr es:[bx]
0289 cwde 
028a mov es, word ptr [0xc6aa]
028e mov word ptr es:[0x9b18], ax
0292 mov di, bx
0294 mov es, dx
0296 mov cx, 0xffff
0299 xor ax, ax
029b repne scasb al, byte ptr es:[di]
029d not cx
029f dec cx
02a0 dec cx
02a1 mov word ptr [bp - 4], cx
02a4 mov word ptr [bp - 2], ax
02a7 mov si, cx
02a9 add si, bx
02ab mov word ptr [bp - 0x272], si
02af mov word ptr [bp - 0x270], es
02b3 cmp byte ptr es:[si], 0x5c
02b7 jne 0x4de
02b9 mov bx, si
02bb mov byte ptr es:[bx], al
02be push ds
02bf push 0xb9a0
02c2 push ax
02c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 708, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 85}}]
02c8 mov si, ax
02ca or si, si
02cc jle 0x500
02ce push si
02cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 720, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
02d4 push ds
02d5 push 0xb9ad
02d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 731, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_SetDataBase
02dd add sp, 4
02e0 push ds
02e1 push 0xb9b6
02e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 743, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_SetDataBase
02e9 add sp, 4
02ec mov al, byte ptr [0xcc7e] ; _displayType
02ef cwde 
02f0 dec ax
02f1 dec ax
02f2 je 0x518
02f4 dec ax
02f5 dec ax
02f6 jne 0x524
02f8 push ds
02f9 push 0xb9bd
02fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 767, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_SetDataBase
0301 add sp, 4
0304 mov es, word ptr [0xc6ac]
0308 mov ax, word ptr es:[0x8b26]
030c mov dx, word ptr es:[0x8b28]
0311 mov word ptr [bp - 8], ax
0314 mov word ptr [bp - 6], dx
0317 mov word ptr [bp - 0x20a], 0xb92b
031d mov word ptr [bp - 0x208], ds
0321 mov word ptr [bp - 0x206], 0xb931
0327 mov word ptr [bp - 0x204], ds
032b mov word ptr [bp - 0x202], 0xb936
0331 mov word ptr [bp - 0x200], ds
0335 mov word ptr [bp - 0x1fe], 0xb93c
033b mov word ptr [bp - 0x1fc], ds
033f mov word ptr [bp - 0x1fa], 0xb941
0345 mov word ptr [bp - 0x1f8], ds
0349 mov word ptr [bp - 0x1f6], 0xb947
034f mov word ptr [bp - 0x1f4], ds
0353 mov word ptr [bp - 0x1f2], 0xb94c
0359 mov word ptr [bp - 0x1f0], ds
035d mov word ptr [bp - 0x1ee], 0xb951
0363 mov word ptr [bp - 0x1ec], ds
0367 mov word ptr [bp - 0x1ea], 0xb956
036d mov word ptr [bp - 0x1e8], ds
0371 mov word ptr [bp - 0x1e6], 0xb95c
0377 mov word ptr [bp - 0x1e4], ds
037b mov word ptr [bp - 0x1e2], 0xb961
0381 mov word ptr [bp - 0x1e0], ds
0385 cmp byte ptr [0xcc7e], 0xff ; _displayType
038a jne 0x5f9
038c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 909, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 286}}]
0391 mov word ptr [bp - 4], ax
0394 push ax
0395 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 918, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 66}}]
039a mov word ptr [bp - 2], ax
039d push ax
039e push 0xc
03a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 929, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
03a5 dec ax
03a6 jne 0x5e6
03a8 push word ptr [bp - 2]
03ab push 0xe
03ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 942, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
03b2 dec ax
03b3 jne 0x5e6
03b5 push word ptr [bp - 4]
03b8 push word ptr [bp - 2]
03bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 956, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
03c0 mov si, 9
03c3 jmp 0x5f4
03c5 nop 
03c6 push word ptr [bp - 4]
03c9 push word ptr [bp - 2]
03cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 973, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
03d1 mov si, 0xa
03d4 mov ax, si
03d6 mov byte ptr [0xcc7e], al ; _displayType
03d9 push word ptr [bp - 6]
03dc push word ptr [bp - 8]
03df mov al, byte ptr [0xcc7e] ; _displayType
03e2 cwde 
03e3 mov si, ax
03e5 shl si, 2
03e8 push word ptr [bp + si - 0x208]
03ec push word ptr [bp + si - 0x20a]
03f0 push ds
03f1 push 0xb967
03f4 lea ax, [bp - 0x26e]
03f8 push ss
03f9 push ax
03fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1021, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
03ff add sp, 0x10
0402 lea ax, [bp - 0x26e]
0406 push ss
0407 push ax
0408 push ds
0409 push 0xb96c
040c nop 
040d push cs
040e call 0x62bc ; _WinPrintf
0411 add sp, 8
0414 lea ax, [bp - 0x26e]
0418 push ss
0419 push ax
041a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1053, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_SetDataBase
041f add sp, 4
0422 mov al, byte ptr [0xcc7e] ; _displayType
0425 cwde 
0426 cmp ax, 0xa
0429 je 0x668
042b ja 0x66d
042d or al, al
042f je 0x658
0431 sub al, 8
0433 je 0x664
0435 jmp 0x66d
0437 nop 
0438 push 1
043a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1085, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetPalette
043f add sp, 2
0442 jmp 0x66d
0444 push 0
0446 jmp 0x65a
0448 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1099, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InitPalette
044d nop 
044e push cs
044f call 0x547c ; _mem_Flush
0452 nop 
0453 push cs
0454 call 0x5684 ; _ralloc_CompressMemory
0457 nop 
0458 push cs
0459 call 0x18ac ; _TickCount
045c mov word ptr [bp - 0x1c8], ax
0460 mov word ptr [bp - 0x1c6], dx
0464 push word ptr [0xcc7c] ; _hInst
0468 push ds
0469 push 0xb91e
046c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1133, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
0471 mov es, word ptr [0xc69c]
0475 mov word ptr es:[0x72d0], ax
0479 push 0x100
047c push <resolved loader operand; see bindings> ; [{'operand_offset': 1149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
047f push 0x76ac
0482 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _getcwd
0487 add sp, 6
048a mov es, word ptr [0xc69e]
048e mov ax, 0x76ac
0491 mov dx, ax
0493 mov di, ax
0495 mov cx, 0xffff
0498 xor ax, ax
049a repne scasb al, byte ptr es:[di]
049c not cx
049e dec cx
049f mov bx, cx
04a1 cmp byte ptr es:[bx + 0x76ab], 0x5c
04a7 je 0x6fe
04a9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1194, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
04ac mov si, ax
04ae push ds
04af push si
04b0 mov di, 0xb929
04b3 mov si, dx
04b5 mov cx, ds
04b7 mov es, cx
04b9 pop ds
04ba mov cx, 0xffff
04bd xor ax, ax
04bf repne scasb al, byte ptr es:[di]
04c1 not cx
04c3 sub di, cx
04c5 mov bx, cx
04c7 xchg si, di
04c9 push ds
04ca push es
04cb pop ds
04cc pop es
04cd mov cx, 0xffff
04d0 repne scasb al, byte ptr es:[di]
04d2 dec di
04d3 mov cx, bx
04d5 shr cx, 1
04d7 rep movsw word ptr es:[di], word ptr [si]
04d9 adc cx, cx
04db rep movsb byte ptr es:[di], byte ptr [si]
04dd pop ds
04de mov <resolved loader operand; see bindings> ; [{'operand_offset': 1247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
04e1 mov es, word ptr [0xc6a0]
04e5 mov si, word ptr es:[0x8b3a]
04ea mov cx, word ptr es:[0x8b3c]
04ef mov di, ax
04f1 mov word ptr [bp - 0x276], si
04f5 mov word ptr [bp - 0x274], cx
04f9 push ds
04fa push di
04fb mov si, dx
04fd pop ds
04fe les di, ptr [bp - 0x276]
0502 mov cx, 0xffff
0505 xor ax, ax
0507 repne scasb al, byte ptr es:[di]
0509 not cx
050b sub di, cx
050d mov bx, cx
050f xchg si, di
0511 push ds
0512 push es
0513 pop ds
0514 pop es
0515 mov cx, 0xffff
0518 repne scasb al, byte ptr es:[di]
051a dec di
051b mov cx, bx
051d shr cx, 1
051f rep movsw word ptr es:[di], word ptr [si]
0521 adc cx, cx
0523 rep movsb byte ptr es:[di], byte ptr [si]
0525 pop ds
0526 push ax
0527 nop 
0528 push cs
0529 call 0x4e36 ; _InitMenu
052c add sp, 2
052f or ax, ax
0531 jne 0x75f
0533 push ds
0534 push 0xb9c5
0537 nop 
0538 push cs
0539 call 0x18be ; _Punt
053c add sp, 4
053f push word ptr [0xcd78] ; _rootWnd
0543 nop 
0544 push cs
0545 call 0x3dfa ; _MSClipStart
0548 add sp, 2
054b push 0xf
054d nop 
054e push cs
054f call 0x4c0e ; _ConvColor
0552 add sp, 2
0555 push ax
0556 push word ptr [0xce86] ; _screenHeight
055a push word ptr [0xcc7a] ; _screenWidth
055e push 0
0560 push 0
0562 nop 
0563 push cs
0564 call 0x19e6 ; _GBoxFill
0567 add sp, 0xa
056a mov al, byte ptr [0xcc7e] ; _displayType
056d cwde 
056e mov si, ax
0570 shl si, 1
0572 mov si, word ptr [bp + si - 0x1de]
0576 push si
0577 lea ax, [bp - 0x1c4]
057b push ss
057c push ax
057d nop 
057e push cs
057f call 0x465c ; _gr_BitMapSize
0582 add sp, 6
0585 push si
0586 mov ax, word ptr [0xce86] ; _screenHeight
0589 sub ax, word ptr [bp - 0x1c2]
058d cdq 
058e sub ax, dx
0590 sar ax, 1
0592 push ax
0593 mov ax, word ptr [0xcc7a] ; _screenWidth
0596 sub ax, word ptr [bp - 0x1c4]
059a cdq 
059b sub ax, dx
059d sar ax, 1
059f push ax
05a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1443, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMap
05a5 add sp, 6
05a8 nop 
05a9 push cs
05aa call 0x3e4c ; _MSClipEnd
05ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1456, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMenuEntries
05b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1461, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _LoadTiles
05b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1466, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InitApplicationStuff
05bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1471, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InitApplicationWindows
05c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1476, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMenuEntries
05c6 push 0x48
05c8 lea ax, [bp - 0x1c8]
05cc push ss
05cd push ax
05ce nop 
05cf push cs
05d0 call 0x47b8 ; _WaitedEnough
05d3 add sp, 6
05d6 or ax, ax
05d8 je 0x7e6
05da nop 
05db push cs
05dc call 0x4038 ; _RedrawScreen
05df pop si
05e0 pop di
05e1 leave 
05e2 retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void InitPalette(void);` — src/recovered/wf_PaintStuff-4a441706dd.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far RallocMemoryFree(void);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbort-1a41498b6d.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbortOrCont-ea87855190.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogWait-50782e4ed5.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far db_SetDataBase(char far *text);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far exit(int status);` — src/recovered/wf_Punt-840c7657cd.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_initControls_1_scaffold-03091459d8.c
- `extern int near hInst;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int near screenHeight;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near screenWidth;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c
- `extern int far stricmp(const char far *a, const char far *b);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_DrawBitMap(unsigned int bitmapOffset, int bitmapArgument, int value);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern int far win_DrawBitMap(unsigned int bitmap, unsigned int bitmapMask, int bitmapNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_ReadConfig'], 'segment': 2, 'target_offset': 2292, 'caller_offsets': [74]}
- {'callee_names': ['_TickCount'], 'segment': 2, 'target_offset': 6316, 'caller_offsets': [1113]}
- {'callee_names': ['_Punt'], 'segment': 2, 'target_offset': 6334, 'caller_offsets': [1337]}
- {'callee_names': ['_GBoxFill'], 'segment': 2, 'target_offset': 6630, 'caller_offsets': [1380]}
- {'callee_names': ['_MSClipStart'], 'segment': 2, 'target_offset': 15866, 'caller_offsets': [1349]}
- {'callee_names': ['_MSClipEnd'], 'segment': 2, 'target_offset': 15948, 'caller_offsets': [1450]}
- {'callee_names': ['_RedrawScreen'], 'segment': 2, 'target_offset': 16440, 'caller_offsets': [1500]}
- {'callee_names': ['_gr_BitMapSize'], 'segment': 2, 'target_offset': 18012, 'caller_offsets': [1407]}
- {'callee_names': ['_WaitedEnough'], 'segment': 2, 'target_offset': 18360, 'caller_offsets': [1488]}
- {'callee_names': ['_ConvColor'], 'segment': 2, 'target_offset': 19470, 'caller_offsets': [1359]}
- {'callee_names': ['_InitMenu'], 'segment': 2, 'target_offset': 20022, 'caller_offsets': [1321]}
- {'callee_names': ['_mem_Flush'], 'segment': 2, 'target_offset': 21628, 'caller_offsets': [1103]}
- {'callee_names': ['_mem_Debugging'], 'segment': 2, 'target_offset': 21638, 'caller_offsets': [237]}
- {'callee_names': ['_ralloc_CompressMemory'], 'segment': 2, 'target_offset': 22148, 'caller_offsets': [1108]}
- {'callee_names': ['_RallocMemoryFree'], 'segment': 2, 'target_offset': 22976, 'caller_offsets': [540]}
- {'callee_names': ['_WinPrintf'], 'segment': 2, 'target_offset': 25276, 'caller_offsets': [1038]}

## Neighbors

- {'symbol': '_DetectDisplay', 'offset': 202, 'source': 'src/recovered/DetectDisplay.c', 'size': 65}
- {'symbol': '_InitGraphics', 'offset': 268, 'source': 'src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c', 'size': 275}
- {'symbol': '_ReadWord', 'offset': 2052, 'source': 'src/recovered/wf_ReadWord-e51efa9f2b.c', 'size': 109}
- {'symbol': '_SkipWords', 'offset': 2162, 'source': 'src/recovered/wf_SkipWords-f10e7d71fd.c', 'size': 130}

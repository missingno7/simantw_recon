# Recovery task _Draw_SimYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 1595 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 push word ptr [0xbcd8]
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
000f add sp, 2
0012 cmp word ptr [0x18b6], 0
0017 je 0xb497
0019 mov es, word ptr [0xc19e]
001d push word ptr es:[0x7a62]
0022 push word ptr es:[0x7a60]
0027 nop 
0028 push cs
0029 call 0xbe04 ; _InvertPatch
002c add sp, 4
002f mov word ptr [0x18b6], 0
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
003a cmp word ptr [bp + 6], 1
003e jle 0xb4a5
0040 jmp 0xb98e
0043 cmp word ptr [0x1886], 0 ; _yardAnimHandle
0048 jne 0xb4ef
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_MakeAnimSet
004f mov word ptr [0x1886], ax ; _yardAnimHandle
0052 mov ax, 0xffff
0055 mov cx, 0x1e
0058 mov di, 0xcb04
005b push ds
005c pop es
005d rep stosb byte ptr es:[di], al
005f mov cx, 0x22
0062 mov di, 0xcb22
0065 rep stosb byte ptr es:[di], al
0067 mov cx, 0x22
006a mov di, 0xcb44
006d rep stosb byte ptr es:[di], al
006f mov word ptr [0x1888], ax
0072 mov word ptr [0x188e], ax
0075 mov word ptr [0x188c], ax
0078 mov word ptr [0x188a], ax
007b mov word ptr [0x1890], ax
007e mov word ptr [0x1892], ax
0081 mov es, word ptr [0xc1bc]
0085 mov word ptr es:[0x9f24], ax
0089 mov word ptr es:[0x9f26], ax
008d cmp word ptr [0xac6c], 0 ; _CatOn
0092 jne 0xb4f9
0094 jmp 0xb57e
0097 mov ax, word ptr [0xac6e] ; _CatX
009a mov word ptr [bp - 2], ax
009d mov ax, word ptr [0xac70] ; _CatY
00a0 mov word ptr [bp - 4], ax
00a3 mov dx, word ptr [0xac6a] ; _CatFrame
00a7 cmp dx, 0xa
00aa jl 0xb536
00ac cmp dx, 0x14
00af jge 0xb524
00b1 mov bx, dx
00b3 mov al, byte ptr [bx + 0x192e]
00b7 cwde 
00b8 add word ptr [bp - 2], ax
00bb mov al, byte ptr [bx + 0x1932]
00bf jmp 0xb532
00c1 nop 
00c2 mov bx, dx
00c4 mov al, byte ptr [bx + 0x192c]
00c8 cwde 
00c9 add word ptr [bp - 2], ax
00cc mov al, byte ptr [bx + 0x1936]
00d0 cwde 
00d1 add word ptr [bp - 4], ax
00d4 cmp word ptr [0x188a], -1
00d9 je 0xb55e
00db push -1
00dd push word ptr [0x188a]
00e1 push word ptr [0x1886] ; _yardAnimHandle
00e5 mov ax, dx
00e7 add ax, 0x514
00ea push ax
00eb push word ptr [bp - 4]
00ee push word ptr [bp - 2]
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
00f6 add sp, 0xc
00f9 jmp 0xb59f
00fb nop 
00fc push -1
00fe mov ax, dx
0100 add ax, 0x514
0103 push ax
0104 push word ptr [bp - 4]
0107 push word ptr [bp - 2]
010a push word ptr [0x1886] ; _yardAnimHandle
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0113 add sp, 0xa
0116 mov word ptr [0x188a], ax
0119 jmp 0xb59f
011b nop 
011c cmp word ptr [0x188a], -1
0121 je 0xb59f
0123 push ds
0124 push 0x195a
0127 push word ptr [0x188a]
012b push word ptr [0x1886] ; _yardAnimHandle
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
0134 add sp, 8
0137 mov word ptr [0x188a], 0xffff
013d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
0142 mov ax, word ptr [0xac5c] ; _DogX
0145 mov word ptr [bp - 2], ax
0148 mov ax, word ptr [0xac5e] ; _DogY
014b mov word ptr [bp - 4], ax
014e cmp word ptr [0xac5a], 0 ; _ForSaleState
0153 jne 0xb627
0155 mov dx, word ptr [0xac60] ; _DogFrame
0159 cmp dx, 0xc
015c jge 0xb5d0
015e mov bx, dx
0160 mov al, byte ptr [bx + 0x1918]
0164 cwde 
0165 add word ptr [bp - 2], ax
0168 mov al, byte ptr [bx + 0x1924]
016c jmp 0xb5de
016e mov bx, dx
0170 mov al, byte ptr [bx + 0x18cc]
0174 cwde 
0175 add word ptr [bp - 2], ax
0178 mov al, byte ptr [bx + 0x18d0]
017c cwde 
017d add word ptr [bp - 4], ax
0180 cmp word ptr [0x188e], -1
0185 je 0xb60a
0187 push -1
0189 push word ptr [0x188e]
018d push word ptr [0x1886] ; _yardAnimHandle
0191 mov ax, dx
0193 add ax, 0x2134
0196 push ax
0197 push word ptr [bp - 4]
019a push word ptr [bp - 2]
019d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 416, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
01a2 add sp, 0xc
01a5 jmp 0xb627
01a7 nop 
01a8 push -1
01aa mov ax, dx
01ac add ax, 0x2134
01af push ax
01b0 push word ptr [bp - 4]
01b3 push word ptr [bp - 2]
01b6 push word ptr [0x1886] ; _yardAnimHandle
01ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 445, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
01bf add sp, 0xa
01c2 mov word ptr [0x188e], ax
01c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 456, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
01ca cmp word ptr [bp + 6], 0
01ce jne 0xb639
01d0 cmp word ptr [0xac74], 0 ; _BoyHere
01d5 je 0xb648
01d7 cmp word ptr [0xac7a], 0 ; _BoyFrame
01dc jl 0xb648
01de nop 
01df push cs
01e0 call 0xaf14 ; _DrawSimKid
01e3 jmp 0xb6b3
01e5 nop 
01e6 cmp word ptr [0x1888], -1
01eb je 0xb669
01ed push ds
01ee push 0x195e
01f1 push word ptr [0x1888]
01f5 push word ptr [0x1886] ; _yardAnimHandle
01f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 508, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
01fe add sp, 8
0201 mov word ptr [0x1888], 0xffff
0207 mov bx, 0x9f24
020a mov es, word ptr [0xc1bc]
020e mov word ptr [bp - 0xc], bx
0211 mov word ptr [bp - 0xa], es
0214 cmp word ptr es:[bx], -1
0218 je 0xb6b3
021a push ds
021b push 0x1962
021e push word ptr es:[bx]
0221 push word ptr [0x1886] ; _yardAnimHandle
0225 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 552, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
022a add sp, 8
022d les bx, ptr [bp - 0xc]
0230 mov word ptr es:[bx], 0xffff
0235 mov es, word ptr [0xc1bc]
0239 push word ptr es:[0x9f20]
023e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 577, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0243 add sp, 2
0246 mov es, word ptr [0xc1bc]
024a mov word ptr es:[0x9f20], 0
0251 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 596, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
0256 nop 
0257 push cs
0258 call 0xb2c4 ; _DrawMower
025b cmp word ptr [0xac64], 0 ; _BirdOn
0260 je 0xb72c
0262 mov ax, word ptr [0xac66] ; _BirdX
0265 sub ax, 0xa
0268 mov word ptr [bp - 2], ax
026b mov ax, word ptr [0xac68] ; _BirdY
026e sub ax, 3
0271 mov word ptr [bp - 4], ax
0274 cmp word ptr [0xac62], 0 ; _BirdFrame
0279 je 0xb6e4
027b inc word ptr [bp - 2]
027e add word ptr [bp - 4], 2
0282 cmp word ptr [0x188c], -1
0287 je 0xb70c
0289 push -1
028b push word ptr [0x188c]
028f push word ptr [0x1886] ; _yardAnimHandle
0293 mov ax, word ptr [0xac62] ; _BirdFrame
0296 add ax, 0x4e2
0299 push ax
029a push word ptr [bp - 4]
029d push word ptr [bp - 2]
02a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 675, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
02a5 add sp, 0xc
02a8 jmp 0xb74d
02aa push -1
02ac mov ax, word ptr [0xac62] ; _BirdFrame
02af add ax, 0x4e2
02b2 push ax
02b3 push word ptr [bp - 4]
02b6 push word ptr [bp - 2]
02b9 push word ptr [0x1886] ; _yardAnimHandle
02bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 704, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
02c2 add sp, 0xa
02c5 mov word ptr [0x188c], ax
02c8 jmp 0xb74d
02ca cmp word ptr [0x188c], -1
02cf je 0xb74d
02d1 push ds
02d2 push 0x196a
02d5 push word ptr [0x188c]
02d9 push word ptr [0x1886] ; _yardAnimHandle
02dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 736, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
02e2 add sp, 8
02e5 mov word ptr [0x188c], 0xffff
02eb cmp word ptr [0xac5a], 0 ; _ForSaleState
02f0 je 0xb79c
02f2 mov word ptr [bp - 4], 0xaa
02f7 mov word ptr [bp - 2], 0xba
02fc cmp word ptr [0x1892], -1
0301 je 0xb782
0303 push -1
0305 push word ptr [0x1892]
0309 push word ptr [0x1886] ; _yardAnimHandle
030d push 0x4ec
0310 push 0xba
0313 push 0xaa
0316 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 793, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
031b add sp, 0xc
031e jmp 0xb79c
0320 push -1
0322 push 0x4ec
0325 push 0xba
0328 push 0xaa
032b push word ptr [0x1886] ; _yardAnimHandle
032f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 818, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0334 add sp, 0xa
0337 mov word ptr [0x1892], ax
033a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 829, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
033f cmp word ptr [0xac72], 0 ; _RainOn
0344 je 0xb814
0346 mov di, 0xe
0349 mov si, 0xcb20
034c sub si, 2
034f mov ax, di
0351 dec di
0352 or ax, ax
0354 jne 0xb7bb
0356 jmp 0xb83e
0359 push 0x190
035c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 863, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0361 add sp, 2
0364 add ax, 0x32
0367 mov word ptr [bp - 2], ax
036a push 0x96
036d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 880, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0372 add sp, 2
0375 mov word ptr [bp - 4], ax
0378 cmp word ptr [si], -1
037b je 0xb7fa
037d push 0x8000
0380 push word ptr [si]
0382 push word ptr [0x1886] ; _yardAnimHandle
0386 push 0x1b5d
0389 push ax
038a push word ptr [bp - 2]
038d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 912, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
0392 add sp, 0xc
0395 jmp 0xb7ae
0397 nop 
0398 push 0x3e8
039b push 0x1b5d
039e push ax
039f push word ptr [bp - 2]
03a2 push word ptr [0x1886] ; _yardAnimHandle
03a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 937, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
03ab add sp, 0xa
03ae mov word ptr [si], ax
03b0 jmp 0xb7ae
03b2 mov si, 0xcb04
03b5 mov di, word ptr [bp - 2]
03b8 cmp word ptr [si], -1
03bb je 0xb835
03bd push ds
03be push 0x196f
03c1 push word ptr [si]
03c3 push word ptr [0x1886] ; _yardAnimHandle
03c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 970, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
03cc add sp, 8
03cf mov word ptr [si], 0xffff
03d3 add si, 2
03d6 cmp si, 0xcb20
03da jbe 0xb81a
03dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 991, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
03e1 nop 
03e2 push cs
03e3 call 0xbb0e ; _DrawSwarm
03e6 push word ptr [0xbcd8]
03ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1005, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
03ef add sp, 2
03f2 cmp word ptr [0x18b6], 0
03f7 jne 0xb877
03f9 mov es, word ptr [0xc19e]
03fd push word ptr es:[0x7a62]
0402 push word ptr es:[0x7a60]
0407 nop 
0408 push cs
0409 call 0xbe04 ; _InvertPatch
040c add sp, 4
040f mov word ptr [0x18b6], 1
0415 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1048, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
041a cmp word ptr [0xbcec], 0
041f je 0xb8f2
0421 push 0x1900
0424 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1063, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0429 add sp, 2
042c or ax, ax
042e je 0xb8f2
0430 push word ptr [0xbcd8]
0434 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1079, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0439 add sp, 2
043c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1087, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0441 mov es, word ptr [0xc1ac]
0445 cmp dx, word ptr es:[0x19a4]
044a jge 0xb8b1
044c jmp 0xb94c
044f jg 0xb8bd
0451 cmp ax, word ptr es:[0x19a2]
0456 ja 0xb8bd
0458 jmp 0xb94c
045b mov es, word ptr [0xc1ae]
045f sub ax, ax
0461 mov word ptr es:[0x1448], ax
0465 mov word ptr es:[0x1446], ax
0469 mov es, word ptr [0xc1b0]
046d mov word ptr es:[0x19a0], ax
0471 mov word ptr es:[0x199e], ax
0475 push 0xc
0477 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
047c add sp, 2
047f push ax
0480 push 0x1916
0483 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
0488 add sp, 4
048b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0490 nop 
0491 push cs
0492 call 0xccee ; _AllocateMapBuffer
0495 mov es, word ptr [0xc1c6]
0499 push word ptr es:[0x19aa]
049e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
04a3 add sp, 2
04a6 mov si, ax
04a8 mov word ptr [bp - 2], dx
04ab push 0xe2
04ae push 0x200
04b1 push dx
04b2 push si
04b3 mov es, word ptr [0xc1c4]
04b7 push word ptr es:[0x8112]
04bc push word ptr es:[0x8110]
04c1 push 0x1900
04c4 push word ptr [0x1886] ; _yardAnimHandle
04c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1227, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RenderAnimSet
04cd add sp, 0x10
04d0 mov es, word ptr [0xc1c6]
04d4 push word ptr es:[0x19aa]
04d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
04de add sp, 2
04e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1252, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
04e6 pop si
04e7 pop di
04e8 leave 
04e9 retf 
04ea mov es, word ptr [0xc1b0]
04ee mov ax, word ptr es:[0x19a0]
04f2 or ax, word ptr es:[0x199e]
04f7 jne 0xb95e
04f9 jmp 0xb8d7
04fc push 2
04fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1281, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0503 add sp, 2
0506 mov es, word ptr [0xc1b0]
050a push word ptr es:[0x19a0]
050f push word ptr es:[0x199e]
0514 push 0x1916
0517 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
051c add sp, 6
051f push 0
0521 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1316, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0526 add sp, 2
0529 jmp 0xb8ed
052c push word ptr [0xbcd8]
0530 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0535 add sp, 2
0538 cmp word ptr [0x18b6], 0
053d jne 0xb9bd
053f mov es, word ptr [0xc19e]
0543 push word ptr es:[0x7a62]
0548 push word ptr es:[0x7a60]
054d nop 
054e push cs
054f call 0xbe04 ; _InvertPatch
0552 add sp, 4
0555 mov word ptr [0x18b6], 1
055b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1374, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0560 lea ax, [bp - 8]
0563 push ss
0564 push ax
0565 push 0x1902
0568 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1387, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
056d add sp, 6
0570 push word ptr [0xbcd8]
0574 lea ax, [bp - 8]
0577 push ss
0578 push ax
0579 push 0
057b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1404, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0580 cmp word ptr [0xbcec], 0
0585 jne 0xb9ec
0587 jmp 0xba99
058a push 0x1900
058d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1424, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0592 add sp, 2
0595 or ax, ax
0597 jne 0xb9fe
0599 jmp 0xba99
059c push word ptr [0xbcd8]
05a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1443, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
05a5 add sp, 2
05a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1451, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
05ad mov es, word ptr [0xc1ac]
05b1 cmp dx, word ptr es:[0x19a4]
05b6 jl 0xba40
05b8 jg 0xba23
05ba cmp ax, word ptr es:[0x19a2]
05bf jbe 0xba40
05c1 mov es, word ptr [0xc1ae]
05c5 sub ax, ax
05c7 mov word ptr es:[0x1448], ax
05cb mov word ptr es:[0x1446], ax
05cf mov es, word ptr [0xc1b0]
05d3 mov word ptr es:[0x19a0], ax
05d7 mov word ptr es:[0x199e], ax
05db jmp 0xba7e
05dd nop 
05de mov es, word ptr [0xc1b0]
05e2 mov ax, word ptr es:[0x19a0]
05e6 or ax, word ptr es:[0x199e]
05eb je 0xba7e
05ed push 2
05ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1522, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
05f4 add sp, 2
05f7 mov es, word ptr [0xc1b0]
05fb push word ptr es:[0x19a0]
0600 push word ptr es:[0x199e]
0605 push 0x1916
0608 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1547, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
060d add sp, 6
0610 push 0
0612 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1557, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0617 add sp, 2
061a jmp 0xba94
061c push 0xc
061e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1569, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0623 add sp, 2
0626 push ax
0627 push 0x1916
062a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1581, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
062f add sp, 4
0632 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1589, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0637 pop si
0638 pop di
0639 leave 
063a retf 
```

## Known declaration examples

- `extern int near BirdFrame;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near BirdFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BirdOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BirdX;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near BirdY;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near BoyFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BoyHere;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near CatFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near CatOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near CatX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near CatY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near DogFrame;` — src/recovered/wf_tu_antedit_A998_DrawDog_1_reviewed-b5499d8ad8.c
- `extern int near DogFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near DogX;` — src/recovered/wf_tu_antedit_A998_DrawDog_1_reviewed-b5499d8ad8.c
- `extern int near DogX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near DogY;` — src/recovered/wf_tu_antedit_A998_DrawDog_1_reviewed-b5499d8ad8.c
- `extern int near DogY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near ForSaleState;` — src/recovered/wf_tu_antedit_A998_DrawDog_1_reviewed-b5499d8ad8.c
- `extern int near ForSaleState;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near ForSaleState;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far InvertPatch(int x, int y);` — src/recovered/wf_tu_antedit_A998_DrawYardCursor_3_scaffold-c71c8e4e09.c
- `extern void far InvertPatch(int x, int y);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near RainOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far hanim_RenderAnimSet(unsigned int setHandle, int window, int left, int top, int a, int b, int size, int mode);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_PrintfAtObj(int object, char far *format, ...);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_DrawSimKid'], 'segment': 3, 'target_offset': 44820, 'caller_offsets': [480]}
- {'callee_names': ['_DrawMower'], 'segment': 3, 'target_offset': 45764, 'caller_offsets': [600]}
- {'callee_names': ['_DrawSwarm'], 'segment': 3, 'target_offset': 47886, 'caller_offsets': [995]}
- {'callee_names': ['_InvertPatch'], 'segment': 3, 'target_offset': 48644, 'caller_offsets': [41, 1033, 1359]}
- {'callee_names': ['_AllocateMapBuffer'], 'segment': 3, 'target_offset': 52462, 'caller_offsets': [1170]}

## Neighbors

- {'symbol': '_DrawMower', 'offset': 45764, 'source': None, 'size': 229}
- {'symbol': '_DrawAnimYardMessage', 'offset': 45994, 'source': 'src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c', 'size': 184}
- {'symbol': '_DrawRain', 'offset': 47774, 'source': 'src/recovered/wf_DrawRain-d667f83eb1.c', 'size': 112}
- {'symbol': '_DrawSwarm', 'offset': 47886, 'source': None, 'size': 718}

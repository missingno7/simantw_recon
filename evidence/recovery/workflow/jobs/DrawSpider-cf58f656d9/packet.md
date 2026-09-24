# Recovery task _DrawSpider

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 1402 bytes.

```asm
0000 enter 0x2e, 0
0004 push di
0005 push si
0006 mov bx, 0x729e
0009 mov es, word ptr [0xbfac]
000d mov word ptr [bp - 0x1c], bx
0010 mov word ptr [bp - 0x1a], es
0013 cmp word ptr es:[bx], 5
0017 jne 0x1db6
0019 mov es, word ptr [0xbfae]
001d mov bx, word ptr es:[0x7290]
0022 mov es, word ptr [0xbfb0]
0026 mov al, byte ptr es:[bx - 0x77ec]
002b cwde 
002c mov word ptr [bp - 8], ax
002f mov es, word ptr [0xbfb2]
0033 mov al, byte ptr es:[bx - 0x77e8]
0038 cwde 
0039 mov word ptr [bp - 0xa], ax
003c push 1
003e push 2
0040 mov es, word ptr [0xbfae]
0044 mov ax, bx
0046 add ax, 0x41a
0049 jmp 0x1ddd
004b nop 
004c mov es, word ptr [0xbfb4]
0050 mov bx, word ptr [0xac80] ; _SpidDir
0054 mov al, byte ptr es:[bx - 0x77fc]
0059 cwde 
005a mov word ptr [bp - 8], ax
005d mov es, word ptr [0xbfb6]
0061 mov al, byte ptr es:[bx - 0x77f4]
0066 cwde 
0067 mov word ptr [bp - 0xa], ax
006a push 1
006c push 2
006e mov ax, bx
0070 add ax, 0x3e8
0073 push ax
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0079 add sp, 6
007c mov word ptr [bp - 0x10], ax
007f push ax
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0085 add sp, 2
0088 mov es, dx
008a mov bx, ax
008c mov di, bx
008e mov word ptr [bp - 0xc], es
0091 cmp word ptr es:[bx], 3
0095 je 0x1e04
0097 jmp 0x20ac
009a mov ax, word ptr [0x1452] ; _theEditBufPtr
009d mov dx, word ptr [0x1454]
00a1 mov word ptr [bp - 6], ax
00a4 mov word ptr [bp - 4], dx
00a7 mov es, word ptr [0xbf92]
00ab mov ax, word ptr es:[0x7d2e]
00af imul word ptr [0x143a] ; _tileWidth
00b3 mov si, word ptr [bp - 8]
00b6 sub si, ax
00b8 add si, word ptr [0xac7c] ; _SpidX
00bc mov ax, word ptr es:[0x7d30]
00c0 imul word ptr [0x143c] ; _tileHeight
00c4 sub ax, word ptr [bp - 0xa]
00c7 neg ax
00c9 add ax, word ptr [0xac7e] ; _SpidY
00cd mov word ptr [bp - 2], ax
00d0 test byte ptr [0xcc7e], 1 ; _displayType
00d5 je 0x1e44
00d7 jmp 0x1eca
00da mov es, word ptr [bp - 0xc]
00dd test byte ptr es:[di + 2], 0x80
00e2 jne 0x1e8c
00e4 mov ax, word ptr [0x143c] ; _tileHeight
00e7 imul word ptr [0xcd7a] ; _editHeight
00eb mov cx, word ptr es:[di + 0xa]
00ef mov dx, ax
00f1 sub ax, cx
00f3 sub ax, word ptr [bp - 2]
00f6 push ax
00f7 push si
00f8 push word ptr es:[di + 8]
00fc push cx
00fd mov ax, word ptr [0x143a] ; _tileWidth
0100 mov cx, dx
0102 imul word ptr [0xcc80] ; _editWidth
0106 push ax
0107 push cx
0108 mov ax, di
010a mov dx, es
010c add ax, 0xc
010f adc dx, 0
0112 push dx
0113 push ax
0114 push word ptr [bp - 4]
0117 push word ptr [bp - 6]
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 285, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvertMaskBitmap2
011f jmp 0x1f06
0121 nop 
0122 mov ax, word ptr [0x143c] ; _tileHeight
0125 imul word ptr [0xcd7a] ; _editHeight
0129 mov cx, word ptr es:[di + 0xa]
012d mov dx, ax
012f sub ax, cx
0131 sub ax, word ptr [bp - 2]
0134 push ax
0135 push si
0136 push word ptr es:[di + 8]
013a push cx
013b mov ax, word ptr [0x143a] ; _tileWidth
013e mov cx, dx
0140 imul word ptr [0xcc80] ; _editWidth
0144 push ax
0145 push cx
0146 mov ax, bx
0148 mov dx, es
014a add ax, 0xc
014d adc dx, 0
0150 push dx
0151 push ax
0152 push word ptr [bp - 4]
0155 push word ptr [bp - 6]
0158 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 347, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _CopyMaskBitmap2
015d jmp 0x1f06
015f nop 
0160 mov ax, word ptr [0x143c] ; _tileHeight
0163 imul word ptr [0xcd7a] ; _editHeight
0167 mov es, word ptr [bp - 0xc]
016a mov cx, word ptr es:[di + 0xa]
016e mov dx, ax
0170 sub ax, cx
0172 sub ax, word ptr [bp - 2]
0175 push ax
0176 push si
0177 push word ptr es:[di + 8]
017b push cx
017c mov ax, word ptr [0x143a] ; _tileWidth
017f mov cx, dx
0181 imul word ptr [0xcc80] ; _editWidth
0185 push ax
0186 push cx
0187 mov ax, es
0189 add di, 0xc
018c adc ax, 0
018f push ax
0190 push di
0191 push word ptr [bp - 4]
0194 push word ptr [bp - 6]
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _CopyMonoMaskBitmap
019c add sp, 0x14
019f sub si, word ptr [bp - 8]
01a2 mov ax, word ptr [bp - 0xa]
01a5 sub word ptr [bp - 2], ax
01a8 les bx, ptr [bp - 0x1c]
01ab cmp word ptr es:[bx], 5
01af je 0x1f47
01b1 mov es, word ptr [0xbfae]
01b5 mov al, byte ptr es:[0x7290]
01b9 and ax, 7
01bc push ax
01bd push word ptr [0xac80] ; _SpidDir
01c1 push word ptr [bp - 2]
01c4 push si
01c5 nop 
01c6 push cs
01c7 call 0x2be0 ; _DrawLegs
01ca add sp, 8
01cd push word ptr [0xac80] ; _SpidDir
01d1 push word ptr [bp - 2]
01d4 push si
01d5 nop 
01d6 push cs
01d7 call 0x2594 ; _DrawPalps
01da add sp, 6
01dd mov bx, 0x78a6
01e0 mov es, word ptr [0xbf94]
01e4 mov word ptr [bp - 0x20], bx
01e7 mov word ptr [bp - 0x1e], es
01ea cmp word ptr es:[bx], 0
01ee jl 0x1f7e
01f0 mov bx, word ptr [0x143a] ; _tileWidth
01f4 mov si, word ptr [bp - 0x20]
01f7 mov ax, word ptr es:[si]
01fa imul bx
01fc mov es, word ptr [0xbf90]
0200 add ax, word ptr es:[0x9b08]
0205 mov word ptr [bp - 0x18], ax
0208 mov cx, bx
020a shl cx, 1
020c add cx, bx
020e shl cx, 1
0210 add cx, bx
0212 jmp 0x1f97
0214 les bx, ptr [bp - 0x20]
0217 mov ax, word ptr es:[bx]
021a add ax, 7
021d imul word ptr [0x143a] ; _tileWidth
0221 mov es, word ptr [0xbf90]
0225 mov cx, word ptr es:[0x9b08]
022a mov word ptr [bp - 0x18], cx
022d add ax, cx
022f mov word ptr [bp - 0x14], ax
0232 mov es, word ptr [0xbfa6]
0236 cmp word ptr es:[0x9fc4], 0
023c jl 0x1fca
023e mov bx, word ptr [0x143c] ; _tileHeight
0242 mov ax, word ptr es:[0x9fc4]
0246 imul bx
0248 mov es, word ptr [0xbf90]
024c add ax, word ptr es:[0x9b0a]
0251 mov word ptr [bp - 0x16], ax
0254 mov cx, bx
0256 shl cx, 1
0258 add cx, bx
025a shl cx, 1
025c add cx, bx
025e jmp 0x1fe1
0260 mov ax, word ptr es:[0x9fc4]
0264 add ax, 7
0267 imul word ptr [0x143c] ; _tileHeight
026b mov es, word ptr [0xbf90]
026f mov cx, word ptr es:[0x9b0a]
0274 mov word ptr [bp - 0x16], cx
0277 add ax, cx
0279 mov word ptr [bp - 0x12], ax
027c push word ptr [0xbca6] ; _win_hwnd
0280 lea ax, [bp - 0x18]
0283 push ss
0284 push ax
0285 push 0
0287 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 648, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
028c les bx, ptr [bp - 0x20]
028f mov si, word ptr es:[bx]
0292 or si, si
0294 jge 0x2002
0296 xor si, si
0298 mov ax, word ptr es:[bx]
029b add ax, 7
029e mov cx, word ptr [0xcc80] ; _editWidth
02a2 dec cx
02a3 cmp ax, cx
02a5 jle 0x2013
02a7 mov ax, cx
02a9 mov word ptr [bp - 0x22], ax
02ac cmp ax, si
02ae jge 0x201d
02b0 jmp 0x20ac
02b3 mov word ptr [bp - 0xa], si
02b6 mov di, word ptr [0xcd7a] ; _editHeight
02ba mov es, word ptr [0xbfa6]
02be mov ax, word ptr es:[0x9fc4]
02c2 add ax, 7
02c5 lea cx, [di - 1]
02c8 mov dx, ax
02ca cmp ax, cx
02cc jle 0x203a
02ce mov ax, cx
02d0 mov word ptr [bp - 0x24], ax
02d3 lea ax, [di - 1]
02d6 cmp dx, ax
02d8 jle 0x2046
02da mov dx, ax
02dc mov word ptr [bp - 0x26], dx
02df mov si, word ptr [0xcd7a] ; _editHeight
02e3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 740, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
02e6 mov es, ax
02e8 mov bx, word ptr es:[0x9fc4]
02ed or bx, bx
02ef jge 0x205d
02f1 xor bx, bx
02f3 cmp word ptr [bp - 0x24], bx
02f6 jl 0x20a1
02f8 mov ax, word ptr [0xcc80] ; _editWidth
02fb imul bx
02fd add ax, word ptr [bp - 0xa]
0300 shl ax, 1
0302 add ax, word ptr [0x1442]
0306 mov dx, word ptr [0x1444]
030a mov word ptr [bp - 4], ax
030d mov word ptr [bp - 2], dx
0310 mov ax, word ptr [0xcc80] ; _editWidth
0313 shl ax, 1
0315 mov word ptr [bp - 8], ax
0318 mov ax, word ptr [bp - 0x26]
031b sub ax, bx
031d inc ax
031e mov word ptr [bp - 6], ax
0321 mov word ptr [bp - 0xc], bx
0324 lds bx, ptr [bp - 4]
0327 mov cx, ax
0329 mov di, word ptr [bp - 8]
032c mov word ptr [bx], 0xffff
0330 add bx, di
0332 dec cx
0333 jne 0x2096
0335 push ss
0336 pop ds
0337 inc word ptr [bp - 0xa]
033a mov ax, word ptr [bp - 0xa]
033d cmp word ptr [bp - 0x22], ax
0340 jge 0x2049
0342 push word ptr [bp - 0x10]
0345 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 840, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
034a add sp, 2
034d push word ptr [bp - 0x10]
0350 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 851, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_ReleaseHandle
0355 add sp, 2
0358 mov es, word ptr [0xbfb8]
035c cmp word ptr es:[0x85fc], 0
0362 jne 0x20d1
0364 jmp 0x22e0
0367 mov es, word ptr [0xbf8e]
036b cmp word ptr es:[0x9c28], 0
0371 jne 0x2155
0373 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 886, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0378 mov es, word ptr [0xbfba]
037c cmp dx, word ptr es:[0x87d8]
0381 jl 0x2155
0383 jg 0x20f6
0385 cmp ax, word ptr es:[0x87d6]
038a jbe 0x2155
038c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 911, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
0391 cdq 
0392 mov si, ax
0394 mov di, dx
0396 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 921, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
039b add si, ax
039d adc di, dx
039f add si, 0xb4
03a3 adc di, 0
03a6 mov es, word ptr [0xbfba]
03aa mov word ptr es:[0x87d6], si
03af mov word ptr es:[0x87d8], di
03b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 951, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
03b9 or ax, ax
03bb jne 0x214a
03bd mov es, word ptr [0xbfbc]
03c1 mov word ptr es:[0x75f8], 1
03c8 mov es, word ptr [0xbfbe]
03cc inc word ptr es:[0x87da]
03d1 cmp word ptr es:[0x87da], 5
03d7 jl 0x2155
03d9 mov word ptr es:[0x87da], ax
03dd jmp 0x2155
03df nop 
03e0 mov es, word ptr [0xbfbc]
03e4 mov word ptr es:[0x75f8], 0
03eb mov es, word ptr [0xbfc0]
03ef mov ax, word ptr es:[0x72f4]
03f3 les bx, ptr [bp - 0x1c]
03f6 cmp word ptr es:[bx], ax
03f9 je 0x2168
03fb jmp 0x22a0
03fe cmp word ptr es:[bx], 4
0402 jle 0x2171
0404 jmp 0x22a0
0407 mov es, word ptr [0xbfbc]
040b cmp word ptr es:[0x75f8], 0
0411 jne 0x2180
0413 jmp 0x22e0
0416 mov es, word ptr [0xbfc2]
041a mov bx, word ptr [0xac80] ; _SpidDir
041e mov al, byte ptr es:[bx + 8]
0423 cwde 
0424 shl ax, 3
0427 add ax, word ptr [0xac7e] ; _SpidY
042b mov word ptr [bp - 2], ax
042e les si, ptr [bp - 0x1c]
0431 mov bx, word ptr es:[si]
0434 mov cx, bx
0436 shl bx, 2
0439 add bx, cx
043b mov es, word ptr [0xbfbe]
043f add bx, word ptr es:[0x87da]
0444 shl bx, 2
0447 mov es, word ptr [0xbfc4]
044b les si, ptr es:[0x76a4]
0450 mov cx, word ptr es:[bx + si]
0453 mov dx, word ptr es:[bx + si + 2]
0457 mov word ptr [bp - 6], cx
045a mov word ptr [bp - 4], dx
045d mov es, word ptr [0xbfc6]
0461 mov bx, word ptr [0xac80] ; _SpidDir
0465 mov al, byte ptr es:[bx]
046a cwde 
046b shl ax, 3
046e add ax, word ptr [0xac7c] ; _SpidX
0472 mov word ptr [bp - 8], ax
0475 cdq 
0476 idiv word ptr [0x143a] ; _tileWidth
047a mov si, ax
047c mov ax, word ptr [bp - 2]
047f cdq 
0480 idiv word ptr [0x143c] ; _tileHeight
0484 mov di, ax
0486 mov bx, 0x9fd0
0489 mov es, word ptr [0xbfc8]
048d mov word ptr [bp - 0x2a], bx
0490 mov word ptr [bp - 0x28], es
0493 cmp word ptr es:[bx], 6
0497 jl 0x2206
0499 jmp 0x22e0
049c cmp word ptr [0xcc76], 1 ; _MapPlane
04a1 jne 0x2240
04a3 mov es, word ptr [0xbf92]
04a7 mov ax, word ptr es:[0x7d2e]
04ab mov word ptr [bp - 0x2c], ax
04ae cmp ax, si
04b0 jg 0x2240
04b2 add ax, word ptr [0xcc80] ; _editWidth
04b6 cmp ax, si
04b8 jle 0x2240
04ba mov ax, word ptr es:[0x7d30]
04be mov word ptr [bp - 0x2e], ax
04c1 lea cx, [di - 3]
04c4 cmp ax, cx
04c6 jg 0x2240
04c8 add ax, word ptr [0xcd7a] ; _editHeight
04cc cmp ax, di
04ce jle 0x2240
04d0 mov dx, 1
04d3 jmp 0x2242
04d5 nop 
04d6 xor dx, dx
04d8 or dx, dx
04da jne 0x2249
04dc jmp 0x22e0
04df mov ax, word ptr [bp - 8]
04e2 les bx, ptr [bp - 0x2a]
04e5 mov si, word ptr es:[bx]
04e8 mov cx, si
04ea shl si, 2
04ed mov es, word ptr [0xbfca]
04f1 mov word ptr es:[si - 0x7f2a], ax
04f6 mov ax, word ptr [bp - 2]
04f9 mov word ptr es:[si - 0x7f28], ax
04fe mov bx, cx
0500 shl bx, 1
0502 mov es, word ptr [0xbfcc]
0506 mov word ptr es:[bx + 0x7d68], 1
050d mov es, word ptr [0xbfce]
0511 mov word ptr es:[bx + 0x78be], 0xa
0518 mov ax, word ptr [bp - 6]
051b mov dx, word ptr [bp - 4]
051e mov es, word ptr [0xbfd0]
0522 mov word ptr es:[si + 0x7c24], ax
0527 mov word ptr es:[si + 0x7c26], dx
052c les bx, ptr [bp - 0x2a]
052f inc word ptr es:[bx]
0532 pop si
0533 pop di
0534 leave 
0535 retf 
0536 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
053b cdq 
053c mov si, ax
053e mov di, dx
0540 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1347, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0545 add si, ax
0547 adc di, dx
0549 add si, 0x1e
054c adc di, 0
054f mov es, word ptr [0xbfba]
0553 mov word ptr es:[0x87d6], si
0558 mov word ptr es:[0x87d8], di
055d mov es, word ptr [0xbfbc]
0561 mov word ptr es:[0x75f8], 0
0568 les bx, ptr [bp - 0x1c]
056b mov ax, word ptr es:[bx]
056e mov es, word ptr [0xbfc0]
0572 mov word ptr es:[0x72f4], ax
0576 pop si
0577 pop di
0578 leave 
0579 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near SpidX;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near SpidY;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_ConvertMonoMaskToTandy-4e3e71229c.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_ConvertMonoMaskToTandy-4e3e71229c.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_ConvertMonoMaskToTandy-4e3e71229c.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int near tileHeight;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_DrawPalps'], 'segment': 3, 'target_offset': 9620, 'caller_offsets': [471]}
- {'callee_names': ['_DrawLegs'], 'segment': 3, 'target_offset': 11232, 'caller_offsets': [455]}

## Neighbors

- {'symbol': '_InvalidUpdateEdit', 'offset': 7150, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 41}
- {'symbol': '_PreDrawSpider', 'offset': 7192, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 337}
- {'symbol': '_ed_MoveTo', 'offset': 8932, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 22}
- {'symbol': '_ed_LineTo', 'offset': 8954, 'source': None, 'size': 665}

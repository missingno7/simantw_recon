# Recovery task _OpenMiniMapWin

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 1254 bytes.

```asm
0000 enter 0x4c, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc22c]
000a mov ax, word ptr es:[0x9c28]
000e mov word ptr [bp - 6], ax
0011 test byte ptr [0xcc7e], 1 ; _displayType
0016 je 0xe392
0018 mov ax, 2
001b jmp 0xe395
001d nop 
001e mov ax, 1
0021 mov bx, 0x9be2
0024 mov es, word ptr [0xc22e]
0028 mov word ptr [bp - 0x26], bx
002b mov word ptr [bp - 0x24], es
002e mov word ptr es:[bx], ax
0031 mov bx, 0x9b88
0034 mov es, word ptr [0xc230]
0038 mov word ptr [bp - 0x22], bx
003b mov word ptr [bp - 0x20], es
003e mov word ptr es:[bx], ax
0041 push word ptr [bp + 8]
0044 push word ptr [bp + 6]
0047 push 0x1400
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
004f add sp, 6
0052 push word ptr [0xbcce]
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
005b add sp, 2
005e nop 
005f push cs
0060 call 0xd474 ; _Mini_DrawMapI
0063 les bx, ptr [bp - 0x26]
0066 mov ax, word ptr es:[bx]
0069 mov bx, 0x7d30
006c mov es, word ptr [0xc224]
0070 mov word ptr [bp - 0x2e], bx
0073 mov word ptr [bp - 0x2c], es
0076 mov cx, ax
0078 imul word ptr es:[bx]
007b mov bx, 0x7ef8
007e mov es, word ptr [0xc232]
0082 mov word ptr [bp - 0x32], bx
0085 mov word ptr [bp - 0x30], es
0088 add ax, word ptr es:[bx]
008b mov bx, 0x78e2
008e mov es, word ptr [0xc234]
0092 mov word ptr [bp - 0x2a], bx
0095 mov word ptr [bp - 0x28], es
0098 mov word ptr es:[bx], ax
009b mov dx, ax
009d mov ax, cx
009f mov bx, dx
00a1 imul word ptr [0xcd7a] ; _editHeight
00a5 add bx, ax
00a7 mov si, 0x78e6
00aa mov word ptr [bp - 0x36], si
00ad mov word ptr [bp - 0x34], es
00b0 mov word ptr es:[si], bx
00b3 les bx, ptr [bp - 0x22]
00b6 mov ax, word ptr es:[bx]
00b9 mov bx, 0x7d2e
00bc mov es, word ptr [0xc224]
00c0 mov word ptr [bp - 0x42], bx
00c3 mov word ptr [bp - 0x40], es
00c6 mov cx, ax
00c8 imul word ptr es:[bx]
00cb mov bx, 0xa0b0
00ce mov es, word ptr [0xc236]
00d2 mov word ptr [bp - 0x46], bx
00d5 mov word ptr [bp - 0x44], es
00d8 add ax, word ptr es:[bx]
00db mov bx, 0x7ef6
00de mov es, word ptr [0xc232]
00e2 mov word ptr [bp - 0x4a], bx
00e5 mov word ptr [bp - 0x48], es
00e8 add ax, word ptr es:[bx]
00eb mov bx, 0x78e0
00ee mov es, word ptr [0xc234]
00f2 mov word ptr [bp - 0x3e], bx
00f5 mov word ptr [bp - 0x3c], es
00f8 mov word ptr es:[bx], ax
00fb mov dx, ax
00fd mov ax, cx
00ff mov si, dx
0101 imul word ptr [0xcc80] ; _editWidth
0105 add si, ax
0107 mov di, 0x78e4
010a mov word ptr [bp - 0x3a], di
010d mov word ptr [bp - 0x38], es
0110 mov word ptr es:[di], si
0113 push word ptr [0xbcce]
0117 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
011c add sp, 2
011f push 1
0121 push word ptr [bp - 0x3c]
0124 push word ptr [bp - 0x3e]
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
012c add sp, 6
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0134 mov word ptr [0x1a34], 1 ; _mmapCursorState
013a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 317, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myButton
013f or ax, ax
0141 je 0xe50c
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myButton
0148 or ax, ax
014a jne 0xe4b7
014c lea ax, [bp - 4]
014f push ss
0150 push ax
0151 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 340, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GetMousePos
0156 add sp, 4
0159 push word ptr [0xbcce]
015d lea ax, [bp - 4]
0160 push ss
0161 push ax
0162 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 355, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
0167 push word ptr [bp - 0x48]
016a push word ptr [bp - 0x4a]
016d lea ax, [bp - 4]
0170 push ss
0171 push ax
0172 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 373, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PointInRect
0177 add sp, 8
017a or ax, ax
017c je 0xe50c
017e push 0x1400
0181 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 388, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
0186 add sp, 2
0189 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 396, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
018e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 401, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _OpenMapYard
0193 pop si
0194 pop di
0195 leave 
0196 retf 
0197 nop 
0198 push 1
019a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 413, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetPause
019f add sp, 2
01a2 push 0x1400
01a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 424, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01aa add sp, 2
01ad or ax, ax
01af jne 0xe528
01b1 jmp 0xe841
01b4 lea ax, [bp - 0x1e]
01b7 push ss
01b8 push ax
01b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 444, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
01be add sp, 4
01c1 or ax, ax
01c3 jne 0xe53c
01c5 jmp 0xe82f
01c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 459, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myButton
01cd or ax, ax
01cf jne 0xe548
01d1 jmp 0xe82f
01d4 push 0x1400
01d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 474, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01dc add sp, 2
01df or ax, ax
01e1 jne 0xe55a
01e3 jmp 0xe82f
01e6 push word ptr [bp - 0x48]
01e9 push word ptr [bp - 0x4a]
01ec lea ax, [bp - 0x16]
01ef push ss
01f0 push ax
01f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 500, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PointInRect
01f6 add sp, 8
01f9 or ax, ax
01fb jne 0xe574
01fd jmp 0xe710
0200 mov word ptr [bp - 4], 0x8000
0205 mov ax, word ptr [bp - 0x16]
0208 cmp word ptr [bp - 4], ax
020b jne 0xe58c
020d mov ax, word ptr [bp - 0x14]
0210 cmp word ptr [bp - 2], ax
0213 jne 0xe58c
0215 jmp 0xe6d2
0218 mov ax, word ptr [bp - 0x16]
021b mov dx, word ptr [bp - 0x14]
021e mov word ptr [bp - 4], ax
0221 mov word ptr [bp - 2], dx
0224 les bx, ptr [bp - 0x4a]
0227 sub ax, word ptr es:[bx]
022a les bx, ptr [bp - 0x22]
022d cdq 
022e idiv word ptr es:[bx]
0231 mov si, ax
0233 mov es, word ptr [0xc228]
0237 mov ax, word ptr es:[0x78ba]
023b mov word ptr [bp - 0x4c], ax
023e cmp ax, 0x40
0241 jne 0xe5ba
0243 sub si, 0x20
0246 mov ax, word ptr [bp - 0x14]
0249 les bx, ptr [bp - 0x32]
024c sub ax, word ptr es:[bx]
024f les bx, ptr [bp - 0x26]
0252 cdq 
0253 idiv word ptr es:[bx]
0256 mov di, ax
0258 or si, si
025a jge 0xe5d3
025c jmp 0xe6d2
025f cmp word ptr [bp - 0x4c], si
0262 jg 0xe5db
0264 jmp 0xe6d2
0267 push word ptr [0xbcce]
026b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 622, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0270 add sp, 2
0273 push 1
0275 push word ptr [bp - 0x3c]
0278 push word ptr [bp - 0x3e]
027b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 638, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
0280 add sp, 6
0283 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 646, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0288 mov word ptr [0x1a34], 0 ; _mmapCursorState
028e push word ptr [0xbca8]
0292 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 661, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0297 add sp, 2
029a nop 
029b push cs
029c call 0xc70c ; _EraseMapCursor
029f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 674, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
02a4 push di
02a5 push si
02a6 nop 
02a7 push cs
02a8 call 0x11620
02ab add sp, 4
02ae or ax, ax
02b0 je 0xe637
02b2 mov es, word ptr [0xc22a]
02b6 cmp word ptr es:[0x85f2], 0
02bc je 0xe637
02be nop 
02bf push cs
02c0 call 0x111e0
02c3 push word ptr [0xbca8]
02c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 714, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
02cc add sp, 2
02cf nop 
02d0 push cs
02d1 call 0xc652 ; _DrawMapCursor
02d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 727, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
02d9 les bx, ptr [bp - 0x26]
02dc mov ax, word ptr es:[bx]
02df les bx, ptr [bp - 0x2e]
02e2 mov cx, ax
02e4 imul word ptr es:[bx]
02e7 les bx, ptr [bp - 0x32]
02ea add ax, word ptr es:[bx]
02ed les bx, ptr [bp - 0x2a]
02f0 mov word ptr es:[bx], ax
02f3 mov dx, ax
02f5 mov ax, cx
02f7 mov bx, dx
02f9 imul word ptr [0xcd7a] ; _editHeight
02fd add bx, ax
02ff les si, ptr [bp - 0x36]
0302 mov word ptr es:[si], bx
0305 les bx, ptr [bp - 0x22]
0308 mov ax, word ptr es:[bx]
030b les bx, ptr [bp - 0x42]
030e mov cx, ax
0310 imul word ptr es:[bx]
0313 les bx, ptr [bp - 0x46]
0316 add ax, word ptr es:[bx]
0319 les bx, ptr [bp - 0x4a]
031c add ax, word ptr es:[bx]
031f les bx, ptr [bp - 0x3e]
0322 mov word ptr es:[bx], ax
0325 mov dx, ax
0327 mov ax, cx
0329 mov si, dx
032b imul word ptr [0xcc80] ; _editWidth
032f add si, ax
0331 les di, ptr [bp - 0x3a]
0334 mov word ptr es:[di], si
0337 push word ptr [0xbcce]
033b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 830, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0340 add sp, 2
0343 push 1
0345 push word ptr [bp - 0x3c]
0348 push word ptr [bp - 0x3e]
034b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 846, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
0350 add sp, 6
0353 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 854, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0358 mov word ptr [0x1a34], 1 ; _mmapCursorState
035e lea ax, [bp - 0x16]
0361 push ss
0362 push ax
0363 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 870, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GetMousePos
0368 add sp, 4
036b push word ptr [0xbcce]
036f lea ax, [bp - 0x16]
0372 push ss
0373 push ax
0374 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 885, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
0379 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 892, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myButton
037e or ax, ax
0380 je 0xe6f9
0382 jmp 0xe579
0385 mov es, word ptr [0xc22a]
0389 cmp word ptr es:[0x85f2], ax
038e je 0xe707
0390 jmp 0xe82f
0393 nop 
0394 push cs
0395 call 0x111e0
0398 jmp 0xe82f
039b nop 
039c push word ptr [0xbcce]
03a0 lea ax, [bp - 0xe]
03a3 push ss
03a4 push ax
03a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 934, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 33}}]
03aa lea ax, [bp - 0xe]
03ad push ss
03ae push ax
03af lea ax, [bp - 0x16]
03b2 push ss
03b3 push ax
03b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 951, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PointInRect
03b9 add sp, 8
03bc or ax, ax
03be jne 0xe737
03c0 jmp 0xe824
03c3 push word ptr [0xbcce]
03c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 970, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
03cc add sp, 2
03cf push 1
03d1 push word ptr [bp - 0x3c]
03d4 push word ptr [bp - 0x3e]
03d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 986, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
03dc add sp, 6
03df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 994, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
03e4 mov word ptr [0x1a34], 0 ; _mmapCursorState
03ea push word ptr [0xbca8]
03ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1009, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
03f3 add sp, 2
03f6 nop 
03f7 push cs
03f8 call 0xc70c ; _EraseMapCursor
03fb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1022, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0400 push word ptr [bp - 0x14]
0403 push word ptr [bp - 0x16]
0406 nop 
0407 push cs
0408 call 0x11620
040b add sp, 4
040e nop 
040f push cs
0410 call 0x111e0
0413 push word ptr [0xbca8]
0417 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1050, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
041c add sp, 2
041f nop 
0420 push cs
0421 call 0xc652 ; _DrawMapCursor
0424 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1063, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0429 les bx, ptr [bp - 0x26]
042c mov ax, word ptr es:[bx]
042f les bx, ptr [bp - 0x2e]
0432 mov cx, ax
0434 imul word ptr es:[bx]
0437 les bx, ptr [bp - 0x32]
043a add ax, word ptr es:[bx]
043d les bx, ptr [bp - 0x2a]
0440 mov word ptr es:[bx], ax
0443 mov dx, ax
0445 mov ax, cx
0447 mov bx, dx
0449 imul word ptr [0xcd7a] ; _editHeight
044d add bx, ax
044f les si, ptr [bp - 0x36]
0452 mov word ptr es:[si], bx
0455 les bx, ptr [bp - 0x22]
0458 mov ax, word ptr es:[bx]
045b les bx, ptr [bp - 0x42]
045e mov cx, ax
0460 imul word ptr es:[bx]
0463 les bx, ptr [bp - 0x46]
0466 add ax, word ptr es:[bx]
0469 les bx, ptr [bp - 0x4a]
046c add ax, word ptr es:[bx]
046f les bx, ptr [bp - 0x3e]
0472 mov word ptr es:[bx], ax
0475 mov dx, ax
0477 mov ax, cx
0479 mov si, dx
047b imul word ptr [0xcc80] ; _editWidth
047f add si, ax
0481 les di, ptr [bp - 0x3a]
0484 mov word ptr es:[di], si
0487 push word ptr [0xbcce]
048b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0490 add sp, 2
0493 push 1
0495 push word ptr [bp - 0x3c]
0498 push word ptr [bp - 0x3e]
049b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
04a0 add sp, 6
04a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
04a8 mov word ptr [0x1a34], 1 ; _mmapCursorState
04ae jmp 0xe82f
04b0 push 0x1400
04b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
04b8 add sp, 2
04bb push 0x1400
04be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1217, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
04c3 add sp, 2
04c6 or ax, ax
04c8 je 0xe841
04ca jmp 0xe528
04cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1232, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
04d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1237, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
04d7 push word ptr [bp - 6]
04da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetPause
04df add sp, 2
04e2 pop si
04e3 pop di
04e4 leave 
04e5 retf 
```

## Known declaration examples

- `extern void far DrawMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);` — src/recovered/EraseMiniMapCursor.c
- `extern void far GetMousePos(struct CursorPoint far *point);` — src/recovered/win_IsCursorInObj.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far OpenMapYard(void);` — src/recovered/DoTab.c
- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/wf_win_IsPointInObj-538ab6cada.c
- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern void far SetPause(int pause);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near mmapCursorState;` — src/recovered/EraseMiniMapCursor.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Close(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_GetEvent(struct DialogEvent far *event);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MapAreaEvent', 'offset': 57600, 'source': None, 'size': 514}
- {'symbol': '_Mini_MakeTable', 'offset': 58114, 'source': 'src/recovered/wf_Mini_MakeTable-a03e1a6138.c', 'size': 114}
- {'symbol': '_DrawMiniMapCursor', 'offset': 59482, 'source': None, 'size': 155}
- {'symbol': '_EraseMiniMapCursor', 'offset': 59638, 'source': 'src/recovered/EraseMiniMapCursor.c', 'size': 40}

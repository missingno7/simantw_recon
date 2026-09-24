# Recovery task _AboutDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1192 bytes.

```asm
0000 enter 0x32, 0
0004 push di
0005 push si
0006 sub ax, ax
0008 mov word ptr [bp - 0xa], ax
000b mov word ptr [bp - 0xc], ax
000e mov es, word ptr [0xc14e]
0012 mov ax, word ptr es:[0x9c28]
0016 mov word ptr [bp - 0x1c], ax
0019 push 1
001b nop 
001c push cs
001d call 0x4e34 ; _SetPause
0020 add sp, 2
0023 push 0x1f00
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
002b add sp, 2
002e push word ptr [0xbce4]
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0037 add sp, 2
003a xor di, di
003c push 0x6a4
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _LoadStringAnt
0044 add sp, 2
0047 mov es, dx
0049 mov bx, ax
004b mov word ptr [bp - 0x1a], bx
004e mov word ptr [bp - 0x18], es
0051 mov ax, word ptr es:[bx + 2]
0055 or ax, word ptr es:[bx]
0058 je 0xcfa4
005a mov ds, word ptr [bp - 0x18]
005d inc di
005e add bx, 4
0061 mov ax, word ptr [bx + 2]
0064 or ax, word ptr [bx]
0066 jne 0xcf97
0068 push ss
0069 pop ds
006a nop 
006b push cs
006c call 0x9b9a ; _DialogClearWaitInit
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0074 mov word ptr [bp - 0x16], ax
0077 mov word ptr [bp - 0x14], dx
007a nop 
007b push cs
007c call 0x9b6c ; _DialogClearWait
007f mov word ptr [bp - 0x12], di
0082 push 0x5a
0084 lea ax, [bp - 0x16]
0087 push ss
0088 push ax
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitedEnough
008e add sp, 6
0091 or ax, ax
0093 jne 0xcffa
0095 nop 
0096 push cs
0097 call 0x9c98 ; _DialogAbortOrCont
009a or ax, ax
009c jne 0xcfe1
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
00a3 or ax, ax
00a5 je 0xcfbc
00a7 cmp word ptr [bp - 0xa], 0
00ab jle 0xcfea
00ad jmp 0xd39e
00b0 jl 0xcff5
00b2 cmp word ptr [bp - 0xc], 1
00b6 jbe 0xcff5
00b8 jmp 0xd39e
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
00c0 add word ptr [bp - 0xc], 1
00c4 adc word ptr [bp - 0xa], 0
00c8 lea ax, [bp - 0x24]
00cb push ss
00cc push ax
00cd push 0x1f02
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
00d5 add sp, 6
00d8 push word ptr [0xbce4]
00dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00e1 add sp, 2
00e4 push 0x1f01
00e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawObjectNum
00ec add sp, 2
00ef lea ax, [bp - 0x24]
00f2 push ss
00f3 push ax
00f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_ToRect
00f9 add sp, 4
00fc push word ptr [bp - 0x24]
00ff push word ptr [bp - 0x22]
0102 push word ptr [bp - 0x20]
0105 push word ptr [bp - 0x1e]
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
010d mov si, ax
010f push word ptr [0xcf52] ; _clipDC
0113 push si
0114 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 277, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 44}}]
0119 push si
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
011f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 290, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0124 push 0x1f02
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
012c add sp, 2
012f xor ax, ax
0131 mov word ptr [bp - 0x10], ax
0134 mov word ptr [bp - 0xe], ax
0137 mov word ptr [bp - 6], ax
013a or di, di
013c jg 0xd07b
013e jmp 0xd370
0141 mov si, ax
0143 mov es, word ptr [0xc150]
0147 cmp word ptr es:[0x34], 0
014d jne 0xd08c
014f jmp 0xd370
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0157 mov word ptr [bp - 0x16], ax
015a mov word ptr [bp - 0x14], dx
015d nop 
015e push cs
015f call 0x9b6c ; _DialogClearWait
0162 mov word ptr [bp - 0xe], si
0165 cmp word ptr [bp - 0x10], 0
0169 jne 0xd0b0
016b cmp si, 1
016e jne 0xd0b0
0170 mov cx, 0x36
0173 jmp 0xd0b3
0175 nop 
0176 mov cx, 1
0179 push cx
017a lea ax, [bp - 0x16]
017d push ss
017e push ax
017f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 386, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitedEnough
0184 add sp, 6
0187 or ax, ax
0189 jne 0xd0f0
018b nop 
018c push cs
018d call 0x9c98 ; _DialogAbortOrCont
0190 or ax, ax
0192 jne 0xd0d7
0194 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 407, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
0199 or ax, ax
019b je 0xd09f
019d cmp word ptr [bp - 0xa], 0
01a1 jle 0xd0e0
01a3 jmp 0xd39e
01a6 jl 0xd0eb
01a8 cmp word ptr [bp - 0xc], 3
01ac jbe 0xd0eb
01ae jmp 0xd39e
01b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 436, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
01b6 add word ptr [bp - 0xc], 1
01ba adc word ptr [bp - 0xa], 0
01be push 4
01c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 451, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
01c5 add sp, 2
01c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 459, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
01cd mov di, ax
01cf push word ptr [0xbce4]
01d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 470, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
01d8 add sp, 2
01db lea ax, [bp - 0x24]
01de push ss
01df push ax
01e0 push 0x1f02
01e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 486, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
01e8 add sp, 6
01eb push word ptr [bp - 0x24]
01ee push word ptr [bp - 0x22]
01f1 push word ptr [bp - 0x20]
01f4 push word ptr [bp - 0x1e]
01f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 504, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 64}}]
01fc mov word ptr [bp - 4], ax
01ff push word ptr [0xcf52] ; _clipDC
0203 push ax
0204 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 517, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 44}}]
0209 push word ptr [bp - 4]
020c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 525, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
0211 push 0x1f02
0214 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 535, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
0219 add sp, 2
021c mov si, word ptr [bp - 0x22]
021f sub si, word ptr [bp - 0xe]
0222 mov ax, word ptr [bp - 0x10]
0225 mov word ptr [bp - 2], ax
0228 cmp word ptr [bp - 6], 0
022c jne 0xd16b
022e jmp 0xd29e
0231 push word ptr [bp - 0x22]
0234 push word ptr [bp - 0x24]
0237 push word ptr [bp - 0x1e]
023a push word ptr [bp - 0x20]
023d mov ax, word ptr [bp - 0x22]
0240 inc ax
0241 push ax
0242 push word ptr [bp - 0x24]
0245 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 584, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxMove
024a add sp, 0xc
024d mov ax, word ptr [bp - 0x1e]
0250 sub ax, word ptr [bp - 0x22]
0253 add si, ax
0255 mov ax, word ptr [bp - 0x1e]
0258 sub ax, word ptr [bp - 0x22]
025b add ax, di
025d dec ax
025e cdq 
025f idiv di
0261 add word ptr [bp - 2], ax
0264 mov ax, word ptr [bp - 0x12]
0267 cmp word ptr [bp - 2], ax
026a jge 0xd208
026c mov bx, word ptr [bp - 2]
026f shl bx, 2
0272 mov es, word ptr [bp - 0x18]
0275 add bx, word ptr [bp - 0x1a]
0278 mov word ptr [bp - 0x30], bx
027b mov word ptr [bp - 0x2e], es
027e les bx, ptr es:[bx]
0281 cmp byte ptr es:[bx], 0
0285 je 0xd208
0287 mov word ptr [bp - 0x2a], si
028a mov ax, di
028c add ax, si
028e mov word ptr [bp - 0x26], ax
0291 mov ax, word ptr [bp - 0x24]
0294 mov word ptr [bp - 0x2c], ax
0297 mov ax, word ptr [bp - 0x20]
029a mov word ptr [bp - 0x28], ax
029d push 3
029f les bx, ptr [bp - 0x30]
02a2 push word ptr es:[bx + 2]
02a6 push word ptr es:[bx]
02a9 lea ax, [bp - 0x2c]
02ac push ss
02ad push ax
02ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 689, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _gr_JustifyStrInRect
02b3 add sp, 0xa
02b6 push word ptr [0xce8a] ; __backColor
02ba mov ax, si
02bc add ax, di
02be push ax
02bf push word ptr [bp - 0x20]
02c2 push si
02c3 mov es, word ptr [0xc152]
02c7 push word ptr es:[0x7692]
02cc jmp 0xd218
02ce push word ptr [0xce8a] ; __backColor
02d2 mov ax, si
02d4 add ax, di
02d6 push ax
02d7 push word ptr [bp - 0x20]
02da push si
02db push word ptr [bp - 0x24]
02de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 737, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
02e3 add sp, 0xa
02e6 mov ax, word ptr [bp - 2]
02e9 dec ax
02ea cmp ax, word ptr [bp - 0x12]
02ed jge 0xd298
02ef mov bx, word ptr [bp - 2]
02f2 shl bx, 2
02f5 mov es, word ptr [bp - 0x18]
02f8 add bx, word ptr [bp - 0x1a]
02fb mov word ptr [bp - 0x30], bx
02fe mov word ptr [bp - 0x2e], es
0301 les bx, ptr es:[bx - 4]
0305 cmp byte ptr es:[bx], 0
0309 je 0xd298
030b mov ax, si
030d sub ax, di
030f mov word ptr [bp - 0x2a], ax
0312 mov cx, ax
0314 add ax, di
0316 mov word ptr [bp - 0x26], ax
0319 mov ax, word ptr [bp - 0x24]
031c mov word ptr [bp - 0x2c], ax
031f mov ax, word ptr [bp - 0x20]
0322 mov word ptr [bp - 0x28], ax
0325 push 3
0327 les bx, ptr [bp - 0x30]
032a push word ptr es:[bx - 2]
032e push word ptr es:[bx - 4]
0332 lea ax, [bp - 0x2c]
0335 push ss
0336 push ax
0337 mov word ptr [bp - 0x32], cx
033a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 829, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _gr_JustifyStrInRect
033f add sp, 0xa
0342 push word ptr [0xce8a] ; __backColor
0346 push si
0347 push word ptr [bp - 0x20]
034a push word ptr [bp - 0x32]
034d mov es, word ptr [0xc152]
0351 push word ptr es:[0x7692]
0356 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 857, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
035b add sp, 0xa
035e mov word ptr [bp - 8], di
0361 jmp 0xd341
0364 cmp word ptr [bp - 0x1e], si
0367 jle 0xd298
0369 mov ax, word ptr [bp - 2]
036c shl ax, 2
036f add ax, word ptr [bp - 0x1a]
0372 mov dx, word ptr [bp - 0x18]
0375 mov word ptr [bp - 6], ax
0378 mov word ptr [bp - 4], dx
037b mov word ptr [bp - 8], di
037e mov ax, word ptr [bp - 0x12]
0381 cmp word ptr [bp - 2], ax
0384 jge 0xd314
0386 les bx, ptr [bp - 6]
0389 les bx, ptr es:[bx]
038c cmp byte ptr es:[bx], 0
0390 je 0xd314
0392 mov word ptr [bp - 0x2a], si
0395 mov ax, di
0397 add ax, si
0399 mov word ptr [bp - 0x26], ax
039c mov ax, word ptr [bp - 0x24]
039f mov word ptr [bp - 0x2c], ax
03a2 mov ax, word ptr [bp - 0x20]
03a5 mov word ptr [bp - 0x28], ax
03a8 push 3
03aa les bx, ptr [bp - 6]
03ad push word ptr es:[bx + 2]
03b1 push word ptr es:[bx]
03b4 lea ax, [bp - 0x2c]
03b7 push ss
03b8 push ax
03b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 956, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _gr_JustifyStrInRect
03be add sp, 0xa
03c1 push word ptr [0xce8a] ; __backColor
03c5 mov ax, si
03c7 add ax, di
03c9 push ax
03ca push word ptr [bp - 0x20]
03cd push si
03ce mov es, word ptr [0xc152]
03d2 push word ptr es:[0x7692]
03d7 jmp 0xd324
03d9 nop 
03da push word ptr [0xce8a] ; __backColor
03de mov ax, si
03e0 add ax, di
03e2 push ax
03e3 push word ptr [bp - 0x20]
03e6 push si
03e7 push word ptr [bp - 0x24]
03ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1005, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
03ef add sp, 0xa
03f2 add word ptr [bp - 6], 4
03f6 inc word ptr [bp - 2]
03f9 mov ax, si
03fb add ax, di
03fd mov si, ax
03ff cmp si, word ptr [bp - 0x1e]
0402 jge 0xd341
0404 jmp 0xd2b8
0407 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1034, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
040c mov ax, word ptr [bp - 8]
040f inc word ptr [bp - 0xe]
0412 cmp word ptr [bp - 0xe], ax
0415 jne 0xd398
0417 xor si, si
0419 inc word ptr [bp - 0x10]
041c push 0
041e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1057, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0423 add sp, 2
0426 mov word ptr [bp - 6], 1
042b mov ax, word ptr [bp - 0x12]
042e cmp word ptr [bp - 0x10], ax
0431 jge 0xd370
0433 jmp 0xd07d
0436 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1081, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
043b push word ptr [0xbce4]
043f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1090, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0444 add sp, 2
0447 push 0x1f02
044a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawObjectNum
044f add sp, 2
0452 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0457 mov di, word ptr [bp - 0x12]
045a jmp 0xcfa9
045d nop 
045e mov si, word ptr [bp - 0xe]
0461 jmp 0xd356
0463 nop 
0464 nop 
0465 push cs
0466 call 0x9cd4 ; _DialogDone
0469 push word ptr [bp - 0x18]
046c push word ptr [bp - 0x1a]
046f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1138, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _free
0474 add sp, 4
0477 push 4
0479 push 0x6a4
047c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1151, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0481 add sp, 4
0484 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
0489 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
048e push 0x1f00
0491 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
0496 add sp, 2
0499 push word ptr [bp - 0x1c]
049c nop 
049d push cs
049e call 0x4e34 ; _SetPause
04a1 add sp, 2
04a4 pop si
04a5 pop di
04a6 leave 
04a7 retf 
```

## Known declaration examples

- `extern void far DialogClearWait(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far DialogClearWaitInit(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far DialogDone(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_PrepareStrings-9dd732cc1e.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
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
- `extern void far SetPause(int pause);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbort-1a41498b6d.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbortOrCont-ea87855190.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogWait-50782e4ed5.c
- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GRectFillOutline-24e4a6aa35.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern int near clipDC;` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far db_PurgeObject(int object, int kind);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern void free(void far *block);` — src/recovered/mem_free_wrapper.c
- `extern void far free(void far *block);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Close(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far win_Events(void);` — src/recovered/wf_myDelay-ac936e115a.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_SetPause'], 'segment': 1, 'target_offset': 20020, 'caller_offsets': [29, 1182]}
- {'callee_names': ['_DialogClearWait'], 'segment': 1, 'target_offset': 39788, 'caller_offsets': [124, 351]}
- {'callee_names': ['_DialogClearWaitInit'], 'segment': 1, 'target_offset': 39834, 'caller_offsets': [108]}
- {'callee_names': ['_DialogAbortOrCont'], 'segment': 1, 'target_offset': 40088, 'caller_offsets': [151, 397]}
- {'callee_names': ['_DialogDone'], 'segment': 1, 'target_offset': 40148, 'caller_offsets': [1126]}

## Neighbors

- {'symbol': '_initControls', 'offset': 52356, 'source': 'src/recovered/wf_tu_simant_B324_initControls_1_scaffold-03091459d8.c', 'size': 291}
- {'symbol': '_DrawSimPayoff', 'offset': 52648, 'source': None, 'size': 401}
- {'symbol': '_ShowIntro', 'offset': 54242, 'source': None, 'size': 290}
- {'symbol': '_LoadMonoPats', 'offset': 54532, 'source': None, 'size': 278}

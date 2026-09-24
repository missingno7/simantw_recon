# Recovery task _win_DrawObjectI

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 1076 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 les bx, ptr [bp + 6]
0009 mov word ptr [bp - 6], bx
000c mov word ptr [bp - 4], es
000f test byte ptr es:[bx + 0x24], 4
0014 je 0xb72c
0016 mov al, byte ptr es:[bx + 0x27]
001a jmp 0xb730
001c mov al, byte ptr es:[bx + 0x26]
0020 cwde 
0021 mov cx, ax
0023 shl ax, 1
0025 add ax, cx
0027 shl ax, 1
0029 add ax, 0x78ec
002c mov word ptr [0xcc58], ax
002f mov <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0035 test byte ptr [0xcc7e], 1 ; _displayType
003a jne 0xb762
003c les bx, ptr [0xcc58]
0040 mov al, byte ptr es:[bx]
0043 cwde 
0044 imul ax, ax, 0x101
0048 push ax
0049 mov cx, ax
004b mov al, byte ptr es:[bx + 2]
004f jmp 0xb775
0051 nop 
0052 les bx, ptr [0xcc58]
0056 mov al, byte ptr es:[bx]
0059 cwde 
005a imul ax, ax, 0x101
005e push ax
005f mov cx, ax
0061 mov al, byte ptr es:[bx + 3]
0065 cwde 
0066 imul ax, ax, 0x101
006a push ax
006b push cx
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
0071 add sp, 6
0074 les bx, ptr [bp + 6]
0077 test byte ptr es:[bx + 0x25], 2
007c je 0xb7a1
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
0083 push word ptr [bp + 8]
0086 push word ptr [bp + 6]
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SubInclude
008e add sp, 4
0091 les bx, ptr [bp + 6]
0094 mov al, byte ptr es:[bx + 0x21]
0098 cwde 
0099 dec ax
009a dec ax
009b cmp ax, 0x14
009e jbe 0xb7b3
00a0 jmp 0xbb10
00a3 shl ax, 1
00a5 xchg bx, ax
00a6 jmp word ptr cs:[bx - 0x4844]
00ab nop 
00ac dw offset 0xb7e6
00ae dw offset 0xbb10
00b0 dw offset 0xb7f8
00b2 dw offset 0xb804
00b4 dw offset 0xb8aa
00b6 dw offset 0xb8be
00b8 dw offset 0xb8be
00ba dw offset 0xb882
00bc dw offset 0xbb10
00be dw offset 0xbb10
00c0 dw offset 0xb8c6
00c2 dw offset 0xb8e4
00c4 dw offset 0xbb10
00c6 dw offset 0xb900
00c8 dw offset 0xb9b1
00ca dw offset 0xb930
00cc dw offset 0xbb10
00ce dw offset 0xba3a
00d0 dw offset 0xba6a
00d2 dw offset 0xba7e
00d4 dw offset 0xbab8
00d6 push word ptr [bp - 4]
00d9 push word ptr [bp - 6]
00dc nop 
00dd push cs
00de call 0xb54a ; _win_RectFill
00e1 add sp, 4
00e4 jmp 0xbb10
00e7 nop 
00e8 push ds
00e9 push 0xbc62
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
00f1 jmp 0xb7f1
00f3 nop 
00f4 les bx, ptr [0xcc58]
00f8 mov al, byte ptr es:[bx + 2]
00fc cwde 
00fd imul ax, ax, 0x101
0101 push ax
0102 push word ptr [bp - 4]
0105 push word ptr [bp - 6]
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
010d add sp, 6
0110 push ds
0111 push 0xbc2b
0114 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 279, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0119 add sp, 4
011c mov es, word ptr [bp + 8]
011f mov bx, word ptr [bp + 6]
0122 test byte ptr es:[bx + 0x24], 4
0127 je 0xb840
0129 mov al, byte ptr es:[bx + 0x27]
012d jmp 0xb844
012f nop 
0130 mov al, byte ptr es:[bx + 0x26]
0134 cwde 
0135 mov cx, ax
0137 shl ax, 1
0139 add ax, cx
013b shl ax, 1
013d add ax, 0x78ec
0140 mov word ptr [0xcc58], ax
0143 mov <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0149 test byte ptr [0xcc7e], 1 ; _displayType
014e jne 0xb894
0150 les bx, ptr [0xcc58]
0154 mov al, byte ptr es:[bx]
0157 cwde 
0158 imul ax, ax, 0x101
015c push ax
015d mov cx, ax
015f mov al, byte ptr es:[bx + 2]
0163 cwde 
0164 imul ax, ax, 0x101
0168 push ax
0169 push cx
016a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 365, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
016f add sp, 6
0172 mov ax, word ptr [bp + 6]
0175 mov dx, word ptr [bp + 8]
0178 add ax, 0x2a
017b mov si, ax
017d mov word ptr [bp - 8], dx
0180 jmp 0xb9fd
0183 nop 
0184 les bx, ptr [0xcc58]
0188 mov al, byte ptr es:[bx]
018b cwde 
018c imul ax, ax, 0x101
0190 push ax
0191 mov cx, ax
0193 mov al, byte ptr es:[bx + 3]
0197 jmp 0xb873
0199 nop 
019a mov bx, word ptr [bp + 6]
019d push word ptr es:[bx + 0x28]
01a1 push es
01a2 push bx
01a3 nop 
01a4 push cs
01a5 call 0xbe30 ; _win_DrawBitMapAtObj
01a8 add sp, 6
01ab jmp 0xbb10
01ae push ds
01af push 0xbc4e
01b2 jmp 0xb7fc
01b5 nop 
01b6 mov si, word ptr [bp - 6]
01b9 mov es, word ptr [bp - 4]
01bc push word ptr es:[si + 6]
01c0 push word ptr es:[si + 2]
01c4 push ds
01c5 push 0xbc74
01c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 459, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01cd add sp, 8
01d0 jmp 0xbb10
01d3 nop 
01d4 mov bx, word ptr [bp + 6]
01d7 mov al, byte ptr es:[bx + 0x24]
01db and ax, 4
01de cmp ax, 1
01e1 sbb si, si
01e3 and si, 2
01e6 add si, 2
01e9 push word ptr es:[bx + si + 0x26]
01ed jmp 0xb8b1
01ef nop 
01f0 mov ax, word ptr [bp - 6]
01f3 mov dx, word ptr [bp - 4]
01f6 push ds
01f7 lea di, [bp - 0x12]
01fa mov si, ax
01fc push ss
01fd pop es
01fe mov ds, dx
0200 movsw word ptr es:[di], word ptr [si]
0201 movsw word ptr es:[di], word ptr [si]
0202 movsw word ptr es:[di], word ptr [si]
0203 movsw word ptr es:[di], word ptr [si]
0204 pop ds
0205 inc word ptr [bp - 0xe]
0208 inc word ptr [bp - 0xc]
020b les bx, ptr [bp + 6]
020e mov al, byte ptr es:[bx + 0x28]
0212 cwde 
0213 push ax
0214 lea ax, [bp - 0x12]
0217 push ss
0218 push ax
0219 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 540, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectOutline
021e jmp 0xb8b8
0220 les bx, ptr [0xcc58]
0224 mov al, byte ptr es:[bx + 2]
0228 cwde 
0229 imul ax, ax, 0x101
022d push ax
022e push word ptr [bp - 4]
0231 push word ptr [bp - 6]
0234 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 567, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
0239 add sp, 6
023c push ds
023d push 0xbc2b
0240 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 579, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0245 add sp, 4
0248 mov es, word ptr [bp + 8]
024b mov bx, word ptr [bp + 6]
024e test byte ptr es:[bx + 0x24], 4
0253 je 0xb96c
0255 mov al, byte ptr es:[bx + 0x27]
0259 jmp 0xb970
025b nop 
025c mov al, byte ptr es:[bx + 0x26]
0260 cwde 
0261 mov cx, ax
0263 shl ax, 1
0265 add ax, cx
0267 shl ax, 1
0269 add ax, 0x78ec
026c mov word ptr [0xcc58], ax
026f mov <resolved loader operand; see bindings> ; [{'operand_offset': 627, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0275 test byte ptr [0xcc7e], 1 ; _displayType
027a je 0xb98f
027c jmp 0xba24
027f les bx, ptr [0xcc58]
0283 mov al, byte ptr es:[bx]
0286 cwde 
0287 imul ax, ax, 0x101
028b push ax
028c mov cx, ax
028e mov al, byte ptr es:[bx + 2]
0292 cwde 
0293 imul ax, ax, 0x101
0297 push ax
0298 push cx
0299 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 668, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
029e add sp, 6
02a1 les bx, ptr [bp + 6]
02a4 mov al, byte ptr es:[bx + 0x28]
02a8 cwde 
02a9 push ax
02aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 685, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
02af add sp, 2
02b2 les bx, ptr [bp + 6]
02b5 mov ax, word ptr es:[bx + 0x2c]
02b9 or ax, word ptr es:[bx + 0x2a]
02bd je 0xb9d2
02bf jmp 0xbae2
02c2 mov ax, bx
02c4 mov dx, es
02c6 add ax, 0x2e
02c9 mov si, ax
02cb mov word ptr [bp - 8], dx
02ce mov es, word ptr [0xc6c8]
02d2 cmp word ptr es:[0xbd08], 0
02d8 jne 0xb9fd
02da push 0x25
02dc push dx
02dd push si
02de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 737, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
02e3 add sp, 6
02e6 or dx, ax
02e8 je 0xb9fd
02ea jmp 0xbb06
02ed les bx, ptr [bp + 6]
02f0 mov al, byte ptr es:[bx + 0x28]
02f4 cwde 
02f5 push ax
02f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 761, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
02fb add sp, 2
02fe les bx, ptr [bp + 6]
0301 mov ax, word ptr es:[bx + 0x24]
0305 and ax, 0x180
0308 shr ax, 7
030b push ax
030c push word ptr [bp - 8]
030f push si
0310 jmp 0xbaf8
0313 nop 
0314 les bx, ptr [0xcc58]
0318 mov al, byte ptr es:[bx]
031b cwde 
031c imul ax, ax, 0x101
0320 push ax
0321 mov cx, ax
0323 mov al, byte ptr es:[bx + 3]
0327 jmp 0xb9a2
032a mov bx, word ptr [bp + 6]
032d mov al, byte ptr es:[bx + 0x28]
0331 cwde 
0332 mov si, ax
0334 or byte ptr [bp - 1], 5
0338 and byte ptr [bp - 1], 0xf5
033c push word ptr [0xcf4e] ; __foreColor
0340 push word ptr [0xcf4e] ; __foreColor
0344 mov al, byte ptr [bp - 1]
0347 push ax
0348 push si
0349 push word ptr [bp - 4]
034c push word ptr [bp - 6]
034f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 850, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectPartialMixedOutline
0354 add sp, 0xc
0357 jmp 0xbb10
035a mov bx, word ptr [bp + 6]
035d mov al, byte ptr es:[bx + 0x28]
0361 cwde 
0362 mov si, ax
0364 and byte ptr [bp - 1], 0xfa
0368 or byte ptr [bp - 1], 0xa
036c jmp 0xba4c
036e mov di, word ptr [bp - 6]
0371 mov ax, word ptr [bp - 4]
0374 push ax
0375 push di
0376 mov si, ax
0378 nop 
0379 push cs
037a call 0xb54a ; _win_RectFill
037d add sp, 4
0380 mov ax, si
0382 les bx, ptr [bp + 6]
0385 mov cx, si
0387 mov al, byte ptr es:[bx + 0x28]
038b cwde 
038c mov si, ax
038e or byte ptr [bp - 1], 5
0392 and byte ptr [bp - 1], 0xf5
0396 push word ptr [0xcf4e] ; __foreColor
039a push word ptr [0xcf4e] ; __foreColor
039e mov al, byte ptr [bp - 1]
03a1 push ax
03a2 push si
03a3 push cx
03a4 push di
03a5 jmp 0xba5f
03a7 nop 
03a8 mov di, word ptr [bp - 6]
03ab mov ax, word ptr [bp - 4]
03ae push ax
03af push di
03b0 mov si, ax
03b2 nop 
03b3 push cs
03b4 call 0xb54a ; _win_RectFill
03b7 add sp, 4
03ba mov ax, si
03bc les bx, ptr [bp + 6]
03bf mov cx, si
03c1 mov al, byte ptr es:[bx + 0x28]
03c5 cwde 
03c6 mov si, ax
03c8 and byte ptr [bp - 1], 0xfa
03cc or byte ptr [bp - 1], 0xa
03d0 jmp 0xbaa6
03d2 mov ax, word ptr es:[bx + 0x24]
03d6 and ax, 0x180
03d9 shr ax, 7
03dc push ax
03dd les bx, ptr es:[bx + 0x2a]
03e1 push word ptr es:[bx + 2]
03e5 push word ptr es:[bx]
03e8 push word ptr [bp - 4]
03eb push word ptr [bp - 6]
03ee nop 
03ef push cs
03f0 call 0xb300 ; _gr_JustifyStrInRect
03f3 add sp, 0xa
03f6 push 0
03f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1019, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
03fd add sp, 2
0400 les bx, ptr [bp + 6]
0403 test byte ptr es:[bx + 0x24], 4
0408 je 0xbb31
040a mov al, byte ptr es:[bx + 0x21]
040e cwde 
040f dec ax
0410 je 0xbb27
0412 sub ax, 5
0415 jne 0xbb31
0417 push es
0418 push bx
0419 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1052, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
041e add sp, 4
0421 les bx, ptr [bp + 6]
0424 test byte ptr es:[bx + 0x25], 2
0429 je 0xbb40
042b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1070, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
0430 pop si
0431 pop di
0432 leave 
0433 retf 
```

## Known declaration examples

- `extern void far GRectFill(struct BitmapObject far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern void far GRectFill(void far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far GRectInv(struct WinRect far *rect);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far GRectOutline(int first, int second, int third);` — src/recovered/win_RectOutline.c
- `extern void far GRectPartialMixedOutline(int, int, int, char, int, int);` — src/recovered/win_RectHOutline.c
- `extern void far GRectPartialMixedOutline(int, int, int, char, int, int);` — src/recovered/win_RectVOutline.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far win_RectFill(struct WinRect far *rect);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_gr_JustifyStrInRect'], 'segment': 7, 'target_offset': 45824, 'caller_offsets': [1008]}
- {'callee_names': ['_win_RectFill'], 'segment': 7, 'target_offset': 46410, 'caller_offsets': [222, 890, 948]}
- {'callee_names': ['_win_DrawBitMapAtObj'], 'segment': 7, 'target_offset': 48688, 'caller_offsets': [421]}

## Neighbors

- {'symbol': '_win_RectHOutline', 'offset': 46810, 'source': 'src/recovered/win_RectHOutline.c', 'size': 40}
- {'symbol': '_win_DrawButtonBorder', 'offset': 46850, 'source': 'src/recovered/win_DrawButtonBorder.c', 'size': 13}
- {'symbol': '_win_DrawObject', 'offset': 47940, 'source': None, 'size': 32}
- {'symbol': '_win_DrawObjectNum', 'offset': 47972, 'source': 'src/recovered/win_DrawObjectNum.c', 'size': 47}

# Recovery task _win_DoProxMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 993 bytes.

```asm
0000 enter 0x2c, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 4], 0xffff
000b mov ax, word ptr [bp + 0xa]
000e mov word ptr [bp - 8], ax
0011 mov ax, word ptr [bp + 0xc]
0014 mov word ptr [bp - 6], ax
0017 cmp word ptr [bp + 8], -2
001b jne 0xde8a
001d mov word ptr [bp + 8], 0xffff
0022 mov di, word ptr [bp + 6]
0025 jmp 0xdf92
0028 push word ptr [0xcd78] ; _rootWnd
002c lea ax, [bp - 0x18]
002f push ss
0030 push ax
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 32}}]
0036 push word ptr [bp + 6]
0039 nop 
003a push cs
003b call 0xe3a8 ; _win_LockWin
003e add sp, 2
0041 mov bl, byte ptr [bp + 6]
0044 sub bh, bh
0046 shl bx, 2
0049 mov si, word ptr [bp + 6]
004c sar si, 8
004f shl si, 2
0052 les si, ptr [si - 0x3166]
0056 mov ax, word ptr es:[bx + si + 0x2c]
005a mov dx, word ptr es:[bx + si + 0x2e]
005e push ds
005f lea di, [bp - 0x10]
0062 mov si, ax
0064 push ss
0065 pop es
0066 mov ds, dx
0068 movsw word ptr es:[di], word ptr [si]
0069 movsw word ptr es:[di], word ptr [si]
006a movsw word ptr es:[di], word ptr [si]
006b movsw word ptr es:[di], word ptr [si]
006c pop ds
006d cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
0072 je 0xdedc
0074 inc word ptr [bp - 0xc]
0077 inc word ptr [bp - 0xa]
007a push word ptr [bp + 6]
007d nop 
007e push cs
007f call 0xe3a4 ; _win_UnlockWin
0082 add sp, 2
0085 push word ptr [0xcd78] ; _rootWnd
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 229}}]
008e mov si, ax
0090 or si, si
0092 jne 0xdefe
0094 xor cx, cx
0096 mov di, word ptr [bp + 6]
0099 jmp 0xdf35
009b nop 
009c mov di, word ptr [bp + 6]
009f push si
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
00a5 or ax, ax
00a7 jne 0xdf19
00a9 push si
00aa push 2
00ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
00b1 mov si, ax
00b3 or si, si
00b5 jne 0xdf01
00b7 or si, si
00b9 je 0xdf33
00bb push si
00bc push 4
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
00c3 or ax, ax
00c5 je 0xdf33
00c7 push si
00c8 push 4
00ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 203, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
00cf mov si, ax
00d1 mov cx, si
00d3 push cx
00d4 lea ax, [bp - 8]
00d7 push ss
00d8 push ax
00d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 28}}]
00de mov ax, word ptr [bp - 0xa]
00e1 sub ax, word ptr [bp - 0xe]
00e4 add ax, word ptr [bp - 6]
00e7 cmp ax, word ptr [bp - 0x12]
00ea jle 0xdf62
00ec mov ax, word ptr [bp - 0x16]
00ef mov cx, word ptr [bp - 0xe]
00f2 sub cx, word ptr [bp - 0xa]
00f5 add word ptr [bp - 6], cx
00f8 cmp word ptr [bp - 6], ax
00fb jge 0xdf62
00fd mov word ptr [bp - 6], ax
0100 mov ax, word ptr [bp - 0xc]
0103 sub ax, word ptr [bp - 0x10]
0106 add ax, word ptr [bp - 8]
0109 cmp ax, word ptr [bp - 0x14]
010c jle 0xdf84
010e mov ax, word ptr [bp - 0x18]
0111 mov cx, word ptr [bp - 0x10]
0114 sub cx, word ptr [bp - 0xc]
0117 add word ptr [bp - 8], cx
011a cmp word ptr [bp - 8], ax
011d jge 0xdf84
011f mov word ptr [bp - 8], ax
0122 push word ptr [0xcd78] ; _rootWnd
0126 lea ax, [bp - 8]
0129 push ss
012a push ax
012b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 300, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
0130 push word ptr [bp - 6]
0133 push word ptr [bp - 8]
0136 push di
0137 nop 
0138 push cs
0139 call 0xca2e ; _win_Open
013c add sp, 6
013f mov bx, di
0141 sar bx, 8
0144 mov word ptr [bp - 0x2c], bx
0147 shl bx, 1
0149 add bx, 0xbca6
014d mov word ptr [bp - 0x2a], bx
0150 push word ptr [bx]
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0157 add sp, 2
015a cmp word ptr [bp + 8], -1
015e je 0xdfc5
0160 jmp 0xe074
0163 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 358, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
0168 mov bx, word ptr [bp - 0x2a]
016b push word ptr [bx]
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0172 add sp, 2
0175 cmp word ptr [0xbe10], -1 ; _lastProxObj
017a je 0xe024
017c test byte ptr [0xbe10], 0xff ; _lastProxObj
0181 je 0xe024
0183 mov si, word ptr [0xbe10] ; _lastProxObj
0187 push si
0188 nop 
0189 push cs
018a call 0xe3a8 ; _win_LockWin
018d add sp, 2
0190 mov ax, si
0192 and si, 0xff
0196 mov bx, ax
0198 sar bx, 8
019b shl bx, 2
019e les bx, ptr [bx - 0x3166]
01a2 add bx, 0x2c
01a5 shl si, 2
01a8 push word ptr es:[bx + si + 2]
01ac push word ptr es:[bx + si]
01af mov si, ax
01b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 436, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
01b6 add sp, 4
01b9 push si
01ba nop 
01bb push cs
01bc call 0xe3a4 ; _win_UnlockWin
01bf add sp, 2
01c2 cmp di, -1
01c5 je 0xe068
01c7 mov ax, di
01c9 sub ah, ah
01cb or ax, ax
01cd je 0xe068
01cf push di
01d0 nop 
01d1 push cs
01d2 call 0xe3a8 ; _win_LockWin
01d5 add sp, 2
01d8 mov si, di
01da and si, 0xff
01de shl si, 2
01e1 mov bx, word ptr [bp - 0x2c]
01e4 shl bx, 2
01e7 les bx, ptr [bx - 0x3166]
01eb add bx, 0x2c
01ee push word ptr es:[bx + si + 2]
01f2 push word ptr es:[bx + si]
01f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 504, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
01fa add sp, 4
01fd push di
01fe nop 
01ff push cs
0200 call 0xe3a4 ; _win_UnlockWin
0203 add sp, 2
0206 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 521, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
020b mov word ptr [0xbe10], di ; _lastProxObj
020f jmp 0xe134
0212 mov si, word ptr [bp + 8]
0215 add si, di
0217 add si, 2
021a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 541, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
021f mov bx, si
0221 sar bx, 8
0224 shl bx, 1
0226 push word ptr [bx - 0x435a]
022a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 557, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
022f add sp, 2
0232 cmp word ptr [0xbe10], -1 ; _lastProxObj
0237 je 0xe0e5
0239 test byte ptr [0xbe10], 0xff ; _lastProxObj
023e je 0xe0e5
0240 mov ax, word ptr [0xbe10] ; _lastProxObj
0243 mov word ptr [bp - 2], ax
0246 push ax
0247 nop 
0248 push cs
0249 call 0xe3a8 ; _win_LockWin
024c add sp, 2
024f mov al, byte ptr [bp - 2]
0252 sub ah, ah
0254 shl ax, 2
0257 mov bx, word ptr [bp - 2]
025a sar bx, 8
025d shl bx, 2
0260 les bx, ptr [bx - 0x3166]
0264 add bx, 0x2c
0267 add bx, ax
0269 push word ptr es:[bx + 2]
026d push word ptr es:[bx]
0270 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 627, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
0275 add sp, 4
0278 push word ptr [bp - 2]
027b nop 
027c push cs
027d call 0xe3a4 ; _win_UnlockWin
0280 add sp, 2
0283 cmp si, -1
0286 je 0xe12b
0288 mov ax, si
028a sub ah, ah
028c or ax, ax
028e je 0xe12b
0290 push si
0291 nop 
0292 push cs
0293 call 0xe3a8 ; _win_LockWin
0296 add sp, 2
0299 mov ax, si
029b sub ah, ah
029d shl ax, 2
02a0 mov bx, si
02a2 sar bx, 8
02a5 shl bx, 2
02a8 les bx, ptr [bx - 0x3166]
02ac add bx, 0x2c
02af add bx, ax
02b1 push word ptr es:[bx + 2]
02b5 push word ptr es:[bx]
02b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 699, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
02bd add sp, 4
02c0 push si
02c1 nop 
02c2 push cs
02c3 call 0xe3a4 ; _win_UnlockWin
02c6 add sp, 2
02c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 716, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
02ce mov word ptr [0xbe10], si ; _lastProxObj
02d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 725, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
02d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 730, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldInit
02dc mov bx, word ptr [bp - 0x2a]
02df cmp word ptr [bx], 0
02e2 je 0xe156
02e4 push word ptr [bx]
02e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 743, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
02eb or ax, ax
02ed je 0xe156
02ef mov dx, 1
02f2 jmp 0xe158
02f4 xor dx, dx
02f6 or dx, dx
02f8 je 0xe1a4
02fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 765, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeld
02ff or ax, ax
0301 jne 0xe16e
0303 mov ax, word ptr [0xbe10] ; _lastProxObj
0306 mov word ptr [bp - 0x1c], ax
0309 jmp 0xe17f
030b nop 
030c lea ax, [bp - 0x28]
030f push ss
0310 push ax
0311 nop 
0312 push cs
0313 call 0xd150 ; _win_GetEvent
0316 add sp, 4
0319 or ax, ax
031b je 0xe13e
031d cmp word ptr [bp - 0x1c], di
0320 jb 0xe13e
0322 lea ax, [di + 0x100]
0326 cmp ax, word ptr [bp - 0x1c]
0329 jbe 0xe13e
032b mov ax, word ptr [bp + 6]
032e add ax, 2
0331 cmp ax, word ptr [bp - 0x1c]
0334 ja 0xe1a4
0336 mov ax, word ptr [bp - 0x1c]
0339 sub ax, word ptr [bp + 6]
033c sub ax, 2
033f mov word ptr [bp - 4], ax
0342 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 837, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
0347 mov bx, word ptr [bp - 0x2a]
034a cmp word ptr [bx], 0
034d jne 0xe1b4
034f jmp 0xe236
0352 mov bx, word ptr [bp - 0x2c]
0355 shl bx, 2
0358 les bx, ptr [bx - 0x3166]
035c and byte ptr es:[bx + 0x1d], 0xfd
0361 mov bx, word ptr [bp - 0x2a]
0364 push word ptr [bx]
0366 push 0
0368 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 873, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 42}}]
036d push word ptr [0xcd78] ; _rootWnd
0371 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 882, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 229}}]
0376 mov si, ax
0378 or si, si
037a jne 0xe1e2
037c xor di, di
037e jmp 0xe216
0380 push si
0381 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 898, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0386 or ax, ax
0388 jne 0xe1fa
038a push si
038b push 2
038d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 910, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
0392 mov si, ax
0394 or si, si
0396 jne 0xe1e2
0398 or si, si
039a je 0xe214
039c push si
039d push 4
039f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 928, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
03a4 or ax, ax
03a6 je 0xe214
03a8 push si
03a9 push 4
03ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 940, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
03b0 mov si, ax
03b2 mov di, si
03b4 or di, di
03b6 je 0xe236
03b8 push di
03b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 954, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
03be push di
03bf push 0x86
03c2 mov es, word ptr [0xc6d8]
03c6 push word ptr es:[0x34]
03cb push 0
03cd push 0
03cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 976, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 111}}]
03d4 mov word ptr [0xbe10], 0xffff ; _lastProxObj
03da mov ax, word ptr [bp - 4]
03dd pop si
03de pop di
03df leave 
03e0 retf 
```

## Known declaration examples

- `extern int far ButtonHeld(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far ButtonHeldInit(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far GRectInv(struct WinRect far *rect);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
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
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int far lastProxObj;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern unsigned int near lastProxObj;` — src/recovered/win_GetProxEvent.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far win_GetEvent(struct DialogEvent far *event);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_win_Open'], 'segment': 7, 'target_offset': 51758, 'caller_offsets': [313]}
- {'callee_names': ['_win_GetEvent'], 'segment': 7, 'target_offset': 53584, 'caller_offsets': [787]}
- {'callee_names': ['_win_UnlockWin'], 'segment': 7, 'target_offset': 58276, 'caller_offsets': [127, 444, 512, 637, 707]}
- {'callee_names': ['_win_LockWin'], 'segment': 7, 'target_offset': 58280, 'caller_offsets': [59, 394, 466, 585, 659]}

## Neighbors

- {'symbol': '__win_SetProxItem', 'offset': 56588, 'source': None, 'size': 197}
- {'symbol': 'INDIRECTDLGPROC', 'offset': 56786, 'source': 'src/recovered/wf_INDIRECTDLGPROC-3e701072c7.c', 'size': 143}
- {'symbol': '_win_InvalidateObject', 'offset': 57924, 'source': 'src/recovered/wf_win_InvalidateObject-69cbeedc5b.c', 'size': 113}
- {'symbol': '_win_IsPointInObj', 'offset': 58038, 'source': 'src/recovered/wf_win_IsPointInObj-538ab6cada.c', 'size': 108}

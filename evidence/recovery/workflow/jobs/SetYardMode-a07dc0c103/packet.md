# Recovery task _SetYardMode

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1009 bytes.

```asm
0000 enter 0x24, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 cmp si, 4
000c jne 0x9fb2
000e push word ptr [0xcc78] ; _OldMapPlane
0012 nop 
0013 push cs
0014 call 0xa5ca ; _SetMapPlane
0017 add sp, 2
001a jmp 0xa37c
001d nop 
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _AllocateMapBuffer
0023 mov es, word ptr [0xc0e6]
0027 push word ptr es:[0x19aa]
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 47, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0031 add sp, 2
0034 mov word ptr [bp - 4], ax
0037 mov word ptr [bp - 2], dx
003a or si, si
003c jne 0x9fd5
003e jmp 0xa1ac
0041 cmp si, 1
0044 jne 0x9fdd
0046 jmp 0xa1ac
0049 mov word ptr [0xce82], si ; _YardMode
004d push 0x1900
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
0055 add sp, 2
0058 push 0x1903
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjInvisible
0060 add sp, 2
0063 push 0x190f
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjInvisible
006b add sp, 2
006e push 0x1900
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
0076 add sp, 2
0079 push 0x1902
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelectable
0081 add sp, 2
0084 push 0
0086 push word ptr [bp - 2]
0089 push word ptr [bp - 4]
008c nop 
008d push cs
008e call 0x9420 ; _win_YardClosed
0091 add sp, 6
0094 test byte ptr [0xcc7e], 1 ; _displayType
0099 je 0xa05a
009b push 0x1914
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjInvisible
00a3 add sp, 2
00a6 push 0x1b5a
00a9 lea ax, [bp - 0x14]
00ac push ss
00ad push ax
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
00b3 add sp, 6
00b6 lea ax, [bp - 0xe]
00b9 push ss
00ba push ax
00bb lea ax, [bp - 0x10]
00be push ss
00bf push ax
00c0 push 0x1b5a
00c3 jmp 0xa185
00c6 push 0x1914
00c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjVisible
00ce add sp, 2
00d1 cmp byte ptr [0xcc7e], 0xa ; _displayType
00d6 jne 0xa06f
00d8 jmp 0xa168
00db cmp byte ptr [0xcc7e], 9 ; _displayType
00e0 jne 0xa079
00e2 jmp 0xa168
00e5 push 0x1b6c
00e8 lea ax, [bp - 0x14]
00eb push ss
00ec push ax
00ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 240, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
00f2 add sp, 6
00f5 mov si, word ptr [bp - 0x12]
00f8 push 0x1b6d
00fb lea ax, [bp - 0x14]
00fe push ss
00ff push ax
0100 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 259, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
0105 add sp, 6
0108 add si, word ptr [bp - 0x12]
010b push 0x1b6e
010e lea ax, [bp - 0x14]
0111 push ss
0112 push ax
0113 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 278, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
0118 add sp, 6
011b lea ax, [bp - 0xa]
011e push ss
011f push ax
0120 lea ax, [bp - 6]
0123 push ss
0124 push ax
0125 push 0x1b6e
0128 mov es, word ptr [0xc0e8]
012c mov cx, word ptr es:[0x807c]
0131 shl cx, 7
0134 push cx
0135 mov es, word ptr [0xc0ea]
0139 mov cx, word ptr es:[0x8096]
013e shl cx, 6
0141 add si, word ptr [bp - 0x12]
0144 cmp cx, si
0146 jle 0xa0de
0148 mov cx, si
014a push cx
014b push 0
014d push 0
014f push word ptr [bp - 2]
0152 push word ptr [bp - 4]
0155 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 344, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
015a add sp, 0x16
015d lea ax, [bp - 0xa]
0160 push ss
0161 push ax
0162 lea ax, [bp - 6]
0165 lea cx, [bp - 6]
0168 push ss
0169 push cx
016a push 0x1b6d
016d mov es, word ptr [0xc0e8]
0171 mov dx, word ptr es:[0x807c]
0176 shl dx, 7
0179 push dx
017a mov es, word ptr [0xc0ea]
017e mov dx, word ptr es:[0x8096]
0183 shl dx, 6
0186 cmp dx, si
0188 jle 0xa120
018a mov dx, si
018c push dx
018d mov di, word ptr [bp - 6]
0190 push di
0191 push 0
0193 push word ptr [bp - 2]
0196 push word ptr [bp - 4]
0199 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 412, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
019e add sp, 0x16
01a1 lea ax, [bp - 0xa]
01a4 push ss
01a5 push ax
01a6 lea ax, [bp - 6]
01a9 push ss
01aa push ax
01ab push 0x1b6c
01ae mov es, word ptr [0xc0e8]
01b2 mov cx, word ptr es:[0x807c]
01b7 shl cx, 7
01ba push cx
01bb mov es, word ptr [0xc0ea]
01bf mov cx, word ptr es:[0x8096]
01c4 shl cx, 6
01c7 cmp cx, si
01c9 jle 0xa161
01cb mov cx, si
01cd push cx
01ce add di, word ptr [bp - 6]
01d1 push di
01d2 jmp 0xa1a7
01d4 push 0x1b6c
01d7 lea ax, [bp - 0x14]
01da push ss
01db push ax
01dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 479, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
01e1 add sp, 6
01e4 lea ax, [bp - 0xa]
01e7 push ss
01e8 push ax
01e9 lea ax, [bp - 6]
01ec push ss
01ed push ax
01ee push 0x1b6c
01f1 mov es, word ptr [0xc0e8]
01f5 mov ax, word ptr es:[0x807c]
01f9 shl ax, 7
01fc push ax
01fd mov es, word ptr [0xc0ea]
0201 mov ax, word ptr es:[0x8096]
0205 shl ax, 6
0208 cmp ax, word ptr [bp - 0x12]
020b jle 0xa1a4
020d mov ax, word ptr [bp - 0x12]
0210 push ax
0211 push 0
0213 push 0
0215 jmp 0xa2b6
0218 mov word ptr [0xce82], si ; _YardMode
021c push 0x1900
021f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 546, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
0224 add sp, 2
0227 push 0x1903
022a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 557, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjInvisible
022f add sp, 2
0232 push 0x190f
0235 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 568, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjInvisible
023a add sp, 2
023d push 0x1902
0240 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 579, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelectable
0245 add sp, 2
0248 push 0x1914
024b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 590, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjInvisible
0250 add sp, 2
0253 push 0x1900
0256 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 601, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
025b add sp, 2
025e push 1
0260 push word ptr [bp - 2]
0263 push word ptr [bp - 4]
0266 nop 
0267 push cs
0268 call 0x9420 ; _win_YardClosed
026b add sp, 6
026e lea ax, [si + 0x1b58]
0272 push ax
0273 push 0x1903
0276 mov si, ax
0278 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 635, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjBitmap
027d add sp, 4
0280 push si
0281 lea ax, [bp - 0x14]
0284 push ss
0285 push ax
0286 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 649, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
028b add sp, 6
028e lea ax, [bp - 8]
0291 push ss
0292 push ax
0293 lea ax, [bp - 0xc]
0296 push ss
0297 push ax
0298 push si
0299 mov bx, 0x807c
029c mov es, word ptr [0xc0e8]
02a0 mov word ptr [bp - 0x20], bx
02a3 mov word ptr [bp - 0x1e], es
02a6 mov ax, word ptr es:[bx]
02a9 shl ax, 7
02ac push ax
02ad mov bx, 0x8096
02b0 mov es, word ptr [0xc0ea]
02b4 mov word ptr [bp - 0x24], bx
02b7 mov word ptr [bp - 0x22], es
02ba mov ax, word ptr es:[bx]
02bd shl ax, 6
02c0 cmp ax, word ptr [bp - 0x12]
02c3 jle 0xa25c
02c5 mov ax, word ptr [bp - 0x12]
02c8 push ax
02c9 push 0
02cb push 0
02cd push word ptr [bp - 2]
02d0 push word ptr [bp - 4]
02d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 726, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
02d8 add sp, 0x16
02db cmp byte ptr [0xcc7e], 0xa ; _displayType
02e0 jne 0xa286
02e2 lea ax, [bp - 8]
02e5 push ss
02e6 push ax
02e7 lea cx, [bp - 0xc]
02ea push ss
02eb push cx
02ec push 0x1b5a
02ef jmp 0xa293
02f1 nop 
02f2 lea ax, [bp - 8]
02f5 push ss
02f6 push ax
02f7 lea cx, [bp - 0xc]
02fa push ss
02fb push cx
02fc push 0x1b5b
02ff les bx, ptr [bp - 0x20]
0302 mov cx, word ptr es:[bx]
0305 shl cx, 7
0308 push cx
0309 les bx, ptr [bp - 0x24]
030c mov cx, word ptr es:[bx]
030f shl cx, 6
0312 cmp cx, word ptr [bp - 0x12]
0315 jle 0xa2ae
0317 mov cx, word ptr [bp - 0x12]
031a push cx
031b push 0
031d mov cx, word ptr [bp - 8]
0320 dec cx
0321 push cx
0322 push word ptr [bp - 2]
0325 push word ptr [bp - 4]
0328 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 811, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
032d add sp, 0x16
0330 mov es, word ptr [0xc0e6]
0334 push word ptr es:[0x19aa]
0339 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 828, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
033e add sp, 2
0341 push 0x1900
0344 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 839, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0349 add sp, 2
034c or ax, ax
034e jne 0xa301
0350 push 0x100
0353 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 854, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0358 add sp, 2
035b or ax, ax
035d je 0xa301
035f push 0x1900
0362 push 0x100
0365 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 872, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Swap
036a add sp, 4
036d lea ax, [bp - 0x1c]
0370 push ss
0371 push ax
0372 push 0x1903
0375 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 888, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
037a add sp, 6
037d mov ax, word ptr [bp - 0x1c]
0380 add ah, 2
0383 mov word ptr [bp - 0x18], ax
0386 mov ax, word ptr [bp - 0x1a]
0389 add ax, 0xe2
038c mov word ptr [bp - 0x16], ax
038f push word ptr [0xbcd8]
0393 lea ax, [bp - 0x1c]
0396 push ss
0397 push ax
0398 push 0
039a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 923, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
039f push word ptr [0xbcd8]
03a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 932, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
03a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 939, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
03ad push 0x1900
03b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 947, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
03b5 add sp, 2
03b8 cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
03bd je 0xa360
03bf mov bx, word ptr [0xce82] ; _YardMode
03c3 shl bx, 1
03c5 push word ptr [bx + 0x1586]
03c9 jmp 0xa36a
03cb nop 
03cc mov bx, word ptr [0xce82] ; _YardMode
03d0 shl bx, 1
03d2 push word ptr [bx + 0x158e]
03d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 985, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
03db add sp, 2
03de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 993, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
03e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 998, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawYard
03e8 nop 
03e9 push cs
03ea call 0x953c ; _SetMapTitle
03ed pop si
03ee pop di
03ef leave 
03f0 retf 
```

## Known declaration examples

- `extern int near OldMapPlane;` — src/recovered/wf_tu_simant_9D04_SetMapPlane_1_scaffold-47a07d4d6a.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far SetMapTitle(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapTitle(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetMapTitle(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far clip_Pop(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_Push(void);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_initControls_1_scaffold-03091459d8.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near ribbonBarWnd;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_MakeObjInvisible(int object);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far win_MakeObjSelected(int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far win_MakeObjSelected(int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far win_Swap(int first, int second);` — src/recovered/wf_YardToMap-2e5b0deea5.c
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

- {'callee_names': ['_win_YardClosed'], 'segment': 1, 'target_offset': 37920, 'caller_offsets': [142, 616]}
- {'callee_names': ['_SetMapTitle'], 'segment': 1, 'target_offset': 38204, 'caller_offsets': [1002]}
- {'callee_names': ['_SetMapPlane'], 'segment': 1, 'target_offset': 42442, 'caller_offsets': [20]}

## Neighbors

- {'symbol': '_SetEditMode', 'offset': 40562, 'source': 'src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c', 'size': 16}
- {'symbol': '_SetMapModeAnt', 'offset': 40578, 'source': 'src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c', 'size': 274}
- {'symbol': '_SetMapPlaneLocation', 'offset': 41862, 'source': None, 'size': 419}
- {'symbol': '_GotoMapPoint', 'offset': 42282, 'source': 'src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c', 'size': 160}

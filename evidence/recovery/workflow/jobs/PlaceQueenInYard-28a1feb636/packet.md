# Recovery task _PlaceQueenInYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 937 bytes.

```asm
0000 enter 0x2a, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 0xa], 0xffff
000b cmp word ptr [0xac8c], 1 ; _QueenStorageB
0010 jge 0xad7c
0012 push 0x7e
0014 push 0
0016 push 1
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
001d add sp, 6
0020 mov es, word ptr [0xc102]
0024 cmp word ptr es:[0x80b4], 2
002a je 0xad62
002c push 1
002e push 0
0030 push 0xb4
0033 mov es, word ptr [0xc112]
0037 les bx, ptr es:[0x737a]
003c push word ptr es:[bx + 0x42]
0040 push word ptr es:[bx + 0x40]
0044 nop 
0045 push cs
0046 call 0x92c0 ; _EditMessage
0049 add sp, 0xa
004c pop si
004d pop di
004e leave 
004f retf 
0050 push 1
0052 push 0
0054 push 0xb4
0057 mov es, word ptr [0xc112]
005b les bx, ptr es:[0x737a]
0060 push word ptr es:[bx + 0x1e]
0064 push word ptr es:[bx + 0x1c]
0068 jmp 0xad56
006a mov <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
006d mov es, ax
006f cmp word ptr es:[0x836e], 1
0075 jne 0xad90
0077 mov word ptr es:[0x836e], 0
007e mov <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0081 mov es, ax
0083 mov ax, word ptr es:[0x7a60]
0087 add ax, 3
008a mov word ptr [bp - 0x12], ax
008d mov ax, word ptr es:[0x7a62]
0091 sub ax, 3
0094 mov word ptr [bp - 0x14], ax
0097 mov ax, word ptr es:[0x7a62]
009b add ax, 3
009e mov word ptr [bp - 0x10], ax
00a1 mov ax, word ptr es:[0x7a60]
00a5 sub ax, 3
00a8 mov word ptr [bp - 0x16], ax
00ab or ax, ax
00ad jge 0xadc8
00af mov word ptr [bp - 0x16], 0
00b4 jmp 0xadd2
00b6 cmp ax, 0xb
00b9 jle 0xadd2
00bb mov word ptr [bp - 0x16], 0xb
00c0 cmp word ptr [bp - 0x12], 0
00c4 jge 0xade0
00c6 mov word ptr [bp - 0x12], 0
00cb jmp 0xadeb
00cd nop 
00ce cmp word ptr [bp - 0x12], 0xb
00d2 jle 0xadeb
00d4 mov word ptr [bp - 0x12], 0xb
00d9 cmp word ptr [bp - 0x14], 0
00dd jge 0xadf8
00df mov word ptr [bp - 0x14], 0
00e4 jmp 0xae03
00e6 cmp word ptr [bp - 0x14], 0xf
00ea jle 0xae03
00ec mov word ptr [bp - 0x14], 0xf
00f1 cmp word ptr [bp - 0x10], 0
00f5 jge 0xae10
00f7 mov word ptr [bp - 0x10], 0
00fc jmp 0xae1b
00fe cmp word ptr [bp - 0x10], 0xf
0102 jle 0xae1b
0104 mov word ptr [bp - 0x10], 0xf
0109 nop 
010a push cs
010b call 0x10000
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
0113 mov ax, 0x737a
0116 mov <resolved loader operand; see bindings> ; [{'operand_offset': 279, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0119 mov word ptr [bp - 0x2a], ax
011c mov word ptr [bp - 0x28], cx
011f push 1
0121 push -1
0123 push -2
0125 les bx, ptr [bp - 0x2a]
0128 les bx, ptr es:[bx]
012b push word ptr es:[bx + 0x22]
012f push word ptr es:[bx + 0x20]
0133 nop 
0134 push cs
0135 call 0x92c0 ; _EditMessage
0138 add sp, 0xa
013b mov ax, 0xffff
013e mov word ptr [bp - 2], ax
0141 mov word ptr [bp - 4], ax
0144 mov word ptr [bp - 6], 0
0149 lea ax, [bp - 0x26]
014c push ss
014d push ax
014e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
0153 add sp, 4
0156 or ax, ax
0158 je 0xae86
015a cmp word ptr [bp - 0x1a], 0x1902
015f jne 0xae86
0161 mov ax, word ptr [bp - 0x1e]
0164 mov dx, word ptr [bp - 0x1c]
0167 mov word ptr [bp - 0xe], ax
016a mov word ptr [bp - 0xc], dx
016d mov word ptr [bp - 6], 1
0172 jmp 0xaea1
0174 lea ax, [bp - 0xe]
0177 push ss
0178 push ax
0179 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 380, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GetMousePos
017e add sp, 4
0181 push word ptr [0xbcd8]
0185 lea ax, [bp - 0xe]
0188 push ss
0189 push ax
018a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 395, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
018f push 0x1900
0192 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 405, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0197 add sp, 2
019a or ax, ax
019c jne 0xaeb3
019e jmp 0xb0a0
01a1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 418, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01a4 mov es, ax
01a6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 10}}]
01a9 mov ds, ax
01ab mov ax, word ptr [bp - 0xc]
01ae sub ax, word ptr es:[0x8112]
01b3 sub ax, word ptr [0x1896]
01b7 mov cx, 0xa
01ba cdq 
01bb idiv cx
01bd mov si, ax
01bf mov dx, ax
01c1 shl ax, 2
01c4 add ax, dx
01c6 shl ax, 1
01c8 sub ax, word ptr es:[0x8110]
01cd sub ax, word ptr [0x1894] ; _patchRgn
01d1 add ax, word ptr [bp - 0xe]
01d4 mov dx, 0x1c
01d7 mov bx, dx
01d9 cdq 
01da idiv bx
01dc mov di, ax
01de cmp di, word ptr [bp - 2]
01e1 jne 0xaefd
01e3 cmp word ptr [bp - 4], si
01e6 jne 0xaefd
01e8 jmp 0xb040
01eb mov word ptr [bp - 2], di
01ee mov word ptr [bp - 4], si
01f1 cmp word ptr [bp - 0xa], -1
01f5 jne 0xaf0c
01f7 jmp 0xb046
01fa push ss
01fb pop ds
01fc push word ptr [0xbcd8]
0200 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 515, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0205 add sp, 2
0208 push word ptr [bp - 8]
020b push word ptr [bp - 0xa]
020e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 529, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvertPatch
0213 add sp, 4
0216 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 537, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
021b mov word ptr [bp - 0xa], 0xffff
0220 cmp word ptr [bp - 0x16], di
0223 jg 0xaf87
0225 cmp word ptr [bp - 0x12], di
0228 jl 0xaf87
022a cmp word ptr [bp - 0x14], si
022d jg 0xaf87
022f cmp word ptr [bp - 0x10], si
0232 jl 0xaf87
0234 mov es, word ptr [0xc0f2]
0238 cmp word ptr es:[0x7a60], di
023d jne 0xaf58
023f cmp word ptr es:[0x7a62], si
0244 je 0xaf79
0246 push word ptr [0xbcd8]
024a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 589, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
024f add sp, 2
0252 push si
0253 push di
0254 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 599, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvertPatch
0259 add sp, 4
025c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 607, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0261 mov word ptr [bp - 0xa], di
0264 mov word ptr [bp - 8], si
0267 mov es, word ptr [0xc0f4]
026b mov word ptr es:[0x789e], di
0270 mov word ptr es:[0x78a0], si
0275 cmp word ptr [bp - 6], 0
0279 jne 0xaf90
027b jmp 0xae5b
027e cmp word ptr [bp - 0xa], -1
0282 je 0xafba
0284 push word ptr [0xbcd8]
0288 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 651, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
028d add sp, 2
0290 push word ptr [bp - 8]
0293 push word ptr [bp - 0xa]
0296 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 665, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvertPatch
029b add sp, 4
029e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 673, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
02a3 mov word ptr [bp - 0xa], 0xffff
02a8 cmp word ptr [bp - 0x16], di
02ab jle 0xafc2
02ad jmp 0xb04c
02b0 cmp word ptr [bp - 0x12], di
02b3 jge 0xafca
02b5 jmp 0xb04c
02b8 cmp word ptr [bp - 0x14], si
02bb jg 0xb04c
02bd cmp word ptr [bp - 0x10], si
02c0 jl 0xb04c
02c2 push 0x7e
02c4 push 0x2afb
02c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 714, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
02cc add sp, 4
02cf dec word ptr [0xac8c] ; _QueenStorageB
02d3 mov es, word ptr [0xc106]
02d7 shl di, 4
02da add di, si
02dc inc byte ptr es:[di + 0xa4]
02e1 mov es, word ptr [0xc114]
02e5 inc word ptr es:[0x80d4]
02ea mov ax, 1
02ed mov es, word ptr [0xc116]
02f1 mov word ptr es:[0x8a68], ax
02f5 push ax
02f6 nop 
02f7 push cs
02f8 call 0x96c8 ; _MakeDMap
02fb add sp, 2
02fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 769, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
0303 push 1
0305 push 0
0307 push 0x78
0309 les bx, ptr [bp - 0x2a]
030c les bx, ptr es:[bx]
030f push word ptr es:[bx + 0x26]
0313 push word ptr es:[bx + 0x24]
0317 nop 
0318 push cs
0319 call 0x92c0 ; _EditMessage
031c add sp, 0xa
031f cmp word ptr [0xac8c], 0 ; _QueenStorageB
0324 jle 0xb0b2
0326 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 809, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateYard
032b jmp 0xb08e
032d nop 
032e push ss
032f pop ds
0330 jmp 0xaf87
0333 nop 
0334 push ss
0335 pop ds
0336 jmp 0xaf32
0339 nop 
033a push 1
033c push 0
033e push 0x78
0340 les bx, ptr [bp - 0x2a]
0343 les bx, ptr es:[bx]
0346 push word ptr es:[bx + 0x2a]
034a push word ptr es:[bx + 0x28]
034e nop 
034f push cs
0350 call 0x92c0 ; _EditMessage
0353 add sp, 0xa
0356 push 0x7e
0358 push 0
035a push 1
035c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 863, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0361 add sp, 6
0364 push 0x10
0366 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 871, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
036b test ah, 0x80
036e je 0xb08e
0370 push 0
0372 push 0x1e
0374 nop 
0375 push cs
0376 call 0x9620 ; _myDelay
0379 add sp, 4
037c push 0x10
037e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 895, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0383 test ah, 0x80
0386 je 0xb09d
0388 jmp 0xae31
038b jmp 0xb0b2
038d nop 
038e push 1
0390 push -1
0392 push -2
0394 push 0
0396 push 0
0398 nop 
0399 push cs
039a call 0x92c0 ; _EditMessage
039d add sp, 0xa
03a0 nop 
03a1 push cs
03a2 call 0x10034
03a5 pop si
03a6 pop di
03a7 leave 
03a8 retf 
```

## Known declaration examples

- `extern void far DrawMap(void);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far GetMousePos(struct CursorPoint far *point);` — src/recovered/win_IsCursorInObj.c
- `extern void far InvertPatch(int x, int y);` — src/recovered/wf_tu_antedit_A998_DrawYardCursor_3_scaffold-c71c8e4e09.c
- `extern void far InvertPatch(int x, int y);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MakeDMap(int mode);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far myDelay(unsigned long ticks);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern struct Point near patchRgn;` — src/recovered/wf_tu_antedit_A998_DrawYardCursor_3_scaffold-c71c8e4e09.c
- `extern struct Point near patchRgn;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far patchRgn;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_GetEvent(struct DialogEvent far *event);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GotoRQueen', 'offset': 43908, 'source': 'src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c', 'size': 12}
- {'symbol': '_XferPatch', 'offset': 43920, 'source': None, 'size': 385}
- {'symbol': '_MysteryButton', 'offset': 45244, 'source': None, 'size': 616}
- {'symbol': '_InitTriVars', 'offset': 45860, 'source': 'src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c', 'size': 152}

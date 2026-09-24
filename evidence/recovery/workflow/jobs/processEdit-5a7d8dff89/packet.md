# Recovery task _processEdit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1168 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov es, word ptr [bp + 8]
000c mov ax, word ptr es:[di + 6]
0010 mov cx, ax
0012 and ax, 0x6000
0015 cmp ax, 1
0018 sbb ax, ax
001a inc ax
001b mov word ptr [bp - 8], ax
001e push cx
001f push ds
0020 push 0x974
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0028 add sp, 6
002b cmp word ptr [bp - 8], 0
002f jne 0x6a99
0031 push 0
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0038 add sp, 2
003b or ax, ax
003d je 0x6a99
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0044 add ax, 6
0047 adc dx, 0
004a mov word ptr [bp - 4], ax
004d mov word ptr [bp - 2], dx
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0055 cmp dx, word ptr [bp - 2]
0058 jl 0x6a88
005a jg 0x6a99
005c cmp ax, word ptr [bp - 4]
005f jb 0x6a88
0061 les bx, ptr [bp + 6]
0064 mov ax, word ptr es:[bx + 8]
0068 mov es, word ptr [0xbf06]
006c sub ax, word ptr es:[0x9b08]
0071 cdq 
0072 idiv word ptr [0x143a] ; _tileWidth
0076 mov si, ax
0078 mov es, word ptr [0xbf08]
007c add si, word ptr es:[0x7d2e]
0081 mov es, word ptr [bp + 8]
0084 mov ax, word ptr es:[bx + 0xa]
0088 mov es, word ptr [0xbf06]
008c sub ax, word ptr es:[0x9b0a]
0091 cdq 
0092 idiv word ptr [0x143c] ; _tileHeight
0096 mov di, ax
0098 mov es, word ptr [0xbf08]
009c add di, word ptr es:[0x7d30]
00a1 mov es, word ptr [0xbf0a]
00a5 cmp word ptr es:[0x80b4], 3
00ab jne 0x6af2
00ad push word ptr [bp - 8]
00b0 push di
00b1 push si
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _processExp
00b7 jmp 0x6ec1
00ba mov <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00bd mov ds, ax
00bf cmp word ptr [0x9c24], 0
00c4 je 0x6b04
00c6 mov word ptr [0x9c24], 0
00cc mov <resolved loader operand; see bindings> ; [{'operand_offset': 205, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00cf mov es, ax
00d1 mov ax, word ptr es:[0x7c22]
00d5 inc ax
00d6 je 0x6b24
00d8 sub ax, 0xb
00db jne 0x6b18
00dd jmp 0x6e6e
00e0 dec ax
00e1 jne 0x6b1e
00e3 jmp 0x6e9c
00e6 push ss
00e7 pop ds
00e8 pop si
00e9 pop di
00ea leave 
00eb retf 
00ec cmp word ptr [bp - 8], 0
00f0 je 0x6b2d
00f2 jmp 0x6bbc
00f5 push ss
00f6 pop ds
00f7 push di
00f8 push si
00f9 push word ptr [0xce80] ; _MePlane
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItYellow
0102 add sp, 6
0105 dec ax
0106 jne 0x6b86
0108 nop 
0109 push cs
010a call 0x96a6 ; _myButton
010d dec ax
010e jne 0x6b66
0110 push 0x10
0112 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0117 test ah, 0x80
011a jne 0x6b66
011c push word ptr [bp + 8]
011f push word ptr [bp + 6]
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _AntMenu
0127 add sp, 4
012a pop si
012b pop di
012c leave 
012d retf 
012e push di
012f push si
0130 push word ptr [0xce80] ; _MePlane
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetLife
0139 add sp, 6
013c cmp ax, 0xfe
013f jne 0x6b7c
0141 jmp 0x6ec4
0144 nop 
0145 push cs
0146 call 0xa6e0 ; _CenterAnt
0149 pop si
014a pop di
014b leave 
014c retf 
014d nop 
014e mov word ptr [bp - 6], si
0151 nop 
0152 push cs
0153 call 0x96a6 ; _myButton
0156 dec ax
0157 je 0x6b94
0159 jmp 0x6ce4
015c push 0x10
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0163 test ah, 0x80
0166 je 0x6ba3
0168 jmp 0x6ce4
016b push word ptr [0xcc76] ; _MapPlane
016f push di
0170 push si
0171 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 372, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _MagnifyMenu
0176 add sp, 6
0179 or ax, ax
017b jge 0x6bb8
017d jmp 0x6ce4
0180 pop si
0181 pop di
0182 leave 
0183 retf 
0184 mov word ptr [bp - 6], si
0187 push ss
0188 pop ds
0189 mov es, word ptr [0xbf0c]
018d cmp word ptr es:[0x9fe8], 0
0193 je 0x6bd0
0195 jmp 0x6ce4
0198 push di
0199 push si
019a push word ptr [0xcc76] ; _MapPlane
019e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 417, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetLife
01a3 add sp, 6
01a6 mov si, ax
01a8 or si, si
01aa jge 0x6be7
01ac jmp 0x6ce4
01af and al, 0x7f
01b1 cmp al, 8
01b3 jge 0x6bf0
01b5 jmp 0x6ce4
01b8 push si
01b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 444, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
01be add sp, 2
01c1 or ax, ax
01c3 je 0x6c00
01c5 jmp 0x6ce4
01c8 push si
01c9 push di
01ca push word ptr [bp - 6]
01cd push word ptr [0xcc76] ; _MapPlane
01d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindAntIndex
01d6 add sp, 8
01d9 mov es, word ptr [0xbf0e]
01dd mov word ptr es:[0x99e4], ax
01e1 or ax, ax
01e3 jge 0x6c20
01e5 jmp 0x6ec4
01e8 mov al, byte ptr [0xce98] ; _MeColor
01eb mov cx, si
01ed xor al, cl
01ef and ax, 0x80
01f2 cmp ax, 1
01f5 sbb ax, ax
01f7 and ax, 1
01fa add ax, 3
01fd mov es, word ptr [0xbf10]
0201 mov word ptr es:[0x9bc4], ax
0205 mov es, word ptr [0xbf12]
0209 mov word ptr es:[0x72ee], si
020e cmp word ptr [0xcc76], 0 ; _MapPlane
0213 jne 0x6c5a
0215 mov es, word ptr [0xbf14]
0219 mov word ptr es:[0x9c6c], 1
0220 jmp 0x6c65
0222 mov ax, word ptr [0xcc76] ; _MapPlane
0225 mov es, word ptr [0xbf14]
0229 mov word ptr es:[0x9c6c], ax
022d mov ax, word ptr [bp - 6]
0230 mov es, word ptr [0xbf16]
0234 mov word ptr es:[0x99e8], ax
0238 mov es, word ptr [0xbf18]
023c mov word ptr es:[0x99ea], di
0241 mov bx, ax
0243 mov ax, word ptr [0xcc76] ; _MapPlane
0246 mov word ptr [bp - 2], ax
0249 or ax, ax
024b jne 0x6c8a
024d mov ax, 1
0250 jmp 0x6c8d
0252 mov ax, word ptr [bp - 2]
0255 mov es, word ptr [0xbf1a]
0259 mov word ptr es:[0x9be0], ax
025d mov es, word ptr [0xbf1c]
0261 mov word ptr es:[0x80c6], bx
0266 mov es, word ptr [0xbf1e]
026a mov word ptr es:[0x80d2], di
026f mov es, word ptr [0xbf20]
0273 mov word ptr es:[0x72e4], 0xfffe
027a cmp word ptr [bp - 2], 2
027e jl 0x6cd5
0280 cmp di, 2
0283 jge 0x6cd5
0285 or bx, bx
0287 jg 0x6cc4
0289 jmp 0x6e62
028c cmp bx, 0x3f
028f jl 0x6ccc
0291 mov bx, 0x3e
0294 mov es, word ptr [0xbf1c]
0298 mov word ptr es:[0x80c6], bx
029d mov es, word ptr [0xbf22]
02a1 mov word ptr es:[0x7d24], 1
02a8 pop si
02a9 pop di
02aa leave 
02ab retf 
02ac mov word ptr [bp - 4], di
02af mov si, di
02b1 cmp word ptr [0xcc76], 1 ; _MapPlane
02b6 jle 0x6cf3
02b8 jmp 0x6d82
02bb mov es, word ptr [0xbf0c]
02bf cmp word ptr es:[0x9fe8], 1
02c5 jne 0x6d0a
02c7 push word ptr [bp - 8]
02ca push si
02cb push word ptr [bp - 6]
02ce jmp 0x6ebc
02d1 nop 
02d2 mov ax, word ptr [bp - 8]
02d5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 726, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
02d8 mov es, cx
02da mov word ptr es:[0x9bc4], ax
02de mov cx, word ptr [bp - 6]
02e1 mov bx, word ptr ss:[0xcc76]
02e6 or bx, bx
02e8 jne 0x6d28
02ea mov ax, 1
02ed jmp 0x6d2a
02ef nop 
02f0 mov ax, bx
02f2 mov <resolved loader operand; see bindings> ; [{'operand_offset': 755, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
02f5 mov es, dx
02f7 mov word ptr es:[0x9be0], ax
02fb mov <resolved loader operand; see bindings> ; [{'operand_offset': 764, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
02fe mov ds, ax
0300 mov word ptr [0x80c6], cx
0304 mov <resolved loader operand; see bindings> ; [{'operand_offset': 773, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0307 mov es, ax
0309 mov word ptr es:[0x80d2], si
030e mov <resolved loader operand; see bindings> ; [{'operand_offset': 783, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0311 mov es, ax
0313 mov word ptr es:[0x72e4], 0xfffe
031a cmp bx, 2
031d jl 0x6d72
031f cmp si, 2
0322 jge 0x6d72
0324 or cx, cx
0326 jg 0x6d66
0328 mov cx, 1
032b jmp 0x6d6e
032d nop 
032e cmp cx, 0x3f
0331 jl 0x6d6e
0333 mov cx, 0x3e
0336 mov word ptr [0x80c6], cx
033a mov <resolved loader operand; see bindings> ; [{'operand_offset': 827, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
033d mov es, ax
033f mov word ptr es:[0x7d24], 1
0346 jmp 0x6b1e
0349 nop 
034a mov es, word ptr [0xbf0c]
034e cmp word ptr es:[0x9fe8], 0
0354 je 0x6d91
0356 jmp 0x6ec4
0359 cmp word ptr [bp - 8], 1
035d jne 0x6e08
035f mov si, word ptr [bp - 6]
0362 push di
0363 push si
0364 push word ptr [0xcc76] ; _MapPlane
0368 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 875, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDigable
036d add sp, 6
0370 dec ax
0371 je 0x6ded
0373 cmp word ptr [0xce80], 2 ; _MePlane
0378 jl 0x6dd4
037a or di, di
037c jg 0x6dd4
037e push di
037f push si
0380 push word ptr [0xcc76] ; _MapPlane
0384 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 903, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0389 add sp, 6
038c push ax
038d push word ptr [0xcc76] ; _MapPlane
0391 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 916, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsThisGrass
0396 add sp, 4
0399 dec ax
039a je 0x6ded
039c test byte ptr [0xcc84], 8 ; _MeType
03a1 jne 0x6dfa
03a3 push di
03a4 push si
03a5 push word ptr [0xcc76] ; _MapPlane
03a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 940, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsLiftable
03ae add sp, 6
03b1 or ax, ax
03b3 jne 0x6dfa
03b5 mov es, word ptr [0xbf10]
03b9 mov word ptr es:[0x9bc4], 2
03c0 jmp 0x6e16
03c2 mov es, word ptr [0xbf10]
03c6 mov word ptr es:[0x9bc4], 1
03cd jmp 0x6e16
03cf nop 
03d0 mov si, word ptr [bp - 6]
03d3 mov es, word ptr [0xbf10]
03d7 mov word ptr es:[0x9bc4], 0
03de mov word ptr [bp - 2], si
03e1 mov cx, word ptr [0xcc76] ; _MapPlane
03e5 or cx, cx
03e7 jne 0x6e26
03e9 mov ax, 1
03ec jmp 0x6e28
03ee mov ax, cx
03f0 mov es, word ptr [0xbf1a]
03f4 mov word ptr es:[0x9be0], ax
03f8 mov ax, si
03fa mov es, word ptr [0xbf1c]
03fe mov word ptr es:[0x80c6], ax
0402 mov es, word ptr [0xbf1e]
0406 mov word ptr es:[0x80d2], di
040b mov es, word ptr [0xbf20]
040f mov word ptr es:[0x72e4], 0xfffe
0416 cmp cx, 2
0419 jge 0x6e56
041b jmp 0x6cd5
041e cmp di, 2
0421 jl 0x6e5e
0423 jmp 0x6cd5
0426 or ax, ax
0428 jg 0x6e68
042a mov bx, 1
042d jmp 0x6ccc
0430 mov bx, ax
0432 jmp 0x6cc4
0435 nop 
0436 mov word ptr [bp - 4], di
0439 mov word ptr [bp - 6], si
043c push ss
043d pop ds
043e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1089, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0443 cmp word ptr [0xcc76], 0 ; _MapPlane
0448 jne 0x6e8a
044a mov word ptr [bp - 2], 1
044f jmp 0x6e90
0451 nop 
0452 mov ax, word ptr [0xcc76] ; _MapPlane
0455 mov word ptr [bp - 2], ax
0458 push di
0459 push si
045a push word ptr [bp - 2]
045d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1120, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ExchangeLives
0462 jmp 0x6ec1
0464 mov word ptr [bp - 4], di
0467 mov word ptr [bp - 6], si
046a push ss
046b pop ds
046c cmp word ptr [0xcc76], 1 ; _MapPlane
0471 jg 0x6ec4
0473 mov es, word ptr [0xbf0c]
0477 cmp word ptr es:[0x9fe8], 1
047d jne 0x6ec4
047f push word ptr [bp - 8]
0482 push di
0483 push si
0484 nop 
0485 push cs
0486 call 0x7198 ; _processSpider
0489 add sp, 6
048c pop si
048d pop di
048e leave 
048f retf 
```

## Known declaration examples

- `extern int far FindAntIndex(int list, int life, int column, int attribute);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far GetLife(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern void far MagnifyMenu(int x, int y, int plane);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern int near tileHeight;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_processSpider'], 'segment': 1, 'target_offset': 29080, 'caller_offsets': [1158]}
- {'callee_names': ['_myButton'], 'segment': 1, 'target_offset': 38566, 'caller_offsets': [266, 339]}
- {'callee_names': ['_CenterAnt'], 'segment': 1, 'target_offset': 42720, 'caller_offsets': [326]}

## Neighbors

- {'symbol': '_SpiderDialog', 'offset': 26426, 'source': None, 'size': 537}
- {'symbol': '_CustomerIDDialog', 'offset': 26964, 'source': None, 'size': 227}
- {'symbol': '_DoLaserFire', 'offset': 28360, 'source': None, 'size': 719}
- {'symbol': '_processSpider', 'offset': 29080, 'source': 'src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c', 'size': 290}

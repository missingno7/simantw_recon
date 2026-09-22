# Recovery task _ProcYardEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 432 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 mov es, word ptr [bp + 8]
000a mov ax, word ptr es:[si + 0xc]
000e sub ax, 0x1902
0011 cmp ax, 0xf
0014 jbe 0xa537
0016 jmp 0xa6cb
0019 shl ax, 1
001b xchg bx, ax
001c jmp word ptr cs:[bx - 0x5ac0]
0021 nop 
0022 dw offset 0xa560
0024 dw offset 0xa6cb
0026 dw offset 0xa6cb
0028 dw offset 0xa6cb
002a dw offset 0xa6cb
002c dw offset 0xa570
002e dw offset 0xa578
0030 dw offset 0xa58c
0032 dw offset 0xa590
0034 dw offset 0xa59a
0036 dw offset 0xa6cb
0038 dw offset 0xa642
003a dw offset 0xa656
003c dw offset 0xa6cb
003e dw offset 0xa664
0040 dw offset 0xa6c0
0042 mov ax, es
0044 push ax
0045 push si
0046 nop 
0047 push cs
0048 call 0xc09a ; _YardArea
004b add sp, 4
004e pop si
004f leave 
0050 retf 
0051 nop 
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YardToMap
0057 pop si
0058 leave 
0059 retf 
005a cmp word ptr [0xce82], 2 ; _YardMode
005f jge 0xa588
0061 mov ax, word ptr [0xce82] ; _YardMode
0064 xor al, 1
0066 push ax
0067 jmp 0xa592
0069 nop 
006a push 0
006c jmp 0xa592
006e push 2
0070 jmp 0xa592
0072 push 3
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetYardMode
0079 jmp 0xa6c8
007c mov es, word ptr [0xc196]
0080 cmp word ptr es:[0x80b4], 2
0086 je 0xa5d8
0088 push 0x7e
008a push 0
008c push 1
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0093 add sp, 6
0096 push 1
0098 push 0
009a push 0xb4
009d mov es, word ptr [0xc198]
00a1 les bx, ptr es:[0x737a]
00a6 push word ptr es:[bx + 0x3e]
00aa push word ptr es:[bx + 0x3c]
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
00b3 add sp, 0xa
00b6 pop si
00b7 leave 
00b8 retf 
00b9 nop 
00ba mov dx, word ptr [0xac9a]
00be add dx, word ptr [0xac9c]
00c2 mov bx, word ptr [0xcc84] ; _MeType
00c6 cmp bx, 0x40
00c9 je 0xa5ee
00cb cmp bx, 0x20
00ce jne 0xa5ef
00d0 dec dx
00d1 or dx, dx
00d3 jg 0xa61c
00d5 push 0x7e
00d7 push 0
00d9 push 1
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00e0 add sp, 6
00e3 push 1
00e5 push 0
00e7 push 0xb4
00ea mov es, word ptr [0xc198]
00ee les bx, ptr es:[0x737a]
00f3 push word ptr es:[bx + 0x16]
00f7 push word ptr es:[bx + 0x14]
00fb jmp 0xa5cc
00fd nop 
00fe mov es, word ptr [0xc19a]
0102 mov word ptr es:[0x7c44], 0xc8
0109 push 1
010b push 0
010d push 0xb4
0110 mov es, word ptr [0xc198]
0114 les bx, ptr es:[0x737a]
0119 push word ptr es:[bx + 0x1a]
011d push word ptr es:[bx + 0x18]
0121 jmp 0xa5cc
0123 nop 
0124 mov es, word ptr [0xc19c]
0128 mov word ptr es:[0x836e], 1
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _UpdateLayQueenModeDisplay
0134 pop si
0135 leave 
0136 retf 
0137 nop 
0138 mov es, word ptr [0xc19c]
013c mov word ptr es:[0x836e], 0
0143 jmp 0xa64d
0145 nop 
0146 push 0x190e
0149 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 332, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
014e add sp, 2
0151 push 0x1910
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
0159 add sp, 2
015c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PlaceQueenInYard
0161 push 0x1900
0164 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 359, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0169 add sp, 2
016c or ax, ax
016e je 0xa6b6
0170 push 1
0172 push word ptr [0xce82] ; _YardMode
0176 nop 
0177 push cs
0178 call 0xb462 ; _Draw_SimYard
017b add sp, 4
017e mov word ptr [0x18b4], 0
0184 push word ptr [0xbcd8]
0188 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 393, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
018d mov word ptr [0x18b4], 1
0193 nop 
0194 push cs
0195 call 0xacd8 ; _DrawYardData
0198 push 0x1910
019b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 414, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjUnselected
01a0 jmp 0xa6c8
01a2 push 0x1906
01a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 424, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoWinHelp
01aa add sp, 2
01ad pop si
01ae leave 
01af retf 
```

## Known declaration examples

- `extern void far DoWinHelp(int mode);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern void far DrawYardData(void);` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far Draw_SimYard(int mode, int selector);` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int near YardMode;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far YardToMap(void);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far YardToMap(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearLastFileName', 'offset': 42160, 'source': 'src/recovered/ClearLastFileName.c', 'size': 11}
- {'symbol': '_CheckRainArray', 'offset': 42172, 'source': 'src/recovered/wf_CheckRainArray-5188fd7161.c', 'size': 97}
- {'symbol': '_ProcYardRibbonEvent', 'offset': 42702, 'source': None, 'size': 714}
- {'symbol': '_DrawYardCursor', 'offset': 43416, 'source': 'src/recovered/DrawYardCursor.c', 'size': 36}

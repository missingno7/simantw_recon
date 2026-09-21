# Recovery task _SetMapModeAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 274 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0007 mov es, ax
0009 mov si, word ptr [bp + 6]
000c cmp word ptr es:[0x8610], si
0011 jne 0x9ea2
0013 cmp si, 4
0016 jl 0x9ea2
0018 cmp si, 8
001b jg 0x9ea2
001d mov si, 1
0020 mov ax, si
0022 or ax, ax
0024 je 0x9ec6
0026 dec ax
0027 jge 0x9eae
0029 jmp 0x9f91
002c jno 0x9eb3
002e jmp 0x9f91
0031 dec ax
0032 dec ax
0033 jle 0x9efb
0035 dec ax
0036 jge 0x9ebd
0038 jmp 0x9f91
003b sub ax, 4
003e jle 0x9eea
0040 pop si
0041 leave 
0042 retf 
0043 nop 
0044 cmp word ptr es:[0x8610], 0
004a jne 0x9ed1
004c jmp 0x9f91
004f mov es, word ptr [0xc0e4]
0053 mov word ptr es:[0x8610], si
0058 push word ptr [0xce82] ; _YardMode
005c nop 
005d push cs
005e call 0x9f94 ; _SetYardMode
0061 add sp, 2
0064 pop si
0065 leave 
0066 retf 
0067 nop 
0068 cmp word ptr [0xcc76], 1 ; _MapPlane
006d je 0x9efb
006f push 1
0071 nop 
0072 push cs
0073 call 0xa5ca ; _SetMapPlane
0076 add sp, 2
0079 mov es, word ptr [0xc0e4]
007d mov word ptr es:[0x8610], si
0082 nop 
0083 push cs
0084 call 0x953c ; _SetMapTitle
0087 push 0x100
008a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
008f add sp, 2
0092 or ax, ax
0094 je 0x9f28
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
009b push 0x100
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
00a3 add sp, 2
00a6 cmp word ptr [0xbcea], 0
00ab je 0x9f56
00ad cmp si, 4
00b0 jl 0x9f4e
00b2 cmp si, 8
00b5 jg 0x9f4e
00b7 shl si, 1
00b9 push word ptr [si + 0x156a]
00bd push 1
00bf push 0x2200
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetGroupSelectedObj
00c7 add sp, 6
00ca jmp 0x9f7d
00cc push 1
00ce push 0x2200
00d1 jmp 0x9f75
00d3 nop 
00d4 cmp si, 4
00d7 jl 0x9f70
00d9 cmp si, 8
00dc jg 0x9f70
00de shl si, 1
00e0 push word ptr [si + 0x1574]
00e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
00e9 add sp, 2
00ec jmp 0x9f7d
00ee push 2
00f0 push 0x100
00f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupUnselected
00f8 add sp, 4
00fb push 0x100
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0103 add sp, 2
0106 or ax, ax
0108 je 0x9f91
010a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 269, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
010f pop si
0110 leave 
0111 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapTitle(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SubtractFood', 'offset': 40484, 'source': None, 'size': 77}
- {'symbol': '_SetEditMode', 'offset': 40562, 'source': 'src/recovered/SetEditMode.c', 'size': 16}
- {'symbol': '_SetYardMode', 'offset': 40852, 'source': None, 'size': 1009}
- {'symbol': '_SetMapPlaneLocation', 'offset': 41862, 'source': None, 'size': 419}

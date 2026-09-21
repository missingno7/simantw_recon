# Recovery task _DrawMower

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 229 bytes.

```asm
0000 enter 6, 0
0004 mov bx, word ptr [0xac74] ; _BoyHere
0008 mov word ptr [bp - 2], 0
000d cmp bx, 3
0010 je 0xb2db
0012 cmp bx, 4
0015 jne 0xb33f
0017 mov es, word ptr [0xc1b6]
001b cmp word ptr es:[0x9c28], 0
0021 jne 0xb2f5
0023 push 0x40
0025 push 0
0027 push 0x24
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
002e add sp, 6
0031 mov ax, word ptr [0xac7a] ; _BoyFrame
0034 sub ax, 0x67
0037 jl 0xb30c
0039 jo 0xb30c
003b dec ax
003c dec ax
003d jle 0xb332
003f sub ax, 4
0042 jl 0xb30c
0044 dec ax
0045 dec ax
0046 jle 0xb33a
0048 cmp word ptr [0x1890], -1
004d jne 0xb316
004f jmp 0xb3a7
0052 push ds
0053 push 0x1954
0056 push word ptr [0x1890]
005a push word ptr [0x1886] ; _yardAnimHandle
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
0063 add sp, 8
0066 mov word ptr [0x1890], 0xffff
006c leave 
006d retf 
006e mov word ptr [bp - 2], 1
0073 jmp 0xb33f
0075 nop 
0076 mov word ptr [bp - 2], 2
007b cmp word ptr [bp - 2], 0
007f jne 0xb34e
0081 mov bx, 0x62
0084 mov dx, 0xb5
0087 jmp 0xb36c
0089 nop 
008a cmp word ptr [bp - 2], 1
008e jne 0xb35e
0090 mov bx, word ptr [0xac76] ; _BoyX
0094 add bx, 0x13
0097 jmp 0xb365
0099 nop 
009a mov bx, word ptr [0xac76] ; _BoyX
009e sub bx, 0xf
00a1 mov dx, word ptr [0xac78] ; _BoyY
00a5 add dx, 0xf
00a8 cmp word ptr [0x1890], -1
00ad je 0xb390
00af push -1
00b1 push word ptr [0x1890]
00b5 push word ptr [0x1886] ; _yardAnimHandle
00b9 mov ax, word ptr [bp - 2]
00bc add ax, 0x2260
00bf push ax
00c0 push dx
00c1 push bx
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
00c7 add sp, 0xc
00ca leave 
00cb retf 
00cc push -1
00ce mov ax, word ptr [bp - 2]
00d1 add ax, 0x2260
00d4 push ax
00d5 push dx
00d6 push bx
00d7 push word ptr [0x1886] ; _yardAnimHandle
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
00e0 mov word ptr [0x1890], ax
00e3 leave 
00e4 retf 
```

## Known declaration examples

- `extern int near BoyFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near BoyHere;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near BoyX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near BoyY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawSimCat', 'offset': 45568, 'source': None, 'size': 132}
- {'symbol': '_DrawForSale', 'offset': 45700, 'source': 'src/recovered/wf_DrawForSale-956dc12b43.c', 'size': 63}
- {'symbol': '_DrawAnimYardMessage', 'offset': 45994, 'source': 'src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c', 'size': 184}
- {'symbol': '_Draw_SimYard', 'offset': 46178, 'source': None, 'size': 1595}

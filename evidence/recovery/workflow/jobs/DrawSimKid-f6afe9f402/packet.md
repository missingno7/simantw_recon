# Recovery task _DrawSimKid

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 507 bytes.

```asm
0000 enter 0x10, 0
0004 push si
0005 mov dx, word ptr [0xac7a] ; _BoyFrame
0009 mov ax, word ptr [0xac76] ; _BoyX
000c mov word ptr [bp - 2], ax
000f mov ax, word ptr [0xac78] ; _BoyY
0012 mov word ptr [bp - 4], ax
0015 cmp dx, 0xc
0018 jge 0xaf3e
001a mov bx, dx
001c mov al, byte ptr [bx + 0x18d4]
0020 cwde 
0021 add word ptr [bp - 2], ax
0024 mov al, byte ptr [bx + 0x18e0]
0028 jmp 0xaf68
002a cmp dx, 0x18
002d jge 0xaf54
002f mov bx, dx
0031 mov al, byte ptr [bx + 0x18d8]
0035 cwde 
0036 add word ptr [bp - 2], ax
0039 mov al, byte ptr [bx + 0x18dc]
003d jmp 0xaf68
003f nop 
0040 cmp dx, 0xc8
0044 jge 0xaf6c
0046 mov bx, dx
0048 mov al, byte ptr [bx + 0x1890]
004c cwde 
004d add word ptr [bp - 2], ax
0050 mov al, byte ptr [bx + 0x189c]
0054 cwde 
0055 add word ptr [bp - 4], ax
0058 cmp word ptr [0x1888], -1
005d je 0xaf94
005f push -1
0061 push word ptr [0x1888]
0065 push word ptr [0x1886] ; _yardAnimHandle
0069 mov ax, word ptr [0xac7a] ; _BoyFrame
006c add ax, 0x1f40
006f push ax
0070 push word ptr [bp - 4]
0073 push word ptr [bp - 2]
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
007b add sp, 0xc
007e jmp 0xafb2
0080 push -1
0082 mov ax, word ptr [0xac7a] ; _BoyFrame
0085 add ax, 0x1f40
0088 push ax
0089 push word ptr [bp - 4]
008c push word ptr [bp - 2]
008f push word ptr [0x1886] ; _yardAnimHandle
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0098 add sp, 0xa
009b mov word ptr [0x1888], ax
009e mov es, word ptr [0xc1b6]
00a2 cmp word ptr es:[0x9c28], 0
00a8 jne 0xafe2
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00af mov es, word ptr [0xc1b8]
00b3 cmp dx, word ptr es:[0x7d4c]
00b8 jl 0xafe2
00ba jg 0xafd7
00bc cmp ax, word ptr es:[0x7d4a]
00c1 jbe 0xafe2
00c3 mov es, word ptr [0xc1ba]
00c7 mov word ptr es:[0x99da], 0
00ce mov bx, 0x9f24
00d1 mov es, word ptr [0xc1bc]
00d5 mov word ptr [bp - 0xc], bx
00d8 mov word ptr [bp - 0xa], es
00db cmp word ptr es:[bx], -1
00df je 0xb010
00e1 push ds
00e2 push 0x190c
00e5 push word ptr es:[bx]
00e8 push word ptr [0x1886] ; _yardAnimHandle
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
00f1 add sp, 8
00f4 les bx, ptr [bp - 0xc]
00f7 mov word ptr es:[bx], 0xffff
00fc mov bx, 0x9f20
00ff mov es, word ptr [0xc1bc]
0103 mov word ptr [bp - 0x10], bx
0106 mov word ptr [bp - 0xe], es
0109 cmp word ptr es:[bx], 0
010d je 0xb044
010f push word ptr es:[bx]
0112 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 277, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0117 add sp, 2
011a les bx, ptr [bp - 0x10]
011d push word ptr es:[bx]
0120 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 291, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0125 add sp, 2
0128 les bx, ptr [bp - 0x10]
012b mov word ptr es:[bx], 0
0130 mov es, word ptr [0xc1ba]
0134 cmp word ptr es:[0x99da], 0
013a jne 0xb053
013c jmp 0xb10c
013f push 2
0141 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 324, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0146 add sp, 2
0149 push 0
014b mov es, word ptr [0xc1be]
014f mov bx, word ptr es:[0x72f2]
0154 shl bx, 2
0157 mov es, word ptr [0xc1c0]
015b les si, ptr es:[0x9e88]
0160 push word ptr es:[bx + si + 2]
0164 push word ptr es:[bx + si]
0167 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 362, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MakeBalloon
016c add sp, 6
016f les bx, ptr [bp - 0x10]
0172 mov word ptr es:[bx], ax
0175 push 0
0177 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 378, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
017c add sp, 2
017f les bx, ptr [bp - 0x10]
0182 push word ptr es:[bx]
0185 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 392, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
018a add sp, 2
018d mov es, word ptr [0xc1c2]
0191 mov word ptr es:[0xa072], ax
0195 mov word ptr es:[0xa074], dx
019a les bx, ptr es:[0xa072]
019f mov ax, word ptr es:[bx + 0xa]
01a3 add word ptr [bp - 2], 4
01a7 mov es, word ptr [0xc1c4]
01ab mov si, word ptr es:[0x8112]
01b0 sub si, ax
01b2 add si, word ptr [0xac78] ; _BoyY
01b6 les bx, ptr [bp - 0xc]
01b9 cmp word ptr es:[bx], -1
01bd je 0xb0f0
01bf push 0x3e7
01c2 push word ptr es:[bx]
01c5 push word ptr [0x1886] ; _yardAnimHandle
01c9 push 0x7530
01cc push si
01cd push word ptr [bp - 2]
01d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 467, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
01d5 add sp, 0xc
01d8 pop si
01d9 leave 
01da retf 
01db nop 
01dc push 0x3e7
01df push 0x7530
01e2 push si
01e3 push word ptr [bp - 2]
01e6 push word ptr [0x1886] ; _yardAnimHandle
01ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 493, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
01ef add sp, 0xa
01f2 les bx, ptr [bp - 0xc]
01f5 mov word ptr es:[bx], ax
01f8 pop si
01f9 leave 
01fa retf 
```

## Known declaration examples

- `extern int near BoyFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int near BoyX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int near BoyY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawYard', 'offset': 44708, 'source': 'src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c', 'size': 56}
- {'symbol': '_UpdateYard', 'offset': 44764, 'source': 'src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c', 'size': 56}
- {'symbol': '_DrawDog', 'offset': 45328, 'source': None, 'size': 134}
- {'symbol': '_DrawSimBird', 'offset': 45462, 'source': 'src/recovered/wf_DrawSimBird-fa6c3c3f83.c', 'size': 105}

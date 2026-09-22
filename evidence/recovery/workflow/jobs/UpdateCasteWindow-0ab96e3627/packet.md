# Recovery task _UpdateCasteWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 547 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 push word ptr [0x15b8] ; _casteBitmap
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
000f add sp, 2
0012 mov si, ax
0014 mov word ptr [bp - 4], dx
0017 lea ax, [bp - 0xe]
001a push ss
001b push ax
001c push 0x1302
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0024 add sp, 6
0027 push 0
0029 mov ax, 0xffff
002c push ax
002d xor dx, dx
002f mov es, word ptr [0xc128]
0033 mov cx, word ptr es:[0x9b64]
0038 mov bx, cx
003a sub di, di
003c sub ax, cx
003e sbb dx, di
0040 push dx
0041 push ax
0042 mov es, word ptr [0xc122]
0046 mov ax, word ptr es:[0x80d0]
004a sub ax, 2
004d push di
004e push ax
004f mov word ptr [bp - 0x16], cx
0052 mov word ptr [bp - 0x14], di
0055 mov di, cx
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
005c push dx
005d push ax
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0063 mov es, word ptr [0xc126]
0067 add ax, word ptr es:[0xa092]
006c mov bx, 0x99de
006f mov es, word ptr [0xc12a]
0073 mov word ptr [bp - 0x12], bx
0076 mov word ptr [bp - 0x10], es
0079 mov word ptr es:[bx], ax
007c push 0
007e push -1
0080 push word ptr [bp - 0x14]
0083 push di
0084 mov es, word ptr [0xc120]
0088 push 0
008a push word ptr es:[0x7f00]
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0094 push dx
0095 push ax
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
009b mov word ptr [bp - 2], ax
009e mov cx, di
00a0 shl ax, 1
00a2 mov es, word ptr [0xc11c]
00a6 mov di, word ptr es:[0x9cec]
00ab sub di, ax
00ad cmp cx, -1
00b0 je 0xb892
00b2 cmp di, 3
00b5 jl 0xb892
00b7 mov ax, 0xffff
00ba mov es, word ptr [0xc128]
00be sub ax, word ptr es:[0x9b64]
00c3 push 0
00c5 push ax
00c6 push 0
00c8 push word ptr es:[0x9b68]
00cd lea ax, [di - 3]
00d0 cdq 
00d1 push dx
00d2 push ax
00d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00d8 push dx
00d9 push ax
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00df mov es, word ptr [0xc126]
00e3 add ax, word ptr es:[0xa094]
00e8 add ax, word ptr [bp - 2]
00eb jmp 0xb89a
00ed nop 
00ee mov es, word ptr [0xc126]
00f2 mov ax, word ptr es:[0xa090]
00f6 add ax, 2
00f9 mov es, word ptr [0xc12a]
00fd mov word ptr es:[0x99dc], ax
0101 mov bx, 0x7c4a
0104 mov es, word ptr [0xc12c]
0108 mov word ptr [bp - 0x1a], bx
010b mov word ptr [bp - 0x18], es
010e cmp word ptr es:[bx], 0
0112 jne 0xb910
0114 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 279, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_MakeAnimSet
0119 les bx, ptr [bp - 0x1a]
011c mov word ptr es:[bx], ax
011f push 0
0121 push 0x578
0124 mov es, word ptr [0xc136]
0128 mov ax, word ptr es:[0x9bd0]
012c cdq 
012d sub ax, dx
012f sar ax, 1
0131 les bx, ptr [bp - 0x12]
0134 sub ax, word ptr es:[bx]
0137 neg ax
0139 push ax
013a mov es, word ptr [0xc136]
013e mov ax, word ptr es:[0x9bce]
0142 cdq 
0143 sub ax, dx
0145 sar ax, 1
0147 mov es, word ptr [0xc12a]
014b sub ax, word ptr es:[0x99dc]
0150 neg ax
0152 push ax
0153 les bx, ptr [bp - 0x1a]
0156 push word ptr es:[bx]
0159 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 348, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
015e add sp, 0xa
0161 mov es, word ptr [0xc138]
0165 mov word ptr es:[0x78a2], ax
0169 jmp 0xb95c
016b nop 
016c push 0x8000
016f mov es, word ptr [0xc138]
0173 push word ptr es:[0x78a2]
0178 les bx, ptr [bp - 0x1a]
017b push word ptr es:[bx]
017e push 0x8000
0181 mov es, word ptr [0xc136]
0185 mov ax, word ptr es:[0x9bd0]
0189 cdq 
018a sub ax, dx
018c sar ax, 1
018e les bx, ptr [bp - 0x12]
0191 sub ax, word ptr es:[bx]
0194 neg ax
0196 push ax
0197 mov es, word ptr [0xc136]
019b mov ax, word ptr es:[0x9bce]
019f cdq 
01a0 sub ax, dx
01a2 sar ax, 1
01a4 mov es, word ptr [0xc12a]
01a8 sub ax, word ptr es:[0x99dc]
01ad neg ax
01af push ax
01b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 435, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
01b5 add sp, 0xc
01b8 mov es, word ptr [bp - 4]
01bb push word ptr es:[si + 2]
01bf push word ptr es:[si]
01c2 lea ax, [si + 4]
01c5 push es
01c6 push ax
01c7 push word ptr [bp - 0xc]
01ca push word ptr [bp - 0xe]
01cd push 0x1300
01d0 les bx, ptr [bp - 0x1a]
01d3 push word ptr es:[bx]
01d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 473, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RenderAnimSet
01db add sp, 0x10
01de push word ptr [0x15b8] ; _casteBitmap
01e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 485, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01e7 add sp, 2
01ea push 0x1309
01ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 496, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_InvalidateObject
01f2 add sp, 2
01f5 push 0x130a
01f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 507, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_InvalidateObject
01fd add sp, 2
0200 push 0x130b
0203 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 518, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_InvalidateObject
0208 add sp, 2
020b push 0x130c
020e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 529, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_InvalidateObject
0213 add sp, 2
0216 push word ptr [0xbccc]
021a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 539, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
021f pop si
0220 pop di
0221 leave 
0222 retf 
```

## Known declaration examples

- `extern unsigned int near casteBitmap;` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far hanim_RenderAnimSet(unsigned int setHandle, int window, int left, int top, int a, int b, int size, int mode);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_CasteControlChanged', 'offset': 46012, 'source': None, 'size': 500}
- {'symbol': '_win_ModeControlChanged', 'offset': 46512, 'source': None, 'size': 500}
- {'symbol': '_UpdateModeWindow', 'offset': 47560, 'source': None, 'size': 547}
- {'symbol': '_OpenCasteWindow', 'offset': 48108, 'source': 'src/recovered/wf_OpenCasteWindow-3d435baaee.c', 'size': 141}

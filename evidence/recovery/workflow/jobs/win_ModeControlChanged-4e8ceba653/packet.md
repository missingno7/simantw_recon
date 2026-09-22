# Recovery task _win_ModeControlChanged

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 500 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 lea ax, [bp - 8]
0009 push ss
000a push ax
000b push 0x120d
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0013 add sp, 6
0016 mov ax, word ptr [bp - 4]
0019 sub ax, word ptr [bp - 8]
001c mov es, word ptr [0xc11c]
0020 mov word ptr es:[0x9cec], ax
0024 shr ax, 1
0026 mov es, word ptr [0xc11e]
002a mov word ptr es:[0x99d6], ax
002e mov bx, 0x7f00
0031 mov es, word ptr [0xc120]
0035 mov word ptr [bp - 0x10], bx
0038 mov word ptr [bp - 0xe], es
003b mov word ptr es:[bx], ax
003e mov cx, word ptr [bp - 2]
0041 sub cx, word ptr [bp - 6]
0044 mov es, word ptr [0xc122]
0048 mov word ptr es:[0x80d0], cx
004d push 0
004f push cx
0050 mov cx, ax
0052 sub dx, dx
0054 mov dl, ah
0056 mov ah, al
0058 sub al, al
005a push dx
005b push ax
005c mov si, cx
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0063 mov es, word ptr [0xc124]
0067 mov word ptr es:[0x9fc0], ax
006b mov word ptr es:[0x9fc2], dx
0070 add si, word ptr [bp - 8]
0073 mov es, word ptr [0xc12e]
0077 mov word ptr es:[0x80f8], si
007c mov ax, word ptr [bp - 6]
007f mov word ptr es:[0x80fa], ax
0083 mov ax, word ptr [bp - 2]
0086 mov word ptr es:[0x8102], ax
008a mov word ptr es:[0x80fe], ax
008e mov ax, word ptr [bp - 8]
0091 mov word ptr es:[0x80fc], ax
0095 mov ax, word ptr [bp - 4]
0098 mov word ptr es:[0x8100], ax
009c push 0
009e mov ax, 0xffff
00a1 push ax
00a2 xor dx, dx
00a4 mov es, word ptr [0xc130]
00a8 mov cx, word ptr es:[0x9c74]
00ad mov bx, cx
00af sub si, si
00b1 sub ax, cx
00b3 sbb dx, si
00b5 push dx
00b6 push ax
00b7 mov es, word ptr [0xc122]
00bb mov ax, word ptr es:[0x80d0]
00bf sub ax, 2
00c2 push si
00c3 push ax
00c4 mov di, cx
00c6 mov word ptr [bp - 0x12], bx
00c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00ce push dx
00cf push ax
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
00d5 mov es, word ptr [0xc12e]
00d9 add ax, word ptr es:[0x80fa]
00de mov es, word ptr [0xc132]
00e2 mov word ptr es:[0x7c1c], ax
00e6 mov ax, di
00e8 push si
00e9 push -1
00eb push si
00ec push ax
00ed les bx, ptr [bp - 0x10]
00f0 push si
00f1 push word ptr es:[bx]
00f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00f9 push dx
00fa push ax
00fb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 254, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0100 mov di, ax
0102 mov es, word ptr [0xc11c]
0106 mov si, word ptr es:[0x9cec]
010b shl ax, 1
010d sub si, ax
010f cmp word ptr [bp - 0x12], -1
0113 je 0xb700
0115 cmp si, 3
0118 jl 0xb700
011a mov ax, 0xffff
011d mov es, word ptr [0xc130]
0121 sub ax, word ptr es:[0x9c74]
0126 push 0
0128 push ax
0129 push 0
012b push word ptr es:[0x9c78]
0130 lea ax, [si - 3]
0133 cdq 
0134 push dx
0135 push ax
0136 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 313, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
013b push dx
013c push ax
013d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0142 mov es, word ptr [0xc12e]
0146 add ax, word ptr es:[0x80fc]
014b add ax, di
014d jmp 0xb708
014f nop 
0150 mov es, word ptr [0xc12e]
0154 mov ax, word ptr es:[0x80f8]
0158 add ax, 2
015b mov es, word ptr [0xc132]
015f mov word ptr es:[0x7c1a], ax
0163 mov bx, 0x7ae2
0166 mov es, word ptr [0xc134]
016a mov word ptr [bp - 0x16], bx
016d mov word ptr [bp - 0x14], es
0170 cmp word ptr es:[bx], 0
0174 je 0xb739
0176 push word ptr es:[bx]
0179 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 380, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimSet
017e add sp, 2
0181 les bx, ptr [bp - 0x16]
0184 mov word ptr es:[bx], 0
0189 cmp word ptr [0x15b6], 0 ; _modeBitmap
018e je 0xb7a0
0190 push 0x11f8
0193 lea ax, [bp - 0xc]
0196 push ss
0197 push ax
0198 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 411, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
019d add sp, 6
01a0 push word ptr [0x15b6] ; _modeBitmap
01a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
01a9 add sp, 2
01ac mov si, ax
01ae mov word ptr [bp - 2], dx
01b1 mov ax, word ptr [bp - 0xc]
01b4 mov es, dx
01b6 mov word ptr es:[si], ax
01b9 mov ax, word ptr [bp - 0xa]
01bc mov word ptr es:[si + 2], ax
01c0 lea ax, [bp - 6]
01c3 push ss
01c4 push ax
01c5 lea ax, [bp - 8]
01c8 push ss
01c9 push ax
01ca push 0x11f8
01cd push word ptr [bp - 0xc]
01d0 push word ptr [bp - 0xa]
01d3 push 0
01d5 push 0
01d7 lea ax, [si + 4]
01da push es
01db push ax
01dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 479, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
01e1 add sp, 0x16
01e4 push word ptr [0x15b6] ; _modeBitmap
01e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 491, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01ed add sp, 2
01f0 pop si
01f1 pop di
01f2 leave 
01f3 retf 
```

## Known declaration examples

- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far hanim_RemoveAnimSet(unsigned int setHandle);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near modeBitmap;` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern unsigned int near modeBitmap;` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitTriVars', 'offset': 45860, 'source': 'src/recovered/wf_InitTriVars-e97b7c6f72.c', 'size': 152}
- {'symbol': '_win_CasteControlChanged', 'offset': 46012, 'source': None, 'size': 500}
- {'symbol': '_UpdateCasteWindow', 'offset': 47012, 'source': None, 'size': 547}
- {'symbol': '_UpdateModeWindow', 'offset': 47560, 'source': None, 'size': 547}

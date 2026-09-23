# Recovery task _win_SetPalette

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 546 bytes.

```asm
0000 enter 0x32, 0
0004 push di
0005 push si
0006 push 0
0008 push 0xf
000a push word ptr [bp + 6]
000d nop 
000e push cs
000f call 0x8292 ; _db_LoadObject
0012 add sp, 6
0015 mov word ptr [bp - 0x16], ax
0018 or ax, ax
001a jne 0xc403
001c jmp 0xc602
001f push ax
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0025 add sp, 2
0028 mov es, dx
002a mov bx, ax
002c mov si, ax
002e mov word ptr [bp - 0x12], es
0031 mov al, byte ptr es:[bx + 1]
0035 cwde 
0036 or ax, ax
0038 je 0xc421
003a jmp 0xc5e7
003d cmp byte ptr [0xcc7e], 0 ; _displayType
0042 jne 0xc478
0044 add si, 2
0047 mov word ptr [bp - 2], ax
004a mov di, ax
004c mov al, byte ptr es:[si]
004f mov cx, ax
0051 and al, 0x20
0053 mov dl, byte ptr es:[si + 2]
0057 and dl, 0x10
005a shr dl, 1
005c mov bl, byte ptr es:[si + 1]
0060 and bl, 0x10
0063 or dl, bl
0065 shr dl, 1
0067 mov bl, byte ptr es:[si + 2]
006b and bl, 0x20
006e or dl, bl
0070 and cl, 0x10
0073 or dl, cl
0075 shr dl, 1
0077 mov cl, byte ptr es:[si + 1]
007b and cl, 0x20
007e or dl, cl
0080 shr dl, 1
0082 or al, dl
0084 mov byte ptr [bp + di - 0x28], al
0087 add si, 3
008a inc di
008b cmp di, 0x10
008e jl 0xc430
0090 jmp 0xc5e7
0093 nop 
0094 cmp byte ptr ss:[0xcc7e], 8
009a je 0xc486
009c push ss
009d pop ds
009e jmp 0xc5e7
00a1 nop 
00a2 mov ax, bx
00a4 mov dx, es
00a6 add ax, 2
00a9 mov di, ax
00ab mov <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ae mov ds, ax
00b0 mov al, byte ptr [0x8c41]
00b3 sub ah, ah
00b5 mov word ptr [bp - 0x2a], ax
00b8 mov al, byte ptr [0x8c42]
00bb mov word ptr [bp - 0x2c], ax
00be mov al, byte ptr [0x8c40]
00c1 mov word ptr [bp - 0x2e], ax
00c4 mov word ptr [bp - 0x10], 0x10
00c9 mov word ptr [bp - 0x14], si
00cc mov ax, word ptr [bp - 0x2c]
00cf mov cl, byte ptr es:[di]
00d2 mov bx, ax
00d4 mov al, byte ptr es:[di + 2]
00d8 sub ah, ah
00da sub bx, ax
00dc mov ax, bx
00de mul bx
00e0 mov dx, ax
00e2 mov ax, word ptr [bp - 0x2a]
00e5 mov bx, ax
00e7 mov al, byte ptr es:[di + 1]
00eb sub ah, ah
00ed sub bx, ax
00ef mov ax, bx
00f1 mov si, dx
00f3 mul bx
00f5 add ax, si
00f7 mov dx, ax
00f9 mov ax, word ptr [bp - 0x2e]
00fc mov bx, ax
00fe sub ch, ch
0100 sub bx, cx
0102 mov ax, bx
0104 mov cx, dx
0106 mul bx
0108 add cx, ax
010a mov word ptr [bp - 8], cx
010d mov word ptr [bp - 6], 0
0112 mov si, 0x8c45
0115 mov word ptr [bp - 0xa], es
0118 mov cl, byte ptr [si]
011a sub ch, ch
011c mov al, byte ptr es:[di + 1]
0120 mov dl, byte ptr es:[di]
0123 lea bx, [si - 1]
0126 mov bl, byte ptr [bx]
0128 sub bh, bh
012a sub dh, dh
012c sub bx, dx
012e mov ax, bx
0130 mov dl, byte ptr es:[di + 1]
0134 mov word ptr [bp - 0x30], dx
0137 mul bx
0139 mov bl, byte ptr [si + 1]
013c sub bh, bh
013e mov dl, byte ptr es:[di + 2]
0142 sub dh, dh
0144 sub bx, dx
0146 mov dx, ax
0148 mov ax, bx
014a mov word ptr [bp - 0x32], dx
014d mul bx
014f add ax, word ptr [bp - 0x32]
0152 mov dx, ax
0154 mov ax, cx
0156 mov cl, byte ptr [bp - 0x30]
0159 sub ax, cx
015b mov cx, ax
015d mov bx, dx
015f mul cx
0161 add bx, ax
0163 sub cx, cx
0165 mov word ptr [bp - 2], cx
0168 cmp cx, word ptr [bp - 6]
016b ja 0xc563
016d jb 0xc558
016f cmp bx, word ptr [bp - 8]
0172 jae 0xc563
0174 mov ax, bx
0176 mov dx, word ptr [bp - 2]
0179 mov word ptr [bp - 8], ax
017c mov word ptr [bp - 6], dx
017f add si, 4
0182 cmp si, 0x8c81
0186 jb 0xc4fc
0188 add di, 3
018b dec word ptr [bp - 0x10]
018e je 0xc577
0190 jmp 0xc4b0
0193 mov ax, word ptr [bp - 0x14]
0196 mov dx, word ptr [bp - 0x12]
0199 add ax, 2
019c mov di, ax
019e mov word ptr [bp - 0xa], dx
01a1 xor si, si
01a3 mov es, word ptr [bp - 0xa]
01a6 mov al, byte ptr es:[di]
01a9 mov byte ptr [si - 0x73c0], al
01ad mov <resolved loader operand; see bindings> ; [{'operand_offset': 430, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01b0 mov es, cx
01b2 mov byte ptr es:[si - 0x7400], al
01b7 mov es, word ptr [bp - 0xa]
01ba mov al, byte ptr es:[di + 1]
01be mov byte ptr [si - 0x73bf], al
01c2 mov es, cx
01c4 mov byte ptr es:[si - 0x73ff], al
01c9 mov es, word ptr [bp - 0xa]
01cc mov al, byte ptr es:[di + 2]
01d0 mov byte ptr [si - 0x73be], al
01d4 mov es, cx
01d6 mov byte ptr es:[si - 0x73fe], al
01db add di, 3
01de add si, 4
01e1 cmp si, 0x40
01e4 jl 0xc587
01e6 push ss
01e7 pop ds
01e8 cmp word ptr [0x85a], 0 ; _paletteH
01ed je 0xc5e2
01ef push word ptr [0x85a] ; _paletteH
01f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 500, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
01f8 mov word ptr [0x85a], 0 ; _paletteH
01fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 513, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InitPalette
0203 push word ptr [bp - 0x16]
0206 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 521, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
020b add sp, 2
020e push 0xf
0210 push word ptr [bp + 6]
0213 nop 
0214 push cs
0215 call 0x8426 ; _db_ReleaseObject
0218 add sp, 4
021b mov ax, 1
021e pop si
021f pop di
0220 leave 
0221 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void InitPalette(void);` — src/recovered/wf_PaintStuff-4a441706dd.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near paletteH;` — src/recovered/ClosePalette.c
- `extern int near paletteH[];` — src/recovered/SetDebugFlag.c
- `extern int near paletteH[];` — src/recovered/mem_Debugging.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_WinObjAddr', 'offset': 50038, 'source': None, 'size': 87}
- {'symbol': '_win_WinAddr', 'offset': 50126, 'source': 'src/recovered/win_WinAddr.c', 'size': 22}
- {'symbol': '_RepointObjects', 'offset': 50694, 'source': None, 'size': 91}
- {'symbol': '_win_LoadWindow', 'offset': 50786, 'source': None, 'size': 419}

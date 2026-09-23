# Recovery task _win_LoadWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 419 bytes.

```asm
0000 enter 0x1c, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push 1
000b push 0
000d mov ax, si
000f mov al, ah
0011 cwde 
0012 mov word ptr [bp - 0x18], ax
0015 push ax
0016 nop 
0017 push cs
0018 call 0x8292 ; _db_LoadObject
001b add sp, 6
001e mov word ptr [bp - 2], ax
0021 or ax, ax
0023 jne 0xc694
0025 push si
0026 push ds
0027 push 0xbd3c
002a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
002f add sp, 6
0032 push word ptr [bp - 2]
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
003a add sp, 2
003d mov bx, word ptr [bp - 0x18]
0040 shl bx, 2
0043 mov word ptr [bx - 0x3166], ax
0047 mov word ptr [bx - 0x3164], dx
004b mov word ptr [bp - 0xe], ax
004e mov word ptr [bp - 0xc], dx
0051 push si
0052 mov di, bx
0054 nop 
0055 push cs
0056 call 0xe3a8 ; _win_LockWin
0059 add sp, 2
005c mov bx, di
005e les bx, ptr [bx - 0x3166]
0062 mov di, bx
0064 mov ax, word ptr es:[bx + 0xc]
0068 mov word ptr [bp - 0x14], ax
006b mov cx, ax
006d shl ax, 2
0070 add bx, ax
0072 lea ax, [bx + 0x2c]
0075 mov word ptr [bp - 8], ax
0078 mov word ptr [bp - 6], es
007b or cx, cx
007d jle 0xc710
007f lea ax, [di + 0x2c]
0082 mov dx, es
0084 mov cx, ax
0086 mov word ptr [bp - 2], dx
0089 mov ax, word ptr [bp - 0x14]
008c mov word ptr [bp - 0xa], ax
008f mov word ptr [bp - 4], cx
0092 mov si, cx
0094 lds bx, ptr [bp - 8]
0097 mov cx, ax
0099 mov es, word ptr [bp - 2]
009c mov word ptr es:[si], bx
009f mov word ptr es:[si + 2], ds
00a3 mov ax, word ptr [bx + 0x22]
00a6 add bx, ax
00a8 add si, 4
00ab dec cx
00ac jne 0xc6fe
00ae les bx, ptr [bp - 0xe]
00b1 mov ax, word ptr es:[bx + 0x2c]
00b5 mov dx, word ptr es:[bx + 0x2e]
00b9 mov word ptr [bp - 4], ax
00bc mov ds, dx
00be mov bx, word ptr [bp - 0x18]
00c1 shl bx, 3
00c4 add bx, 0x7f02
00c8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00cb mov es, ax
00cd cmp word ptr es:[bx], 0x8000
00d2 je 0xc74e
00d4 mov ax, bx
00d6 mov dx, es
00d8 mov bx, word ptr [bp - 4]
00db push ds
00dc lea di, [bx + 8]
00df mov si, ax
00e1 push ds
00e2 pop es
00e3 mov ds, dx
00e5 movsw word ptr es:[di], word ptr [si]
00e6 movsw word ptr es:[di], word ptr [si]
00e7 movsw word ptr es:[di], word ptr [si]
00e8 movsw word ptr es:[di], word ptr [si]
00e9 pop ds
00ea jmp 0xc75c
00ec mov ax, word ptr [bp - 4]
00ef add ax, 8
00f2 mov si, ax
00f4 mov di, bx
00f6 movsw word ptr es:[di], word ptr [si]
00f7 movsw word ptr es:[di], word ptr [si]
00f8 movsw word ptr es:[di], word ptr [si]
00f9 movsw word ptr es:[di], word ptr [si]
00fa les bx, ptr [bp - 0xe]
00fd and byte ptr es:[bx + 0x1d], 0xf7
0102 mov word ptr [bp - 6], 0
0107 cmp word ptr es:[bx + 0xc], 0
010c jg 0xc773
010e jmp 0xc7f4
0111 mov ax, bx
0113 mov dx, es
0115 add ax, 0x2c
0118 mov word ptr [bp - 0xa], ax
011b mov word ptr [bp - 8], dx
011e mov ds, dx
0120 les bx, ptr [bp - 0xa]
0123 mov ax, word ptr es:[bx]
0126 mov dx, word ptr es:[bx + 2]
012a mov word ptr [bp - 4], ax
012d mov word ptr [bp - 2], dx
0130 cmp word ptr [bp - 6], 0
0134 jne 0xc7af
0136 mov ax, word ptr [bp - 0xe]
0139 mov dx, word ptr [bp - 4]
013c mov bx, word ptr [bp - 2]
013f push ds
0140 mov di, ax
0142 mov si, dx
0144 push ds
0145 pop es
0146 mov ds, bx
0148 movsw word ptr es:[di], word ptr [si]
0149 movsw word ptr es:[di], word ptr [si]
014a movsw word ptr es:[di], word ptr [si]
014b movsw word ptr es:[di], word ptr [si]
014c pop ds
014d les bx, ptr [bp - 4]
0150 mov al, byte ptr es:[bx + 0x21]
0154 cwde 
0155 sub ax, 4
0158 je 0xc7cc
015a sub ax, 0xc
015d jl 0xc7e2
015f jo 0xc7e2
0161 dec ax
0162 dec ax
0163 jle 0xc7d8
0165 jmp 0xc7e2
0167 nop 
0168 nop 
0169 nop 
016a xor ax, ax
016c mov cx, 0xe
016f lea di, [bx + 0x2a]
0172 rep stosb byte ptr es:[di], al
0174 jmp 0xc7e2
0176 sub ax, ax
0178 mov word ptr es:[bx + 0x2c], ax
017c mov word ptr es:[bx + 0x2a], ax
0180 add word ptr [bp - 0xa], 4
0184 inc word ptr [bp - 6]
0187 mov ax, word ptr [bp - 6]
018a mov bx, word ptr [bp - 0xe]
018d cmp word ptr [bx + 0xc], ax
0190 jg 0xc782
0192 push ss
0193 pop ds
0194 push word ptr [bp + 6]
0197 nop 
0198 push cs
0199 call 0xe3a4 ; _win_UnlockWin
019c add sp, 2
019f pop si
01a0 pop di
01a1 leave 
01a2 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetPalette', 'offset': 50148, 'source': None, 'size': 546}
- {'symbol': '_RepointObjects', 'offset': 50694, 'source': None, 'size': 91}
- {'symbol': '_win_LoadAllWindows', 'offset': 51206, 'source': None, 'size': 552}
- {'symbol': '_win_Open', 'offset': 51758, 'source': None, 'size': 1385}

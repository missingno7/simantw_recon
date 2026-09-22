# Recovery task _win_EditChanged

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 458 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0008 push 0x9b08
000b push 4
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0012 add sp, 6
0015 mov es, word ptr [0xbf90]
0019 mov ax, word ptr es:[0x9b0e]
001d sub ax, word ptr es:[0x9b0a]
0022 add ax, word ptr [0x143c] ; _tileHeight
0026 dec ax
0027 cdq 
0028 idiv word ptr [0x143c] ; _tileHeight
002c mov word ptr [0xcd7a], ax ; _editHeight
002f mov cx, ax
0031 mov ax, word ptr es:[0x9b0c]
0035 sub ax, word ptr es:[0x9b08]
003a add ax, word ptr [0x143a] ; _tileWidth
003e dec ax
003f cdq 
0040 idiv word ptr [0x143a] ; _tileWidth
0044 mov word ptr [0xcc80], ax ; _editWidth
0047 imul word ptr [0x143a] ; _tileWidth
004b add ax, word ptr es:[0x9b08]
0050 mov word ptr es:[0x9b0c], ax
0054 mov ax, cx
0056 imul word ptr [0x143c] ; _tileHeight
005a add ax, word ptr es:[0x9b0a]
005f mov word ptr es:[0x9b0e], ax
0063 mov bx, 0x8df2
0066 mov es, word ptr [0xbf8a]
006a mov word ptr [bp - 6], bx
006d mov word ptr [bp - 4], es
0070 cmp word ptr es:[bx], 0
0074 je 0xcf9
0076 push word ptr es:[bx]
0079 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
007e add sp, 2
0081 les bx, ptr [bp - 6]
0084 push word ptr es:[bx]
0087 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
008c add sp, 2
008f les bx, ptr [bp - 6]
0092 mov word ptr es:[bx], 0
0097 mov bx, 0x8df4
009a mov es, word ptr [0xbf8a]
009e mov word ptr [bp - 0xa], bx
00a1 mov word ptr [bp - 8], es
00a4 cmp word ptr es:[bx], 0
00a8 je 0xd2d
00aa push word ptr es:[bx]
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00b2 add sp, 2
00b5 les bx, ptr [bp - 0xa]
00b8 push word ptr es:[bx]
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
00c0 add sp, 2
00c3 les bx, ptr [bp - 0xa]
00c6 mov word ptr es:[bx], 0
00cb push ds
00cc push 0x14a0
00cf push 1
00d1 mov ax, word ptr [0xcd7a] ; _editHeight
00d4 imul word ptr [0xcc80] ; _editWidth
00d8 push dx
00d9 push ax
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
00df add sp, 0xa
00e2 les bx, ptr [bp - 6]
00e5 mov word ptr es:[bx], ax
00e8 push ax
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00ee add sp, 2
00f1 mov word ptr [0x143e], ax
00f4 mov word ptr [0x1440], dx
00f8 push ds
00f9 push 0x14ad
00fc push 1
00fe mov ax, word ptr [0xcd7a] ; _editHeight
0101 imul word ptr [0xcc80] ; _editWidth
0105 shl ax, 1
0107 rcl dx, 1
0109 push dx
010a push ax
010b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0110 add sp, 0xa
0113 les bx, ptr [bp - 0xa]
0116 mov word ptr es:[bx], ax
0119 push ax
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 285, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
011f add sp, 2
0122 mov word ptr [0x1442], ax
0125 mov word ptr [0x1444], dx
0129 mov ax, word ptr [0xcd7a] ; _editHeight
012c mov dx, word ptr [0x1442]
0130 mov bx, word ptr [0x1444]
0134 mov cx, dx
0136 imul word ptr [0xcc80] ; _editWidth
013a mov dx, cx
013c mov cx, ax
013e shl cx, 1
0140 mov ax, 0xffff
0143 mov di, dx
0145 mov es, bx
0147 rep stosb byte ptr es:[di], al
0149 mov es, word ptr [0xbf8a]
014d mov word ptr es:[0x8df6], 0
0154 mov word ptr [bp - 2], 0x40
0159 mov ax, word ptr [0xcc76] ; _MapPlane
015c or ax, ax
015e jl 0xdc7
0160 jo 0xdc7
0162 dec ax
0163 jle 0xdcc
0165 mov cx, 0x40
0168 jmp 0xdcf
016a mov cx, 0x80
016d mov <resolved loader operand; see bindings> ; [{'operand_offset': 366, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0170 mov es, ax
0172 cmp word ptr es:[0x7d2e], 0
0178 jge 0xde6
017a mov word ptr es:[0x7d2e], 0
0181 jmp 0xdfb
0183 nop 
0184 mov bx, word ptr [0xcc80] ; _editWidth
0188 mov ax, word ptr es:[0x7d2e]
018c add ax, bx
018e cmp ax, cx
0190 jle 0xdfb
0192 sub cx, bx
0194 mov word ptr es:[0x7d2e], cx
0199 cmp word ptr es:[0x7d30], 0
019f jge 0xe0c
01a1 mov word ptr es:[0x7d30], 0
01a8 jmp 0xe24
01aa mov bx, word ptr [0xcd7a] ; _editHeight
01ae mov ax, word ptr es:[0x7d30]
01b2 add ax, bx
01b4 cmp ax, 0x40
01b7 jle 0xe24
01b9 mov ax, 0x40
01bc sub ax, bx
01be mov word ptr es:[0x7d30], ax
01c2 nop 
01c3 push cs
01c4 call 0x6086 ; _ResetEditScrollRange
01c7 pop di
01c8 leave 
01c9 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_InitMapFunctions-70fb457ea5.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
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

- {'symbol': '_ClearEditDeltaTables', 'offset': 2690, 'source': None, 'size': 247}
- {'symbol': '_ProcEditEvent', 'offset': 2938, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 232}
- {'symbol': '_OpenEditWindow', 'offset': 3628, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 11}
- {'symbol': '_MakeEditOpen', 'offset': 3640, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 24}

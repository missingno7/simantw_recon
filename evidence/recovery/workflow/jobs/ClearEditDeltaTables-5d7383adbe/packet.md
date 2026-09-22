# Recovery task _ClearEditDeltaTables

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 247 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 mov bx, 0x8df2
0008 mov es, word ptr [0xbf8a]
000c mov word ptr [bp - 4], bx
000f mov word ptr [bp - 2], es
0012 cmp word ptr es:[bx], 0
0016 je 0xabb
0018 push word ptr es:[bx]
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0020 add sp, 2
0023 les bx, ptr [bp - 4]
0026 push word ptr es:[bx]
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
002e add sp, 2
0031 les bx, ptr [bp - 4]
0034 mov word ptr es:[bx], 0
0039 mov bx, 0x8df4
003c mov es, word ptr [0xbf8a]
0040 mov word ptr [bp - 8], bx
0043 mov word ptr [bp - 6], es
0046 cmp word ptr es:[bx], 0
004a je 0xaef
004c push word ptr es:[bx]
004f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0054 add sp, 2
0057 les bx, ptr [bp - 8]
005a push word ptr es:[bx]
005d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0062 add sp, 2
0065 les bx, ptr [bp - 8]
0068 mov word ptr es:[bx], 0
006d push ds
006e push 0x14a0
0071 push 1
0073 mov ax, word ptr [0xcd7a] ; _editHeight
0076 imul word ptr [0xcc80] ; _editWidth
007a push dx
007b push ax
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0081 add sp, 0xa
0084 les bx, ptr [bp - 4]
0087 mov word ptr es:[bx], ax
008a push ax
008b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0090 add sp, 2
0093 mov word ptr [0x143e], ax
0096 mov word ptr [0x1440], dx
009a push ds
009b push 0x14ad
009e push 1
00a0 mov ax, word ptr [0xcd7a] ; _editHeight
00a3 imul word ptr [0xcc80] ; _editWidth
00a7 shl ax, 1
00a9 rcl dx, 1
00ab push dx
00ac push ax
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
00b2 add sp, 0xa
00b5 les bx, ptr [bp - 8]
00b8 mov word ptr es:[bx], ax
00bb push ax
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00c1 add sp, 2
00c4 mov word ptr [0x1442], ax
00c7 mov word ptr [0x1444], dx
00cb mov ax, word ptr [0xcd7a] ; _editHeight
00ce mov dx, word ptr [0x1442]
00d2 mov bx, word ptr [0x1444]
00d6 mov cx, dx
00d8 imul word ptr [0xcc80] ; _editWidth
00dc mov di, cx
00de mov cx, ax
00e0 shl cx, 1
00e2 mov ax, 0xffff
00e5 mov es, bx
00e7 rep stosb byte ptr es:[di], al
00e9 mov es, word ptr [0xbf8a]
00ed mov word ptr es:[0x8df6], 0
00f4 pop di
00f5 leave 
00f6 retf 
```

## Known declaration examples

- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
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

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OverlayTileSet', 'offset': 244, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 227}
- {'symbol': '_LoadTiles', 'offset': 472, 'source': None, 'size': 2218}
- {'symbol': '_ProcEditEvent', 'offset': 2938, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 232}
- {'symbol': '_win_EditChanged', 'offset': 3170, 'source': None, 'size': 458}

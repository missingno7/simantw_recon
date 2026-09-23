# Recovery task _ShowIntro

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 290 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
000b push 0x300
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0013 add sp, 2
0016 push word ptr [0xbcac]
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
001f add sp, 2
0022 push 0x7e
0024 push 0x2711
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
002c add sp, 4
002f push ds
0030 push 0x15f0
0033 push 1
0035 push 0
0037 push 0x1e
0039 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
003e add sp, 0xa
0041 mov es, word ptr [0xc154]
0045 mov word ptr es:[0x7c0c], ax
0049 push ax
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
004f add sp, 2
0052 mov di, ax
0054 mov word ptr [bp - 2], dx
0057 xor si, si
0059 mov word ptr [bp - 6], si
005c mov ds, dx
005e mov <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0061 mov es, ax
0063 mov ax, si
0065 mov cx, 8
0068 cdq 
0069 idiv cx
006b mov bx, di
006d add bx, dx
006f mov al, byte ptr [bx]
0071 cwde 
0072 mov cx, ax
0074 mov ax, si
0076 mov dx, 0x1e
0079 mov word ptr [bp - 8], dx
007c cdq 
007d idiv word ptr [bp - 8]
0080 mov ax, bx
0082 mov bx, dx
0084 mov dx, ax
0086 mov al, byte ptr es:[bx - 0x74c2]
008b cwde 
008c add cx, ax
008e mov ax, cx
0090 add ax, si
0092 mov cx, 0xa
0095 mov bx, dx
0097 cdq 
0098 idiv cx
009a add dl, 0x30
009d mov byte ptr [bx], dl
009f inc si
00a0 cmp si, 0x100
00a4 jl 0xd445
00a6 push ss
00a7 pop ds
00a8 mov es, word ptr [bp - 2]
00ab mov byte ptr es:[di + 8], ch
00af mov es, word ptr [0xc154]
00b3 push word ptr es:[0x7c0c]
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00bd add sp, 2
00c0 push 0x28
00c2 nop 
00c3 push cs
00c4 call 0x9bfe ; _DialogWaitInit
00c7 add sp, 2
00ca push 0x300
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00d2 add sp, 2
00d5 or ax, ax
00d7 je 0xd4e6
00d9 mov si, word ptr [bp - 6]
00dc or si, si
00de jne 0xd4e6
00e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
00e5 or ax, ax
00e7 jne 0xd4d4
00e9 nop 
00ea push cs
00eb call 0x9c98 ; _DialogAbortOrCont
00ee or ax, ax
00f0 je 0xd4d7
00f2 mov si, 1
00f5 push 0x300
00f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00fd add sp, 2
0100 or ax, ax
0102 jne 0xd4be
0104 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 263, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
0109 push 0x300
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
0111 add sp, 2
0114 nop 
0115 push cs
0116 call 0x9cd4 ; _DialogDone
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 284, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
011e pop si
011f pop di
0120 leave 
0121 retf 
```

## Known declaration examples

- `extern void far DialogDone(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_Events(void);` — src/recovered/wf_myDelay-ac936e115a.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int flags);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawSimPayoff', 'offset': 52648, 'source': None, 'size': 401}
- {'symbol': '_AboutDialog', 'offset': 53050, 'source': None, 'size': 1192}
- {'symbol': '_LoadMonoPats', 'offset': 54532, 'source': None, 'size': 278}
- {'symbol': '_Quit', 'offset': 54810, 'source': 'src/recovered/Quit.c', 'size': 13}

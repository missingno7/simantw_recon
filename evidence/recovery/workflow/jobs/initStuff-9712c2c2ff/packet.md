# Recovery task _initStuff

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 576 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 push 0x3e8
0008 nop 
0009 push cs
000a call 0x3f4 ; _LoadStringAnt
000d add sp, 2
0010 mov es, word ptr [0xc2ac]
0014 mov word ptr es:[0x9be6], ax
0018 mov word ptr es:[0x9be8], dx
001d push 0x3e9
0020 nop 
0021 push cs
0022 call 0x3f4 ; _LoadStringAnt
0025 add sp, 2
0028 mov es, word ptr [0xc2ae]
002c mov word ptr es:[0x7a4a], ax
0030 mov word ptr es:[0x7a4c], dx
0035 push 0x3f2
0038 nop 
0039 push cs
003a call 0x3f4 ; _LoadStringAnt
003d add sp, 2
0040 mov es, word ptr [0xc2b0]
0044 mov word ptr es:[0x737a], ax
0048 mov word ptr es:[0x737c], dx
004d push 0x3fc
0050 nop 
0051 push cs
0052 call 0x3f4 ; _LoadStringAnt
0055 add sp, 2
0058 mov es, word ptr [0xc2b2]
005c mov word ptr es:[0x7c94], ax
0060 mov word ptr es:[0x7c96], dx
0065 push 0x41a
0068 nop 
0069 push cs
006a call 0x3f4 ; _LoadStringAnt
006d add sp, 2
0070 mov es, word ptr [0xc2b4]
0074 mov word ptr es:[0x72e8], ax
0078 mov word ptr es:[0x72ea], dx
007d push 0x44c
0080 nop 
0081 push cs
0082 call 0x3f4 ; _LoadStringAnt
0085 add sp, 2
0088 mov es, word ptr [0xc2b6]
008c mov word ptr es:[0x8098], ax
0090 mov word ptr es:[0x809a], dx
0095 push 0x44d
0098 nop 
0099 push cs
009a call 0x3f4 ; _LoadStringAnt
009d add sp, 2
00a0 mov es, word ptr [0xc2b8]
00a4 mov word ptr es:[0x8074], ax
00a8 mov word ptr es:[0x8076], dx
00ad push 0x44e
00b0 nop 
00b1 push cs
00b2 call 0x3f4 ; _LoadStringAnt
00b5 add sp, 2
00b8 mov es, word ptr [0xc2ba]
00bc mov word ptr es:[0x78b2], ax
00c0 mov word ptr es:[0x78b4], dx
00c5 push 0x44f
00c8 nop 
00c9 push cs
00ca call 0x3f4 ; _LoadStringAnt
00cd add sp, 2
00d0 mov es, word ptr [0xc2bc]
00d4 mov word ptr es:[0x7892], ax
00d8 mov word ptr es:[0x7894], dx
00dd push 0x4b0
00e0 nop 
00e1 push cs
00e2 call 0x3f4 ; _LoadStringAnt
00e5 add sp, 2
00e8 mov es, word ptr [0xc2be]
00ec mov word ptr es:[0x9e88], ax
00f0 mov word ptr es:[0x9e8a], dx
00f5 push 0x4ba
00f8 nop 
00f9 push cs
00fa call 0x3f4 ; _LoadStringAnt
00fd add sp, 2
0100 mov es, word ptr [0xc2c0]
0104 mov word ptr es:[0x76a4], ax
0108 mov word ptr es:[0x76a6], dx
010d push 0x4c4
0110 nop 
0111 push cs
0112 call 0x3f4 ; _LoadStringAnt
0115 add sp, 2
0118 mov es, word ptr [0xc2c2]
011c mov word ptr es:[0x9c68], ax
0120 mov word ptr es:[0x9c6a], dx
0125 push 0x4ce
0128 nop 
0129 push cs
012a call 0x3f4 ; _LoadStringAnt
012d add sp, 2
0130 mov es, word ptr [0xc2c4]
0134 mov word ptr es:[0xa0ec], ax
0138 mov word ptr es:[0xa0ee], dx
013d push 0x4d8
0140 nop 
0141 push cs
0142 call 0x3f4 ; _LoadStringAnt
0145 add sp, 2
0148 mov es, word ptr [0xc2c6]
014c mov word ptr es:[0x8108], ax
0150 mov word ptr es:[0x810a], dx
0155 push 0x4e2
0158 nop 
0159 push cs
015a call 0x3f4 ; _LoadStringAnt
015d add sp, 2
0160 mov es, word ptr [0xc2c8]
0164 mov word ptr es:[0x9e8e], ax
0168 mov word ptr es:[0x9e90], dx
016d push 0x4ec
0170 nop 
0171 push cs
0172 call 0x3f4 ; _LoadStringAnt
0175 add sp, 2
0178 mov es, word ptr [0xc2ca]
017c mov word ptr es:[0xa076], ax
0180 mov word ptr es:[0xa078], dx
0185 push 0x76c
0188 nop 
0189 push cs
018a call 0x3f4 ; _LoadStringAnt
018d add sp, 2
0190 mov es, word ptr [0xc2cc]
0194 mov word ptr es:[0x78ac], ax
0198 mov word ptr es:[0x78ae], dx
019d push 0x708
01a0 nop 
01a1 push cs
01a2 call 0x3f4 ; _LoadStringAnt
01a5 add sp, 2
01a8 mov es, word ptr [0xc2ce]
01ac mov word ptr es:[0x7294], ax
01b0 mov word ptr es:[0x7296], dx
01b5 push 0
01b7 push 9
01b9 push 0x3e8
01bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 447, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
01c1 add sp, 6
01c4 mov si, ax
01c6 or si, si
01c8 jne 0x1e9
01ca push word ptr [bp - 2]
01cd push 0x3e8
01d0 push ds
01d1 push 0x226a
01d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 471, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01d9 add sp, 8
01dc push si
01dd push ds
01de push 0x2293
01e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 484, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _Quit
01e6 add sp, 6
01e9 push si
01ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 493, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _FlipHandleWords
01ef add sp, 2
01f2 push si
01f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 502, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
01f8 add sp, 2
01fb mov es, word ptr [0xc2d0]
01ff mov word ptr es:[0x9fca], ax
0203 mov word ptr es:[0x9fcc], dx
0208 push si
0209 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 524, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
020e add sp, 2
0211 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 532, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _initSimWindows
0216 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 537, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _OverlayOutsideTiles
021b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 542, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _BootUpGame
0220 or ax, ax
0222 jne 0x233
0224 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 551, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitSimVars
0229 nop 
022a push cs
022b call 0x152a ; _SeedSRand
022e nop 
022f push cs
0230 call 0x1536 ; _SeedRRand
0233 push 0
0235 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 568, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetSimCursor
023a add sp, 2
023d pop si
023e leave 
023f retf 
```

## Known declaration examples

- `extern void far InitSimVars(void);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_PrepareStrings-9dd732cc1e.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far SeedSRand(void);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimAllocate', 'offset': 576, 'source': 'src/recovered/SimAllocate.c', 'size': 1}
- {'symbol': '_PrepareStrings', 'offset': 578, 'source': 'src/recovered/wf_PrepareStrings-9dd732cc1e.c', 'size': 433}

# Recovery task _CustomerIDDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 227 bytes.

```asm
0000 enter 0x90, 0
0004 push di
0005 push si
0006 push 0
0008 push 0xa
000a push 0x83
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0012 add sp, 6
0015 mov di, ax
0017 push 0
0019 push 0xa
001b push 0x84
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0023 add sp, 6
0026 mov si, ax
0028 push di
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
002e add sp, 2
0031 mov word ptr [bp - 0x90], ax
0035 mov word ptr [bp - 0x8e], dx
0039 push <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003c push 0x8b3e
003f nop 
0040 push cs
0041 call 0x10a ; _DecodeString
0044 add sp, 4
0047 mov word ptr [bp - 0x8c], ax
004b mov word ptr [bp - 0x8a], dx
004f mov word ptr [bp - 0x88], 0x96f
0055 mov word ptr [bp - 0x86], ds
0059 push si
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
005f add sp, 2
0062 mov word ptr [bp - 0x84], ax
0066 mov word ptr [bp - 0x82], dx
006a mov es, word ptr [0xbf04]
006e push word ptr es:[0x7c0c]
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0078 add sp, 2
007b mov word ptr [bp - 0x80], ax
007e mov word ptr [bp - 0x7e], dx
0081 mov word ptr [bp - 0x7c], 0x971
0086 mov word ptr [bp - 0x7a], ds
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
008e push 1
0090 push 0
0092 push 6
0094 lea ax, [bp - 0x90]
0098 push ss
0099 push ax
009a nop 
009b push cs
009c call 0x62bc ; _PictureDialog
009f add sp, 0xa
00a2 push di
00a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00a8 add sp, 2
00ab push si
00ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00b1 add sp, 2
00b4 mov es, word ptr [0xbf04]
00b8 push word ptr es:[0x7c0c]
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 192, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00c2 add sp, 2
00c5 push 0xa
00c7 push 0x83
00ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 205, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
00cf add sp, 4
00d2 push 0xa
00d4 push 0x84
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
00dc add sp, 4
00df pop si
00e0 pop di
00e1 leave 
00e2 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far PictureDialog(char far * far *strings, int count, int picture, int force);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far db_PurgeObject(int object, int kind);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EndGameDialog', 'offset': 26114, 'source': None, 'size': 312}
- {'symbol': '_SpiderDialog', 'offset': 26426, 'source': None, 'size': 537}
- {'symbol': '_processEdit', 'offset': 27192, 'source': None, 'size': 1168}
- {'symbol': '_DoLaserFire', 'offset': 28360, 'source': None, 'size': 719}

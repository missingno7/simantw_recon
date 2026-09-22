# Recovery task _initControls

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 291 bytes.

```asm
0000 enter 8, 0
0004 push si
0005 push 0x578
0008 push <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000b push 0x9bce
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
0013 add sp, 6
0016 lea ax, [bp - 8]
0019 push ss
001a push ax
001b push 0x120d
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0023 add sp, 6
0026 mov ax, 1
0029 mov es, word ptr [0xc142]
002d mov word ptr es:[0x9fce], ax
0031 mov es, word ptr [0xc13c]
0035 mov word ptr es:[0x8630], ax
0039 mov es, word ptr [0xc146]
003d mov word ptr es:[0x7602], ax
0041 mov es, word ptr [0xc148]
0045 mov word ptr es:[0x8632], ax
0049 mov ax, 0xffff
004c mov es, word ptr [0xc14a]
0050 mov word ptr es:[0x72a0], ax
0054 mov es, word ptr [0xc14c]
0058 mov word ptr es:[0x9be4], ax
005c xor si, si
005e mov <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0061 mov ds, ax
0063 mov <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0066 mov es, ax
0068 mov ax, word ptr es:[si - 0x79ae]
006d mov <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0070 mov es, cx
0072 mov word ptr es:[si - 0x638c], ax
0077 mov <resolved loader operand; see bindings> ; [{'operand_offset': 120, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
007a mov es, cx
007c mov word ptr es:[si - 0x79a8], ax
0081 mov ax, word ptr [si - 0x79cc]
0085 mov <resolved loader operand; see bindings> ; [{'operand_offset': 134, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0088 mov es, cx
008a mov word ptr es:[si - 0x649c], ax
008f mov <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0092 mov es, cx
0094 mov word ptr es:[si - 0x79c6], ax
0099 add si, 2
009c cmp si, 6
009f jl 0xcce7
00a1 push ss
00a2 pop ds
00a3 nop 
00a4 push cs
00a5 call 0xb5b0 ; _win_ModeControlChanged
00a8 nop 
00a9 push cs
00aa call 0xb3bc ; _win_CasteControlChanged
00ad push 0
00af push -1
00b1 mov ax, 0x64
00b4 mov es, word ptr [0xc128]
00b8 mul word ptr es:[0x9b66]
00bd add ax, 0x3fff
00c0 adc dx, 0
00c3 push dx
00c4 push ax
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
00ca mov es, word ptr [0xc140]
00ce mov word ptr es:[0x8622], ax
00d2 push 0
00d4 push -1
00d6 mov ax, 0x64
00d9 mov es, word ptr [0xc128]
00dd mul word ptr es:[0x9b68]
00e2 add ax, 0x3fff
00e5 adc dx, 0
00e8 push dx
00e9 push ax
00ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 237, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
00ef mov es, word ptr [0xc140]
00f3 mov word ptr es:[0x8624], ax
00f7 push 0
00f9 push -1
00fb mov ax, 0x32
00fe mov es, word ptr [0xc128]
0102 mul word ptr es:[0x9b64]
0107 add ax, 0x3fff
010a adc dx, 0
010d push dx
010e push ax
010f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 274, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0114 mov es, word ptr [0xc140]
0118 mov word ptr es:[0x8626], ax
011c mov word ptr es:[0x8628], ax
0120 pop si
0121 leave 
0122 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far win_CasteControlChanged(void);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_ModeControlChanged(void);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetTriLatDist', 'offset': 51834, 'source': None, 'size': 299}
- {'symbol': '_SetTriLatPoint', 'offset': 52134, 'source': None, 'size': 221}
- {'symbol': '_DrawSimPayoff', 'offset': 52648, 'source': None, 'size': 401}
- {'symbol': '_AboutDialog', 'offset': 53050, 'source': None, 'size': 1192}

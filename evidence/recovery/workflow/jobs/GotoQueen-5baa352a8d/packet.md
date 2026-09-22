# Recovery task _GotoQueen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 420 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 xor si, si
0007 mov bx, word ptr [bp + 6]
000a mov <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
000d mov ds, ax
000f mov al, byte ptr [si + 0x3d18]
0013 and ax, 0xf8
0016 cmp ax, bx
0018 je 0xa964
001a inc si
001b cmp si, 0x1f4
001f jl 0xa921
0021 xor si, si
0023 mov al, byte ptr [si + 0x2f62]
0027 and ax, 0xf8
002a cmp ax, bx
002c je 0xa9b4
002e inc si
002f cmp si, 0x3e8
0033 jl 0xa935
0035 xor si, si
0037 mov al, byte ptr [si + 0x46e6]
003b and ax, 0xf8
003e cmp ax, bx
0040 jne 0xa957
0042 jmp 0xaa26
0045 inc si
0046 cmp si, 0x1f4
004a jl 0xa949
004c push ss
004d pop ds
004e pop si
004f leave 
0050 retf 
0051 nop 
0052 push ss
0053 pop ds
0054 mov es, word ptr [0xc0de]
0058 mov al, byte ptr es:[si + 0x3736]
005d sub ah, ah
005f mov word ptr [bp - 4], ax
0062 mov al, byte ptr es:[si + 0x392c]
0067 mov word ptr [bp - 2], ax
006a push 0x100
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0072 add sp, 2
0075 or ax, ax
0077 je 0xa9a1
0079 push word ptr [0xbca8]
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0082 add sp, 2
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
008a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
008f cmp word ptr [0xcc76], 2 ; _MapPlane
0094 je 0xa9f8
0096 push word ptr [bp - 2]
0099 push word ptr [bp - 4]
009c push 2
009e jmp 0xaa72
00a1 nop 
00a2 push ss
00a3 pop ds
00a4 mov es, word ptr [0xc0de]
00a8 mov al, byte ptr es:[si + 0x23a4]
00ad sub ah, ah
00af mov word ptr [bp - 4], ax
00b2 mov al, byte ptr es:[si + 0x278e]
00b7 mov word ptr [bp - 2], ax
00ba push 0x100
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 192, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00c2 add sp, 2
00c5 or ax, ax
00c7 je 0xa9f1
00c9 push word ptr [0xbca8]
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00d2 add sp, 2
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00df cmp word ptr [0xcc76], 1 ; _MapPlane
00e4 jne 0xaa1c
00e6 push word ptr [bp - 2]
00e9 push word ptr [bp - 4]
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
00f1 add sp, 4
00f4 or ax, ax
00f6 je 0xaa0f
00f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
00fd mov es, word ptr [0xc0f6]
0101 mov word ptr es:[0x72f0], 0
0108 jmp 0xaa8e
010a push word ptr [bp - 2]
010d push word ptr [bp - 4]
0110 push 1
0112 jmp 0xaa72
0114 push ss
0115 pop ds
0116 mov es, word ptr [0xc0de]
011a mov al, byte ptr es:[si + 0x4104]
011f sub ah, ah
0121 mov word ptr [bp - 4], ax
0124 mov al, byte ptr es:[si + 0x42fa]
0129 mov word ptr [bp - 2], ax
012c push 0x100
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0134 add sp, 2
0137 or ax, ax
0139 je 0xaa63
013b push word ptr [0xbca8]
013f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 322, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0144 add sp, 2
0147 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 330, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0151 cmp word ptr [0xcc76], 3 ; _MapPlane
0156 je 0xa9f8
0158 push word ptr [bp - 2]
015b push word ptr [bp - 4]
015e push 3
0160 nop 
0161 push cs
0162 call 0xa386 ; _SetMapPlaneLocation
0165 add sp, 6
0168 push 0x100
016b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 366, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0170 add sp, 2
0173 or ax, ax
0175 je 0xaa8e
0177 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 378, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
017c push 0x100
017f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 386, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0184 add sp, 2
0187 or ax, ax
0189 je 0xaab3
018b push word ptr [0xbca8]
018f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 402, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0194 add sp, 2
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapCursor
019c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 415, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01a1 pop si
01a2 leave 
01a3 retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlaneLocation(int plane, int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GotoMyAnt', 'offset': 42852, 'source': None, 'size': 224}
- {'symbol': '_GotoSpider', 'offset': 43076, 'source': None, 'size': 205}
- {'symbol': '_GotoBQueen', 'offset': 43702, 'source': None, 'size': 205}
- {'symbol': '_GotoRQueen', 'offset': 43908, 'source': 'src/recovered/GotoRQueen.c', 'size': 12}

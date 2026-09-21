# Recovery task _ExpAddAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 266 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 push 8
0007 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 10, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
000c add sp, 2
000f add ax, 0x10
0012 mov word ptr [bp - 2], ax
0015 mov es, word ptr [0xc270]
0019 cmp byte ptr es:[0x8603], 1
001f jne 0x7a22
0021 add word ptr [bp - 2], 0x80
0026 mov ax, word ptr [0xcc76] ; _MapPlane
0029 or ax, ax
002b jge 0x7a2c
002d jmp 0x7af5
0030 jno 0x7a31
0032 jmp 0x7af5
0035 dec ax
0036 jle 0x7a3e
0038 dec ax
0039 je 0x7a6a
003b dec ax
003c je 0x7ab0
003e jmp 0x7af5
0041 nop 
0042 push word ptr [bp + 8]
0045 push word ptr [bp + 6]
0048 push 1
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
004f add sp, 6
0052 or ax, ax
0054 jne 0x7a55
0056 jmp 0x7b03
0059 push 0
005b push 2
005d push word ptr [bp - 2]
0060 push word ptr [bp + 8]
0063 push word ptr [bp + 6]
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToAList
006b jmp 0x7af2
006e cmp word ptr [bp + 8], 0
0072 jne 0x7a73
0074 jmp 0x7b03
0077 mov si, word ptr [bp + 6]
007a shl si, 6
007d mov bx, word ptr [bp + 8]
0080 cmp byte ptr [bx + si + 0x48e8], 0x1c
0085 jb 0x7a8f
0087 push bx
0088 push word ptr [bp + 6]
008b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
0090 add sp, 4
0093 cmp word ptr [bp - 2], 0x80
0098 jle 0x7a9c
009a push 0
009c push 7
009e jmp 0x7aa0
00a0 push 0
00a2 push 2
00a4 push word ptr [bp - 2]
00a7 push word ptr [bp + 8]
00aa push word ptr [bp + 6]
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
00b2 jmp 0x7af2
00b4 cmp word ptr [bp + 8], 0
00b8 je 0x7b03
00ba mov si, word ptr [bp + 6]
00bd shl si, 6
00c0 mov bx, word ptr [bp + 8]
00c3 cmp byte ptr [bx + si + 0x58e8], 0x1c
00c8 jb 0x7ad2
00ca push bx
00cb push word ptr [bp + 6]
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
00d3 add sp, 4
00d6 cmp word ptr [bp - 2], 0x80
00db jle 0x7ae0
00dd push 0
00df push 2
00e1 jmp 0x7ae4
00e3 nop 
00e4 push 0
00e6 push 7
00e8 push word ptr [bp - 2]
00eb push word ptr [bp + 8]
00ee push word ptr [bp + 6]
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
00f6 add sp, 0xa
00f9 push 0x7e
00fb push 0
00fd push 0x1c
00ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 258, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0104 add sp, 6
0107 pop si
0108 leave 
0109 retf 
```

## Known declaration examples

- `extern void far AddAntToAList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearLifeB', 'offset': 31060, 'source': 'src/recovered/wf_ClearLifeB-f9a6e1c57a.c', 'size': 83}
- {'symbol': '_ClearLifeR', 'offset': 31144, 'source': 'src/recovered/wf_ClearLifeR-d74962e731.c', 'size': 83}
- {'symbol': '_ExpAddFood', 'offset': 31494, 'source': 'src/recovered/wf_ExpAddFood-cd1bed365e.c', 'size': 152}
- {'symbol': '_ExpIncSmell', 'offset': 31646, 'source': None, 'size': 445}

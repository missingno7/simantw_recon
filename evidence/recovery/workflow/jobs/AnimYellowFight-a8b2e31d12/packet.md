# Recovery task _AnimYellowFight

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 545 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 mov si, word ptr [bp + 8]
000c push 0xff
000f push word ptr [0xcf50] ; _MeDir
0013 push word ptr [0xcc84] ; _MeType
0017 push word ptr [0xce7e] ; _MeLocY
001b push word ptr [0xcd88] ; _MeLocX
001f push word ptr [0xce80] ; _MePlane
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0028 add sp, 0xc
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
0030 mov ax, word ptr [bp + 6]
0033 mov word ptr [bp - 0x14], ax
0036 mov word ptr [bp - 0x12], si
0039 mov word ptr [bp - 0xc], di
003c mov ax, word ptr [0xcc84] ; _MeType
003f mov word ptr [bp - 0xe], ax
0042 mov ax, word ptr [bp + 0xc]
0045 mov word ptr [bp - 0x10], ax
0048 cmp word ptr [bp + 0x10], 0
004c jne 0x7eaa
004e mov ax, 6
0051 jmp 0x7ecf
0053 nop 
0054 push 0
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
005b add sp, 2
005e or ax, ax
0060 je 0x7ecc
0062 mov es, word ptr [0xc3d4]
0066 cmp word ptr es:[0x85f4], 1
006c sbb ax, ax
006e and al, 0xe0
0070 add ax, 0x40
0073 jmp 0x7ecf
0075 nop 
0076 mov ax, 8
0079 mov word ptr [bp - 8], ax
007c cmp word ptr [bp + 0x10], 0xa
0080 jne 0x7eeb
0082 mov bx, si
0084 shl bx, 6
0087 mov al, byte ptr [bx + di + 0x28e8]
008b sub ah, ah
008d mov word ptr [bp - 6], ax
0090 mov word ptr [bp - 8], 0x20
0095 cmp word ptr [bp + 0x10], 2
0099 jne 0x7ef6
009b mov word ptr [bp - 0x16], 3
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00a5 mov word ptr [bp - 4], ax
00a8 mov word ptr [bp - 2], dx
00ab mov word ptr [bp - 0xa], 0
00b0 cmp word ptr [bp - 8], 0
00b4 jg 0x7f0f
00b6 jmp 0x8027
00b9 mov ax, si
00bb shl ax, 6
00be add ax, di
00c0 add ax, 0x28e8
00c3 mov word ptr [bp - 0x18], ax
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00cb cmp dx, word ptr [bp - 2]
00ce jg 0x7f4a
00d0 jl 0x7f2d
00d2 cmp ax, word ptr [bp - 4]
00d5 ja 0x7f4a
00d7 push 0
00d9 push 1
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myDelay
00e0 add sp, 4
00e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 230, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00e8 cmp dx, word ptr [bp - 2]
00eb jl 0x7f2d
00ed jg 0x7f4a
00ef cmp ax, word ptr [bp - 4]
00f2 jbe 0x7f2d
00f4 mov di, word ptr [bp + 0x10]
00f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 250, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00fc add ax, 6
00ff adc dx, 0
0102 mov word ptr [bp - 4], ax
0105 mov word ptr [bp - 2], dx
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
010d or di, di
010f jne 0x7f7f
0111 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 276, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0116 or ax, ax
0118 je 0x7f7f
011a push 0x7e
011c push 0x32c8
011f push 0x25
0121 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 292, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0126 add sp, 6
0129 cmp di, 0xa
012c jne 0x7fac
012e push 0x7f
0130 push 0x55f0
0133 push 0x31
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 312, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
013a add sp, 6
013d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0142 or ax, ax
0144 je 0x7fa4
0146 mov al, byte ptr [bp - 6]
0149 sub al, 3
014b jmp 0x7fa7
014d nop 
014e mov al, byte ptr [bp - 6]
0151 mov bx, word ptr [bp - 0x18]
0154 mov byte ptr [bx], al
0156 or di, di
0158 je 0x7fca
015a cmp di, 0xa
015d jge 0x7fca
015f mov es, word ptr [0xc3d4]
0163 cmp word ptr es:[0x85f4], 0
0169 je 0x7fca
016b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 366, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySongIsDone
0170 or ax, ax
0172 jne 0x8027
0174 cmp di, 2
0177 jne 0x7ffa
0179 mov si, word ptr [bp - 0x16]
017c lea ax, [si + 0x38]
017f push ax
0180 push word ptr [bp + 0xa]
0183 push word ptr [bp + 8]
0186 push word ptr [bp + 6]
0189 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 396, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
018e add sp, 8
0191 cmp si, 5
0194 jge 0x7ff2
0196 inc si
0197 mov word ptr [bp - 0x16], si
019a jmp 0x7ffa
019c cmp si, 3
019f jle 0x7ffa
01a1 dec si
01a2 jmp 0x7fed
01a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01a9 push ax
01aa push word ptr [bp + 0xe]
01ad push word ptr [bp + 0xa]
01b0 push word ptr [bp + 8]
01b3 push word ptr [bp + 6]
01b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 441, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MoveMyLife
01bb add sp, 0xa
01be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 449, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
01c3 mov ax, word ptr [bp - 8]
01c6 inc word ptr [bp - 0xa]
01c9 cmp word ptr [bp - 0xa], ax
01cc jge 0x8027
01ce jmp 0x7f1c
01d1 cmp word ptr [bp + 0x10], 0xa
01d5 jne 0x803d
01d7 mov al, byte ptr [bp - 6]
01da mov si, word ptr [bp + 8]
01dd shl si, 6
01e0 mov bx, word ptr [bp + 0xa]
01e3 mov byte ptr [bx + si + 0x28e8], al
01e7 push word ptr [0xcf50] ; _MeDir
01eb push word ptr [bp + 0xe]
01ee push word ptr [bp + 0xa]
01f1 push word ptr [bp + 8]
01f4 push word ptr [bp + 6]
01f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 506, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
01fc add sp, 0xa
01ff mov ax, word ptr [bp - 0x14]
0202 mov word ptr [0xce80], ax ; _MePlane
0205 mov ax, word ptr [bp - 0x12]
0208 mov word ptr [0xcd88], ax ; _MeLocX
020b mov ax, word ptr [bp - 0xc]
020e mov word ptr [0xce7e], ax ; _MeLocY
0211 mov ax, word ptr [bp - 0xe]
0214 mov word ptr [0xcc84], ax ; _MeType
0217 mov ax, word ptr [bp - 0x10]
021a mov word ptr [0xcf50], ax ; _MeDir
021d pop si
021e pop di
021f leave 
0220 retf 
```

## Known declaration examples

- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_EnterNest-606488b329.c
- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern void far DoEditUpdateDraw(void);` — src/recovered/DoEditAndMapUpdateDraw.c
- `extern unsigned long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near MeDir;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeDir;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SetMap(int plane, int x, int y, int value);` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_EnterNest-606488b329.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntMoveY', 'offset': 30196, 'source': None, 'size': 1793}
- {'symbol': '_DoAntSimY', 'offset': 31990, 'source': None, 'size': 351}
- {'symbol': '_AnimYellowInsane', 'offset': 32888, 'source': None, 'size': 454}
- {'symbol': '_YellowFight', 'offset': 33342, 'source': None, 'size': 457}

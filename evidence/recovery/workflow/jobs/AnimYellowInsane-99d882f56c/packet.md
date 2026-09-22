# Recovery task _AnimYellowInsane

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 454 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 push ds
0007 push 0x22f6
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
000f add sp, 4
0012 push 0xff
0015 push word ptr [0xcf50] ; _MeDir
0019 push word ptr [0xcc84] ; _MeType
001d push word ptr [0xce7e] ; _MeLocY
0021 push word ptr [0xcd88] ; _MeLocX
0025 push word ptr [0xce80] ; _MePlane
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
002e add sp, 0xc
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
0036 mov ax, word ptr [bp + 6]
0039 mov word ptr [bp - 0x14], ax
003c mov di, word ptr [bp + 8]
003f mov ax, word ptr [bp + 0xa]
0042 mov word ptr [bp - 0xc], ax
0045 mov ax, word ptr [0xcc84] ; _MeType
0048 mov word ptr [bp - 0x10], ax
004b mov ax, word ptr [bp + 0xc]
004e mov word ptr [bp - 0x12], ax
0051 push 0
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0058 add sp, 2
005b cmp ax, 1
005e sbb si, si
0060 and si, 0xffe8
0063 add si, 0x20
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
006b mov word ptr [bp - 4], ax
006e mov word ptr [bp - 2], dx
0071 mov word ptr [bp - 8], 0
0076 mov word ptr [bp - 0xe], di
0079 mov word ptr [bp - 0xa], si
007c jmp 0x81ed
007f nop 
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0085 cmp dx, word ptr [bp - 2]
0088 jg 0x8126
008a jl 0x8109
008c cmp ax, word ptr [bp - 4]
008f ja 0x8126
0091 push 0
0093 push 1
0095 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myDelay
009a add sp, 4
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00a2 cmp dx, word ptr [bp - 2]
00a5 jl 0x8109
00a7 jg 0x8126
00a9 cmp ax, word ptr [bp - 4]
00ac jbe 0x8109
00ae mov di, word ptr [bp + 0xa]
00b1 mov si, word ptr [bp + 8]
00b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00b9 add ax, 3
00bc adc dx, 0
00bf mov word ptr [bp - 4], ax
00c2 mov word ptr [bp - 2], dx
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
00ca push word ptr [bp - 0xc]
00cd push word ptr [bp - 0xe]
00d0 push di
00d1 push si
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
00d7 add sp, 8
00da or ax, ax
00dc jne 0x8182
00de mov ax, word ptr [bp - 0xa]
00e1 sub ax, word ptr [bp - 8]
00e4 dec ax
00e5 je 0x8182
00e7 push 7
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
00ee add sp, 2
00f1 add ax, di
00f3 sub ax, 3
00f6 push ax
00f7 push 7
00f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 252, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
00fe add sp, 2
0101 add ax, si
0103 sub ax, 3
0106 push ax
0107 jmp 0x8188
0109 nop 
010a push word ptr [bp - 0xc]
010d push word ptr [bp - 0xe]
0110 push di
0111 push si
0112 push word ptr [bp + 6]
0115 nop 
0116 push cs
0117 call 0x405e ; _GetBestDir
011a add sp, 0xa
011d mov word ptr [bp - 6], ax
0120 or ax, ax
0122 jl 0x81b8
0124 mov es, word ptr [0xc3ca]
0128 mov bx, ax
012a mov al, byte ptr es:[bx]
012f cwde 
0130 add si, ax
0132 mov es, word ptr [0xc3c4]
0136 mov al, byte ptr es:[bx + 8]
013b cwde 
013c add di, ax
013e jmp 0x81c0
0140 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 323, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0145 mov word ptr [bp - 6], ax
0148 push word ptr [bp - 6]
014b push word ptr [bp + 0xe]
014e push di
014f push si
0150 push word ptr [bp + 6]
0153 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 342, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MoveMyLife
0158 add sp, 0xa
015b push ds
015c push 0x2307
015f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 354, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0164 add sp, 4
0167 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 362, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
016c inc word ptr [bp - 8]
016f mov word ptr [bp + 8], si
0172 mov word ptr [bp + 0xa], di
0175 mov ax, word ptr [bp - 8]
0178 cmp word ptr [bp - 0xa], ax
017b jle 0x81f8
017d jmp 0x80f8
0180 push word ptr [0xcf50] ; _MeDir
0184 push word ptr [bp + 0xe]
0187 push word ptr [bp + 0xa]
018a push word ptr [bp + 8]
018d push word ptr [bp + 6]
0190 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
0195 add sp, 0xa
0198 mov ax, word ptr [bp - 0x14]
019b mov word ptr [0xce80], ax ; _MePlane
019e mov ax, word ptr [bp - 0xe]
01a1 mov word ptr [0xcd88], ax ; _MeLocX
01a4 mov ax, word ptr [bp - 0xc]
01a7 mov word ptr [0xce7e], ax ; _MeLocY
01aa mov ax, word ptr [bp - 0x10]
01ad mov word ptr [0xcc84], ax ; _MeType
01b0 mov ax, word ptr [bp - 0x12]
01b3 mov word ptr [0xcf50], ax ; _MeDir
01b6 push ds
01b7 push 0x2309
01ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 445, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01bf add sp, 4
01c2 pop si
01c3 pop di
01c4 leave 
01c5 retf 
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
- `extern int far RRand(int range);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int far RRand(int range);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_EnterNest-606488b329.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntSimY', 'offset': 31990, 'source': None, 'size': 351}
- {'symbol': '_AnimYellowFight', 'offset': 32342, 'source': None, 'size': 545}
- {'symbol': '_YellowFight', 'offset': 33342, 'source': None, 'size': 457}
- {'symbol': '_EnterNest', 'offset': 33800, 'source': 'src/recovered/wf_EnterNest-606488b329.c', 'size': 155}

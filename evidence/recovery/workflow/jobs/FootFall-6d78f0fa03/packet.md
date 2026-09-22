# Recovery task _FootFall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 339 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 push 0x14
0008 push 0
000a push 0x23
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0011 add sp, 6
0014 mov es, word ptr [0xc500]
0018 test byte ptr es:[0x8a72], 1
001e je 0x33b4
0020 mov bx, word ptr [bp + 6]
0023 lea cx, [bx + 0x10]
0026 mov di, word ptr [bp + 8]
0029 add di, 6
002c jmp 0x33c0
002e mov bx, word ptr [bp + 6]
0031 lea cx, [bx + 6]
0034 mov di, word ptr [bp + 8]
0037 add di, 0x10
003a mov dx, bx
003c mov word ptr [bp - 6], di
003f cmp cx, bx
0041 jg 0x33cc
0043 jmp 0x3486
0046 mov word ptr [bp - 0xa], cx
0049 mov ax, bx
004b shl ax, 6
004e mov word ptr [bp - 8], ax
0051 mov ax, word ptr [bp + 8]
0054 mov si, ax
0056 cmp word ptr [bp - 6], ax
0059 jg 0x33e8
005b mov di, word ptr [bp - 8]
005e jmp 0x3474
0061 nop 
0062 mov di, word ptr [bp - 8]
0065 mov word ptr [bp - 4], dx
0068 or di, di
006a jl 0x3468
006c cmp di, 0x1fc0
0070 jg 0x3468
0072 or si, si
0074 jl 0x3468
0076 cmp si, 0x7f
0079 jg 0x3468
007b mov bx, di
007d add bx, si
007f mov al, byte ptr [bx + 0x68e8]
0083 sub ah, ah
0085 mov word ptr [bp - 2], ax
0088 or ax, ax
008a je 0x3468
008c push ax
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0092 add sp, 2
0095 or ax, ax
0097 jne 0x345e
0099 push si
009a push word ptr [bp - 4]
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
00a2 add sp, 4
00a5 mov word ptr [bp - 2], ax
00a8 or ax, ax
00aa jl 0x3468
00ac mov es, word ptr [0xc54a]
00b0 mov bx, ax
00b2 mov al, byte ptr es:[bx + 0x2f62]
00b7 and ax, 0x80
00ba push ax
00bb push si
00bc push word ptr [bp - 4]
00bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _DeadAntHere
00c4 add sp, 6
00c7 mov es, word ptr [0xc54a]
00cb mov bx, word ptr [bp - 2]
00ce mov byte ptr es:[bx + 0x2f62], 0
00d4 jmp 0x3468
00d6 nop 
00d7 nop 
00d8 push 5
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
00df add sp, 2
00e2 inc si
00e3 cmp si, word ptr [bp - 6]
00e6 jge 0x3471
00e8 jmp 0x33ee
00eb mov dx, word ptr [bp - 4]
00ee add di, 0x40
00f1 mov word ptr [bp - 8], di
00f4 inc dx
00f5 cmp dx, word ptr [bp - 0xa]
00f8 jge 0x3483
00fa jmp 0x33d7
00fd mov cx, word ptr [bp - 0xa]
0100 mov <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0103 mov es, ax
0105 mov ax, word ptr es:[0x78b8]
0109 cmp ax, word ptr [bp + 6]
010c jl 0x34b1
010e cmp ax, cx
0110 jge 0x34b1
0112 mov <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0115 mov es, ax
0117 mov ax, word ptr [bp + 8]
011a cmp word ptr es:[0x78ea], ax
011f jl 0x34b1
0121 mov ax, word ptr [bp - 6]
0124 cmp word ptr es:[0x78ea], ax
0129 jl 0x34b8
012b push ss
012c pop ds
012d pop si
012e pop di
012f leave 
0130 retf 
0131 nop 
0132 push ss
0133 pop ds
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _KillSpider
0139 mov es, word ptr [0xc544]
013d cmp word ptr es:[0x9fe8], 1
0143 jne 0x34d5
0145 push 5
0147 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 330, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
014c add sp, 2
014f pop si
0150 pop di
0151 leave 
0152 retf 
```

## Known declaration examples

- `extern int far FindInAList(int x, int y);` — src/recovered/wf_tu_simant1_0000_DoSmells_10_scaffold-13ce956607.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_9_scaffold-03367c8694.c
- `extern void far YellowDeath(int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_11_scaffold-950e5ffcca.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FollowCatDir', 'offset': 12966, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c', 'size': 67}
- {'symbol': '_MakeBark', 'offset': 13034, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c', 'size': 155}
- {'symbol': '_MowerFall', 'offset': 13530, 'source': None, 'size': 166}
- {'symbol': '_MaintainSwarm', 'offset': 13696, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c', 'size': 119}

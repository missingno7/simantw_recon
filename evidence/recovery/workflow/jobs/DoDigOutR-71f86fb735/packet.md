# Recovery task _DoDigOutR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 656 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov al, byte ptr [bp + 0xa]
000c and ax, 7
000f push ax
0010 push word ptr [bp + 8]
0013 push di
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirR
0019 add sp, 6
001c mov si, ax
001e or si, si
0020 jle 0x7250
0022 dec si
0023 jmp 0x725f
0025 nop 
0026 mov al, byte ptr [bp + 0xa]
0029 and ax, 7
002c push ax
002d call 0x2a22 ; _RandTurn
0030 add sp, 2
0033 mov si, ax
0035 mov al, byte ptr [bp + 0xa]
0038 and ax, 0xf8
003b or ax, si
003d mov word ptr [bp - 0xc], ax
0040 mov bx, di
0042 shl bx, 6
0045 add bx, word ptr [bp + 8]
0048 mov word ptr [bp - 0x10], bx
004b mov byte ptr [bx - 0x6718], al
004f mov bx, 0x9b6a
0052 mov es, word ptr [0xc384]
0056 mov word ptr [bp - 0x14], bx
0059 mov word ptr [bp - 0x12], es
005c mov bx, word ptr es:[bx]
005f mov es, word ptr [0xc386]
0063 mov byte ptr es:[bx + 0x46e6], al
0068 mov es, word ptr [0xc398]
006c mov al, byte ptr es:[si]
0071 cwde 
0072 add ax, di
0074 mov word ptr [bp - 6], ax
0077 mov es, word ptr [0xc396]
007b mov al, byte ptr es:[si + 8]
0080 cwde 
0081 mov cx, ax
0083 add cx, word ptr [bp + 8]
0086 cmp word ptr [bp - 6], 0
008a jge 0x72b9
008c jmp 0x74b6
008f mov word ptr [bp - 0xe], si
0092 cmp word ptr [bp - 6], 0x3f
0096 jle 0x72c5
0098 jmp 0x74b6
009b cmp cx, 0x3f
009e jle 0x72cd
00a0 jmp 0x74b6
00a3 cmp cx, 1
00a6 jge 0x72e0
00a8 push di
00a9 nop 
00aa push cs
00ab call 0x74ba ; _GetOutR
00ae add sp, 2
00b1 pop si
00b2 pop di
00b3 leave 
00b4 retf 
00b5 nop 
00b6 mov si, word ptr [bp + 8]
00b9 mov bx, word ptr [bp - 6]
00bc shl bx, 6
00bf add bx, cx
00c1 mov word ptr [bp - 0x16], bx
00c4 cmp byte ptr [bx + 0x58e8], 0x30
00c9 jb 0x7354
00cb mov es, word ptr [0xc386]
00cf mov bx, word ptr [bp - 0x10]
00d2 cmp byte ptr es:[bx + 0x13a4], 0
00d8 je 0x7309
00da dec byte ptr es:[bx + 0x13a4]
00df mov cl, byte ptr [bp + 0xa]
00e2 and cx, 0x78
00e5 sar cx, 3
00e8 cmp cx, 5
00eb je 0x731c
00ed cmp cx, 9
00f0 jne 0x7332
00f2 les bx, ptr [bp - 0x14]
00f5 mov bx, word ptr es:[bx]
00f8 mov es, word ptr [0xc386]
00fc sub byte ptr es:[bx + 0x46e6], 0x18
0102 mov byte ptr es:[bx + 0x44f0], 4
0108 cmp cx, 2
010b je 0x733f
010d cmp cx, 6
0110 je 0x733f
0112 jmp 0x74b6
0115 les bx, ptr [bp - 0x14]
0118 mov bx, word ptr es:[bx]
011b mov es, word ptr [0xc386]
011f mov byte ptr es:[bx + 0x44f0], 4
0125 pop si
0126 pop di
0127 leave 
0128 retf 
0129 nop 
012a mov word ptr [bp - 4], cx
012d mov al, byte ptr [bx + 0x58e8]
0131 sub ah, ah
0133 push ax
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDirt
0139 add sp, 2
013c or ax, ax
013e je 0x736d
0140 jmp 0x74b6
0143 mov bx, word ptr [bp - 0x10]
0146 mov byte ptr [bx - 0x6718], 0
014b mov bx, word ptr [bp - 0x16]
014e mov al, byte ptr [bx - 0x6718]
0152 sub ah, ah
0154 mov word ptr [bp - 2], ax
0157 cmp ax, 7
015a jle 0x73da
015c cmp ax, 0x68
015f jge 0x73da
0161 push ax
0162 push word ptr [bp - 4]
0165 push word ptr [bp - 6]
0168 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 363, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
016d add sp, 6
0170 mov word ptr [bp - 8], ax
0173 or ax, ax
0175 jl 0x7400
0177 push word ptr [bp - 0xc]
017a push word ptr [bp - 2]
017d call 0x26f4 ; _GetWinner
0180 add sp, 4
0183 mov es, word ptr [0xc386]
0187 mov bx, word ptr [bp - 8]
018a mov byte ptr es:[bx + 0x48dc], al
018f and al, 0x80
0191 add al, 0x70
0193 mov byte ptr es:[bx + 0x46e6], al
0198 mov bx, word ptr [bp - 0x16]
019b mov byte ptr [bx - 0x6718], al
019f mov bx, word ptr [bp - 8]
01a2 mov byte ptr es:[bx + 0x44f0], 0xa
01a8 mov word ptr [bp - 0xa], 1
01ad jmp 0x7405
01af nop 
01b0 push ax
01b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 436, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
01b6 add sp, 2
01b9 or ax, ax
01bb je 0x7400
01bd cmp word ptr [0xce98], 0 ; _MeColor
01c2 jne 0x7400
01c4 les bx, ptr [bp - 0x14]
01c7 push word ptr es:[bx]
01ca push 3
01cc nop 
01cd push cs
01ce call 0x823e ; _YellowFight
01d1 add sp, 4
01d4 jmp 0x73d2
01d6 mov word ptr [bp - 0xa], 0
01db cmp word ptr [bp - 0xa], 0
01df je 0x740e
01e1 jmp 0x74b6
01e4 les bx, ptr [bp - 0x14]
01e7 mov bx, word ptr es:[bx]
01ea mov es, word ptr [0xc386]
01ee mov al, byte ptr es:[bx + 0x46e6]
01f3 mov cx, bx
01f5 mov bx, word ptr [bp - 0x16]
01f8 and al, 0xf8
01fa or al, byte ptr [bp - 0xe]
01fd mov byte ptr [bx - 0x6718], al
0201 mov bx, cx
0203 mov byte ptr es:[bx + 0x46e6], al
0208 mov al, byte ptr [bp - 6]
020b mov byte ptr es:[bx + 0x4104], al
0210 mov al, byte ptr [bp - 4]
0213 mov byte ptr es:[bx + 0x42fa], al
0218 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 539, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
021d cmp ax, word ptr [0xac88] ; _HealthR
0221 jle 0x74b6
0223 mov bx, word ptr [bp - 0x10]
0226 mov dl, byte ptr [bx + 0x58e8]
022a sub dh, dh
022c cmp dx, 0x10
022f jl 0x74b6
0231 cmp dx, 0x13
0234 jg 0x74b6
0236 cmp dx, 0x10
0239 jne 0x7474
023b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 574, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0240 mov bx, word ptr [bp - 0x10]
0243 mov byte ptr [bx + 0x58e8], al
0247 jmp 0x7478
0249 nop 
024a dec byte ptr [bx + 0x58e8]
024e mov es, word ptr [0xc394]
0252 cmp word ptr es:[0x72de], 0
0258 jle 0x7489
025a dec word ptr es:[0x72de]
025f mov ax, word ptr [0xac84] ; _RpopT
0262 add ax, word ptr [0xaca4]
0266 sar ax, 4
0269 mov es, word ptr [0xc3a4]
026d add word ptr es:[0x7c8e], 5
0273 cmp ax, word ptr es:[0x7c8e]
0278 jge 0x74b6
027a mov word ptr es:[0x7c8e], 0
0281 cmp word ptr [0xac88], 0x64 ; _HealthR
0286 jge 0x74b6
0288 inc word ptr [0xac88] ; _HealthR
028c pop si
028d pop di
028e leave 
028f retf 
```

## Known declaration examples

- `extern int far FindInRList(int x, int y, int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far GetExitDirR(int x, int y, int limit);` — src/recovered/wf_RaidOutR-a39ba19d03.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near HealthR;` — src/recovered/DecEatR.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near MeColor;` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near RpopT;` — src/recovered/DecEatR.c
- `extern int near RpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandR-fc777553ef.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoFoodInR', 'offset': 27788, 'source': None, 'size': 640}
- {'symbol': '_DoDigInR', 'offset': 28428, 'source': None, 'size': 798}
- {'symbol': '_GetOutR', 'offset': 29882, 'source': None, 'size': 314}
- {'symbol': '_DoAntMoveY', 'offset': 30196, 'source': None, 'size': 1793}

# Recovery task _DoFoodInR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 640 bytes.

```asm
0000 enter 0x1c, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 mov al, byte ptr [bp + 0xa]
000c and ax, 7
000f push ax
0010 push si
0011 push word ptr [bp + 6]
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirR
0019 add sp, 6
001c mov word ptr [bp - 6], ax
001f or ax, ax
0021 jge 0x6cb2
0023 jmp 0x6e2e
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
002b or ax, ax
002d jne 0x6cbe
002f jmp 0x6e2e
0032 mov al, byte ptr [bp + 0xa]
0035 and ax, 0xf8
0038 or ax, word ptr [bp - 6]
003b mov word ptr [bp - 0xa], ax
003e mov bx, word ptr [bp + 6]
0041 shl bx, 6
0044 mov byte ptr [bx + si - 0x6718], al
0048 mov bx, 0x9b6a
004b mov es, word ptr [0xc384]
004f mov word ptr [bp - 0x10], bx
0052 mov word ptr [bp - 0xe], es
0055 mov bx, word ptr es:[bx]
0058 mov es, word ptr [0xc386]
005c mov byte ptr es:[bx + 0x46e6], al
0061 mov es, word ptr [0xc398]
0065 mov bx, word ptr [bp - 6]
0068 mov al, byte ptr es:[bx]
006d cwde 
006e add ax, word ptr [bp + 6]
0071 mov word ptr [bp - 4], ax
0074 mov es, word ptr [0xc396]
0078 mov al, byte ptr es:[bx + 8]
007d cwde 
007e mov di, ax
0080 add di, si
0082 cmp word ptr [bp - 4], 0x3f
0086 jle 0x6d17
0088 jmp 0x6f08
008b cmp word ptr [bp - 4], 0
008f jge 0x6d20
0091 jmp 0x6f08
0094 cmp di, 0x3f
0097 jle 0x6d28
0099 jmp 0x6f08
009c cmp di, 1
009f jge 0x6d3c
00a1 push word ptr [bp + 6]
00a4 nop 
00a5 push cs
00a6 call 0x74ba ; _GetOutR
00a9 add sp, 2
00ac pop si
00ad pop di
00ae leave 
00af retf 
00b0 mov si, word ptr [bp - 4]
00b3 mov bx, si
00b5 shl bx, 6
00b8 add bx, di
00ba mov word ptr [bp - 0x12], bx
00bd cmp byte ptr [bx + 0x58e8], 0x30
00c2 jb 0x6d53
00c4 jmp 0x6f08
00c7 mov bx, word ptr [bp + 6]
00ca shl bx, 6
00cd add bx, word ptr [bp + 8]
00d0 mov byte ptr [bx - 0x6718], 0
00d5 mov bx, word ptr [bp - 0x12]
00d8 mov al, byte ptr [bx - 0x6718]
00dc sub ah, ah
00de mov word ptr [bp - 2], ax
00e1 cmp ax, 7
00e4 jle 0x6dc2
00e6 cmp ax, 0x68
00e9 jge 0x6dc2
00eb push ax
00ec push di
00ed push si
00ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 241, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
00f3 add sp, 6
00f6 mov word ptr [bp - 8], ax
00f9 or ax, ax
00fb jl 0x6de8
00fd push word ptr [bp - 0xa]
0100 push word ptr [bp - 2]
0103 call 0x26f4 ; _GetWinner
0106 add sp, 4
0109 mov es, word ptr [0xc386]
010d mov bx, word ptr [bp - 8]
0110 mov byte ptr es:[bx + 0x48dc], al
0115 and al, 0x80
0117 add al, 0x70
0119 mov byte ptr es:[bx + 0x46e6], al
011e mov bx, word ptr [bp - 0x12]
0121 mov byte ptr [bx - 0x6718], al
0125 mov bx, word ptr [bp - 8]
0128 mov byte ptr es:[bx + 0x44f0], 0xa
012e mov word ptr [bp - 0xc], 1
0133 jmp 0x6ded
0135 nop 
0136 push ax
0137 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
013c add sp, 2
013f or ax, ax
0141 je 0x6de8
0143 cmp word ptr [0xce98], 0 ; _MeColor
0148 jne 0x6de8
014a les bx, ptr [bp - 0x10]
014d push word ptr es:[bx]
0150 push 3
0152 nop 
0153 push cs
0154 call 0x823e ; _YellowFight
0157 add sp, 4
015a jmp 0x6dba
015c mov word ptr [bp - 0xc], 0
0161 cmp word ptr [bp - 0xc], 0
0165 je 0x6df6
0167 jmp 0x6f08
016a les bx, ptr [bp - 0x10]
016d mov bx, word ptr es:[bx]
0170 mov es, word ptr [0xc386]
0174 mov cl, byte ptr es:[bx + 0x46e6]
0179 and cx, 0xf8
017d or cx, word ptr [bp - 6]
0180 mov byte ptr es:[bx + 0x46e6], cl
0185 mov ax, bx
0187 mov bx, word ptr [bp - 0x12]
018a mov byte ptr [bx - 0x6718], cl
018e mov bx, ax
0190 mov cx, si
0192 mov byte ptr es:[bx + 0x4104], cl
0197 mov cx, di
0199 mov byte ptr es:[bx + 0x42fa], cl
019e pop si
019f pop di
01a0 leave 
01a1 retf 
01a2 mov di, word ptr [bp + 6]
01a5 mov bx, di
01a7 shl bx, 6
01aa add bx, si
01ac add bx, 0x58e8
01b0 mov word ptr [bp - 0x14], bx
01b3 mov dl, byte ptr [bx]
01b5 sub dh, dh
01b7 cmp dx, 0x10
01ba jge 0x6e4e
01bc mov byte ptr [bx], 0x10
01bf jmp 0x6e55
01c1 nop 
01c2 cmp dx, 0x13
01c5 jge 0x6e55
01c7 inc byte ptr [bx]
01c9 mov bx, 0x72de
01cc mov es, word ptr [0xc394]
01d0 mov word ptr [bp - 0x18], bx
01d3 mov word ptr [bp - 0x16], es
01d6 inc word ptr es:[bx]
01d9 mov bx, 0x9b6a
01dc mov es, word ptr [0xc384]
01e0 mov word ptr [bp - 0x10], bx
01e3 mov word ptr [bp - 0xe], es
01e6 mov bx, word ptr es:[bx]
01e9 add bx, 0x46e6
01ed mov es, word ptr [0xc386]
01f1 test byte ptr es:[bx], 8
01f5 je 0x6e87
01f7 sub byte ptr es:[bx], 8
01fb push 0x64
01fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 512, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0202 add sp, 2
0205 cmp ax, word ptr [0xac88] ; _HealthR
0209 jle 0x6ee7
020b mov bx, word ptr [bp - 0x14]
020e cmp byte ptr [bx], 0x10
0211 jne 0x6eac
0213 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 534, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0218 mov bx, word ptr [bp - 0x14]
021b mov byte ptr [bx], al
021d jmp 0x6eae
021f nop 
0220 dec byte ptr [bx]
0222 les bx, ptr [bp - 0x18]
0225 cmp word ptr es:[bx], 0
0229 jle 0x6eba
022b dec word ptr es:[bx]
022e mov ax, word ptr [0xac84] ; _RpopT
0231 add ax, word ptr [0xaca4]
0235 sar ax, 4
0238 mov es, word ptr [0xc3a4]
023c add word ptr es:[0x7c8e], 5
0242 cmp ax, word ptr es:[0x7c8e]
0247 jge 0x6ee7
0249 mov word ptr es:[0x7c8e], 0
0250 cmp word ptr [0xac88], 0x64 ; _HealthR
0255 jge 0x6ee7
0257 inc word ptr [0xac88] ; _HealthR
025b mov al, byte ptr [bp + 0xa]
025e and ax, 0x78
0261 sar ax, 3
0264 push ax
0265 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 616, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
026a add sp, 2
026d les bx, ptr [bp - 0x10]
0270 mov bx, word ptr es:[bx]
0273 mov es, word ptr [0xc386]
0277 mov byte ptr es:[bx + 0x44f0], al
027c pop si
027d pop di
027e leave 
027f retf 
```

## Known declaration examples

- `extern int far FindInRList(int x, int y, int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far GetNewModeR(int mode);` — src/recovered/wf_DoRandR-fc777553ef.c
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
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
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

- {'symbol': '_StealFoodR', 'offset': 27686, 'source': None, 'size': 67}
- {'symbol': '_DecEatR', 'offset': 27754, 'source': 'src/recovered/DecEatR.c', 'size': 34}
- {'symbol': '_DoDigInR', 'offset': 28428, 'source': None, 'size': 798}
- {'symbol': '_DoDigOutR', 'offset': 29226, 'source': None, 'size': 656}

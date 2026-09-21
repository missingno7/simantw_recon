# Recovery task _DoDigInR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 798 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 0xc], 2
000a je 0x6f40
000c cmp word ptr [bp + 0xc], 6
0010 je 0x6f40
0012 push word ptr [bp + 0xc]
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
001a add sp, 2
001d mov es, word ptr [0xc384]
0021 mov bx, word ptr es:[0x9b6a]
0026 mov es, word ptr [0xc386]
002a mov byte ptr es:[bx + 0x44f0], al
002f pop si
0030 pop di
0031 leave 
0032 retf 
0033 nop 
0034 mov si, word ptr [bp + 8]
0037 mov al, byte ptr [bp + 0xa]
003a and ax, 7
003d push ax
003e push si
003f push word ptr [bp + 6]
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirR
0047 add sp, 6
004a mov word ptr [bp - 8], ax
004d or ax, ax
004f jge 0x6f65
0051 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0056 mov word ptr [bp - 8], ax
0059 mov al, byte ptr [bp + 0xa]
005c and ax, 0xf8
005f or ax, word ptr [bp - 8]
0062 mov word ptr [bp - 0xa], ax
0065 mov bx, word ptr [bp + 6]
0068 shl bx, 6
006b add bx, si
006d mov word ptr [bp - 0xc], bx
0070 mov byte ptr [bx - 0x6718], al
0074 mov bx, 0x9b6a
0077 mov es, word ptr [0xc384]
007b mov word ptr [bp - 0x10], bx
007e mov word ptr [bp - 0xe], es
0081 mov bx, word ptr es:[bx]
0084 mov es, word ptr [0xc386]
0088 mov byte ptr es:[bx + 0x46e6], al
008d cmp si, 0x3f
0090 jne 0x6fb2
0092 push word ptr [bp + 0xc]
0095 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
009a add sp, 2
009d les bx, ptr [bp - 0x10]
00a0 mov bx, word ptr es:[bx]
00a3 jmp 0x6f32
00a5 nop 
00a6 mov cx, word ptr [bp - 8]
00a9 mov es, word ptr [0xc396]
00ad mov bx, cx
00af mov al, byte ptr es:[bx + 8]
00b4 cwde 
00b5 mov si, ax
00b7 add si, word ptr [bp + 8]
00ba mov es, word ptr [0xc398]
00be mov al, byte ptr es:[bx]
00c3 cwde 
00c4 mov di, ax
00c6 add di, word ptr [bp + 6]
00c9 cmp di, 0x3f
00cc jle 0x6fdd
00ce jmp 0x7226
00d1 or di, di
00d3 jge 0x6fe4
00d5 jmp 0x7226
00d8 cmp si, 0x3f
00db jle 0x6fec
00dd jmp 0x7226
00e0 cmp si, 1
00e3 jge 0x7000
00e5 push word ptr [bp + 6]
00e8 nop 
00e9 push cs
00ea call 0x74ba ; _GetOutR
00ed add sp, 2
00f0 pop si
00f1 pop di
00f2 leave 
00f3 retf 
00f4 mov bx, di
00f6 shl bx, 6
00f9 add bx, si
00fb mov word ptr [bp - 0x12], bx
00fe cmp byte ptr [bx + 0x58e8], 0x30
0103 jb 0x7014
0105 jmp 0x7226
0108 mov al, byte ptr [bx + 0x58e8]
010c sub ah, ah
010e push ax
010f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 274, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDirt
0114 add sp, 2
0117 or ax, ax
0119 je 0x705c
011b push si
011c push di
011d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 288, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileThemR
0122 add sp, 4
0125 or ax, ax
0127 jne 0x7038
0129 jmp 0x70c0
012c les bx, ptr [bp - 0x10]
012f mov bx, word ptr es:[bx]
0132 mov es, word ptr [0xc386]
0136 add byte ptr es:[bx + 0x46e6], 0x18
013c mov byte ptr es:[bx + 0x44f0], 5
0142 push 0
0144 push 0
0146 push 0x12
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
014d add sp, 6
0150 mov bx, word ptr [bp - 0xc]
0153 mov byte ptr [bx - 0x6718], 0
0158 mov bx, word ptr [bp - 0x12]
015b mov al, byte ptr [bx - 0x6718]
015f sub ah, ah
0161 mov word ptr [bp - 2], ax
0164 cmp ax, 7
0167 jle 0x70d4
0169 cmp ax, 0x68
016c jge 0x70d4
016e push ax
016f push si
0170 push di
0171 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 372, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0176 add sp, 6
0179 mov word ptr [bp - 4], ax
017c or ax, ax
017e jl 0x7100
0180 push word ptr [bp - 0xa]
0183 push word ptr [bp - 2]
0186 call 0x26f4 ; _GetWinner
0189 add sp, 4
018c mov es, word ptr [0xc386]
0190 mov bx, word ptr [bp - 4]
0193 mov byte ptr es:[bx + 0x48dc], al
0198 and al, 0x80
019a add al, 0x70
019c mov byte ptr es:[bx + 0x46e6], al
01a1 mov bx, word ptr [bp - 0x12]
01a4 mov byte ptr [bx - 0x6718], al
01a8 mov bx, word ptr [bp - 4]
01ab mov byte ptr es:[bx + 0x44f0], 0xa
01b1 jmp 0x70f8
01b3 nop 
01b4 les bx, ptr [bp - 0x10]
01b7 mov bx, word ptr es:[bx]
01ba mov es, word ptr [0xc386]
01be mov byte ptr es:[bx + 0x44f0], 0
01c4 pop si
01c5 pop di
01c6 leave 
01c7 retf 
01c8 push ax
01c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 460, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
01ce add sp, 2
01d1 or ax, ax
01d3 je 0x7100
01d5 cmp word ptr [0xce98], 0 ; _MeColor
01da jne 0x7100
01dc les bx, ptr [bp - 0x10]
01df push word ptr es:[bx]
01e2 push 3
01e4 nop 
01e5 push cs
01e6 call 0x823e ; _YellowFight
01e9 add sp, 4
01ec mov word ptr [bp - 6], 1
01f1 jmp 0x7105
01f3 nop 
01f4 mov word ptr [bp - 6], 0
01f9 cmp word ptr [bp - 6], 0
01fd je 0x710e
01ff jmp 0x7226
0202 les bx, ptr [bp - 0x10]
0205 mov bx, word ptr es:[bx]
0208 mov es, word ptr [0xc386]
020c mov al, byte ptr es:[bx + 0x46e6]
0211 and ax, 0xf8
0214 or ax, word ptr [bp - 8]
0217 mov word ptr [bp - 0xa], ax
021a mov byte ptr es:[bx + 0x46e6], al
021f mov ax, bx
0221 mov bx, word ptr [bp - 0x12]
0224 mov cl, byte ptr [bp - 0xa]
0227 mov byte ptr [bx - 0x6718], cl
022b mov bx, ax
022d mov cx, di
022f mov byte ptr es:[bx + 0x4104], cl
0234 mov cx, si
0236 mov byte ptr es:[bx + 0x42fa], cl
023b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 574, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
0240 cmp ax, word ptr [0xac88] ; _HealthR
0244 jle 0x71ba
0246 mov bx, word ptr [bp - 0xc]
0249 mov dl, byte ptr [bx + 0x58e8]
024d sub dh, dh
024f cmp dx, 0x10
0252 jl 0x71ba
0254 cmp dx, 0x13
0257 jg 0x71ba
0259 cmp dx, 0x10
025c jne 0x7178
025e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0263 mov bx, word ptr [bp - 0xc]
0266 mov byte ptr [bx + 0x58e8], al
026a jmp 0x717c
026c dec byte ptr [bx + 0x58e8]
0270 mov es, word ptr [0xc394]
0274 cmp word ptr es:[0x72de], 0
027a jle 0x718d
027c dec word ptr es:[0x72de]
0281 mov ax, word ptr [0xac84] ; _RpopT
0284 add ax, word ptr [0xaca4]
0288 sar ax, 4
028b mov es, word ptr [0xc3a4]
028f add word ptr es:[0x7c8e], 5
0295 cmp ax, word ptr es:[0x7c8e]
029a jge 0x71ba
029c mov word ptr es:[0x7c8e], 0
02a3 cmp word ptr [0xac88], 0x64 ; _HealthR
02a8 jge 0x71ba
02aa inc word ptr [0xac88] ; _HealthR
02ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 689, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
02b3 or ax, ax
02b5 jne 0x71cd
02b7 push si
02b8 push di
02b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 700, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FixExitMapR
02be add sp, 4
02c1 mov bx, word ptr [bp - 0x12]
02c4 cmp byte ptr [bx + 0x58e8], 0x14
02c9 jne 0x7226
02cb xor al, al
02cd les bx, ptr [bp - 0x10]
02d0 mov bx, word ptr es:[bx]
02d3 mov es, word ptr [0xc386]
02d7 mov byte ptr es:[bx + 0x46e6], al
02dc mov bx, word ptr [bp - 0x12]
02df mov byte ptr [bx - 0x6718], al
02e3 push 0
02e5 push 3
02e7 mov al, byte ptr [bp - 0xa]
02ea and al, 0x7f
02ec cmp al, 0x30
02ee jge 0x7206
02f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 755, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
02f5 add ax, 0x90
02f8 jmp 0x720e
02fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 765, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
02ff add ax, 0xb0
0302 mov word ptr [bp - 0xa], ax
0305 push ax
0306 push si
0307 push di
0308 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 779, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
030d add sp, 0xa
0310 mov al, byte ptr [bp - 0xa]
0313 mov bx, word ptr [bp - 0x12]
0316 mov byte ptr [bx - 0x7718], al
031a pop si
031b pop di
031c leave 
031d retf 
```

## Known declaration examples

- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far DigTileThemR(int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
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
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DecEatR', 'offset': 27754, 'source': 'src/recovered/DecEatR.c', 'size': 34}
- {'symbol': '_DoFoodInR', 'offset': 27788, 'source': None, 'size': 640}
- {'symbol': '_DoDigOutR', 'offset': 29226, 'source': None, 'size': 656}
- {'symbol': '_GetOutR', 'offset': 29882, 'source': None, 'size': 314}

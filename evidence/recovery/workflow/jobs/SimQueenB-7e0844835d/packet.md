# Recovery task _SimQueenB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 666 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 0xa]
0009 cmp dx, 0xc
000c je 0x3dd3
000e jmp 0x3eea
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
0016 or ax, ax
0018 jne 0x3e2e
001a cmp word ptr [0xac86], ax ; _HealthB
001e jne 0x3e16
0020 xor al, al
0022 mov es, word ptr [0xc350]
0026 mov bx, word ptr es:[0x9b6a]
002b mov es, word ptr [0xc352]
002f mov byte ptr es:[bx + 0x3d18], al
0034 mov si, word ptr [bp + 6]
0037 shl si, 6
003a mov bx, word ptr [bp + 8]
003d mov byte ptr [bx + si - 0x7718], al
0041 push 1
0043 push 0x271f
0046 push 0
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
004d add sp, 6
0050 pop si
0051 pop di
0052 leave 
0053 retf 
0054 push word ptr [bp + 0xc]
0057 push word ptr [bp + 8]
005a push word ptr [bp + 6]
005d nop 
005e push cs
005f call 0x4154 ; _QueenMoveB
0062 add sp, 6
0065 or ax, ax
0067 je 0x3e2e
0069 jmp 0x4058
006c mov es, word ptr [0xc350]
0070 mov bx, word ptr es:[0x9b6a]
0075 mov es, word ptr [0xc352]
0079 mov si, word ptr es:[bx + 0x3d18]
007e and si, 0xff
0082 mov bx, si
0084 xor bl, 0xfc
0087 and bx, 7
008a mov es, word ptr [0xc364]
008e mov al, byte ptr es:[bx + 8]
0093 cwde 
0094 mov di, ax
0096 add di, word ptr [bp + 8]
0099 lea ax, [si + 8]
009c mov word ptr [bp - 2], ax
009f mov es, word ptr [0xc366]
00a3 mov al, byte ptr es:[bx]
00a8 cwde 
00a9 mov bx, ax
00ab add bx, word ptr [bp + 6]
00ae mov word ptr [bp - 4], bx
00b1 shl bx, 6
00b4 mov al, byte ptr [bx + di - 0x7718]
00b8 sub ah, ah
00ba cmp ax, word ptr [bp - 2]
00bd jne 0x3e86
00bf xor ax, ax
00c1 jmp 0x3e9c
00c3 nop 
00c4 push word ptr [bp - 2]
00c7 push di
00c8 push word ptr [bp - 4]
00cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
00d0 add sp, 6
00d3 or ax, ax
00d5 jge 0x3e81
00d7 mov ax, 1
00da or ax, ax
00dc je 0x3ebe
00de xor si, si
00e0 mov es, word ptr [0xc350]
00e4 mov bx, word ptr es:[0x9b6a]
00e9 mov es, word ptr [0xc352]
00ed mov byte ptr es:[bx + 0x3d18], 0
00f3 mov es, word ptr [0xc370]
00f7 dec word ptr es:[0x78e8]
00fc mov ax, si
00fe mov si, word ptr [bp + 6]
0101 shl si, 6
0104 mov bx, word ptr [bp + 8]
0107 mov byte ptr [bx + si - 0x7718], al
010b mov es, word ptr [0xc358]
010f cmp word ptr es:[0x85fc], 0
0115 jne 0x3edc
0117 jmp 0x4058
011a push 2
011c push bx
011d push word ptr [bp + 6]
0120 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 291, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _QueenBalloons
0125 jmp 0x3e0f
0128 cmp dx, 0xd
012b je 0x3ef2
012d jmp 0x4058
0130 mov es, word ptr [0xc350]
0134 mov bx, word ptr es:[0x9b6a]
0139 mov es, word ptr [0xc352]
013d mov si, word ptr es:[bx + 0x3d18]
0142 and si, 0xff
0146 mov ax, si
0148 mov bx, word ptr [bp + 6]
014b shl bx, 6
014e add bx, word ptr [bp + 8]
0151 add bx, 0x88e8
0155 mov word ptr [bp - 8], bx
0158 mov byte ptr [bx], al
015a mov es, word ptr [0xc370]
015e cmp word ptr es:[0x78e8], 0
0164 jg 0x3f2b
0166 jmp 0x3fac
0169 mov bx, ax
016b and bx, 7
016e mov es, word ptr [0xc364]
0172 mov al, byte ptr es:[bx + 8]
0177 cwde 
0178 mov di, ax
017a add di, word ptr [bp + 8]
017d lea ax, [si - 8]
0180 mov word ptr [bp - 2], ax
0183 mov es, word ptr [0xc366]
0187 mov al, byte ptr es:[bx]
018c cwde 
018d mov bx, ax
018f add bx, word ptr [bp + 6]
0192 mov word ptr [bp - 4], bx
0195 shl bx, 6
0198 mov al, byte ptr [bx + di - 0x7718]
019c sub ah, ah
019e cmp ax, word ptr [bp - 2]
01a1 jne 0x3f6c
01a3 xor ax, ax
01a5 jmp 0x3f82
01a7 nop 
01a8 nop 
01a9 nop 
01aa push word ptr [bp - 2]
01ad push di
01ae push word ptr [bp - 4]
01b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 436, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
01b6 add sp, 6
01b9 or ax, ax
01bb jge 0x3f65
01bd mov ax, 1
01c0 or ax, ax
01c2 je 0x3fac
01c4 mov es, word ptr [0xc370]
01c8 dec word ptr es:[0x78e8]
01cd xor al, al
01cf mov es, word ptr [0xc350]
01d3 mov bx, word ptr es:[0x9b6a]
01d8 mov es, word ptr [0xc352]
01dc mov byte ptr es:[bx + 0x3d18], al
01e1 mov bx, word ptr [bp - 8]
01e4 mov byte ptr [bx], al
01e6 pop si
01e7 pop di
01e8 leave 
01e9 retf 
01ea mov es, word ptr [0xc364]
01ee mov bl, byte ptr [bp + 0xc]
01f1 xor bl, 0xfc
01f4 and bx, 7
01f7 mov al, byte ptr es:[bx + 8]
01fc cwde 
01fd add ax, word ptr [bp + 8]
0200 mov word ptr [bp - 2], ax
0203 push ax
0204 mov es, word ptr [0xc366]
0208 mov al, byte ptr es:[bx]
020d cwde 
020e add ax, word ptr [bp + 6]
0211 mov word ptr [bp - 4], ax
0214 push ax
0215 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 536, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InNestBounds
021a add sp, 4
021d or ax, ax
021f je 0x4058
0221 mov ax, word ptr [bp - 4]
0224 mov es, word ptr [0xc372]
0228 mov word ptr es:[0x8362], ax
022c mov ax, word ptr [bp - 2]
022f mov word ptr es:[0x8364], ax
0233 mov es, word ptr [0xc368]
0237 test byte ptr es:[0x75fc], 0xf
023d jne 0x4058
023f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 578, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand128
0244 cmp ax, word ptr [0xac86] ; _HealthB
0248 jg 0x4058
024a push 1
024c push word ptr [bp - 2]
024f push word ptr [bp - 4]
0252 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 597, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PlaceEggB
0257 add sp, 6
025a mov es, word ptr [0xc374]
025e dec word ptr es:[0x7402]
0263 jns 0x4048
0265 mov ax, word ptr [0xac82] ; _BpopT
0268 sar ax, 5
026b mov word ptr es:[0x7402], ax
026f cmp word ptr [0xac86], 0 ; _HealthB
0274 jle 0x4048
0276 mov es, word ptr [0xc376]
027a cmp word ptr es:[0x8a60], 0
0280 jne 0x4048
0282 dec word ptr [0xac86] ; _HealthB
0286 mov es, word ptr [0xc378]
028a add word ptr es:[0x9af8], 1
0290 adc word ptr es:[0x9afa], 0
0296 pop si
0297 pop di
0298 leave 
0299 retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near BpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DropFoodB', 'offset': 15420, 'source': None, 'size': 100}
- {'symbol': '_SimEggB', 'offset': 15520, 'source': None, 'size': 290}
- {'symbol': '_GetBestDir', 'offset': 16478, 'source': None, 'size': 246}
- {'symbol': '_QueenMoveB', 'offset': 16724, 'source': None, 'size': 246}

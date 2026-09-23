# Recovery task _PickupMyRock

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 692 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov bx, word ptr [0xcc84] ; _MeType
000a cmp bx, 0x10
000d je 0x8608
000f cmp bx, 0x30
0012 je 0x8608
0014 xor ax, ax
0016 pop si
0017 pop di
0018 leave 
0019 retf 
001a mov word ptr [bp - 4], 0
001f mov word ptr [bp - 2], 0xffff
0024 mov cx, word ptr [bp + 6]
0027 cmp cx, 1
002a jg 0x8646
002c mov di, word ptr [bp + 8]
002f or di, di
0031 jl 0x8638
0033 mov si, word ptr [bp + 0xa]
0036 cmp di, 0x7f
0039 jg 0x863b
003b or si, si
003d jl 0x863b
003f cmp si, 0x3f
0042 jg 0x863b
0044 mov dx, 1
0047 jmp 0x863d
0049 nop 
004a mov si, word ptr [bp + 0xa]
004d xor dx, dx
004f dec dx
0050 je 0x8656
0052 mov bx, word ptr [bp - 2]
0055 jmp 0x8694
0057 nop 
0058 cmp word ptr [bp + 8], 0
005c jl 0x8638
005e mov si, word ptr [bp + 0xa]
0061 cmp word ptr [bp + 8], 0x3f
0065 jmp 0x8627
0067 nop 
0068 mov ax, cx
006a or ax, ax
006c jl 0x8640
006e jo 0x8640
0070 dec ax
0071 jle 0x866a
0073 dec ax
0074 je 0x8678
0076 dec ax
0077 je 0x8686
0079 jmp 0x8640
007b nop 
007c mov bx, word ptr [bp + 8]
007f shl bx, 6
0082 add bx, si
0084 mov bl, byte ptr [bx + 0x28e8]
0088 jmp 0x8692
008a mov bx, word ptr [bp + 8]
008d shl bx, 6
0090 add bx, si
0092 mov bl, byte ptr [bx + 0x48e8]
0096 jmp 0x8692
0098 mov bx, word ptr [bp + 8]
009b shl bx, 6
009e add bx, si
00a0 mov bl, byte ptr [bx + 0x58e8]
00a4 sub bh, bh
00a6 mov dx, bx
00a8 cmp cx, 1
00ab jle 0x869e
00ad jmp 0x8770
00b0 jg 0x86b2
00b2 dec cx
00b3 jne 0x86bc
00b5 cmp dx, 0x51
00b8 jl 0x86bc
00ba cmp dx, 0x53
00bd jg 0x86bc
00bf mov dx, 1
00c2 jmp 0x86be
00c4 cmp dx, 0x30
00c7 jl 0x86bc
00c9 cmp dx, 0x31
00cc jle 0x86ad
00ce xor dx, dx
00d0 or dx, dx
00d2 je 0x8726
00d4 cmp word ptr [bp + 8], 0x40
00d8 jge 0x86e8
00da mov di, word ptr [bp - 4]
00dd mov es, word ptr [0xc4a8]
00e1 mov al, byte ptr es:[si - 0x7d2e]
00e6 sub ah, ah
00e8 cmp ax, word ptr [bp + 8]
00eb jne 0x8708
00ed mov bx, si
00ef shl bx, 6
00f2 mov byte ptr [bx + 0x48e8], 0x18
00f7 jmp 0x8705
00f9 nop 
00fa mov di, word ptr [bp - 4]
00fd mov es, word ptr [0xc4aa]
0101 mov al, byte ptr es:[si - 0x7cee]
0106 sub ah, ah
0108 cmp ax, word ptr [bp + 8]
010b jne 0x8708
010d mov bx, si
010f shl bx, 6
0112 mov byte ptr [bx + 0x58e8], 0x18
0117 mov di, 1
011a or di, di
011c je 0x8744
011e mov es, word ptr [0xc4ac]
0122 cmp word ptr es:[0x9b6e], 0
0128 jne 0x872c
012a mov bx, word ptr [bp + 8]
012d shl bx, 6
0130 mov byte ptr [bx + si + 0x28e8], 0x50
0135 mov word ptr [bp - 4], di
0138 mov si, word ptr [bp - 4]
013b jmp 0x8878
013e push 7
0140 nop 
0141 push cs
0142 call 0x158a ; _SRand1
0145 add sp, 2
0148 add al, 0x59
014a mov bx, word ptr [bp + 8]
014d shl bx, 6
0150 mov byte ptr [bx + si + 0x28e8], al
0154 jmp 0x8723
0156 mov es, word ptr [0xc4ac]
015a cmp word ptr es:[0x9b6e], 0
0160 jne 0x8762
0162 nop 
0163 push cs
0164 call 0x160e ; _SRand16
0167 mov bx, word ptr [bp + 8]
016a shl bx, 6
016d mov byte ptr [bx + si + 0x28e8], al
0171 jmp 0x8875
0174 mov bx, word ptr [bp + 8]
0177 shl bx, 6
017a mov byte ptr [bx + si + 0x28e8], 0
017f jmp 0x8875
0182 cmp dx, 0x30
0185 je 0x8778
0187 jmp 0x881c
018a nop 
018b push cs
018c call 0x15ee ; _SRand8
018f mov si, ax
0191 cmp word ptr [bp + 6], 1
0195 jg 0x87a2
0197 cmp word ptr [bp + 8], 0
019b jl 0x87ba
019d cmp word ptr [bp + 8], 0x7f
01a1 jg 0x87ba
01a3 cmp word ptr [bp + 0xa], 0
01a7 jl 0x87ba
01a9 cmp word ptr [bp + 0xa], 0x3f
01ad jg 0x87ba
01af mov dx, 1
01b2 jmp 0x87bc
01b4 cmp word ptr [bp + 8], 0
01b8 jl 0x87ba
01ba cmp word ptr [bp + 8], 0x3f
01be jg 0x87ba
01c0 cmp word ptr [bp + 0xa], 0
01c4 jl 0x87ba
01c6 cmp word ptr [bp + 0xa], 0x3f
01ca jle 0x879d
01cc xor dx, dx
01ce dec dx
01cf je 0x87c2
01d1 jmp 0x8875
01d4 mov ax, word ptr [bp + 6]
01d7 or ax, ax
01d9 jl 0x8809
01db jo 0x8809
01dd dec ax
01de jle 0x87d6
01e0 dec ax
01e1 je 0x87e8
01e3 dec ax
01e4 je 0x87fa
01e6 jmp 0x8809
01e8 mov bx, word ptr [bp + 0xa]
01eb mov di, word ptr [bp + 8]
01ee shl di, 6
01f1 mov ax, si
01f3 mov byte ptr [bx + di + 0x28e8], al
01f7 jmp 0x8809
01f9 nop 
01fa mov bx, word ptr [bp + 0xa]
01fd mov di, word ptr [bp + 8]
0200 shl di, 6
0203 mov ax, si
0205 mov byte ptr [bx + di + 0x48e8], al
0209 jmp 0x8809
020b nop 
020c mov ax, si
020e mov si, word ptr [bp + 8]
0211 shl si, 6
0214 mov bx, word ptr [bp + 0xa]
0217 mov byte ptr [bx + si + 0x58e8], al
021b push word ptr [bp + 0xa]
021e push word ptr [bp + 8]
0221 push word ptr [bp + 6]
0224 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 551, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0229 add sp, 6
022c jmp 0x8875
022e cmp dx, 0x31
0231 je 0x8824
0233 jmp 0x8726
0236 cmp word ptr [bp + 6], 2
023a jne 0x884a
023c mov di, word ptr [bp + 8]
023f mov si, word ptr [bp + 0xa]
0242 mov bx, di
0244 shl bx, 6
0247 mov byte ptr [bx + si + 0x48e8], 0x18
024c mov es, word ptr [0xc4a8]
0250 mov bl, byte ptr es:[di - 0x7d2e]
0255 sub bh, bh
0257 shl bx, 6
025a jmp 0x8870
025c mov di, word ptr [bp + 8]
025f mov si, word ptr [bp + 0xa]
0262 mov bx, di
0264 mov ax, di
0266 shl bx, 6
0269 mov byte ptr [bx + si + 0x58e8], 0x18
026e mov bx, di
0270 mov si, di
0272 mov es, word ptr [0xc4aa]
0276 mov di, word ptr es:[si - 0x7cee]
027b and di, 0xff
027f shl di, 6
0282 mov byte ptr [bx + di + 0x28e8], 0x50
0287 mov si, 1
028a or si, si
028c je 0x889c
028e cmp word ptr [0xcc84], 0x10 ; _MeType
0293 jne 0x8888
0295 mov ax, 0x28
0298 jmp 0x888b
029a mov ax, 0x48
029d mov word ptr [0xcc84], ax ; _MeType
02a0 push 0x7e
02a2 push 0
02a4 push 0x1e
02a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 681, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
02ab add sp, 6
02ae mov ax, si
02b0 pop si
02b1 pop di
02b2 leave 
02b3 retf 
```

## Known declaration examples

- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DropMyRock', 'offset': 31826, 'source': None, 'size': 1334}
- {'symbol': '_DropMyEgg', 'offset': 33160, 'source': None, 'size': 1126}
- {'symbol': '_FindEggAt', 'offset': 34978, 'source': None, 'size': 499}
- {'symbol': '_FindLifeAt', 'offset': 35478, 'source': None, 'size': 473}

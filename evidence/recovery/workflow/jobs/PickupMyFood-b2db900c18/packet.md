# Recovery task _PickupMyFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 672 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, 0xffff
0009 push word ptr [bp + 0xa]
000c push word ptr [bp + 8]
000f push word ptr [bp + 6]
0012 nop 
0013 push cs
0014 call 0x56da ; _IsValidLocation
0017 add sp, 6
001a dec ax
001b jne 0x8faf
001d mov ax, word ptr [bp + 6]
0020 or ax, ax
0022 jl 0x8faf
0024 jo 0x8faf
0026 dec ax
0027 jle 0x8f7e
0029 dec ax
002a je 0x8f8e
002c dec ax
002d je 0x8f9e
002f jmp 0x8faf
0031 nop 
0032 mov bx, word ptr [bp + 0xa]
0035 mov si, word ptr [bp + 8]
0038 shl si, 6
003b mov di, word ptr [bx + si + 0x28e8]
003f jmp 0x8fab
0041 nop 
0042 mov bx, word ptr [bp + 0xa]
0045 mov si, word ptr [bp + 8]
0048 shl si, 6
004b mov di, word ptr [bx + si + 0x48e8]
004f jmp 0x8fab
0051 nop 
0052 mov bx, word ptr [bp + 0xa]
0055 mov si, word ptr [bp + 8]
0058 shl si, 6
005b mov di, word ptr [bx + si + 0x58e8]
005f and di, 0xff
0063 mov si, di
0065 or si, si
0067 jge 0x8fc2
0069 xor dx, dx
006b or dx, dx
006d jne 0x8fe6
006f xor ax, ax
0071 pop si
0072 pop di
0073 leave 
0074 retf 
0075 nop 
0076 cmp word ptr [bp + 6], 1
007a jg 0x8fd6
007c push si
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
0082 add sp, 2
0085 mov dx, ax
0087 jmp 0x8fb7
0089 nop 
008a cmp si, 0x10
008d jl 0x8fb5
008f cmp si, 0x13
0092 jg 0x8fb5
0094 mov dx, 1
0097 jmp 0x8fb7
0099 nop 
009a mov es, word ptr [0xc4a0]
009e cmp word ptr es:[0x9af2], 0
00a4 je 0x8ff8
00a6 mov si, 1
00a9 jmp 0x9008
00ab nop 
00ac mov dx, word ptr [0xcc84] ; _MeType
00b0 cmp dx, 0x10
00b3 je 0x9006
00b5 cmp dx, 0x30
00b8 jne 0x8fbb
00ba xor si, si
00bc cmp word ptr [bp + 6], 1
00c0 jg 0x906c
00c2 push word ptr [bp + 0xa]
00c5 push word ptr [bp + 8]
00c8 nop 
00c9 push cs
00ca call 0x10d18
00cd add sp, 4
00d0 or si, si
00d2 je 0x9023
00d4 jmp 0x91bc
00d7 mov word ptr [0xce88], 0xc8 ; _MeScent
00dd mov es, word ptr [0xc4b4]
00e1 push word ptr es:[0x835c]
00e6 push word ptr es:[0x835a]
00eb push word ptr [bp + 0xa]
00ee push word ptr [bp + 8]
00f1 nop 
00f2 push cs
00f3 call 0x1122 ; _GetDis
00f6 add sp, 8
00f9 mov es, word ptr [0xc4b6]
00fd mov word ptr es:[0x9fe2], ax
0101 inc ax
0102 mov es, word ptr [0xc4b8]
0106 mov word ptr es:[0x80aa], ax
010a push word ptr [0xce88] ; _MeScent
010e push word ptr [bp + 0xa]
0111 push word ptr [bp + 8]
0114 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 279, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _JamScentBT
0119 add sp, 6
011c jmp 0x91bc
011f nop 
0120 mov di, word ptr [bp + 6]
0123 mov cx, 0xffff
0126 cmp di, 1
0129 jg 0x9094
012b cmp word ptr [bp + 8], 0
012f jl 0x90ac
0131 cmp word ptr [bp + 8], 0x7f
0135 jg 0x90ac
0137 cmp word ptr [bp + 0xa], 0
013b jl 0x90ac
013d cmp word ptr [bp + 0xa], 0x3f
0141 jg 0x90ac
0143 mov dx, 1
0146 jmp 0x90ae
0148 cmp word ptr [bp + 8], 0
014c jl 0x90ac
014e cmp word ptr [bp + 8], 0x3f
0152 jg 0x90ac
0154 cmp word ptr [bp + 0xa], 0
0158 jl 0x90ac
015a cmp word ptr [bp + 0xa], 0x3f
015e jle 0x908f
0160 xor dx, dx
0162 dec dx
0163 jne 0x90f3
0165 mov ax, di
0167 or ax, ax
0169 jl 0x90f3
016b jo 0x90f3
016d dec ax
016e jle 0x90c4
0170 dec ax
0171 je 0x90d4
0173 dec ax
0174 je 0x90e4
0176 jmp 0x90f3
0178 mov bx, word ptr [bp + 8]
017b shl bx, 6
017e add bx, word ptr [bp + 0xa]
0181 mov cl, byte ptr [bx + 0x28e8]
0185 jmp 0x90f1
0187 nop 
0188 mov bx, word ptr [bp + 8]
018b shl bx, 6
018e add bx, word ptr [bp + 0xa]
0191 mov cl, byte ptr [bx + 0x48e8]
0195 jmp 0x90f1
0197 nop 
0198 mov bx, word ptr [bp + 8]
019b shl bx, 6
019e add bx, word ptr [bp + 0xa]
01a1 mov cl, byte ptr [bx + 0x58e8]
01a5 sub ch, ch
01a7 mov dx, cx
01a9 cmp dx, 0x10
01ac jne 0x9104
01ae nop 
01af push cs
01b0 call 0x15ee ; _SRand8
01b3 mov dx, ax
01b5 jmp 0x9105
01b7 nop 
01b8 dec dx
01b9 cmp di, 1
01bc jg 0x9128
01be cmp word ptr [bp + 8], 0
01c2 jl 0x9140
01c4 cmp word ptr [bp + 8], 0x7f
01c8 jg 0x9140
01ca cmp word ptr [bp + 0xa], 0
01ce jl 0x9140
01d0 cmp word ptr [bp + 0xa], 0x3f
01d4 jg 0x9140
01d6 mov cx, 1
01d9 jmp 0x9142
01db nop 
01dc cmp word ptr [bp + 8], 0
01e0 jl 0x9140
01e2 cmp word ptr [bp + 8], 0x3f
01e6 jg 0x9140
01e8 cmp word ptr [bp + 0xa], 0
01ec jl 0x9140
01ee cmp word ptr [bp + 0xa], 0x3f
01f2 jle 0x9122
01f4 xor cx, cx
01f6 dec cx
01f7 jne 0x9194
01f9 mov ax, di
01fb or ax, ax
01fd jl 0x9185
01ff jo 0x9185
0201 dec ax
0202 jle 0x9158
0204 dec ax
0205 je 0x9168
0207 dec ax
0208 je 0x9178
020a jmp 0x9185
020c mov bx, word ptr [bp + 8]
020f shl bx, 6
0212 add bx, word ptr [bp + 0xa]
0215 mov byte ptr [bx + 0x28e8], dl
0219 jmp 0x9185
021b nop 
021c mov bx, word ptr [bp + 8]
021f shl bx, 6
0222 add bx, word ptr [bp + 0xa]
0225 mov byte ptr [bx + 0x48e8], dl
0229 jmp 0x9185
022b nop 
022c mov bx, word ptr [bp + 8]
022f shl bx, 6
0232 add bx, word ptr [bp + 0xa]
0235 mov byte ptr [bx + 0x58e8], dl
0239 push word ptr [bp + 0xa]
023c push word ptr [bp + 8]
023f push di
0240 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 579, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0245 add sp, 6
0248 cmp di, 2
024b jne 0x91ac
024d mov <resolved loader operand; see bindings> ; [{'operand_offset': 590, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0250 mov ds, ax
0252 cmp word ptr [0x9ea4], 0
0257 jle 0x91bc
0259 dec word ptr [0x9ea4]
025d jmp 0x91bc
025f nop 
0260 mov <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0263 mov ds, ax
0265 cmp word ptr [0x72de], 0
026a jle 0x91bc
026c dec word ptr [0x72de]
0270 or si, si
0272 je 0x91d0
0274 mov <resolved loader operand; see bindings> ; [{'operand_offset': 629, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0277 mov es, ax
0279 mov word ptr es:[0x8a6e], 0
0280 push ss
0281 pop ds
0282 jmp 0x91e5
0284 push ss
0285 pop ds
0286 push 0x7e
0288 push 0
028a push 0x1d
028c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 655, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0291 add sp, 6
0294 add word ptr [0xcc84], 8 ; _MeType
0299 mov ax, 1
029c pop si
029d pop di
029e leave 
029f retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_0000_GetDefendDir_2_scaffold-cdac288ff9.c
- `extern unsigned long far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far IsItFood(int tile);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far IsValidLocation(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EatMyFood', 'offset': 36058, 'source': None, 'size': 443}
- {'symbol': '_PickupMyEgg', 'offset': 36502, 'source': 'src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c', 'size': 181}
- {'symbol': '_DropMyObject', 'offset': 37356, 'source': 'src/recovered/wf_DropMyObject-9eb45c4e42.c', 'size': 100}
- {'symbol': '_PickupMyObject', 'offset': 37456, 'source': 'src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c', 'size': 241}

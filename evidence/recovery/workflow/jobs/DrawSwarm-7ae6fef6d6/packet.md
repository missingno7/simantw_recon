# Recovery task _DrawSwarm

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 718 bytes.

```asm
0000 enter 0x1e, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc1c8]
000a cmp word ptr es:[0x8610], 0
0010 je 0xbb23
0012 jmp 0xbdd8
0015 mov es, word ptr [0xc19e]
0019 mov ax, word ptr es:[0x7a62]
001d mov cx, ax
001f shl ax, 2
0022 add ax, cx
0024 shl ax, 1
0026 mov cx, ax
0028 add ax, 0x2e
002b mov bx, 0x7efe
002e mov es, word ptr [0xc1ca]
0032 mov word ptr [bp - 0xa], bx
0035 mov word ptr [bp - 8], es
0038 mov word ptr es:[bx], ax
003b mov es, word ptr [0xc19e]
003f imul ax, word ptr es:[0x7a60], 0x1c
0045 sub ax, cx
0047 add ax, 0xb2
004a mov bx, 0x7d58
004d mov es, word ptr [0xc1cc]
0051 mov word ptr [bp - 0xe], bx
0054 mov word ptr [bp - 0xc], es
0057 mov word ptr es:[bx], ax
005a xor di, di
005c mov es, word ptr [0xc1ce]
0060 cmp word ptr es:[0x807a], di
0065 jg 0xbb78
0067 jmp 0xbc75
006a mov si, 0xcb22
006d cmp si, 0xcb42
0071 jb 0xbb84
0073 jmp 0xbc75
0076 cmp word ptr [0xac8c], di ; _QueenStorageB
007a jg 0xbb8d
007c jmp 0xbc75
007f mov bx, di
0081 add bx, 0x9b8c
0085 mov es, word ptr [0xc1d0]
0089 mov word ptr [bp - 0x12], bx
008c mov word ptr [bp - 0x10], es
008f mov al, byte ptr es:[bx]
0092 cwde 
0093 mov cx, ax
0095 mov bx, di
0097 add bx, 0x9b32
009b mov es, word ptr [0xc1d2]
009f mov word ptr [bp - 0x16], bx
00a2 mov word ptr [bp - 0x14], es
00a5 mov al, byte ptr es:[bx]
00a8 cwde 
00a9 mov word ptr [bp - 2], ax
00ac cmp ax, 0xf
00af jg 0xbbd2
00b1 cmp ax, 0xfff1
00b4 jl 0xbbd2
00b6 cmp cx, 0xf
00b9 jg 0xbbd2
00bb cmp cx, -0xf
00be jl 0xbbd2
00c0 xor dx, dx
00c2 jmp 0xbbd5
00c4 mov dx, 1
00c7 or dx, dx
00c9 je 0xbbf3
00cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
00d0 sub al, 0xa
00d2 les bx, ptr [bp - 0x16]
00d5 mov byte ptr es:[bx], al
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 219, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
00dd sub al, 0xa
00df les bx, ptr [bp - 0x12]
00e2 mov byte ptr es:[bx], al
00e5 push 3
00e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00ec add sp, 2
00ef dec al
00f1 les bx, ptr [bp - 0x16]
00f4 add byte ptr es:[bx], al
00f7 mov al, byte ptr es:[bx]
00fa cwde 
00fb les bx, ptr [bp - 0xe]
00fe add ax, word ptr es:[bx]
0101 mov word ptr [bp - 2], ax
0104 push 3
0106 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
010b add sp, 2
010e dec al
0110 les bx, ptr [bp - 0x12]
0113 add byte ptr es:[bx], al
0116 mov al, byte ptr es:[bx]
0119 cwde 
011a les bx, ptr [bp - 0xa]
011d add ax, word ptr es:[bx]
0120 cmp word ptr [si], -1
0123 je 0xbc4c
0125 push -1
0127 push word ptr [si]
0129 push word ptr [0x1886] ; _yardAnimHandle
012d push 0x1b5e
0130 push ax
0131 push word ptr [bp - 2]
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
0139 add sp, 0xc
013c jmp 0xbc63
013e push -1
0140 push 0x1b5e
0143 push ax
0144 push word ptr [bp - 2]
0147 push word ptr [0x1886] ; _yardAnimHandle
014b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 334, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0150 add sp, 0xa
0153 mov word ptr [si], ax
0155 add si, 2
0158 inc di
0159 mov es, word ptr [0xc1ce]
015d cmp word ptr es:[0x807a], di
0162 jle 0xbc75
0164 jmp 0xbb7b
0167 cmp di, 0x10
016a jge 0xbca6
016c mov si, di
016e shl si, 1
0170 add si, 0xcb22
0174 cmp word ptr [si], -1
0177 je 0xbc9d
0179 push ds
017a push 0x1974
017d push word ptr [si]
017f push word ptr [0x1886] ; _yardAnimHandle
0183 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 390, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
0188 add sp, 8
018b mov word ptr [si], 0xffff
018f add si, 2
0192 cmp si, 0xcb42
0196 jb 0xbc82
0198 xor di, di
019a mov es, word ptr [0xc1d4]
019e cmp word ptr es:[0x9c26], di
01a3 jg 0xbcb6
01a5 jmp 0xbda7
01a8 mov si, 0xcb44
01ab cmp si, 0xcb64
01af jb 0xbcc2
01b1 jmp 0xbda7
01b4 cmp word ptr [0xac8e], di ; _QueenStorageR
01b8 jg 0xbccb
01ba jmp 0xbda7
01bd mov bx, di
01bf add bx, 0x9c34
01c3 mov es, word ptr [0xc1d6]
01c7 mov word ptr [bp - 0x1a], bx
01ca mov word ptr [bp - 0x18], es
01cd mov al, byte ptr es:[bx]
01d0 cwde 
01d1 mov cx, ax
01d3 mov bx, di
01d5 add bx, 0x9bf0
01d9 mov es, word ptr [0xc1d8]
01dd mov word ptr [bp - 0x1e], bx
01e0 mov word ptr [bp - 0x1c], es
01e3 mov al, byte ptr es:[bx]
01e6 cwde 
01e7 mov word ptr [bp - 2], ax
01ea cmp ax, 0xf
01ed jg 0xbd10
01ef cmp ax, 0xfff1
01f2 jl 0xbd10
01f4 cmp cx, 0xf
01f7 jg 0xbd10
01f9 cmp cx, -0xf
01fc jl 0xbd10
01fe xor dx, dx
0200 jmp 0xbd13
0202 mov dx, 1
0205 or dx, dx
0207 je 0xbd25
0209 xor al, al
020b mov es, word ptr [bp - 0x1c]
020e mov byte ptr es:[bx], al
0211 les bx, ptr [bp - 0x1a]
0214 mov byte ptr es:[bx], al
0217 push 3
0219 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 540, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
021e add sp, 2
0221 dec al
0223 les bx, ptr [bp - 0x1e]
0226 add byte ptr es:[bx], al
0229 mov al, byte ptr es:[bx]
022c cwde 
022d les bx, ptr [bp - 0xe]
0230 add ax, word ptr es:[bx]
0233 mov word ptr [bp - 2], ax
0236 push 3
0238 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 571, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
023d add sp, 2
0240 dec al
0242 les bx, ptr [bp - 0x1a]
0245 add byte ptr es:[bx], al
0248 mov al, byte ptr es:[bx]
024b cwde 
024c les bx, ptr [bp - 0xa]
024f add ax, word ptr es:[bx]
0252 cmp word ptr [si], -1
0255 je 0xbd7e
0257 push -1
0259 push word ptr [si]
025b push word ptr [0x1886] ; _yardAnimHandle
025f push 0x1b5f
0262 push ax
0263 push word ptr [bp - 2]
0266 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 617, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
026b add sp, 0xc
026e jmp 0xbd95
0270 push -1
0272 push 0x1b5f
0275 push ax
0276 push word ptr [bp - 2]
0279 push word ptr [0x1886] ; _yardAnimHandle
027d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 640, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0282 add sp, 0xa
0285 mov word ptr [si], ax
0287 add si, 2
028a inc di
028b mov es, word ptr [0xc1d4]
028f cmp word ptr es:[0x9c26], di
0294 jle 0xbda7
0296 jmp 0xbcb9
0299 cmp di, 0x10
029c jge 0xbdd8
029e mov si, di
02a0 shl si, 1
02a2 add si, 0xcb44
02a6 cmp word ptr [si], -1
02a9 je 0xbdcf
02ab push ds
02ac push 0x197b
02af push word ptr [si]
02b1 push word ptr [0x1886] ; _yardAnimHandle
02b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 696, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimObject
02ba add sp, 8
02bd mov word ptr [si], 0xffff
02c1 add si, 2
02c4 cmp si, 0xcb64
02c8 jb 0xbdb4
02ca pop si
02cb pop di
02cc leave 
02cd retf 
```

## Known declaration examples

- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int near QueenStorageR;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageR;` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int near QueenStorageR;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Draw_SimYard', 'offset': 46178, 'source': None, 'size': 1595}
- {'symbol': '_DrawRain', 'offset': 47774, 'source': 'src/recovered/wf_DrawRain-d667f83eb1.c', 'size': 112}
- {'symbol': '_TooFar', 'offset': 48604, 'source': 'src/recovered/wf_TooFar-89685c4366.c', 'size': 39}
- {'symbol': '_InvertPatch', 'offset': 48644, 'source': None, 'size': 159}

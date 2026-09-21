# Recovery task _AddFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 513 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 8], 1
000a jne 0x6a72
000c push 0x7e
000e push 0
0010 push 0x20
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0017 add sp, 6
001a cmp word ptr [bp + 6], 0
001e jge 0x6a90
0020 mov di, 0x40
0023 push 0x30
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
002a add sp, 2
002d add ax, 8
0030 mov word ptr [bp - 0xa], ax
0033 mov si, 0xc8
0036 jmp 0x6aa2
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand128
003d mov di, ax
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
0044 mov word ptr [bp - 0xa], ax
0047 mov si, word ptr [bp + 6]
004a mov es, word ptr [0xc62a]
004e mov word ptr es:[0x836a], di
0053 mov word ptr es:[0x836c], ax
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
005c add ax, 5
005f mov word ptr [bp - 0xe], ax
0062 or si, si
0064 jg 0x6ac1
0066 jmp 0x6c55
0069 mov word ptr [bp - 0x12], di
006c mov word ptr [bp - 0xc], si
006f mov word ptr [bp + 6], si
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand256
0077 mov word ptr [bp - 4], ax
007a push word ptr [bp - 0xe]
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0082 add sp, 2
0085 mov word ptr [bp - 8], ax
0088 mov si, word ptr [bp - 4]
008b sub si, -0x40
008e and si, 0x7f
0091 cmp si, 0x3f
0094 jle 0x6af5
0096 mov ax, 0x80
0099 sub ax, si
009b mov si, ax
009d cmp si, 0x40
00a0 jne 0x6b00
00a2 mov bx, 0x7fff
00a5 jmp 0x6b19
00a7 nop 
00a8 and si, 0x3f
00ab shl si, 1
00ad mov es, word ptr [0xc628]
00b1 mov ax, word ptr es:[0x9fca]
00b5 mov dx, word ptr es:[0x9fcc]
00ba mov es, dx
00bc add si, ax
00be mov bx, word ptr es:[si]
00c1 mov al, byte ptr [bp - 4]
00c4 add al, 0x40
00c6 sub ah, ah
00c8 cmp ax, 0x7f
00cb jle 0x6b27
00cd neg bx
00cf push 0
00d1 push 0x7fff
00d4 mov ax, bx
00d6 imul word ptr [bp - 8]
00d9 push dx
00da push ax
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00e0 add ax, word ptr [bp - 0x12]
00e3 mov word ptr [bp - 0x10], ax
00e6 mov si, word ptr [bp - 4]
00e9 and si, 0x7f
00ec cmp si, 0x3f
00ef jle 0x6b50
00f1 mov ax, 0x80
00f4 sub ax, si
00f6 mov si, ax
00f8 cmp si, 0x40
00fb jne 0x6b5c
00fd mov word ptr [bp - 6], 0x7fff
0102 jmp 0x6b72
0104 mov bx, si
0106 and bx, 0x3f
0109 shl bx, 1
010b mov es, word ptr [0xc628]
010f les si, ptr es:[0x9fca]
0114 mov ax, word ptr es:[bx + si]
0117 mov word ptr [bp - 6], ax
011a mov al, byte ptr [bp - 4]
011d sub ah, ah
011f cmp ax, 0x7f
0122 jle 0x6b7f
0124 neg word ptr [bp - 6]
0127 push 0
0129 push 0x7fff
012c mov ax, word ptr [bp - 6]
012f imul word ptr [bp - 8]
0132 push dx
0133 push ax
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0139 mov si, ax
013b add si, word ptr [bp - 0xa]
013e cmp word ptr [bp - 0x10], 0
0142 jge 0x6b9f
0144 jmp 0x6c4d
0147 cmp word ptr [bp - 0x10], 0x7f
014b jle 0x6ba8
014d jmp 0x6c4d
0150 or si, si
0152 jge 0x6baf
0154 jmp 0x6c4d
0157 cmp si, 0x3f
015a jle 0x6bb7
015c jmp 0x6c4d
015f mov bx, word ptr [bp - 0x10]
0162 shl bx, 6
0165 add bx, si
0167 mov word ptr [bp - 0x16], bx
016a cmp byte ptr [bx + 0x68e8], 0
016f je 0x6bcc
0171 jmp 0x6c4d
0174 add bx, 0x28e8
0178 mov bl, byte ptr [bx]
017a sub bh, bh
017c mov es, word ptr [0xc5b4]
0180 cmp word ptr es:[0x9b6e], 0
0186 je 0x6c1e
0188 cmp bx, 0x18
018b jge 0x6c0c
018d cmp bx, 4
0190 jge 0x6bfc
0192 lea ax, [bx + 6]
0195 shl al, 2
0198 mov di, word ptr [bp - 0x16]
019b mov byte ptr [di + 0x28e8], al
019f jmp 0x6c44
01a1 nop 
01a2 nop 
01a3 nop 
01a4 lea ax, [bx - 8]
01a7 and al, 0xfc
01a9 add al, 0x18
01ab mov bx, word ptr [bp - 0x16]
01ae mov byte ptr [bx + 0x28e8], al
01b2 jmp 0x6c44
01b4 cmp bx, 0x28
01b7 jge 0x6c4d
01b9 mov ax, bx
01bb mov cx, 4
01be cdq 
01bf idiv cx
01c1 cmp dx, 3
01c4 jmp 0x6c3b
01c6 cmp bx, 0x18
01c9 jge 0x6c30
01cb mov cx, word ptr [bp - 0x10]
01ce mov bx, word ptr [bp - 0x16]
01d1 mov byte ptr [bx + 0x28e8], 0x48
01d6 jmp 0x6c44
01d8 mov cx, word ptr [bp - 0x10]
01db cmp bx, 0x48
01de jl 0x6c4d
01e0 cmp bx, 0x4b
01e3 jge 0x6c4d
01e5 mov bx, word ptr [bp - 0x16]
01e8 inc byte ptr [bx + 0x28e8]
01ec mov es, word ptr [0xc5e4]
01f0 inc word ptr es:[0x9e84]
01f5 dec word ptr [bp - 0xc]
01f8 je 0x6c55
01fa jmp 0x6aca
01fd pop si
01fe pop di
01ff leave 
0200 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_fracSIN', 'offset': 27080, 'source': 'src/recovered/wf_fracSIN-85445ba91f.c', 'size': 70}
- {'symbol': '_fracCOS', 'offset': 27150, 'source': 'src/recovered/wf_fracCOS-62316b393c.c', 'size': 74}
- {'symbol': '_AddBlackAnts', 'offset': 27738, 'source': None, 'size': 163}
- {'symbol': '_AddRedAnts', 'offset': 27902, 'source': None, 'size': 173}

# Recovery task _MakeNewHoleB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 436 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 push 0x1f
0008 nop 
0009 push cs
000a call 0x158a ; _SRand1
000d add sp, 2
0010 mov word ptr [bp - 4], ax
0013 mov es, word ptr [0xc3fc]
0017 cmp word ptr es:[0x9b6e], 0
001d jne 0x1b28
001f jmp 0x1be2
0022 xor di, di
0024 mov ax, word ptr [bp - 4]
0027 add ax, di
0029 mov cx, 0x20
002c cdq 
002d idiv cx
002f mov bx, dx
0031 add bx, 2
0034 mov word ptr [bp - 6], bx
0037 shl bx, 6
003a add bx, word ptr [bp + 6]
003d mov al, byte ptr [bx + 0x28e8]
0041 sub ah, ah
0043 mov si, ax
0045 or si, si
0047 jne 0x1b54
0049 mov dx, 0x86
004c jmp 0x1b6a
004e cmp si, 2
0051 jne 0x1b5e
0053 mov dx, 0x8a
0056 jmp 0x1b6a
0058 cmp si, 3
005b je 0x1b59
005d cmp si, 0x5e
0060 jge 0x1b7a
0062 xor dx, dx
0064 or dx, dx
0066 jne 0x1b98
0068 inc di
0069 cmp di, 0x22
006c jl 0x1b2a
006e mov word ptr [bp - 8], di
0071 jmp 0x1bd0
0073 nop 
0074 cmp si, 0x62
0077 jge 0x1b84
0079 lea dx, [si + 0x22]
007c jmp 0x1b6a
007e cmp si, 0x66
0081 jne 0x1b8e
0083 mov dx, 0x85
0086 jmp 0x1b6a
0088 cmp si, 0x68
008b jne 0x1b68
008d mov dx, 0x84
0090 jmp 0x1b6a
0092 mov word ptr [bp - 8], di
0095 mov word ptr [bp - 2], dx
0098 mov al, byte ptr [bp - 2]
009b mov bx, word ptr [bp - 6]
009e shl bx, 6
00a1 add bx, word ptr [bp + 6]
00a4 mov byte ptr ss:[bx + 0x28e8], al
00a9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ac mov ds, ax
00ae mov ax, word ptr [bp - 6]
00b1 mov word ptr [0x835a], ax
00b4 mov ax, word ptr [bp + 6]
00b7 mov word ptr [0x835c], ax
00ba mov <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00bd mov es, cx
00bf mov word ptr es:[0x8352], ax
00c3 mov word ptr es:[0x8354], 0
00ca mov si, di
00cc cmp si, 0x22
00cf je 0x1bdc
00d1 push ss
00d2 pop ds
00d3 jmp 0x1c9c
00d6 push ss
00d7 pop ds
00d8 pop si
00d9 pop di
00da leave 
00db retf 
00dc xor si, si
00de mov di, ax
00e0 push word ptr [bp + 6]
00e3 mov ax, di
00e5 add ax, si
00e7 mov cx, 0x20
00ea cdq 
00eb idiv cx
00ed add dx, 2
00f0 mov word ptr [bp - 6], dx
00f3 push dx
00f4 push 1
00f6 nop 
00f7 push cs
00f8 call 0x5ad2 ; _IsClear3x3
00fb add sp, 6
00fe or ax, ax
0100 jne 0x1c12
0102 inc si
0103 cmp si, 0x22
0106 jl 0x1be6
0108 jmp 0x1c97
010b nop 
010c mov word ptr [bp - 8], si
010f mov cx, word ptr [bp + 6]
0112 mov bx, word ptr [bp - 6]
0115 mov si, bx
0117 shl si, 6
011a add si, cx
011c mov byte ptr ss:[si + 0x28e8], 0x50
0122 mov <resolved loader operand; see bindings> ; [{'operand_offset': 291, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0125 mov ds, ax
0127 mov word ptr [0x835a], bx
012b mov word ptr [0x835c], cx
012f mov <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0132 mov es, ax
0134 mov word ptr es:[0x8352], cx
0139 xor si, si
013b mov word ptr es:[0x8354], si
0140 mov di, si
0142 push ss
0143 pop ds
0144 mov es, word ptr [0xc3fe]
0148 mov al, byte ptr es:[di + 8]
014d cwde 
014e mov si, ax
0150 add si, word ptr [bp + 6]
0153 mov es, word ptr [0xc400]
0157 mov al, byte ptr es:[di]
015c cwde 
015d mov cx, ax
015f add cx, word ptr [bp - 6]
0162 js 0x1c8e
0164 cmp cx, 0x7f
0167 jg 0x1c8e
0169 or si, si
016b jl 0x1c8e
016d cmp si, 0x3f
0170 jg 0x1c8e
0172 mov bx, cx
0174 shl bx, 6
0177 add bx, si
0179 add bx, 0x28e8
017d cmp byte ptr [bx], 0x50
0180 jae 0x1c8e
0182 mov al, byte ptr [di + 0x230c]
0186 mov byte ptr [bx], al
0188 inc di
0189 cmp di, 8
018c jl 0x1c4a
018e mov si, word ptr [bp - 8]
0191 cmp si, 0x22
0194 je 0x1cb6
0196 mov al, byte ptr [bp - 6]
0199 mov es, word ptr [0xc402]
019d mov bx, word ptr [bp + 6]
01a0 mov byte ptr es:[bx - 0x7d2e], al
01a5 push 1
01a7 push bx
01a8 nop 
01a9 push cs
01aa call 0x1fe4 ; _DigTileB
01ad add sp, 4
01b0 pop si
01b1 pop di
01b2 leave 
01b3 retf 
```

## Known declaration examples

- `extern void far DigTileB(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far DigTileB(int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CreateNewHole', 'offset': 5914, 'source': None, 'size': 506}
- {'symbol': '_DigMyTile', 'offset': 6420, 'source': None, 'size': 498}
- {'symbol': '_CanBeHouseHole', 'offset': 7354, 'source': 'src/recovered/wf_CanBeHouseHole-987878d5ee.c', 'size': 72}
- {'symbol': '_MakeNewHoleR', 'offset': 7426, 'source': None, 'size': 650}

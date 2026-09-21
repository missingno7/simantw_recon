# Recovery task _DeadAntHere

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 353 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov bx, 0x9ea8
0009 mov es, word ptr [0xc344]
000d mov word ptr [bp - 6], bx
0010 mov word ptr [bp - 4], es
0013 inc word ptr es:[bx]
0016 cmp word ptr es:[bx], 0x64
001a jl 0x28e1
001c mov word ptr es:[bx], 0
0021 les bx, ptr [bp - 6]
0024 mov bx, word ptr es:[bx]
0027 mov es, word ptr [0xc346]
002b mov si, word ptr es:[bx - 0x628a]
0030 and si, 0xff
0034 mov es, word ptr [0xc348]
0038 mov al, byte ptr es:[bx - 0x637e]
003d sub ah, ah
003f mov di, ax
0041 mov bx, di
0043 shl bx, 6
0046 mov cl, byte ptr [bx + si + 0x28e8]
004a sub ch, ch
004c mov es, word ptr [0xc320]
0050 cmp word ptr es:[0x9b6e], 0
0056 jne 0x298c
0058 cmp cx, 0x10
005b jl 0x2934
005d cmp cx, 0x18
0060 jge 0x2934
0062 mov bx, di
0064 shl bx, 6
0067 mov di, bx
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
006e add di, si
0070 mov byte ptr [di + 0x28e8], al
0074 mov di, word ptr [bp + 8]
0077 mov si, word ptr [bp + 6]
007a mov ax, si
007c les bx, ptr [bp - 6]
007f mov bx, word ptr es:[bx]
0082 mov es, word ptr [0xc348]
0086 mov byte ptr es:[bx - 0x637e], al
008b mov es, word ptr [0xc346]
008f mov ax, di
0091 mov byte ptr es:[bx - 0x628a], al
0096 mov bx, si
0098 shl bx, 6
009b add bx, di
009d mov word ptr [bp - 8], bx
00a0 cmp byte ptr [bx + 0x28e8], 0x18
00a5 jb 0x296a
00a7 jmp 0x2a18
00aa cmp word ptr [bp + 0xa], 0
00ae je 0x2982
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
00b5 add al, 0x14
00b7 mov bx, word ptr [bp - 8]
00ba mov byte ptr [bx + 0x28e8], al
00be jmp 0x2a18
00c1 nop 
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
00c7 add al, 0x10
00c9 jmp 0x2977
00cb nop 
00cc cmp cx, 8
00cf jl 0x29a5
00d1 cmp cx, 0x18
00d4 jge 0x29a5
00d6 sub cx, 8
00d9 sar cx, 2
00dc mov bx, ax
00de shl bx, 6
00e1 mov byte ptr [bx + si + 0x28e8], cl
00e5 mov di, word ptr [bp + 8]
00e8 mov si, word ptr [bp + 6]
00eb mov ax, si
00ed les bx, ptr [bp - 6]
00f0 mov bx, word ptr es:[bx]
00f3 mov es, word ptr [0xc348]
00f7 mov byte ptr es:[bx - 0x637e], al
00fc mov es, word ptr [0xc346]
0100 mov ax, di
0102 mov byte ptr es:[bx - 0x628a], al
0107 mov bx, si
0109 shl bx, 6
010c add bx, di
010e mov word ptr [bp - 8], bx
0111 mov al, byte ptr [bx + 0x28e8]
0115 sub ah, ah
0117 mov word ptr [bp - 2], ax
011a cmp ax, 4
011d jge 0x2a18
011f cmp word ptr [bp + 0xa], 0
0123 je 0x29fc
0125 push 2
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
012c add sp, 2
012f mov cl, byte ptr [bp - 2]
0132 shl cl, 2
0135 add al, cl
0137 add al, 0xa
0139 jmp 0x2977
013c push 2
013e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 321, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0143 add sp, 2
0146 mov cl, byte ptr [bp - 2]
0149 add cl, 2
014c shl cl, 2
014f add cl, al
0151 mov bx, word ptr [bp - 8]
0154 mov byte ptr [bx + 0x28e8], cl
0158 mov byte ptr [bx + 0x68e8], 0
015d pop si
015e pop di
015f leave 
0160 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetWinner', 'offset': 9972, 'source': None, 'size': 241}
- {'symbol': '_DoFightA', 'offset': 10214, 'source': None, 'size': 217}
- {'symbol': '_RandTurn', 'offset': 10786, 'source': 'src/recovered/RandTurn.c', 'size': 30}
- {'symbol': '_DoAttackAnt', 'offset': 10816, 'source': None, 'size': 640}

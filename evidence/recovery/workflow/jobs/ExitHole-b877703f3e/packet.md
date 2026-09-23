# Recovery task _ExitHole

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 313 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 xor si, si
0008 mov es, word ptr [0xc42c]
000c mov al, byte ptr es:[si + 8]
0011 cwde 
0012 mov di, ax
0014 add di, word ptr [bp + 8]
0017 push di
0018 mov es, word ptr [0xc42e]
001c mov al, byte ptr es:[si]
0021 cwde 
0022 add ax, word ptr [bp + 6]
0025 mov word ptr [bp - 2], ax
0028 push ax
0029 nop 
002a push cs
002b call 0x9c02 ; _IsValidA
002e add sp, 4
0031 dec ax
0032 jne 0x2df7
0034 mov bx, word ptr [bp - 2]
0037 shl bx, 6
003a cmp byte ptr [bx + di + 0x28e8], 0x50
003f jb 0x2dfd
0041 inc si
0042 cmp si, 8
0045 jl 0x2dbe
0047 cmp si, 8
004a jne 0x2e0a
004c xor ax, ax
004e push ss
004f pop ds
0050 pop si
0051 pop di
0052 leave 
0053 retf 
0054 mov <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0057 mov es, ax
0059 mov <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
005c mov ds, ax
005e mov al, byte ptr [bp - 2]
0061 mov bx, word ptr es:[0x80f0]
0066 mov byte ptr [bx + 0x23a4], al
006a mov ax, di
006c mov byte ptr [bx + 0x278e], al
0070 mov al, byte ptr [bp + 0xa]
0073 mov byte ptr [bx + 0x2f62], al
0077 mov si, word ptr [bp + 0xc]
007a mov ax, si
007c mov byte ptr [bx + 0x2b78], al
0080 cmp si, 6
0083 jne 0x2e44
0085 mov al, byte ptr [bp + 0xe]
0088 mov byte ptr [bx + 0x334c], al
008c jmp 0x2e73
008e mov byte ptr [bx + 0x334c], 0
0093 cmp si, 3
0096 je 0x2e73
0098 cmp si, 7
009b je 0x2e73
009d mov bx, word ptr [bp + 6]
00a0 test byte ptr [bp + 0xa], 0x80
00a4 je 0x2e64
00a6 cmp bx, 0x40
00a9 jle 0x2e73
00ab jmp 0x2e69
00ad nop 
00ae cmp bx, 0x40
00b1 jge 0x2e73
00b3 mov bx, word ptr es:[0x80f0]
00b8 mov byte ptr [bx + 0x334c], 0x78
00bd cmp word ptr es:[0x80f0], 0x3e8
00c4 jge 0x2e86
00c6 inc word ptr es:[0x80f0]
00cb push ss
00cc pop ds
00cd jmp 0x2ee8
00cf nop 
00d0 xor si, si
00d2 mov di, si
00d4 cmp word ptr es:[0x80f0], si
00d9 jle 0x2ed3
00db cmp byte ptr [si + 0x2f62], 0
00e0 je 0x2eca
00e2 or di, di
00e4 je 0x2ecb
00e6 mov al, byte ptr [si + 0x2f62]
00ea mov bx, si
00ec add bx, di
00ee mov byte ptr [bx + 0x2f62], al
00f2 mov al, byte ptr [si + 0x23a4]
00f6 mov byte ptr [bx + 0x23a4], al
00fa mov al, byte ptr [si + 0x278e]
00fe mov byte ptr [bx + 0x278e], al
0102 mov al, byte ptr [si + 0x2b78]
0106 mov byte ptr [bx + 0x2b78], al
010a mov al, byte ptr [si + 0x334c]
010e mov byte ptr [bx + 0x334c], al
0112 jmp 0x2ecb
0114 dec di
0115 inc si
0116 cmp word ptr es:[0x80f0], si
011b jg 0x2e91
011d push ss
011e pop ds
011f add word ptr es:[0x80f0], di
0124 cmp word ptr es:[0x80f0], 0x3e8
012b jge 0x2ee8
012d inc word ptr es:[0x80f0]
0132 mov ax, 1
0135 pop si
0136 pop di
0137 leave 
0138 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simtwo_4CDC_StorePillarMap_4_scaffold-c16d27de40.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrownBList', 'offset': 11542, 'source': None, 'size': 79}
- {'symbol': '_DrownRList', 'offset': 11622, 'source': None, 'size': 79}
- {'symbol': '_AddAntToAList', 'offset': 12016, 'source': None, 'size': 89}
- {'symbol': '_AddAntToBList', 'offset': 12106, 'source': 'src/recovered/wf_tu_simone_2B42_FindInAList_7_scaffold-13e673a867.c', 'size': 89}

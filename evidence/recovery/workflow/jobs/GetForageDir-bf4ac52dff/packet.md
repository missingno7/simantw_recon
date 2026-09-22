# Recovery task _GetForageDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 384 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 or di, di
000b jne 0xae6
000d mov si, word ptr [bp + 8]
0010 or si, si
0012 jne 0xaca
0014 mov ax, 3
0017 jmp 0xc2c
001a cmp si, 0x3f
001d jne 0xad6
001f mov ax, 1
0022 pop si
0023 pop di
0024 leave 
0025 retf 
0026 push 3
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
002d add sp, 2
0030 inc ax
0031 pop si
0032 pop di
0033 leave 
0034 retf 
0035 nop 
0036 mov si, word ptr [bp + 8]
0039 or si, si
003b jne 0xb0a
003d cmp di, 0x7f
0040 jne 0xaf8
0042 mov ax, 5
0045 jmp 0xc2c
0048 push 3
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004f add sp, 2
0052 add ax, 3
0055 pop si
0056 pop di
0057 leave 
0058 retf 
0059 nop 
005a cmp di, 0x7f
005d jne 0xb2c
005f cmp si, 0x3f
0062 jne 0xb1a
0064 mov ax, 7
0067 jmp 0xc2c
006a push 3
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0071 add sp, 2
0074 add ax, 5
0077 pop si
0078 pop di
0079 leave 
007a retf 
007b nop 
007c cmp si, 0x3f
007f jne 0xb44
0081 push 3
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 134, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0088 add sp, 2
008b dec al
008d and ax, 7
0090 pop si
0091 pop di
0092 leave 
0093 retf 
0094 mov bx, di
0096 sar bx, 1
0098 mov cx, si
009a mov di, si
009c sar di, 1
009e mov al, byte ptr [bp + 0xc]
00a1 and ax, 0x80
00a4 mov word ptr [bp - 8], ax
00a7 or ax, ax
00a9 je 0xbc0
00ab mov es, word ptr [0xc4e4]
00af mov si, bx
00b1 shl si, 5
00b4 add si, di
00b6 mov al, byte ptr es:[si + 0x7ad2]
00bb sub ah, ah
00bd mov word ptr [bp - 0xc], ax
00c0 mov word ptr [bp - 0x10], di
00c3 mov word ptr [bp - 0xe], bx
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00cb mov word ptr [bp - 0xa], ax
00ce xor ax, ax
00d0 mov word ptr [bp - 6], ax
00d3 mov si, ax
00d5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00d8 mov ds, ax
00da mov <resolved loader operand; see bindings> ; [{'operand_offset': 219, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00dd mov es, ax
00df mov al, byte ptr es:[si]
00e4 cwde 
00e5 mov di, ax
00e7 add di, word ptr [bp - 0xe]
00ea and di, 0x3f
00ed mov <resolved loader operand; see bindings> ; [{'operand_offset': 238, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00f0 mov es, ax
00f2 mov cl, byte ptr es:[si + 8]
00f7 add cl, byte ptr [bp - 0x10]
00fa and cx, 0x1f
00fd cmp word ptr [bp - 8], 0
0101 je 0xbd2
0103 mov bx, di
0105 shl bx, 5
0108 add bx, cx
010a mov al, byte ptr [bx + 0x7ad2]
010e jmp 0xbdd
0110 mov es, word ptr [0xc4e4]
0114 mov si, bx
0116 shl si, 5
0119 add si, di
011b mov al, byte ptr es:[si + 0x6ad2]
0120 jmp 0xb6b
0122 mov bx, di
0124 shl bx, 5
0127 add bx, cx
0129 mov al, byte ptr [bx + 0x6ad2]
012d sub ah, ah
012f cmp ax, word ptr [bp - 6]
0132 jle 0xbea
0134 mov word ptr [bp - 6], ax
0137 mov word ptr [bp - 0xa], si
013a inc si
013b cmp si, 8
013e jl 0xb8a
0140 push ss
0141 pop ds
0142 mov si, word ptr [bp + 0xa]
0145 mov di, word ptr [bp - 6]
0148 or di, di
014a jle 0xc14
014c cmp word ptr [bp - 0xc], di
014f jle 0xc06
0151 mov ax, 0xffff
0154 jmp 0xc2c
0156 mov es, word ptr [0xc4e6]
015a mov bx, si
015c shl bx, 3
015f add bx, word ptr [bp - 0xa]
0162 jmp 0xc26
0164 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 359, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0169 mov bx, ax
016b mov ax, si
016d shl ax, 3
0170 add bx, ax
0172 mov es, word ptr [0xc4e6]
0176 mov al, byte ptr es:[bx + 0x24]
017b cwde 
017c pop si
017d pop di
017e leave 
017f retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_0000_DoDefendNest_5_scaffold-f75b17a9a4.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetNewModeB', 'offset': 2512, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 127}
- {'symbol': '_GetNewModeR', 'offset': 2640, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 95}
- {'symbol': '_GetNestDir', 'offset': 3120, 'source': None, 'size': 547}
- {'symbol': '_GetAlarmDir', 'offset': 3668, 'source': None, 'size': 286}

# Recovery task _ClearMyLife

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 465 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 cmp word ptr [bp + 6], 1
0009 jg 0x6346
000b mov bx, word ptr [bp + 8]
000e or bx, bx
0010 jl 0x635e
0012 cmp bx, 0x7f
0015 jg 0x635e
0017 cmp word ptr [bp + 0xa], 0
001b jl 0x635e
001d cmp word ptr [bp + 0xa], 0x3f
0021 jg 0x635e
0023 mov bx, 1
0026 jmp 0x6360
0028 cmp word ptr [bp + 8], 0
002c jl 0x635e
002e cmp word ptr [bp + 8], 0x3f
0032 jg 0x635e
0034 cmp word ptr [bp + 0xa], 0
0038 jl 0x635e
003a cmp word ptr [bp + 0xa], 0x3f
003e jle 0x6341
0040 xor bx, bx
0042 dec bx
0043 je 0x6366
0045 jmp 0x63f4
0048 mov si, 0xffff
004b push word ptr [bp + 0xa]
004e push word ptr [bp + 8]
0051 push word ptr [bp + 6]
0054 nop 
0055 push cs
0056 call 0x56da ; _IsValidLocation
0059 add sp, 6
005c dec ax
005d jne 0x63ca
005f mov ax, word ptr [bp + 6]
0062 or ax, ax
0064 jl 0x63c3
0066 jo 0x63c3
0068 dec ax
0069 jle 0x6392
006b dec ax
006c je 0x63a2
006e dec ax
006f je 0x63b2
0071 jmp 0x63c3
0073 nop 
0074 mov bx, word ptr [bp + 0xa]
0077 mov si, word ptr [bp + 8]
007a shl si, 6
007d mov si, word ptr [bx + si + 0x68e8]
0081 jmp 0x63bf
0083 nop 
0084 mov bx, word ptr [bp + 0xa]
0087 mov si, word ptr [bp + 8]
008a shl si, 6
008d mov si, word ptr [bx + si - 0x7718]
0091 jmp 0x63bf
0093 nop 
0094 mov bx, word ptr [bp + 0xa]
0097 mov si, word ptr [bp + 8]
009a shl si, 6
009d mov si, word ptr [bx + si - 0x6718]
00a1 and si, 0xff
00a5 or si, si
00a7 jne 0x63ca
00a9 mov si, 0xffff
00ac cmp si, 0xff
00b0 jne 0x63e3
00b2 push 0
00b4 push word ptr [bp + 0xa]
00b7 push word ptr [bp + 8]
00ba push word ptr [bp + 6]
00bd nop 
00be push cs
00bf call 0x5d18 ; _SetLife
00c2 add sp, 8
00c5 push word ptr [bp + 0xa]
00c8 push word ptr [bp + 8]
00cb push word ptr [bp + 6]
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
00d3 add sp, 6
00d6 cmp word ptr [bp + 0xc], 0x60
00da je 0x63fd
00dc jmp 0x6484
00df mov <resolved loader operand; see bindings> ; [{'operand_offset': 224, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00e2 mov es, ax
00e4 mov bx, word ptr [bp + 0xe]
00e7 xor bl, 4
00ea mov al, byte ptr es:[bx]
00ef cwde 
00f0 add ax, word ptr [bp + 8]
00f3 mov word ptr [bp - 2], ax
00f6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00f9 mov es, ax
00fb mov al, byte ptr es:[bx + 8]
0100 cwde 
0101 add ax, word ptr [bp + 0xa]
0104 mov word ptr [bp - 4], ax
0107 cmp word ptr [bp + 6], 1
010b jg 0x646a
010d cmp word ptr [bp - 2], 0
0111 jl 0x6438
0113 cmp word ptr [bp - 2], 0x7f
0117 jmp 0x6474
0119 nop 
011a xor dx, dx
011c dec dx
011d jne 0x6484
011f push ss
0120 pop ds
0121 mov si, 0xffff
0124 push ax
0125 push word ptr [bp - 2]
0128 push word ptr [bp + 6]
012b nop 
012c push cs
012d call 0x56da ; _IsValidLocation
0130 add sp, 6
0133 dec ax
0134 jne 0x64c2
0136 mov ax, word ptr [bp + 6]
0139 or ax, ax
013b jl 0x64bb
013d jo 0x64bb
013f dec ax
0140 jle 0x648a
0142 dec ax
0143 je 0x649a
0145 dec ax
0146 je 0x64aa
0148 jmp 0x64bb
014a nop 
014b nop 
014c cmp word ptr [bp - 2], 0
0150 jl 0x6438
0152 cmp word ptr [bp - 2], 0x3f
0156 jg 0x6438
0158 or ax, ax
015a jl 0x6438
015c cmp ax, 0x3f
015f jg 0x6438
0161 mov dx, 1
0164 jmp 0x643a
0166 push ss
0167 pop ds
0168 pop si
0169 leave 
016a retf 
016b nop 
016c mov bx, word ptr [bp - 4]
016f mov si, word ptr [bp - 2]
0172 shl si, 6
0175 mov si, word ptr [bx + si + 0x68e8]
0179 jmp 0x64b7
017b nop 
017c mov bx, word ptr [bp - 4]
017f mov si, word ptr [bp - 2]
0182 shl si, 6
0185 mov si, word ptr [bx + si - 0x7718]
0189 jmp 0x64b7
018b nop 
018c mov bx, word ptr [bp - 4]
018f mov si, word ptr [bp - 2]
0192 shl si, 6
0195 mov si, word ptr [bx + si - 0x6718]
0199 and si, 0xff
019d or si, si
019f jne 0x64c2
01a1 mov si, 0xffff
01a4 cmp si, 0xfe
01a8 jne 0x64db
01aa push 0
01ac push word ptr [bp - 4]
01af push word ptr [bp - 2]
01b2 push word ptr [bp + 6]
01b5 nop 
01b6 push cs
01b7 call 0x5d18 ; _SetLife
01ba add sp, 8
01bd push word ptr [bp - 4]
01c0 push word ptr [bp - 2]
01c3 push word ptr [bp + 6]
01c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 457, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
01cb add sp, 6
01ce pop si
01cf leave 
01d0 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far IsValidLocation(int plane, int x, int y);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far SetLife(int plane, int x, int y, int code);` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_SetMap-0b7117ef15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetMap', 'offset': 24954, 'source': 'src/recovered/wf_SetMap-0b7117ef15.c', 'size': 162}
- {'symbol': '_ClearLife', 'offset': 25116, 'source': None, 'size': 258}
- {'symbol': '_SetQueenTail', 'offset': 25840, 'source': None, 'size': 70}
- {'symbol': '_SetMyLife', 'offset': 25910, 'source': None, 'size': 196}

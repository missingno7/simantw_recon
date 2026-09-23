# Recovery task _DropPebble

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 662 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 6], 1
000a jle 0x79cb
000c jmp 0x7abc
000f jg 0x79e6
0011 mov di, word ptr [bp + 8]
0014 mov si, word ptr [bp + 0xa]
0017 push si
0018 push di
0019 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItHole
001e add sp, 4
0021 mov word ptr [bp - 2], ax
0024 mov cx, ax
0026 jmp 0x7a78
0029 nop 
002a mov si, word ptr [bp + 0xa]
002d or si, si
002f jle 0x79f6
0031 xor cx, cx
0033 mov di, word ptr [bp + 8]
0036 jmp 0x7a78
0039 nop 
003a mov dx, 0xffff
003d cmp word ptr [bp + 6], 1
0041 jg 0x7a1a
0043 mov di, word ptr [bp + 8]
0046 or di, di
0048 jl 0x7a2f
004a cmp di, 0x7f
004d jg 0x7a2f
004f or si, si
0051 jl 0x7a2f
0053 cmp si, 0x3f
0056 jg 0x7a2f
0058 mov cx, 1
005b jmp 0x7a31
005d nop 
005e mov di, word ptr [bp + 8]
0061 or di, di
0063 jl 0x7a2f
0065 cmp di, 0x3f
0068 jg 0x7a2f
006a or si, si
006c jl 0x7a2f
006e cmp si, 0x3f
0071 jle 0x7a14
0073 xor cx, cx
0075 dec cx
0076 jne 0x7a6b
0078 mov ax, word ptr [bp + 6]
007b or ax, ax
007d jl 0x7a6b
007f jo 0x7a6b
0081 dec ax
0082 jle 0x7a48
0084 dec ax
0085 je 0x7a54
0087 dec ax
0088 je 0x7a60
008a jmp 0x7a6b
008c mov bx, di
008e shl bx, 6
0091 mov dl, byte ptr [bx + si + 0x28e8]
0095 jmp 0x7a69
0097 nop 
0098 mov bx, di
009a shl bx, 6
009d mov dl, byte ptr [bx + si + 0x48e8]
00a1 jmp 0x7a69
00a3 nop 
00a4 mov bx, di
00a6 shl bx, 6
00a9 mov dl, byte ptr [bx + si + 0x58e8]
00ad sub dh, dh
00af cmp dx, 0x18
00b2 jne 0x7a76
00b4 mov cx, 1
00b7 jmp 0x7a78
00b9 nop 
00ba xor cx, cx
00bc or cx, cx
00be je 0x7ab5
00c0 cmp di, 0x40
00c3 jge 0x7a9c
00c5 mov es, word ptr [0xc4a8]
00c9 mov al, byte ptr es:[si - 0x7d2e]
00ce sub ah, ah
00d0 cmp ax, di
00d2 jne 0x7a9c
00d4 mov bx, si
00d6 shl bx, 6
00d9 mov byte ptr [bx + 0x48e8], 0x31
00de jmp 0x7ab5
00e0 mov es, word ptr [0xc4aa]
00e4 mov al, byte ptr es:[si - 0x7cee]
00e9 sub ah, ah
00eb cmp ax, di
00ed jne 0x7ab5
00ef mov bx, si
00f1 shl bx, 6
00f4 mov byte ptr [bx + 0x58e8], 0x31
00f9 mov dx, 0x51
00fc jmp 0x7bbb
00ff nop 
0100 cmp word ptr [bp + 6], 1
0104 jg 0x7ad4
0106 push word ptr [bp + 0xa]
0109 push word ptr [bp + 8]
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItHole
0111 add sp, 4
0114 mov si, ax
0116 jmp 0x7adc
0118 cmp word ptr [bp + 0xa], 0
011c jle 0x7afc
011e xor si, si
0120 or si, si
0122 jne 0x7ae3
0124 jmp 0x7bb8
0127 cmp word ptr [bp + 6], 2
012b je 0x7aec
012d jmp 0x7b98
0130 mov es, word ptr [0xc4a8]
0134 mov bx, word ptr [bp + 8]
0137 mov bl, byte ptr es:[bx - 0x7d2e]
013c jmp 0x7ba4
013f nop 
0140 mov cx, 0xffff
0143 cmp word ptr [bp + 6], 1
0147 jg 0x7b22
0149 mov di, word ptr [bp + 8]
014c or di, di
014e jl 0x7b3a
0150 cmp di, 0x7f
0153 jg 0x7b3a
0155 cmp word ptr [bp + 0xa], 0
0159 jl 0x7b3a
015b cmp word ptr [bp + 0xa], 0x3f
015f jg 0x7b3a
0161 mov dx, 1
0164 jmp 0x7b3c
0166 cmp word ptr [bp + 8], 0
016a jl 0x7b3a
016c cmp word ptr [bp + 8], 0x3f
0170 jg 0x7b3a
0172 cmp word ptr [bp + 0xa], 0
0176 jl 0x7b3a
0178 cmp word ptr [bp + 0xa], 0x3f
017c jle 0x7b1d
017e xor dx, dx
0180 mov word ptr [bp - 2], cx
0183 dec dx
0184 je 0x7b46
0186 mov dx, cx
0188 jmp 0x7b89
018a mov ax, word ptr [bp + 6]
018d or ax, ax
018f jl 0x7b42
0191 jo 0x7b42
0193 dec ax
0194 jle 0x7b5a
0196 dec ax
0197 je 0x7b6a
0199 dec ax
019a je 0x7b7a
019c jmp 0x7b42
019e mov si, word ptr [bp + 8]
01a1 shl si, 6
01a4 mov bx, word ptr [bp + 0xa]
01a7 mov dl, byte ptr [bx + si + 0x28e8]
01ab jmp 0x7b87
01ad nop 
01ae mov si, word ptr [bp + 8]
01b1 shl si, 6
01b4 mov bx, word ptr [bp + 0xa]
01b7 mov dl, byte ptr [bx + si + 0x48e8]
01bb jmp 0x7b87
01bd nop 
01be mov si, word ptr [bp + 8]
01c1 shl si, 6
01c4 mov bx, word ptr [bp + 0xa]
01c7 mov dl, byte ptr [bx + si + 0x58e8]
01cb sub dh, dh
01cd cmp dx, 0x18
01d0 je 0x7b91
01d2 jmp 0x7ada
01d5 mov si, 1
01d8 jmp 0x7adc
01db nop 
01dc mov es, word ptr [0xc4aa]
01e0 mov bx, word ptr [bp + 8]
01e3 mov bl, byte ptr es:[bx - 0x7cee]
01e8 sub bh, bh
01ea mov si, bx
01ec shl si, 6
01ef mov bx, word ptr [bp + 8]
01f2 mov byte ptr [bx + si + 0x28e8], 0x51
01f7 mov dx, 0x31
01fa jmp 0x7bbb
01fc mov dx, 0x30
01ff cmp word ptr [bp + 6], 1
0203 jg 0x7bde
0205 cmp word ptr [bp + 8], 0
0209 jl 0x7bf6
020b cmp word ptr [bp + 8], 0x7f
020f jg 0x7bf6
0211 cmp word ptr [bp + 0xa], 0
0215 jl 0x7bf6
0217 cmp word ptr [bp + 0xa], 0x3f
021b jg 0x7bf6
021d mov bx, 1
0220 jmp 0x7bf8
0222 cmp word ptr [bp + 8], 0
0226 jl 0x7bf6
0228 cmp word ptr [bp + 8], 0x3f
022c jg 0x7bf6
022e cmp word ptr [bp + 0xa], 0
0232 jl 0x7bf6
0234 cmp word ptr [bp + 0xa], 0x3f
0238 jle 0x7bd9
023a xor bx, bx
023c dec bx
023d jne 0x7c4e
023f mov ax, word ptr [bp + 6]
0242 or ax, ax
0244 jl 0x7c3d
0246 jo 0x7c3d
0248 dec ax
0249 jle 0x7c10
024b dec ax
024c je 0x7c20
024e dec ax
024f je 0x7c30
0251 jmp 0x7c3d
0253 nop 
0254 mov si, word ptr [bp + 8]
0257 shl si, 6
025a mov bx, word ptr [bp + 0xa]
025d mov byte ptr [bx + si + 0x28e8], dl
0261 jmp 0x7c3d
0263 nop 
0264 mov si, word ptr [bp + 8]
0267 shl si, 6
026a mov bx, word ptr [bp + 0xa]
026d mov byte ptr [bx + si + 0x48e8], dl
0271 jmp 0x7c3d
0273 nop 
0274 mov si, word ptr [bp + 8]
0277 shl si, 6
027a mov bx, word ptr [bp + 0xa]
027d mov byte ptr [bx + si + 0x58e8], dl
0281 push word ptr [bp + 0xa]
0284 push word ptr [bp + 8]
0287 push word ptr [bp + 6]
028a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 653, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
028f add sp, 6
0292 pop si
0293 pop di
0294 leave 
0295 retf 
```

## Known declaration examples

- `extern int far IsItHole(int x, int y);` — src/recovered/wf_IsItAHole-fd9d6ad240.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoLifeExchange', 'offset': 26690, 'source': None, 'size': 3379}
- {'symbol': '_DropMyFood', 'offset': 30070, 'source': None, 'size': 1093}
- {'symbol': '_DropMyRock', 'offset': 31826, 'source': None, 'size': 1334}
- {'symbol': '_DropMyEgg', 'offset': 33160, 'source': None, 'size': 1126}

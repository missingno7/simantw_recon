# Recovery task _SetLife

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 432 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 cmp word ptr [bp + 6], 1
0008 jg 0x5d40
000a mov bx, word ptr [bp + 8]
000d or bx, bx
000f jl 0x5d58
0011 cmp bx, 0x7f
0014 jg 0x5d58
0016 cmp word ptr [bp + 0xa], 0
001a jl 0x5d58
001c cmp word ptr [bp + 0xa], 0x3f
0020 jg 0x5d58
0022 mov bx, 1
0025 jmp 0x5d5a
0027 nop 
0028 cmp word ptr [bp + 8], 0
002c jl 0x5d58
002e cmp word ptr [bp + 8], 0x3f
0032 jg 0x5d58
0034 cmp word ptr [bp + 0xa], 0
0038 jl 0x5d58
003a cmp word ptr [bp + 0xa], 0x3f
003e jle 0x5d3a
0040 xor bx, bx
0042 dec bx
0043 je 0x5d60
0045 jmp 0x5ec5
0048 mov ax, word ptr [bp + 6]
004b or ax, ax
004d jge 0x5d6a
004f jmp 0x5eb4
0052 jno 0x5d6f
0054 jmp 0x5eb4
0057 dec ax
0058 jle 0x5d7e
005a dec ax
005b je 0x5d92
005d dec ax
005e jne 0x5d7b
0060 jmp 0x5e16
0063 jmp 0x5eb4
0066 mov al, byte ptr [bp + 0xc]
0069 mov si, word ptr [bp + 8]
006c shl si, 6
006f mov bx, word ptr [bp + 0xa]
0072 mov byte ptr [bx + si + 0x68e8], al
0076 jmp 0x5eb4
0079 nop 
007a mov dx, word ptr [bp + 0xc]
007d mov ax, dx
007f mov si, word ptr [bp + 8]
0082 shl si, 6
0085 mov bx, word ptr [bp + 0xa]
0088 mov byte ptr [bx + si - 0x7718], dl
008c or ax, ax
008e jg 0x5dab
0090 jmp 0x5eb4
0093 cmp word ptr [bp + 6], 2
0097 jge 0x5db4
0099 jmp 0x5e90
009c cmp word ptr [bp + 8], 0
00a0 jl 0x5dce
00a2 cmp word ptr [bp + 8], 0x3f
00a6 jg 0x5dce
00a8 or bx, bx
00aa jl 0x5dce
00ac cmp bx, 0x3f
00af jg 0x5dce
00b1 mov dx, 1
00b4 jmp 0x5dd0
00b6 xor dx, dx
00b8 or dx, dx
00ba jne 0x5dd7
00bc jmp 0x5e90
00bf push bx
00c0 push word ptr [bp + 8]
00c3 push word ptr [bp + 6]
00c6 nop 
00c7 push cs
00c8 call 0x60e2 ; _GetMap
00cb add sp, 6
00ce mov si, ax
00d0 push si
00d1 nop 
00d2 push cs
00d3 call 0x1182 ; _IsItDirt
00d6 add sp, 2
00d9 or ax, ax
00db je 0x5dfc
00dd mov dx, 1
00e0 jmp 0x5e92
00e3 nop 
00e4 cmp word ptr [bp + 6], 2
00e8 jl 0x5e0c
00ea cmp si, 0x1c
00ed jl 0x5e0c
00ef cmp si, 0x1f
00f2 jle 0x5e89
00f4 xor bx, bx
00f6 cmp bx, 1
00f9 sbb dx, dx
00fb inc dx
00fc jmp 0x5e92
00fe mov dx, word ptr [bp + 0xc]
0101 mov ax, dx
0103 mov si, word ptr [bp + 8]
0106 shl si, 6
0109 mov bx, word ptr [bp + 0xa]
010c mov byte ptr [bx + si - 0x6718], dl
0110 or ax, ax
0112 jg 0x5e2f
0114 jmp 0x5eb4
0117 cmp word ptr [bp + 6], 2
011b jl 0x5e90
011d cmp word ptr [bp + 8], 0
0121 jl 0x5e52
0123 cmp word ptr [bp + 8], 0x3f
0127 jg 0x5e52
0129 or bx, bx
012b jl 0x5e52
012d cmp bx, 0x3f
0130 jg 0x5e52
0132 mov dx, 1
0135 jmp 0x5e54
0137 nop 
0138 nop 
0139 nop 
013a xor dx, dx
013c or dx, dx
013e je 0x5e90
0140 push bx
0141 push word ptr [bp + 8]
0144 push word ptr [bp + 6]
0147 nop 
0148 push cs
0149 call 0x60e2 ; _GetMap
014c add sp, 6
014f mov si, ax
0151 push si
0152 nop 
0153 push cs
0154 call 0x1182 ; _IsItDirt
0157 add sp, 2
015a or ax, ax
015c je 0x5e79
015e jmp 0x5df5
0161 cmp word ptr [bp + 6], 2
0165 jl 0x5e0c
0167 cmp si, 0x1c
016a jl 0x5e0c
016c cmp si, 0x1f
016f jg 0x5e0c
0171 mov bx, 1
0174 jmp 0x5e0e
0177 nop 
0178 xor dx, dx
017a dec dx
017b jne 0x5eb4
017d push word ptr [bp + 0xa]
0180 push word ptr [bp + 8]
0183 push word ptr [bp + 6]
0186 nop 
0187 push cs
0188 call 0x1914 ; _DigMyTile
018b add sp, 6
018e push 0x3f
0190 push 0
0192 push 0x13
0194 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 407, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0199 add sp, 6
019c push word ptr [bp + 0xa]
019f push word ptr [bp + 8]
01a2 push word ptr [bp + 6]
01a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 424, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
01aa add sp, 6
01ad pop si
01ae leave 
01af retf 
```

## Known declaration examples

- `extern void far DigMyTile(int plane, int x, int y);` — src/recovered/wf_EnterNest-606488b329.c
- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_ConnectWall-bbdd72e7a8.c
- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_WallNeighbors-7ac5fa173f.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_SetMap-0b7117ef15.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsClearTile', 'offset': 23340, 'source': None, 'size': 332}
- {'symbol': '_AddAntToList', 'offset': 23672, 'source': 'src/recovered/wf_AddAntToList-44a11714fc.c', 'size': 159}
- {'symbol': '_IsThisEgg', 'offset': 24264, 'source': 'src/recovered/IsThisEgg.c', 'size': 28}
- {'symbol': '_IsThisGrass', 'offset': 24292, 'source': 'src/recovered/wf_IsThisGrass-f06e1489c1.c', 'size': 32}

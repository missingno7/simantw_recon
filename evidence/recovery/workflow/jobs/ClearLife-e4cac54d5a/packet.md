# Recovery task _ClearLife

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 258 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 cmp word ptr [bp + 6], 1
0008 jg 0x6244
000a mov bx, word ptr [bp + 8]
000d or bx, bx
000f jl 0x625c
0011 cmp bx, 0x7f
0014 jg 0x625c
0016 cmp word ptr [bp + 0xa], 0
001a jl 0x625c
001c cmp word ptr [bp + 0xa], 0x3f
0020 jg 0x625c
0022 mov bx, 1
0025 jmp 0x625e
0027 nop 
0028 cmp word ptr [bp + 8], 0
002c jl 0x625c
002e cmp word ptr [bp + 8], 0x3f
0032 jg 0x625c
0034 cmp word ptr [bp + 0xa], 0
0038 jl 0x625c
003a cmp word ptr [bp + 0xa], 0x3f
003e jle 0x623e
0040 xor bx, bx
0042 dec bx
0043 je 0x6264
0045 jmp 0x631b
0048 mov dx, 0xffff
004b cmp word ptr [bp + 6], 1
004f jg 0x628a
0051 cmp word ptr [bp + 8], 0
0055 jl 0x62a2
0057 cmp word ptr [bp + 8], 0x7f
005b jg 0x62a2
005d cmp word ptr [bp + 0xa], 0
0061 jl 0x62a2
0063 cmp word ptr [bp + 0xa], 0x3f
0067 jg 0x62a2
0069 mov bx, 1
006c jmp 0x62a4
006e cmp word ptr [bp + 8], 0
0072 jl 0x62a2
0074 cmp word ptr [bp + 8], 0x3f
0078 jg 0x62a2
007a cmp word ptr [bp + 0xa], 0
007e jl 0x62a2
0080 cmp word ptr [bp + 0xa], 0x3f
0084 jle 0x6285
0086 xor bx, bx
0088 dec bx
0089 jne 0x62f2
008b mov ax, word ptr [bp + 6]
008e or ax, ax
0090 jl 0x62eb
0092 jo 0x62eb
0094 dec ax
0095 jle 0x62bc
0097 dec ax
0098 je 0x62cc
009a dec ax
009b je 0x62dc
009d jmp 0x62eb
009f nop 
00a0 mov si, word ptr [bp + 8]
00a3 shl si, 6
00a6 mov bx, word ptr [bp + 0xa]
00a9 mov dl, byte ptr [bx + si + 0x68e8]
00ad jmp 0x62e9
00af nop 
00b0 mov si, word ptr [bp + 8]
00b3 shl si, 6
00b6 mov bx, word ptr [bp + 0xa]
00b9 mov dl, byte ptr [bx + si - 0x7718]
00bd jmp 0x62e9
00bf nop 
00c0 mov si, word ptr [bp + 8]
00c3 shl si, 6
00c6 mov bx, word ptr [bp + 0xa]
00c9 mov dl, byte ptr [bx + si - 0x6718]
00cd sub dh, dh
00cf or dx, dx
00d1 jne 0x62f2
00d3 mov dx, 0xffff
00d6 cmp dx, word ptr [bp + 0xc]
00d9 jne 0x630a
00db push 0
00dd push word ptr [bp + 0xa]
00e0 push word ptr [bp + 8]
00e3 push word ptr [bp + 6]
00e6 nop 
00e7 push cs
00e8 call 0x5d18 ; _SetLife
00eb add sp, 8
00ee push word ptr [bp + 0xa]
00f1 push word ptr [bp + 8]
00f4 push word ptr [bp + 6]
00f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 250, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
00fc add sp, 6
00ff pop si
0100 leave 
0101 retf 
```

## Known declaration examples

- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_SetMap-0b7117ef15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetMap', 'offset': 24802, 'source': 'src/recovered/wf_GetMap-cddf28f960.c', 'size': 152}
- {'symbol': '_SetMap', 'offset': 24954, 'source': 'src/recovered/wf_SetMap-0b7117ef15.c', 'size': 162}
- {'symbol': '_ClearMyLife', 'offset': 25374, 'source': None, 'size': 465}
- {'symbol': '_SetQueenTail', 'offset': 25840, 'source': None, 'size': 70}

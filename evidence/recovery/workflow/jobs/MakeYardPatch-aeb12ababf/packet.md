# Recovery task _MakeYardPatch

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 401 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc430]
000a cmp word ptr es:[0x9b6e], 0
0010 je 0x41ca
0012 mov ax, 0x3e8
0015 mov es, word ptr [0xc432]
0019 mov word ptr es:[0x85ea], ax
001d push ax
001e push 0
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _OverlayTileSet
0025 add sp, 4
0028 xor di, di
002a xor si, si
002c mov word ptr [bp - 2], di
002f nop 
0030 push cs
0031 call 0x160e ; _SRand16
0034 mov bx, di
0036 add bx, si
0038 mov byte ptr [bx + 0x28e8], al
003c inc si
003d cmp si, 0x40
0040 jl 0x41d1
0042 add di, 0x40
0045 cmp di, 0x2000
0049 jl 0x41cc
004b nop 
004c push cs
004d call 0x4334 ; _AddRocks
0050 nop 
0051 push cs
0052 call 0x15ce ; _SRand4
0055 inc ax
0056 push ax
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitAntLions
005c add sp, 2
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitPillar
0064 mov word ptr [bp - 2], 0x14
0069 push 0x7d
006b nop 
006c push cs
006d call 0x158a ; _SRand1
0070 add sp, 2
0073 mov si, ax
0075 inc si
0076 push 0x3d
0078 nop 
0079 push cs
007a call 0x158a ; _SRand1
007d add sp, 2
0080 mov di, ax
0082 inc di
0083 mov bx, si
0085 shl bx, 6
0088 add bx, di
008a mov word ptr [bp - 4], bx
008d cmp byte ptr [bx + 0x28e8], 0x18
0092 jae 0x425f
0094 cmp byte ptr [bx + 0x2928], 0x18
0099 jae 0x425f
009b cmp byte ptr [bx + 0x28e9], 0x18
00a0 jae 0x425f
00a2 cmp byte ptr [bx + 0x2929], 0x18
00a7 jae 0x425f
00a9 mov byte ptr [bx + 0x28e8], 0x20
00ae mov byte ptr [bx + 0x2928], 0x21
00b3 mov byte ptr [bx + 0x28e9], 0x22
00b8 mov byte ptr [bx + 0x2929], 0x23
00bd dec word ptr [bp - 2]
00c0 jne 0x420b
00c2 mov word ptr [bp - 2], 0x1e
00c7 push 0x7d
00c9 nop 
00ca push cs
00cb call 0x158a ; _SRand1
00ce add sp, 2
00d1 mov si, ax
00d3 inc si
00d4 push 0x3d
00d6 nop 
00d7 push cs
00d8 call 0x158a ; _SRand1
00db add sp, 2
00de mov di, ax
00e0 inc di
00e1 mov bx, si
00e3 shl bx, 6
00e6 add bx, di
00e8 mov word ptr [bp - 4], bx
00eb cmp byte ptr [bx + 0x28e8], 0x18
00f0 jae 0x42b6
00f2 cmp byte ptr [bx + 0x2928], 0x18
00f7 jae 0x42b6
00f9 push 2
00fb nop 
00fc push cs
00fd call 0x158a ; _SRand1
0100 add sp, 2
0103 add al, 0x12
0105 shl al, 1
0107 mov bx, word ptr [bp - 4]
010a mov byte ptr [bx + 0x28e8], al
010e inc al
0110 mov byte ptr [bx + 0x2928], al
0114 dec word ptr [bp - 2]
0117 jne 0x4269
0119 mov word ptr [bp - 2], 0x64
011e push 0x7d
0120 nop 
0121 push cs
0122 call 0x158a ; _SRand1
0125 add sp, 2
0128 mov si, ax
012a inc si
012b push 0x3d
012d nop 
012e push cs
012f call 0x158a ; _SRand1
0132 add sp, 2
0135 mov di, ax
0137 inc di
0138 mov bx, si
013a shl bx, 6
013d add bx, di
013f mov word ptr [bp - 4], bx
0142 cmp byte ptr [bx + 0x28e8], 0x18
0147 jae 0x42f0
0149 mov byte ptr [bx + 0x28e8], 0x28
014e dec word ptr [bp - 2]
0151 jne 0x42c0
0153 mov word ptr [bp - 2], 0x80
0158 push 0x7d
015a nop 
015b push cs
015c call 0x158a ; _SRand1
015f add sp, 2
0162 mov si, ax
0164 inc si
0165 push 0x3d
0167 nop 
0168 push cs
0169 call 0x158a ; _SRand1
016c add sp, 2
016f mov di, ax
0171 inc di
0172 mov bx, si
0174 shl bx, 6
0177 add bx, di
0179 mov word ptr [bp - 4], bx
017c cmp byte ptr [bx + 0x28e8], 0x18
0181 jae 0x432a
0183 mov byte ptr [bx + 0x28e8], 0x51
0188 dec word ptr [bp - 2]
018b jne 0x42fa
018d pop si
018e pop di
018f leave 
0190 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FillMap', 'offset': 16212, 'source': None, 'size': 85}
- {'symbol': '_FillMapLegs', 'offset': 16298, 'source': None, 'size': 503}
- {'symbol': '_AddRocks', 'offset': 17204, 'source': None, 'size': 440}
- {'symbol': '_AddRock5', 'offset': 17644, 'source': None, 'size': 191}

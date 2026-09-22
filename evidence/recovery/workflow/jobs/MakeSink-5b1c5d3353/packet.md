# Recovery task _MakeSink

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 487 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov bx, 0x3242
0009 mov ax, 0x101
000c mov cx, 0xf
000f mov di, bx
0011 push ds
0012 pop es
0013 rep stosw word ptr es:[di], ax
0015 stosb byte ptr es:[di], al
0016 add bx, 0x40
0019 cmp bx, 0x3fc2
001d jbe 0x3765
001f mov bx, 0x3349
0022 mov ax, 0xc2c2
0025 mov cx, 0xa
0028 mov di, bx
002a rep stosw word ptr es:[di], ax
002c stosb byte ptr es:[di], al
002d add bx, 0x40
0030 cmp bx, 0x3a09
0034 jbe 0x377e
0036 mov bx, 0x338b
0039 mov ax, 0xc1c1
003c mov cx, 9
003f mov di, bx
0041 rep stosw word ptr es:[di], ax
0043 stosb byte ptr es:[di], al
0044 add bx, 0x40
0047 cmp bx, 0x3a0b
004b jbe 0x3795
004d push 0x35
004f push 0x20
0051 push 0x44
0053 push 0x28
0055 nop 
0056 push cs
0057 call 0x3aa2 ; _TileFrame2
005a add sp, 8
005d mov si, 0x3b49
0060 mov ax, 0xc2c2
0063 mov cx, 0xa
0066 mov di, si
0068 push ds
0069 pop es
006a rep stosw word ptr es:[di], ax
006c stosb byte ptr es:[di], al
006d add si, 0x40
0070 cmp si, 0x3f09
0074 jbe 0x37bc
0076 mov bx, 0x3b8b
0079 mov ax, 0xc1c1
007c mov cx, 9
007f mov di, bx
0081 rep stosw word ptr es:[di], ax
0083 stosb byte ptr es:[di], al
0084 add bx, 0x40
0087 cmp bx, 0x3f0b
008b jbe 0x37d5
008d push 0x35
008f push 0x20
0091 push 0x58
0093 push 0x48
0095 nop 
0096 push cs
0097 call 0x3aa2 ; _TileFrame2
009a add sp, 8
009d push 0x38
009f push 0x1a
00a1 push 0x5b
00a3 push 0x25
00a5 nop 
00a6 push cs
00a7 call 0x3944 ; _TileFrame1
00aa add sp, 8
00ad xor di, di
00af mov word ptr [bp - 4], di
00b2 mov word ptr [bp - 2], di
00b5 mov dx, di
00b7 xor si, si
00b9 mov di, word ptr [bp - 4]
00bc add di, 0x233c
00c0 mov word ptr [bp - 2], dx
00c3 mov bx, dx
00c5 mov al, byte ptr [di]
00c7 add di, 5
00ca mov byte ptr [bx + si + 0x3403], al
00ce inc si
00cf cmp si, 5
00d2 jl 0x381f
00d4 inc word ptr [bp - 4]
00d7 add dx, 0x40
00da cmp dx, 0x140
00de jl 0x3813
00e0 xor dx, dx
00e2 mov cx, dx
00e4 xor si, si
00e6 mov di, cx
00e8 add di, 0x233c
00ec mov word ptr [bp - 2], dx
00ef mov word ptr [bp - 4], cx
00f2 mov bx, dx
00f4 mov al, byte ptr [di]
00f6 add di, 5
00f9 mov byte ptr [bx + si + 0x3803], al
00fd inc si
00fe cmp si, 5
0101 jl 0x384e
0103 inc cx
0104 add dx, 0x40
0107 cmp dx, 0x140
010b jl 0x3840
010d mov byte ptr [0x3885], 0x4d
0112 xor dx, dx
0114 mov cx, dx
0116 xor si, si
0118 mov di, cx
011a add di, 0x233c
011e mov word ptr [bp - 2], dx
0121 mov word ptr [bp - 4], cx
0124 mov bx, dx
0126 mov al, byte ptr [di]
0128 add di, 5
012b mov byte ptr [bx + si + 0x3603], al
012f inc si
0130 cmp si, 5
0133 jl 0x3880
0135 inc cx
0136 add dx, 0x40
0139 cmp dx, 0x140
013d jl 0x3872
013f xor dx, dx
0141 mov cx, dx
0143 xor si, si
0145 mov di, cx
0147 add di, 0x233c
014b mov word ptr [bp - 2], dx
014e mov word ptr [bp - 4], cx
0151 mov bx, dx
0153 mov al, byte ptr [di]
0155 add di, 5
0158 mov byte ptr [bx + si + 0x360c], al
015c inc si
015d cmp si, 5
0160 jl 0x38ad
0162 inc cx
0163 add dx, 0x40
0166 cmp dx, 0x140
016a jl 0x389f
016c mov bx, 0x3605
016f mov ax, 0x4e4e
0172 mov cx, 5
0175 mov di, bx
0177 push ds
0178 pop es
0179 rep stosw word ptr es:[di], ax
017b add bx, 0x40
017e cmp bx, 0x3705
0182 jbe 0x38cb
0184 mov bx, 0x3605
0187 mov ax, 0x4343
018a mov cx, 5
018d mov di, bx
018f rep stosw word ptr es:[di], ax
0191 add bx, 0x40
0194 cmp bx, 0x3605
0198 jbe 0x38e3
019a mov bx, 0x3705
019d mov ax, 0x4444
01a0 mov cx, 5
01a3 mov di, bx
01a5 rep stosw word ptr es:[di], ax
01a7 add bx, 0x40
01aa cmp bx, 0x3705
01ae jbe 0x38f9
01b0 mov byte ptr [0x3610], 0x45
01b5 mov byte ptr [0x3710], 0x48
01ba mov si, 0x3691
01bd mov ax, 0xc2c2
01c0 mov cx, 1
01c3 mov di, si
01c5 rep stosw word ptr es:[di], ax
01c7 add si, 0x40
01ca cmp si, 0x3711
01ce jbe 0x3919
01d0 mov bx, 0x374b
01d3 mov cx, 4
01d6 mov di, bx
01d8 rep stosw word ptr es:[di], ax
01da add bx, 0x40
01dd cmp bx, 0x378b
01e1 jbe 0x392f
01e3 pop si
01e4 pop di
01e5 leave 
01e6 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CarpetFloorR', 'offset': 13794, 'source': None, 'size': 182}
- {'symbol': '_MakeKitchenWall', 'offset': 13976, 'source': None, 'size': 196}
- {'symbol': '_TileFrame1', 'offset': 14660, 'source': None, 'size': 350}
- {'symbol': '_TileFrame2', 'offset': 15010, 'source': None, 'size': 350}

# Recovery task _TileFrame1

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 350 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov bx, word ptr [bp + 6]
000c cmp bx, di
000e jg 0x3996
0010 mov ax, bx
0012 shl ax, 6
0015 mov word ptr [bp - 2], ax
0018 mov dx, word ptr [bp + 0xa]
001b mov word ptr [bp - 4], dx
001e mov ax, dx
0020 sub ax, dx
0022 inc ax
0023 mov word ptr [bp - 0xa], ax
0026 mov ax, di
0028 sub ax, bx
002a inc ax
002b mov word ptr [bp - 6], ax
002e mov word ptr [bp - 8], bx
0031 mov bx, word ptr [bp - 2]
0034 mov ax, 0x54
0037 mov si, word ptr [bp - 4]
003a add si, bx
003c mov cx, word ptr [bp - 0xa]
003f lea di, [si + 0x28e8]
0043 push ds
0044 pop es
0045 rep stosb byte ptr es:[di], al
0047 add bx, 0x40
004a dec word ptr [bp - 6]
004d jne 0x3978
004f mov di, word ptr [bp + 8]
0052 mov dx, word ptr [bp + 6]
0055 mov bx, dx
0057 cmp dx, di
0059 jg 0x39e1
005b mov ax, dx
005d shl ax, 6
0060 mov word ptr [bp - 2], ax
0063 mov cx, word ptr [bp + 0xc]
0066 mov word ptr [bp - 4], cx
0069 mov ax, cx
006b sub ax, cx
006d inc ax
006e mov word ptr [bp - 0xc], ax
0071 mov ax, di
0073 sub ax, bx
0075 inc ax
0076 mov word ptr [bp - 6], ax
0079 mov word ptr [bp - 8], bx
007c mov bx, word ptr [bp - 2]
007f mov ax, 0x51
0082 mov si, word ptr [bp - 4]
0085 add si, bx
0087 mov cx, word ptr [bp - 0xc]
008a lea di, [si + 0x28e8]
008e push ds
008f pop es
0090 rep stosb byte ptr es:[di], al
0092 add bx, 0x40
0095 dec word ptr [bp - 6]
0098 jne 0x39c3
009a mov dx, word ptr [bp + 6]
009d mov bx, dx
009f mov ax, dx
00a1 shl ax, 6
00a4 mov word ptr [bp - 2], ax
00a7 mov ax, word ptr [bp + 0xa]
00aa mov word ptr [bp - 4], ax
00ad sub ax, word ptr [bp + 0xc]
00b0 neg ax
00b2 inc ax
00b3 mov word ptr [bp - 0xe], ax
00b6 mov ax, dx
00b8 sub ax, bx
00ba inc ax
00bb mov word ptr [bp - 6], ax
00be mov word ptr [bp - 8], bx
00c1 mov bx, word ptr [bp - 2]
00c4 mov ax, word ptr [bp + 0xa]
00c7 cmp word ptr [bp + 0xc], ax
00ca jl 0x3a23
00cc mov ax, 0x5a
00cf mov si, word ptr [bp - 4]
00d2 add si, bx
00d4 mov cx, word ptr [bp - 0xe]
00d7 lea di, [si + 0x28e8]
00db push ds
00dc pop es
00dd rep stosb byte ptr es:[di], al
00df add bx, 0x40
00e2 dec word ptr [bp - 6]
00e5 jne 0x3a08
00e7 mov di, word ptr [bp + 8]
00ea mov bx, di
00ec mov ax, di
00ee shl ax, 6
00f1 mov word ptr [bp - 2], ax
00f4 mov ax, word ptr [bp + 0xa]
00f7 mov word ptr [bp - 4], ax
00fa sub ax, word ptr [bp + 0xc]
00fd neg ax
00ff inc ax
0100 mov word ptr [bp - 0x10], ax
0103 mov ax, di
0105 sub ax, bx
0107 inc ax
0108 mov word ptr [bp - 6], ax
010b mov word ptr [bp - 8], bx
010e mov bx, word ptr [bp - 2]
0111 mov ax, word ptr [bp + 0xa]
0114 cmp word ptr [bp + 0xc], ax
0117 jl 0x3a70
0119 mov ax, 0x5b
011c mov si, word ptr [bp - 4]
011f add si, bx
0121 mov cx, word ptr [bp - 0x10]
0124 lea di, [si + 0x28e8]
0128 push ds
0129 pop es
012a rep stosb byte ptr es:[di], al
012c add bx, 0x40
012f dec word ptr [bp - 6]
0132 jne 0x3a55
0134 mov di, word ptr [bp + 8]
0137 mov bx, word ptr [bp + 0xa]
013a mov si, word ptr [bp + 6]
013d shl si, 6
0140 mov byte ptr [bx + si + 0x28e8], 0x53
0145 shl di, 6
0148 mov byte ptr [bx + di + 0x28e8], 0x55
014d mov bx, word ptr [bp + 0xc]
0150 mov byte ptr [bx + si + 0x28e8], 0x50
0155 mov byte ptr [bx + di + 0x28e8], 0x52
015a pop si
015b pop di
015c leave 
015d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeKitchenWall', 'offset': 13976, 'source': None, 'size': 196}
- {'symbol': '_MakeSink', 'offset': 14172, 'source': None, 'size': 487}
- {'symbol': '_TileFrame2', 'offset': 15010, 'source': None, 'size': 350}
- {'symbol': '_MakeOutletV', 'offset': 15360, 'source': None, 'size': 257}

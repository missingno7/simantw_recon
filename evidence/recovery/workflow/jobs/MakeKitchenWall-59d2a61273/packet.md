# Recovery task _MakeKitchenWall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 196 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov bx, 0x28e8
0009 mov ax, 0x6262
000c mov cx, 0xc
000f mov di, bx
0011 push ds
0012 pop es
0013 rep stosw word ptr es:[di], ax
0015 add bx, 0x40
0018 cmp bx, 0x48a8
001c jbe 0x36a1
001e mov bx, 0x2900
0021 xor ax, ax
0023 mov cx, 0x14
0026 mov di, bx
0028 rep stosw word ptr es:[di], ax
002a add bx, 0x40
002d cmp bx, 0x48c0
0031 jbe 0x36b9
0033 xor cx, cx
0035 mov bx, cx
0037 add bx, 0x28e8
003b mov dx, 0x80
003e mov byte ptr [bx], 0x68
0041 add bx, 0x40
0044 dec dx
0045 jne 0x36d6
0047 add cx, 8
004a cmp cx, 0x18
004d jl 0x36cd
004f xor di, di
0051 mov dx, di
0053 xor bx, bx
0055 mov word ptr [bp - 4], dx
0058 mov si, di
005a add si, bx
005c add si, 0x28e8
0060 cmp byte ptr [si], 0x62
0063 jne 0x3702
0065 mov byte ptr [si], 0x66
0068 jmp 0x3705
006a mov byte ptr [si], 0x67
006d inc bx
006e cmp bx, 0x18
0071 jl 0x36f0
0073 add dx, 8
0076 add di, 0x200
007a cmp di, 0x2000
007e jl 0x36eb
0080 mov si, 0x28ff
0083 mov dx, word ptr [bp - 4]
0086 cmp byte ptr [si], 0x62
0089 jne 0x3728
008b mov al, 0x68
008d jmp 0x372a
008f nop 
0090 mov al, 0x69
0092 mov byte ptr [si], al
0094 add si, 0x40
0097 cmp si, 0x48ff
009b jb 0x371e
009d push 2
009f push 0x24
00a1 nop 
00a2 push cs
00a3 call 0x3c00 ; _MakeOutletV
00a6 add sp, 4
00a9 push 2
00ab push 0x54
00ad nop 
00ae push cs
00af call 0x3c00 ; _MakeOutletV
00b2 add sp, 4
00b5 mov es, word ptr [0xc434]
00b9 mov word ptr es:[0x9c66], 2
00c0 pop si
00c1 pop di
00c2 leave 
00c3 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeLint2', 'offset': 13688, 'source': None, 'size': 105}
- {'symbol': '_CarpetFloorR', 'offset': 13794, 'source': None, 'size': 182}
- {'symbol': '_MakeSink', 'offset': 14172, 'source': None, 'size': 487}
- {'symbol': '_TileFrame1', 'offset': 14660, 'source': None, 'size': 350}

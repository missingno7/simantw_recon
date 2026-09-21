# Recovery task _FloorTiles

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 188 bytes.

```asm
0000 push di
0001 push si
0002 xor di, di
0004 mov dx, di
0006 xor bx, bx
0008 mov ax, bx
000a sar ax, 4
000d mov cx, dx
000f sar cx, 4
0012 add al, cl
0014 test al, 1
0016 je 0x3426
0018 mov byte ptr [bx + di + 0x28e8], 0
001d jmp 0x342b
001f nop 
0020 mov byte ptr [bx + di + 0x28e8], 1
0025 inc bx
0026 cmp bx, 0x40
0029 jl 0x340e
002b inc dx
002c add di, 0x40
002f cmp di, 0x2000
0033 jl 0x340c
0035 xor cx, cx
0037 xor dx, dx
0039 mov bx, cx
003b add bx, 0x28e8
003f mov al, cl
0041 add al, dl
0043 and ax, 0x10
0046 cmp ax, 1
0049 sbb al, al
004b and al, 1
004d add al, 0x60
004f mov byte ptr [bx], al
0051 add bx, 0x40
0054 inc dx
0055 cmp dx, 0x80
0059 jl 0x3445
005b add cx, 0x10
005e cmp cx, 0x40
0061 jl 0x343d
0063 xor di, di
0065 mov dx, di
0067 xor bx, bx
0069 mov si, di
006b add si, bx
006d add si, 0x28e8
0071 cmp byte ptr [si], 2
0074 jae 0x3490
0076 mov al, bl
0078 add al, dl
007a test al, 0x10
007c je 0x348a
007e mov byte ptr [si], 0x5e
0081 jmp 0x34a1
0083 nop 
0084 mov byte ptr [si], 0x5f
0087 jmp 0x34a1
0089 nop 
008a mov al, bl
008c add al, dl
008e test al, 0x10
0090 je 0x349e
0092 mov byte ptr [si], 0x5d
0095 jmp 0x34a1
0097 nop 
0098 mov byte ptr [si], 0x5c
009b inc bx
009c cmp bx, 0x40
009f jl 0x346f
00a1 add dx, 0x10
00a4 add di, 0x400
00a8 cmp di, 0x2000
00ac jl 0x346d
00ae mov es, word ptr [0xc434]
00b2 mov word ptr es:[0x9c66], 0
00b9 pop si
00ba pop di
00bb retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeMap', 'offset': 12544, 'source': None, 'size': 32}
- {'symbol': '_MakeHousePatch', 'offset': 12576, 'source': None, 'size': None}
- {'symbol': '_CarpetFloorL', 'offset': 13506, 'source': None, 'size': 181}
- {'symbol': '_MakeLint2', 'offset': 13688, 'source': None, 'size': 105}

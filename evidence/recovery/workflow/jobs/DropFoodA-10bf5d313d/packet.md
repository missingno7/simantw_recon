# Recovery task _DropFoodA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 292 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 mov di, word ptr [bp + 6]
000c mov bx, di
000e shl bx, 6
0011 add bx, si
0013 add bx, 0x28e8
0017 mov word ptr [bp - 0xc], bx
001a mov cl, byte ptr [bx]
001c sub ch, ch
001e mov es, word ptr [0xc2e6]
0022 cmp word ptr es:[0x9b6e], 1
0028 je 0xdb3
002a jmp 0xe90
002d cmp cx, 4
0030 jge 0xdd2
0032 mov al, cl
0034 add al, 6
0036 shl al, 2
0039 mov byte ptr [bx], al
003b mov es, word ptr [0xc2f0]
003f inc word ptr es:[0x9e84]
0044 mov ax, 1
0047 pop si
0048 pop di
0049 leave 
004a retf 
004b nop 
004c cmp cx, 8
004f jl 0xde8
0051 cmp cx, 0x18
0054 jge 0xde8
0056 mov ax, cx
0058 sub ax, 8
005b sar ax, 2
005e mov cx, ax
0060 jmp 0xdb8
0062 cmp cx, 0x18
0065 jl 0xdf6
0067 cmp cx, 0x27
006a jge 0xdf6
006c inc byte ptr [bx]
006e jmp 0xdc1
0070 cmp cx, 0x40
0073 jl 0xdfe
0075 jmp 0xea4
0078 mov word ptr [bp - 0xa], 1
007d mov cx, di
007f mov word ptr [bp - 2], si
0082 shl di, 6
0085 mov word ptr [bp - 6], di
0088 mov es, word ptr [0xc2f2]
008c mov bx, word ptr es:[0x9c66]
0091 mov al, byte ptr [bx + 0x22be]
0095 sub ah, ah
0097 shl ax, 6
009a mov word ptr [bp - 8], ax
009d mov bx, di
009f add bx, si
00a1 add bx, 0x28e8
00a5 mov word ptr [bp - 0xe], bx
00a8 mov al, byte ptr [bx]
00aa sub ah, ah
00ac mov word ptr [bp - 4], ax
00af cmp ax, 4
00b2 jge 0xe52
00b4 mov al, byte ptr [bp - 4]
00b7 add al, 6
00b9 shl al, 2
00bc mov byte ptr [bx], al
00be mov es, word ptr [0xc2f0]
00c2 inc word ptr es:[0x9e84]
00c7 mov word ptr [bp - 0xa], 0
00cc add di, word ptr [bp - 8]
00cf mov es, word ptr [0xc2f2]
00d3 mov bx, word ptr es:[0x9c66]
00d8 mov al, byte ptr [bx + 0x22c2]
00dc sub ah, ah
00de add si, ax
00e0 mov al, byte ptr [bx + 0x22be]
00e4 add cx, ax
00e6 js 0xe73
00e8 cmp cx, 0x7f
00eb jle 0xe8a
00ed xor dx, dx
00ef or si, si
00f1 jl 0xe7e
00f3 cmp si, 0x3f
00f6 jle 0xe80
00f8 xor dx, dx
00fa mov word ptr [bp - 0xa], dx
00fd or dx, dx
00ff jne 0xe23
0101 jmp 0xdca
0104 mov dx, word ptr [bp - 0xa]
0107 jmp 0xe75
0109 nop 
010a cmp cx, 0x4b
010d jge 0xea4
010f cmp cx, 0x48
0112 jl 0xe9d
0114 jmp 0xdf2
0117 mov byte ptr [bx], 0x48
011a jmp 0xdc1
011d nop 
011e xor ax, ax
0120 pop si
0121 pop di
0122 leave 
0123 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DropWater', 'offset': 3156, 'source': None, 'size': 195}
- {'symbol': '_PickupFoodA', 'offset': 3352, 'source': None, 'size': 109}
- {'symbol': '_FoodFall', 'offset': 3754, 'source': None, 'size': 150}
- {'symbol': '_PickupFoodB', 'offset': 3904, 'source': None, 'size': 98}

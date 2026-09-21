# Recovery task _TileCanBeMovedOn

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 349 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov cx, word ptr [bp + 6]
0009 cmp cx, 1
000c jg 0x93a8
000e mov bx, word ptr [bp + 8]
0011 or bx, bx
0013 jge 0x935a
0015 jmp 0x9497
0018 cmp bx, 0x7f
001b jle 0x9362
001d jmp 0x9497
0020 mov di, word ptr [bp + 0xa]
0023 or di, di
0025 jge 0x936c
0027 jmp 0x9497
002a cmp di, 0x3f
002d jle 0x9374
002f jmp 0x9497
0032 shl bx, 6
0035 mov cl, byte ptr [bx + di + 0x28e8]
0039 sub ch, ch
003b mov es, word ptr [0xc4ac]
003f cmp word ptr es:[0x9b6e], 0
0045 jne 0x9394
0047 cmp cx, 0x53
004a jg 0x939a
004c mov ax, 1
004f jmp 0x939c
0051 nop 
0052 cmp cx, 0x90
0056 jle 0x938e
0058 xor ax, ax
005a mov word ptr [bp - 4], ax
005d mov dx, ax
005f mov ax, dx
0061 pop si
0062 pop di
0063 leave 
0064 retf 
0065 nop 
0066 mov di, word ptr [bp + 8]
0069 or di, di
006b jge 0x93b2
006d jmp 0x9497
0070 cmp di, 0x3f
0073 jle 0x93ba
0075 jmp 0x9497
0078 mov bx, word ptr [bp + 0xa]
007b or bx, bx
007d jge 0x93c4
007f jmp 0x9497
0082 cmp bx, 0x3f
0085 jle 0x93cc
0087 jmp 0x9497
008a cmp cx, 2
008d jne 0x93de
008f mov si, di
0091 shl si, 6
0094 add si, bx
0096 mov dl, byte ptr [si + 0x48e8]
009a jmp 0x93e9
009c mov si, di
009e shl si, 6
00a1 add si, bx
00a3 mov dl, byte ptr [si + 0x58e8]
00a7 sub dh, dh
00a9 cmp dx, 0x18
00ac jle 0x9420
00ae cmp dx, 0x30
00b1 jl 0x93fa
00b3 cmp dx, 0x31
00b6 jle 0x9420
00b8 cmp word ptr [bp + 0x12], 0
00bc je 0x941c
00be cmp dx, 0x20
00c1 jl 0x940a
00c3 cmp dx, 0x2e
00c6 jle 0x9414
00c8 cmp dx, 0x1c
00cb jl 0x941c
00cd cmp dx, 0x1f
00d0 jg 0x941c
00d2 mov dx, 1
00d5 mov word ptr [bp - 2], dx
00d8 jmp 0x9428
00da xor dx, dx
00dc jmp 0x9428
00de mov dx, 1
00e1 mov word ptr [bp - 2], 0
00e6 or dx, dx
00e8 je 0x9499
00ea cmp bx, 1
00ed jg 0x9499
00ef cmp word ptr [bp + 0xc], cx
00f2 jne 0x9499
00f4 cmp word ptr [bp + 0x12], 0
00f8 jne 0x944e
00fa or bx, bx
00fc je 0x948d
00fe cmp di, word ptr [bp + 0xe]
0101 je 0x9499
0103 cmp word ptr [bp + 0x10], 0
0107 jne 0x9499
0109 jmp 0x9497
010b nop 
010c mov word ptr [bp - 4], dx
010f mov dx, di
0111 cmp word ptr [bp - 2], 0
0115 je 0x9486
0117 cmp word ptr [bp + 0xe], dx
011a jne 0x9497
011c mov dx, word ptr [bp - 4]
011f or bx, bx
0121 jne 0x9499
0123 cmp word ptr [bp + 6], 2
0127 jne 0x9472
0129 mov cl, byte ptr [si + 0x48e9]
012d jmp 0x9478
012f nop 
0130 mov bx, si
0132 mov cl, byte ptr [bx + 0x58e9]
0136 sub ch, ch
0138 cmp cx, 0x20
013b jl 0x9499
013d cmp cx, 0x2e
0140 jg 0x9499
0142 jmp 0x9497
0144 mov dx, word ptr [bp - 4]
0147 or bx, bx
0149 jne 0x9499
014b cmp di, word ptr [bp + 0xe]
014e jne 0x9497
0150 cmp bx, word ptr [bp + 0x10]
0153 je 0x9499
0155 xor dx, dx
0157 mov ax, dx
0159 pop si
015a pop di
015b leave 
015c retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DropMyObject', 'offset': 37356, 'source': None, 'size': 100}
- {'symbol': '_PickupMyObject', 'offset': 37456, 'source': None, 'size': 241}
- {'symbol': '_IsNotBarrier', 'offset': 38048, 'source': 'src/recovered/IsNotBarrier.c', 'size': 37}
- {'symbol': '_IsNotObstacle', 'offset': 38086, 'source': None, 'size': 255}

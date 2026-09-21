# Recovery task _IsItDigable

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 240 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 cmp di, 2
000c jge 0x95d7
000e jmp 0x96b0
0011 mov dx, word ptr [bp + 8]
0014 or dx, dx
0016 jl 0x95f4
0018 mov cx, word ptr [bp + 0xa]
001b cmp dx, 0x3f
001e jg 0x95f7
0020 or cx, cx
0022 jl 0x95f7
0024 cmp cx, 0x3f
0027 jg 0x95f7
0029 mov bx, 1
002c jmp 0x95f9
002e mov cx, word ptr [bp + 0xa]
0031 xor bx, bx
0033 or bx, bx
0035 jne 0x9600
0037 jmp 0x96b0
003a mov word ptr [bp - 2], 0xffff
003f cmp di, 1
0042 jg 0x9622
0044 or dx, dx
0046 jl 0x9634
0048 cmp dx, 0x7f
004b jg 0x9634
004d or cx, cx
004f jl 0x9634
0051 cmp cx, 0x3f
0054 jg 0x9634
0056 mov bx, 1
0059 jmp 0x9636
005b nop 
005c or dx, dx
005e jl 0x9634
0060 cmp dx, 0x3f
0063 jg 0x9634
0065 or cx, cx
0067 jl 0x9634
0069 cmp cx, 0x3f
006c jle 0x961c
006e xor bx, bx
0070 dec bx
0071 jne 0x9678
0073 mov ax, di
0075 or ax, ax
0077 jl 0x9678
0079 jo 0x9678
007b dec ax
007c jle 0x964c
007e dec ax
007f je 0x965a
0081 dec ax
0082 je 0x9668
0084 jmp 0x9678
0086 mov si, dx
0088 shl si, 6
008b mov bx, cx
008d mov al, byte ptr [bx + si + 0x28e8]
0091 jmp 0x9673
0093 nop 
0094 mov si, dx
0096 shl si, 6
0099 mov bx, cx
009b mov al, byte ptr [bx + si + 0x48e8]
009f jmp 0x9673
00a1 nop 
00a2 mov si, dx
00a4 shl si, 6
00a7 mov bx, cx
00a9 mov al, byte ptr [bx + si + 0x58e8]
00ad sub ah, ah
00af mov word ptr [bp - 2], ax
00b2 mov si, word ptr [bp - 2]
00b5 push si
00b6 nop 
00b7 push cs
00b8 call 0x11182
00bb add sp, 2
00be or ax, ax
00c0 je 0x9690
00c2 mov ax, 1
00c5 pop si
00c6 pop di
00c7 leave 
00c8 retf 
00c9 nop 
00ca cmp di, 2
00cd jl 0x96a4
00cf cmp si, 0x1c
00d2 jl 0x96a4
00d4 cmp si, 0x1f
00d7 jg 0x96a4
00d9 mov dx, 1
00dc jmp 0x96a6
00de xor dx, dx
00e0 cmp dx, 1
00e3 sbb ax, ax
00e5 inc ax
00e6 pop si
00e7 pop di
00e8 leave 
00e9 retf 
00ea xor ax, ax
00ec pop si
00ed pop di
00ee leave 
00ef retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsNotBarrier', 'offset': 38048, 'source': 'src/recovered/IsNotBarrier.c', 'size': 37}
- {'symbol': '_IsNotObstacle', 'offset': 38086, 'source': None, 'size': 255}
- {'symbol': '_IsItYellow', 'offset': 38582, 'source': None, 'size': 206}
- {'symbol': '_IsLessThanHole', 'offset': 38788, 'source': 'src/recovered/IsLessThanHole.c', 'size': 37}

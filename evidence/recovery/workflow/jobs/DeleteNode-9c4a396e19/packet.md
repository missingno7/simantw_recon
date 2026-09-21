# Recovery task _DeleteNode

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 189 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 sub sp, 2
0006 push si
0007 push di
0008 push ds
0009 mov ds, word ptr [0xb8de]
000d mov bx, word ptr [bp + 6]
0010 shl bx, 1
0012 mov ax, 0x1000
0015 cmp word ptr [bx + 0x521a], ax
0019 jne 0xa9ac
001b jmp 0xaa44
001e cmp word ptr [bx + 0x3018], ax
0022 jne 0xa9bc
0024 mov cx, word ptr [bx + 0x1016]
0028 mov si, cx
002a add si, si
002c jmp 0xaa22
002e cmp word ptr [bx + 0x1016], ax
0032 jne 0xa9cc
0034 mov cx, word ptr [bx + 0x3018]
0038 mov si, cx
003a add si, si
003c jmp 0xaa22
003e mov cx, word ptr [bx + 0x1016]
0042 mov si, cx
0044 shl si, 1
0046 cmp word ptr [si + 0x3018], 0x1000
004c je 0xaa14
004e mov si, word ptr [si + 0x3018]
0052 add si, si
0054 cmp word ptr [si + 0x3018], 0x1000
005a jne 0xa9dc
005c mov dx, word ptr [si + 0x1016]
0060 mov di, word ptr [si + 0x521a]
0064 mov cx, di
0066 shl di, 1
0068 mov word ptr [di + 0x3018], dx
006c mov di, dx
006e shl di, 1
0070 mov word ptr [di + 0x521a], cx
0074 mov di, word ptr [bx + 0x1016]
0078 mov word ptr [si + 0x1016], di
007c mov cx, si
007e shr cx, 1
0080 shl di, 1
0082 mov word ptr [di + 0x521a], cx
0086 mov di, word ptr [bx + 0x3018]
008a mov word ptr [si + 0x3018], di
008e add di, di
0090 mov word ptr [di + 0x521a], cx
0094 mov di, word ptr [bx + 0x521a]
0098 mov word ptr [si + 0x521a], di
009c add di, di
009e mov dx, bx
00a0 shr dx, 1
00a2 cmp word ptr [di + 0x3018], dx
00a6 jne 0xaa3c
00a8 mov word ptr [di + 0x3018], cx
00ac jmp 0xaa40
00ae mov word ptr [di + 0x1016], cx
00b2 mov word ptr [bx + 0x521a], ax
00b6 pop ds
00b7 pop di
00b8 pop si
00b9 mov sp, bp
00bb pop bp
00bc retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitTree', 'offset': 43096, 'source': None, 'size': 28}
- {'symbol': '_InsertNode', 'offset': 43124, 'source': None, 'size': 282}
- {'symbol': '_font_ReadFont', 'offset': 43596, 'source': None, 'size': 509}
- {'symbol': '_font_DumpFont', 'offset': 44106, 'source': None, 'size': 123}

# Recovery task _InsertNode

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 282 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 sub sp, 2
0006 push di
0007 push si
0008 push ds
0009 mov ds, word ptr [0xb8de]
000d mov word ptr [bp - 2], 1
0012 mov di, 0
0015 mov dx, word ptr [bp + 6]
0018 add di, dx
001a mov cl, byte ptr [di + 4]
001e xor ch, ch
0020 add cx, 0x1001
0024 mov bx, dx
0026 shl bx, 1
0028 mov word ptr [bx + 0x3018], 0x1000
002e mov word ptr [bx + 0x1016], 0x1000
0034 mov word ptr [2], 0
003a mov bx, cx
003c shl bx, 1
003e cmp word ptr [bp - 2], 0
0042 jl 0xa8d9
0044 cmp word ptr [bx + 0x3018], 0x1000
004a je 0xa8ca
004c mov cx, word ptr [bx + 0x3018]
0050 mov bx, cx
0052 shl bx, 1
0054 jmp 0xa8fa
0056 mov word ptr [bx + 0x3018], dx
005a mov bx, dx
005c shl bx, 1
005e mov word ptr [bx + 0x521a], cx
0062 jmp 0xa987
0065 cmp word ptr [bx + 0x1016], 0x1000
006b je 0xa8eb
006d mov cx, word ptr [bx + 0x1016]
0071 mov bx, cx
0073 shl bx, 1
0075 jmp 0xa8fa
0077 mov word ptr [bx + 0x1016], dx
007b mov bx, dx
007d shl bx, 1
007f mov word ptr [bx + 0x521a], cx
0083 jmp 0xa987
0086 mov bx, 1
0089 mov si, 0
008c add si, cx
008e xor dh, dh
0090 mov dl, byte ptr [bx + di + 4]
0094 xor ah, ah
0096 mov al, byte ptr [bx + si + 4]
009a sub dx, ax
009c jne 0xa918
009e inc bx
009f cmp bx, 0x12
00a2 jl 0xa902
00a4 mov word ptr [bp - 2], dx
00a7 cmp bx, word ptr [2]
00ab jle 0xa92e
00ad mov word ptr [0], cx
00b1 mov word ptr [2], bx
00b5 cmp bx, 0x12
00b8 jge 0xa934
00ba mov dx, word ptr [bp + 6]
00bd jmp 0xa8ae
00c0 mov bx, cx
00c2 shl bx, 1
00c4 mov si, word ptr [bp + 6]
00c7 mov dx, si
00c9 add si, si
00cb mov ax, word ptr [bx + 0x521a]
00cf mov word ptr [si + 0x521a], ax
00d3 mov ax, word ptr [bx + 0x1016]
00d7 mov word ptr [si + 0x1016], ax
00db mov ax, word ptr [bx + 0x3018]
00df mov word ptr [si + 0x3018], ax
00e3 mov si, word ptr [bx + 0x1016]
00e7 add si, si
00e9 mov word ptr [si + 0x521a], dx
00ed mov si, word ptr [bx + 0x3018]
00f1 add si, si
00f3 mov word ptr [si + 0x521a], dx
00f7 mov si, word ptr [bx + 0x521a]
00fb add si, si
00fd cmp cx, word ptr [si + 0x3018]
0101 jne 0xa97d
0103 mov word ptr [si + 0x3018], dx
0107 jmp 0xa981
0109 mov word ptr [si + 0x1016], dx
010d mov word ptr [bx + 0x521a], 0x1000
0113 pop ds
0114 pop si
0115 pop di
0116 mov sp, bp
0118 pop bp
0119 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UnpackFileClose', 'offset': 43084, 'source': None, 'size': 11}
- {'symbol': '_InitTree', 'offset': 43096, 'source': None, 'size': 28}
- {'symbol': '_DeleteNode', 'offset': 43406, 'source': None, 'size': 189}
- {'symbol': '_font_ReadFont', 'offset': 43596, 'source': None, 'size': 509}

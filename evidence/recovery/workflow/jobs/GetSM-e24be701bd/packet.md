# Recovery task _GetSM

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 193 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 or si, si
000b jl 0x8cec
000d cmp si, 0x3f
0010 jg 0x8cec
0012 cmp word ptr [bp + 8], 0
0016 jl 0x8cec
0018 cmp word ptr [bp + 8], 0x1f
001c jg 0x8cec
001e mov dx, 1
0021 jmp 0x8cee
0023 nop 
0024 xor dx, dx
0026 or dx, dx
0028 jne 0x8cfa
002a mov ax, 0xffff
002d pop si
002e pop di
002f leave 
0030 retf 
0031 nop 
0032 mov es, word ptr [0xc270]
0036 mov al, byte ptr es:[0x8605]
003a cwde 
003b or ax, ax
003d je 0x8d18
003f dec ax
0040 je 0x8d2e
0042 dec ax
0043 je 0x8d44
0045 dec ax
0046 je 0x8d5a
0048 dec ax
0049 je 0x8d70
004b mov cx, word ptr [bp - 2]
004e jmp 0x8d83
0050 mov bx, word ptr [bp + 8]
0053 mov es, word ptr [0xc27a]
0057 mov di, si
0059 shl di, 5
005c add di, bx
005e mov cl, byte ptr es:[di + 0x62d2]
0063 jmp 0x8d81
0065 nop 
0066 mov bx, word ptr [bp + 8]
0069 mov es, word ptr [0xc27a]
006d mov di, si
006f shl di, 5
0072 add di, bx
0074 mov cl, byte ptr es:[di + 0x6ad2]
0079 jmp 0x8d81
007b nop 
007c mov bx, word ptr [bp + 8]
007f mov es, word ptr [0xc27a]
0083 mov di, si
0085 shl di, 5
0088 add di, bx
008a mov cl, byte ptr es:[di + 0x72d2]
008f jmp 0x8d81
0091 nop 
0092 mov bx, word ptr [bp + 8]
0095 mov es, word ptr [0xc27a]
0099 mov di, si
009b shl di, 5
009e add di, bx
00a0 mov cl, byte ptr es:[di + 0x7ad2]
00a5 jmp 0x8d81
00a7 nop 
00a8 mov bx, word ptr [bp + 8]
00ab mov es, word ptr [0xc27a]
00af shl si, 5
00b2 add si, bx
00b4 mov cl, byte ptr es:[si + 0x52d2]
00b9 sub ch, ch
00bb mov ax, cx
00bd pop si
00be pop di
00bf leave 
00c0 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SmoothACell', 'offset': 35060, 'source': None, 'size': 944}
- {'symbol': '_IsValidSLoc', 'offset': 36004, 'source': 'src/recovered/IsValidSLoc.c', 'size': 36}
- {'symbol': '_SetSM', 'offset': 36234, 'source': None, 'size': 186}
- {'symbol': '_clip_SetWin', 'offset': 36420, 'source': 'src/recovered/clip_SetWin.c', 'size': 1}

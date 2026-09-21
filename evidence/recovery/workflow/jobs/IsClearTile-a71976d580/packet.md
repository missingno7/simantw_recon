# Recovery task _IsClearTile

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 332 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 6]
0009 mov word ptr [bp - 6], 0
000e mov word ptr [bp - 4], 0xffff
0013 cmp dx, 1
0016 jg 0x5b70
0018 mov si, word ptr [bp + 8]
001b or si, si
001d jl 0x5b62
001f mov di, word ptr [bp + 0xa]
0022 cmp si, 0x7f
0025 jg 0x5b65
0027 or di, di
0029 jl 0x5b65
002b cmp di, 0x3f
002e jg 0x5b65
0030 mov cx, 1
0033 jmp 0x5b67
0035 nop 
0036 mov di, word ptr [bp + 0xa]
0039 xor cx, cx
003b dec cx
003c je 0x5b80
003e mov cx, word ptr [bp - 4]
0041 jmp 0x5bb7
0043 nop 
0044 mov si, word ptr [bp + 8]
0047 or si, si
0049 jl 0x5b62
004b mov di, word ptr [bp + 0xa]
004e cmp si, 0x3f
0051 jmp 0x5b51
0053 nop 
0054 mov ax, dx
0056 or ax, ax
0058 jl 0x5b6a
005a jo 0x5b6a
005c dec ax
005d jle 0x5b94
005f dec ax
0060 je 0x5ba0
0062 dec ax
0063 je 0x5bac
0065 jmp 0x5b6a
0067 nop 
0068 mov bx, si
006a shl bx, 6
006d mov cl, byte ptr [bx + di + 0x28e8]
0071 jmp 0x5bb5
0073 nop 
0074 mov bx, si
0076 shl bx, 6
0079 mov cl, byte ptr [bx + di + 0x48e8]
007d jmp 0x5bb5
007f nop 
0080 mov bx, si
0082 shl bx, 6
0085 mov cl, byte ptr [bx + di + 0x58e8]
0089 sub ch, ch
008b mov word ptr [bp - 2], cx
008e or cx, cx
0090 jge 0x5bc1
0092 jmp 0x5c71
0095 mov word ptr [bp - 4], 0xffff
009a cmp dx, 1
009d jg 0x5be2
009f or si, si
00a1 jl 0x5bf4
00a3 cmp si, 0x7f
00a6 jg 0x5bf4
00a8 or di, di
00aa jl 0x5bf4
00ac cmp di, 0x3f
00af jg 0x5bf4
00b1 mov cx, 1
00b4 jmp 0x5bf6
00b6 or si, si
00b8 jl 0x5bf4
00ba cmp si, 0x3f
00bd jg 0x5bf4
00bf or di, di
00c1 jl 0x5bf4
00c3 cmp di, 0x3f
00c6 jle 0x5bdd
00c8 xor cx, cx
00ca dec cx
00cb je 0x5bfe
00cd mov cx, word ptr [bp - 4]
00d0 jmp 0x5c3e
00d2 mov ax, dx
00d4 or ax, ax
00d6 jl 0x5c0f
00d8 jo 0x5c0f
00da dec ax
00db jle 0x5c14
00dd dec ax
00de je 0x5c20
00e0 dec ax
00e1 je 0x5c2c
00e3 mov cx, word ptr [bp - 4]
00e6 jmp 0x5c37
00e8 mov bx, si
00ea shl bx, 6
00ed mov cl, byte ptr [bx + di + 0x68e8]
00f1 jmp 0x5c35
00f3 nop 
00f4 mov bx, si
00f6 shl bx, 6
00f9 mov cl, byte ptr [bx + di - 0x7718]
00fd jmp 0x5c35
00ff nop 
0100 mov bx, si
0102 shl bx, 6
0105 mov cl, byte ptr [bx + di - 0x6718]
0109 sub ch, ch
010b or cx, cx
010d jne 0x5c3e
010f mov cx, 0xffff
0112 mov bx, cx
0114 or bx, bx
0116 jl 0x5c5a
0118 cmp bx, 0xff
011c je 0x5c54
011e cmp bx, 0xfe
0122 je 0x5c54
0124 xor bx, bx
0126 jmp 0x5c57
0128 mov bx, 1
012b dec bx
012c jne 0x5c71
012e cmp dx, 1
0131 jg 0x5c66
0133 cmp word ptr [bp - 2], 0x10
0137 jmp 0x5c6a
0139 nop 
013a cmp word ptr [bp - 2], 8
013e jge 0x5c71
0140 mov word ptr [bp - 6], 1
0145 mov ax, word ptr [bp - 6]
0148 pop si
0149 pop di
014a leave 
014b retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindAntIndex', 'offset': 23036, 'source': None, 'size': 213}
- {'symbol': '_IsClear3x3', 'offset': 23250, 'source': None, 'size': 90}
- {'symbol': '_AddAntToList', 'offset': 23672, 'source': 'src/recovered/wf_AddAntToList-44a11714fc.c', 'size': 159}
- {'symbol': '_SetLife', 'offset': 23832, 'source': None, 'size': 432}

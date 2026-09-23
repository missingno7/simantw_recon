# Recovery task _Encode

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 542 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 sub sp, 0x2a
0006 push di
0007 push si
0008 nop 
0009 push cs
000a call 0xa858 ; _InitTree
000d mov byte ptr [bp - 0x26], 0
0011 mov byte ptr [bp - 1], 1
0015 mov word ptr [bp - 0xa], 1
001a mov word ptr [bp - 0xc], 0xfee
001f sub ax, ax
0021 mov word ptr [bp - 0x10], ax
0024 mov word ptr [bp - 0x14], ax
0027 mov word ptr [bp - 4], ax
002a jmp 0xa447
002c mov es, word ptr [0xc690]
0030 mov bx, word ptr [bp - 4]
0033 mov byte ptr es:[bx + 4], 0x20
0039 inc word ptr [bp - 4]
003c cmp word ptr [bp - 4], 0xfee
0041 jl 0xa437
0043 sub si, si
0045 push cs
0046 call 0xa26a ; _PackReadByte
0049 mov word ptr [bp - 0x12], ax
004c inc ax
004d je 0xa46c
004f mov al, byte ptr [bp - 0x12]
0052 mov es, word ptr [0xc690]
0056 mov byte ptr es:[si + 0xff2], al
005b inc si
005c cmp si, 0x12
005f jl 0xa450
0061 or si, si
0063 jne 0xa473
0065 jmp 0xa623
0068 mov word ptr [bp - 8], si
006b mov di, 1
006e mov ax, 0xfee
0071 sub ax, di
0073 push ax
0074 nop 
0075 push cs
0076 call 0xa874 ; _InsertNode
0079 pop bx
007a inc di
007b cmp di, 0x12
007e jle 0xa479
0080 mov ax, 0xfee
0083 push ax
0084 nop 
0085 push cs
0086 call 0xa874 ; _InsertNode
0089 pop bx
008a mov ax, word ptr [bp - 8]
008d mov bx, 2
0090 mov es, word ptr [0xc692]
0094 mov word ptr [bp - 0x2a], bx
0097 mov word ptr [bp - 0x28], es
009a cmp word ptr es:[bx], ax
009d jle 0xa4ad
009f mov word ptr es:[bx], ax
00a2 mov ax, word ptr [bp - 0xe]
00a5 cmp word ptr [bp - 0x12], ax
00a8 jne 0xa4c5
00aa inc word ptr [bp - 0x10]
00ad cmp word ptr [bp - 0x10], 0xf
00b1 jle 0xa4d0
00b3 mov word ptr [bp - 0x10], 0xf
00b8 jmp 0xa4d0
00ba mov ax, word ptr [bp - 0x12]
00bd mov word ptr [bp - 0xe], ax
00c0 mov word ptr [bp - 0x10], 0
00c5 mov ax, word ptr [bp - 0x10]
00c8 add ax, word ptr [0xb7c2] ; _pack_threshold
00cc les bx, ptr [bp - 0x2a]
00cf cmp ax, word ptr es:[bx]
00d2 jl 0xa4ff
00d4 mov word ptr es:[bx], 1
00d9 mov al, byte ptr [bp - 1]
00dc or byte ptr [bp - 0x26], al
00df mov di, word ptr [bp - 0xa]
00e2 mov es, word ptr [0xc690]
00e6 mov bx, word ptr [bp - 0xc]
00e9 mov al, byte ptr es:[bx + 4]
00ee mov byte ptr [bp + di - 0x26], al
00f1 inc di
00f2 jmp 0xa52a
00f4 mov di, word ptr [bp - 0xa]
00f7 mov es, word ptr [0xc694]
00fb mov al, byte ptr es:[0]
00ff mov byte ptr [bp + di - 0x26], al
0102 mov cl, 4
0104 mov ax, word ptr es:[0]
0108 sar ax, cl
010a and al, 0xf0
010c les bx, ptr [bp - 0x2a]
010f mov cl, byte ptr es:[bx]
0112 sub cl, byte ptr [0xb7c2] ; _pack_threshold
0116 dec cl
0118 or al, cl
011a inc di
011b mov byte ptr [bp + di - 0x26], al
011e inc di
011f shl byte ptr [bp - 1], 1
0122 cmp byte ptr [bp - 1], 0
0126 jne 0xa55c
0128 mov word ptr [bp - 4], 0
012d mov word ptr [bp - 0xa], di
0130 jmp 0xa54c
0132 mov si, word ptr [bp - 4]
0135 mov al, byte ptr [bp + si - 0x26]
0138 push ax
0139 push cs
013a call 0xa201 ; _PackWriteByte
013d pop bx
013e inc word ptr [bp - 4]
0141 cmp word ptr [bp - 4], di
0144 jl 0xa53d
0146 mov byte ptr [bp - 0x26], 0
014a mov byte ptr [bp - 1], 1
014e mov di, 1
0151 les bx, ptr [bp - 0x2a]
0154 mov ax, word ptr es:[bx]
0157 mov word ptr [bp - 6], ax
015a mov word ptr [bp - 4], 0
015f mov word ptr [bp - 0xa], di
0162 mov si, word ptr [bp - 0x14]
0165 mov di, word ptr [bp - 0x12]
0168 jmp 0xa5b8
016a push cs
016b call 0xa26a ; _PackReadByte
016e mov di, ax
0170 cmp di, -1
0173 je 0xa5c0
0175 push si
0176 nop 
0177 push cs
0178 call 0xa98e ; _DeleteNode
017b pop bx
017c mov ax, di
017e mov es, word ptr [0xc690]
0182 mov byte ptr es:[si + 4], al
0187 cmp si, 0x11
018a jge 0xa59c
018c mov byte ptr es:[si + 0x1004], al
0191 lea ax, [si + 1]
0194 and ah, 0xf
0197 mov si, ax
0199 mov ax, word ptr [bp - 0xc]
019c inc ax
019d and ah, 0xf
01a0 mov word ptr [bp - 0xc], ax
01a3 push ax
01a4 nop 
01a5 push cs
01a6 call 0xa874 ; _InsertNode
01a9 pop bx
01aa inc word ptr [bp - 4]
01ad mov ax, word ptr [bp - 6]
01b0 cmp word ptr [bp - 4], ax
01b3 jl 0xa575
01b5 mov word ptr [bp - 0x12], di
01b8 mov word ptr [bp - 0x14], si
01bb jmp 0xa5f1
01bd push word ptr [bp - 0x14]
01c0 nop 
01c1 push cs
01c2 call 0xa98e ; _DeleteNode
01c5 pop bx
01c6 mov ax, word ptr [bp - 0x14]
01c9 inc ax
01ca and ah, 0xf
01cd mov word ptr [bp - 0x14], ax
01d0 mov ax, word ptr [bp - 0xc]
01d3 inc ax
01d4 and ah, 0xf
01d7 mov word ptr [bp - 0xc], ax
01da dec word ptr [bp - 8]
01dd je 0xa5f1
01df push ax
01e0 nop 
01e1 push cs
01e2 call 0xa874 ; _InsertNode
01e5 pop bx
01e6 mov ax, word ptr [bp - 4]
01e9 inc word ptr [bp - 4]
01ec cmp ax, word ptr [bp - 6]
01ef jl 0xa5c8
01f1 cmp word ptr [bp - 8], 0
01f5 jle 0xa605
01f7 jmp 0xa495
01fa mov di, word ptr [bp - 0xa]
01fd cmp di, 1
0200 jle 0xa61f
0202 sub si, si
0204 cmp si, di
0206 jge 0xa61f
0208 mov al, byte ptr [bp + si - 0x26]
020b push ax
020c push cs
020d call 0xa201 ; _PackWriteByte
0210 pop bx
0211 inc si
0212 jmp 0xa60f
0214 push cs
0215 call 0xa241
0218 pop si
0219 pop di
021a mov sp, bp
021c pop bp
021d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PackFileToFile', 'offset': 41765, 'source': None, 'size': 87}
- {'symbol': '_PackMemoryToMemory', 'offset': 41917, 'source': None, 'size': 78}
- {'symbol': '_UnpackInit', 'offset': 42538, 'source': None, 'size': 62}
- {'symbol': '_Unpack', 'offset': 42600, 'source': None, 'size': 306}

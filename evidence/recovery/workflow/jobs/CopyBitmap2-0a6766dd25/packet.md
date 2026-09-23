# Recovery task _CopyBitmap2

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 370 bytes.

```asm
0000 enter 0x5a, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 0x10]
0009 shl ax, 2
000c add ax, 0x1f
000f cdq 
0010 and dx, 0x1f
0013 add ax, dx
0015 sar ax, 5
0018 shl ax, 2
001b cdq 
001c mov word ptr [bp - 4], ax
001f mov word ptr [bp - 2], dx
0022 mov ax, word ptr [bp + 0x14]
0025 shl ax, 2
0028 add ax, 0x1f
002b cdq 
002c and dx, 0x1f
002f add ax, dx
0031 sar ax, 5
0034 shl ax, 2
0037 cdq 
0038 mov word ptr [bp - 0xc], ax
003b mov word ptr [bp - 0xa], dx
003e mov ax, word ptr [bp + 0x14]
0041 mov cx, 2
0044 cdq 
0045 idiv cx
0047 or dx, dx
0049 jne 0x2a9a
004b mov ax, word ptr [bp + 0x14]
004e cdq 
004f and dx, 1
0052 add ax, dx
0054 sar ax, 1
0056 cdq 
0057 jmp 0x2aa9
0059 nop 
005a mov ax, word ptr [bp + 0x14]
005d cdq 
005e sub ax, dx
0060 sar ax, 1
0062 cdq 
0063 add ax, 1
0066 adc dx, 0
0069 mov word ptr [bp - 8], ax
006c cmp word ptr [bp + 0x16], 0
0070 jge 0x2ade
0072 mov ax, word ptr [bp + 0x16]
0075 neg ax
0077 mov word ptr [bp - 0x12], ax
007a mov ax, word ptr [bp + 0x14]
007d cmp word ptr [bp + 0x18], 0
0081 jge 0x2af6
0083 mov ax, word ptr [bp + 0x18]
0086 neg ax
0088 mov word ptr [bp - 0x16], ax
008b mov ax, word ptr [bp + 0x12]
008e mov word ptr [bp - 0x18], ax
0091 mov ax, word ptr [bp - 0x16]
0094 cdq 
0095 mov word ptr [bp - 0x10], ax
0098 mov word ptr [bp - 0xe], dx
009b jmp 0x2b16
009d nop 
009e mov word ptr [bp - 0x12], 0
00a3 mov ax, word ptr [bp + 0x16]
00a6 add ax, word ptr [bp + 0x14]
00a9 cmp ax, word ptr [bp + 0x10]
00ac jle 0x2aba
00ae mov ax, word ptr [bp + 0x10]
00b1 sub ax, word ptr [bp + 0x16]
00b4 jmp 0x2abd
00b6 mov word ptr [bp - 0x16], 0
00bb mov ax, word ptr [bp + 0x18]
00be add ax, word ptr [bp + 0x12]
00c1 cmp ax, word ptr [bp + 0xe]
00c4 jle 0x2acb
00c6 mov ax, word ptr [bp + 0xe]
00c9 sub ax, word ptr [bp + 0x18]
00cc jmp 0x2ace
00ce add word ptr [bp - 0x10], 1
00d2 adc word ptr [bp - 0xe], 0
00d6 mov ax, word ptr [bp - 0x18]
00d9 cdq 
00da cmp dx, word ptr [bp - 0xe]
00dd jge 0x2b22
00df jmp 0x2bae
00e2 jg 0x2b2c
00e4 cmp ax, word ptr [bp - 0x10]
00e7 ja 0x2b2c
00e9 jmp 0x2bae
00ec push word ptr [bp - 2]
00ef push word ptr [bp - 4]
00f2 mov ax, word ptr [bp + 0x18]
00f5 cdq 
00f6 add ax, word ptr [bp - 0x10]
00f9 adc dx, word ptr [bp - 0xe]
00fc push dx
00fd push ax
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0103 mov cx, ax
0105 mov ax, word ptr [bp - 0x12]
0108 sar ax, 1
010a mov bx, ax
010c mov si, dx
010e cdq 
010f add cx, ax
0111 adc si, dx
0113 mov ax, word ptr [bp + 0x16]
0116 sar ax, 1
0118 cdq 
0119 add ax, cx
011b adc dx, si
011d add ax, word ptr [bp + 6]
0120 adc dx, 0
0123 mov <resolved loader operand; see bindings> ; [{'operand_offset': 292, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0126 shl dx, cl
0128 add dx, word ptr [bp + 8]
012b push word ptr [bp - 0xa]
012e push word ptr [bp - 0xc]
0131 push word ptr [bp - 0xe]
0134 push word ptr [bp - 0x10]
0137 mov si, ax
0139 mov di, dx
013b mov word ptr [bp - 0x5a], bx
013e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 321, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0143 add ax, word ptr [bp + 0xa]
0146 adc dx, 0
0149 mov <resolved loader operand; see bindings> ; [{'operand_offset': 330, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
014c shl dx, cl
014e add dx, word ptr [bp + 0xc]
0151 mov cx, word ptr [bp - 8]
0154 sub cx, word ptr [bp - 0x5a]
0157 push ds
0158 push di
0159 mov di, si
015b mov si, ax
015d pop es
015e mov ds, dx
0160 shr cx, 1
0162 rep movsw word ptr es:[di], word ptr [si]
0164 adc cx, cx
0166 rep movsb byte ptr es:[di], byte ptr [si]
0168 pop ds
0169 jmp 0x2b0e
016c nop 
016d nop 
016e pop si
016f pop di
0170 leave 
0171 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ConvertBitmap', 'offset': 9326, 'source': None, 'size': 674}
- {'symbol': '_ConvertBitmap2', 'offset': 10000, 'source': None, 'size': 816}
- {'symbol': '_CopyMonoBitmap', 'offset': 11186, 'source': None, 'size': 801}
- {'symbol': '_CopyMonoMaskBitmap', 'offset': 11988, 'source': None, 'size': 1110}

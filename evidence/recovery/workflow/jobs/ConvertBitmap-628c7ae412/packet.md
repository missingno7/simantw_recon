# Recovery task _ConvertBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 674 bytes.

```asm
0000 enter 0x40, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 0x10]
0009 mov ax, bx
000b shl ax, 2
000e add ax, 0x1f
0011 cdq 
0012 and dx, 0x1f
0015 add ax, dx
0017 sar ax, 5
001a shl ax, 2
001d cdq 
001e mov word ptr [bp - 0x10], ax
0021 mov word ptr [bp - 0xe], dx
0024 mov ax, bx
0026 mov cx, 8
0029 cdq 
002a idiv cx
002c or dx, dx
002e jne 0x24ac
0030 mov ax, bx
0032 cdq 
0033 and dx, 7
0036 add ax, dx
0038 sar ax, 3
003b cdq 
003c jmp 0x24be
003e mov ax, bx
0040 cdq 
0041 and dx, 7
0044 add ax, dx
0046 sar ax, 3
0049 cdq 
004a add ax, 1
004d adc dx, 0
0050 mov word ptr [bp - 0x14], ax
0053 mov word ptr [bp - 0x12], dx
0056 sub ax, ax
0058 mov word ptr [bp - 0xa], ax
005b mov word ptr [bp - 0xc], ax
005e cmp word ptr [bp + 0xe], ax
0061 jg 0x24d4
0063 jmp 0x270c
0066 mov ax, word ptr [bp - 0x14]
0069 mov cx, ax
006b mov bx, dx
006d shl ax, 1
006f rcl dx, 1
0071 add ax, cx
0073 adc dx, bx
0075 mov word ptr [bp - 0x22], ax
0078 mov word ptr [bp - 0x20], dx
007b mov ax, word ptr [bp + 0xe]
007e cdq 
007f mov di, ax
0081 mov word ptr [bp - 0x1c], dx
0084 neg di
0086 neg di
0088 adc word ptr [bp - 0x1c], -1
008c mov si, word ptr [bp - 0x1c]
008f push word ptr [bp - 0x12]
0092 push word ptr [bp - 0x14]
0095 mov ax, word ptr [bp + 0xe]
0098 cdq 
0099 sub ax, word ptr [bp - 0xc]
009c sbb dx, word ptr [bp - 0xa]
009f sub ax, 1
00a2 sbb dx, 0
00a5 push dx
00a6 push ax
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00ac shl ax, 1
00ae rcl dx, 1
00b0 shl ax, 1
00b2 rcl dx, 1
00b4 mov word ptr [bp - 8], ax
00b7 mov word ptr [bp - 6], dx
00ba sub ax, ax
00bc mov word ptr [bp - 2], ax
00bf mov word ptr [bp - 4], ax
00c2 cmp word ptr [bp - 0xe], ax
00c5 jne 0x253d
00c7 cmp word ptr [bp - 0x10], ax
00ca jne 0x253d
00cc jmp 0x26f8
00cf push word ptr [bp - 0xe]
00d2 push word ptr [bp - 0x10]
00d5 push word ptr [bp - 0xa]
00d8 push word ptr [bp - 0xc]
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00e0 mov word ptr [bp - 0x26], ax
00e3 mov word ptr [bp - 0x24], dx
00e6 push 0
00e8 push 4
00ea push word ptr [bp - 2]
00ed push word ptr [bp - 4]
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00f5 add ax, word ptr [bp - 8]
00f8 adc dx, word ptr [bp - 6]
00fb push 0
00fd push 4
00ff push word ptr [bp - 2]
0102 push word ptr [bp - 4]
0105 mov word ptr [bp - 0x2a], ax
0108 mov word ptr [bp - 0x28], dx
010b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFlrem
0110 mov cx, ax
0112 mov ax, word ptr [bp - 0x2a]
0115 mov dx, word ptr [bp - 0x28]
0118 add ax, word ptr [bp - 0x22]
011b adc dx, word ptr [bp - 0x20]
011e mov word ptr [bp - 0x2e], cx
0121 add ax, word ptr [bp + 0xa]
0124 adc dx, 0
0127 mov <resolved loader operand; see bindings> ; [{'operand_offset': 296, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
012a shl dx, cl
012c add dx, word ptr [bp + 0xc]
012f mov es, dx
0131 mov bx, ax
0133 mov al, byte ptr es:[bx]
0136 mov cx, ax
0138 mov ax, word ptr [bp - 0x2a]
013b mov dx, word ptr [bp - 0x28]
013e mov bx, cx
0140 add ax, word ptr [bp + 0xa]
0143 adc dx, 0
0146 mov <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0149 shl dx, cl
014b add dx, word ptr [bp + 0xc]
014e mov es, dx
0150 mov cx, bx
0152 mov bx, ax
0154 mov al, byte ptr es:[bx]
0157 mov dx, cx
0159 mov cl, 7
015b mov bl, byte ptr [bp - 0x2e]
015e shl bl, 1
0160 sub cl, bl
0162 mov bx, cx
0164 dec cl
0166 mov word ptr [bp - 0x30], dx
0169 shr dl, cl
016b and dl, 1
016e mov word ptr [bp - 0x32], cx
0171 mov cl, bl
0173 mov bx, ax
0175 shr al, cl
0177 mov word ptr [bp - 0x34], ax
017a mov ax, dx
017c mov word ptr [bp - 0x36], ax
017f mov ax, word ptr [bp - 0x2a]
0182 mov dx, word ptr [bp - 0x28]
0185 add ax, word ptr [bp - 0x14]
0188 adc dx, word ptr [bp - 0x12]
018b mov word ptr [bp - 0x38], cx
018e add ax, word ptr [bp + 0xa]
0191 adc dx, 0
0194 mov <resolved loader operand; see bindings> ; [{'operand_offset': 405, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0197 shl dx, cl
0199 add dx, word ptr [bp + 0xc]
019c mov es, dx
019e mov cx, bx
01a0 mov bx, ax
01a2 mov al, byte ptr es:[bx]
01a5 mov dx, cx
01a7 mov cl, byte ptr [bp - 0x38]
01aa mov bx, ax
01ac shr al, cl
01ae mov cx, ax
01b0 mov ax, dx
01b2 mov word ptr [bp - 0x3a], ax
01b5 mov ax, word ptr [bp - 0x14]
01b8 mov dx, word ptr [bp - 0x12]
01bb shl ax, 1
01bd rcl dx, 1
01bf add ax, word ptr [bp - 0x2a]
01c2 adc dx, word ptr [bp - 0x28]
01c5 mov word ptr [bp - 0x3c], cx
01c8 add ax, word ptr [bp + 0xa]
01cb adc dx, 0
01ce mov <resolved loader operand; see bindings> ; [{'operand_offset': 463, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
01d1 shl dx, cl
01d3 add dx, word ptr [bp + 0xc]
01d6 mov es, dx
01d8 mov cx, bx
01da mov dx, cx
01dc mov cl, byte ptr [bp - 0x38]
01df mov bx, ax
01e1 mov al, byte ptr es:[bx]
01e4 mov bx, ax
01e6 shr al, cl
01e8 and al, 1
01ea mov cx, ax
01ec mov al, byte ptr [bp - 0x30]
01ef mov ax, cx
01f1 mov cl, byte ptr [bp - 0x38]
01f4 mov word ptr [bp - 0x3e], dx
01f7 mov dl, byte ptr [bp - 0x30]
01fa shr dl, cl
01fc shl dl, 1
01fe or al, dl
0200 shl al, 1
0202 mov cl, byte ptr [bp - 0x3c]
0205 and cl, 1
0208 or al, cl
020a shl al, 1
020c mov cl, byte ptr [bp - 0x34]
020f and cl, 1
0212 or al, cl
0214 shl al, 1
0216 or al, byte ptr [bp - 0x36]
0219 shl al, 1
021b mov byte ptr [bp - 0x1e], al
021e mov ax, word ptr [bp - 0x26]
0221 mov dx, word ptr [bp - 0x24]
0224 add ax, word ptr [bp - 4]
0227 adc dx, word ptr [bp - 2]
022a add ax, word ptr [bp + 6]
022d adc dx, 0
0230 mov <resolved loader operand; see bindings> ; [{'operand_offset': 561, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 113}}]
0233 shl dx, cl
0235 add dx, word ptr [bp + 8]
0238 mov es, dx
023a mov cx, bx
023c mov bx, ax
023e mov al, byte ptr [bp - 0x32]
0241 mov dx, cx
0243 mov cl, al
0245 mov al, byte ptr [bp - 0x3a]
0248 shr al, cl
024a and al, 1
024c shr dl, cl
024e and dl, 1
0251 or dl, byte ptr [bp - 0x1e]
0254 shl dl, 1
0256 mov word ptr [bp - 0x40], ax
0259 mov al, byte ptr [bp - 0x3e]
025c shr al, cl
025e and al, 1
0260 or dl, al
0262 shl dl, 1
0264 or dl, byte ptr [bp - 0x40]
0267 mov byte ptr es:[bx], dl
026a mov ax, word ptr [bp - 0x10]
026d mov dx, word ptr [bp - 0xe]
0270 add word ptr [bp - 4], 1
0274 adc word ptr [bp - 2], 0
0278 cmp word ptr [bp - 2], dx
027b jae 0x26ee
027d jmp 0x2554
0280 ja 0x26f8
0282 cmp word ptr [bp - 4], ax
0285 jae 0x26f8
0287 jmp 0x2554
028a add word ptr [bp - 0xc], 1
028e adc word ptr [bp - 0xa], 0
0292 dec di
0293 je 0x2706
0295 jmp 0x24fd
0298 dec si
0299 js 0x270c
029b jmp 0x24fd
029e pop si
029f pop di
02a0 leave 
02a1 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CalcBitmapStuff', 'offset': 7794, 'source': 'src/recovered/wf_CalcBitmapStuff-605c34021c.c', 'size': 146}
- {'symbol': '_ConvertMaskBitmap2', 'offset': 7940, 'source': None, 'size': 1385}
- {'symbol': '_ConvertBitmap2', 'offset': 10000, 'source': None, 'size': 816}
- {'symbol': '_CopyBitmap2', 'offset': 10816, 'source': None, 'size': 370}

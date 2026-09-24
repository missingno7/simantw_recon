# Recovery task _MakeHousePatch

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 742 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc430]
000a cmp word ptr es:[0x9b6e], 1
0010 je 0x3148
0012 mov ax, 0x3e9
0015 mov es, word ptr [0xc432]
0019 mov word ptr es:[0x85ea], ax
001d push ax
001e push 0
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _OverlayTileSet
0025 add sp, 4
0028 push 0
002a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitAntLions
002f add sp, 2
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitPillar
0037 mov ax, word ptr [bp + 6]
003a cmp ax, 0x25
003d ja 0x31b4
003f shl ax, 1
0041 xchg bx, ax
0042 jmp word ptr cs:[bx + 0x3168]
0047 nop 
0048 dw offset 0x31bc
004a dw offset 0x31b4
004c dw offset 0x31ca
004e dw offset 0x31ca
0050 dw offset 0x31d2
0052 dw offset 0x31da
0054 dw offset 0x3228
0056 dw offset 0x32a8
0058 dw offset 0x32fc
005a dw offset 0x3350
005c dw offset 0x31d2
005e dw offset 0x31d2
0060 dw offset 0x336c
0062 dw offset 0x31d2
0064 dw offset 0x31d2
0066 dw offset 0x3388
0068 dw offset 0x31b4
006a dw offset 0x31ca
006c dw offset 0x31ca
006e dw offset 0x31ca
0070 dw offset 0x33d6
0072 dw offset 0x33d6
0074 dw offset 0x33d6
0076 dw offset 0x33d6
0078 dw offset 0x33d6
007a dw offset 0x33d6
007c dw offset 0x33d6
007e dw offset 0x33d6
0080 dw offset 0x33d6
0082 dw offset 0x33d6
0084 dw offset 0x33d6
0086 dw offset 0x33d6
0088 dw offset 0x31b4
008a dw offset 0x31ca
008c dw offset 0x31ca
008e dw offset 0x31ca
0090 dw offset 0x33e0
0092 dw offset 0x33e0
0094 nop 
0095 push cs
0096 call 0x3698 ; _MakeKitchenWall
0099 jmp 0x3402
009c nop 
009d push cs
009e call 0x3698 ; _MakeKitchenWall
00a1 nop 
00a2 push cs
00a3 call 0x375c ; _MakeSink
00a6 jmp 0x3402
00a9 nop 
00aa nop 
00ab push cs
00ac call 0x3406 ; _FloorTiles
00af jmp 0x3402
00b2 nop 
00b3 push cs
00b4 call 0x34c2 ; _CarpetFloorL
00b7 jmp 0x3402
00ba nop 
00bb push cs
00bc call 0x34c2 ; _CarpetFloorL
00bf mov si, 0x2efc
00c2 mov ax, 0x202
00c5 mov cx, 0x16
00c8 mov di, si
00ca push ds
00cb pop es
00cc rep stosw word ptr es:[di], ax
00ce add si, 0x40
00d1 cmp si, 0x3a7c
00d5 jbe 0x31e2
00d7 xor dx, dx
00d9 mov cx, dx
00db xor si, si
00dd mov di, cx
00df add di, 0x2356
00e3 mov word ptr [bp - 2], dx
00e6 mov word ptr [bp - 4], cx
00e9 mov bx, dx
00eb mov al, byte ptr [di]
00ed add di, 3
00f0 mov byte ptr [bx + si + 0x3315], al
00f4 inc si
00f5 cmp si, 3
00f8 jl 0x3209
00fa inc cx
00fb add dx, 0x40
00fe cmp dx, 0xc0
0102 jl 0x31fb
0104 jmp 0x3402
0107 nop 
0108 nop 
0109 push cs
010a call 0x34c2 ; _CarpetFloorL
010d mov si, 0x2ee8
0110 mov ax, 0x202
0113 mov cx, 0x20
0116 mov di, si
0118 push ds
0119 pop es
011a rep stosw word ptr es:[di], ax
011c add si, 0x40
011f cmp si, 0x3a68
0123 jbe 0x3230
0125 xor dx, dx
0127 mov cx, dx
0129 xor si, si
012b mov di, cx
012d add di, 0x2356
0131 mov word ptr [bp - 2], dx
0134 mov word ptr [bp - 4], cx
0137 mov bx, dx
0139 mov al, byte ptr [di]
013b add di, 3
013e mov byte ptr [bx + si + 0x30fc], al
0142 inc si
0143 cmp si, 3
0146 jl 0x3257
0148 inc cx
0149 add dx, 0x40
014c cmp dx, 0xc0
0150 jl 0x3249
0152 xor dx, dx
0154 mov cx, dx
0156 xor di, di
0158 mov si, cx
015a add si, 0x2360
015e mov word ptr [bp - 2], dx
0161 mov word ptr [bp - 4], cx
0164 cmp byte ptr [si], 0
0167 je 0x3291
0169 mov al, byte ptr [si]
016b mov bx, dx
016d mov byte ptr [bx + di + 0x329f], al
0171 add si, 3
0174 inc di
0175 cmp di, 3
0178 jl 0x3284
017a inc cx
017b add dx, 0x40
017e cmp dx, 0xc0
0182 jl 0x3276
0184 jmp 0x3402
0187 nop 
0188 nop 
0189 push cs
018a call 0x34c2 ; _CarpetFloorL
018d mov si, 0x2ee8
0190 mov ax, 0x202
0193 mov cx, 0xa
0196 mov di, si
0198 push ds
0199 pop es
019a rep stosw word ptr es:[di], ax
019c stosb byte ptr es:[di], al
019d add si, 0x40
01a0 cmp si, 0x3a68
01a4 jbe 0x32b0
01a6 xor dx, dx
01a8 mov cx, dx
01aa xor di, di
01ac mov si, cx
01ae add si, 0x2360
01b2 mov word ptr [bp - 2], dx
01b5 mov word ptr [bp - 4], cx
01b8 cmp byte ptr [si], 0
01bb je 0x32e5
01bd mov al, byte ptr [si]
01bf mov bx, dx
01c1 mov byte ptr [bx + di + 0x3372], al
01c5 add si, 3
01c8 inc di
01c9 cmp di, 3
01cc jl 0x32d8
01ce inc cx
01cf add dx, 0x40
01d2 cmp dx, 0xc0
01d6 jl 0x32ca
01d8 pop si
01d9 pop di
01da leave 
01db retf 
01dc nop 
01dd push cs
01de call 0x34c2 ; _CarpetFloorL
01e1 push 2
01e3 push 0x2d
01e5 push 0xf
01e7 push 0x36
01e9 push 0x18
01eb nop 
01ec push cs
01ed call 0x3faa ; _FillMapLegs
01f0 add sp, 0xa
01f3 xor di, di
01f5 mov word ptr [bp - 4], di
01f8 mov word ptr [bp - 2], di
01fb mov dx, di
01fd xor di, di
01ff mov si, word ptr [bp - 4]
0202 add si, 0x2360
0206 mov word ptr [bp - 2], dx
0209 cmp byte ptr [si], 0
020c je 0x3336
020e mov al, byte ptr [si]
0210 mov bx, dx
0212 mov byte ptr [bx + di + 0x300a], al
0216 add si, 3
0219 inc di
021a cmp di, 3
021d jl 0x3329
021f inc word ptr [bp - 4]
0222 add dx, 0x40
0225 cmp dx, 0xc0
0229 jl 0x331d
022b pop si
022c pop di
022d leave 
022e retf 
022f nop 
0230 mov bx, 0x28e8
0233 mov ax, 0x303
0236 mov cx, 0x20
0239 mov di, bx
023b push ds
023c pop es
023d rep stosw word ptr es:[di], ax
023f add bx, 0x40
0242 cmp bx, 0x48a8
0246 jbe 0x3353
0248 jmp 0x33f7
024b nop 
024c nop 
024d push cs
024e call 0x34c2 ; _CarpetFloorL
0251 push 2
0253 push 0x2e
0255 push 8
0257 push 0x5f
0259 push 0x2d
025b nop 
025c push cs
025d call 0x3faa ; _FillMapLegs
0260 add sp, 0xa
0263 pop si
0264 pop di
0265 leave 
0266 retf 
0267 nop 
0268 nop 
0269 push cs
026a call 0x34c2 ; _CarpetFloorL
026d push 2
026f push 0x2d
0271 push 0xa
0273 push 0x64
0275 push 0x32
0277 nop 
0278 push cs
0279 call 0x3faa ; _FillMapLegs
027c add sp, 0xa
027f xor di, di
0281 mov word ptr [bp - 4], di
0284 mov word ptr [bp - 2], di
0287 mov dx, di
0289 xor si, si
028b mov di, word ptr [bp - 4]
028e add di, 0x2356
0292 mov word ptr [bp - 2], dx
0295 mov bx, dx
0297 mov al, byte ptr [di]
0299 add di, 3
029c mov byte ptr [bx + si + 0x3bca], al
02a0 inc si
02a1 cmp si, 3
02a4 jl 0x33b5
02a6 inc word ptr [bp - 4]
02a9 add dx, 0x40
02ac cmp dx, 0xc0
02b0 jl 0x33a9
02b2 pop si
02b3 pop di
02b4 leave 
02b5 retf 
02b6 nop 
02b7 push cs
02b8 call 0x35e2 ; _CarpetFloorR
02bb pop si
02bc pop di
02bd leave 
02be retf 
02bf nop 
02c0 mov bx, 0x28e8
02c3 xor ax, ax
02c5 mov cx, 0x20
02c8 mov di, bx
02ca push ds
02cb pop es
02cc rep stosw word ptr es:[di], ax
02ce add bx, 0x40
02d1 cmp bx, 0x48a8
02d5 jbe 0x33e3
02d7 mov es, word ptr [0xc434]
02db mov word ptr es:[0x9c66], 2
02e2 pop si
02e3 pop di
02e4 leave 
02e5 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearListR', 'offset': 12532, 'source': 'src/recovered/wf_tu_simone_2B42_FindInAList_7_scaffold-13e673a867.c', 'size': 12}
- {'symbol': '_MakeMap', 'offset': 12544, 'source': None, 'size': 32}
- {'symbol': '_FloorTiles', 'offset': 13318, 'source': None, 'size': 188}
- {'symbol': '_CarpetFloorL', 'offset': 13506, 'source': None, 'size': 181}

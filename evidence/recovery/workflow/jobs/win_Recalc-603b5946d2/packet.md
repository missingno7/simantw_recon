# Recovery task _win_Recalc

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 738 bytes.

```asm
0000 enter 0x2c, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 6]
0009 sar bx, 8
000c shl bx, 2
000f les bx, ptr [bx - 0x3166]
0013 mov di, bx
0015 mov word ptr [bp - 0x22], es
0018 mov ax, word ptr es:[bx + 0xc]
001c mov word ptr [bp - 0x26], ax
001f or ax, ax
0021 jle 0xe740
0023 lea ax, [di + 0x2c]
0026 mov cx, es
0028 mov word ptr [bp - 4], ax
002b mov word ptr [bp - 2], cx
002e mov ax, word ptr [bp - 0x26]
0031 mov word ptr [bp - 6], ax
0034 mov bx, word ptr [bp - 4]
0037 mov cx, ax
0039 mov word ptr [bp - 0x24], di
003c mov ds, word ptr [bp - 2]
003f mov ax, 0x8000
0042 les si, ptr [bx]
0044 mov word ptr es:[si + 6], ax
0048 mov word ptr es:[si + 2], ax
004c mov word ptr es:[si + 4], ax
0050 mov word ptr es:[si], ax
0053 add bx, 4
0056 dec cx
0057 jne 0xe721
0059 mov di, word ptr [bp - 0x24]
005c push ss
005d pop ds
005e xor ax, ax
0060 mov word ptr [bp - 0x18], ax
0063 cmp word ptr [bp - 0x26], ax
0066 jg 0xe74d
0068 jmp 0xe87c
006b lea ax, [di + 0x2c]
006e mov cx, word ptr [bp - 0x22]
0071 mov word ptr [bp - 0x14], ax
0074 mov word ptr [bp - 0x12], cx
0077 mov ax, word ptr [bp - 0x26]
007a mov word ptr [bp - 0x1e], ax
007d mov word ptr [bp - 0x24], di
0080 les bx, ptr [bp - 0x14]
0083 les bx, ptr es:[bx]
0086 mov di, bx
0088 mov word ptr [bp - 0x1a], es
008b test byte ptr es:[bx + 0x24], 0x40
0090 je 0xe78b
0092 push es
0093 push di
0094 nop 
0095 push cs
0096 call 0xe406 ; _win_AutoSize
0099 add sp, 4
009c mov es, word ptr [bp - 0x1a]
009f mov word ptr es:[di + 0xc], ax
00a3 mov ax, dx
00a5 mov word ptr es:[di + 0xe], ax
00a9 mov ax, di
00ab mov dx, es
00ad mov cx, di
00af mov word ptr [bp - 0xa], dx
00b2 add ax, 0x10
00b5 mov word ptr [bp - 6], dx
00b8 mov word ptr [bp - 0xe], 4
00bd mov si, ax
00bf mov es, word ptr [bp - 6]
00c2 mov ax, word ptr es:[si + 8]
00c6 cmp ax, 5
00c9 ja 0xe7c2
00cb shl ax, 1
00cd xchg bx, ax
00ce jmp word ptr cs:[bx - 0x184a]
00d3 nop 
00d4 dw offset 0xe7c8
00d6 dw offset 0xe7cc
00d8 dw offset 0xe7d4
00da dw offset 0xe7dc
00dc dw offset 0xe7e4
00de dw offset 0xe7fe
00e0 mov cx, 1
00e3 jmp 0xe851
00e6 xor cx, cx
00e8 jmp 0xe83a
00ea mov word ptr [bp - 2], 0
00ef jmp 0xe7e9
00f1 nop 
00f2 mov word ptr [bp - 2], 1
00f7 jmp 0xe7e9
00f9 nop 
00fa mov word ptr [bp - 2], 2
00ff jmp 0xe7e9
0101 nop 
0102 mov word ptr [bp - 2], 3
0107 push word ptr [bp - 2]
010a push word ptr es:[si]
010d nop 
010e push cs
010f call 0xe4e8 ; _win_GetVal
0112 add sp, 4
0115 mov word ptr [bp - 4], ax
0118 mov cx, ax
011a jmp 0xe83a
011c mov ax, word ptr es:[si]
011f mov word ptr [bp - 2], ax
0122 mov al, byte ptr [bp + 7]
0125 cwde 
0126 mov es, word ptr [0xc6dc]
012a cmp ax, word ptr es:[0x78de]
012f jl 0xe820
0131 cmp word ptr [bp + 6], 0x2800
0136 jge 0xe820
0138 mov cx, 0x8000
013b jmp 0xe83a
013d nop 
013e mov ax, word ptr [bp - 2]
0141 shl ax, 1
0143 mov bx, word ptr [bp + 6]
0146 sar bx, 8
0149 shl bx, 2
014c les bx, ptr [bx - 0x3166]
0150 add bx, 0x10
0153 add bx, ax
0155 mov cx, word ptr es:[bx]
0158 cmp cx, 0x8000
015c je 0xe84e
015e mov es, word ptr [bp - 6]
0161 lea bx, [si - 8]
0164 add cx, word ptr es:[bx]
0167 mov word ptr [bp - 2], cx
016a jmp 0xe851
016c mov cx, 0x8000
016f mov es, word ptr [bp - 0xa]
0172 cmp word ptr es:[di], cx
0175 je 0xe85f
0177 mov word ptr es:[di], cx
017a inc word ptr [bp - 0x18]
017d add si, 2
0180 add di, 2
0183 dec word ptr [bp - 0xe]
0186 je 0xe86d
0188 jmp 0xe7a1
018b add word ptr [bp - 0x14], 4
018f dec word ptr [bp - 0x1e]
0192 je 0xe879
0194 jmp 0xe762
0197 mov di, word ptr [bp - 0x24]
019a cmp word ptr [bp - 0x18], 0
019e je 0xe885
01a0 jmp 0xe740
01a3 mov word ptr [bp - 0x24], di
01a6 les bx, ptr [bp - 0x24]
01a9 mov ax, word ptr es:[bx + 0x2c]
01ad mov dx, word ptr es:[bx + 0x2e]
01b1 push es
01b2 push ds
01b3 mov si, ax
01b5 mov ds, dx
01b7 movsw word ptr es:[di], word ptr [si]
01b8 movsw word ptr es:[di], word ptr [si]
01b9 movsw word ptr es:[di], word ptr [si]
01ba movsw word ptr es:[di], word ptr [si]
01bb pop ds
01bc pop es
01bd les bx, ptr es:[bx + 0x2c]
01c1 cmp byte ptr es:[bx + 0x21], 0xf
01c6 jne 0xe8cc
01c8 les bx, ptr [bp - 0x24]
01cb les si, ptr es:[bx + 0x2c]
01cf mov al, byte ptr es:[si + 0x28]
01d3 cwde 
01d4 mov es, word ptr [bp - 0x22]
01d7 add word ptr es:[bx], ax
01da add word ptr es:[bx + 2], ax
01de mov cx, ax
01e0 inc ax
01e1 sub word ptr es:[bx + 4], ax
01e5 inc cx
01e6 sub word ptr es:[bx + 6], cx
01ea cmp word ptr [bp - 0x26], 0
01ee jle 0xe944
01f0 mov ax, word ptr [bp - 0x24]
01f3 mov dx, word ptr [bp - 0x22]
01f6 add ax, 0x2c
01f9 mov cx, ax
01fb mov word ptr [bp - 6], dx
01fe mov es, word ptr [0xc6de]
0202 mov ax, word ptr es:[0xbd0a]
0206 mov word ptr [bp - 0x2c], ax
0209 mov ax, word ptr [bp - 0x26]
020c mov word ptr [bp - 4], ax
020f mov di, word ptr [bp - 0x24]
0212 mov es, word ptr [bp - 6]
0215 mov si, cx
0217 lds bx, ptr es:[si]
021a mov ax, word ptr [bx]
021c mov word ptr [bp - 2], ax
021f cmp ax, word ptr [bx + 4]
0222 jle 0xe911
0224 mov ax, word ptr [bx + 4]
0227 mov word ptr [bx], ax
0229 mov ax, word ptr [bp - 2]
022c mov word ptr [bx + 4], ax
022f mov ax, word ptr [bx + 2]
0232 mov word ptr [bp - 2], ax
0235 cmp ax, word ptr [bx + 6]
0238 jle 0xe928
023a mov ax, word ptr [bx + 6]
023d mov word ptr [bx + 2], ax
0240 mov ax, word ptr [bp - 2]
0243 mov word ptr [bx + 6], ax
0246 cmp word ptr [bp - 0x2c], 0
024a je 0xe94a
024c mov es, word ptr [bp - 0x22]
024f mov ax, word ptr es:[di]
0252 mov dx, ax
0254 add ax, 2
0257 sub word ptr [bx], ax
0259 add dx, 2
025c sub word ptr [bx + 4], dx
025f jmp 0xe955
0261 nop 
0262 mov di, word ptr [bp - 0x24]
0265 jmp 0xe9a5
0267 nop 
0268 mov es, word ptr [bp - 0x22]
026b mov ax, word ptr es:[di]
026e sub word ptr [bx], ax
0270 sub word ptr [bx + 4], ax
0273 test byte ptr es:[di + 0x1c], 4
0278 je 0xe970
027a mov ax, word ptr es:[di + 2]
027e mov dx, ax
0280 add ax, 0x12
0283 sub word ptr [bx + 2], ax
0286 add dx, 0x12
0289 sub word ptr [bx + 6], dx
028c jmp 0xe992
028e cmp word ptr [bp - 0x2c], 0
0292 je 0xe988
0294 mov ax, word ptr es:[di + 2]
0298 mov dx, ax
029a add ax, 2
029d sub word ptr [bx + 2], ax
02a0 add dx, 2
02a3 jmp 0xe96b
02a5 nop 
02a6 mov ax, word ptr es:[di + 2]
02aa sub word ptr [bx + 2], ax
02ad sub word ptr [bx + 6], ax
02b0 dec word ptr [bx + 4]
02b3 dec word ptr [bx + 6]
02b6 add cx, 4
02b9 dec word ptr [bp - 4]
02bc je 0xe9a3
02be jmp 0xe8f4
02c1 push ss
02c2 pop ds
02c3 mov es, word ptr [bp - 0x22]
02c6 les bx, ptr es:[di + 0x2c]
02ca cmp byte ptr es:[bx + 0x21], 0xf
02cf jne 0xe9c0
02d1 mov es, word ptr [bp - 0x22]
02d4 les bx, ptr es:[di + 0x2c]
02d8 mov word ptr es:[bx + 2], 0
02de pop si
02df pop di
02e0 leave 
02e1 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_GetArg', 'offset': 58738, 'source': None, 'size': 60}
- {'symbol': '__win_CalcObjElement', 'offset': 58798, 'source': None, 'size': 307}
- {'symbol': '_win_SetObjSelectableState', 'offset': 59844, 'source': 'src/recovered/win_SetObjSelectableState.c', 'size': 62}
- {'symbol': '_win_MakeObjSelectable', 'offset': 59906, 'source': 'src/recovered/win_MakeObjSelectable.c', 'size': 46}

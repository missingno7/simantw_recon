# Recovery task _TryMoveDirB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 266 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xa]
0009 or si, si
000b jge 0x43b2
000d xor ax, ax
000f pop si
0010 pop di
0011 leave 
0012 retf 
0013 nop 
0014 mov es, word ptr [0xc364]
0018 mov al, byte ptr es:[si + 8]
001d cwde 
001e mov di, ax
0020 add di, word ptr [bp + 8]
0023 mov es, word ptr [0xc366]
0027 mov al, byte ptr es:[si]
002c cwde 
002d add ax, word ptr [bp + 6]
0030 cmp ax, 0x3f
0033 jg 0x43ab
0035 or ax, ax
0037 jl 0x43ab
0039 cmp di, 0x3f
003c jg 0x43ab
003e cmp di, 1
0041 jge 0x43f0
0043 push word ptr [bp + 6]
0046 nop 
0047 push cs
0048 call 0x520a ; _GetOutB
004b add sp, 2
004e pop si
004f pop di
0050 leave 
0051 retf 
0052 mov si, ax
0054 mov bx, ax
0056 shl bx, 6
0059 add bx, di
005b mov word ptr [bp - 4], bx
005e cmp byte ptr [bx + 0x48e8], 0x1c
0063 jae 0x43ab
0065 cmp byte ptr [bx - 0x7718], 0xff
006a jne 0x4453
006c mov es, word ptr [0xc37e]
0070 cmp word ptr es:[0x9af2], 0
0076 je 0x4453
0078 mov es, word ptr [0xc350]
007c mov bx, word ptr es:[0x9b6a]
0081 mov es, word ptr [0xc352]
0085 cmp byte ptr es:[bx + 0x3736], 0x80
008b jae 0x4453
008d mov al, byte ptr es:[bx + 0x3d18]
0092 and al, 0xf8
0094 or al, byte ptr [bp + 0xa]
0097 mov bx, word ptr [bp + 6]
009a shl bx, 6
009d add bx, word ptr [bp + 8]
00a0 mov byte ptr [bx - 0x7718], al
00a4 push word ptr [bp + 0xa]
00a7 push word ptr [bp + 8]
00aa push word ptr [bp + 6]
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoTroph
00b2 add sp, 6
00b5 mov es, word ptr [0xc350]
00b9 mov bx, word ptr es:[0x9b6a]
00be mov es, word ptr [0xc352]
00c2 mov al, byte ptr es:[bx + 0x3d18]
00c7 and al, 0xf8
00c9 or al, byte ptr [bp + 0xa]
00cc lea cx, [bx + 0x3d18]
00d0 mov dx, bx
00d2 mov bx, word ptr [bp - 4]
00d5 mov byte ptr [bx - 0x7718], al
00d9 mov bx, word ptr [bp + 8]
00dc mov ax, si
00de mov si, word ptr [bp + 6]
00e1 shl si, 6
00e4 mov byte ptr [bx + si - 0x7718], 0
00e9 mov bx, dx
00eb mov byte ptr es:[bx + 0x3736], al
00f0 mov ax, di
00f2 mov byte ptr es:[bx + 0x392c], al
00f7 mov bx, word ptr [bp - 4]
00fa mov al, byte ptr [bx - 0x7718]
00fe mov bx, cx
0100 mov byte ptr es:[bx], al
0103 mov ax, 1
0106 pop si
0107 pop di
0108 leave 
0109 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LostHeadB', 'offset': 17118, 'source': None, 'size': 94}
- {'symbol': '_LostTailB', 'offset': 17212, 'source': None, 'size': 98}
- {'symbol': '_DoNestingB', 'offset': 17576, 'source': None, 'size': 797}
- {'symbol': '_TryEatFoodB', 'offset': 18374, 'source': None, 'size': 126}

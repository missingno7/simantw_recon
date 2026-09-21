# Recovery task _FoodFall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 150 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov word ptr [bp - 8], 1
000e mov cx, di
0010 mov si, word ptr [bp + 8]
0013 shl di, 6
0016 mov es, word ptr [0xc2f2]
001a mov bx, word ptr es:[0x9c66]
001f mov al, byte ptr [bx + 0x22be]
0023 sub ah, ah
0025 shl ax, 6
0028 mov word ptr [bp - 6], ax
002b mov bx, di
002d add bx, si
002f add bx, 0x28e8
0033 mov al, byte ptr [bx]
0035 sub ah, ah
0037 mov word ptr [bp - 2], ax
003a cmp ax, 4
003d jge 0xf01
003f mov al, byte ptr [bp - 2]
0042 add al, 6
0044 shl al, 2
0047 mov byte ptr [bx], al
0049 mov es, word ptr [0xc2f0]
004d inc word ptr es:[0x9e84]
0052 mov word ptr [bp - 8], 0
0057 add di, word ptr [bp - 6]
005a mov es, word ptr [0xc2f2]
005e mov bx, word ptr es:[0x9c66]
0063 mov al, byte ptr [bx + 0x22c2]
0067 sub ah, ah
0069 add si, ax
006b mov al, byte ptr [bx + 0x22be]
006f add cx, ax
0071 js 0xf28
0073 cmp cx, 0x7f
0076 jg 0xf28
0078 mov dx, word ptr [bp - 8]
007b jmp 0xf2a
007d nop 
007e xor dx, dx
0080 or si, si
0082 jl 0xf33
0084 cmp si, 0x3f
0087 jle 0xf35
0089 xor dx, dx
008b mov word ptr [bp - 8], dx
008e or dx, dx
0090 jne 0xed5
0092 pop si
0093 pop di
0094 leave 
0095 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PickupFoodA', 'offset': 3352, 'source': None, 'size': 109}
- {'symbol': '_DropFoodA', 'offset': 3462, 'source': None, 'size': 292}
- {'symbol': '_PickupFoodB', 'offset': 3904, 'source': None, 'size': 98}
- {'symbol': '_PickupFoodR', 'offset': 4002, 'source': None, 'size': 98}

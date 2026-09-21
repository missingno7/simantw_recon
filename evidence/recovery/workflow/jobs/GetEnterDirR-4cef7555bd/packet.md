# Recovery task _GetEnterDirR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 152 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 0xa]
0009 xor al, 4
000b mov word ptr [bp - 4], ax
000e mov word ptr [bp - 8], 0xffff
0013 mov es, word ptr [0xc2f4]
0017 mov bx, word ptr [bp + 6]
001a shl bx, 6
001d add bx, word ptr [bp + 8]
0020 mov al, byte ptr es:[bx + 0x13a4]
0025 sub ah, ah
0027 mov word ptr [bp - 6], ax
002a xor si, si
002c cmp word ptr [bp - 4], si
002f je 0x1407
0031 mov es, word ptr [0xc2f6]
0035 mov al, byte ptr es:[si + 8]
003a cwde 
003b mov cx, ax
003d add cx, word ptr [bp + 8]
0040 mov es, word ptr [0xc2f8]
0044 mov al, byte ptr es:[si]
0049 cwde 
004a add ax, word ptr [bp + 6]
004d js 0x1407
004f cmp ax, 0x3f
0052 jg 0x1407
0054 or cx, cx
0056 jl 0x1407
0058 cmp cx, 0x3f
005b jg 0x1407
005d mov es, word ptr [0xc2f4]
0061 mov bx, ax
0063 shl bx, 6
0066 add bx, cx
0068 mov al, byte ptr es:[bx + 0x13a4]
006d sub ah, ah
006f mov di, ax
0071 or di, di
0073 je 0x1407
0075 cmp word ptr [bp - 6], di
0078 jl 0x1407
007a jg 0x1401
007c nop 
007d push cs
007e call 0x15ae ; _SRand2
0081 or ax, ax
0083 je 0x1407
0085 mov word ptr [bp - 6], di
0088 mov word ptr [bp - 8], si
008b inc si
008c cmp si, 8
008f jl 0x13a8
0091 mov ax, word ptr [bp - 8]
0094 pop si
0095 pop di
0096 leave 
0097 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetExitDirR', 'offset': 4672, 'source': None, 'size': 164}
- {'symbol': '_GetEnterDirB', 'offset': 4836, 'source': None, 'size': 152}
- {'symbol': '_TryAntTheme', 'offset': 5140, 'source': None, 'size': 104}
- {'symbol': '_SGIRand', 'offset': 5244, 'source': None, 'size': 39}

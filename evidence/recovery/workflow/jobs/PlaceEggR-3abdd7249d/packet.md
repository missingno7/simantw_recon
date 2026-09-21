# Recovery task _PlaceEggR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 100 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc2d8]
0009 cmp word ptr es:[0x72cc], 0x1f4
0010 jge 0x10c8
0012 mov si, word ptr [bp + 6]
0015 or si, si
0017 jl 0x1098
0019 mov di, word ptr [bp + 8]
001c cmp si, 0x3f
001f jg 0x109b
0021 cmp di, 1
0024 jl 0x109b
0026 cmp di, 0x3f
0029 jg 0x109b
002b mov dx, 1
002e jmp 0x109d
0030 mov di, word ptr [bp + 8]
0033 xor dx, dx
0035 or dx, dx
0037 je 0x10c8
0039 push di
003a push si
003b nop 
003c push cs
003d call 0x21de ; _DigTileR
0040 add sp, 4
0043 push 0
0045 push 8
0047 push word ptr [bp + 0xa]
004a push di
004b push si
004c nop 
004d push cs
004e call 0x2fa4 ; _AddAntToRList
0051 add sp, 0xa
0054 mov al, byte ptr [bp + 0xa]
0057 mov bx, si
0059 shl bx, 6
005c mov byte ptr [bx + di - 0x6718], al
0060 pop si
0061 pop di
0062 leave 
0063 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PickupFoodR', 'offset': 4002, 'source': None, 'size': 98}
- {'symbol': '_PlaceEggB', 'offset': 4100, 'source': None, 'size': 100}
- {'symbol': '_GetDir', 'offset': 4300, 'source': None, 'size': 86}
- {'symbol': '_GetDis', 'offset': 4386, 'source': 'src/recovered/GetDis.c', 'size': 57}

# Recovery task _PickupFoodA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 109 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c mov bx, si
000e shl bx, 6
0011 add bx, di
0013 add bx, 0x28e8
0017 mov word ptr [bp - 4], bx
001a mov cl, byte ptr [bx]
001c sub ch, ch
001e mov es, word ptr [0xc2e6]
0022 cmp word ptr es:[0x9b6e], 0
0028 jne 0xd54
002a cmp cx, 0x48
002d jne 0xd6e
002f nop 
0030 push cs
0031 call 0x160e ; _SRand16
0034 mov bx, word ptr [bp - 4]
0037 mov byte ptr [bx], al
0039 jmp 0xd70
003b nop 
003c mov word ptr [bp - 2], cx
003f mov ax, cx
0041 mov cx, 4
0044 cdq 
0045 idiv cx
0047 or dx, dx
0049 jne 0xd6e
004b mov ax, word ptr [bp - 2]
004e sub ax, 0x18
0051 sar ax, 2
0054 jmp 0xd4c
0056 dec byte ptr [bx]
0058 mov es, word ptr [0xc2f0]
005c cmp word ptr es:[0x9e84], 0
0062 jle 0xd81
0064 dec word ptr es:[0x9e84]
0069 pop si
006a pop di
006b leave 
006c retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddWater', 'offset': 2954, 'source': None, 'size': 201}
- {'symbol': '_DropWater', 'offset': 3156, 'source': None, 'size': 195}
- {'symbol': '_DropFoodA', 'offset': 3462, 'source': None, 'size': 292}
- {'symbol': '_FoodFall', 'offset': 3754, 'source': None, 'size': 150}

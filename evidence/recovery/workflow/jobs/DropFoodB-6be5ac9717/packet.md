# Recovery task _DropFoodB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 100 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c xor cx, cx
000e mov bx, si
0010 shl bx, 6
0013 add bx, di
0015 add bx, 0x48e8
0019 mov word ptr [bp - 2], bx
001c mov dl, byte ptr [bx]
001e sub dh, dh
0020 cmp dx, 0x10
0023 jge 0x3c66
0025 mov byte ptr [bx], 0x10
0028 jmp 0x3c6d
002a cmp dx, 0x13
002d jge 0x3c70
002f inc byte ptr [bx]
0031 mov cx, 1
0034 mov es, word ptr [0xc362]
0038 inc word ptr es:[0x9ea4]
003d mov es, word ptr [0xc350]
0041 mov bx, word ptr es:[0x9b6a]
0046 add bx, 0x3d18
004a mov es, word ptr [0xc352]
004e mov word ptr [bp - 6], bx
0051 mov word ptr [bp - 4], es
0054 test byte ptr es:[bx], 8
0058 je 0x3c9a
005a sub byte ptr es:[bx], 8
005e mov ax, cx
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

- {'symbol': '_DoNestFightB', 'offset': 14932, 'source': None, 'size': 334}
- {'symbol': '_CheckNestFightB', 'offset': 15266, 'source': None, 'size': 154}
- {'symbol': '_SimEggB', 'offset': 15520, 'source': None, 'size': 290}
- {'symbol': '_SimQueenB', 'offset': 15810, 'source': None, 'size': 666}

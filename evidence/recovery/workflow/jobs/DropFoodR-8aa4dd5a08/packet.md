# Recovery task _DropFoodR

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
0015 add bx, 0x58e8
0019 mov word ptr [bp - 2], bx
001c mov dl, byte ptr [bx]
001e sub dh, dh
0020 cmp dx, 0x10
0023 jge 0x626c
0025 mov byte ptr [bx], 0x10
0028 jmp 0x6273
002a cmp dx, 0x13
002d jge 0x6276
002f inc byte ptr [bx]
0031 mov cx, 1
0034 mov es, word ptr [0xc394]
0038 inc word ptr es:[0x72de]
003d mov es, word ptr [0xc384]
0041 mov bx, word ptr es:[0x9b6a]
0046 add bx, 0x46e6
004a mov es, word ptr [0xc386]
004e mov word ptr [bp - 6], bx
0051 mov word ptr [bp - 4], es
0054 test byte ptr es:[bx], 8
0058 je 0x62a0
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

- {'symbol': '_DoNestFightR', 'offset': 24690, 'source': None, 'size': 304}
- {'symbol': '_CheckNestFightR', 'offset': 24994, 'source': None, 'size': 160}
- {'symbol': '_SimEggR', 'offset': 25254, 'source': None, 'size': 223}
- {'symbol': '_SimQueenR', 'offset': 25478, 'source': None, 'size': 639}

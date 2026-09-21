# Recovery task _SimEggA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 88 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 4]
0009 mov es, word ptr [0xc318]
000d mov al, byte ptr es:[si + 0x278e]
0012 sub ah, ah
0014 mov word ptr [bp - 2], ax
0017 mov cl, byte ptr es:[si + 0x2f62]
001c mov dl, byte ptr es:[si + 0x23a4]
0021 sub dh, dh
0023 mov di, dx
0025 mov bx, dx
0027 shl bx, 6
002a add bx, ax
002c mov byte ptr [bx + 0x68e8], cl
0030 push 0xc8
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0038 add sp, 2
003b or ax, ax
003d jne 0xa70
003f xor al, al
0041 mov es, word ptr [0xc318]
0045 mov byte ptr es:[si + 0x2f62], al
004a shl di, 6
004d mov bx, word ptr [bp - 2]
0050 mov byte ptr [bx + di + 0x68e8], al
0054 pop si
0055 pop di
0056 leave 
0057 ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FeedAnts', 'offset': 1140, 'source': None, 'size': 100}
- {'symbol': '_DoAntSimA', 'offset': 1240, 'source': None, 'size': None}
- {'symbol': '_SimQueenA', 'offset': 2676, 'source': None, 'size': 169}
- {'symbol': '_LostHeadA', 'offset': 2846, 'source': None, 'size': 87}

# Recovery task _PillFoodTile

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 110 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c push di
000d push si
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0013 add sp, 4
0016 dec ax
0017 jne 0x5a6c
0019 push di
001a push si
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0020 add sp, 4
0023 dec ax
0024 jne 0x5a56
0026 mov es, word ptr [0xc5a0]
002a test byte ptr es:[0x9b1e], 1
0030 je 0x5a38
0032 mov ax, si
0034 jmp 0x5a3a
0036 mov ax, di
0038 mov cx, 6
003b cdq 
003c idiv cx
003e mov es, word ptr [0xc5a6]
0042 mov bx, dx
0044 shl bx, 1
0046 mov al, byte ptr es:[bx + 0x7c0e]
004b mov bx, si
004d shl bx, 6
0050 mov byte ptr [bx + di + 0x28e8], al
0054 mov bx, si
0056 shl bx, 6
0059 add bx, di
005b add bx, 0x28e8
005f mov word ptr [bp - 2], bx
0062 cmp byte ptr [bx], 0x18
0065 jae 0x5a6c
0067 mov byte ptr [bx], 0x4b
006a pop si
006b pop di
006c leave 
006d retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsPillDead', 'offset': 22314, 'source': None, 'size': 168}
- {'symbol': '_MakePillFood', 'offset': 22482, 'source': None, 'size': 560}
- {'symbol': '_InitSimVars', 'offset': 23152, 'source': 'src/recovered/InitSimVars.c', 'size': 63}
- {'symbol': '_RandWorld', 'offset': 23216, 'source': None, 'size': 1493}

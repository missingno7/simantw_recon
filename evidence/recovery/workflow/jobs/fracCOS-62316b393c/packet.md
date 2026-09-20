# Recovery task _fracCOS

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 74 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov bx, di
000a sub bl, 0xc0
000d and bx, 0x7f
0010 cmp bx, 0x3f
0013 jle 0x6a2a
0015 mov ax, 0x80
0018 sub ax, bx
001a mov bx, ax
001c cmp bx, 0x40
001f jne 0x6a34
0021 mov cx, 0x7fff
0024 jmp 0x6a45
0026 and bx, 0x3f
0029 shl bx, 1
002b mov es, word ptr [0xc628]
002f les si, ptr es:[0x9fca]
0034 mov cx, word ptr es:[bx + si]
0037 mov ax, di
0039 add al, 0x40
003b sub ah, ah
003d cmp ax, 0x7f
0040 jle 0x6a52
0042 neg cx
0044 mov ax, cx
0046 pop si
0047 pop di
0048 leave 
0049 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeRedQueen', 'offset': 26886, 'source': None, 'size': 194}
- {'symbol': '_fracSIN', 'offset': 27080, 'source': 'src/recovered/wf_fracSIN-85445ba91f.c', 'size': 70}
- {'symbol': '_AddFood', 'offset': 27224, 'source': None, 'size': 513}
- {'symbol': '_AddBlackAnts', 'offset': 27738, 'source': None, 'size': 163}

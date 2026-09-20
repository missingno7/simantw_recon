# Recovery task _fracSIN

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 70 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov bx, di
000a and bx, 0x7f
000d cmp bx, 0x3f
0010 jle 0x69e1
0012 mov ax, 0x80
0015 sub ax, bx
0017 mov bx, ax
0019 cmp bx, 0x40
001c jne 0x69ec
001e mov cx, 0x7fff
0021 jmp 0x69fd
0023 nop 
0024 and bx, 0x3f
0027 shl bx, 1
0029 mov es, word ptr [0xc628]
002d les si, ptr es:[0x9fca]
0032 mov cx, word ptr es:[bx + si]
0035 mov ax, di
0037 sub ah, ah
0039 cmp ax, 0x7f
003c jle 0x6a08
003e neg cx
0040 mov ax, cx
0042 pop si
0043 pop di
0044 leave 
0045 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PlaceRedQueen', 'offset': 26586, 'source': None, 'size': 299}
- {'symbol': '_MakeRedQueen', 'offset': 26886, 'source': None, 'size': 194}
- {'symbol': '_fracCOS', 'offset': 27150, 'source': None, 'size': 74}
- {'symbol': '_AddFood', 'offset': 27224, 'source': None, 'size': 513}

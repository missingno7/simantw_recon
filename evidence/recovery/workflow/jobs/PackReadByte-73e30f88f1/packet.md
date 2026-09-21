# Recovery task _PackReadByte

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 81 bytes.

```asm
0000 cmp word ptr [0xcc34], 0
0005 jne 0xa29f
0007 mov ax, word ptr [0xcc3e]
000a mov dx, word ptr [0xcc40]
000e mov word ptr [0xcc36], ax
0011 mov word ptr [0xcc38], dx
0015 mov cx, word ptr [0xcc30]
0019 mov word ptr [0xcc34], cx
001d push cx
001e push dx
001f push ax
0020 lcall [0xcc2c]
0024 add sp, 6
0027 mov word ptr [0xcc34], ax
002a cmp ax, 0xffff
002d je 0xa2b1
002f or ax, ax
0031 jne 0xa26a
0033 jmp 0xa2b1
0035 dec word ptr [0xcc34]
0039 les bx, ptr [0xcc36]
003d inc word ptr [0xcc36]
0041 mov al, byte ptr es:[bx]
0044 sub ah, ah
0046 retf 
0047 mov word ptr [0xcc34], 0
004d mov ax, 0xffff
0050 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DeleteIndex', 'offset': 41078, 'source': None, 'size': 245}
- {'symbol': '_PackWriteByte', 'offset': 41473, 'source': None, 'size': 64}
- {'symbol': '_PackFileToFile', 'offset': 41765, 'source': None, 'size': 87}
- {'symbol': '_PackMemoryToMemory', 'offset': 41917, 'source': None, 'size': 78}

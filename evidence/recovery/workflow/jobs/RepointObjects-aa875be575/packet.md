# Recovery task _RepointObjects

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 91 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 sar si, 8
000c shl si, 2
000f les cx, ptr [si - 0x3166]
0013 mov si, cx
0015 mov ax, word ptr es:[si + 0xc]
0019 mov bx, ax
001b shl ax, 2
001e mov di, bx
0020 add ax, si
0022 mov dx, es
0024 add ax, 0x2c
0027 mov word ptr [bp - 8], ax
002a mov word ptr [bp - 6], dx
002d or di, di
002f jle 0xc65d
0031 mov ax, si
0033 add ax, 0x2c
0036 mov di, ax
0038 mov word ptr [bp - 0xa], bx
003b mov si, di
003d lds bx, ptr [bp - 8]
0040 mov cx, word ptr [bp - 0xa]
0043 mov word ptr es:[si], bx
0046 mov word ptr es:[si + 2], ds
004a mov ax, word ptr [bx + 0x22]
004d add bx, ax
004f add si, 4
0052 dec cx
0053 jne 0xc649
0055 push ss
0056 pop ds
0057 pop si
0058 pop di
0059 leave 
005a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_WinAddr', 'offset': 50126, 'source': 'src/recovered/win_WinAddr.c', 'size': 22}
- {'symbol': '_win_SetPalette', 'offset': 50148, 'source': None, 'size': 546}
- {'symbol': '_win_LoadWindow', 'offset': 50786, 'source': None, 'size': 419}
- {'symbol': '_win_LoadAllWindows', 'offset': 51206, 'source': None, 'size': 552}

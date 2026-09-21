# Recovery task __font_StringWidth

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 150 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 lds di, ptr [bp + 0xa]
0009 xor cx, cx
000b mov si, cx
000d cmp word ptr [di + 0x26], cx
0010 je 0xad3a
0012 cmp word ptr [di + 8], cx
0015 jge 0xace2
0017 mov ax, 1
001a jmp 0xace4
001c xor ax, ax
001e mov word ptr [bp - 2], ax
0021 les bx, ptr [bp + 6]
0024 cmp byte ptr es:[bx], 0
0028 je 0xad36
002a mov bx, word ptr [di + 0x28]
002d shl bx, 1
002f mov es, word ptr [di + 0x24]
0032 add bx, word ptr [di + 0x22]
0035 mov al, byte ptr es:[bx]
0038 sub ah, ah
003a mov word ptr [bp - 6], ax
003d les bx, ptr [bp + 6]
0040 mov bl, byte ptr es:[bx + si]
0043 sub bh, bh
0045 shl bx, 1
0047 mov es, word ptr [di + 0x24]
004a add bx, word ptr [di + 0x22]
004d mov ax, word ptr es:[bx]
0050 mov word ptr [bp - 8], ax
0053 inc ax
0054 je 0xad26
0056 mov al, byte ptr [bp - 8]
0059 sub ah, ah
005b add cx, ax
005d jmp 0xad29
005f nop 
0060 add cx, word ptr [bp - 6]
0063 inc si
0064 add cx, word ptr [bp - 2]
0067 les bx, ptr [bp + 6]
006a cmp byte ptr es:[bx + si], 0
006e jne 0xad03
0070 mov si, cx
0072 jmp 0xad54
0074 mov bx, di
0076 mov ax, word ptr [bx + 6]
0079 mov dx, ax
007b les di, ptr [bp + 6]
007e mov cx, 0xffff
0081 xor ax, ax
0083 repne scasb al, byte ptr es:[di]
0085 not cx
0087 dec cx
0088 mov ax, dx
008a imul cx
008c mov si, ax
008e mov ax, si
0090 push ss
0091 pop ds
0092 pop si
0093 pop di
0094 leave 
0095 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_font_ReadFont', 'offset': 43596, 'source': None, 'size': 509}
- {'symbol': '_font_DumpFont', 'offset': 44106, 'source': None, 'size': 123}
- {'symbol': '__font_CharWidth', 'offset': 44380, 'source': None, 'size': 99}
- {'symbol': '__font_FontHeight', 'offset': 44480, 'source': 'src/recovered/font_FontHeightNative.c', 'size': 13}

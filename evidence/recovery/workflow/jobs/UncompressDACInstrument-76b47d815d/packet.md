# Recovery task _UncompressDACInstrument

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 133 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov byte ptr [bp - 1], 0x80
000a mov ax, word ptr [bp + 6]
000d mov dx, word ptr [bp + 8]
0010 mov cx, 8
0013 push ds
0014 lea di, [bp - 0x16]
0017 mov si, ax
0019 push ss
001a pop es
001b mov ds, dx
001d rep movsw word ptr es:[di], word ptr [si]
001f pop ds
0020 add word ptr [bp + 6], 0x10
0024 xor di, di
0026 mov word ptr [bp - 6], di
0029 shr word ptr [bp + 0xe], 1
002c cmp word ptr [bp + 0xe], di
002f je 0x7707
0031 mov word ptr [bp - 4], di
0034 mov si, di
0036 les cx, ptr [bp + 0xa]
0039 mov ds, dx
003b mov bx, word ptr [bp + 6]
003e add bx, di
0040 mov bl, byte ptr [bx]
0042 mov ax, bx
0044 shr bl, 4
0047 sub bh, bh
0049 lea dx, [bp - 0x16]
004c add bx, dx
004e mov dl, byte ptr ss:[bx]
0051 add byte ptr [bp - 1], dl
0054 mov dl, byte ptr [bp - 1]
0057 mov bx, cx
0059 mov byte ptr es:[bx + si], dl
005c mov bl, al
005e and bx, 0xf
0061 lea ax, [bp - 0x16]
0064 add bx, ax
0066 add dl, byte ptr ss:[bx]
0069 mov byte ptr [bp - 1], dl
006c mov bx, cx
006e inc si
006f mov byte ptr es:[bx + si], dl
0072 inc si
0073 inc di
0074 cmp di, word ptr [bp + 0xe]
0077 jb 0x76c7
0079 push ss
007a pop ds
007b mov ax, word ptr [bp + 0xa]
007e mov dx, word ptr [bp + 0xc]
0081 pop si
0082 pop di
0083 leave 
0084 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_gr_GetFromBuf', 'offset': 29664, 'source': None, 'size': 342}
- {'symbol': '_gr_PutToBuf', 'offset': 30006, 'source': None, 'size': 342}
- {'symbol': '_IsMMMidiAvail', 'offset': 30482, 'source': 'src/recovered/wf_IsMMMidiAvail-25316c8456.c', 'size': 42}
- {'symbol': '_IsMMWaveAvail', 'offset': 30524, 'source': 'src/recovered/wf_IsMMWaveAvail-6cf4f4e231.c', 'size': 42}

# Recovery task _CalcBitmapStuff

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 146 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov bx, word ptr [bp + 0xe]
0008 or bx, bx
000a jge 0x1e94
000c mov ax, bx
000e neg ax
0010 les si, ptr [bp + 0x12]
0013 mov word ptr es:[si], ax
0016 mov ax, word ptr [bp + 0xc]
0019 les si, ptr [bp + 0x16]
001c mov word ptr es:[si], ax
001f jmp 0x1eba
0021 nop 
0022 les si, ptr [bp + 0x12]
0025 mov word ptr es:[si], 0
002a mov di, word ptr [bp + 8]
002d mov cx, word ptr [bp + 0xc]
0030 mov ax, bx
0032 add ax, cx
0034 cmp ax, di
0036 jle 0x1eb4
0038 sub di, bx
003a les bx, ptr [bp + 0x16]
003d mov word ptr es:[bx], di
0040 jmp 0x1eba
0042 les bx, ptr [bp + 0x16]
0045 mov word ptr es:[bx], cx
0048 mov bx, word ptr [bp + 0x10]
004b or bx, bx
004d jge 0x1ed8
004f mov ax, bx
0051 neg ax
0053 les si, ptr [bp + 0x1a]
0056 mov word ptr es:[si], ax
0059 mov ax, word ptr [bp + 0xa]
005c les si, ptr [bp + 0x1e]
005f mov word ptr es:[si], ax
0062 pop si
0063 pop di
0064 leave 
0065 retf 
0066 les si, ptr [bp + 0x1a]
0069 mov word ptr es:[si], 0
006e mov di, word ptr [bp + 6]
0071 mov cx, word ptr [bp + 0xa]
0074 mov ax, bx
0076 add ax, cx
0078 cmp ax, di
007a jle 0x1efa
007c sub di, bx
007e les bx, ptr [bp + 0x1e]
0081 mov word ptr es:[bx], di
0084 pop si
0085 pop di
0086 leave 
0087 retf 
0088 les bx, ptr [bp + 0x1e]
008b mov word ptr es:[bx], cx
008e pop si
008f pop di
0090 leave 
0091 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_BitmapImageSize', 'offset': 7040, 'source': 'src/recovered/BitmapImageSize.c', 'size': 49}
- {'symbol': '_ConvertMaskBitmap', 'offset': 7090, 'source': None, 'size': 703}
- {'symbol': '_ConvertMaskBitmap2', 'offset': 7940, 'source': None, 'size': 1385}
- {'symbol': '_ConvertBitmap', 'offset': 9326, 'source': None, 'size': 674}

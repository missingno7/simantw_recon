# Recovery task _ConvertMonoBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 123 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xe]
0009 mov bx, word ptr [bp + 0x10]
000c lea ax, [bx + 0x1f]
000f cdq 
0010 and dx, 0x1f
0013 add ax, dx
0015 sar ax, 5
0018 shl ax, 2
001b mov word ptr [bp - 0xe], ax
001e lea ax, [bx + 7]
0021 cdq 
0022 and dx, 7
0025 add ax, dx
0027 sar ax, 3
002a mov word ptr [bp - 0xa], ax
002d or di, di
002f jle 0x3645
0031 mov ax, word ptr [bp + 0xa]
0034 mov dx, word ptr [bp + 0xc]
0037 mov word ptr [bp - 4], ax
003a mov ds, dx
003c lea ax, [di - 1]
003f imul word ptr [bp - 0xe]
0042 add ax, word ptr [bp + 6]
0045 mov dx, word ptr [bp + 8]
0048 mov word ptr [bp - 8], ax
004b mov word ptr [bp - 6], dx
004e mov word ptr [bp - 0xc], di
0051 mov ax, word ptr [bp - 4]
0054 mov cx, word ptr [bp - 0xa]
0057 mov si, ax
0059 les di, ptr [bp - 8]
005c shr cx, 1
005e rep movsw word ptr es:[di], word ptr [si]
0060 adc cx, cx
0062 rep movsb byte ptr es:[di], byte ptr [si]
0064 mov ax, word ptr [bp - 0xa]
0067 add word ptr [bp - 4], ax
006a mov ax, word ptr [bp - 0xe]
006d sub word ptr [bp - 8], ax
0070 dec word ptr [bp - 0xc]
0073 jne 0x3621
0075 push ss
0076 pop ds
0077 pop si
0078 pop di
0079 leave 
007a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CopyMonoMaskBitmap', 'offset': 11988, 'source': None, 'size': 1110}
- {'symbol': '_DoBitmap', 'offset': 13098, 'source': None, 'size': 678}
- {'symbol': '_DoMonoBitmap', 'offset': 13900, 'source': None, 'size': 870}
- {'symbol': '_DoFastBitmap', 'offset': 14770, 'source': None, 'size': 405}

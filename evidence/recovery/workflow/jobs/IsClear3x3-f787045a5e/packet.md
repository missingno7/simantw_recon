# Recovery task _IsClear3x3

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 90 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 0xa]
0008 push di
0009 push word ptr [bp + 8]
000c push word ptr [bp + 6]
000f nop 
0010 push cs
0011 call 0x5b2c ; _IsClearTile
0014 add sp, 6
0017 dec ax
0018 jne 0x5b26
001a xor si, si
001c mov es, word ptr [0xc478]
0020 mov al, byte ptr es:[si + 8]
0025 cwde 
0026 add ax, di
0028 push ax
0029 mov es, word ptr [0xc47a]
002d mov al, byte ptr es:[si]
0032 cwde 
0033 add ax, word ptr [bp + 8]
0036 push ax
0037 push word ptr [bp + 6]
003a nop 
003b push cs
003c call 0x5b2c ; _IsClearTile
003f add sp, 6
0042 or ax, ax
0044 je 0x5b26
0046 inc si
0047 cmp si, 8
004a jl 0x5aee
004c mov ax, 1
004f pop si
0050 pop di
0051 leave 
0052 retf 
0053 nop 
0054 xor ax, ax
0056 pop si
0057 pop di
0058 leave 
0059 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindLifeIndex', 'offset': 22818, 'source': None, 'size': 217}
- {'symbol': '_FindAntIndex', 'offset': 23036, 'source': None, 'size': 213}
- {'symbol': '_IsClearTile', 'offset': 23340, 'source': None, 'size': 332}
- {'symbol': '_AddAntToList', 'offset': 23672, 'source': None, 'size': 159}

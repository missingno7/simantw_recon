# Recovery task _CheckMyBestDirs

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 169 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xe]
0009 mov word ptr [bp - 6], 0
000e push word ptr [bp + 0x12]
0011 push word ptr [bp + 0x10]
0014 push di
0015 push word ptr [bp + 0xc]
0018 push word ptr [bp + 0xa]
001b nop 
001c push cs
001d call 0x8828 ; _GetMyBestDirs
0020 add sp, 0xa
0023 mov si, ax
0025 or si, si
0027 jl 0x8b8c
0029 mov es, word ptr [0xc3ca]
002d mov al, byte ptr es:[si]
0032 cwde 
0033 add ax, word ptr [bp + 0xc]
0036 mov word ptr [bp - 2], ax
0039 mov es, word ptr [0xc3c4]
003d mov al, byte ptr es:[si + 8]
0042 cwde 
0043 add ax, di
0045 mov word ptr [bp - 4], ax
0048 or si, si
004a jge 0x8b92
004c mov di, word ptr [bp - 6]
004f jmp 0x8bd6
0051 nop 
0052 mov di, word ptr [bp - 6]
0055 cmp di, 0x40
0058 jge 0x8bd6
005a push word ptr [bp + 0x12]
005d push word ptr [bp + 0x10]
0060 push word ptr [bp - 4]
0063 push word ptr [bp - 2]
0066 push word ptr [bp + 0xa]
0069 nop 
006a push cs
006b call 0x8828 ; _GetMyBestDirs
006e add sp, 0xa
0071 mov si, ax
0073 or si, si
0075 jl 0x8bd1
0077 mov es, word ptr [0xc3ca]
007b mov al, byte ptr es:[si]
0080 cwde 
0081 add word ptr [bp - 2], ax
0084 mov es, word ptr [0xc3c4]
0088 mov al, byte ptr es:[si + 8]
008d cwde 
008e add word ptr [bp - 4], ax
0091 inc di
0092 or si, si
0094 jge 0x8b95
0096 les bx, ptr [bp + 6]
0099 mov word ptr es:[bx], di
009c or si, si
009e jl 0x8be3
00a0 mov si, 0xffff
00a3 mov ax, si
00a5 pop si
00a6 pop di
00a7 leave 
00a8 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetMyBestDirs', 'offset': 34856, 'source': None, 'size': 256}
- {'symbol': '_GetMyRandDirs', 'offset': 35112, 'source': None, 'size': 536}
- {'symbol': '_GetMyNextRandDirs', 'offset': 35818, 'source': None, 'size': 244}
- {'symbol': '_GetMyInitialRandDir', 'offset': 36062, 'source': None, 'size': 91}

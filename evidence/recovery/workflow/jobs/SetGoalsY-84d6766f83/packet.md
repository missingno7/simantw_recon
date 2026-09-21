# Recovery task _SetGoalsY

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 105 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov cx, word ptr [bp + 6]
0006 or cx, cx
0008 jne 0x734c
000a mov es, word ptr [0xbf1a]
000e mov word ptr es:[0x9be0], 1
0015 jmp 0x7355
0017 nop 
0018 mov es, word ptr [0xbf1a]
001c mov word ptr es:[0x9be0], cx
0021 mov bx, word ptr [bp + 8]
0024 mov es, word ptr [0xbf1c]
0028 mov word ptr es:[0x80c6], bx
002d mov ax, word ptr [bp + 0xa]
0030 mov es, word ptr [0xbf1e]
0034 mov word ptr es:[0x80d2], ax
0038 mov es, word ptr [0xbf20]
003c mov word ptr es:[0x72e4], 0xfffe
0043 cmp cx, 2
0046 jl 0x739b
0048 cmp ax, 2
004b jge 0x739b
004d or bx, bx
004f jg 0x738a
0051 mov bx, 1
0054 jmp 0x7392
0056 cmp bx, 0x3f
0059 jl 0x7392
005b mov bx, 0x3e
005e mov es, word ptr [0xbf1c]
0062 mov word ptr es:[0x80c6], bx
0067 leave 
0068 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_processSpider', 'offset': 29080, 'source': None, 'size': 290}
- {'symbol': '_ResetYellowVars', 'offset': 29370, 'source': None, 'size': 122}
- {'symbol': '_YellowBirth', 'offset': 29598, 'source': None, 'size': 936}
- {'symbol': '_YellowDeath', 'offset': 30534, 'source': None, 'size': None}

# Recovery task _WaitedEnough

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 94 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 nop 
0009 push cs
000a call 0x18ac ; _TickCount
000d mov es, word ptr [bp + 8]
0010 cmp word ptr es:[di + 2], dx
0014 jg 0x47fa
0016 jl 0x47d5
0018 cmp word ptr es:[di], ax
001b ja 0x47fa
001d nop 
001e push cs
001f call 0x18ac ; _TickCount
0022 mov cx, ax
0024 mov ax, word ptr [bp + 0xa]
0027 mov bx, dx
0029 cdq 
002a mov es, word ptr [bp + 8]
002d add ax, word ptr es:[di]
0030 adc dx, word ptr es:[di + 2]
0034 cmp dx, bx
0036 jl 0x47fa
0038 jg 0x47f6
003a cmp ax, cx
003c jbe 0x47fa
003e xor si, si
0040 jmp 0x47fd
0042 mov si, 1
0045 or si, si
0047 je 0x4810
0049 nop 
004a push cs
004b call 0x18ac ; _TickCount
004e mov es, word ptr [bp + 8]
0051 mov word ptr es:[di], ax
0054 mov word ptr es:[di + 2], dx
0058 mov ax, si
005a pop si
005b pop di
005c leave 
005d retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_gr_BitMapSize', 'offset': 18012, 'source': None, 'size': 185}
- {'symbol': '_StillDown', 'offset': 18198, 'source': None, 'size': 161}
- {'symbol': '_gr_CenterStrInRectClear', 'offset': 18454, 'source': None, 'size': 217}
- {'symbol': '_gr_CenterStrInRect', 'offset': 18672, 'source': None, 'size': 137}

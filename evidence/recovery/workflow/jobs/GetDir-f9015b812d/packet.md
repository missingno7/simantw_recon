# Recovery task _GetDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 86 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov dx, word ptr [bp + 0xc]
0006 sub dx, word ptr [bp + 8]
0009 mov bx, word ptr [bp + 0xa]
000c sub bx, word ptr [bp + 6]
000f jne 0x10f6
0011 or dx, dx
0013 jne 0x10e6
0015 xor ax, ax
0017 leave 
0018 retf 
0019 nop 
001a or dx, dx
001c jge 0x10f0
001e mov ax, 1
0021 leave 
0022 retf 
0023 nop 
0024 mov ax, 5
0027 leave 
0028 retf 
0029 nop 
002a or bx, bx
002c jle 0x110e
002e or dx, dx
0030 jge 0x1104
0032 mov ax, 2
0035 leave 
0036 retf 
0037 nop 
0038 cmp dx, 1
003b sbb ax, ax
003d add ax, 4
0040 leave 
0041 retf 
0042 or dx, dx
0044 jle 0x1118
0046 mov ax, 6
0049 jmp 0x1120
004b nop 
004c cmp dx, 1
004f sbb ax, ax
0051 add ax, 8
0054 leave 
0055 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PlaceEggB', 'offset': 4100, 'source': None, 'size': 100}
- {'symbol': '_PlaceEggR', 'offset': 4200, 'source': None, 'size': 100}
- {'symbol': '_GetDis', 'offset': 4386, 'source': 'src/recovered/GetDis.c', 'size': 57}
- {'symbol': '_InNestBounds', 'offset': 4444, 'source': 'src/recovered/wf_InNestBounds-bacfde5aec.c', 'size': 38}

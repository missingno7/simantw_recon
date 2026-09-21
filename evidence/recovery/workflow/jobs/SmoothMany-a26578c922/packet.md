# Recovery task _SmoothMany

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 87 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 8]
0008 mov si, word ptr [bp + 6]
000b push di
000c push si
000d nop 
000e push cs
000f call 0x88f4 ; _SmoothACell
0012 add sp, 4
0015 lea ax, [di - 1]
0018 push ax
0019 push si
001a nop 
001b push cs
001c call 0x88f4 ; _SmoothACell
001f add sp, 4
0022 push di
0023 lea ax, [si + 1]
0026 push ax
0027 nop 
0028 push cs
0029 call 0x88f4 ; _SmoothACell
002c add sp, 4
002f lea ax, [di + 1]
0032 push ax
0033 push si
0034 nop 
0035 push cs
0036 call 0x88f4 ; _SmoothACell
0039 add sp, 4
003c push di
003d lea ax, [si - 1]
0040 push ax
0041 nop 
0042 push cs
0043 call 0x88f4 ; _SmoothACell
0046 add sp, 4
0049 push di
004a push si
004b nop 
004c push cs
004d call 0x88f4 ; _SmoothACell
0050 add sp, 4
0053 pop si
0054 pop di
0055 leave 
0056 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FillDirtB', 'offset': 34584, 'source': None, 'size': 193}
- {'symbol': '_FillDirtR', 'offset': 34778, 'source': None, 'size': 193}
- {'symbol': '_SmoothACell', 'offset': 35060, 'source': None, 'size': 944}
- {'symbol': '_IsValidSLoc', 'offset': 36004, 'source': 'src/recovered/IsValidSLoc.c', 'size': 36}

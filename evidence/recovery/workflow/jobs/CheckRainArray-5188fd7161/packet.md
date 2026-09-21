# Recovery task _CheckRainArray

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 97 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 xor dx, dx
0006 mov bx, 0xcb04
0009 cmp word ptr [bx], -1
000c jne 0xa4d4
000e inc dx
000f add bx, 2
0012 cmp bx, 0xcb20
0016 jbe 0xa4c5
0018 cmp dx, 0xe
001b jg 0xa518
001d push word ptr [bp + 8]
0020 push word ptr [bp + 6]
0023 push ds
0024 push 0x18b8
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
002c add sp, 8
002f mov si, 0xcb04
0032 push word ptr [si]
0034 push ds
0035 push 0x18bb
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
003d add sp, 6
0040 add si, 2
0043 cmp si, 0xcb20
0047 jbe 0xa4ee
0049 push ds
004a push 0x18c0
004d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0052 add sp, 4
0055 mov ax, 1
0058 pop si
0059 leave 
005a retf 
005b nop 
005c xor ax, ax
005e pop si
005f leave 
0060 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SaveGame', 'offset': 41534, 'source': None, 'size': 626}
- {'symbol': '_ClearLastFileName', 'offset': 42160, 'source': 'src/recovered/ClearLastFileName.c', 'size': 11}
- {'symbol': '_ProcYardEvent', 'offset': 42270, 'source': None, 'size': None}
- {'symbol': '_ProcYardRibbonEvent', 'offset': 42702, 'source': None, 'size': None}

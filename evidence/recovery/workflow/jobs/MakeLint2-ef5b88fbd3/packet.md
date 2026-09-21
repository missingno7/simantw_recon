# Recovery task _MakeLint2

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 105 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 8]
0009 mov bx, word ptr [bp + 6]
000c cmp bx, dx
000e jg 0x35dd
0010 mov ax, bx
0012 shl ax, 6
0015 mov word ptr [bp - 2], ax
0018 mov ax, dx
001a sub ax, bx
001c inc ax
001d mov word ptr [bp - 4], ax
0020 mov si, word ptr [bp + 0xa]
0023 cmp si, word ptr [bp + 0xc]
0026 jle 0x35a6
0028 mov di, word ptr [bp - 2]
002b jmp 0x35d2
002d nop 
002e mov di, word ptr [bp - 2]
0031 push 0xc8
0034 nop 
0035 push cs
0036 call 0x158a ; _SRand1
0039 add sp, 2
003c or ax, ax
003e jne 0x35cc
0040 push 2
0042 nop 
0043 push cs
0044 call 0x158a ; _SRand1
0047 add sp, 2
004a add al, 0x3e
004c mov bx, di
004e add bx, si
0050 mov byte ptr [bx + 0x28e8], al
0054 inc si
0055 cmp si, word ptr [bp + 0xc]
0058 jle 0x35a9
005a add di, 0x40
005d mov word ptr [bp - 2], di
0060 dec word ptr [bp - 4]
0063 jne 0x3598
0065 pop si
0066 pop di
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

- {'symbol': '_FloorTiles', 'offset': 13318, 'source': None, 'size': 188}
- {'symbol': '_CarpetFloorL', 'offset': 13506, 'source': None, 'size': 181}
- {'symbol': '_CarpetFloorR', 'offset': 13794, 'source': None, 'size': 182}
- {'symbol': '_MakeKitchenWall', 'offset': 13976, 'source': None, 'size': 196}

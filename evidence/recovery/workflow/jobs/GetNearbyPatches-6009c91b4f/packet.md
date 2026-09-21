# Recovery task _GetNearbyPatches

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 103 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 xor cx, cx
0008 mov word ptr [bp - 2], cx
000b mov bx, word ptr [bp - 2]
000e mov si, word ptr [bx + 0x25e2]
0012 and si, 0xff
0016 add si, word ptr [bp + 8]
0019 mov al, byte ptr [bx + 0x25dc]
001d sub ah, ah
001f mov di, ax
0021 add di, word ptr [bp + 6]
0024 js 0x3d3c
0026 or si, si
0028 jl 0x3d3c
002a cmp di, 0xc
002d jge 0x3d3c
002f cmp si, 0x10
0032 jge 0x3d3c
0034 mov es, word ptr [0xc564]
0038 mov bx, di
003a shl bx, 4
003d add bx, si
003f cmp byte ptr es:[bx + 0xa4], ah
0044 je 0x3d2d
0046 add cx, 3
0049 mov es, word ptr [0xc562]
004d cmp byte ptr es:[bx + 0x164], 0
0053 je 0x3d3c
0055 sub cx, 3
0058 inc word ptr [bp - 2]
005b cmp word ptr [bp - 2], 6
005f jl 0x3cef
0061 mov ax, cx
0063 pop si
0064 pop di
0065 leave 
0066 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MaintainSwarm', 'offset': 13696, 'source': None, 'size': 119}
- {'symbol': '_SimColonies', 'offset': 13816, 'source': None, 'size': 1771}
- {'symbol': '_Reproduce', 'offset': 15692, 'source': None, 'size': 165}
- {'symbol': '_StartMigrate', 'offset': 15858, 'source': None, 'size': 121}

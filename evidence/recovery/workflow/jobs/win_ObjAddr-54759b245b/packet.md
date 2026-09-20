# Recovery task _win_ObjAddr

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 72 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov ax, di
000b sub ah, ah
000d mov bx, di
000f sar bx, 8
0012 shl bx, 2
0015 les bx, ptr [bx - 0x3166]
0019 mov si, bx
001b mov word ptr [bp - 2], es
001e cmp word ptr es:[bx + 0xc], ax
0022 jg 0xc35e
0024 push ds
0025 push 0xbd12
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
002d add sp, 4
0030 mov es, word ptr [bp - 2]
0033 mov bx, di
0035 sub bh, bh
0037 shl bx, 2
003a add bx, si
003c mov ax, word ptr es:[bx + 0x2c]
0040 mov dx, word ptr es:[bx + 0x2e]
0044 pop si
0045 pop di
0046 leave 
0047 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_Zoom', 'offset': 49850, 'source': 'src/recovered/win_Zoom.c', 'size': 24}
- {'symbol': '_win_GetObjRect', 'offset': 49874, 'source': None, 'size': 91}
- {'symbol': '_win_WinObjAddr', 'offset': 50038, 'source': None, 'size': 87}
- {'symbol': '_win_WinAddr', 'offset': 50126, 'source': 'src/recovered/win_WinAddr.c', 'size': 22}

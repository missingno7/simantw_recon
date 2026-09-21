# Recovery task _win_WinObjAddr

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 87 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 and si, 0xff00
000d add si, word ptr [bp + 8]
0010 mov bx, si
0012 sar bx, 8
0015 shl bx, 2
0018 mov ax, word ptr [bx - 0x3166]
001c mov dx, word ptr [bx - 0x3164]
0020 mov di, ax
0022 mov word ptr [bp - 2], dx
0025 mov es, dx
0027 mov bx, di
0029 mov ax, si
002b sub ah, ah
002d cmp word ptr es:[bx + 0xc], ax
0031 jg 0xc3b5
0033 push ds
0034 push 0xbd12
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
003c add sp, 4
003f mov es, word ptr [bp - 2]
0042 mov bx, si
0044 sub bh, bh
0046 shl bx, 2
0049 add bx, di
004b mov ax, word ptr es:[bx + 0x2c]
004f mov dx, word ptr es:[bx + 0x2e]
0053 pop si
0054 pop di
0055 leave 
0056 retf 
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

- {'symbol': '_win_GetObjRect', 'offset': 49874, 'source': None, 'size': 91}
- {'symbol': '_win_ObjAddr', 'offset': 49966, 'source': 'src/recovered/wf_win_ObjAddr-54759b245b.c', 'size': 72}
- {'symbol': '_win_WinAddr', 'offset': 50126, 'source': 'src/recovered/win_WinAddr.c', 'size': 22}
- {'symbol': '_win_SetPalette', 'offset': 50148, 'source': None, 'size': 546}

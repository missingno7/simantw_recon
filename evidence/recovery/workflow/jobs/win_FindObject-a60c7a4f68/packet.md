# Recovery task _win_FindObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 101 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 sar di, 8
000c shl di, 2
000f les bx, ptr [di - 0x3166]
0013 mov ax, word ptr es:[bx + 0xc]
0017 dec ax
0018 mov si, ax
001a or ax, ax
001c jl 0xd10e
001e shl ax, 2
0021 add ax, bx
0023 add ax, 0x2c
0026 mov word ptr [bp - 6], es
0029 mov di, ax
002b mov es, word ptr [bp - 6]
002e les bx, ptr es:[di]
0031 test byte ptr es:[bx + 0x24], 2
0036 je 0xd0fc
0038 push es
0039 push bx
003a push word ptr [bp + 0xa]
003d push word ptr [bp + 8]
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PointInRect
0045 add sp, 8
0048 or ax, ax
004a jne 0xd104
004c sub di, 4
004f dec si
0050 jns 0xd0db
0052 jmp 0xd10e
0054 mov ax, si
0056 or ax, word ptr [bp + 6]
0059 pop si
005a pop di
005b leave 
005c retf 
005d nop 
005e mov ax, word ptr [bp + 6]
0061 pop si
0062 pop di
0063 leave 
0064 retf 
```

## Known declaration examples

- `extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_Close', 'offset': 53144, 'source': None, 'size': 168}
- {'symbol': '_win_Events', 'offset': 53312, 'source': None, 'size': 112}
- {'symbol': '_UpdateAllWindows', 'offset': 53526, 'source': 'src/recovered/wf_UpdateAllWindows-97a1ff92dc.c', 'size': 58}
- {'symbol': '_win_GetEvent', 'offset': 53584, 'source': None, 'size': 420}

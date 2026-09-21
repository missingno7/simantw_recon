# Recovery task _StorePillarMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 110 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 8]
0008 mov si, word ptr [bp + 6]
000b push di
000c push si
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0012 add sp, 4
0015 dec ax
0016 jne 0x536e
0018 mov es, word ptr [0xc5a0]
001c test byte ptr es:[0x9b1e], 1
0022 je 0x534a
0024 mov bx, si
0026 shl bx, 6
0029 mov al, byte ptr [bx + di + 0x28e8]
002d sub ah, ah
002f mov cx, ax
0031 mov ax, si
0033 mov dx, 6
0036 mov bx, dx
0038 cdq 
0039 idiv bx
003b mov bx, dx
003d shl bx, 1
003f mov es, word ptr [0xc5a6]
0043 jmp 0x5369
0045 nop 
0046 mov bx, si
0048 shl bx, 6
004b mov al, byte ptr [bx + di + 0x28e8]
004f mov cx, ax
0051 mov ax, di
0053 mov dx, 6
0056 mov bx, dx
0058 cdq 
0059 idiv bx
005b mov bx, dx
005d shl bx, 1
005f mov es, word ptr [0xc5a6]
0063 sub ch, ch
0065 mov word ptr es:[bx + 0x7c0e], cx
006a pop si
006b pop di
006c leave 
006d retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitPillar', 'offset': 19448, 'source': None, 'size': 228}
- {'symbol': '_DoPillar', 'offset': 19676, 'source': None, 'size': 1576}
- {'symbol': '_ReplacePillarMap', 'offset': 21362, 'source': None, 'size': 104}
- {'symbol': '_MakeAPill', 'offset': 21466, 'source': None, 'size': 767}

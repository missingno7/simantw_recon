# Recovery task _Extract24BitVal

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 118 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 les bx, ptr [bp + 0xa]
0008 sub ax, ax
000a mov word ptr es:[bx + 2], ax
000e mov word ptr es:[bx], ax
0011 mov ax, es
0013 add bx, 1
0016 adc ax, 0
0019 les si, ptr [bp + 6]
001c mov dx, word ptr es:[si]
001f mov di, word ptr es:[si + 2]
0023 push si
0024 push es
0025 push ds
0026 push di
0027 mov di, bx
0029 mov si, dx
002b mov es, ax
002d pop ds
002e movsw word ptr es:[di], word ptr [si]
002f movsb byte ptr es:[di], byte ptr [si]
0030 pop ds
0031 pop es
0032 pop si
0033 les bx, ptr [bp + 0xa]
0036 push word ptr es:[bx + 2]
003a push word ptr es:[bx]
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipLong
0042 add sp, 4
0045 les bx, ptr [bp + 0xa]
0048 mov word ptr es:[bx], ax
004b mov word ptr es:[bx + 2], dx
004f les bx, ptr [bp + 6]
0052 mov ax, word ptr es:[bx]
0055 mov dx, word ptr es:[bx + 2]
0059 add ax, 3
005c adc dx, 0
005f mov word ptr es:[bx], ax
0062 mov word ptr es:[bx + 2], dx
0066 les bx, ptr [bp + 0xe]
0069 sub word ptr es:[bx], 3
006d sbb word ptr es:[bx + 2], 0
0072 pop si
0073 pop di
0074 leave 
0075 retf 
```

## Known declaration examples

- `extern unsigned long far FlipLong(unsigned long value);` — src/recovered/wf_ExtractDWord-f367d1b9bc.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExtractWord', 'offset': 33782, 'source': 'src/recovered/ExtractWord.c', 'size': 68}
- {'symbol': '_ExtractVariableLen', 'offset': 33850, 'source': None, 'size': 222}
- {'symbol': '_myBeginSong', 'offset': 34190, 'source': None, 'size': None}
- {'symbol': '_MciOutWave', 'offset': 38300, 'source': None, 'size': 788}

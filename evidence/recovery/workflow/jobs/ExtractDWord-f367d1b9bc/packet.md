# Recovery task _ExtractDWord

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 81 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 0xa]
0008 mov si, word ptr [bp + 6]
000b mov es, word ptr [bp + 8]
000e les bx, ptr es:[si]
0011 mov ax, word ptr es:[bx]
0014 mov dx, word ptr es:[bx + 2]
0018 mov es, word ptr [bp + 0xc]
001b mov word ptr es:[di], ax
001e mov word ptr es:[di + 2], dx
0022 push dx
0023 push ax
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipLong
0029 add sp, 4
002c mov es, word ptr [bp + 0xc]
002f mov word ptr es:[di], ax
0032 mov word ptr es:[di + 2], dx
0036 mov es, word ptr [bp + 8]
0039 mov ax, word ptr es:[si]
003c mov dx, word ptr es:[si + 2]
0040 add ax, 4
0043 adc dx, 0
0046 mov word ptr es:[si], ax
0049 mov word ptr es:[si + 2], dx
004d pop si
004e pop di
004f leave 
0050 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_myBeginSoundList', 'offset': 33426, 'source': 'src/recovered/myBeginSoundList.c', 'size': 1}
- {'symbol': '_StopSong', 'offset': 33428, 'source': None, 'size': 272}
- {'symbol': '_ExtractWord', 'offset': 33782, 'source': 'src/recovered/ExtractWord.c', 'size': 68}
- {'symbol': '_ExtractVariableLen', 'offset': 33850, 'source': None, 'size': 222}

# Recovery task _FlipHandleWords

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 82 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push si
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
000f add sp, 2
0012 shr dx, 1
0014 rcr ax, 1
0016 mov di, ax
0018 push si
0019 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
001e add sp, 2
0021 or di, di
0023 jle 0x78a3
0025 mov cx, di
0027 mov bx, ax
0029 mov ds, dx
002b mov ax, word ptr [bx]
002d mov dx, ax
002f mov ah, al
0031 mov word ptr [bp - 0xa], ax
0034 mov al, dh
0036 mov ah, byte ptr [bp - 0xa]
0039 mov word ptr [bx], ax
003b add bx, 2
003e dec cx
003f jne 0x788b
0041 push ss
0042 pop ds
0043 push word ptr [bp + 6]
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
004b add sp, 2
004e pop si
004f pop di
0050 leave 
0051 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FinishVertStep', 'offset': 30662, 'source': None, 'size': 119}
- {'symbol': '_BlockMove', 'offset': 30782, 'source': None, 'size': 33}
- {'symbol': '_OverlayOutsideTiles', 'offset': 30898, 'source': 'src/recovered/OverlayOutsideTiles.c', 'size': 12}
- {'symbol': '_OverlayInsideTiles', 'offset': 30910, 'source': 'src/recovered/OverlayInsideTiles.c', 'size': 12}

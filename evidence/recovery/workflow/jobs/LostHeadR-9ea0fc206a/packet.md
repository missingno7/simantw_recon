# Recovery task _LostHeadR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 94 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc396]
000a mov bl, byte ptr [bp + 0xa]
000d and bx, 7
0010 mov al, byte ptr es:[bx + 8]
0015 cwde 
0016 mov si, ax
0018 add si, word ptr [bp + 8]
001b mov di, word ptr [bp + 0xa]
001e sub di, 8
0021 mov es, word ptr [0xc398]
0025 mov al, byte ptr es:[bx]
002a cwde 
002b mov bx, ax
002d add bx, word ptr [bp + 6]
0030 mov word ptr [bp - 2], bx
0033 shl bx, 6
0036 mov al, byte ptr [bx + si - 0x6718]
003a sub ah, ah
003c cmp ax, di
003e jne 0x67d6
0040 xor ax, ax
0042 pop si
0043 pop di
0044 leave 
0045 retf 
0046 push di
0047 push si
0048 push word ptr [bp - 2]
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0050 add sp, 6
0053 or ax, ax
0055 jge 0x67d0
0057 mov ax, 1
005a pop si
005b pop di
005c leave 
005d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeNewTailR', 'offset': 26364, 'source': None, 'size': 101}
- {'symbol': '_KillTailR', 'offset': 26466, 'source': None, 'size': 45}
- {'symbol': '_LostTailR', 'offset': 26606, 'source': None, 'size': 98}
- {'symbol': '_TryMoveDirR', 'offset': 26704, 'source': None, 'size': 186}

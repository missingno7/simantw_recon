# Recovery task _LostTailR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 98 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc396]
000a mov bl, byte ptr [bp + 0xa]
000d xor bl, 0xfc
0010 and bx, 7
0013 mov al, byte ptr es:[bx + 8]
0018 cwde 
0019 mov si, ax
001b add si, word ptr [bp + 8]
001e mov di, word ptr [bp + 0xa]
0021 add di, 8
0024 mov es, word ptr [0xc398]
0028 mov al, byte ptr es:[bx]
002d cwde 
002e mov bx, ax
0030 add bx, word ptr [bp + 6]
0033 mov word ptr [bp - 2], bx
0036 shl bx, 6
0039 mov al, byte ptr [bx + si - 0x6718]
003d sub ah, ah
003f cmp ax, di
0041 jne 0x6838
0043 xor ax, ax
0045 pop si
0046 pop di
0047 leave 
0048 retf 
0049 nop 
004a push di
004b push si
004c push word ptr [bp - 2]
004f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0054 add sp, 6
0057 or ax, ax
0059 jge 0x6831
005b mov ax, 1
005e pop si
005f pop di
0060 leave 
0061 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_KillTailR', 'offset': 26466, 'source': None, 'size': 45}
- {'symbol': '_LostHeadR', 'offset': 26512, 'source': None, 'size': 94}
- {'symbol': '_TryMoveDirR', 'offset': 26704, 'source': None, 'size': 186}
- {'symbol': '_DoNestingR', 'offset': 26890, 'source': None, 'size': 557}

# Recovery task _ReadWord

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 109 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push 1
000b lea ax, [bp - 1]
000e push ss
000f push ax
0010 push di
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
0016 add sp, 8
0019 or ax, ax
001b je 0x832
001d mov al, byte ptr [bp - 1]
0020 cwde 
0021 push ax
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
0027 add sp, 2
002a or ax, ax
002c jne 0x80d
002e mov si, word ptr [bp + 8]
0031 mov al, byte ptr [bp - 1]
0034 mov es, word ptr [bp + 0xa]
0037 mov bx, si
0039 inc si
003a mov byte ptr es:[bx], al
003d push 1
003f lea ax, [bp - 1]
0042 push ss
0043 push ax
0044 push di
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
004a add sp, 8
004d or ax, ax
004f je 0x866
0051 mov al, byte ptr [bp - 1]
0054 cwde 
0055 push ax
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
005b add sp, 2
005e or ax, ax
0060 je 0x835
0062 mov es, word ptr [bp + 0xa]
0065 mov byte ptr es:[si], 0
0069 pop si
006a pop di
006b leave 
006c retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitGraphics', 'offset': 268, 'source': None, 'size': 275}
- {'symbol': '_IBMInitStuff', 'offset': 544, 'source': None, 'size': 1507}
- {'symbol': '_SkipWords', 'offset': 2162, 'source': None, 'size': 130}
- {'symbol': '_ReadConfig', 'offset': 2292, 'source': None, 'size': 548}

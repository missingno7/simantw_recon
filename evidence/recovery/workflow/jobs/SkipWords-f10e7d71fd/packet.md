# Recovery task _SkipWords

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 130 bytes.

```asm
0000 enter 0x24, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 jmp 0x8e6
000b nop 
000c lea ax, [bp - 0x24]
000f mov di, ax
0011 mov word ptr [bp - 4], ss
0014 mov word ptr [bp - 6], di
0017 push 1
0019 lea ax, [bp - 1]
001c push ss
001d push ax
001e push si
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
0024 add sp, 8
0027 or ax, ax
0029 je 0x8ae
002b mov al, byte ptr [bp - 1]
002e cwde 
002f push ax
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
0035 add sp, 2
0038 or ax, ax
003a jne 0x889
003c mov al, byte ptr [bp - 1]
003f mov es, word ptr [bp - 4]
0042 mov bx, di
0044 inc di
0045 mov byte ptr es:[bx], al
0048 push 1
004a lea ax, [bp - 1]
004d push ss
004e push ax
004f push si
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
0055 add sp, 8
0058 or ax, ax
005a je 0x8df
005c mov al, byte ptr [bp - 1]
005f cwde 
0060 push ax
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
0066 add sp, 2
0069 or ax, ax
006b je 0x8ae
006d mov es, word ptr [bp - 4]
0070 mov byte ptr es:[di], 0
0074 mov ax, word ptr [bp + 8]
0077 dec word ptr [bp + 8]
007a or ax, ax
007c jne 0x87e
007e pop si
007f pop di
0080 leave 
0081 retf 
```

## Known declaration examples

- `extern int far isspace(int character);` — src/recovered/wf_ReadWord-e51efa9f2b.c
- `extern int far read(int fd, void far *buffer, unsigned int count);` — src/recovered/wf_ReadWord-e51efa9f2b.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IBMInitStuff', 'offset': 544, 'source': None, 'size': 1507}
- {'symbol': '_ReadWord', 'offset': 2052, 'source': 'src/recovered/wf_ReadWord-e51efa9f2b.c', 'size': 109}
- {'symbol': '_ReadConfig', 'offset': 2292, 'source': None, 'size': 548}
- {'symbol': '_GBoxFillOutline', 'offset': 2840, 'source': None, 'size': 164}

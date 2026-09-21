# Recovery task _SpecialTutorialInit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 153 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push 0x5c
000b push word ptr [bp + 8]
000e push di
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
0014 add sp, 6
0017 mov si, ax
0019 mov word ptr [bp - 2], dx
001c or dx, ax
001e je 0x9d0e
0020 inc si
0021 jmp 0x9d16
0023 nop 
0024 mov ax, word ptr [bp + 8]
0027 mov si, di
0029 mov word ptr [bp - 2], ax
002c mov es, word ptr [0xc172]
0030 les bx, ptr es:[0x7294]
0035 push word ptr es:[bx + 2]
0039 push word ptr es:[bx]
003c push word ptr [bp - 2]
003f push si
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _stricmp,_strcmpi
0045 add sp, 8
0048 cmp ax, 1
004b sbb di, di
004d neg di
004f or di, di
0051 je 0x9d70
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GenerateTutorial
0058 push ds
0059 push 0x17dd
005c nop 
005d push cs
005e call 0x11b06
0061 add sp, 4
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitSimVars
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SeedSRand
006e push 1
0070 push -1
0072 push -2
0074 push 0
0076 push 0
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
007d add sp, 0xa
0080 mov ax, di
0082 pop si
0083 pop di
0084 leave 
0085 retf 
0086 mov ax, word ptr [bp - 2]
0089 push ax
008a push si
008b nop 
008c push cs
008d call 0x11b06
0090 add sp, 4
0093 mov ax, di
0095 pop si
0096 pop di
0097 leave 
0098 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': 'SAVEASDLG', 'offset': 38116, 'source': None, 'size': 1083}
- {'symbol': '_FileSelect', 'offset': 39200, 'source': None, 'size': 970}
- {'symbol': '_DoPreLoadInits', 'offset': 40324, 'source': 'src/recovered/wf_DoPreLoadInits-ed37124107.c', 'size': 58}
- {'symbol': '_DoLoadInitializations', 'offset': 40382, 'source': None, 'size': 481}

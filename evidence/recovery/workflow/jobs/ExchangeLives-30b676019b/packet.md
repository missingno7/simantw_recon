# Recovery task _ExchangeLives

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 149 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov es, word ptr [0xc488]
0007 mov word ptr es:[0x9fb0], 1
000e push word ptr [bp + 0xa]
0011 push word ptr [bp + 8]
0014 push word ptr [bp + 6]
0017 nop 
0018 push cs
0019 call 0x6842 ; _DoLifeExchange
001c mov sp, bp
001e dec ax
001f jne 0x6834
0021 mov es, word ptr [0xc482]
0025 mov word ptr es:[0x7c22], 0xffff
002c mov es, word ptr [0xc484]
0030 push word ptr es:[0x9ea2]
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PauseGame
003a mov sp, bp
003c cmp word ptr [0xcc84], 0x60 ; _MeType
0041 jne 0x682c
0043 push 0x7e
0045 push 0
0047 push 0xf
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
004e mov sp, bp
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySoundIsDone
005a or ax, ax
005c jne 0x681e
005e push 0
0060 push 5
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myDelay
0067 mov sp, bp
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySoundIsDone
006e or ax, ax
0070 je 0x680a
0072 push 0x7e
0074 push 0x2afe
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 122, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
007c mov sp, bp
007e leave 
007f retf 
0080 push 0x7e
0082 push 0
0084 push 0xf
0086 jmp 0x683a
0088 push 0x7e
008a push 0
008c push 1
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0093 leave 
0094 retf 
```

## Known declaration examples

- `extern void far DoEditUpdateDraw(void);` — src/recovered/DoEditAndMapUpdateDraw.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern void far PauseGame(int paused);` — src/recovered/EndLifeTransferMode.c
- `extern void far PauseGame(int paused);` — src/recovered/EndTargetMode.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_StartLifeTransfer', 'offset': 26436, 'source': None, 'size': 73}
- {'symbol': '_EndLifeTransferMode', 'offset': 26510, 'source': 'src/recovered/EndLifeTransferMode.c', 'size': 29}
- {'symbol': '_DoLifeExchange', 'offset': 26690, 'source': None, 'size': 3379}
- {'symbol': '_DropMyFood', 'offset': 30070, 'source': None, 'size': 1093}

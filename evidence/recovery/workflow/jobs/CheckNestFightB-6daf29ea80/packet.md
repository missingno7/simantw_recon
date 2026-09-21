# Recovery task _CheckNestFightB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 154 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 6]
0009 shl bx, 6
000c add bx, word ptr [bp + 8]
000f add bx, 0x88e8
0013 mov word ptr [bp - 2], bx
0016 mov si, word ptr [bx]
0018 and si, 0xff
001c push si
001d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 32, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0022 add sp, 2
0025 dec ax
0026 jne 0x3bec
0028 cmp word ptr [0xce98], 0 ; _MeColor
002d je 0x3bec
002f mov es, word ptr [0xc350]
0033 push word ptr es:[0x9b6a]
0038 push 2
003a nop 
003b push cs
003c call 0x823e ; _YellowFight
003f add sp, 4
0042 mov ax, 1
0045 pop si
0046 pop di
0047 leave 
0048 retf 
0049 nop 
004a cmp si, 0x87
004e jle 0x3c36
0050 cmp si, 0xe8
0054 jge 0x3c36
0056 push si
0057 push word ptr [bp + 8]
005a push word ptr [bp + 6]
005d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0062 add sp, 6
0065 mov di, ax
0067 or di, di
0069 jl 0x3c36
006b push word ptr [bp + 0xa]
006e push si
006f call 0x26f4 ; _GetWinner
0072 add sp, 4
0075 mov es, word ptr [0xc352]
0079 mov byte ptr es:[di + 0x3f0e], al
007e and al, 0x80
0080 add al, 0x70
0082 mov byte ptr es:[di + 0x3d18], al
0087 mov bx, word ptr [bp - 2]
008a mov byte ptr [bx], al
008c mov byte ptr es:[di + 0x3b22], 0xa
0092 jmp 0x3be4
0094 xor ax, ax
0096 pop si
0097 pop di
0098 leave 
0099 retf 
```

## Known declaration examples

- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_StartFightA-b2f3e31b2f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRecruitN', 'offset': 14700, 'source': None, 'size': 232}
- {'symbol': '_DoNestFightB', 'offset': 14932, 'source': None, 'size': 334}
- {'symbol': '_DropFoodB', 'offset': 15420, 'source': None, 'size': 100}
- {'symbol': '_SimEggB', 'offset': 15520, 'source': None, 'size': 290}

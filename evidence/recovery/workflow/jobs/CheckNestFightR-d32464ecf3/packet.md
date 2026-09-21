# Recovery task _CheckNestFightR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 160 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c mov bx, si
000e shl bx, 6
0011 add bx, di
0013 add bx, 0x98e8
0017 mov word ptr [bp - 6], bx
001a mov al, byte ptr [bx]
001c sub ah, ah
001e mov word ptr [bp - 2], ax
0021 cmp ax, 7
0024 jle 0x6212
0026 cmp ax, 0x68
0029 jge 0x6212
002b push ax
002c push di
002d push si
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0033 add sp, 6
0036 mov word ptr [bp - 4], ax
0039 or ax, ax
003b jl 0x623c
003d push word ptr [bp + 0xa]
0040 push word ptr [bp - 2]
0043 call 0x26f4 ; _GetWinner
0046 add sp, 4
0049 mov es, word ptr [0xc386]
004d mov bx, word ptr [bp - 4]
0050 mov byte ptr es:[bx + 0x48dc], al
0055 and al, 0x80
0057 add al, 0x70
0059 mov byte ptr es:[bx + 0x46e6], al
005e mov si, word ptr [bp - 6]
0061 mov byte ptr [si], al
0063 mov byte ptr es:[bx + 0x44f0], 0xa
0069 mov ax, 1
006c pop si
006d pop di
006e leave 
006f retf 
0070 push ax
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0076 add sp, 2
0079 or ax, ax
007b je 0x623c
007d cmp word ptr [0xce98], 0 ; _MeColor
0082 jne 0x623c
0084 mov es, word ptr [0xc384]
0088 push word ptr es:[0x9b6a]
008d push 3
008f nop 
0090 push cs
0091 call 0x823e ; _YellowFight
0094 add sp, 4
0097 jmp 0x620b
0099 nop 
009a xor ax, ax
009c pop si
009d pop di
009e leave 
009f retf 
```

## Known declaration examples

- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRandR', 'offset': 24442, 'source': None, 'size': 248}
- {'symbol': '_DoNestFightR', 'offset': 24690, 'source': None, 'size': 304}
- {'symbol': '_DropFoodR', 'offset': 25154, 'source': None, 'size': 100}
- {'symbol': '_SimEggR', 'offset': 25254, 'source': None, 'size': 223}

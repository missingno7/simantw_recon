# Recovery task _StartFightA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 137 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xc]
0009 mov es, word ptr [0xc318]
000d mov bx, word ptr [bp + 4]
0010 mov al, byte ptr es:[bx + 0x2f62]
0015 sub ah, ah
0017 mov word ptr [bp - 4], ax
001a xor al, al
001c mov byte ptr es:[bx + 0x2f62], al
0021 mov bx, word ptr [bp + 8]
0024 mov si, word ptr [bp + 6]
0027 shl si, 6
002a mov byte ptr [bx + si + 0x68e8], al
002e push di
002f push word ptr [bp + 0xa]
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
0037 add sp, 4
003a mov si, ax
003c or si, si
003e jl 0x26ef
0040 push word ptr [bp - 4]
0043 mov es, word ptr [0xc318]
0047 mov al, byte ptr es:[si + 0x2f62]
004c sub ah, ah
004e push ax
004f call 0x26f4 ; _GetWinner
0052 add sp, 4
0055 mov es, word ptr [0xc318]
0059 mov cx, ax
005b and al, 0x80
005d add al, 0x70
005f mov byte ptr es:[si + 0x2f62], al
0064 mov bx, word ptr [bp + 0xa]
0067 shl bx, 6
006a mov byte ptr [bx + di + 0x68e8], al
006e mov byte ptr es:[si + 0x2b78], 0xa
0074 mov byte ptr es:[si + 0x334c], cl
0079 push 0x28
007b push di
007c push word ptr [bp + 0xa]
007f call 0x947e ; _AlarmHere2
0082 add sp, 6
0085 pop si
0086 pop di
0087 leave 
0088 ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRecruitAnt', 'offset': 8872, 'source': None, 'size': 722}
- {'symbol': '_GoInNest', 'offset': 9594, 'source': None, 'size': 240}
- {'symbol': '_GetWinner', 'offset': 9972, 'source': None, 'size': 241}
- {'symbol': '_DoFightA', 'offset': 10214, 'source': None, 'size': 217}

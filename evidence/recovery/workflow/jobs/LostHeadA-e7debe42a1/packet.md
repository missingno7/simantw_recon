# Recovery task _LostHeadA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 87 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc31c]
0009 mov bl, byte ptr [bp + 8]
000c and bx, 7
000f mov al, byte ptr es:[bx + 8]
0014 cwde 
0015 mov si, ax
0017 add si, word ptr [bp + 6]
001a mov es, word ptr [0xc31e]
001e mov al, byte ptr es:[bx]
0023 cwde 
0024 mov di, ax
0026 add di, word ptr [bp + 4]
0029 mov bx, di
002b shl bx, 6
002e mov al, byte ptr [bx + si + 0x68e8]
0032 sub ah, ah
0034 sub ax, word ptr [bp + 8]
0037 cmp ax, 0xfff8
003a jne 0xb60
003c xor ax, ax
003e pop si
003f pop di
0040 leave 
0041 ret 
0042 push si
0043 push di
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
0049 add sp, 4
004c or ax, ax
004e jge 0xb5a
0050 mov ax, 1
0053 pop si
0054 pop di
0055 leave 
0056 ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimEggA', 'offset': 2588, 'source': None, 'size': 88}
- {'symbol': '_SimQueenA', 'offset': 2676, 'source': None, 'size': 169}
- {'symbol': '_DoRestAnt', 'offset': 2934, 'source': None, 'size': 168}
- {'symbol': '_DoRepoLoit', 'offset': 3102, 'source': None, 'size': 91}

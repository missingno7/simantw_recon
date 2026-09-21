# Recovery task _GetSmellT

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 106 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov cx, word ptr [bp + 8]
0008 mov es, word ptr [0xc472]
000c mov bx, cx
000e mov al, byte ptr es:[bx + 8]
0013 cwde 
0014 mov di, ax
0016 add di, word ptr [bp + 6]
0019 mov es, word ptr [0xc474]
001d mov al, byte ptr es:[bx]
0022 cwde 
0023 mov si, ax
0025 add si, word ptr [bp + 4]
0028 jns 0x9642
002a xor ax, ax
002c pop si
002d pop di
002e leave 
002f ret 
0030 cmp si, 0x3f
0033 jg 0x963c
0035 or di, di
0037 jl 0x963c
0039 cmp di, 0x1f
003c jg 0x963c
003e cmp word ptr [bp + 0xa], 0
0042 je 0x9668
0044 mov es, word ptr [0xc476]
0048 mov bx, si
004a shl bx, 5
004d add bx, di
004f mov al, byte ptr es:[bx + 0x7ad2]
0054 jmp 0x9676
0056 mov es, word ptr [0xc476]
005a shl si, 5
005d add si, di
005f mov al, byte ptr es:[si + 0x6ad2]
0064 sub ah, ah
0066 pop si
0067 pop di
0068 leave 
0069 ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_JamScentRT', 'offset': 38262, 'source': 'src/recovered/wf_JamScentRT-49b609e816.c', 'size': 63}
- {'symbol': '_DecTSmell', 'offset': 38326, 'source': None, 'size': 92}
- {'symbol': '_MakeRedInitiator', 'offset': 38524, 'source': None, 'size': 88}
- {'symbol': '_DoRedInitiator', 'offset': 38612, 'source': None, 'size': 619}

# Recovery task _GetMowDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 225 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 4], 3
000b mov <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000e mov es, ax
0010 mov bx, word ptr [bp - 4]
0013 mov al, byte ptr [bx + 0x25d4]
0017 cwde 
0018 mov si, ax
001a add si, word ptr [bp + 6]
001d mov al, byte ptr [bx + 0x25d8]
0021 cwde 
0022 mov di, ax
0024 add di, word ptr [bp + 8]
0027 or si, si
0029 jl 0x1f9a
002b or di, di
002d jl 0x1f9a
002f cmp si, 0xb
0032 jg 0x1f9a
0034 cmp di, 0xf
0037 jg 0x1f9a
0039 mov dx, 1
003c jmp 0x1f9c
003e xor dx, dx
0040 or dx, dx
0042 je 0x1fc4
0044 mov bx, si
0046 shl bx, 1
0048 mov cx, di
004a mov ax, 1
004d shl ax, cl
004f test word ptr es:[bx - 0x5f4a], ax
0054 je 0x1fbe
0056 shl si, 1
0058 sub word ptr es:[si - 0x5f4a], ax
005d mov bx, 1
0060 jmp 0x1fc0
0062 xor bx, bx
0064 or bx, bx
0066 jne 0x1fd6
0068 dec word ptr [bp - 4]
006b jns 0x1f6c
006d cmp word ptr [bp + 6], 0xa
0071 jle 0x1fde
0073 xor ax, ax
0075 pop si
0076 pop di
0077 leave 
0078 retf 
0079 nop 
007a mov ax, word ptr [bp - 4]
007d pop si
007e pop di
007f leave 
0080 retf 
0081 nop 
0082 mov dx, word ptr [bp + 8]
0085 cmp dx, 0xe
0088 jle 0x1fee
008a mov ax, 1
008d pop si
008e pop di
008f leave 
0090 retf 
0091 nop 
0092 cmp dx, 1
0095 jge 0x202e
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
009c add ax, 0x12c
009f adc dx, 0
00a2 mov es, word ptr [0xc4f6]
00a6 mov word ptr es:[0x7d4a], ax
00aa mov word ptr es:[0x7d4c], dx
00af mov es, word ptr [0xc504]
00b3 mov word ptr es:[0x99da], 1
00ba mov es, word ptr [0xc52a]
00be mov word ptr es:[0x72f2], 6
00c5 mov word ptr [0xac74], 4 ; _BoyHere
00cb mov ax, 2
00ce pop si
00cf pop di
00d0 leave 
00d1 retf 
00d2 mov es, word ptr [0xc52c]
00d6 mov al, byte ptr es:[0x7a5c]
00da and ax, 3
00dd pop si
00de pop di
00df leave 
00e0 retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimRain', 'offset': 5610, 'source': None, 'size': 177}
- {'symbol': '_SimKidOutside', 'offset': 5788, 'source': None, 'size': 2240}
- {'symbol': '_NotMowed', 'offset': 8254, 'source': None, 'size': 52}
- {'symbol': '_IsValidYard', 'offset': 8306, 'source': 'src/recovered/IsValidYard.c', 'size': 36}

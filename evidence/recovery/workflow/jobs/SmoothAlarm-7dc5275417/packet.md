# Recovery task _SmoothAlarm

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 187 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 xor di, di
0008 mov <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
000b mov ds, ax
000d xor si, si
000f mov word ptr [bp - 2], di
0012 mov bx, di
0014 add bx, si
0016 mov al, byte ptr [bx + 0x52d2]
001a mov byte ptr [bx + 0x4ad2], al
001e inc si
001f cmp si, 0x20
0022 jl 0x9392
0024 add di, 0x20
0027 cmp di, 0x800
002b jl 0x938d
002d xor di, di
002f mov dx, di
0031 xor si, si
0033 mov word ptr [bp - 6], dx
0036 xor cx, cx
0038 or di, di
003a jle 0x93c4
003c mov bx, di
003e add bx, si
0040 mov cl, byte ptr [bx + 0x4ab2]
0044 or si, si
0046 jle 0x93d4
0048 mov bx, si
004a add bx, di
004c mov al, byte ptr [bx + 0x4ad1]
0050 sub ah, ah
0052 add cx, ax
0054 cmp di, 0x7e0
0058 jge 0x93e6
005a mov bx, si
005c add bx, di
005e mov al, byte ptr [bx + 0x4af2]
0062 sub ah, ah
0064 add cx, ax
0066 cmp si, 0x1f
0069 jge 0x93f7
006b mov bx, si
006d add bx, di
006f mov al, byte ptr [bx + 0x4ad3]
0073 sub ah, ah
0075 add cx, ax
0077 mov bx, di
0079 add bx, si
007b mov al, byte ptr [bx + 0x4ad2]
007f sub ah, ah
0081 sar cx, 2
0084 add ax, cx
0086 sar ax, 1
0088 mov word ptr [bp - 2], ax
008b cmp ax, 8
008e jle 0x941a
0090 mov al, byte ptr [bp - 2]
0093 mov byte ptr [bx + 0x52d2], al
0097 jmp 0x941f
0099 nop 
009a mov byte ptr [bx + 0x52d2], 0
009f inc si
00a0 cmp si, 0x20
00a3 jl 0x93b6
00a5 mov dx, word ptr [bp - 6]
00a8 inc dx
00a9 add di, 0x20
00ac cmp di, 0x800
00b0 jge 0x9435
00b2 jmp 0x93b1
00b5 push ss
00b6 pop ds
00b7 pop si
00b8 pop di
00b9 leave 
00ba ret 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ColonySmellBT', 'offset': 37638, 'source': None, 'size': 62}
- {'symbol': '_ColonySmellRT', 'offset': 37700, 'source': None, 'size': 60}
- {'symbol': '_AlarmHere', 'offset': 37948, 'source': None, 'size': 65}
- {'symbol': '_AlarmHere2', 'offset': 38014, 'source': None, 'size': 56}

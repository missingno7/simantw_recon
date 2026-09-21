# Recovery task _GetExitDirR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 164 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 8], 1
000a jne 0x1270
000c mov bx, word ptr [bp + 6]
000f shl bx, 6
0012 cmp byte ptr [bx + 0x58e8], 0x18
0017 jne 0x1260
0019 mov ax, 1
001c pop si
001d pop di
001e leave 
001f retf 
0020 nop 
0021 push cs
0022 call 0x15ae ; _SRand2
0025 shl ax, 2
0028 add ax, 3
002b pop si
002c pop di
002d leave 
002e retf 
002f nop 
0030 mov ax, word ptr [bp + 0xa]
0033 xor al, 4
0035 mov word ptr [bp - 6], ax
0038 xor si, si
003a mov word ptr [bp - 8], si
003d mov word ptr [bp - 4], si
0040 mov <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0043 mov ds, ax
0045 mov al, byte ptr [si + 8]
0049 cwde 
004a mov di, ax
004c add di, word ptr [bp + 8]
004f mov <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0052 mov es, ax
0054 mov al, byte ptr es:[si]
0059 cwde 
005a mov cx, ax
005c add cx, word ptr [bp + 6]
005f js 0x12d5
0061 cmp cx, 0x3f
0064 jg 0x12d5
0066 or di, di
0068 jl 0x12d5
006a cmp di, 0x3f
006d jg 0x12d5
006f mov <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0072 mov es, ax
0074 mov bx, cx
0076 shl bx, 6
0079 add bx, di
007b mov al, byte ptr es:[bx + 0x13a4]
0080 sub ah, ah
0082 cmp ax, word ptr [bp - 4]
0085 jle 0x12d5
0087 cmp word ptr [bp - 6], si
008a je 0x12d5
008c mov word ptr [bp - 4], ax
008f lea ax, [si + 1]
0092 mov word ptr [bp - 8], ax
0095 inc si
0096 cmp si, 8
0099 jl 0x1285
009b push ss
009c pop ds
009d mov ax, word ptr [bp - 8]
00a0 pop si
00a1 pop di
00a2 leave 
00a3 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsItDirt', 'offset': 4482, 'source': 'src/recovered/wf_IsItDirt-30ab0b6cc4.c', 'size': 26}
- {'symbol': '_GetExitDirB', 'offset': 4508, 'source': 'src/recovered/wf_GetExitDirB-2bfd4e5303.c', 'size': 164}
- {'symbol': '_GetEnterDirB', 'offset': 4836, 'source': None, 'size': 152}
- {'symbol': '_GetEnterDirR', 'offset': 4988, 'source': None, 'size': 152}

# Recovery task _InitPillar

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 228 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 xor ax, ax
0008 mov <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
000b mov es, cx
000d mov word ptr es:[0x8a8a], ax
0011 mov <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0014 mov es, cx
0016 mov word ptr es:[0x8a8c], ax
001a mov <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001d mov es, cx
001f mov word ptr es:[0x8a8e], ax
0023 mov <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0026 mov es, cx
0028 mov word ptr es:[0x78d4], ax
002c mov <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002f mov es, cx
0031 mov word ptr es:[0x9b1e], ax
0035 mov <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0038 mov es, cx
003a mov cx, 6
003d mov di, 0x7c0e
0040 rep stosw word ptr es:[di], ax
0042 mov <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0045 mov es, ax
0047 cmp word ptr es:[0x9b6e], 0
004d je 0x4c4e
004f push ss
0050 pop ds
0051 pop si
0052 pop di
0053 leave 
0054 retf 
0055 nop 
0056 mov si, 4
0059 push ss
005a pop ds
005b push 0x80
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0063 add sp, 2
0066 mov di, ax
0068 push 0x40
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
006f add sp, 2
0072 mov bx, ax
0074 mov word ptr [bp - 2], bx
0077 mov ax, di
0079 shl ax, 6
007c add bx, ax
007e add bx, 0x28e8
0082 mov word ptr [bp - 4], bx
0085 cmp byte ptr [bx], 0x10
0088 jae 0x4cd1
008a mov es, word ptr [0xc574]
008e mov word ptr es:[si - 0x6438], di
0093 mov ax, word ptr [bp - 2]
0096 mov es, word ptr [0xc576]
009a mov word ptr es:[si - 0x6426], ax
009f push 8
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00a6 add sp, 2
00a9 mov es, word ptr [0xc578]
00ad mov word ptr es:[si - 0x63d6], ax
00b2 mov bx, word ptr [bp - 4]
00b5 mov al, byte ptr [bx]
00b7 sub ah, ah
00b9 mov es, word ptr [0xc57a]
00bd mov word ptr es:[si + 0x78cc], ax
00c2 mov es, word ptr [0xc578]
00c6 mov di, word ptr es:[si - 0x63d6]
00cb mov es, word ptr [0xc57c]
00cf mov al, byte ptr es:[di - 0x7570]
00d4 mov byte ptr [bx], al
00d6 sub si, 2
00d9 or si, si
00db je 0x4cd8
00dd jmp 0x4c53
00e0 pop si
00e1 pop di
00e2 leave 
00e3 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindInLionList', 'offset': 19218, 'source': None, 'size': 69}
- {'symbol': '_KillAntLion', 'offset': 19288, 'source': None, 'size': 160}
- {'symbol': '_DoPillar', 'offset': 19676, 'source': None, 'size': 1576}
- {'symbol': '_StorePillarMap', 'offset': 21252, 'source': 'src/recovered/wf_tu_simtwo_4CDC_StorePillarMap_4_scaffold-c16d27de40.c', 'size': 110}

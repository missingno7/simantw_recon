# Recovery task _DoFightA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 217 bytes.

```asm
0000 enter 0xa, 0
0004 push si
0005 mov si, word ptr [bp + 4]
0008 mov es, word ptr [0xc318]
000c mov al, byte ptr es:[si + 0x23a4]
0011 sub ah, ah
0013 mov word ptr [bp - 2], ax
0016 mov al, byte ptr es:[si + 0x278e]
001b mov word ptr [bp - 4], ax
001e push 7
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0025 add sp, 2
0028 mov bx, si
002a add bx, 0x2f62
002e mov es, word ptr [0xc318]
0032 mov word ptr [bp - 8], bx
0035 mov word ptr [bp - 6], es
0038 mov cl, byte ptr es:[bx]
003b and cl, 0xf8
003e add cl, al
0040 mov byte ptr es:[bx], cl
0043 mov al, cl
0045 mov bx, word ptr [bp - 2]
0048 shl bx, 6
004b add bx, word ptr [bp - 4]
004e add bx, 0x68e8
0052 mov word ptr [bp - 0xa], bx
0055 mov byte ptr [bx], al
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
005c or ax, ax
005e jne 0x28a0
0060 mov es, word ptr [0xc318]
0064 mov al, byte ptr es:[si + 0x334c]
0069 mov bx, word ptr [bp - 0xa]
006c mov byte ptr [bx], al
006e les bx, ptr [bp - 8]
0071 mov byte ptr es:[bx], al
0074 mov cx, ax
0076 sub ah, ah
0078 push ax
0079 and cl, 0x78
007c shr cl, 3
007f sub ch, ch
0081 push cx
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
0087 add sp, 4
008a mov es, word ptr [0xc316]
008e mov bx, word ptr es:[0x9b6a]
0093 mov es, word ptr [0xc318]
0097 mov byte ptr es:[bx + 0x2b78], al
009c mov byte ptr es:[si + 0x334c], 0
00a2 les bx, ptr [bp - 8]
00a5 mov al, byte ptr es:[bx]
00a8 and ax, 0x80
00ab push ax
00ac push word ptr [bp - 4]
00af push word ptr [bp - 2]
00b2 nop 
00b3 push cs
00b4 call 0x28c0 ; _DeadAntHere
00b7 jmp 0x28b9
00b9 nop 
00ba mov es, word ptr [0xc322]
00be cmp word ptr es:[0x85fc], 1
00c4 jne 0x28bc
00c6 push 1
00c8 push word ptr [bp - 4]
00cb push word ptr [bp - 2]
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _FightBalloons
00d3 add sp, 6
00d6 pop si
00d7 leave 
00d8 ret 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_StartFightA', 'offset': 9834, 'source': 'src/recovered/wf_StartFightA-b2f3e31b2f.c', 'size': 137}
- {'symbol': '_GetWinner', 'offset': 9972, 'source': None, 'size': 241}
- {'symbol': '_DeadAntHere', 'offset': 10432, 'source': None, 'size': 353}
- {'symbol': '_RandTurn', 'offset': 10786, 'source': 'src/recovered/RandTurn.c', 'size': 30}

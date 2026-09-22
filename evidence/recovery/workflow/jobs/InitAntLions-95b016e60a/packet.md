# Recovery task _InitAntLions

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 347 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 6]
0009 xor ax, ax
000b mov si, 0x8a88
000e mov es, word ptr [0xc582]
0012 mov word ptr [bp - 0x10], si
0015 mov word ptr [bp - 0xe], es
0018 mov word ptr es:[si], ax
001b mov es, word ptr [0xc584]
001f mov word ptr es:[0x9c6e], ax
0023 cmp bx, 0xa
0026 jle 0x40f1
0028 mov bx, 0xa
002b or bx, bx
002d jg 0x40f8
002f jmp 0x4214
0032 mov word ptr [bp - 0xa], bx
0035 mov word ptr [bp + 6], bx
0038 xor di, di
003a push 0x40
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0041 add sp, 2
0044 mov si, ax
0046 push 0x41
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004d add sp, 2
0050 add si, ax
0052 push 0x20
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0059 add sp, 2
005c push 0x21
005e mov word ptr [bp - 0x12], ax
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0066 add sp, 2
0069 add ax, word ptr [bp - 0x12]
006c mov word ptr [bp - 8], ax
006f push ax
0070 push si
0071 push 1
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClear3x3
0078 add sp, 6
007b dec ax
007c je 0x4164
007e push word ptr [bp - 8]
0081 push si
0082 push 1
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
0089 add sp, 6
008c dec ax
008d jne 0x415a
008f cmp di, 0x64
0092 jge 0x4164
0094 inc di
0095 cmp di, 0xc8
0099 jl 0x4100
009b jmp 0x4209
009e push 0x38
00a0 push word ptr [bp - 8]
00a3 push si
00a4 push 1
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
00ab add sp, 8
00ae xor di, di
00b0 mov es, word ptr [0xc57e]
00b4 mov al, byte ptr es:[di + 8]
00b9 cwde 
00ba add ax, word ptr [bp - 8]
00bd mov word ptr [bp - 2], ax
00c0 push ax
00c1 mov es, word ptr [0xc580]
00c5 mov al, byte ptr es:[di]
00ca cwde 
00cb add ax, si
00cd mov word ptr [bp - 4], ax
00d0 push ax
00d1 push 1
00d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
00d8 add sp, 6
00db dec ax
00dc jne 0x41be
00de mov al, byte ptr [di + 0x25e8]
00e2 sub ah, ah
00e4 add ax, 0x30
00e7 push ax
00e8 push word ptr [bp - 2]
00eb push word ptr [bp - 4]
00ee push 1
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
00f5 add sp, 8
00f8 inc di
00f9 cmp di, 8
00fc jl 0x4176
00fe mov ax, si
0100 les bx, ptr [bp - 0x10]
0103 mov bx, word ptr es:[bx]
0106 mov es, word ptr [0xc586]
010a mov byte ptr es:[bx - 0x7f64], al
010f mov es, word ptr [0xc588]
0113 mov al, byte ptr [bp - 8]
0116 mov byte ptr es:[bx - 0x7f44], al
011b mov es, word ptr [0xc58a]
011f xor al, al
0121 mov byte ptr es:[bx + 0x7a68], al
0126 mov es, word ptr [0xc58c]
012a mov byte ptr es:[bx + 0x7d34], al
012f mov es, word ptr [0xc58e]
0133 mov byte ptr es:[bx + 0x7d4e], al
0138 cmp bx, 9
013b jge 0x4209
013d les bx, ptr [bp - 0x10]
0140 inc word ptr es:[bx]
0143 dec word ptr [bp - 0xa]
0146 je 0x4211
0148 jmp 0x40fe
014b mov bx, word ptr [bp + 6]
014e mov es, word ptr [0xc590]
0152 mov word ptr es:[0x9e8c], bx
0157 pop si
0158 pop di
0159 leave 
015a retf 
```

## Known declaration examples

- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_tu_simtwo_3EF8_AddAntLion_2_scaffold-16d1d1e00e.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far SetMap(int plane, int x, int y, int value);` — src/recovered/wf_tu_simtwo_3EF8_AddAntLion_2_scaffold-16d1d1e00e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitSow', 'offset': 16120, 'source': None, 'size': 146}
- {'symbol': '_DoSow', 'offset': 16266, 'source': None, 'size': 315}
- {'symbol': '_AddRandAntLion', 'offset': 16930, 'source': None, 'size': 285}
- {'symbol': '_AddAntLion', 'offset': 17216, 'source': 'src/recovered/wf_tu_simtwo_3EF8_AddAntLion_2_scaffold-16d1d1e00e.c', 'size': 186}

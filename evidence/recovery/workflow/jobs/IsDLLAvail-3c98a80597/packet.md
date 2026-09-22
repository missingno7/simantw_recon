# Recovery task _IsDLLAvail

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 300 bytes.

```asm
0000 enter 0x100, 0
0004 push di
0005 push si
0006 lea ax, [bp - 0x100]
000a push ss
000b push ax
000c push 0x100
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 134}}]
0014 lea di, [bp - 0x100]
0018 mov ax, ss
001a mov es, ax
001c mov cx, 0xffff
001f xor ax, ax
0021 repne scasb al, byte ptr es:[di]
0023 not cx
0025 dec cx
0026 mov si, cx
0028 cmp byte ptr [bp + si - 0x101], 0x5c
002d je 0x784c
002f lea ax, [bp - 0x100]
0033 push ss
0034 push ax
0035 push ds
0036 push 0xb54
0039 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
003e lea ax, [bp - 0x100]
0042 push ss
0043 push ax
0044 push word ptr [bp + 8]
0047 push word ptr [bp + 6]
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
004f push 0
0051 lea ax, [bp - 0x100]
0055 push ss
0056 push ax
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
005c add sp, 6
005f or ax, ax
0061 jne 0x7878
0063 mov ax, 1
0066 pop si
0067 pop di
0068 leave 
0069 retf 
006a lea ax, [bp - 0x100]
006e push ss
006f push ax
0070 push 0x100
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 135}}]
0078 lea di, [bp - 0x100]
007c mov ax, ss
007e mov es, ax
0080 mov cx, 0xffff
0083 xor ax, ax
0085 repne scasb al, byte ptr es:[di]
0087 not cx
0089 dec cx
008a mov si, cx
008c cmp byte ptr [bp + si - 0x101], 0x5c
0091 je 0x78b0
0093 lea ax, [bp - 0x100]
0097 push ss
0098 push ax
0099 push ds
009a push 0xb56
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
00a2 mov si, word ptr [bp + 6]
00a5 lea ax, [bp - 0x100]
00a9 push ss
00aa push ax
00ab push word ptr [bp + 8]
00ae push si
00af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
00b4 push 0
00b6 lea ax, [bp - 0x100]
00ba push ss
00bb push ax
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
00c1 add sp, 6
00c4 or ax, ax
00c6 je 0x7871
00c8 push word ptr [0xcc7c] ; _hInst
00cc lea ax, [bp - 0x100]
00d0 push ss
00d1 push ax
00d2 push 0x100
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 49}}]
00da push 0x5c
00dc lea ax, [bp - 0x100]
00e0 push ss
00e1 push ax
00e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 229, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
00e7 add sp, 6
00ea mov es, dx
00ec mov bx, ax
00ee mov byte ptr es:[bx], 0
00f2 lea ax, [bp - 0x100]
00f6 push ss
00f7 push ax
00f8 push ds
00f9 push 0xb58
00fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 253, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
0101 lea ax, [bp - 0x100]
0105 push ss
0106 push ax
0107 mov ax, word ptr [bp + 8]
010a push ax
010b push si
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 269, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
0111 push 0
0113 lea ax, [bp - 0x100]
0117 push ss
0118 push ax
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 284, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
011e add sp, 6
0121 cmp ax, 1
0124 sbb ax, ax
0126 neg ax
0128 pop si
0129 pop di
012a leave 
012b retf 
```

## Known declaration examples

- `extern int far access(char far *path, int mode);` — src/recovered/db_Exists.c
- `extern int near hInst;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern char far * far strrchr(const char far *text, int character);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsMMWaveAvail', 'offset': 30524, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_11_scaffold-950e5ffcca.c', 'size': 42}
- {'symbol': '_CheckMMWave', 'offset': 30566, 'source': None, 'size': 168}
- {'symbol': '_snd_Install', 'offset': 31034, 'source': None, 'size': 804}
- {'symbol': '_snd_Deinstall', 'offset': 31838, 'source': None, 'size': 608}

# Recovery task _CheckMMWave

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 168 bytes.

```asm
0000 enter 0x104, 0
0004 push di
0005 push si
0006 lea ax, [bp - 0x104]
000a push ss
000b push ax
000c push 0x100
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 134}}]
0014 lea di, [bp - 0x104]
0018 mov ax, ss
001a mov es, ax
001c mov cx, 0xffff
001f xor ax, ax
0021 repne scasb al, byte ptr es:[di]
0023 not cx
0025 dec cx
0026 mov si, cx
0028 cmp byte ptr [bp + si - 0x105], 0x5c
002d jne 0x77a2
002f lea ax, [bp - 0x104]
0033 push ss
0034 push ax
0035 push ds
0036 push 0xb1e
0039 jmp 0x77ac
003b nop 
003c lea ax, [bp - 0x104]
0040 push ss
0041 push ax
0042 push ds
0043 push 0xb32
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
004b push 0
004d lea ax, [bp - 0x104]
0051 push ss
0052 push ax
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
0058 add sp, 6
005b or ax, ax
005d jne 0x7808
005f push ds
0060 push 0xb47
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 95}}]
0068 mov es, word ptr [0xbf78]
006c mov word ptr es:[0x8d08], ax
0070 cmp ax, 0x20
0073 jb 0x7808
0075 push ax
0076 push ds
0077 push 0xb0c
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
007f mov word ptr [bp - 4], ax
0082 mov word ptr [bp - 2], dx
0085 or dx, ax
0087 je 0x77f6
0089 lcall [bp - 4]
008c mov si, ax
008e jmp 0x77f8
0090 xor si, si
0092 or si, si
0094 je 0x7808
0096 mov es, word ptr [0xbf78]
009a mov ax, word ptr es:[0x8d08]
009e pop si
009f pop di
00a0 leave 
00a1 retf 
00a2 xor ax, ax
00a4 pop si
00a5 pop di
00a6 leave 
00a7 retf 
```

## Known declaration examples

- `extern int far access(char far *path, int mode);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsMMMidiAvail', 'offset': 30482, 'source': 'src/recovered/wf_IsMMMidiAvail-25316c8456.c', 'size': 42}
- {'symbol': '_IsMMWaveAvail', 'offset': 30524, 'source': 'src/recovered/wf_IsMMWaveAvail-6cf4f4e231.c', 'size': 42}
- {'symbol': '_IsDLLAvail', 'offset': 30734, 'source': None, 'size': 300}
- {'symbol': '_snd_Install', 'offset': 31034, 'source': None, 'size': 804}

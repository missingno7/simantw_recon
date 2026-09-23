# Recovery task _ReadConfig

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 548 bytes.

```asm
0000 enter 0x2a, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc6ae]
000a push word ptr es:[0x8b38]
000f push word ptr es:[0x8b36]
0014 push 0
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 85}}]
001b mov word ptr [bp - 0xa], ax
001e or ax, ax
0020 jg 0x92c
0022 mov es, word ptr [0xc6b0]
0026 mov ax, word ptr es:[0x8b32]
002a mov dx, word ptr es:[0x8b34]
002f mov cx, ax
0031 mov word ptr [bp - 6], dx
0034 jmp 0xa79
0037 nop 
0038 mov word ptr [bp - 0xc], 2
003d jmp 0x9a1
003f nop 
0040 lea ax, [bp - 0x2a]
0043 mov si, ax
0045 mov word ptr [bp - 6], ss
0048 mov word ptr [bp - 8], si
004b push 1
004d lea ax, [bp - 1]
0050 push ss
0051 push ax
0052 push word ptr [bp - 0xa]
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
005a add sp, 8
005d or ax, ax
005f je 0x966
0061 mov al, byte ptr [bp - 1]
0064 cwde 
0065 push ax
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
006b add sp, 2
006e or ax, ax
0070 jne 0x93f
0072 mov di, word ptr [bp - 0xa]
0075 mov al, byte ptr [bp - 1]
0078 mov es, word ptr [bp - 6]
007b mov bx, si
007d inc si
007e mov byte ptr es:[bx], al
0081 push 1
0083 lea ax, [bp - 1]
0086 push ss
0087 push ax
0088 push di
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
008e add sp, 8
0091 or ax, ax
0093 je 0x99a
0095 mov al, byte ptr [bp - 1]
0098 cwde 
0099 push ax
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
009f add sp, 2
00a2 or ax, ax
00a4 je 0x969
00a6 mov es, word ptr [bp - 6]
00a9 mov byte ptr es:[si], 0
00ad mov ax, word ptr [bp - 0xc]
00b0 dec word ptr [bp - 0xc]
00b3 or ax, ax
00b5 jne 0x934
00b7 push word ptr [bp - 0xa]
00ba lea ax, [bp - 3]
00bd push ss
00be push ax
00bf push 1
00c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
00c6 mov word ptr [bp - 0xc], 2
00cb jmp 0xa2f
00cd nop 
00ce lea ax, [bp - 0x2a]
00d1 mov si, ax
00d3 mov word ptr [bp - 6], ss
00d6 mov word ptr [bp - 8], si
00d9 push 1
00db lea ax, [bp - 1]
00de push ss
00df push ax
00e0 push word ptr [bp - 0xa]
00e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 230, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
00e8 add sp, 8
00eb or ax, ax
00ed je 0x9f4
00ef mov al, byte ptr [bp - 1]
00f2 cwde 
00f3 push ax
00f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
00f9 add sp, 2
00fc or ax, ax
00fe jne 0x9cd
0100 mov di, word ptr [bp - 0xa]
0103 mov al, byte ptr [bp - 1]
0106 mov es, word ptr [bp - 6]
0109 mov bx, si
010b inc si
010c mov byte ptr es:[bx], al
010f push 1
0111 lea ax, [bp - 1]
0114 push ss
0115 push ax
0116 push di
0117 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
011c add sp, 8
011f or ax, ax
0121 je 0xa28
0123 mov al, byte ptr [bp - 1]
0126 cwde 
0127 push ax
0128 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 299, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isspace
012d add sp, 2
0130 or ax, ax
0132 je 0x9f7
0134 mov es, word ptr [bp - 6]
0137 mov byte ptr es:[si], 0
013b mov ax, word ptr [bp - 0xc]
013e dec word ptr [bp - 0xc]
0141 or ax, ax
0143 jne 0x9c2
0145 mov di, word ptr [bp - 0xa]
0148 push di
0149 lea ax, [bp - 2]
014c push ss
014d push ax
014e push 1
0150 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 337, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
0155 push di
0156 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
015b mov al, byte ptr [bp - 3]
015e cwde 
015f cmp ax, 0x77
0162 jne 0xa5b
0164 jmp 0xaf4
0167 ja 0xa73
0169 cmp al, 0x54
016b je 0xacc
016d jg 0xa9a
016f sub al, 0x3f
0171 je 0xaac
0173 sub al, 6
0175 je 0xab4
0177 sub al, 3
0179 je 0xabc
017b sub al, 5
017d je 0xac4
017f mov cx, 0xb9d6
0182 mov word ptr [bp - 6], ds
0185 push word ptr [0xcd78] ; _rootWnd
0189 push word ptr [bp - 6]
018c push cx
018d push ds
018e push 0xb9ff
0191 push 0x30
0193 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0198 push 1
019a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 413, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _exit
019f add sp, 2
01a2 jmp 0xaf9
01a4 nop 
01a5 nop 
01a6 sub al, 0x56
01a8 je 0xad4
01aa dec al
01ac je 0xadc
01ae sub al, 0xe
01b0 je 0xae4
01b2 sub al, 8
01b4 je 0xaec
01b6 jmp 0xa73
01b8 mov byte ptr [0xcc7e], 0xff ; _displayType
01bd jmp 0xaf9
01bf nop 
01c0 mov byte ptr [0xcc7e], 0 ; _displayType
01c5 jmp 0xaf9
01c7 nop 
01c8 mov byte ptr [0xcc7e], 3 ; _displayType
01cd jmp 0xaf9
01cf nop 
01d0 mov byte ptr [0xcc7e], 5 ; _displayType
01d5 jmp 0xaf9
01d7 nop 
01d8 mov byte ptr [0xcc7e], 2 ; _displayType
01dd jmp 0xaf9
01df nop 
01e0 mov byte ptr [0xcc7e], 8 ; _displayType
01e5 jmp 0xaf9
01e7 nop 
01e8 mov byte ptr [0xcc7e], 0xa ; _displayType
01ed jmp 0xaf9
01ef nop 
01f0 mov byte ptr [0xcc7e], 4 ; _displayType
01f5 jmp 0xaf9
01f7 nop 
01f8 mov byte ptr [0xcc7e], 7 ; _displayType
01fd jmp 0xaf9
01ff nop 
0200 mov byte ptr [0xcc7e], 9 ; _displayType
0205 mov al, byte ptr [bp - 2]
0208 cwde 
0209 push ax
020a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 525, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _isdigit
020f add sp, 2
0212 or ax, ax
0214 je 0xb14
0216 mov al, byte ptr [bp - 2]
0219 cwde 
021a sub ax, 0x30
021d mov word ptr [0xb91c], ax ; _musicDevice
0220 pop si
0221 pop di
0222 leave 
0223 retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far exit(int status);` — src/recovered/wf_Punt-840c7657cd.c
- `extern int far isspace(int character);` — src/recovered/wf_ReadWord-e51efa9f2b.c
- `extern int far isspace(int character);` — src/recovered/wf_SkipWords-f10e7d71fd.c
- `extern int far read(int fd, void far *buffer, unsigned int count);` — src/recovered/wf_ReadWord-e51efa9f2b.c
- `extern int far read(int fd, void far *buffer, unsigned int count);` — src/recovered/wf_SkipWords-f10e7d71fd.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ReadWord', 'offset': 2052, 'source': 'src/recovered/wf_ReadWord-e51efa9f2b.c', 'size': 109}
- {'symbol': '_SkipWords', 'offset': 2162, 'source': 'src/recovered/wf_SkipWords-f10e7d71fd.c', 'size': 130}
- {'symbol': '_GBoxFillOutline', 'offset': 2840, 'source': 'src/recovered/wf_GBoxFillOutline-d99ffce56d.c', 'size': 164}
- {'symbol': '_GTextBox', 'offset': 3004, 'source': 'src/recovered/GTextBox.c', 'size': 35}

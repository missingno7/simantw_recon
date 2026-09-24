# Recovery task _FileSelect

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 970 bytes.

```asm
0000 enter 0x3e2, 0
0004 push di
0005 push si
0006 push ds
0007 push 0x16fd
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _IsDLLAvail
000f add sp, 4
0012 or ax, ax
0014 jne 0x9939
0016 jmp 0x9a3c
0019 push ds
001a push 0x1709
001d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 95}}]
0022 mov word ptr [bp - 6], ax
0025 cmp ax, 0x20
0028 jae 0x994d
002a jmp 0x9a3c
002d mov bx, word ptr [bp + 6]
0030 mov es, word ptr [bp + 8]
0033 xor ax, ax
0035 mov byte ptr es:[bx], al
0038 mov cx, 0x48
003b push es
003c lea di, [bp - 0xde]
0040 push ss
0041 pop es
0042 rep stosb byte ptr es:[di], al
0044 pop es
0045 mov word ptr [bp - 0xde], 0x48
004b mov word ptr [bp - 0xdc], ax
004f mov ax, word ptr [0xcd78] ; _rootWnd
0052 mov word ptr [bp - 0xda], ax
0056 mov word ptr [bp - 0xd6], 0x1715
005c mov word ptr [bp - 0xd4], ds
0060 mov word ptr [bp - 0xca], 1
0066 mov word ptr [bp - 0xc8], 0
006c mov word ptr [bp - 0xc6], bx
0070 mov word ptr [bp - 0xc4], es
0074 mov word ptr [bp - 0xc2], 0x100
007a mov word ptr [bp - 0xc0], 0
0080 mov word ptr [bp - 0xa6], 0x1731
0086 mov word ptr [bp - 0xa4], ds
008a cmp word ptr [bp + 0xa], 0
008e jne 0x99f6
0090 push word ptr [bp - 6]
0093 push ds
0094 push 0x1735
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
009c mov word ptr [bp - 4], ax
009f mov word ptr [bp - 2], dx
00a2 mov word ptr [bp - 0xae], 0x1800
00a8 mov word ptr [bp - 0xac], 0
00ae mov word ptr [bp - 0xb2], 0x1745
00b4 mov word ptr [bp - 0xb0], ds
00b8 mov ax, dx
00ba or ax, word ptr [bp - 4]
00bd jne 0x99e2
00bf jmp 0x9ce4
00c2 lea ax, [bp - 0xde]
00c6 push ss
00c7 push ax
00c8 lcall [bp - 4]
00cb or ax, ax
00cd jne 0x99f2
00cf jmp 0x9ce4
00d2 jmp 0x9cdc
00d5 nop 
00d6 push word ptr [bp - 6]
00d9 push ds
00da push 0x1753
00dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00e2 mov word ptr [bp - 4], ax
00e5 mov word ptr [bp - 2], dx
00e8 mov word ptr [bp - 0xae], 0x802
00ee mov word ptr [bp - 0xac], 0
00f4 mov word ptr [bp - 0xb2], 0x1763
00fa mov word ptr [bp - 0xb0], ds
00fe mov ax, dx
0100 or ax, word ptr [bp - 4]
0103 jne 0x9a28
0105 jmp 0x9ce4
0108 lea ax, [bp - 0xde]
010c push ss
010d push ax
010e lcall [bp - 4]
0111 or ax, ax
0113 je 0x9a38
0115 jmp 0x9cdc
0118 jmp 0x9ce4
011b nop 
011c mov es, word ptr [0xc170]
0120 mov byte ptr es:[0x94a0], 0
0126 cmp word ptr [bp + 0xa], 0
012a jne 0x9a74
012c mov di, 0x9f10
012f mov si, 0x1774
0132 movsw word ptr es:[di], word ptr [si]
0133 movsw word ptr es:[di], word ptr [si]
0134 movsw word ptr es:[di], word ptr [si]
0135 push <resolved loader operand; see bindings> ; [{'operand_offset': 310, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0138 push 0x9248
013b push word ptr [0xcc7c] ; _hInst
013f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 51}}]
0144 mov word ptr [bp - 4], ax
0147 mov word ptr [bp - 2], dx
014a push word ptr [0xcc7c] ; _hInst
014e push ds
014f push 0x177a
0152 jmp 0x9a9a
0154 mov di, 0x9f10
0157 mov si, 0x177f
015a movsw word ptr es:[di], word ptr [si]
015b movsw word ptr es:[di], word ptr [si]
015c movsw word ptr es:[di], word ptr [si]
015d push <resolved loader operand; see bindings> ; [{'operand_offset': 350, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0160 push 0x94e4
0163 push word ptr [0xcc7c] ; _hInst
0167 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 360, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 51}}]
016c mov word ptr [bp - 4], ax
016f mov word ptr [bp - 2], dx
0172 push word ptr [0xcc7c] ; _hInst
0176 push ds
0177 push 0x1785
017a push word ptr [0xcd78] ; _rootWnd
017e push dx
017f push ax
0180 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 385, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 87}}]
0185 mov word ptr [bp - 6], ax
0188 push word ptr [bp - 2]
018b push word ptr [bp - 4]
018e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 399, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 52}}]
0193 push word ptr [0xcd78] ; _rootWnd
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 408, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 22}}]
019c cmp word ptr [bp - 6], 0
01a0 jne 0x9ac5
01a2 jmp 0x9ce4
01a5 push 0x100
01a8 lea ax, [bp - 0x1de]
01ac push ss
01ad push ax
01ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 433, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _getcwd
01b3 add sp, 6
01b6 mov bx, 0x93a0
01b9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 442, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01bc mov word ptr [bp - 0x3e2], bx
01c0 mov word ptr [bp - 0x3e0], ax
01c4 mov dx, ax
01c6 mov di, bx
01c8 lea si, [bp - 0x2de]
01cc mov es, ax
01ce push ds
01cf mov cx, 0xffff
01d2 xor ax, ax
01d4 repne scasb al, byte ptr es:[di]
01d6 not cx
01d8 sub di, cx
01da xchg si, di
01dc push ds
01dd push es
01de pop ds
01df pop es
01e0 shr cx, 1
01e2 rep movsw word ptr es:[di], word ptr [si]
01e4 adc cx, cx
01e6 rep movsb byte ptr es:[di], byte ptr [si]
01e8 pop ds
01e9 mov word ptr [bp - 4], bx
01ec mov word ptr [bp - 2], dx
01ef mov es, dx
01f1 cmp byte ptr es:[bx], al
01f4 je 0x9b3e
01f6 mov si, bx
01f8 mov ds, dx
01fa mov al, byte ptr [si]
01fc cwde 
01fd mov bx, ax
01ff test byte ptr ss:[bx - 0x52cd], 7
0205 jne 0x9b36
0207 cmp al, 0x2e
0209 je 0x9b36
020b cmp al, 0x3a
020d je 0x9b36
020f cmp al, 0x5c
0211 je 0x9b36
0213 mov byte ptr [si], 0x5f
0216 inc si
0217 cmp byte ptr [si], 0
021a jne 0x9b1a
021c push ss
021d pop ds
021e push 0x2e
0220 push word ptr [bp - 0x3e0]
0224 push word ptr [bp - 0x3e2]
0228 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 555, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
022d add sp, 6
0230 mov si, ax
0232 mov word ptr [bp - 6], dx
0235 or dx, ax
0237 jne 0x9b74
0239 lea di, [bp - 0x10]
023c mov si, 0x178c
023f mov ax, ss
0241 mov es, ax
0243 movsw word ptr es:[di], word ptr [si]
0244 movsw word ptr es:[di], word ptr [si]
0245 movsb byte ptr es:[di], byte ptr [si]
0246 mov es, word ptr [0xc170]
024a mov byte ptr es:[0x93a8], 0
0250 jmp 0x9c12
0253 nop 
0254 mov byte ptr [bp - 0x10], 0
0258 les di, ptr [bp - 0x3e2]
025c mov cx, 0xffff
025f xor ax, ax
0261 repne scasb al, byte ptr es:[di]
0263 not cx
0265 dec cx
0266 cmp cx, 0xc
0269 ja 0x9b8e
026b jmp 0x9c12
026e push 8
0270 push es
0271 push word ptr [bp - 0x3e2]
0275 lea ax, [bp - 0x20]
0278 push ss
0279 push ax
027a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 637, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strncpy
027f add sp, 0xa
0282 mov byte ptr [bp - 0x18], 0
0286 push 0x2e
0288 lea ax, [bp - 0x20]
028b push ss
028c push ax
028d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 656, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
0292 add sp, 6
0295 mov di, ax
0297 mov word ptr [bp - 2], dx
029a or dx, ax
029c jne 0x9be4
029e mov byte ptr [bp - 0x18], 0
02a2 mov byte ptr [bp - 0x10], 0x2e
02a6 mov es, word ptr [bp - 6]
02a9 mov al, byte ptr es:[si + 1]
02ad mov byte ptr [bp - 0xf], al
02b0 mov al, byte ptr es:[si + 2]
02b4 mov byte ptr [bp - 0xe], al
02b7 mov al, byte ptr es:[si + 3]
02bb mov byte ptr [bp - 0xd], al
02be mov byte ptr [bp - 0xc], 0
02c2 jmp 0x9bec
02c4 mov es, word ptr [bp - 2]
02c7 mov byte ptr es:[di + 4], 0
02cc lea di, [bp - 0x20]
02cf mov cx, ss
02d1 mov es, cx
02d3 push ds
02d4 lds si, ptr [bp - 0x3e2]
02d8 mov cx, 0xffff
02db xor ax, ax
02dd repne scasb al, byte ptr es:[di]
02df not cx
02e1 sub di, cx
02e3 xchg si, di
02e5 push ds
02e6 push es
02e7 pop ds
02e8 pop es
02e9 shr cx, 1
02eb rep movsw word ptr es:[di], word ptr [si]
02ed adc cx, cx
02ef rep movsb byte ptr es:[di], byte ptr [si]
02f1 pop ds
02f2 lea di, [bp - 0x1de]
02f6 mov ax, ss
02f8 mov es, ax
02fa mov cx, 0xffff
02fd xor ax, ax
02ff repne scasb al, byte ptr es:[di]
0301 not cx
0303 dec cx
0304 mov si, cx
0306 cmp byte ptr [bp + si - 0x1df], 0x5c
030b jne 0x9c4a
030d mov si, word ptr [bp + 6]
0310 lea ax, [bp - 0x10]
0313 push ss
0314 push ax
0315 push word ptr [bp - 0x3e0]
0319 push word ptr [bp - 0x3e2]
031d lea ax, [bp - 0x1de]
0321 push ss
0322 push ax
0323 push ds
0324 push 0x1791
0327 jmp 0x9c64
0329 nop 
032a mov si, word ptr [bp + 6]
032d lea ax, [bp - 0x10]
0330 push ss
0331 push ax
0332 push word ptr [bp - 0x3e0]
0336 push word ptr [bp - 0x3e2]
033a lea ax, [bp - 0x1de]
033e push ss
033f push ax
0340 push ds
0341 push 0x1798
0344 push word ptr [bp + 8]
0347 push si
0348 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 843, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
034d add sp, 0x14
0350 cmp word ptr [bp + 0xa], 1
0354 jne 0x9cdc
0356 push 0
0358 mov ax, word ptr [bp + 8]
035b push ax
035c push si
035d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 864, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
0362 add sp, 6
0365 or ax, ax
0367 jne 0x9cdc
0369 push 0x2e
036b lea ax, [bp - 0x2de]
036f push ss
0370 push ax
0371 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 884, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
0376 add sp, 6
0379 or dx, ax
037b jne 0x9caa
037d lea ax, [bp - 0x2de]
0381 push ss
0382 push ax
0383 push ds
0384 push 0x17a0
0387 jmp 0x9cb4
0389 nop 
038a lea ax, [bp - 0x2de]
038e push ss
038f push ax
0390 push ds
0391 push 0x17b9
0394 lea ax, [bp - 0x3de]
0398 push ss
0399 push ax
039a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 925, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
039f add sp, 0xc
03a2 push word ptr [0xcd78] ; _rootWnd
03a6 lea ax, [bp - 0x3de]
03aa push ss
03ab push ax
03ac push ds
03ad push 0x17ce
03b0 push 0x23
03b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 947, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
03b7 cmp ax, 6
03ba jne 0x9ce4
03bc mov ax, 1
03bf pop si
03c0 pop di
03c1 leave 
03c2 retf 
03c3 nop 
03c4 xor ax, ax
03c6 pop si
03c7 pop di
03c8 leave 
03c9 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far access(char far *path, int mode);` — src/recovered/db_Exists.c
- `extern int far access(const char far *path, int mode);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern int far access(char far *path, int mode);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c
- `extern int near hInst;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': 'OPENDLG', 'offset': 37448, 'source': None, 'size': 667}
- {'symbol': 'SAVEASDLG', 'offset': 38116, 'source': None, 'size': 1083}
- {'symbol': '_SpecialTutorialInit', 'offset': 40170, 'source': 'src/recovered/wf_SpecialTutorialInit-e0cff25916.c', 'size': 153}
- {'symbol': '_DoPreLoadInits', 'offset': 40324, 'source': 'src/recovered/wf_DoPreLoadInits-ed37124107.c', 'size': 58}

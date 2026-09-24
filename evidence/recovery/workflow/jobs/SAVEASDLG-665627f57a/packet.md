# Recovery task SAVEASDLG

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 1083 bytes.

```asm
0000 mov ax, ss
0002 enter 0x212, 0
0006 push di
0007 push si
0008 push ds
0009 mov ds, ax
000b mov ax, word ptr [bp + 0xc]
000e sub ax, 0x110
0011 je 0x94fe
0013 dec ax
0014 je 0x9540
0016 jmp 0x9916
0019 nop 
001a mov si, word ptr [bp + 0xe]
001d push 0xc010
0020 push si
0021 nop 
0022 push cs
0023 call 0x8e56 ; _UpdateListBox
0026 add sp, 4
0029 push si
002a push 0x191
002d push <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0030 push 0x9f10
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 92}}]
0038 push si
0039 push 0x191
003c push 0x401
003f push 0
0041 push 1
0043 push 0
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
004a push si
004b push 0x191
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 91}}]
0053 push ax
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 22}}]
0059 jmp 0x9916
005c mov ax, word ptr [bp + 0xa]
005f dec ax
0060 je 0x9558
0062 dec ax
0063 jne 0x954c
0065 jmp 0x970c
0068 sub ax, 0x192
006b jne 0x9554
006d jmp 0x971a
0070 jmp 0x9916
0073 nop 
0074 mov di, word ptr [bp + 0xe]
0077 push di
0078 push 0x191
007b mov ax, 0x93a0
007e mov <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0081 mov word ptr [bp - 0x20a], ax
0085 mov word ptr [bp - 0x208], cx
0089 push cx
008a push ax
008b push 0x80
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 93}}]
0093 mov es, word ptr [0xc170]
0097 mov byte ptr es:[0x941f], 0
009d push 0x2a
009f push word ptr [bp - 0x208]
00a3 push word ptr [bp - 0x20a]
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
00ac add sp, 6
00af or dx, ax
00b1 jne 0x95ce
00b3 push 0x3f
00b5 push word ptr [bp - 0x208]
00b9 push word ptr [bp - 0x20a]
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 192, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
00c2 add sp, 6
00c5 or dx, ax
00c7 jne 0x95ce
00c9 push di
00ca push 0x194
00cd push 0x409
00d0 push 0
00d2 push 0
00d4 push 0
00d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 215, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
00db cmp ax, 0xffff
00de jne 0x95ce
00e0 cmp dx, ax
00e2 jne 0x95ce
00e4 xor si, si
00e6 jmp 0x96d3
00e9 nop 
00ea push word ptr [bp - 0x208]
00ee push word ptr [bp - 0x20a]
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
00f7 mov bx, ax
00f9 add bx, 0x93a0
00fd mov es, word ptr [0xc170]
0101 mov si, bx
0103 mov word ptr [bp - 4], es
0106 cmp byte ptr es:[bx], 0x3a
010a je 0x961b
010c cmp byte ptr es:[si], 0x5c
0110 je 0x961b
0112 mov ax, si
0114 cmp ax, 0x93a0
0117 jbe 0x961b
0119 push word ptr [bp - 0x208]
011d push word ptr [bp - 0x20a]
0121 push es
0122 push si
0123 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 292, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 473}}]
0128 mov es, dx
012a mov bx, ax
012c mov si, ax
012e mov word ptr [bp - 4], es
0131 cmp byte ptr es:[bx], 0x3a
0135 jne 0x95f0
0137 mov es, word ptr [bp - 4]
013a cmp byte ptr es:[si], 0x3a
013e je 0x9644
0140 cmp byte ptr es:[si], 0x5c
0144 je 0x9644
0146 push <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0149 push 0x9f10
014c push word ptr [bp - 0x208]
0150 push word ptr [bp - 0x20a]
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
0159 mov byte ptr [bp - 0x106], 0
015e jmp 0x968e
0160 push <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0163 push 0x9f10
0166 mov cx, es
0168 mov word ptr [bp - 0x20e], si
016c mov word ptr [bp - 0x20c], cx
0170 inc si
0171 push cx
0172 push si
0173 mov di, es
0175 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 374, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
017a mov es, di
017c mov al, byte ptr es:[si]
017f mov byte ptr [bp - 1], al
0182 lea ax, [bp - 0x106]
0186 push ss
0187 push ax
0188 push word ptr [bp - 0x208]
018c push word ptr [bp - 0x20a]
0190 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 401, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
0195 mov al, byte ptr [bp - 1]
0198 mov es, di
019a mov byte ptr es:[si], al
019d mov si, word ptr [bp - 0x20e]
01a1 sub si, 0x93a0
01a5 mov byte ptr [bp + si - 0x105], 0
01aa cmp byte ptr [bp - 0x106], 0
01af je 0x96c2
01b1 mov bx, 0x94a0
01b4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 437, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01b7 push ds
01b8 lea di, [bp - 0x106]
01bc mov si, bx
01be mov cx, ss
01c0 mov es, cx
01c2 mov ds, ax
01c4 mov cx, 0xffff
01c7 xor ax, ax
01c9 repne scasb al, byte ptr es:[di]
01cb not cx
01cd sub di, cx
01cf xchg si, di
01d1 push ds
01d2 push es
01d3 pop ds
01d4 pop es
01d5 shr cx, 1
01d7 rep movsw word ptr es:[di], word ptr [si]
01d9 adc cx, cx
01db rep movsb byte ptr es:[di], byte ptr [si]
01dd pop ds
01de push 0xc010
01e1 push word ptr [bp + 0xe]
01e4 nop 
01e5 push cs
01e6 call 0x8e56 ; _UpdateListBox
01e9 add sp, 4
01ec mov si, 1
01ef or si, si
01f1 je 0x96de
01f3 mov ax, 1
01f6 jmp 0x9918
01f9 nop 
01fa les bx, ptr [bp - 0x20a]
01fe cmp byte ptr es:[bx], 0
0202 jne 0x96fe
0204 mov di, word ptr [bp + 0xe]
0207 push di
0208 push ds
0209 push 0x16e6
020c push 0
020e push 0
0210 push 0x10
0212 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 531, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0217 jmp 0x96d7
0219 nop 
021a mov di, word ptr [bp + 0xe]
021d push di
021e push 1
0220 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 545, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 88}}]
0225 jmp 0x96d7
0227 nop 
0228 push word ptr [bp + 0xe]
022b push 0
022d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 558, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 88}}]
0232 jmp 0x9916
0235 nop 
0236 mov ax, word ptr [bp + 8]
0239 dec ax
023a je 0x9726
023c dec ax
023d je 0x9798
023f jmp 0x96d7
0241 nop 
0242 push word ptr [bp + 0xe]
0245 lea ax, [bp - 0x206]
0249 push ss
024a push ax
024b push 0x194
024e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 591, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 99}}]
0253 or ax, ax
0255 je 0x976e
0257 mov bx, 0x9f10
025a mov <resolved loader operand; see bindings> ; [{'operand_offset': 603, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
025d mov di, bx
025f lea si, [bp - 0x206]
0263 mov es, ax
0265 push ds
0266 mov cx, 0xffff
0269 xor ax, ax
026b repne scasb al, byte ptr es:[di]
026d not cx
026f sub di, cx
0271 mov bx, cx
0273 xchg si, di
0275 push ds
0276 push es
0277 pop ds
0278 pop es
0279 mov cx, 0xffff
027c repne scasb al, byte ptr es:[di]
027e dec di
027f mov cx, bx
0281 shr cx, 1
0283 rep movsw word ptr es:[di], word ptr [si]
0285 adc cx, cx
0287 rep movsb byte ptr es:[di], byte ptr [si]
0289 pop ds
028a push word ptr [bp + 0xe]
028d push 0x191
0290 lea ax, [bp - 0x206]
0294 push ss
0295 push ax
0296 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 663, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 92}}]
029b push word ptr [bp + 0xe]
029e push 0x191
02a1 push 0x401
02a4 push 0
02a6 push 0x7fff
02a9 push 0
02ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 684, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
02b0 jmp 0x96d7
02b3 nop 
02b4 mov di, word ptr [bp + 0xe]
02b7 push di
02b8 push 0x191
02bb mov ax, 0x93a0
02be mov <resolved loader operand; see bindings> ; [{'operand_offset': 703, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
02c1 mov word ptr [bp - 0x20a], ax
02c5 mov word ptr [bp - 0x208], cx
02c9 push cx
02ca push ax
02cb push 0x80
02ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 719, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 93}}]
02d3 mov es, word ptr [0xc170]
02d7 mov byte ptr es:[0x941f], 0
02dd push 0x2a
02df push word ptr [bp - 0x208]
02e3 push word ptr [bp - 0x20a]
02e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 746, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
02ec add sp, 6
02ef or dx, ax
02f1 jne 0x980e
02f3 push 0x3f
02f5 push word ptr [bp - 0x208]
02f9 push word ptr [bp - 0x20a]
02fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 768, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
0302 add sp, 6
0305 or dx, ax
0307 jne 0x980e
0309 push di
030a push 0x194
030d push 0x409
0310 push 0
0312 push 0
0314 push 0
0316 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 791, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
031b cmp ax, 0xffff
031e jne 0x980e
0320 cmp dx, ax
0322 jne 0x980e
0324 xor si, si
0326 jmp 0x96d7
0329 nop 
032a push word ptr [bp - 0x208]
032e push word ptr [bp - 0x20a]
0332 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 819, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
0337 mov bx, ax
0339 add bx, 0x93a0
033d mov es, word ptr [0xc170]
0341 mov si, bx
0343 mov word ptr [bp - 4], es
0346 cmp byte ptr es:[bx], 0x3a
034a je 0x985b
034c cmp byte ptr es:[si], 0x5c
0350 je 0x985b
0352 mov ax, si
0354 cmp ax, 0x93a0
0357 jbe 0x985b
0359 push word ptr [bp - 0x208]
035d push word ptr [bp - 0x20a]
0361 push es
0362 push si
0363 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 868, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 473}}]
0368 mov es, dx
036a mov bx, ax
036c mov si, ax
036e mov word ptr [bp - 4], es
0371 cmp byte ptr es:[bx], 0x3a
0375 jne 0x9830
0377 mov es, word ptr [bp - 4]
037a cmp byte ptr es:[si], 0x3a
037e je 0x9884
0380 cmp byte ptr es:[si], 0x5c
0384 je 0x9884
0386 push <resolved loader operand; see bindings> ; [{'operand_offset': 903, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0389 push 0x9f10
038c push word ptr [bp - 0x208]
0390 push word ptr [bp - 0x20a]
0394 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 917, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
0399 mov byte ptr [bp - 0x106], 0
039e jmp 0x98ce
03a0 push <resolved loader operand; see bindings> ; [{'operand_offset': 929, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
03a3 push 0x9f10
03a6 mov cx, es
03a8 mov word ptr [bp - 0x212], si
03ac mov word ptr [bp - 0x210], cx
03b0 inc si
03b1 push cx
03b2 push si
03b3 mov di, es
03b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 950, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
03ba mov es, di
03bc mov al, byte ptr es:[si]
03bf mov byte ptr [bp - 1], al
03c2 lea ax, [bp - 0x106]
03c6 push ss
03c7 push ax
03c8 push word ptr [bp - 0x208]
03cc push word ptr [bp - 0x20a]
03d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 977, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
03d5 mov al, byte ptr [bp - 1]
03d8 mov es, di
03da mov byte ptr es:[si], al
03dd mov si, word ptr [bp - 0x212]
03e1 sub si, 0x93a0
03e5 mov byte ptr [bp + si - 0x105], 0
03ea cmp byte ptr [bp - 0x106], 0
03ef je 0x9902
03f1 mov bx, 0x94a0
03f4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1013, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
03f7 push ds
03f8 lea di, [bp - 0x106]
03fc mov si, bx
03fe mov cx, ss
0400 mov es, cx
0402 mov ds, ax
0404 mov cx, 0xffff
0407 xor ax, ax
0409 repne scasb al, byte ptr es:[di]
040b not cx
040d sub di, cx
040f xchg si, di
0411 push ds
0412 push es
0413 pop ds
0414 pop es
0415 shr cx, 1
0417 rep movsw word ptr es:[di], word ptr [si]
0419 adc cx, cx
041b rep movsb byte ptr es:[di], byte ptr [si]
041d pop ds
041e push 0xc010
0421 push word ptr [bp + 0xe]
0424 nop 
0425 push cs
0426 call 0x8e56 ; _UpdateListBox
0429 add sp, 4
042c mov si, 1
042f jmp 0x96d7
0432 xor ax, ax
0434 pop ds
0435 pop si
0436 pop di
0437 leave 
0438 retf 0xa
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_UpdateListBox'], 'segment': 3, 'target_offset': 36438, 'caller_offsets': [35, 486, 1062]}

## Neighbors

- {'symbol': '_ChangeDirectory', 'offset': 37084, 'source': None, 'size': 364}
- {'symbol': 'OPENDLG', 'offset': 37448, 'source': None, 'size': 667}
- {'symbol': '_FileSelect', 'offset': 39200, 'source': None, 'size': 970}
- {'symbol': '_SpecialTutorialInit', 'offset': 40170, 'source': 'src/recovered/wf_SpecialTutorialInit-e0cff25916.c', 'size': 153}

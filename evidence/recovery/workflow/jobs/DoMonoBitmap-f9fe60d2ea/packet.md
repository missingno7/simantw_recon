# Recovery task _DoMonoBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 870 bytes.

```asm
0000 enter 0x2c, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xc]
0009 push ds
000a push 0xbab2
000d push 0
000f mov ax, di
0011 cdq 
0012 mov word ptr [bp - 0x2c], ax
0015 mov word ptr [bp - 0x2a], dx
0018 push dx
0019 push ax
001a push 0
001c push 0x20
001e mov ax, word ptr [bp + 0xa]
0021 cdq 
0022 mov word ptr [bp - 0x28], ax
0025 mov word ptr [bp - 0x26], dx
0028 add ax, 0x1f
002b adc dx, 0
002e push dx
002f push ax
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0035 push dx
0036 push ax
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
003c shl ax, 1
003e rcl dx, 1
0040 shl ax, 1
0042 rcl dx, 1
0044 mov word ptr [bp - 0x24], ax
0047 mov word ptr [bp - 0x22], dx
004a add ax, 0x20
004d adc dx, 0
0050 push dx
0051 push ax
0052 nop 
0053 push cs
0054 call 0x54da ; _mem_Alloc
0057 add sp, 0xa
005a mov si, ax
005c push ds
005d push 0xbab5
0060 push 0
0062 push 0
0064 push 0x30
0066 nop 
0067 push cs
0068 call 0x54da ; _mem_Alloc
006b add sp, 0xa
006e mov word ptr [bp - 0x1a], ax
0071 mov ax, word ptr [bp + 0x10]
0074 or ax, word ptr [bp + 0xe]
0077 jne 0x36c8
0079 jmp 0x3990
007c or si, si
007e jne 0x36cf
0080 jmp 0x3990
0083 cmp word ptr [bp - 0x1a], 0
0087 jne 0x36d8
0089 jmp 0x3990
008c push si
008d nop 
008e push cs
008f call 0x558e ; _mem_Lock
0092 add sp, 2
0095 mov word ptr [bp - 0x18], ax
0098 mov word ptr [bp - 0x16], dx
009b push word ptr [bp - 0x1a]
009e nop 
009f push cs
00a0 call 0x558e ; _mem_Lock
00a3 add sp, 2
00a6 mov word ptr [bp - 0x20], ax
00a9 mov word ptr [bp - 0x1e], dx
00ac push word ptr [0xcf52] ; _clipDC
00b0 push 1
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 2}}]
00b7 cmp word ptr [bp + 0x12], 0
00bb je 0x3780
00bd mov word ptr [bp - 0x1c], si
00c0 mov ax, word ptr [bp + 0xa]
00c3 add ax, 0x1f
00c6 cdq 
00c7 and dx, 0x1f
00ca add ax, dx
00cc sar ax, 5
00cf shl ax, 2
00d2 mov word ptr [bp - 0xe], ax
00d5 mov ax, word ptr [bp + 0xa]
00d8 add ax, 7
00db cdq 
00dc and dx, 7
00df add ax, dx
00e1 sar ax, 3
00e4 mov word ptr [bp - 0xa], ax
00e7 or di, di
00e9 jle 0x377b
00eb mov ax, word ptr [bp + 0xe]
00ee mov dx, word ptr [bp + 0x10]
00f1 mov word ptr [bp - 4], ax
00f4 mov ds, dx
00f6 lea ax, [di - 1]
00f9 imul word ptr [bp - 0xe]
00fc add ax, word ptr [bp - 0x18]
00ff mov dx, word ptr [bp - 0x16]
0102 mov word ptr [bp - 8], ax
0105 mov word ptr [bp - 6], dx
0108 mov word ptr [bp - 0xc], di
010b mov ax, word ptr [bp - 4]
010e mov cx, word ptr [bp - 0xa]
0111 mov si, ax
0113 les di, ptr [bp - 8]
0116 shr cx, 1
0118 rep movsw word ptr es:[di], word ptr [si]
011a adc cx, cx
011c rep movsb byte ptr es:[di], byte ptr [si]
011e mov ax, word ptr [bp - 0xa]
0121 add word ptr [bp - 4], ax
0124 mov ax, word ptr [bp - 0xe]
0127 sub word ptr [bp - 8], ax
012a dec word ptr [bp - 0xc]
012d jne 0x3757
012f push ss
0130 pop ds
0131 jmp 0x37f1
0133 nop 
0134 mov word ptr [bp - 0x1c], si
0137 mov ax, word ptr [bp - 0x24]
013a mov dx, word ptr [bp - 0x22]
013d mov word ptr [bp - 4], ax
0140 mov word ptr [bp - 2], dx
0143 mov ax, word ptr [bp + 0xe]
0146 mov dx, word ptr [bp + 0x10]
0149 mov word ptr [bp - 8], ax
014c mov word ptr [bp - 6], dx
014f mov ax, word ptr [bp - 0x18]
0152 mov dx, word ptr [bp - 0x16]
0155 mov word ptr [bp - 0xc], ax
0158 mov word ptr [bp - 0xa], dx
015b sub ax, ax
015d cmp word ptr [bp - 2], ax
0160 jne 0x37b3
0162 cmp word ptr [bp - 4], ax
0165 je 0x37f1
0167 mov ax, word ptr [bp - 4]
016a mov dx, word ptr [bp - 2]
016d mov word ptr [bp - 0xe], dx
0170 mov di, ax
0172 sub cx, cx
0174 mov si, dx
0176 neg di
0178 neg di
017a adc si, -1
017d les bx, ptr [bp - 8]
0180 add word ptr [bp - 8], 1
0184 jae 0x37d7
0186 add <resolved loader operand; see bindings> ; [{'operand_offset': 393, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
018b mov al, byte ptr es:[bx]
018e les bx, ptr [bp - 0xc]
0191 add word ptr [bp - 0xc], 1
0195 jae 0x37e8
0197 add <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
019c mov byte ptr es:[bx], al
019f dec di
01a0 jne 0x37c9
01a2 dec si
01a3 jns 0x37c9
01a5 les bx, ptr [bp - 0x20]
01a8 mov word ptr es:[bx], 0x28
01ad mov word ptr es:[bx + 2], 0
01b3 mov ax, word ptr [bp - 0x28]
01b6 mov dx, word ptr [bp - 0x26]
01b9 mov word ptr es:[bx + 4], ax
01bd mov word ptr es:[bx + 6], dx
01c1 mov ax, word ptr [bp - 0x2c]
01c4 mov dx, word ptr [bp - 0x2a]
01c7 mov word ptr es:[bx + 8], ax
01cb mov word ptr es:[bx + 0xa], dx
01cf mov ax, 1
01d2 mov word ptr es:[bx + 0xc], ax
01d6 mov word ptr es:[bx + 0xe], ax
01da sub ax, ax
01dc mov word ptr es:[bx + 0x12], ax
01e0 mov word ptr es:[bx + 0x10], ax
01e4 mov ax, word ptr [bp - 0x24]
01e7 mov dx, word ptr [bp - 0x22]
01ea mov word ptr es:[bx + 0x14], ax
01ee mov word ptr es:[bx + 0x16], dx
01f2 sub ax, ax
01f4 mov word ptr es:[bx + 0x1a], ax
01f8 mov word ptr es:[bx + 0x18], ax
01fc mov word ptr es:[bx + 0x1e], ax
0200 mov word ptr es:[bx + 0x1c], ax
0204 mov word ptr es:[bx + 0x22], ax
0208 mov word ptr es:[bx + 0x20], ax
020c mov word ptr es:[bx + 0x26], ax
0210 mov word ptr es:[bx + 0x24], ax
0214 test byte ptr [0xcc7e], 1 ; _displayType
0219 je 0x386a
021b jmp 0x38ee
021e mov di, word ptr [0xce8a] ; __backColor
0222 mov es, word ptr [0xc6b6]
0226 mov bx, di
0228 and bx, 0xf
022b shl bx, 2
022e mov al, byte ptr es:[bx - 0x73be]
0233 les si, ptr [bp - 0x20]
0236 mov byte ptr es:[si + 0x28], al
023a mov es, word ptr [0xc6b6]
023e mov al, byte ptr es:[bx - 0x73bf]
0243 mov es, word ptr [bp - 0x1e]
0246 mov byte ptr es:[si + 0x29], al
024a mov es, word ptr [0xc6b6]
024e mov al, byte ptr es:[bx - 0x73c0]
0253 les bx, ptr [bp - 0x20]
0256 mov byte ptr es:[bx + 0x2a], al
025a mov byte ptr es:[bx + 0x2b], ah
025e mov si, word ptr [0xcf4e] ; __foreColor
0262 mov bx, si
0264 and bx, 0xf
0267 shl bx, 2
026a mov es, word ptr [0xc6b6]
026e mov al, byte ptr es:[bx - 0x73be]
0273 mov cx, bx
0275 les bx, ptr [bp - 0x20]
0278 mov byte ptr es:[bx + 0x2c], al
027c mov bx, cx
027e mov es, word ptr [0xc6b6]
0282 mov al, byte ptr es:[bx - 0x73bf]
0287 les bx, ptr [bp - 0x20]
028a mov byte ptr es:[bx + 0x2d], al
028e mov es, word ptr [0xc6b6]
0292 mov bx, cx
0294 mov al, byte ptr es:[bx - 0x73c0]
0299 les bx, ptr [bp - 0x20]
029c mov byte ptr es:[bx + 0x2e], al
02a0 jmp 0x393c
02a2 test byte ptr [0xce97], 0x80 ; _monoPat
02a7 je 0x391c
02a9 mov al, 0xff
02ab mov byte ptr es:[bx + 0x28], al
02af mov byte ptr es:[bx + 0x29], al
02b3 mov byte ptr es:[bx + 0x2a], al
02b7 xor al, al
02b9 mov byte ptr es:[bx + 0x2c], al
02bd mov byte ptr es:[bx + 0x2d], al
02c1 mov byte ptr es:[bx + 0x2e], al
02c5 mov byte ptr es:[bx + 0x2f], al
02c9 mov byte ptr es:[bx + 0x2b], al
02cd jmp 0x3941
02cf nop 
02d0 mov al, 0xff
02d2 mov byte ptr es:[bx + 0x2c], al
02d6 mov byte ptr es:[bx + 0x2d], al
02da mov byte ptr es:[bx + 0x2e], al
02de xor al, al
02e0 mov byte ptr es:[bx + 0x28], al
02e4 mov byte ptr es:[bx + 0x29], al
02e8 mov byte ptr es:[bx + 0x2a], al
02ec mov byte ptr es:[bx + 0x2b], al
02f0 mov byte ptr es:[bx + 0x2f], 0
02f5 push word ptr [0xcf52] ; _clipDC
02f9 push word ptr [bp + 6]
02fc push word ptr [bp + 8]
02ff push word ptr [bp + 0xa]
0302 push word ptr [bp + 0xc]
0305 push 0
0307 push 0
0309 push 0
030b push word ptr [bp + 0xc]
030e push word ptr [bp - 0x16]
0311 push word ptr [bp - 0x18]
0314 push es
0315 push bx
0316 push 0
0318 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 793, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 443}}]
031d push word ptr [bp - 0x1c]
0320 nop 
0321 push cs
0322 call 0x559c ; _mem_Unlock
0325 add sp, 2
0328 push word ptr [bp - 0x1c]
032b nop 
032c push cs
032d call 0x5580 ; _mem_Free
0330 add sp, 2
0333 push word ptr [bp - 0x1a]
0336 nop 
0337 push cs
0338 call 0x559c ; _mem_Unlock
033b add sp, 2
033e push word ptr [bp - 0x1a]
0341 jmp 0x39a6
0343 nop 
0344 cmp word ptr [bp - 0x1a], 0
0348 je 0x39a1
034a push word ptr [bp - 0x1a]
034d nop 
034e push cs
034f call 0x5580 ; _mem_Free
0352 add sp, 2
0355 or si, si
0357 je 0x39ae
0359 push si
035a nop 
035b push cs
035c call 0x5580 ; _mem_Free
035f add sp, 2
0362 pop si
0363 pop di
0364 leave 
0365 retf 
```

## Known declaration examples

- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GRectFillOutline-24e4a6aa35.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near clipDC;` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern unsigned char near monoPat;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoBitmap', 'offset': 13098, 'source': None, 'size': 678}
- {'symbol': '_ConvertMonoBitmap', 'offset': 13776, 'source': None, 'size': 123}
- {'symbol': '_DoFastBitmap', 'offset': 14770, 'source': None, 'size': 405}
- {'symbol': '_DoFastMonoBitmap', 'offset': 15176, 'source': 'src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c', 'size': 337}

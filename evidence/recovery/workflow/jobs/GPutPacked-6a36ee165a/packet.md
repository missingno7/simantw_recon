# Recovery task _GPutPacked

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 634 bytes.

```asm
0000 enter 0x20, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xa]
0009 mov es, word ptr [bp + 0xc]
000c push word ptr es:[si + 2]
0010 lea ax, [si + 4]
0013 push es
0014 push ax
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnpackInit
001a add sp, 6
001d push 0xc
001f lea ax, [bp - 0x1e]
0022 push ss
0023 push ax
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
0029 add sp, 6
002c mov al, byte ptr [bp - 0x14]
002f and ax, 7
0032 mov word ptr [bp - 8], ax
0035 and byte ptr [bp - 0x14], 0xf8
0039 mov word ptr [bp - 2], 0
003e test byte ptr [bp - 0x1c], 0x80
0042 je 0x10fc
0044 mov al, byte ptr [bp - 0x1c]
0047 and ax, 0x7f
004a mul word ptr [bp - 0x16]
004d mov si, ax
004f add si, 0x1f
0052 and si, 0xffe7
0055 shr si, 3
0058 jmp 0x1138
005a mov al, byte ptr [bp - 0x1c]
005d and al, 0x7f
005f cmp al, 4
0061 je 0x1120
0063 mov al, byte ptr [bp - 0x1c]
0066 and al, 0x7f
0068 cmp al, 8
006a je 0x1120
006c push 0
006e mov ax, word ptr [bp - 0x16]
0071 dec ax
0072 push ax
0073 push 0
0075 push 0
0077 nop 
0078 push cs
0079 call 0x3dd6 ; _GImgSize
007c jmp 0x1130
007e push 0
0080 mov ax, word ptr [bp - 0x16]
0083 dec ax
0084 push ax
0085 push 0
0087 push 0
0089 nop 
008a push cs
008b call 0x3db2 ; _GPicSize
008e add sp, 8
0091 mov si, ax
0093 sub si, 4
0096 cmp word ptr [bp - 0x1e], 3
009a je 0x1141
009c jmp 0x11d0
009f push ds
00a0 push 0xba08
00a3 push 1
00a5 push 1
00a7 mov ax, word ptr [bp - 0x16]
00aa add ax, word ptr [bp + 6]
00ad add ax, 0xf
00b0 and al, 0xf8
00b2 dec ax
00b3 push ax
00b4 push 0
00b6 push word ptr [bp + 6]
00b9 nop 
00ba push cs
00bb call 0x3dd6 ; _GImgSize
00be add sp, 8
00c1 sub ax, 4
00c4 mov word ptr [bp - 0xe], ax
00c7 cdq 
00c8 shl ax, 1
00ca rcl dx, 1
00cc shl ax, 1
00ce rcl dx, 1
00d0 shl ax, 1
00d2 rcl dx, 1
00d4 add ax, 4
00d7 adc dx, 0
00da push dx
00db push ax
00dc nop 
00dd push cs
00de call 0x54da ; _mem_Alloc
00e1 add sp, 0xa
00e4 mov word ptr [bp - 0x12], ax
00e7 push ds
00e8 push 0xba15
00eb mov ax, word ptr [bp - 0x10]
00ee shl ax, 3
00f1 add ax, 4
00f4 push ax
00f5 nop 
00f6 push cs
00f7 call 0x54bc ; _mem_malloc
00fa add sp, 6
00fd mov si, ax
00ff mov word ptr [bp - 0xa], dx
0102 push word ptr [bp - 0x12]
0105 nop 
0106 push cs
0107 call 0x558e ; _mem_Lock
010a add sp, 2
010d mov di, ax
010f mov word ptr [bp - 4], dx
0112 mov ax, word ptr [bp - 0x16]
0115 mov es, dx
0117 mov word ptr es:[di], ax
011a mov word ptr es:[di + 2], 8
0120 mov es, word ptr [bp - 0xa]
0123 mov word ptr es:[si], ax
0126 mov word ptr es:[si + 2], 8
012c jmp 0x1209
012e mov word ptr [bp - 0xe], si
0131 push ds
0132 push 0xba20
0135 push 1
0137 mov ax, si
0139 cdq 
013a shl ax, 1
013c rcl dx, 1
013e shl ax, 1
0140 rcl dx, 1
0142 shl ax, 1
0144 rcl dx, 1
0146 add ax, 4
0149 adc dx, 0
014c push dx
014d push ax
014e nop 
014f push cs
0150 call 0x54da ; _mem_Alloc
0153 add sp, 0xa
0156 mov word ptr [bp - 0x12], ax
0159 push ax
015a nop 
015b push cs
015c call 0x558e ; _mem_Lock
015f add sp, 2
0162 mov di, ax
0164 mov word ptr [bp - 4], dx
0167 cmp word ptr [bp - 0x14], 0
016b jne 0x1212
016d jmp 0x12fc
0170 mov si, word ptr [bp + 8]
0173 mov word ptr [bp - 6], di
0176 mov ax, word ptr [bp - 0xe]
0179 shl ax, 3
017c push ax
017d lea ax, [di + 4]
0180 mov cx, word ptr [bp - 4]
0183 push cx
0184 push ax
0185 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 392, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
018a add sp, 6
018d or ax, ax
018f je 0x127d
0191 cmp word ptr [bp - 0x1e], 0
0195 jne 0x1268
0197 mov al, byte ptr [bp - 0x1c]
019a and al, 0x80
019c mov byte ptr [bp - 0x20], al
019f or al, al
01a1 je 0x1248
01a3 jmp 0x12d4
01a6 cmp al, 1
01a8 sbb ax, ax
01aa neg ax
01ac push ax
01ad push 8
01af push word ptr [bp - 0x16]
01b2 lea ax, [di + 4]
01b5 mov cx, word ptr [bp - 4]
01b8 push cx
01b9 push ax
01ba push si
01bb push word ptr [bp + 6]
01be nop 
01bf push cs
01c0 call 0x3d3c ; _GPutPicS
01c3 add sp, 0xe
01c6 test byte ptr [bp - 0x1c], 0x80
01ca jne 0x1271
01cc add si, 8
01cf mov ax, word ptr [bp - 0x14]
01d2 add word ptr [bp - 2], 8
01d6 cmp word ptr [bp - 2], ax
01d9 jb 0x1218
01db mov word ptr [bp + 8], si
01de cmp word ptr [bp - 8], 0
01e2 je 0x1302
01e4 mov ax, word ptr [bp - 8]
01e7 imul word ptr [bp - 0xe]
01ea push ax
01eb mov ax, word ptr [bp - 6]
01ee mov dx, word ptr [bp - 4]
01f1 add ax, 4
01f4 push dx
01f5 push ax
01f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 505, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
01fb add sp, 6
01fe cmp word ptr [bp - 0x1e], 0
0202 jne 0x1302
0204 mov al, byte ptr [bp - 0x1c]
0207 and al, 0x80
0209 cmp al, 1
020b sbb ax, ax
020d neg ax
020f push ax
0210 push word ptr [bp - 8]
0213 push word ptr [bp - 0x16]
0216 mov ax, word ptr [bp - 6]
0219 mov dx, word ptr [bp - 4]
021c add ax, 4
021f push dx
0220 push ax
0221 push word ptr [bp + 8]
0224 push word ptr [bp + 6]
0227 nop 
0228 push cs
0229 call 0x3d3c ; _GPutPicS
022c add sp, 0xe
022f jmp 0x1302
0231 nop 
0232 cmp byte ptr [bp - 0x20], 1
0236 sbb ax, ax
0238 neg ax
023a push ax
023b push 8
023d push word ptr [bp - 0x16]
0240 lea ax, [di + 4]
0243 mov cx, word ptr [bp - 4]
0246 push cx
0247 push ax
0248 mov ax, word ptr [bp - 0x14]
024b sub ax, word ptr [bp - 2]
024e add ax, word ptr [bp - 8]
0251 add ax, si
0253 sub ax, 8
0256 push ax
0257 jmp 0x125d
025a mov word ptr [bp - 6], di
025d jmp 0x1280
0260 push word ptr [bp - 0x12]
0263 nop 
0264 push cs
0265 call 0x559c ; _mem_Unlock
0268 add sp, 2
026b push word ptr [bp - 0x12]
026e nop 
026f push cs
0270 call 0x5580 ; _mem_Free
0273 add sp, 2
0276 pop si
0277 pop di
0278 leave 
0279 retf 
```

## Known declaration examples

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

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GRectFill', 'offset': 3992, 'source': 'src/recovered/GRectFill.c', 'size': 46}
- {'symbol': '_GRectFillOutline', 'offset': 4038, 'source': 'src/recovered/wf_GRectFillOutline-24e4a6aa35.c', 'size': 220}
- {'symbol': '_GMixedFill', 'offset': 4892, 'source': 'src/recovered/wf_GMixedFill-842c303c86.c', 'size': 130}
- {'symbol': '_GMixedFillBox', 'offset': 5022, 'source': 'src/recovered/wf_GMixedFillBox-e22515d7ab.c', 'size': 76}

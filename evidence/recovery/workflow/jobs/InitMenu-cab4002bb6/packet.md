# Recovery task _InitMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 790 bytes.

```asm
0000 enter 0x28, 0
0004 push di
0005 push si
0006 push 0
0008 push 6
000a push word ptr [bp + 6]
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0012 add sp, 6
0015 mov word ptr [bp - 2], ax
0018 or ax, ax
001a jne 0x4e55
001c jmp 0x5148
001f push ax
0020 nop 
0021 push cs
0022 call 0x558e ; _mem_Lock
0025 add sp, 2
0028 mov word ptr [0xbae2], ax
002b mov word ptr [0xbae4], dx
002f push 6
0031 push word ptr [bp + 6]
0034 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_UnhookObject
0039 add sp, 4
003c mov word ptr [bp - 0x14], 0
0041 mov ax, word ptr [0xbae2]
0044 mov dx, word ptr [0xbae4]
0048 mov di, ax
004a mov word ptr [bp - 4], dx
004d mov es, dx
004f mov bx, ax
0051 mov cx, word ptr es:[bx + 2]
0055 or cx, word ptr es:[bx]
0058 je 0x4ee4
005a mov cx, ax
005c mov ax, cx
005e mov dx, word ptr [0xbae4]
0062 add word ptr es:[di], ax
0065 adc word ptr es:[di + 2], dx
0069 mov ax, word ptr es:[di]
006c mov dx, word ptr es:[di + 2]
0070 mov bx, ax
0072 mov word ptr [bp - 0x1a], dx
0075 mov es, dx
0077 mov si, bx
0079 mov ax, word ptr es:[si + 2]
007d or ax, word ptr es:[si]
0080 je 0x4ed5
0082 mov word ptr [bp - 6], di
0085 mov ds, dx
0087 mov ax, cx
0089 mov dx, word ptr ss:[0xbae4]
008e add word ptr [bx], ax
0090 adc word ptr [bx + 2], dx
0093 add bx, 4
0096 mov ax, word ptr [bx + 2]
0099 or ax, word ptr [bx]
009b jne 0x4ebd
009d push ss
009e pop ds
009f mov es, word ptr [bp - 4]
00a2 add di, 4
00a5 mov ax, word ptr es:[di + 2]
00a9 or ax, word ptr es:[di]
00ac jne 0x4e92
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 151}}]
00b3 mov bx, 0x7260
00b6 mov es, word ptr [0xc6c0]
00ba mov word ptr [bp - 0x20], bx
00bd mov word ptr [bp - 0x1e], es
00c0 mov word ptr es:[bx], ax
00c3 mov word ptr [bp - 0x14], 0
00c8 les bx, ptr [0xbae2]
00cc mov ax, word ptr es:[bx]
00cf mov dx, word ptr es:[bx + 2]
00d3 mov si, ax
00d5 mov word ptr [bp - 0x1a], dx
00d8 mov es, dx
00da mov bx, si
00dc mov cx, word ptr es:[bx + 2]
00e0 or cx, word ptr es:[bx]
00e3 jne 0x4f1e
00e5 jmp 0x5136
00e8 mov word ptr [bp - 0x1c], si
00eb mov word ptr [bp - 0x18], 0
00f0 mov word ptr [bp - 8], 0x7262
00f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 151}}]
00fa mov bx, word ptr [bp - 8]
00fd mov es, word ptr [0xc6c0]
0101 mov word ptr [bp - 0x24], bx
0104 mov word ptr [bp - 0x22], es
0107 mov word ptr es:[bx], ax
010a mov word ptr [bp - 0x12], 0
010f les bx, ptr [0xbae2]
0113 mov di, word ptr [bp - 0x18]
0116 mov ax, word ptr es:[bx + di + 4]
011a mov dx, word ptr es:[bx + di + 6]
011e mov si, ax
0120 mov word ptr [bp - 0xa], dx
0123 mov es, dx
0125 mov bx, si
0127 mov cx, word ptr es:[bx + 2]
012b or cx, word ptr es:[bx]
012e jne 0x4f69
0130 jmp 0x50fb
0133 les bx, ptr es:[si]
0136 cmp byte ptr es:[bx], 0x2d
013a jne 0x4f90
013c les bx, ptr [bp - 0x24]
013f push word ptr es:[bx]
0142 push 0x800
0145 mov ax, word ptr [bp - 0x14]
0148 shl ax, 4
014b add ax, word ptr [bp - 0x12]
014e sub ax, 0x2ff
0151 push ax
0152 push 0
0154 push 0
0156 jmp 0x50e1
0159 nop 
015a push 0x23
015c mov es, word ptr [bp - 0xa]
015f push word ptr es:[si + 2]
0163 push word ptr es:[si]
0166 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 361, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
016b add sp, 6
016e mov word ptr [bp - 6], ax
0171 mov word ptr [bp - 4], dx
0174 or dx, ax
0176 jne 0x4fb1
0178 jmp 0x50c2
017b les bx, ptr [bp - 6]
017e mov byte ptr es:[bx], 0
0182 lea ax, [bp - 0x16]
0185 push ss
0186 push ax
0187 mov cx, word ptr [bp - 6]
018a mov dx, word ptr [bp - 4]
018d inc cx
018e push dx
018f push cx
0190 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _atoi
0195 add sp, 4
0198 push ax
0199 nop 
019a push cs
019b call 0x4cce ; _ms_LoadPopUpResource
019e add sp, 6
01a1 mov di, ax
01a3 mov word ptr [bp - 0xe], dx
01a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 415}}]
01ab mov es, word ptr [0xc6c0]
01af mov bx, word ptr [0xbb06]
01b3 shl bx, 1
01b5 mov word ptr es:[bx + 0x7276], ax
01ba mov word ptr [bp - 2], 0
01bf cmp word ptr [bp - 0x16], 0
01c3 jg 0x4ffe
01c5 jmp 0x508a
01c8 mov word ptr [bp - 0xc], si
01cb mov ax, word ptr [bp - 0xe]
01ce mov cx, di
01d0 mov word ptr [bp - 4], ax
01d3 mov si, word ptr [bp - 2]
01d6 mov word ptr [bp - 6], cx
01d9 mov word ptr [bp - 0x10], di
01dc mov es, word ptr [bp - 4]
01df les bx, ptr es:[di]
01e2 inc bx
01e3 mov word ptr [bp - 0x28], bx
01e6 mov word ptr [bp - 0x26], es
01e9 cmp byte ptr es:[bx], 0x2d
01ed jne 0x504c
01ef mov es, word ptr [0xc6c0]
01f3 mov bx, word ptr [0xbb06]
01f7 shl bx, 1
01f9 push word ptr es:[bx + 0x7276]
01fe push 0x800
0201 mov ax, word ptr [0xbb06]
0204 or ax, 0xff90
0207 shl ax, 4
020a lea cx, [si + 1]
020d or ax, cx
020f push ax
0210 push 0
0212 push 0
0214 jmp 0x5072
0216 mov es, word ptr [0xc6c0]
021a mov bx, word ptr [0xbb06]
021e shl bx, 1
0220 push word ptr es:[bx + 0x7276]
0225 push 0
0227 mov ax, word ptr [0xbb06]
022a or ax, 0xff90
022d shl ax, 4
0230 lea cx, [si + 1]
0233 or ax, cx
0235 push ax
0236 push word ptr [bp - 0x26]
0239 push word ptr [bp - 0x28]
023c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 573, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 411}}]
0241 add di, 4
0244 lea ax, [si + 1]
0247 mov si, ax
0249 cmp si, word ptr [bp - 0x16]
024c jl 0x5012
024e mov di, word ptr [bp - 0x10]
0251 mov si, word ptr [bp - 0xc]
0254 push word ptr [bp - 0xe]
0257 push di
0258 nop 
0259 push cs
025a call 0x54ca ; _mem_free
025d add sp, 4
0260 les bx, ptr [bp - 0x24]
0263 push word ptr es:[bx]
0266 push 0x10
0268 mov es, word ptr [0xc6c0]
026c mov bx, word ptr [0xbb06]
0270 shl bx, 1
0272 push word ptr es:[bx + 0x7276]
0277 mov es, word ptr [bp - 0xa]
027a push word ptr es:[si + 2]
027e push word ptr es:[si]
0281 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 642, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 411}}]
0286 inc word ptr [0xbb06]
028a jmp 0x50e6
028c les bx, ptr [bp - 0x24]
028f push word ptr es:[bx]
0292 push 0
0294 mov ax, word ptr [bp - 0x14]
0297 shl ax, 4
029a add ax, word ptr [bp - 0x12]
029d sub ax, 0x2ff
02a0 push ax
02a1 mov es, word ptr [bp - 0xa]
02a4 push word ptr es:[si + 2]
02a8 push word ptr es:[si]
02ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 684, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 411}}]
02b0 inc word ptr [bp - 0x12]
02b3 mov es, word ptr [bp - 0xa]
02b6 add si, 4
02b9 mov ax, word ptr es:[si + 2]
02bd or ax, word ptr es:[si]
02c0 je 0x50fb
02c2 jmp 0x4f69
02c5 les bx, ptr [bp - 0x20]
02c8 push word ptr es:[bx]
02cb push 0x10
02cd les bx, ptr [bp - 0x24]
02d0 push word ptr es:[bx]
02d3 les bx, ptr [bp - 0x1c]
02d6 push word ptr es:[bx + 2]
02da push word ptr es:[bx]
02dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 734, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 411}}]
02e2 add word ptr [bp - 0x18], 4
02e6 add word ptr [bp - 8], 2
02ea inc word ptr [bp - 0x14]
02ed add word ptr [bp - 0x1c], 4
02f1 les bx, ptr [bp - 0x1c]
02f4 mov ax, word ptr es:[bx + 2]
02f8 or ax, word ptr es:[bx]
02fb je 0x5136
02fd jmp 0x4f2b
0300 push word ptr [0xcd7e] ; _mainRootWnd
0304 les bx, ptr [bp - 0x20]
0307 push word ptr es:[bx]
030a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 779, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 158}}]
030f mov ax, 1
0312 pop si
0313 pop di
0314 leave 
0315 retf 
```

## Known declaration examples

- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far db_UnhookObject(int object, int kind);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far db_UnhookObject(int object, int kind);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near mainRootWnd;` — src/recovered/wf_PaintStuff-4a441706dd.c
- `extern int near mainRootWnd;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetMenuOptionText', 'offset': 19614, 'source': 'src/recovered/SetMenuOptionText.c', 'size': 48}
- {'symbol': '_ms_LoadPopUpResource', 'offset': 19662, 'source': None, 'size': 359}
- {'symbol': '_ms_PopUpMenuResource', 'offset': 20812, 'source': None, 'size': 320}
- {'symbol': '_TrapFill', 'offset': 21132, 'source': None, 'size': 495}

# Recovery task _ScrollEditArrays

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 734 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 or si, si
000b jg 0xe6c
000d jmp 0xf08
0010 mov ax, word ptr [0xcd7a] ; _editHeight
0013 sub ax, si
0015 imul word ptr [0xcc80] ; _editWidth
0019 sub ax, word ptr [bp + 6]
001c shl ax, 1
001e push ax
001f push word ptr [0x1444]
0023 push word ptr [0x1442]
0027 mov ax, word ptr [0xcc80] ; _editWidth
002a imul si
002c add ax, word ptr [bp + 6]
002f shl ax, 1
0031 add ax, word ptr [0x1442]
0035 mov dx, word ptr [0x1444]
0039 push dx
003a push ax
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
0040 add sp, 0xa
0043 mov ax, word ptr [0xcd7a] ; _editHeight
0046 sub ax, si
0048 imul word ptr [0xcc80] ; _editWidth
004c sub ax, word ptr [bp + 6]
004f push ax
0050 push word ptr [0x1440]
0054 push word ptr [0x143e]
0058 mov ax, word ptr [0xcc80] ; _editWidth
005b imul si
005d add ax, word ptr [0x143e]
0061 mov dx, word ptr [0x1440]
0065 add ax, word ptr [bp + 6]
0068 push dx
0069 push ax
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
006f add sp, 0xa
0072 mov ax, word ptr [0xcc80] ; _editWidth
0075 mov dx, word ptr [0x1442]
0079 mov bx, word ptr [0x1444]
007d mov cx, dx
007f imul si
0081 mov dx, cx
0083 mov cx, ax
0085 shl cx, 1
0087 mov di, ax
0089 mov ax, 0xffff
008c mov word ptr [bp - 0x10], di
008f mov di, dx
0091 mov es, bx
0093 rep stosb byte ptr es:[di], al
0095 mov dx, word ptr [0x143e]
0099 mov bx, word ptr [0x1440]
009d mov cx, word ptr [bp - 0x10]
00a0 mov di, dx
00a2 mov es, bx
00a4 rep stosb byte ptr es:[di], al
00a6 mov di, word ptr [bp + 6]
00a9 jmp 0x105e
00ac or si, si
00ae jl 0xf0f
00b0 jmp 0xfb0
00b3 neg si
00b5 mov ax, word ptr [0xcd7a] ; _editHeight
00b8 sub ax, si
00ba imul word ptr [0xcc80] ; _editWidth
00be add ax, word ptr [bp + 6]
00c1 shl ax, 1
00c3 push ax
00c4 mov ax, si
00c6 imul word ptr [0xcc80] ; _editWidth
00ca sub ax, word ptr [bp + 6]
00cd shl ax, 1
00cf add ax, word ptr [0x1442]
00d3 mov dx, word ptr [0x1444]
00d7 push dx
00d8 push ax
00d9 push dx
00da push word ptr [0x1442]
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
00e3 add sp, 0xa
00e6 mov ax, word ptr [0xcd7a] ; _editHeight
00e9 sub ax, si
00eb imul word ptr [0xcc80] ; _editWidth
00ef add ax, word ptr [bp + 6]
00f2 push ax
00f3 mov ax, si
00f5 imul word ptr [0xcc80] ; _editWidth
00f9 sub ax, word ptr [bp + 6]
00fc add ax, word ptr [0x143e]
0100 mov dx, word ptr [0x1440]
0104 push dx
0105 push ax
0106 push dx
0107 push word ptr [0x143e]
010b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
0110 add sp, 0xa
0113 lea ax, [si + 1]
0116 mov cx, ax
0118 mov ax, word ptr [0xcd7a] ; _editHeight
011b sub ax, si
011d dec ax
011e imul word ptr [0xcc80] ; _editWidth
0122 mov bx, ax
0124 shl bx, 1
0126 les si, ptr [0x1442]
012a mov dx, ax
012c mov ax, cx
012e mov cx, dx
0130 imul word ptr [0xcc80] ; _editWidth
0134 mov dx, cx
0136 mov cx, ax
0138 shl cx, 1
013a mov di, ax
013c mov ax, 0xffff
013f mov word ptr [bp - 0x12], di
0142 lea di, [bx + si]
0144 rep stosb byte ptr es:[di], al
0146 mov bx, dx
0148 les si, ptr [0x143e]
014c mov cx, word ptr [bp - 0x12]
014f lea di, [bx + si]
0151 jmp 0xf00
0154 mov di, word ptr [bp + 6]
0157 or di, di
0159 jne 0xfba
015b jmp 0x105e
015e or di, di
0160 jge 0x1012
0162 neg di
0164 mov ax, word ptr [0xcd7a] ; _editHeight
0167 imul word ptr [0xcc80] ; _editWidth
016b sub ax, di
016d shl ax, 1
016f push ax
0170 mov ax, di
0172 shl ax, 1
0174 add ax, word ptr [0x1442]
0178 mov dx, word ptr [0x1444]
017c push dx
017d push ax
017e push dx
017f push word ptr [0x1442]
0183 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 390, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
0188 add sp, 0xa
018b mov ax, word ptr [0xcd7a] ; _editHeight
018e imul word ptr [0xcc80] ; _editWidth
0192 sub ax, di
0194 push ax
0195 mov ax, word ptr [0x143e]
0198 mov dx, word ptr [0x1440]
019c add ax, di
019e push dx
019f push ax
01a0 push dx
01a1 push word ptr [0x143e]
01a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 424, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
01aa add sp, 0xa
01ad mov ax, di
01af neg ax
01b1 mov di, ax
01b3 jmp 0x105e
01b5 nop 
01b6 mov ax, word ptr [0xcd7a] ; _editHeight
01b9 imul word ptr [0xcc80] ; _editWidth
01bd sub ax, di
01bf shl ax, 1
01c1 push ax
01c2 push word ptr [0x1444]
01c6 push word ptr [0x1442]
01ca mov ax, di
01cc shl ax, 1
01ce add ax, word ptr [0x1442]
01d2 mov dx, word ptr [0x1444]
01d6 push dx
01d7 push ax
01d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 475, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
01dd add sp, 0xa
01e0 mov ax, word ptr [0xcd7a] ; _editHeight
01e3 imul word ptr [0xcc80] ; _editWidth
01e7 sub ax, di
01e9 push ax
01ea push word ptr [0x1440]
01ee mov ax, word ptr [0x143e]
01f1 push ax
01f2 mov dx, word ptr [0x1440]
01f6 add ax, di
01f8 push dx
01f9 push ax
01fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 509, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
01ff add sp, 0xa
0202 or di, di
0204 jne 0x1065
0206 jmp 0x1136
0209 or di, di
020b jge 0x10e0
020d neg di
020f mov cx, word ptr [0xcd7a] ; _editHeight
0213 or cx, cx
0215 jg 0x1076
0217 jmp 0x1136
021a mov bx, word ptr [0xcc80] ; _editWidth
021e mov ax, bx
0220 sub ax, di
0222 mov si, ax
0224 add ax, word ptr [0x143e]
0228 mov dx, word ptr [0x1440]
022c dec ax
022d mov word ptr [bp - 8], ax
0230 mov word ptr [bp - 6], dx
0233 shl si, 1
0235 add si, word ptr [0x1442]
0239 mov dx, word ptr [0x1444]
023d sub si, 2
0240 mov word ptr [bp - 4], si
0243 mov word ptr [bp - 2], dx
0246 mov ax, bx
0248 shl ax, 1
024a mov word ptr [bp - 0xc], ax
024d mov word ptr [bp - 0xa], cx
0250 mov word ptr [bp + 6], di
0253 mov bx, word ptr [bp - 8]
0256 mov ax, 0xffff
0259 mov cx, word ptr [bp + 6]
025c inc cx
025d mov dx, cx
025f shl cx, 1
0261 les di, ptr [bp - 4]
0264 rep stosb byte ptr es:[di], al
0266 mov es, word ptr [bp - 6]
0269 mov cx, dx
026b mov di, bx
026d rep stosb byte ptr es:[di], al
026f mov ax, word ptr [0xcc80] ; _editWidth
0272 add bx, ax
0274 mov ax, word ptr [bp - 0xc]
0277 add word ptr [bp - 4], ax
027a dec word ptr [bp - 0xa]
027d jne 0x10b2
027f pop si
0280 pop di
0281 leave 
0282 retf 
0283 nop 
0284 mov word ptr [bp + 6], di
0287 mov cx, word ptr [0xcd7a] ; _editHeight
028b or cx, cx
028d jle 0x1136
028f mov ax, word ptr [0x143e]
0292 mov dx, word ptr [0x1440]
0296 mov bx, ax
0298 mov word ptr [bp - 0xa], dx
029b mov ax, word ptr [0x1442]
029e mov dx, word ptr [0x1444]
02a2 mov word ptr [bp - 4], ax
02a5 mov word ptr [bp - 2], dx
02a8 mov ax, word ptr [0xcc80] ; _editWidth
02ab shl ax, 1
02ad mov word ptr [bp - 8], ax
02b0 mov word ptr [bp - 6], cx
02b3 mov ax, 0xffff
02b6 mov cx, word ptr [bp + 6]
02b9 shl cx, 1
02bb les di, ptr [bp - 4]
02be rep stosb byte ptr es:[di], al
02c0 mov es, word ptr [bp - 0xa]
02c3 mov cx, word ptr [bp + 6]
02c6 mov di, bx
02c8 rep stosb byte ptr es:[di], al
02ca mov ax, word ptr [0xcc80] ; _editWidth
02cd add bx, ax
02cf mov ax, word ptr [bp - 8]
02d2 add word ptr [bp - 4], ax
02d5 dec word ptr [bp - 6]
02d8 jne 0x110f
02da pop si
02db pop di
02dc leave 
02dd retf 
```

## Known declaration examples

- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near editWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ForceUpdateEdit', 'offset': 3664, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 6}
- {'symbol': '_DoEditUpdateDraw', 'offset': 3670, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c', 'size': 6}
- {'symbol': '_ScrollEditWindow', 'offset': 4410, 'source': None, 'size': 165}
- {'symbol': '_UpdateEdit', 'offset': 4576, 'source': None, 'size': 694}

# Recovery task _GBoxFill

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 203 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 mov bx, word ptr [bp + 6]
000c mov cx, word ptr [bp + 0xc]
000f mov dx, word ptr [bp + 8]
0012 mov ax, di
0014 cmp di, bx
0016 jle 0x1a00
0018 mov di, bx
001a mov word ptr [bp - 8], di
001d mov si, cx
001f cmp cx, dx
0021 jle 0x1a0b
0023 mov cx, dx
0025 mov word ptr [bp - 6], cx
0028 cmp ax, bx
002a jge 0x1a14
002c mov ax, bx
002e inc ax
002f mov word ptr [bp - 4], ax
0032 cmp si, dx
0034 jge 0x1a1e
0036 mov si, dx
0038 inc si
0039 mov word ptr [bp - 2], si
003c test byte ptr [0xcc7e], 1 ; _displayType
0041 jne 0x1a38
0043 mov al, byte ptr [bp + 0xe]
0046 and ax, 0xf
0049 cdq 
004a or dh, 1
004d push dx
004e push ax
004f jmp 0x1a91
0051 nop 
0052 mov al, byte ptr [bp + 0xe]
0055 and ax, 0x70
0058 test al, 0xf
005a jne 0x1a5e
005c shr ax, 3
005f cmp ax, 0xc
0062 ja 0x1a5e
0064 xchg bx, ax
0065 jmp word ptr cs:[bx + 0x1a50]
006a dw offset 0x1a66
006c dw offset 0x1a6c
006e dw offset 0x1a74
0070 dw offset 0x1a7c
0072 dw offset 0x1a5e
0074 dw offset 0x1a84
0076 dw offset 0x1a8c
0078 push 0xff
007b push -1
007d jmp 0x1a91
007f nop 
0080 push 0
0082 push 0
0084 jmp 0x1a91
0086 push 0x60
0088 push 0x6060
008b jmp 0x1a91
008d nop 
008e push 0x80
0091 push 0x8080
0094 jmp 0x1a91
0096 push 0xa0
0099 push 0xa0a0
009c jmp 0x1a91
009e push 0xc0
00a1 push 0xc0c0
00a4 jmp 0x1a91
00a6 push 0x20
00a8 push 0x2020
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 66}}]
00b0 mov si, ax
00b2 push word ptr [0xcf52] ; _clipDC
00b6 lea ax, [bp - 8]
00b9 push ss
00ba push ax
00bb push si
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 81}}]
00c1 push si
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
00c7 pop si
00c8 pop di
00c9 leave 
00ca retf 
```

## Known declaration examples

- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near clipDC;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GInvBox', 'offset': 6502, 'source': None, 'size': 78}
- {'symbol': '_GSetAttrib', 'offset': 6580, 'source': 'src/recovered/wf_GSetAttrib-bba4337448.c', 'size': 50}
- {'symbol': '_GPatBox', 'offset': 6834, 'source': None, 'size': 205}
- {'symbol': '_BitmapImageSize', 'offset': 7040, 'source': 'src/recovered/BitmapImageSize.c', 'size': 49}

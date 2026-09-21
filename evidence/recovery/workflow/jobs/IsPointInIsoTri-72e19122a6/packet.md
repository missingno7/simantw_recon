# Recovery task _IsPointInIsoTri

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 188 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 les bx, ptr [bp + 0xa]
0009 mov si, word ptr es:[bx + 2]
000d mov ax, word ptr es:[bx + 6]
0011 mov word ptr [bp - 2], ax
0014 mov cx, word ptr es:[bx + 4]
0018 mov word ptr [bp - 0xa], cx
001b mov dx, word ptr es:[bx]
001e mov word ptr [bp - 6], dx
0021 mov ax, cx
0023 add ax, dx
0025 cdq 
0026 sub ax, dx
0028 sar ax, 1
002a mov word ptr [bp - 4], ax
002d les bx, ptr [bp + 6]
0030 mov ax, word ptr es:[bx]
0033 mov word ptr [bp - 8], ax
0036 mov di, word ptr es:[bx + 2]
003a cmp word ptr [bp - 2], di
003d jle 0xc432
003f cmp di, si
0041 jl 0xc432
0043 mov ax, word ptr [bp - 2]
0046 sub ax, si
0048 cdq 
0049 push dx
004a push ax
004b mov ax, word ptr [bp - 6]
004e sub ax, word ptr [bp - 4]
0051 mov cx, di
0053 sub cx, word ptr [bp - 2]
0056 imul cx
0058 push dx
0059 push ax
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
005f mov cx, ax
0061 mov ax, word ptr [bp - 6]
0064 mov bx, dx
0066 cdq 
0067 add cx, ax
0069 adc bx, dx
006b mov ax, word ptr [bp - 8]
006e cdq 
006f cmp bx, dx
0071 jl 0xc3f5
0073 jg 0xc432
0075 cmp cx, ax
0077 ja 0xc432
0079 mov ax, si
007b sub ax, word ptr [bp - 2]
007e cdq 
007f push dx
0080 push ax
0081 mov ax, word ptr [bp - 4]
0084 sub ax, word ptr [bp - 0xa]
0087 mov cx, di
0089 sub cx, si
008b imul cx
008d push dx
008e push ax
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0094 mov cx, ax
0096 mov ax, word ptr [bp - 4]
0099 mov bx, dx
009b cdq 
009c add cx, ax
009e adc bx, dx
00a0 mov ax, word ptr [bp - 8]
00a3 cdq 
00a4 cmp bx, dx
00a6 jg 0xc42a
00a8 jl 0xc432
00aa cmp cx, ax
00ac jb 0xc432
00ae mov ax, 1
00b1 pop si
00b2 pop di
00b3 leave 
00b4 retf 
00b5 nop 
00b6 xor ax, ax
00b8 pop si
00b9 pop di
00ba leave 
00bb retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ProcCasteEvent', 'offset': 48392, 'source': None, 'size': None}
- {'symbol': '_ProcModeEvent', 'offset': 49274, 'source': None, 'size': None}
- {'symbol': '_BoundPointToTri', 'offset': 50232, 'source': 'src/recovered/wf_BoundPointToTri-0892cf4e80.c', 'size': 176}
- {'symbol': '_win_DrawModeWindow', 'offset': 50408, 'source': None, 'size': 216}

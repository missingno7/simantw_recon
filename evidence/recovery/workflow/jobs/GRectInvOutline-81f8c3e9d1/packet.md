# Recovery task _GRectInvOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 167 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 les cx, ptr [bp + 6]
0009 mov ax, es
000b or ax, cx
000d jne 0xe1c
000f jmp 0xead
0012 mov si, word ptr [bp + 0xa]
0015 mov bx, cx
0017 mov di, word ptr es:[bx]
001a mov ax, word ptr es:[bx + 2]
001e mov word ptr [bp - 2], ax
0021 mov ax, word ptr es:[bx + 4]
0025 mov word ptr [bp - 4], ax
0028 mov ax, word ptr es:[bx + 6]
002c mov word ptr [bp - 6], ax
002f or si, si
0031 je 0xead
0033 push word ptr [bp - 2]
0036 mov ax, si
0038 sub si, word ptr [bp - 4]
003b neg si
003d lea cx, [si - 1]
0040 push cx
0041 mov dx, ax
0043 add ax, word ptr [bp - 2]
0046 dec ax
0047 push ax
0048 mov ax, dx
004a add dx, di
004c push dx
004d mov word ptr [bp - 8], ax
0050 mov word ptr [bp - 0xa], cx
0053 mov word ptr [bp - 0xc], dx
0056 nop 
0057 push cs
0058 call 0x1966 ; _GInvBox
005b add sp, 8
005e mov ax, word ptr [bp - 6]
0061 dec ax
0062 push ax
0063 push word ptr [bp - 0xa]
0066 mov cx, word ptr [bp - 6]
0069 sub cx, word ptr [bp - 8]
006c push cx
006d push word ptr [bp - 0xc]
0070 mov word ptr [bp - 0xe], ax
0073 nop 
0074 push cs
0075 call 0x1966 ; _GInvBox
0078 add sp, 8
007b push word ptr [bp - 0xe]
007e push di
007f push word ptr [bp - 2]
0082 mov ax, word ptr [bp - 0xc]
0085 dec ax
0086 push ax
0087 nop 
0088 push cs
0089 call 0x1966 ; _GInvBox
008c add sp, 8
008f push word ptr [bp - 0xe]
0092 push si
0093 push word ptr [bp - 2]
0096 mov ax, word ptr [bp - 4]
0099 dec ax
009a push ax
009b nop 
009c push cs
009d call 0x1966 ; _GInvBox
00a0 add sp, 8
00a3 pop si
00a4 pop di
00a5 leave 
00a6 retf 
```

## Known declaration examples

- `extern void GInvBox(int,int,int,int);` — src/recovered/GRectInv.c
- `extern void far GInvBox(int a, int b, int c, int d);` — src/recovered/wf_GInvOutline-07520ef33f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GRectPartialOutline', 'offset': 3266, 'source': None, 'size': 200}
- {'symbol': '_GInvOutline', 'offset': 3466, 'source': 'src/recovered/wf_GInvOutline-07520ef33f.c', 'size': 128}
- {'symbol': '_GRectInv', 'offset': 3762, 'source': 'src/recovered/GRectInv.c', 'size': 43}
- {'symbol': '_GRectOutline', 'offset': 3806, 'source': None, 'size': 186}

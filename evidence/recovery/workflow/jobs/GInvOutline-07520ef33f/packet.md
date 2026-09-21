# Recovery task _GInvOutline

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 128 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xe]
0009 or si, si
000b je 0xe06
000d mov di, word ptr [bp + 8]
0010 push di
0011 mov ax, si
0013 sub si, word ptr [bp + 0xa]
0016 neg si
0018 lea cx, [si - 1]
001b push cx
001c mov dx, ax
001e add ax, di
0020 dec ax
0021 push ax
0022 mov ax, dx
0024 add dx, word ptr [bp + 6]
0027 push dx
0028 mov word ptr [bp - 2], ax
002b mov word ptr [bp - 4], cx
002e mov word ptr [bp - 6], dx
0031 nop 
0032 push cs
0033 call 0x1966 ; _GInvBox
0036 add sp, 8
0039 mov ax, word ptr [bp + 0xc]
003c dec ax
003d push ax
003e push word ptr [bp - 4]
0041 mov cx, word ptr [bp + 0xc]
0044 sub cx, word ptr [bp - 2]
0047 push cx
0048 push word ptr [bp - 6]
004b mov word ptr [bp - 8], ax
004e nop 
004f push cs
0050 call 0x1966 ; _GInvBox
0053 add sp, 8
0056 push word ptr [bp - 8]
0059 push word ptr [bp + 6]
005c push di
005d mov ax, word ptr [bp - 6]
0060 dec ax
0061 push ax
0062 nop 
0063 push cs
0064 call 0x1966 ; _GInvBox
0067 add sp, 8
006a push word ptr [bp - 8]
006d push si
006e push di
006f mov ax, word ptr [bp + 0xa]
0072 dec ax
0073 push ax
0074 nop 
0075 push cs
0076 call 0x1966 ; _GInvBox
0079 add sp, 8
007c pop si
007d pop di
007e leave 
007f retf 
```

## Known declaration examples

- `extern void GInvBox(int,int,int,int);` — src/recovered/GRectInv.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GBoxOutline', 'offset': 3122, 'source': None, 'size': 144}
- {'symbol': '_GRectPartialOutline', 'offset': 3266, 'source': None, 'size': 200}
- {'symbol': '_GRectInvOutline', 'offset': 3594, 'source': None, 'size': 167}
- {'symbol': '_GRectInv', 'offset': 3762, 'source': 'src/recovered/GRectInv.c', 'size': 43}

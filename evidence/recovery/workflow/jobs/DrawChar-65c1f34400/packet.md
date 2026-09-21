# Recovery task _DrawChar

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 188 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 add bp, 6
0006 push es
0007 push ds
0008 push si
0009 push di
000a mov <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 10}}]
000d mov ds, ax
000f mov cx, 3
0012 mov bx, word ptr [bp + 0xc]
0015 mov al, bl
0017 and al, 7
0019 mov si, bx
001b shr si, cl
001d mov dx, word ptr [bp + 0xe]
0020 mov ah, dl
0022 and ah, 7
0025 mov di, dx
0027 shr di, cl
0029 mov bx, ax
002b les ax, ptr [bp]
002e mov word ptr [0xb90e], es
0032 add si, ax
0034 les ax, ptr [bp + 4]
0037 mov word ptr [0xb910], es
003b add di, ax
003d mov cx, bx
003f mov bx, word ptr [bp + 8]
0042 mov bp, word ptr [bp + 0xa]
0045 mov dx, bx
0047 shr dx, 1
0049 shr dx, 1
004b shr dx, 1
004d mov word ptr [0xb918], dx
0051 push si
0052 push di
0053 mov dx, word ptr [0xb918]
0057 mov es, word ptr [0xb910]
005b mov ds, word ptr [0xb90e]
005f or dx, dx
0061 je 0xb0ad
0063 lodsw ax, word ptr [si]
0064 xchg al, ah
0066 shl ax, cl
0068 xor al, al
006a xchg ch, cl
006c shr ax, cl
006e xchg ch, cl
0070 xchg al, ah
0072 or word ptr es:[di], ax
0075 inc di
0076 dec si
0077 dec dx
0078 jne 0xb096
007a mov ax, bx
007c and ax, 7
007f je 0xb0d5
0081 mov dx, bx
0083 mov bx, 0xb02a
0086 xlatb 
0088 mov bx, dx
008a xor dx, dx
008c mov dh, al
008e lodsw ax, word ptr [si]
008f xchg al, ah
0091 shl ax, cl
0093 xor al, al
0095 xchg ch, cl
0097 and ax, dx
0099 shr ax, cl
009b xchg ch, cl
009d xchg al, ah
009f or word ptr es:[di], ax
00a2 pop di
00a3 pop si
00a4 dec bp
00a5 je 0xb0e9
00a7 mov <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 10}}]
00aa mov ds, ax
00ac add si, word ptr [0xb912] ; _source_bitmap_width
00b0 add di, word ptr [0xb914] ; _dest_bitmap_width
00b4 jmp 0xb084
00b6 pop di
00b7 pop si
00b8 pop ds
00b9 pop es
00ba pop bp
00bb retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '__font_LineHeight', 'offset': 44494, 'source': 'src/recovered/font_LineHeight.c', 'size': 17}
- {'symbol': '_font_MakeImage', 'offset': 44512, 'source': None, 'size': 586}
- {'symbol': '_ClearBuffer', 'offset': 45295, 'source': None, 'size': 32}
- {'symbol': '_CopyMaskBitmap2', 'offset': 45328, 'source': None, 'size': 496}

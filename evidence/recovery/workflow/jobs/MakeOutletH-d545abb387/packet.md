# Recovery task _MakeOutletH

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 257 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov dx, di
000b mov ax, di
000d add ax, 0xc
0010 cmp ax, dx
0012 jl 0x3da3
0014 mov bx, di
0016 shl bx, 6
0019 mov cx, word ptr [bp + 8]
001c mov word ptr [bp - 2], cx
001f mov ax, cx
0021 sub ax, cx
0023 add ax, 9
0026 mov word ptr [bp - 8], ax
0029 mov ax, di
002b sub ax, dx
002d add ax, 0xd
0030 mov word ptr [bp - 4], ax
0033 mov word ptr [bp - 6], dx
0036 mov ax, word ptr [bp + 8]
0039 add ax, 8
003c cmp ax, word ptr [bp + 8]
003f jl 0x3d98
0041 mov ax, 0x63
0044 mov si, word ptr [bp - 2]
0047 add si, bx
0049 mov cx, word ptr [bp - 8]
004c lea di, [si + 0x28e8]
0050 push ds
0051 pop es
0052 rep stosb byte ptr es:[di], al
0054 add bx, 0x40
0057 dec word ptr [bp - 4]
005a jne 0x3d7a
005c mov di, word ptr [bp + 6]
005f mov ax, word ptr [bp + 8]
0062 add ax, 8
0065 push ax
0066 push word ptr [bp + 8]
0069 lea ax, [di + 0xc]
006c push ax
006d push di
006e nop 
006f push cs
0070 call 0x3944 ; _TileFrame1
0073 add sp, 8
0076 mov word ptr [bp - 4], 0
007b mov ax, di
007d shl ax, 6
0080 mov word ptr [bp - 2], ax
0083 mov dx, ax
0085 xor si, si
0087 mov di, word ptr [bp - 4]
008a add di, 0x2328
008e mov cx, word ptr [bp + 8]
0091 mov word ptr [bp - 2], dx
0094 mov al, byte ptr [di]
0096 add di, 4
0099 mov bx, dx
009b add bx, si
009d add bx, cx
009f mov byte ptr [bx + 0x296a], al
00a3 inc si
00a4 cmp si, 5
00a7 jl 0x3dd8
00a9 add dx, 0x40
00ac inc word ptr [bp - 4]
00af cmp word ptr [bp - 4], 4
00b3 jl 0x3dc9
00b5 mov word ptr [bp - 4], 0
00ba mov dx, word ptr [bp + 6]
00bd shl dx, 6
00c0 xor si, si
00c2 mov di, word ptr [bp - 4]
00c5 add di, 0x2328
00c9 mov cx, word ptr [bp + 8]
00cc mov word ptr [bp - 2], dx
00cf mov al, byte ptr [di]
00d1 add di, 4
00d4 mov bx, dx
00d6 add bx, si
00d8 add bx, cx
00da mov byte ptr [bx + 0x2aaa], al
00de inc si
00df cmp si, 5
00e2 jl 0x3e13
00e4 add dx, 0x40
00e7 inc word ptr [bp - 4]
00ea cmp word ptr [bp - 4], 4
00ee jl 0x3e04
00f0 mov si, word ptr [bp + 6]
00f3 shl si, 6
00f6 mov bx, cx
00f8 mov byte ptr [bx + si + 0x2a6c], 0x65
00fd pop si
00fe pop di
00ff leave 
0100 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeOutletV', 'offset': 15360, 'source': None, 'size': 257}
- {'symbol': '_MakePlugV', 'offset': 15618, 'source': 'src/recovered/wf_MakePlugV-9d1d0472d2.c', 'size': 66}
- {'symbol': '_MakePlugH', 'offset': 15942, 'source': 'src/recovered/wf_MakePlugH-4c8422f5bd.c', 'size': 66}
- {'symbol': '_MakeKnob', 'offset': 16008, 'source': 'src/recovered/wf_MakeKnob-7ddc938695.c', 'size': 66}

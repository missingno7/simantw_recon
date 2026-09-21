# Recovery task _ExtractVariableLen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 222 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 lds di, ptr [bp + 6]
0009 xor si, si
000b mov ax, word ptr [bp + 0xa]
000e mov dx, word ptr [bp + 0xc]
0011 mov cx, ax
0013 mov word ptr [bp - 2], dx
0016 mov es, dx
0018 mov bx, ax
001a sub ax, ax
001c mov word ptr es:[bx + 2], ax
0020 mov word ptr es:[bx], ax
0023 les bx, ptr [di]
0025 test byte ptr es:[bx], 0x80
0029 je 0x84a0
002b mov word ptr [bp - 4], cx
002e mov cx, word ptr [bp + 0xe]
0031 mov al, byte ptr es:[bx]
0034 and al, 0x7f
0036 mov byte ptr [bp + si - 8], al
0039 inc si
003a mov ax, bx
003c mov bx, cx
003e mov dx, es
0040 mov es, word ptr [bp + 0x10]
0043 sub word ptr es:[bx], 1
0047 sbb word ptr es:[bx + 2], 0
004c mov bx, ax
004e mov ax, dx
0050 add bx, 1
0053 adc ax, 0
0056 mov es, ax
0058 mov word ptr [di], bx
005a mov word ptr [di + 2], es
005d test byte ptr es:[bx], 0x80
0061 jne 0x846b
0063 mov cx, word ptr [bp - 4]
0066 mov al, byte ptr es:[bx]
0069 mov dx, es
006b mov es, word ptr [bp - 2]
006e mov word ptr [bp - 0xc], bx
0071 mov word ptr [bp - 0xa], dx
0074 mov bx, cx
0076 mov byte ptr es:[bx], al
0079 les bx, ptr [bp + 0xe]
007c sub word ptr es:[bx], 1
0080 sbb word ptr es:[bx + 2], 0
0085 mov ax, word ptr [bp - 0xc]
0088 add ax, 1
008b adc dx, 0
008e mov word ptr [di], ax
0090 mov word ptr [di + 2], dx
0093 dec si
0094 js 0x8512
0096 mov al, byte ptr [bp + si - 8]
0099 mov dx, ax
009b shl al, 7
009e mov es, word ptr [bp - 2]
00a1 mov bx, cx
00a3 or byte ptr es:[bx], al
00a6 shr dl, 1
00a8 mov byte ptr es:[bx + 1], dl
00ac dec si
00ad js 0x8512
00af mov al, byte ptr [bp + si - 8]
00b2 mov dx, ax
00b4 shl al, 6
00b7 or byte ptr es:[bx + 1], al
00bb shr dl, 2
00be mov byte ptr es:[bx + 2], dl
00c2 dec si
00c3 js 0x8512
00c5 mov al, byte ptr [bp + si - 8]
00c8 mov dx, ax
00ca shl al, 5
00cd or byte ptr es:[bx + 2], al
00d1 shr dl, 3
00d4 mov byte ptr es:[bx + 3], dl
00d8 push ss
00d9 pop ds
00da pop si
00db pop di
00dc leave 
00dd retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExtractDWord', 'offset': 33700, 'source': 'src/recovered/wf_ExtractDWord-f367d1b9bc.c', 'size': 81}
- {'symbol': '_ExtractWord', 'offset': 33782, 'source': 'src/recovered/ExtractWord.c', 'size': 68}
- {'symbol': '_Extract24BitVal', 'offset': 34072, 'source': 'src/recovered/wf_Extract24BitVal-523b60cef9.c', 'size': 118}
- {'symbol': '_myBeginSong', 'offset': 34190, 'source': None, 'size': None}

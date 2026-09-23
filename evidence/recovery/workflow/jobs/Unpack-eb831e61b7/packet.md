# Recovery task _Unpack

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 306 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 sub sp, 4
0006 push di
0007 push si
0008 mov word ptr [bp - 2], 0
000d mov bx, word ptr [0xb7ca]
0011 mov dx, word ptr [0xb7ce]
0015 mov cx, word ptr [0xb7d0]
0019 push ds
001a mov ax, word ptr [0xb7c0]
001d mov word ptr [bp - 4], ax
0020 mov ax, word ptr [0xb7cc]
0023 les di, ptr [bp + 6]
0026 lds si, ptr [0xb7c4]
002a cmp word ptr ss:[0xb7d4], 0
0030 je 0xa6c8
0032 dec word ptr ss:[0xb7d4]
0037 je 0xa6cf
0039 dec word ptr ss:[0xb7d4]
003e je 0xa6dd
0040 dec word ptr ss:[0xb7d4]
0045 je 0xa706
0047 dec word ptr ss:[0xb7d4]
004c je 0xa710
004e mov ds, word ptr [bp - 4]
0051 jmp 0xa758
0054 mov di, 1
0057 jmp 0xa779
005a mov di, 2
005d jmp 0xa779
0060 shr ax, 1
0062 test ah, 1
0065 jne 0xa6d9
0067 dec word ptr ss:[0xb7c8]
006c js 0xa6bc
006e lodsb al, byte ptr [si]
006f mov ah, 0xff
0071 test al, 1
0073 je 0xa706
0075 dec word ptr ss:[0xb7c8]
007a js 0xa6c2
007c mov dl, byte ptr [si]
007e inc si
007f mov byte ptr es:[di], dl
0082 inc di
0083 mov ds, word ptr [bp - 4]
0086 mov byte ptr [bx + 4], dl
008a mov ds, word ptr ss:[0xb7c6]
008f inc bx
0090 and bx, 0xfff
0094 inc word ptr [bp - 2]
0097 dec word ptr [bp + 0xa]
009a je 0xa776
009c jmp 0xa6c8
009e dec word ptr ss:[0xb7c8]
00a3 js 0xa76c
00a5 mov cl, byte ptr [si]
00a7 inc si
00a8 dec word ptr ss:[0xb7c8]
00ad js 0xa767
00af mov dl, byte ptr [si]
00b1 inc si
00b2 mov ch, dl
00b4 shr ch, 1
00b6 shr ch, 1
00b8 shr ch, 1
00ba shr ch, 1
00bc and dl, 0xf
00bf add dl, byte ptr ss:[0xb7c2]
00c4 xor dh, dh
00c6 mov word ptr ss:[0xb7d2], dx
00cb mov ds, word ptr [bp - 4]
00ce xchg cx, bx
00d0 mov dl, byte ptr [bx + 4]
00d4 inc bx
00d5 and bx, 0xfff
00d9 mov byte ptr es:[di], dl
00dc inc di
00dd xchg cx, bx
00df mov byte ptr [bx + 4], dl
00e3 inc bx
00e4 and bx, 0xfff
00e8 inc word ptr [bp - 2]
00eb dec word ptr [bp + 0xa]
00ee je 0xa771
00f0 dec word ptr ss:[0xb7d2]
00f5 jns 0xa736
00f7 mov ds, word ptr ss:[0xb7c6]
00fc jmp 0xa6c8
00ff mov di, 4
0102 jmp 0xa779
0104 mov di, 3
0107 jmp 0xa779
0109 mov di, 5
010c jmp 0xa779
010e mov di, 0
0111 pop ds
0112 mov word ptr [0xb7d4], di
0116 mov word ptr [0xb7cc], ax
0119 mov word ptr [0xb7ca], bx
011d mov word ptr [0xb7c4], si
0121 mov word ptr [0xb7ce], dx
0125 mov word ptr [0xb7d0], cx
0129 mov ax, word ptr [bp - 2]
012c pop si
012d pop di
012e mov sp, bp
0130 pop bp
0131 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Encode', 'offset': 41995, 'source': None, 'size': 542}
- {'symbol': '_UnpackInit', 'offset': 42538, 'source': None, 'size': 62}
- {'symbol': '_UnpackSetBuf', 'offset': 42906, 'source': None, 'size': 22}
- {'symbol': '_UnpackFileOpen', 'offset': 42928, 'source': None, 'size': 57}

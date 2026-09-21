# Recovery task _TryMoveDirR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 186 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xa]
0009 or si, si
000b jge 0x6864
000d xor ax, ax
000f pop si
0010 pop di
0011 leave 
0012 retf 
0013 nop 
0014 mov es, word ptr [0xc396]
0018 mov al, byte ptr es:[si + 8]
001d cwde 
001e mov di, ax
0020 add di, word ptr [bp + 8]
0023 mov es, word ptr [0xc398]
0027 mov al, byte ptr es:[si]
002c cwde 
002d add ax, word ptr [bp + 6]
0030 cmp ax, 0x3f
0033 jg 0x685d
0035 mov si, ax
0037 or si, si
0039 jl 0x685d
003b cmp di, 0x3f
003e jg 0x685d
0040 cmp di, 1
0043 jge 0x68a4
0045 push word ptr [bp + 6]
0048 nop 
0049 push cs
004a call 0x74ba ; _GetOutR
004d add sp, 2
0050 pop si
0051 pop di
0052 leave 
0053 retf 
0054 mov bx, si
0056 shl bx, 6
0059 add bx, di
005b mov word ptr [bp - 4], bx
005e cmp byte ptr [bx + 0x58e8], 0x1c
0063 jae 0x685d
0065 mov es, word ptr [0xc384]
0069 mov bx, word ptr es:[0x9b6a]
006e mov es, word ptr [0xc386]
0072 mov al, byte ptr es:[bx + 0x46e6]
0077 and al, 0xf8
0079 or al, byte ptr [bp + 0xa]
007c lea cx, [bx + 0x46e6]
0080 mov dx, bx
0082 mov bx, word ptr [bp - 4]
0085 mov byte ptr [bx - 0x6718], al
0089 mov bx, word ptr [bp + 8]
008c mov ax, si
008e mov si, word ptr [bp + 6]
0091 shl si, 6
0094 mov byte ptr [bx + si - 0x6718], 0
0099 mov bx, dx
009b mov byte ptr es:[bx + 0x4104], al
00a0 mov ax, di
00a2 mov byte ptr es:[bx + 0x42fa], al
00a7 mov bx, word ptr [bp - 4]
00aa mov al, byte ptr [bx - 0x6718]
00ae mov bx, cx
00b0 mov byte ptr es:[bx], al
00b3 mov ax, 1
00b6 pop si
00b7 pop di
00b8 leave 
00b9 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LostHeadR', 'offset': 26512, 'source': None, 'size': 94}
- {'symbol': '_LostTailR', 'offset': 26606, 'source': None, 'size': 98}
- {'symbol': '_DoNestingR', 'offset': 26890, 'source': None, 'size': 557}
- {'symbol': '_TryEatFoodR', 'offset': 27448, 'source': None, 'size': 126}

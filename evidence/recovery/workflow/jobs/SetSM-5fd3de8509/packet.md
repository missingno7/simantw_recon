# Recovery task _SetSM

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 186 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 6]
0008 or si, si
000a jl 0x8dac
000c mov di, word ptr [bp + 8]
000f cmp si, 0x3f
0012 jg 0x8daf
0014 or di, di
0016 jl 0x8daf
0018 cmp di, 0x1f
001b jg 0x8daf
001d mov dx, 1
0020 jmp 0x8db1
0022 mov di, word ptr [bp + 8]
0025 xor dx, dx
0027 or dx, dx
0029 jne 0x8db8
002b jmp 0x8e40
002e mov cx, word ptr [bp + 0xa]
0031 cmp cx, 0xff
0035 jle 0x8dc4
0037 mov cx, 0xff
003a mov es, word ptr [0xc270]
003e mov al, byte ptr es:[0x8605]
0042 cwde 
0043 or ax, ax
0045 je 0x8de2
0047 dec ax
0048 je 0x8df6
004a dec ax
004b je 0x8e0a
004d dec ax
004e je 0x8e1e
0050 dec ax
0051 je 0x8e32
0053 pop si
0054 pop di
0055 leave 
0056 retf 
0057 nop 
0058 mov es, word ptr [0xc27a]
005c mov bx, si
005e shl bx, 5
0061 add bx, di
0063 mov byte ptr es:[bx + 0x62d2], cl
0068 pop si
0069 pop di
006a leave 
006b retf 
006c mov es, word ptr [0xc27a]
0070 mov bx, si
0072 shl bx, 5
0075 add bx, di
0077 mov byte ptr es:[bx + 0x6ad2], cl
007c pop si
007d pop di
007e leave 
007f retf 
0080 mov es, word ptr [0xc27a]
0084 mov bx, si
0086 shl bx, 5
0089 add bx, di
008b mov byte ptr es:[bx + 0x72d2], cl
0090 pop si
0091 pop di
0092 leave 
0093 retf 
0094 mov es, word ptr [0xc27a]
0098 mov bx, si
009a shl bx, 5
009d add bx, di
009f mov byte ptr es:[bx + 0x7ad2], cl
00a4 pop si
00a5 pop di
00a6 leave 
00a7 retf 
00a8 mov es, word ptr [0xc27a]
00ac shl si, 5
00af add si, di
00b1 mov byte ptr es:[si + 0x52d2], cl
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

- {'symbol': '_IsValidSLoc', 'offset': 36004, 'source': 'src/recovered/IsValidSLoc.c', 'size': 36}
- {'symbol': '_GetSM', 'offset': 36040, 'source': None, 'size': 193}
- {'symbol': '_clip_SetWin', 'offset': 36420, 'source': 'src/recovered/clip_SetWin.c', 'size': 1}
- {'symbol': '_clip_Off', 'offset': 36422, 'source': 'src/recovered/clip_Off.c', 'size': 1}

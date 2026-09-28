; Copy the selected rectangle of a mask bitmap into its destination.
; The source and destination rows are normalized through __AHINCR.
.186
EXTRN __AHINCR:ABS

_DATA SEGMENT WORD PUBLIC 'DATA'
CopyMaskSourceX DW 0
CopyMaskWidthX DW 0
CopyMaskSourceY DW 0
CopyMaskHeightY DW 0
CopyMaskDestinationStride DW 0
CopyMaskSourceStride DW 0
CopyMaskDestinationOffset DW 0
CopyMaskDestinationSegment DW 0
CopyMaskSourceOffset DW 0
CopyMaskSourceSegment DW 0
_DATA ENDS
DGROUP GROUP _DATA

SIMTWO_MODULE SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE, DS:DGROUP
PUBLIC _CopyMaskBitmap2
_CopyMaskBitmap2 PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es

    test WORD PTR [bp+16h], 8000h
    je copy_x_inside
    mov ax, WORD PTR [bp+16h]
    neg ax
    mov WORD PTR ds:[CopyMaskSourceX], ax
    mov ax, WORD PTR [bp+14h]
    mov WORD PTR ds:[CopyMaskWidthX], ax
    jmp SHORT copy_x_ready
copy_x_inside:
    mov ax, WORD PTR [bp+16h]
    cmp ax, WORD PTR [bp+10h]
    jl copy_x_negative
    jmp copy_done
copy_x_negative:
    mov WORD PTR ds:[CopyMaskSourceX], 0
    mov ax, WORD PTR [bp+16h]
    add ax, WORD PTR [bp+14h]
    cmp ax, WORD PTR [bp+10h]
    jle copy_x_clip_right
    mov ax, WORD PTR [bp+10h]
    sub ax, WORD PTR [bp+16h]
    mov WORD PTR ds:[CopyMaskWidthX], ax
    jmp SHORT copy_x_ready
copy_x_clip_right:
    mov ax, WORD PTR [bp+14h]
    mov WORD PTR ds:[CopyMaskWidthX], ax
copy_x_ready:
    test WORD PTR [bp+18h], 8000h
    je copy_y_inside
    mov ax, WORD PTR [bp+18h]
    neg ax
    mov WORD PTR ds:[CopyMaskSourceY], ax
    mov ax, WORD PTR [bp+12h]
    mov WORD PTR ds:[CopyMaskHeightY], ax
    jmp SHORT copy_y_ready
copy_y_inside:
    mov ax, WORD PTR [bp+18h]
    cmp ax, WORD PTR [bp+0Eh]
    jl copy_y_negative
    jmp copy_done
copy_y_negative:
    mov WORD PTR ds:[CopyMaskSourceY], 0
    mov ax, WORD PTR [bp+18h]
    add ax, WORD PTR [bp+12h]
    cmp ax, WORD PTR [bp+0Eh]
    jle copy_y_clip_bottom
    mov ax, WORD PTR [bp+0Eh]
    sub ax, WORD PTR [bp+18h]
    mov WORD PTR ds:[CopyMaskHeightY], ax
    jmp SHORT copy_y_ready
copy_y_clip_bottom:
    mov ax, WORD PTR [bp+12h]
    mov WORD PTR ds:[CopyMaskHeightY], ax
copy_y_ready:
    mov ax, WORD PTR ds:[CopyMaskSourceX]
    shr ax, 1
    mov WORD PTR ds:[CopyMaskSourceX], ax
    mov ax, WORD PTR ds:[CopyMaskWidthX]
    shr ax, 1
    mov WORD PTR ds:[CopyMaskWidthX], ax
    mov ax, WORD PTR [bp+10h]
    shl ax, 2
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    mov WORD PTR ds:[CopyMaskDestinationStride], ax
    mov ax, WORD PTR [bp+14h]
    shl ax, 2
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    mov WORD PTR ds:[CopyMaskSourceStride], ax

    les di, [bp+0Ah]
    mov ax, WORD PTR ds:[CopyMaskSourceY]
    mul WORD PTR ds:[CopyMaskSourceStride]
    add di, ax
    cmp dx, 0
    je copy_dest_row_ready
copy_dest_row_segment:
    mov ax, es
copy_dest_row_add_segment:
    add ax, OFFSET __AHINCR
    dec dx
    jne copy_dest_row_add_segment
    mov es, ax
copy_dest_row_ready:
    mov ax, es
    mov WORD PTR ds:[CopyMaskSourceSegment], ax
    mov WORD PTR ds:[CopyMaskSourceOffset], di

    les di, [bp+6]
    mov bx, WORD PTR [bp+16h]
    test bx, 8000h
    je copy_source_x_inside
    neg bx
    shr bx, 1
    neg bx
    xor bx, bx
    jmp SHORT copy_source_x_ready
copy_source_x_inside:
    shr bx, 1
copy_source_x_ready:
    mov ax, WORD PTR [bp+18h]
    add ax, WORD PTR ds:[CopyMaskSourceY]
    mul WORD PTR ds:[CopyMaskDestinationStride]
    add ax, bx
    add di, ax
    cmp dx, 0
    je copy_source_row_ready
copy_source_row_segment:
    mov ax, es
copy_source_row_add_segment:
    add ax, OFFSET __AHINCR
    dec dx
    jne copy_source_row_add_segment
    mov es, ax
copy_source_row_ready:
    mov ax, es
    mov WORD PTR ds:[CopyMaskDestinationSegment], ax
    mov WORD PTR ds:[CopyMaskDestinationOffset], di

copy_row_setup:
    mov cx, WORD PTR ds:[CopyMaskSourceY]
copy_row_loop:
    mov bx, WORD PTR ds:[CopyMaskSourceX]
    push WORD PTR ds:[CopyMaskDestinationOffset]
copy_pixel:
    les di, DWORD PTR ds:[CopyMaskSourceOffset]
    mov ah, BYTE PTR es:[bx+di]
    mov al, 0DDh
    test WORD PTR [bp+16h], 1
    je copy_even_nibble
    ror ax, 4
copy_even_nibble:
    les di, DWORD PTR ds:[CopyMaskDestinationOffset]
    cmp ah, 0DDh
    je copy_second_pixel
    xor dh, dh
    mov dl, ah
    and dl, 0Fh
    cmp dl, 0Dh
    jne copy_first_high_test
    or dh, 0Fh
    and ah, 0F0h
    jmp SHORT copy_first_merge
copy_first_high_test:
    mov dl, ah
    and dl, 0F0h
    cmp dl, 0D0h
    jne copy_first_merge
    or dh, 0F0h
    and ah, 0Fh
copy_first_merge:
    and BYTE PTR es:[di], dh
    or BYTE PTR es:[di], ah
copy_second_pixel:
    cmp al, 0DDh
    je copy_advance_pair
    xor dh, dh
    mov dl, al
    and dl, 0Fh
    cmp dl, 0Dh
    jne copy_second_high_test
    or dh, 0Fh
    and al, 0F0h
    jmp SHORT copy_second_merge
copy_second_high_test:
    mov dl, al
    and dl, 0F0h
    cmp dl, 0D0h
    jne copy_second_merge
    or dh, 0F0h
    and al, 0Fh
copy_second_merge:
    and BYTE PTR es:[di+1], dh
    or BYTE PTR es:[di+1], al
copy_advance_pair:
    inc WORD PTR ds:[CopyMaskDestinationOffset]
    inc bx
    cmp bx, WORD PTR ds:[CopyMaskWidthX]
    jl copy_pixel
    pop di
    add di, WORD PTR ds:[CopyMaskDestinationStride]
    jae copy_dest_next_row
copy_dest_next_segment:
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
copy_dest_next_row:
    mov ax, es
    mov WORD PTR ds:[CopyMaskDestinationSegment], ax
    mov WORD PTR ds:[CopyMaskDestinationOffset], di
    les di, DWORD PTR ds:[CopyMaskSourceOffset]
    add di, WORD PTR ds:[CopyMaskSourceStride]
    jae copy_source_next_row
copy_source_next_segment:
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
copy_source_next_row:
    mov ax, es
    mov WORD PTR ds:[CopyMaskSourceSegment], ax
    mov WORD PTR ds:[CopyMaskSourceOffset], di
    inc cx
    cmp cx, WORD PTR ds:[CopyMaskHeightY]
    jge copy_done
    jmp copy_row_loop
copy_done:
    pop es
    pop ds
    popa
    pop bp
    retf
_CopyMaskBitmap2 ENDP
SIMTWO_MODULE ENDS
END


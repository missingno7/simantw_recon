; Host-only DOS launcher. Does not enter reconstructed game objects.
; NASM -f bin tools/capture_cl.asm -o toolchain/CAPCL.COM
; Inherits its command tail, merges child stderr into stdout, runs authentic CL.
bits 16
org 100h
mov bx,1
mov cx,2
mov ah,46h
int 21h
mov ax,cs
mov [params+4],ax
mov [params+8],ax
mov [params+12],ax
mov sp,1000h
mov bx,100h
mov ah,4ah
int 21h
mov bx,params
mov dx,program
mov ax,4b00h
int 21h
jc failed
mov ah,4dh
int 21h
mov ah,4ch
int 21h
failed:
mov ax,4cffh
int 21h
params: dw 0,80h,0,5ch,0,6ch,0
program: db 'T:\BIN\CL.EXE',0

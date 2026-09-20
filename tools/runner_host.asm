; Host experiment only. Start a resident DPMI host, then the unchanged C7 driver.
; Runs inside one DOS process environment, never linked into recovered objects.
bits 16
org 100h
mov sp,2000h
mov bx,200h
mov ah,4ah
int 21h
mov ax,cs
mov [params+4],ax
mov [params+8],ax
mov [params+12],ax
mov bx,params
mov dx,host
mov ax,4b00h
int 21h
jc failed
push cs
pop ds
push cs
pop es
mov word [params+2],80h
mov bx,params
mov dx,compiler
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
params: dw 0,tail,0,5ch,0,6ch,0
%ifdef CWSDPMI
host: db 'CWSDPMI.EXE',0
tail: db 3,' -p',13
%else
host: db 'HDPMI32.EXE',0
tail: db 3,' -r',13
%endif
compiler: db 'CL.EXE',0

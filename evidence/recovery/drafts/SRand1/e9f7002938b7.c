extern unsigned int near edata[];

/* Galois LFSR step on the shared random seed (polynomial 0x1BF5), written as
   inline assembly: returns the new seed modulo range */
int SRand1(unsigned int range)
{
    int result;

    _asm {
        mov dx, 0
        mov ax, word ptr edata[402]
        shl ax, 1
        jnc done
        xor ax, 1bf5h
    done:
        mov word ptr edata[402], ax
        mov bx, range
        div bx
        mov ax, dx
        mov result, ax
    }
    return result;
}

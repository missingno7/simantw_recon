static unsigned int seed;

/* Galois LFSR step on the shared seed (polynomial 0x1BF5), written as inline
   assembly in the original; returns the new seed modulo range. */
int SRand1(unsigned int range)
{
    int result;

    _asm {
        mov dx, 0
        mov ax, seed
        shl ax, 1
        jnc done
        xor ax, 1bf5h
    done:
        mov seed, ax
        mov bx, range
        div bx
        mov ax, dx
        mov result, ax
    }
    return result;
}

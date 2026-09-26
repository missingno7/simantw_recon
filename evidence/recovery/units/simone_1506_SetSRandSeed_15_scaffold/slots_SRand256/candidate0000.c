static unsigned int seed;

/* Galois LFSR step on the shared seed (polynomial 0x1BF5), written as inline
   assembly in the original; returns its low bits, 0..255. */
int SRand256(void)
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
        and ax, 255
        mov result, ax
    }
    return result;
}

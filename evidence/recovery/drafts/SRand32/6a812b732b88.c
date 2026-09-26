extern unsigned int near edata[];

/* Galois LFSR step on the shared random seed (polynomial 0x1BF5), written as
   inline assembly: returns its low bits, 0..31 */
int SRand32(void)
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
        and ax, 31
        mov result, ax
    }
    return result;
}

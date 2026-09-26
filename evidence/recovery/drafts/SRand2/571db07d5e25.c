extern unsigned int near edata[];

int SRand2(void)
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
        and ax, 1
        mov result, ax
    }
    return result;
}

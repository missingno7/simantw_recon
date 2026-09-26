/* Random-seed translation unit: the admitted six members plus SRand1..SRand256, whose
 * bodies are inline assembly in the original (hand-written "mov dx,0", carry branch). */

extern unsigned long far TickCount(void);
extern void far srand(unsigned int value);
extern int far rand(void);


void SeedSRand(void);
void SeedRRand(void);
int RRand(int limit);
int SRand1(unsigned int range);
int SRand2(void);
int SRand4(void);
int SRand8(void);
int SRand16(void);
int SRand32(void);
int SRand64(void);
int SRand128(void);
int SRand256(void);

#pragma alloc_text(RUN2_TEXT, SeedSRand, SeedRRand, RRand, SRand1, SRand2, SRand4, SRand8, SRand16, SRand32, SRand64, SRand128, SRand256)

static unsigned int seed;
void SetSRandSeed(int value)
{
    seed = value;
}

unsigned long GetSRandSeed(void)
{
    return (unsigned long)(unsigned int)seed;
}

void SetRRandSeed(void)
{
}

void SeedSRand(void)
{
    seed = (unsigned int)TickCount() ^ 0x3751;
}

void SeedRRand(void)
{
    union { unsigned long whole; unsigned int part[2]; } tick;
    int count;
    tick.whole = TickCount();
    seed = tick.part[0] ^ 0x3751;
    count = SRand128();
    srand((unsigned int)TickCount());
    if (count > 0) {
        int left = count;
        do { rand(); --left; } while (left != 0);
    }
}

int RRand(int limit) { int v=rand(); if(v<0) v=-v; return v%limit; }


/* Galois LFSR step on seed (polynomial 0x1BF5); returns the new seed modulo range. */
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

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..1. */
int SRand2(void)
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
        and ax, 1
        mov result, ax
    }
    return result;
}

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..3. */
int SRand4(void)
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
        and ax, 3
        mov result, ax
    }
    return result;
}

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..7. */
int SRand8(void)
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
        and ax, 7
        mov result, ax
    }
    return result;
}

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..15. */
int SRand16(void)
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
        and ax, 15
        mov result, ax
    }
    return result;
}

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..31. */
int SRand32(void)
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
        and ax, 31
        mov result, ax
    }
    return result;
}

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..63. */
int SRand64(void)
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
        and ax, 63
        mov result, ax
    }
    return result;
}

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..127. */
int SRand128(void)
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
        and ax, 127
        mov result, ax
    }
    return result;
}

/* Galois LFSR step on seed (polynomial 0x1BF5); returns its low bits, 0..255. */
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

/* Candidate translation unit simone_1506_SetSRandSeed_15_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _SetSRandSeed, _GetSRandSeed, _SetRRandSeed, _SeedSRand, _SeedRRand, _RRand, _SRand1, _SRand2, _SRand4, _SRand8, _SRand16, _SRand32, _SRand64, _SRand128, _SRand256
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern unsigned long far TickCount(void);
extern int far SRand128(void);
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

#pragma alloc_text(RUN2_TEXT, SeedSRand, SeedRRand, RRand, SRand1)
#pragma alloc_text(RUN2_TEXT, SRand2, SRand4, SRand8, SRand16)
#pragma alloc_text(RUN2_TEXT, SRand32, SRand64, SRand128, SRand256)

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


/*
 * Hypothesis: walk the nonzero B-hole entries in Dx8[0x82d2].  For each
 * entry, test the corresponding MapA tile (a 64-byte row stride) for the
 * hole marker 0x51.  Matching entries seed the Dx8 scent band at 0x62d2;
 * the target's DS/ES liveness is represented by the far Dx8 declaration and
 * the near MapA declaration.
 */
extern unsigned char far Dx8[];
extern unsigned char near MapA[];

void far FillHolesBN(void)
{
    int index;
    unsigned char kind;

    index = 0;
    while (Dx8[0x82d2 + index] != 0) {
        kind = Dx8[0x82d2 + index];
        if (MapA[((unsigned int)kind << 6) + index] == 0x51)
            Dx8[0x62d2 + ((kind & 0xfe) << 4) + (index >> 1)] = 0xff;
        ++index;
    }
}

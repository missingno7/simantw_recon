/*
 * Paired R-plane hypothesis: walk the nonzero Dx8[0x8312+i] entries,
 * inspect MapA[(kind << 6) + i], and write the R scent byte at 0x72d2.
 * The BN twin establishes the same 0x51 branch, word kind spill, 0x40
 * bound, near return, and unresolved DS/ES/private MapA layout obligations.
 */
extern unsigned char far Dx8[];
extern unsigned char near MapA[];

void near FillHolesRN(void)
{
    int index;
    volatile int kind;

    index = 0;
    do {
        if (Dx8[0x8312 + index] == 0)
            break;
        kind = Dx8[0x8312 + index];
        if (MapA[(kind << 6) + index] != 0x51)
            Dx8[0x72d2 + ((kind & 0xfe) << 4) + (index >> 1)] = 0xff;
        else
            Dx8[0x72d2 + ((kind & 0xfe) << 4) + (index >> 1)] = 0;
        ++index;
    } while (index < 0x40);
}

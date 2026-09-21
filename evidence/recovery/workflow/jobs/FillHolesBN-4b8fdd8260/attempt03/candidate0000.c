/*
 * Hypothesis: walk the nonzero B-hole entries in Dx8[0x82d2].  For each
 * entry, test the corresponding MapA tile (a 64-byte row stride) for the
 * hole marker 0x51.  Matching entries seed the Dx8 scent band at 0x62d2;
 * the target's DS/ES liveness is represented by the far Dx8 declaration and
 * the near MapA declaration.
 */
extern unsigned char far Dx8[];
extern unsigned char near MapA[];

void near FillHolesBN(void)
{
    int index;
    int kind;
    unsigned char far *list;
    unsigned char far *scent;

    index = 0;
    list = Dx8;
    scent = Dx8;
    do {
        if (list[0x82d2 + index] == 0)
            break;
        kind = list[0x82d2 + index];
        if (MapA[(kind << 6) + index] != 0x51)
            scent[0x62d2 + ((kind & 0xfe) << 4) + (index >> 1)] = 0xff;
        else
            scent[0x62d2 + ((kind & 0xfe) << 4) + (index >> 1)] = 0;
        ++index;
    } while (index < 0x40);
}

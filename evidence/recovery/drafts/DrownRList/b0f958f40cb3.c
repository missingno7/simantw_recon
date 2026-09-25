/* Semantic hypothesis: R-list mirror of the strict B-list walk. */
/* Descend through matching live entries and mark validated status kinds drowned. */
extern int far ListIndexR;
extern unsigned char far Dx8[];

void DrownRList(int listKind)
{
    int index;
    int state;

    index = ListIndexR;
    if (index > 0) {
        do {
            --index;
            if (Dx8[index + 0x42fa] != listKind)
                continue;
            if (Dx8[index + 0x46e6] == 0)
                continue;
            state = Dx8[index + 0x46e6];
            state = (state & 0x78) >> 3;
            if (state <= 0 || state >= 0x0c)
                continue;
            Dx8[index + 0x44f0] = 0x11;
        } while (index > 0);
    }
}

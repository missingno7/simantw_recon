/* Semantic hypothesis: preserve word-sized state promotion after a direct byte guard. */
/* Mark live matching entries with a validated packed kind. */
extern int far ListIndexB;
extern unsigned char far Dx8[];

void DrownBList(int listKind)
{
    int index;
    int state;

    index = ListIndexB;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x392c] != listKind)
            continue;
        if (Dx8[index + 0x3d18] == 0)
            continue;
        state = Dx8[index + 0x3d18];
        state = (state & 0x78) >> 3;
        if (state <= 0 || state >= 0x0c)
            continue;
        Dx8[index + 0x3b22] = 0x11;
    }
}

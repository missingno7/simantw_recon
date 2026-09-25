/*
 * Clear the R-life cell for a coordinate after removing matching stale list
 * entries.  ListIndexR is the exclusive R-list bound; the records live in
 * the separately selected Dx8 segment and use the symmetric R-list fields.
 */
extern int far ListIndexR;
extern unsigned char far Dx8[];
extern unsigned char near LifeR[];

void far ClearLifeR(int life, int column)
{
    int index;

    index = ListIndexR;
    while (index) {
        --index;
        if (Dx8[index + 0x46e6] != 0 &&
            Dx8[index + 0x4104] == life &&
            Dx8[index + 0x42fa] == column)
            Dx8[index + 0x46e6] = 0;
    }

    LifeR[((unsigned int)life << 6) + column] = 0;
}

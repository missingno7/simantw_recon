/*
 * Clear the B-life cell for a coordinate after removing matching stale list
 * entries.  ListIndexB is a far DGROUP handle to the exclusive B-list bound;
 * the list records live in the separately selected Dx8 segment.  The three
 * observed record fields are occupancy, life kind, and life column.
 */
extern int far ListIndexB;
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];

void far ClearLifeB(int life, int column)
{
    int index;

    index = ListIndexB;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x3d18] != 0 &&
            Dx8[index + 0x3736] == life &&
            Dx8[index + 0x392c] == column)
            Dx8[index + 0x3d18] = 0;
    }

    LifeB[((unsigned int)life << 6) + column] = 0;
}

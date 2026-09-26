/*
 * ColonySmellBN ages every nonzero byte in PherMapBN once. The 64-by-32
 * based map is visited as 64 rows of 32 scent cells.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBN[64][32];

void near ColonySmellBN(void)
{
    int row;
    int cell;

    for (row = 0; row < 64; ++row) {
        for (cell = 0; cell < 32; ++cell) {
            if (PherMapBN[row][cell] != 0)
                --PherMapBN[row][cell];
        }
    }
}

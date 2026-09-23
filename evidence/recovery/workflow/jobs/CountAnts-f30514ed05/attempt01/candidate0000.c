/*
 * Hypothesis: count live entries from the three colony lists into the named
 * TemCensus PACK array, then derive the five caste totals for each colony.
 * ListIndexA/B/R are word counts; each record's caste byte is read from its
 * established Dx8 field.  MeMode gates the player-ant contribution, while
 * MeColor selects its red-colony census band.  MAPSYM-backed far globals name
 * the census, game mode, transfer flag, and victory state.
 */
extern int far ListIndexA, ListIndexB, ListIndexR;
extern int far TemCensus[];
extern unsigned char far Dx8[];
extern int near CastePopB[], CastePopR[];
extern int near BpopT, RpopT, MeColor, MeType;
extern int far MeMode, CurGameType, JustXfered, IsGameOver, BlackWon;
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far PictStrnDialog(int picture, int object, int force);
extern int far SRand1(int range);

static void count_list(int count, int field)
{
    int i;
    int caste;

    i = count;
    while (i > 0) {
        --i;
        caste = Dx8[i + field];
        if (caste != 0) {
            caste &= 0xfffb;
            caste >>= 2;
            ++TemCensus[caste];
        }
    }
}

void far CountAnts(void)
{
    int i;
    int caste;

    for (i = 0; i < 32; ++i)
        TemCensus[i] = 0;

    count_list(ListIndexA, 0x2f62);
    count_list(ListIndexB, 0x3d18);
    count_list(ListIndexR, 0x46e6);

    if (MeMode == 0) {
        caste = MeType & 0xfffb;
        if (MeColor != 0)
            caste |= 0x80;
        ++TemCensus[caste >> 2];
    }

    CastePopB[0] = TemCensus[0];
    CastePopB[1] = TemCensus[1] + TemCensus[2] + TemCensus[3] + TemCensus[5];
    CastePopB[2] = TemCensus[6] + TemCensus[7] + TemCensus[9];
    CastePopB[3] = TemCensus[4];
    CastePopB[4] = TemCensus[8];

    if (CastePopB[5] == 0 && TemCensus[12] == 0 && JustXfered == 0) {
        myBeginSong(0x2b0c, 0x7e);
        PictStrnDialog(0, 0x271a, 1);
        if (CurGameType <= 1)
            PictStrnDialog(0, 0x271b, 1);
        IsGameOver = 1;
        BlackWon = 0;
    }

    CastePopR[0] = TemCensus[16];
    CastePopR[1] = TemCensus[17] + TemCensus[18] + TemCensus[19] + TemCensus[21];
    CastePopR[2] = TemCensus[22] + TemCensus[23] + TemCensus[25];
    CastePopR[3] = TemCensus[20];
    CastePopR[4] = TemCensus[24];

    if (CastePopR[5] == 0 && TemCensus[28] == 0 && JustXfered == 0) {
        myBeginSong(0x2b0d, 0x7e);
        PictStrnDialog(0, 0x271c, 1);
        if (CurGameType <= 1)
            PictStrnDialog(0, 0x271d, 1);
        IsGameOver = 1;
        BlackWon = 1;
    }

    if (CurGameType == 2 && TemCensus[0] == -1 &&
        TemCensus[0] == 0x0b && TemCensus[1] == 8)
        Dx8[SRand1(6) * 16 + 0x184] = 0x14;

    BpopT = CastePopB[1] + CastePopB[2] + CastePopB[3] +
            CastePopB[4] + CastePopB[5];
    CastePopR[5] = TemCensus[28];
    RpopT = CastePopR[0] + CastePopR[1] + CastePopR[2] +
            CastePopR[3] + CastePopR[4];
    JustXfered = 0;
}

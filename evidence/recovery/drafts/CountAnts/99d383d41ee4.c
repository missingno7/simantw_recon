/*
 * Hypothesis: count live entries from the three colony lists into the named
 * TemCensus PACK array, then derive the five caste totals for each colony.
 * ListIndexA/B/R are word counts; each record's caste byte is read from its
 * established Dx8 field.  MeMode gates the player-ant contribution, while
 * MeColor selects its red-colony census band.  MAPSYM-backed far globals name
 * the census, game mode, transfer flag, and victory state.
 */
extern int far ListIndexA, ListIndexB, ListIndexR;
extern int far pack_buf;
extern unsigned char far TemCensus[];
extern unsigned char far Dx8[];
extern unsigned char far YMapPopR[];
extern int near CastePopB[];
extern int near CastePopR[];
extern int near BpopT;
extern int near RpopT;
extern int near MeColor;
extern int near MeType;
extern int far MeMode, CurGameType, JustXfered, IsGameOver, BlackWon;
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far PictStrnDialog(int picture, int object, int force);
extern int far SRand1(int range);

void far CountAnts(void)
{
    int i;
    int caste;

    CastePopR[0] = 0;
    CastePopB[0] = 0;

    for (i = 0; i < 32; ++i)
        ((unsigned int far *)TemCensus)[i] = 0;

    i = ListIndexA;
    if (i > 0) do {
        --i;
        caste = Dx8[i + 0x2f62];
        if (caste != 0) {
            caste &= 0xfffb;
            caste >>= 2;
            ++*((unsigned int far *)(TemCensus + caste));
        }
    } while (i > 0);

    i = ListIndexB;
    if (i > 0) do {
        --i;
        caste = Dx8[i + 0x3d18];
        if (caste != 0) {
            caste &= 0xfffb;
            caste >>= 2;
            ++*((unsigned int far *)(TemCensus + caste));
        }
    } while (i > 0);

    i = ListIndexR;
    if (i > 0) do {
        --i;
        caste = Dx8[i + 0x46e6];
        if (caste != 0) {
            caste &= 0xfffb;
            caste >>= 2;
            ++*((unsigned int far *)(TemCensus + caste));
        }
    } while (i > 0);

    if (MeMode == 0) {
        if (MeColor == 0)
            ++*((unsigned int far *)(TemCensus + ((int)(MeType & 0xfffb) >> 2)));
        else
            ++*((unsigned int far *)(TemCensus + ((int)((MeType & 0xfffb) | 0x80) >> 2)));
    }

    CastePopB[0] = ((unsigned int far *)TemCensus)[0];
    CastePopB[1] = ((unsigned int far *)TemCensus)[1] + ((unsigned int far *)TemCensus)[2] + ((unsigned int far *)TemCensus)[3] + ((unsigned int far *)TemCensus)[5];
    CastePopB[2] = ((unsigned int far *)TemCensus)[6] + ((unsigned int far *)TemCensus)[7] + ((unsigned int far *)TemCensus)[9];
    CastePopB[3] = ((unsigned int far *)TemCensus)[4];
    CastePopB[4] = ((unsigned int far *)TemCensus)[8];

    if (CastePopB[5] != 0 && ((unsigned int far *)TemCensus)[12] == 0 && JustXfered == 0) {
        myBeginSong(0x2b0c, 0x7e);
        PictStrnDialog(0, 0x271a, 1);
        if (CurGameType <= 1)
            PictStrnDialog(0, 0x271b, 1);
        IsGameOver = 1;
        BlackWon = 0;
    }

    CastePopR[0] = ((unsigned int far *)TemCensus)[16];
    CastePopR[1] = ((unsigned int far *)TemCensus)[17] + ((unsigned int far *)TemCensus)[18] + ((unsigned int far *)TemCensus)[19] + ((unsigned int far *)TemCensus)[21];
    CastePopR[2] = ((unsigned int far *)TemCensus)[22] + ((unsigned int far *)TemCensus)[23] + ((unsigned int far *)TemCensus)[25];
    CastePopR[3] = ((unsigned int far *)TemCensus)[20];
    CastePopR[4] = ((unsigned int far *)TemCensus)[24];

    if (CastePopR[5] == 0 && ((unsigned int far *)TemCensus)[28] == 0 && JustXfered == 0) {
        myBeginSong(0x2b0d, 0x7e);
        PictStrnDialog(0, 0x271c, 1);
        if (CurGameType <= 1)
            PictStrnDialog(0, 0x271d, 1);
        IsGameOver = 1;
        BlackWon = 1;
    }

    if (CurGameType == 2 && ((unsigned char far *)&pack_buf)[0x3d2c] == 0x0b &&
        ((unsigned char far *)&pack_buf)[0x3d2d] == 8)
        YMapPopR[SRand1(6) * 16 + 0x184] = 0x14;

    BpopT = CastePopB[1] + CastePopB[2] + CastePopB[3] +
            CastePopB[4] + CastePopB[5];
    CastePopR[5] = ((unsigned int far *)TemCensus)[28];
    RpopT = CastePopR[0] + CastePopR[1] + CastePopR[2] +
            CastePopR[3] + CastePopR[4];
    JustXfered = 0;
}


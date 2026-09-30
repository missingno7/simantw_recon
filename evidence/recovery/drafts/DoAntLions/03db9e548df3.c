/*
 * DoAntLions: create the first ant lion when the scenario requests one, then
 * update every live lion. State M=0 checks the cell and nearby ants and may
 * move the lion into an adjacent food/pebble cell; M=1 checks the eight-cell
 * ring and advances its emergence timer; M=2 counts down and records a lion
 * completion, with a periodic chance to add another lion.
 */
extern int far LionIndex;
extern int far InitialLions;
extern int far AntsEatenByLions;
extern long far BAntsEaten;

extern long far RAntsEaten;

extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern unsigned char far LionListT[];
extern char far Dx8[];
extern char far Dy8[];
extern char far Dx9[];
extern char far Dy9[];
extern unsigned char LifeA[];
extern int near MeDir;

extern int near MeType;


extern int far SRand1(int range);
extern int far SRand8(void);
extern int far IsClear3x3(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);
extern int far GetMap(int plane, int x, int y);
extern int far IsThisPebble(int category, int tile);
extern int far IsThisFood(int category, int tile);
extern int far IsYellowAnt(int tile);
extern int far FindInAList(int x, int y);
extern void far RemoveFromAList(int index);
extern void far SetMap(int plane, int x, int y, int value);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern void far YellowDeath(int reason);
extern void far myBeginSound(int sound, int channel, int duration);
extern void far myBeginSoundSection(int id, int p2, int p3, int p4,
                                    int duration, int p6, int p7);
extern void far PictStrnDialog(int flags, int message, int mode);

struct EatenPointer { int far *value; };

static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};

void far DoAntLions(void)
{
    int x;
    int y;
    int i;
    int j;
    int direction;
    int lx;
    int ly;
    int tile;
    int adjacentTile;
    int found;
    int count;
    int listIndex;
    int oldIndex;
    unsigned char far *pLionX;
    unsigned char far *pLionY;
    unsigned char far *pLionM;
    unsigned char far *pLionT;
    struct EatenPointer eatenPointer;

    /* The empty-list path occasionally lays down the scenario's first lion. */
    if (LionIndex == 0) {
        if (InitialLions > 0 && SRand1(0x400) == 0) {
            i = 0;
            for (;;) {
                x = SRand1(0x40) + SRand1(0x41);
                y = SRand1(0x20) + SRand1(0x21);
                if (IsClear3x3(1, x, y) == 1)
                    break;
                if (IsClearTile(1, x, y) == 1 && i >= 100)
                    break;
                i++;
                if (i >= 200)
                    return;
            }

            SetMap(1, x, y, 0x38);
            for (i = 0; i < 8; i++) {
                ly = y + Dy8[i];
                lx = x + Dx8[i];
                if (IsClearTile(1, lx, ly) == 1)
                    SetMap(1, lx, ly, lionRing[i] + 0x30);
            }

            LionListX[LionIndex] = x;
            LionListY[LionIndex] = y;
            LionListM[LionIndex] = 0;
            LionListS[LionIndex] = 0;
            LionListT[LionIndex] = 0;
            if (LionIndex < 9)
                LionIndex++;
            return;
        }
    }

    /* Each live entry takes one of the three observed update paths. */
    for (i = 0; i < LionIndex; i++) {
        pLionM = &LionListM[i];
        switch (*pLionM) {
        case 0: {
            pLionY = &LionListY[i];
            pLionX = &LionListX[i];
            pLionT = &LionListT[i];
            y = *pLionY;
            x = *pLionX;
            tile = GetMap(1, x, y);

            /* Food or a pebble lets the lion trade places with a clear cell. */
            if (IsThisPebble(1, tile) == 1 || IsThisFood(1, tile) == 1) {
                if (SRand1(0x200) != 0)
                    continue;

                direction = SRand8();
                for (j = 0; j < 8; j++) {
                    ly = y + Dy8[direction];
                    lx = x + Dx8[direction];
                    if (IsClearTile(1, lx, ly) == 1) {
                        SetMap(1, lx, ly, tile);
                        myBeginSound(0x1e, 0, 10);
                        myBeginSoundSection(0x26, 0, 0, 0,
                                            0x1770, 0, 10);
                        LionListS[i] = 0x19;
                        *pLionM = 1;
                        *pLionT = 1;
                        SetMap(1, LionListX[i], LionListY[i], LionListT[i] + 0x38);
                        break;
                    }
                    direction = (direction + 1) & 7;
                }
                continue;
            }

            /* Look in two random cells from the lion's nine-cell direction
               table; a yellow ant is driven away, while another ant is eaten. */
            for (j = 0, direction = 0; j < 2; ) {
                ly = y + Dy9[direction];
                lx = x + Dx9[direction];
                adjacentTile = LifeA[(ly << 6) + lx];
                if (adjacentTile == 0) {
                    j++;
                    direction = SRand1(8) + 1;
                    continue;
                }

                if (IsYellowAnt(adjacentTile) == 1) {
                    MoveMyLife(1, LionListX[i], LionListY[i], MeType, MeDir);
                    YellowDeath(2);
                } else {
                    if (SRand8() == 0)
                        myBeginSoundSection(0x26, 0, 0, 0,
                                            0x1770, 0, 10);
                    listIndex = FindInAList(lx, ly);
                    if (listIndex >= 0)
                        RemoveFromAList(listIndex);
                    if (adjacentTile & 0x80)
                        RAntsEaten++;
                    else
                        BAntsEaten++;
                }
                LionListS[i] = 0x32;
                LionListM[i] = 1;
                LionListT[i] = 1;
                break;
            }
            continue;
        }

        case 1: {
            pLionX = &LionListX[i];
            pLionY = &LionListY[i];
            pLionT = &LionListT[i];
            x = *pLionX;
            y = *pLionY;
            count = 0;
            for (j = 0; j < 8; j++) {
                lx = x + Dx8[j];
                ly = y + Dx8[j + 8];
                if (LifeA[(ly << 6) + lx] != 0)
                    count++;
            }

            /* Seven occupied neighbours crush the ant lion and remove its
               slot, compacting all five parallel lion lists. */
            if (count >= 7) {
                PictStrnDialog(0, 0x2742, 0);
                SetMap(1, x, y, 0x3f);
                if (LionIndex > 0) {
                    LionIndex--;
                    for (listIndex = i; listIndex < LionIndex; listIndex++) {
                        LionListX[listIndex] = LionListX[listIndex + 1];
                        LionListY[listIndex] = LionListY[listIndex + 1];
                        LionListT[listIndex] = LionListT[listIndex + 1];
                        LionListM[listIndex] = LionListM[listIndex + 1];
                        LionListS[listIndex] = LionListS[listIndex + 1];
                    }
                }
                continue;
            }

            if (*pLionT < 4) {
                (*pLionT)++;
                continue;
            }
            if (LionListS[i] != 0) {
                LionListS[i]--;
                if (LionListS[i] & 1)
                    continue;
                *pLionT = SRand1(4) + 3;
                continue;
            }
            *pLionM = 2;
            *pLionT = 4;
            continue;
        }

        case 2: {
            pLionT = &LionListT[i];
            if (*pLionT != 0) {
                (*pLionT)--;
                continue;
            }

            eatenPointer.value = &AntsEatenByLions;
            *pLionM = 0;
            (*eatenPointer.value)++;
            if (LionIndex >= 9 || (*eatenPointer.value & 0x0f) != 0x0f)
                continue;

            /* Every fifteenth completed lion can seed another colony entry. */
            oldIndex = i;
            i = 0;
            for (;;) {
                x = SRand1(0x40) + SRand1(0x41);
                y = SRand1(0x20) + SRand1(0x21);
                if (IsClear3x3(1, x, y) == 1)
                    break;
                if (IsClearTile(1, x, y) == 1 && i >= 100)
                    break;
                i++;
                if (i >= 200) {
                    i = oldIndex;
                    goto next_lion;
                }
            }

            SetMap(1, x, y, 0x38);
            for (j = 0; j < 8; j++) {
                ly = y + Dx8[j + 8];
                lx = x + Dx8[j];
                if (IsClearTile(1, lx, ly) == 1)
                    SetMap(1, lx, ly, lionRing[j] + 0x30);
            }

            LionListX[LionIndex] = x;
            LionListY[LionIndex] = y;
            LionListM[LionIndex] = 0;
            LionListS[LionIndex] = 0;
            LionListT[LionIndex] = 0;
            if (LionIndex < 9)
                LionIndex++;
            SetMap(1, LionListX[oldIndex], LionListY[oldIndex],
                   LionListT[oldIndex] + 0x38);
            i = oldIndex;
        }
        }
next_lion:
        ;
    }
}

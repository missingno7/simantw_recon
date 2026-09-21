/*
 * AddAntLion: place a new ant lion at yard cell (x, y).  The cell gets
 * tile 0x38 and each of the eight neighbours (Dx8/Dy8 offsets) that is a
 * clear tile gets one of the private ring tiles 0x30 + {1,2,4,7,6,5,3,0}
 * (DGROUP bytes at 0x25e8).  The lion is appended to the five far lion
 * lists (x, y, mode 0, stamina 0, type 0) at LionIndex, which grows
 * while below 9.  The compiler keeps the Dx8 segment in DS for the tail
 * and reloads the list segment per store.
 */
static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};

extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern unsigned char far LionListT[];
extern int far LionIndex;

extern void far SetMap(int plane, int x, int y, int value);
extern int far IsClearTile(int plane, int x, int y);

void far AddAntLion(int x, int y)
{
    int i;
    int lx;
    int ly;

    SetMap(1, x, y, 0x38);
    for (i = 0; i < 8; i++) {
        if (IsClearTile(1, lx = x + Dx8[i], ly = y + Dy8[i]) == 1)
            SetMap(1, lx, ly, lionRing[i] + 0x30);
    }
    LionListX[LionIndex] = x;
    LionListY[LionIndex] = y;
    LionListM[LionIndex] = 0;
    LionListS[LionIndex] = 0;
    LionListT[LionIndex] = 0;
    if (LionIndex < 9)
        LionIndex++;
}

/* FootFall(x, y): play the footstep sound, then scan a directional
 * rectangle of tiles for ants and kill them.  BoyDir&1 selects a wide
 * (16 rows x 6 cols) vs tall (6 rows x 16 cols) rectangle starting at
 * (x,y).  Each in-range tile (row*64 in [0,0x1fc0], col in [0,0x7f])
 * with a nonzero LifeA byte either kills a yellow ant (YellowDeath(5))
 * or, for an ordinary ant, resolves it through FindInAList, notifies
 * DeadAntHere with its team bit and clears its AlistT flag.  Finally,
 * if the entity at SuserX/SuserY falls inside the scanned rectangle, KillSpider() is
 * called too, and if MeMode==1 that also triggers YellowDeath(5).
 */

extern int far BoyDir;
extern unsigned char near LifeA[128][64];
extern int far SuserX;
extern int far SuserY;

extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern int far MeMode;

extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far IsYellowAnt(int ant);
extern void far YellowDeath(int code);
extern int far FindInAList(int x, int y);
extern void far DeadAntHere(int x, int y, int flags);
extern void far KillSpider(void);

void far FootFall(int x, int y)
{
    int rowEnd;
    int colStart, colEnd;
    int row, col;
    int rowBase;
    int terrain;
    int found;

    myBeginSound(0x23, 0, 0x14);

    if (BoyDir & 1) {
        rowEnd = x + 0x10;
        colEnd = y + 6;
    } else {
        rowEnd = x + 6;
        colEnd = y + 0x10;
    }

    for (row = x; row < rowEnd; row++) {
            rowBase = row << 6;
            for (col = y; col < colEnd; col++) {
                if (rowBase < 0 || rowBase > 0x1fc0 || col < 0 || col > 0x7f)
                    continue;
                terrain = ((unsigned char far *)LifeA)[rowBase + col];
                if (terrain == 0)
                    continue;
                if (IsYellowAnt(terrain)) {
                    YellowDeath(5);
                    continue;
                }
                found = FindInAList(row, col);
                if (found < 0)
                    continue;
                DeadAntHere(row, col, AlistT[found] & 0x80);
                AlistT[found] = 0;
            }
    }

    if (SuserX >= x && SuserX < rowEnd && SuserY >= y && SuserY < colEnd) {
        KillSpider();
        if (MeMode == 1)
            YellowDeath(5);
    }
}

/* Fold the column origin into the inner-loop initializer. */

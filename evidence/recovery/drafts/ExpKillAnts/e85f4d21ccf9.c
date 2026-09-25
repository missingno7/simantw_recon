/*
 * ExpKillAnts: experimental map-editor tool that kills ants (and
 * incidentally the spider or an ant lion) near (x, y), eight times per
 * call.  Experiment sub-state 6 selects the mode for every iteration:
 * set means an exact single-cell placement at (x, y) with no sound
 * pitch; clear means a cell randomised within +/-4 of (x, y) and a
 * pitched placement sound.  Each iteration validates the cell on the
 * current MapPlane, then dispatches on the plane: 0/1 clears the A
 * list/life entry at that cell (playing DeadAntHere first), also
 * killing the spider if it occupies the same cell and, for a
 * wall/antlion-range tile, the ant lion there too; plane 2/3 clear the
 * matching B/R list/life entry.  match_position is used as a shared
 * scratch slot for the just-found list index.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far Dx8[];
extern int far match_position[];
extern int near MapPlane;
extern unsigned char far ExpSubStates[];
extern int near SpidX;
extern int near SpidY;

extern int far pascal GetAsyncKeyState(unsigned int key);
extern int far SRand1(int range);
extern int far IsValidLocation(int plane, int x, int y);
extern int far FindInAList(int x, int y);
extern int far FindInBList(int x, int y, int ant);
extern int far FindInRList(int x, int y, int ant);
extern void far DeadAntHere(int x, int y, int flag);
extern void far KillSpider(void);
extern int far FindInLionList(int x, int y);
extern void far KillAntLion(int lion);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

void far ExpKillAnts(int x, int y)
{
    int count;
    int mode;
    int cellIndex;
    int si;
    int di;

    if (ExpSubStates[6] == 0)
        mode = 8;
    else
        mode = 1;

    for (count = 8; count != 0; count--) {
        if (mode != 1) {
            si = SRand1(9) + x - 4;
            di = SRand1(9) + y - 4;
            myBeginSound(9, SRand1(1000) + 0x278f, 0x7e);
        } else {
            si = x;
            di = y;
            myBeginSound(9, 0, 0x7e);
        }

        if (!IsValidLocation(MapPlane, si, di))
            continue;

        if (MapPlane <= 1) {
            cellIndex = (si << 6) + di;
            if (LifeA[si][di] != 0) {
                match_position[0x4db5] = FindInAList(si, di);
                if (match_position[0x4db5] >= 0) {
                    DeadAntHere(si, di, Dx8[match_position[0x4db5] + 0x2f62] & 0x80);
                    Dx8[match_position[0x4db5] + 0x2f62] = 0;
                    LifeA[si][di] = 0;
                }
                if (SpidX >> 4 == si && SpidY >> 4 == di)
                    KillSpider();
                if (MapA[si][di] >= 0x38 && MapA[si][di] <= 0x3e)
                    KillAntLion(FindInLionList(si, di));
            }
        } else if (MapPlane == 2) {
            cellIndex = (si << 6) + di;
            if (LifeB[cellIndex] != 0) {
                match_position[0x4db5] = FindInBList(si, di, LifeB[cellIndex]);
                if (match_position[0x4db5] >= 0) {
                    Dx8[match_position[0x4db5] + 0x3d18] = 0;
                    LifeB[cellIndex] = 0;
                }
            }
        } else if (MapPlane == 3) {
            cellIndex = (si << 6) + di;
            if (LifeR[cellIndex] != 0) {
                match_position[0x4db5] = FindInRList(si, di, LifeR[cellIndex]);
                if (match_position[0x4db5] >= 0) {
                    Dx8[match_position[0x4db5] + 0x46e6] = 0;
                    LifeR[cellIndex] = 0;
                }
            }
        }
    }
}

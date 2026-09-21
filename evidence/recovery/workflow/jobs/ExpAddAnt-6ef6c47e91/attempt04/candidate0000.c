/*
 * ExpAddAnt: experimental map-editor tool that adds an ant of a random
 * strength to whichever plane is currently selected (MapPlane).  The
 * base strength is SRand1(8)+16; experiment sub-state 3 boosts it by
 * 128.  Plane 0/1 add to the A list only when the target cell is clear
 * (IsClearTile), doing nothing otherwise.  Plane 2/3 (B/R) require a
 * nonzero y, dig through an existing wall-family B/R tile first, then
 * add to the matching list with type flag 7 for the ordinary strength
 * range and 2 for the boosted range.  Any successful add (or a plane
 * outside 0-3) ends with the placement sound; an early miss (blocked
 * A-plane cell, or B/R plane with y == 0) returns silently.
 */
extern unsigned char far ExpSubStates[];
extern int near MapPlane;
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern int far SRand1(int range);
extern int far IsClearTile(int plane, int x, int y);
extern void far AddAntToAList(int x, int y, int type, int a, int b);
extern void far AddAntToBList(int x, int y, int type, int a, int b);
extern void far AddAntToRList(int x, int y, int type, int a, int b);
extern void far DigTileB(int x, int y);
extern void far DigTileR(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

void far ExpAddAnt(int x, int y)
{
    int amt;

    amt = SRand1(8) + 16;
    if (ExpSubStates[3] == 1)
        amt += 0x80;

    switch (MapPlane) {
    case 0:
    case 1:
        if (IsClearTile(1, x, y))
            AddAntToAList(x, y, amt, 2, 0);
        else
            return;
        break;
    case 2:
        if (y == 0)
            return;
        if (MapB[x][y] >= 0x1c)
            DigTileB(x, y);
        if (amt > 0x80)
            AddAntToBList(x, y, amt, 7, 0);
        else
            AddAntToBList(x, y, amt, 2, 0);
        break;
    case 3:
        if (y == 0)
            return;
        if (MapR[x][y] >= 0x1c)
            DigTileR(x, y);
        if (amt <= 0x80)
            AddAntToRList(x, y, amt, 7, 0);
        else
            AddAntToRList(x, y, amt, 2, 0);
        break;
    }

    myBeginSound(0x1c, 0, 0x7e);
}

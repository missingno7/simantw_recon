/*
 * ClearLife: clear the life-tracking cell at (plane, x, y) if it holds
 * the given code. Bounds (0<=x<=0x7f/0<=y<=0x3f for plane<=1, else
 * 0<=x<=0x3f/0<=y<=0x3f) are checked twice in the target (an apparent
 * duplicate, reproduced here) before returning early out of range. The
 * tracking byte comes from the near LifeA/LifeB/LifeR array for the
 * plane (exact MAPSYM names, offsets matching AddAntToBList/
 * AddAntToRList's LifeB/LifeR and this unit's LifeA), defaulting to -1
 * when the stored byte is 0. Only when that value equals the code
 * parameter does it call SetLife(plane,x,y,0) to clear the cell and the
 * cross-segment ZapEuMapAt(plane,x,y) to clear the editor overlay.
 */
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern void far SetLife(int plane, int x, int y, int code);
extern void far ZapEuMapAt(int plane, int x, int y);

void far ClearLife(int plane, int x, int y, int code)
{
    int inBounds;
    int life;

    if (plane <= 1)
        inBounds = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        inBounds = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (!inBounds)
        return;

    life = -1;
    if (plane <= 1)
        inBounds = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        inBounds = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);

    inBounds--;
    if (inBounds == 0) {
        switch (plane) {
        case 0:
        case 1:
            life = LifeA[x][y];
            break;
        case 2:
            life = LifeB[x][y];
            break;
        case 3:
            life = LifeR[x][y];
            break;
        }
    }

    if (life == 0)
        life = -1;

    if (life != code)
        return;

    SetLife(plane, x, y, 0);
    ZapEuMapAt(plane, x, y);
}

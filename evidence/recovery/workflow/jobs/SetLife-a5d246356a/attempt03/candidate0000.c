/*
 * SetLife: mark the occupancy grid cell (plane, x, y) with `code` (the
 * same LifeA/LifeB/LifeR arrays and bounds idiom as the admitted
 * MoveMyLife, which already declares this exact prototype -- src/
 * recovered/wf_MoveMyLife-f66a8c0d06.c).  Out of range does nothing.
 *
 * For the two underground planes, a positive code that lands in bounds
 * also triggers a dig: GetMap/IsItDirt (both already admitted --
 * src/recovered/wf_GetMap-cddf28f960.c, src/recovered/wf_IsItDirt-
 * 30ab0b6cc4.c) read the terrain there, and a dirt tile or one of the
 * special 0x1c-0x1f codes calls DigMyTile and starts the dig sound
 * (myBeginSound, same signature as the admitted callers in wf_ExpAddAnt/
 * wf_ExpAddFood).  Every call finishes by repainting the destination
 * cell through ZapEuMapAt (src/recovered/wf_AddWater-d30012f385.c /
 * wf_SetMap-0b7117ef15.c), regardless of plane or bounds.
 */
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];

extern int far GetMap(int plane, int x, int y);
extern int IsItDirt(int value);
extern void far DigMyTile(int plane, int x, int y);
extern void far ZapEuMapAt(int plane, int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

#define TRUE 1
#define FALSE 0

void far SetLife(int plane, int x, int y, int code)
{
    int ok;
    int tile;

    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == FALSE)
        return;

    switch (plane) {
    case 0:
    case 1:
        LifeA[x][y] = (unsigned char)code;
        break;
    case 2:
        LifeB[x][y] = (unsigned char)code;
        if (code <= 0)
            break;
        if (plane < 2)
            break;
        if (x < 0)
            break;
        if (x > 0x3f)
            break;
        if (y < 0)
            break;
        if (y > 0x3f)
            break;
        tile = GetMap(plane, x, y);
        if (IsItDirt(tile) != 0)
            goto dodig;
        if (tile >= 0x1c && tile <= 0x1f)
            goto dodig;
        break;
    case 3:
        LifeR[x][y] = (unsigned char)code;
        if (code <= 0)
            break;
        if (plane < 2)
            break;
        if (x < 0)
            break;
        if (x > 0x3f)
            break;
        if (y < 0)
            break;
        if (y > 0x3f)
            break;
        tile = GetMap(plane, x, y);
        if (IsItDirt(tile) != 0)
            goto dodig;
        if (tile >= 0x1c && tile <= 0x1f)
            goto dodig;
        break;

    dodig:
        DigMyTile(plane, x, y);
        myBeginSound(0x13, 0, 0x3f);
        break;
    }

    ZapEuMapAt(plane, x, y);
}

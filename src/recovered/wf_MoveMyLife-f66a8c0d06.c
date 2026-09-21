/*
 * MoveMyLife: relocate the player's ant to (plane, x, y, type, dir).
 *
 * The current cell is cleared first with ClearMyLife on the Me* position
 * globals (same-segment far call; exact MAPSYM names MePlane, MeLocX,
 * MeLocY, MeType, MeDir).  A plane of 0 means the surface plane 1; the
 * effective plane is a frame local.  The destination is then range
 * checked with the unit's GetMap idiom (src/recovered/wf_GetMap-
 * cddf28f960.c): a materialised flag, 0<=x<=0x7f and 0<=y<=0x3f on the
 * surface planes, 0<=x<=0x3f and 0<=y<=0x3f underground, and the move
 * only happens when `ok == TRUE`: the destination cell is marked 0xff
 * with SetLife; a queen (type 0x60) also marks the cell behind her
 * (0xfe) at the reverse direction dir^4 through the far Dx8/Dy8 step
 * tables (char deltas, same tables as the goStep unit); finally the Me*
 * globals take the new x, y, dir, type and plane.  Out of range the
 * function returns with the old cell already cleared.
 */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern char far Dy8[];
extern char far Dx8[];

extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far SetLife(int plane, int x, int y, int code);

#define TRUE 1
#define FALSE 0

void far MoveMyLife(int plane, int x, int y, int type, int dir)
{
    int p;
    int ok;

    ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
    if (plane == 0)
        p = 1;
    else
        p = plane;
    if (p <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == TRUE) {
        SetLife(p, x, y, 0xff);
        if (type == 0x60)
            SetLife(p, x + Dx8[dir ^ 4], y + Dy8[dir ^ 4], 0xfe);
        MeLocX = x;
        MeLocY = y;
        MeDir = dir;
        MeType = type;
        MePlane = p;
    }
}

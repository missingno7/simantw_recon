/*
 * MoveMyLife: relocate the player's ant to (plane, x, y, type, dir).
 * Clears the ant's current life cell (ClearMyLife on the current My*
 * globals, matching src/recovered/wf_EnterNest-606488b329.c's call
 * shape), defaults plane to 1 when the caller passes 0, then bounds
 * checks the destination: 0<=x<=0x7f, 0<=y<=0x3f for plane<=1 (yard),
 * else 0<=x<=0x3f, 0<=y<=0x3f (nest); out-of-range silently returns
 * (the current cell stays cleared). On success the destination cell is
 * marked 0xff via SetLife(plane,x,y,code); for a queen (type==0x60) the
 * cell behind her (offset by the Dx8/Dy8 delta at the reverse direction
 * dir^4, the same reverse-direction idiom as GetExitDirB/R) is marked
 * 0xfe too (the queen occupies two cells). The My* position globals are
 * then updated to the new plane/x/y/type/dir.
 */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define DX(off) (*(signed char far *)&AT(off))

extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far SetLife(int plane, int x, int y, int code);

void far MoveMyLife(int plane, int x, int y, int type, int dir)
{
    int adjustedPlane;

    ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
    if (plane != 0)
        adjustedPlane = plane;
    else
        adjustedPlane = 1;
    if (adjustedPlane > 1) {
        if (x < 0)
            return;
        if (x > 0x3f)
            return;
        if (y < 0)
            return;
        if (y > 0x3f)
            return;
    } else {
        if (x < 0)
            return;
        if (x > 0x7f)
            return;
        if (y < 0)
            return;
        if (y > 0x3f)
            return;
    }
    SetLife(adjustedPlane, x, y, 0xff);
    if (type == 0x60)
        SetLife(adjustedPlane, x + DX(dir ^ 4), y + DX(8 + (dir ^ 4)), 0xfe);
    MeLocX = x;
    MeLocY = y;
    MeDir = dir;
    MeType = type;
    MePlane = adjustedPlane;
}

/*
 * SetMyLife validates a cell, writes its life value, and for type 0x60
 * writes the opposite-direction companion value; the 0xff sentinel maps
 * to 0xfe. Nonzero life updates the current-ant globals.
 */extern int near MeLocX;
extern int near MeLocY;
extern int near MeDir;
extern int near MeType;
extern int near MePlane;

extern char far Dy8[];
extern char far Dx8[];

extern void far SetLife(int plane, int x, int y, int value);

void far SetMyLife(int plane, int x, int y, int type, int dir, int life)
{
    int ok;
    int val;

    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == 1) {
        SetLife(plane, x, y, life);
        if (type == 0x60) {
            val = (life == 0xff) ? 0xfe : life;
            SetLife(plane, Dx8[dir ^ 4] + x, Dy8[dir ^ 4] + y, val);
        }
        if (life != 0) {
            MeLocX = x;
            MeLocY = y;
            MeDir = dir;
            MeType = type;
            MePlane = plane;
        }
    }
}


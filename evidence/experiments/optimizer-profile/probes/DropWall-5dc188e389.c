/*
 * DropWall: experimental map-editor tool that drags a wall from (x, y)
 * toward (tx, ty) on the A ant plane, one map cell per loop iteration
 * while the destination stays reachable (IsValidA).  Holding CONTROL
 * repaints the cell with a random low value whenever it already holds a
 * wall-family tile (strictly between 0x50 and 0x68) and always
 * reconnects the wall graph, but plays no sound.  Without CONTROL, an
 * empty (< 0x50) cell with no life becomes a new wall tile: experiment
 * sub-state 1 picks a random 0x51-0x53 variant and a pitched placement
 * sound (no reconnect call for this variant), while the default state
 * writes the fixed solid-wall tile 0x60, reconnects and plays the plain
 * connect sound; an already-occupied cell in the default state still
 * reconnects and plays the same plain sound.  GetDir then supplies the
 * next step toward (tx, ty): a nonzero Dx9[dir] steps x, otherwise
 * Dy9[dir] steps y; dir == 0 ends the drag.
 */
extern unsigned char near MapA[8192];
extern unsigned char near LifeA[8192];
extern unsigned char far ExpSubStates[];
extern char far Dx9[];
extern char far Dy9[];

extern int far pascal GetAsyncKeyState(unsigned int key);
extern int far IsValidA(int x, int y);
extern int far SRand1(int range);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far ConnectAll(int x, int y);
extern int far GetDir(int x, int y, int tx, int ty);

void far DropWall(int x, int y, int tx, int ty)
{
    int dir;
    int delta;
    int idx;

    while (IsValidA(x, y)) {
        if (GetAsyncKeyState(0x11) & 0x8000) {
            idx = (x << 6) + y;
            if (MapA[idx] > 0x50 && MapA[idx] < 0x68)
                MapA[idx] = (unsigned char)SRand1(16);
            ConnectAll(x, y);
        } else if (ExpSubStates[1]) {
            idx = (x << 6) + y;
            if (MapA[idx] < 0x50 && LifeA[idx] == 0)
                MapA[idx] = (unsigned char)(SRand1(3) + 0x51);
            myBeginSound(10, SRand1(10000) + 2000, 0x7e);
        } else {
            idx = (x << 6) + y;
            if (MapA[idx] < 0x50 && LifeA[idx] == 0)
                MapA[idx] = 0x60;
            ConnectAll(x, y);
            myBeginSound(0x28, 0, 0x7e);
        }

        dir = GetDir(x, y, tx, ty);
        delta = Dx9[dir];
        if (delta != 0)
            x += delta;
        else
            y += Dy9[dir];

        if (dir == 0)
            break;
    }
}

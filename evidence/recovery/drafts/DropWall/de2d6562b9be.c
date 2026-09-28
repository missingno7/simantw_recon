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

void far DropWall(int argX, int argY, int tx, int ty)
{
  register int cx = argX;
  register int cy = argY;
  char temp;
  int dir;
  int pos;
  volatile int idx;
  while (IsValidA(cx, cy))
  {
    if (GetAsyncKeyState(0x11) & 0x8000)
    {
      idx = (cx << 6) + cy;
      if (MapA[idx] > 0x50 && MapA[idx] < 0x68)
        MapA[idx] = (unsigned char) SRand1(16);
      ConnectAll(cx, cy);
    }
    else
      if (ExpSubStates[1] == 0)
    {
      pos = cx << 6;
      idx = pos + cy;
      if (MapA[idx] < 0x50 && LifeA[idx] == 0)
        MapA[idx] = 0x60;
      ConnectAll(cx, cy);
      myBeginSound(0x28, 0, 0x7e);
    }
    else
    {
      idx = (cx << 6) + cy;
      if (MapA[idx] < 0x50 && LifeA[idx] == 0)
        MapA[idx] = (unsigned char) (SRand1(3) + 0x51);
      myBeginSound(10, SRand1(10000) + 2000, 0x7e);
    }
    dir = GetDir(cx, cy, tx, ty);
    temp = Dx9[dir];
    if (temp != 0)
      cx = cx + temp;
    else
      cy += Dy9[dir];
    if (dir == 0)
      break;
  }

}


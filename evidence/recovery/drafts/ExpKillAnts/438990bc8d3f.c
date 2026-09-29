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
extern int far Tindex;

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
  int index;
  int count;
  int mode;
  int pos;
  int cellIndex;
  int offset;
  int far * volatile indexPtr;
  if (ExpSubStates[6] == 0)
    mode = 8;
  else
    mode = 1;
  indexPtr = &Tindex;
  for (count = 8; count != 0; count--)
  {
    if (mode == 1)
    {
      myBeginSound(9, 0, 0x7e);
    }
    else
    {
      x = SRand1(9) + x - 4;
      y = SRand1(9) + y - 4;
      myBeginSound(9, SRand1(1000) + 0x278f, 0x7e);
    }
    if (!IsValidLocation(MapPlane, x, y))
      continue;
    switch (MapPlane)
    {
      case 0:

      case 1:
      {
        cellIndex = (x << 6) + y;
        if (LifeA[x][y] != 0)
        {
          *indexPtr = FindInAList(x, y);
          if ((*indexPtr) >= 0)
          {
            offset = Dx8[(*indexPtr) + 0x2f62] & 0x80;
            DeadAntHere(x, y, offset);
            index = (*indexPtr) + 0x2f62;
            Dx8[index] = 0;
            LifeA[x][y] = 0;
          }
          if (SpidX >> 4 == x)
          {
            if (SpidY >> 4 == y)
              KillSpider();
          }
          if (MapA[x][y] >= 0x38 && MapA[x][y] <= 0x3e)
            KillAntLion(FindInLionList(x, y));
        }
      }
        break;

      case 2:
      {
        cellIndex = (x << 6) + y;
        if (LifeB[cellIndex] != 0)
        {
          *indexPtr = FindInBList(x, y, LifeB[cellIndex]);
          if ((*indexPtr) >= 0)
          {
            pos = (*indexPtr) + 0x3d18;
            Dx8[pos] = 0;
            LifeB[cellIndex] = 0;
          }
        }
      }
        break;

      case 3:
      {
        cellIndex = (x << 6) + y;
        if (LifeR[cellIndex] != 0)
        {
          *indexPtr = FindInRList(x, y, LifeR[cellIndex]);
          if ((*indexPtr) >= 0)
          {
            Dx8[(*indexPtr) + 0x46e6] = 0;
            LifeR[cellIndex] = 0;
          }
        }
      }
        break;

      default:
        break;

    }

  }

}


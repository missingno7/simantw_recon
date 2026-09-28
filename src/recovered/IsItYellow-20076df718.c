/* IsItYellow: the matching-plane arm contains both the spider-distance
 * result and the life-map result; a nonmatch returns zero immediately. */
extern int near MePlane;
extern int near SpidX;
extern int near SpidY;
extern int far MeMode;
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern unsigned long far GetDis(int x1, int y1, int x2, int y2);

int far IsItYellow(int level, int x, int y)
{
  int effectiveLevel;
  int matches;
  unsigned long status;
  register int tile;
  int result;
  if (level == 0)
    effectiveLevel = 1;
  else
    effectiveLevel = level;
  if (MePlane == effectiveLevel)
    matches = 1;
  else
    matches = 0;
  if (matches == 0)
  {
    return 0;
  }
  else
  {
    if (MeMode == 1)
    {
      if (level > 1)
        return 0;
      status = GetDis(x * 16 + 8, y * 16 + 8, SpidX, SpidY);
      if (status < 0x200UL)
        return 1;
      return 0;
    }
    switch (level)
    {
      case 0:

      case 1:
        tile = LifeA[x][y];
        break;

      case 2:
        tile = LifeB[x][y];
        break;

      case 3:
        tile = LifeR[x][y];
        break;

    }

    if (tile == 0xff || tile == 0xfe)
      result = 1;
    else
      result = 0;
    return result;
  }
}


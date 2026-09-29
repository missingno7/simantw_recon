extern unsigned char far Dx8[]; extern char far Dy8[]; extern int far MeCrazyCnt; extern int far match_position[];
extern int far GetMyBestDirs(int plane,int x,int y,int a,int b);
extern void far GetMyRandDirs(int far *outDirA,int far *outDirB,int plane,int x,int y,int a,int b);
int far GetMyNextRandDirs(int plane,int x,int y,int a,int b)
{
  int dir;
  struct 
  {
    int spare;
    int tries;
    int ny;
    int nx;
  } scan;
  scan.tries = 0;
  dir = GetMyBestDirs(plane, x, y, a, b);
  if (dir >= 0)
  {
    scan.nx = x + Dx8[dir];
    scan.ny = y + Dy8[dir];
    while (dir >= 0 && scan.tries < 0x40)
    {
      dir = GetMyBestDirs(plane, scan.nx, scan.ny, a, b);
      if (dir >= 0)
      {
        scan.nx += Dx8[dir];
        scan.ny += Dy8[dir];
      }
      scan.tries += 1;
    }

    if (dir >= 0)
      dir = -1;
  }
  if (dir == (-2))
  {
    GetMyRandDirs((int far *) (&match_position[0x78a4 / 2]), (int far *) (&match_position[0xa0d8 / 2]), plane, x, y, a, b);
  }
  else
  {
    MeCrazyCnt = -1;
    return GetMyBestDirs(plane, x, y, a, b);
  }
}


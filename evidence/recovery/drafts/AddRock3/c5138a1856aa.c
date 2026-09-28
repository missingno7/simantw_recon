extern unsigned char near MapA[128][64];
extern unsigned char far Dx8[];
void far AddRock3(int x, int y, int id)
{
  int r3;
  int offset;
  int col1;
  int ypos;
  int row;
  r3 = id * 3;
  row = 0;
  ypos = x * 64;
  for (; row < 3; row++)
  {
    for (col1 = 0; col1 < 3; col1++)
    {
      offset = r3 * 3 + row;
      if ((*((&Dx8[offset + col1 * 3]) + 0x87a0)) != 0)
      {
        if (MapA[0][y + ypos + col1] > 0x10)
          return;
      }
    }

    ypos += 0x40;
  }

  row = 0;
  ypos = x * 64;
  for (; row < 3; row++)
  {
    int col2;
    for (col2 = 0; col2 < 3; col2++)
    {
      int v = *((&Dx8[r3 * 3 + row + col2 * 3]) + 0x87a0);
      if (v != 0)
        MapA[0][y + ypos + col2] = v;
    }

    ypos += 0x40;
  }

}


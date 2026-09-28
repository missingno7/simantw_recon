extern unsigned char far Dx8[];

void near SmoothAlarm(void)
{
  int value;
  int row;
  int offset;
  int col;
  int sum;
  int val;
  for (row = 0; row < 0x40; row++)
  {
    for (col = 0; col < 0x20; col++)
      Dx8[row * 0x20 + col + 0x4ad2] = Dx8[row * 0x20 + col + 0x52d2];

  }

  for (row = 0; row < 0x40; row++)
  {
    for (col = 0; col < 0x20; col++)
    {
      sum = 0;
      if (row > 0)
        sum = Dx8[(row - 1) * 0x20 + col + 0x4ad2];
      if (col > 0)
        sum += Dx8[row * 0x20 + col - 1 + 0x4ad2];
      if (row < 0x3f)
        sum += Dx8[(row + 1) * 0x20 + col + 0x4ad2];
      if (col < 0x1f)
        sum += Dx8[row * 0x20 + col + 1 + 0x4ad2];
      sum >>= 2;
      val = Dx8[row * 0x20 + col + 0x4ad2];
      value = val + sum;
      val = value >> 1;
      offset = row * 0x20 + col;
      Dx8[offset + 0x52d2] = (val > 8) ? (val) : (0);
    }

  }

}


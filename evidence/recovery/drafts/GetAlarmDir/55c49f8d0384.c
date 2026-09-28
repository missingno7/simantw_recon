/* GetAlarmDir: choose a defensive direction for an ant reacting to alarm,
 * at map position (x, y) currently facing dir.  Border tiles reuse the
 * same edge/corner turning logic as the admitted GetRandDir (x==0/
 * x==127/y==0/y==63 combinations pick a biased random turn via
 * SRand1).  On an interior tile the eight compass neighbours (the
 * Dx8[i]/Dy8[i] delta pair against the half-resolution x,y) are
 * scored through the shared AlarmMap at Dx8+0x52d2 (32-byte rows,
 * matching the admitted AlarmHere writer); the direction with the
 * highest score wins.  When no neighbour scores above zero, SRand8()
 * picks the fallback column of TurnTab[dir].
 */
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlarmGrid[];
extern char far TurnTab[][8];
extern int far SRand1(int range);
extern int far SRand8(void);

int far GetAlarmDir(int x, int y, int dir)
{
  int r;
  register int i;
  unsigned int best;
  register int bestValue;
  char row;
  int col;
  int yh;
  int xh;
  xh = x >> 1;
  yh = y >> 1;
  if (x == 0)
  {
    if (y == 0)
      r = SRand1(3) + 3;
    else
      if (y == 63)
      r = SRand1(3) + 1;
    else
      r = SRand1(5) + 1;
  }
  else
    if (y == 0)
  {
    r = (x == 127) ? (SRand1(3) + 5) : (SRand1(5) + 3);
  }
  else
    if (x == 127)
  {
    if (y == 63)
      r = SRand1(3) + 7;
    else
      r = SRand1(5) + 5;
  }
  else
    if (y == 63)
    r = SRand1(5) + 7;
  else
    r = 0;
  if (r != 0)
    return ((unsigned char) r) - 1 & 7;
  i = 0;
  bestValue = i;
  best = bestValue;
  for (; i < 8; i++)
  {
    int offset;
    col = Dy8[i] + yh & 0x1f;
    row = Dx8[i] + xh & 0x3f;
    offset = 0x52d2 + (row << 5);
    if (AlarmGrid[offset + col] > bestValue)
    {
      bestValue = *(AlarmGrid + (offset + col));
      best = i;
    }
  }

  if (bestValue != 0)
    return TurnTab[dir][best];
  return TurnTab[dir][SRand8()];
}



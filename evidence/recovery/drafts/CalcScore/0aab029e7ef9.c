extern int far HistStart;

extern int far HistCnt;
extern int far match_position[];
extern long far TotalEggsLaidB;
extern long far TotalEggsDiedB;
extern int far BlackLost;
extern int far RedLost;
extern int far CurGameType;
extern int far BColoniesStarted;
extern int far RColoniesStarted;
extern int far BColoniesKilled;
extern unsigned long far GameTime;

extern int near MeHealth;
extern int near paletteH;

extern unsigned char far YMapPopB[12][16];

long far CalcScore(int far *score)
{
  int historyStart;
  int historyCount;
  int position;
  int blackTotal;
  int redTotal;
  int denominator;
  int gameType;
  int population;
  register int row;
  int column;
  long index;
  register int i;
  long weightedScore;
  long elapsed;
  long factor;
  long result;
  for (i = 0; i < 8; ++i)
    score[i] = 0;

  historyCount = HistCnt;
  historyStart = HistStart - historyCount & 63;
  blackTotal = 0;
  position = historyStart;
  if (historyCount > 0)
  {
    for (i = 0; i < historyCount; ++i)
    {
      blackTotal += match_position[position - 0x3068];
      position = position + 1 & 63;
    }
  }
  score[0] = historyCount > 0 ? blackTotal / historyCount : 0;
  blackTotal = 0;
  redTotal = 0;
  position = historyStart;
  if (historyCount > 0)
  {
    for (i = 0; i < historyCount; ++i)
    {
      blackTotal += match_position[position + 0x3e4c];
      redTotal += match_position[position + 0x3ebb];
      position = position + 1 & 63;
    }

    denominator = blackTotal + redTotal;
    if (denominator > 0)
      score[1] = ((long) blackTotal) * 100L / denominator;
  }
  if (TotalEggsLaidB <= 0)
  {
    score[2] = 100;
  }
  else
    score[2] = (int) ((TotalEggsLaidB - TotalEggsDiedB) * 100L / TotalEggsLaidB);
  denominator = BlackLost + RedLost;
  if (denominator <= 0)
  {
    score[3] = 100;
  }
  else
    score[3] = BlackLost * 100 / denominator;
  gameType = CurGameType;
  if (!(gameType != 2 && gameType != 3))
  {
    denominator = BColoniesStarted + RColoniesStarted;
    if (denominator > 0)
      score[4] = ((long) BColoniesStarted) * 100L / denominator;
    else
      score[4] = 100;
    denominator = BColoniesStarted + BColoniesKilled;
    score[5] = (denominator <= 0) ? (100) : (((long) BColoniesStarted) * 100L / denominator);
  }
  population = 0;
  for (row = 0; row < 16; ++row)
  {
    for (column = (row < 5) ? (3) : (2); column < 12; ++column)
    {
      if (YMapPopB[column][row])
        ++population;
    }

  }

  score[6] = ((long) population) * 100L / 155L;
  population = 0;
  for (row = 0; row < 16; ++row)
  {
    for (column = 0; column < ((row < 5) ? (3) : (2)); ++column)
    {
      if (YMapPopB[column][row])
        ++population;
    }

  }

  index = ((long) population) * 100L;
  score[7] = index / 37L;
  weightedScore = MeHealth;
  for (i = 0; i < 8; ++i)
    weightedScore += ((long near) ((char near *) (&paletteH))[0xee + i]) * score[i];

  elapsed = GameTime;
  if (gameType != 2)
  {
    weightedScore = weightedScore * 29L / 10L;
    if (elapsed < 4100L)
    {
      factor = elapsed / 100L;
      if (factor <= 0)
        factor = 1;
      result = weightedScore * factor / 41L;
    }
    else
    {
      result = weightedScore;
    }
  }
  else
  {
    if (elapsed < 8100L)
    {
      factor = elapsed / 100L;
      if (factor <= 0)
        factor = 1;
      result = weightedScore * factor / 81L;
    }
    else
    {
      result = weightedScore;
    }
  }
  return elapsed + result;
}


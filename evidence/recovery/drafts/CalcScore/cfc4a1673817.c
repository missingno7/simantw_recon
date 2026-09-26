struct CalcInput { int value; };
extern unsigned char far HistStart;
extern int far HistCnt;
extern int far Dx8[];
extern long far TotalEggsLaidB;
extern long far TotalEggsDiedB;
extern int far BlackLost;
extern int far RedLost;
extern int far CurGameType;
extern int far BColoniesStarted;
extern int far RColoniesStarted;
extern int far BColoniesKilled;
extern int near MeHealth;

void far CalcScore(int far *score)
{
    int i;
    int first;
    int count;
    int total;
    long numerator;
    long denominator;
    long value;

    for (i = 0; i < 8; ++i)
        score[i] = 0;

    first = HistStart;
    count = HistCnt;
    total = 0;
    for (i = 0; i < count; ++i) {
        total += Dx8[(first + i) & 63];
    }
    if (count > 0)
        score[0] = total / count;

    total = 0;
    for (i = 0; i < count; ++i)
        total += Dx8[((first + i) & 63) + 64];
    if (count > 0)
        score[1] = (total * 100) / count;

    numerator = TotalEggsLaidB;
    denominator = numerator + TotalEggsDiedB;
    if (denominator != 0)
        score[2] = (int)((numerator * 100L) / denominator);

    if (BColoniesStarted != 0)
        score[3] = BColoniesKilled * 100 / BColoniesStarted;
    if (RColoniesStarted != 0)
        score[4] = RedLost * 100 / RColoniesStarted;

    score[5] = BlackLost + RedLost;
    score[6] = MeHealth;
    if (CurGameType == 0)
        score[7] = score[2] + score[3];
    else
        score[7] = score[2] + score[4];

    value = score[7];
    if (value < 0)
        score[7] = 0;
}

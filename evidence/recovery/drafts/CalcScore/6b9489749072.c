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
    int work[8];
    int i;
    int first;
    int count;
    int total;
    int secondTotal;
    long numerator;
    long denominator;

    for (i = 0; i < 8; ++i)
        score[i] = 0;

    first = HistStart;
    count = HistCnt;
    work[0] = first;
    work[1] = count;
    total = 0;
    i = first;
    for (; count > 0; --count) {
        total += Dx8[i];
        i = (i + 1) & 63;
    }
    if (HistCnt > 0)
        score[0] = total / HistCnt;

    count = HistCnt;
    i = first;
    total = 0;
    secondTotal = 0;
    for (; count > 0; --count) {
        total += Dx8[64 + i];
        secondTotal += Dx8[128 + i];
        i = (i + 1) & 63;
    }
    work[2] = total;
    work[3] = secondTotal;
    if (HistCnt > 0)
        score[1] = (total * 100) / HistCnt;

    numerator = TotalEggsLaidB;
    denominator = numerator + TotalEggsDiedB;
    work[4] = (int)numerator;
    work[5] = (int)denominator;
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
    work[6] = score[7];
}

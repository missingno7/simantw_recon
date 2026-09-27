extern unsigned char far HistStart;
extern int far HistCnt;
extern int far H_BHeal[64];
extern int far H_BFood[64];
extern int far H_RFood[64];
extern long far TotalEggsLaidB;
extern long far TotalEggsDiedB;
extern int far BlackLost;
extern int far RedLost;
extern int far CurGameType;
extern int far BColoniesStarted;
extern int far RColoniesStarted;
extern int far BColoniesKilled;
extern long far GameTime;
extern int near MeHealth;
extern char near paletteH[];
extern unsigned char __based(__segname("PACK")) pack_buf[];

long far CalcScore(int far *score)
{
    int historyStart;
    int historyCount;
    int position;
    int blackTotal;
    int redTotal;
    int denominator;
    int gameType;
    int coloniesStarted;
    int population;
    int row;
    int column;
    int i;
    long laid;
    long weightedScore;
    long elapsed;
    long factor;
    long result;

    for (i = 0; i < 8; ++i)
        score[i] = 0;

    historyCount = HistCnt;
    historyStart = (HistStart - historyCount) & 63;
    blackTotal = 0;
    position = historyStart;
    if (historyCount > 0) {
        for (i = 0; i < historyCount; ++i) {
            blackTotal += H_BHeal[position];
            position = (position + 1) & 63;
        }
        score[0] = blackTotal / historyCount;
    }

    blackTotal = 0;
    redTotal = 0;
    position = historyStart;
    if (historyCount > 0) {
        for (i = 0; i < historyCount; ++i) {
            blackTotal += H_BFood[position];
            redTotal += H_RFood[position];
            position = (position + 1) & 63;
        }
        denominator = blackTotal + redTotal;
        if (denominator > 0)
            score[1] = blackTotal * 100 / denominator;
    }

    laid = TotalEggsLaidB;
    if (laid > 0)
        score[2] = (int)(((laid - TotalEggsDiedB) * 100L) / laid);
    else
        score[2] = 100;

    denominator = BlackLost + RedLost;
    if (denominator > 0)
        score[3] = BlackLost * 100 / denominator;
    else
        score[3] = 100;

    gameType = CurGameType;
    if (gameType == 2 || gameType == 3) {
        coloniesStarted = BColoniesStarted;
        denominator = coloniesStarted + RColoniesStarted;
        if (denominator > 0)
            score[4] = coloniesStarted * 100 / denominator;
        else
            score[4] = 100;

        denominator = coloniesStarted + BColoniesKilled;
        if (denominator > 0)
            score[5] = coloniesStarted * 100 / denominator;
        else
            score[5] = 100;
    }

    population = 0;
    for (row = 0; row < 16; ++row) {
        for (column = (row < 5 ? 3 : 2); column < 12; ++column) {
            if (pack_buf[0xa0 + (column << 4) + row])
                ++population;
        }
    }
    score[6] = population * 100 / 155;

    population = 0;
    for (row = 0; row < 16; ++row) {
        for (column = 0; column < (row < 5 ? 3 : 2); ++column) {
            if (pack_buf[0xa0 + (column << 4) + row])
                ++population;
        }
    }
    score[7] = population * 100 / 37;

    weightedScore = MeHealth;
    for (i = 0; i < 8; ++i)
        weightedScore += (long)paletteH[0xee + i] * score[i];

    elapsed = GameTime;
    if (gameType == 2) {
        if (elapsed < 8100L) {
            factor = elapsed / 100L;
            if (factor <= 0)
                factor = 1;
            result = weightedScore * factor / 81L;
        } else {
            result = weightedScore;
        }
    } else {
        weightedScore = weightedScore * 29L / 10L;
        if (elapsed < 4100L) {
            factor = elapsed / 100L;
            if (factor <= 0)
                factor = 1;
            result = weightedScore * factor / 41L;
        } else {
            result = weightedScore;
        }
    }

    return elapsed + result;
}

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
            blackTotal += match_position[position - 0x3068];
            position = (position + 1) & 63;
        }
        score[0] = blackTotal / historyCount;
    }

    blackTotal = 0;
    redTotal = 0;
    position = historyStart;
    if (historyCount > 0) {
        for (i = 0; i < historyCount; ++i) {
            blackTotal += match_position[position + 0x3e4c];
            redTotal += match_position[position + 0x3ebb];
            position = (position + 1) & 63;
        }
        denominator = blackTotal + redTotal;
        if (denominator > 0)
            score[1] = (long)blackTotal * 100L / denominator;
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
        denominator = BColoniesStarted + RColoniesStarted;
        if (denominator > 0)
            score[4] = (long)BColoniesStarted * 100L / denominator;
        else
            score[4] = 100;

        denominator = BColoniesStarted + BColoniesKilled;
        if (denominator > 0)
            score[5] = (long)BColoniesStarted * 100L / denominator;
        else
            score[5] = 100;
    }

    population = 0;
    for (row = 0; row < 16; ++row) {
        for (column = (row < 5 ? 3 : 2); column < 12; ++column) {
            if (YMapPopB[column][row])
                ++population;
        }
    }
    score[6] = (long)population * 100L / 155L;

    population = 0;
    for (row = 0; row < 16; ++row) {
        for (column = 0; column < (row < 5 ? 3 : 2); ++column) {
            if (YMapPopB[column][row])
                ++population;
        }
    }
    score[7] = (long)population * 100L / 37L;

    weightedScore = MeHealth;
    for (i = 0; i < 8; ++i)
        weightedScore += (long)((char near *)&paletteH)[0xee + i] * score[i];

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

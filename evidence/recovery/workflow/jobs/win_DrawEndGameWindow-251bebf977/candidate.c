/* win_DrawEndGameWindow: draw the end-of-game rating window; flags bit 1
 * gates it, same idiom as win_DrawPictureWindow.  CalcScore fills a
 * private score buffer and returns the overall score as a long.  When
 * CurGameType == 2 the score is scaled to a fifth (score/5) before
 * picking a 0..4 rating tier by long-compared thresholds, else the raw
 * score picks the tier directly.  BlackWon shifts into the second half
 * of the ten-entry EndGameRatingStrs table.  The scenario name
 * (ScenarioNameStrs[CurGameType] when it is 0..3, else the fixed
 * "custom" entry 2) is printed at object 0x402, the raw score as "%ld"
 * at 0x403, and the rating caption at 0x404, all in font 4, then the
 * font is reset to 0.
 */

extern int CurGameType[1];
extern int far BlackWon;
extern char far * far * far ScenarioNameStrs;
extern char far * far * far EndGameRatingStrs;

extern long far CalcScore(int far *scores);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int objectNumber, char far *format, ...);

void far win_DrawEndGameWindow(int flags)
{
    int scores[8];
    long score;
    long quotient;
    int tier;
    int far *p;
    char far *scenarioText;

    if (!(flags & 2))
        return;

    score = CalcScore(scores);
    p = CurGameType;

    if (*p == 2)
        quotient = score / 5L;
    else
        quotient = score;

    if (quotient < 0x344ccL)
        tier = 0;
    else if (quotient < 0x68998L)
        tier = 1;
    else if (quotient < 0x9ce64L)
        tier = 2;
    else if (quotient < 0xd1330L)
        tier = 3;
    else
        tier = 4;

    if (BlackWon)
        tier += 5;

    font_SetFont(4);

    if (*p >= 0 && *p <= 3)
        scenarioText = ScenarioNameStrs[*p];
    else
        scenarioText = ScenarioNameStrs[2];

    win_PrintfAtObj(0x402, scenarioText);
    win_PrintfAtObj(0x403, "%ld", score);
    win_PrintfAtObj(0x404, EndGameRatingStrs[tier]);

    font_SetFont(0);
}

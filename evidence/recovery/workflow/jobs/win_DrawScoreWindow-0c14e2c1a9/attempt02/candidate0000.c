/* Draw score details when requested; otherwise concatenate the game and scenario names. */
extern int far CurGameType;
extern long far OverallScore;
extern char far * far * far MiscStrs;
extern char far * far * far ScenarioNameStrs;
extern void far CalcScore(int far *score);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);

void far win_DrawScoreWindow(int flags)
{
    int scores[4];
    char title[0x60];
    char *dst;
    char far *p;
    int i;

    if (flags & 2) {
        CalcScore(scores);
        OverallScore = *(long far *)scores;
        font_SetFont(4);
        if (CurGameType == 2) {
            for (i = 0; i < 4; ++i)
                win_PrintfAtObj(0x1806 + i, "%d", scores[i]);
        } else {
            for (i = 0; i < 4; ++i)
                win_PrintfAtObj(0x1806 + i, MiscStrs[16]);
        }
        font_SetFont(4);
        if (CurGameType == 3) {
            win_PrintfAtObj(0x180a, MiscStrs[17]);
            win_PrintfAtObj(0x180b, MiscStrs[18]);
        }
        return;
    }

    dst = title;
    p = MiscStrs[13];
    while (*p) *dst++ = *p++;
    p = ScenarioNameStrs[CurGameType];
    while (*p) *dst++ = *p++;
    p = MiscStrs[14];
    while (*p) *dst++ = *p++;
    *dst = 0;
    win_PrintfAtObj(0x180a, title);
    win_PrintfAtObj(0x180b, "%ld", OverallScore);
}

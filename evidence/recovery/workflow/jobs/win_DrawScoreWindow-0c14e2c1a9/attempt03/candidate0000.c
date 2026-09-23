/* Draw score details when requested; otherwise concatenate the game and scenario names. */
extern int far CurGameType;
extern long far OverallScore;
extern char far * far * far MiscStrs;
extern char far * far * far ScenarioNameStrs;
extern long far CalcScore(int far *detailScores);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);

struct ScoreDetails {
    long total;
    int values[4];
};

void far win_DrawScoreWindow(int flags)
{
    struct ScoreDetails details;
    char title[0x60];
    char *dst;
    char far *p;
    int i;

    if (flags & 2) {
        OverallScore = CalcScore(details.values);
        font_SetFont(4);
        if (CurGameType == 2) {
            for (i = 4; i < 8; ++i)
                win_PrintfAtObj(0x1802 + i, "%d", details.values[i - 4]);
        } else {
            for (i = 4; i < 8; ++i)
                win_PrintfAtObj(0x1802 + i, MiscStrs[16]);
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

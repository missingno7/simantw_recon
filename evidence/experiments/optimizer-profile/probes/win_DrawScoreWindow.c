/* Refresh and draw score details when requested; other game modes also draw a combined title. */
extern int far CurGameType;
extern long far OverallScore;
extern char far * far * far MiscStrs;
extern char far * far * far ScenarioNameStrs;
extern long far CalcScore(int far *detailScores);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);

extern char far * far strcat(char far *destination, const char far *source);

void far win_DrawScoreWindow(int flags)
{
    int scores[4];
    char title[0x58];
    char *dst;
    char far *p;
    int gameType;
    int i;
    int *scorep;

    if (flags & 2) {
        OverallScore = CalcScore(scores);
        font_SetFont(4);
        gameType = CurGameType;
        if (gameType == 2) {
            for (scorep = scores, i = 4; scorep < scores + 4; ++scorep, ++i)
                win_PrintfAtObj(0x1802 + i, "%d", *scorep);
        } else {
            for (i = 4; i < 8; ++i)
                win_PrintfAtObj(0x1802 + i, MiscStrs[16]);
        }
        font_SetFont(4);
        if (gameType == 3) {
            win_PrintfAtObj(0x180a, MiscStrs[17]);
            win_PrintfAtObj(0x180b, MiscStrs[18]);
            return;
        }

        dst = title;
        *dst = 0;
        p = MiscStrs[13];
        strcat(dst, p);
        p = ScenarioNameStrs[gameType];
        strcat(dst, p);
        p = MiscStrs[14];
        strcat(dst, p);
        win_PrintfAtObj(0x180a, title);
    }
    win_PrintfAtObj(0x180b, "%ld", OverallScore);
}




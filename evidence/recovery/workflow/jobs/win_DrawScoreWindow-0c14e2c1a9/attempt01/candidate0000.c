/* Draw score details when requested; otherwise concatenate the game and scenario names. */
extern int far CurGameType;
extern long far OverallScore;
extern char far * far * far MiscStrs;
extern char far * far * far ScenarioNameStrs;
extern void far CalcScore(long far *score);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);

struct ScoreObject {
    unsigned char pad[0x38];
    char far *name;
};
extern struct ScoreObject far * far match_position;

void far win_DrawScoreWindow(int flags)
{
    long score;
    char title[0x60];
    char *dst;
    char far *p;
    int i;

    if (flags & 2) {
        CalcScore(&score);
        OverallScore = score;
        font_SetFont(4);
        if (CurGameType == 2) {
            for (i = 4; i < 8; ++i)
                win_PrintfAtObj(0x1802 + i, "%d", (int)(score >> 16));
        } else {
            for (i = 4; i < 8; ++i)
                win_PrintfAtObj(0x1802 + i, MiscStrs[0x20]);
        }
        font_SetFont(4);
        if (CurGameType == 3) {
            win_PrintfAtObj(0x180a, MiscStrs[0x23]);
            win_PrintfAtObj(0x180b, MiscStrs[0x24]);
        }
        return;
    }

    dst = title;
    p = MiscStrs[0x1a];
    while (*p) *dst++ = *p++;
    p = ScenarioNameStrs[CurGameType];
    while (*p) *dst++ = *p++;
    p = match_position->name;
    while (*p) *dst++ = *p++;
    *dst = 0;
    win_PrintfAtObj(0x180a, title);
    win_PrintfAtObj(0x180b, "%ld", OverallScore);
}

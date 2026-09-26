/* Feedback: tutorial tick gate followed by conditional tutorial/advice messages. */
extern char far * far match_position;
extern unsigned char far Dx8[];
extern int near MeHealth;
extern int near HealthB;
extern int far MeWarnHealth;
extern int far BlkWarnHealth;
extern int far TilesDugB;
extern int far MeMode;
extern long far TimeTemp;
extern int far OptionStates[];
extern int near BpopT;
extern int far TutLesson;
extern int far MeNestStarted;
extern char far * far AdviceStrs[];
extern long far MacTickCount(void);
extern void far GiveLesson(int lesson);
extern int far LessonDone(int lesson);
extern void far EditMessage(int p0, int p1, int width, int p3, int p4);
extern void far SetDefaultWindPrompt(void);

void far Feedback(void)
{
    int far * volatile matchCount;
    int far * volatile lessonActive;
    int lesson;
    int dug;
    int now;

    if (*((int far *)match_position + 0x405a) != 0)
        return;
    ++*(int far *)(Dx8 + 0x85ec);
    if (*(int far *)(Dx8 + 0x85ec) > 0x400)
        *(int far *)(Dx8 + 0x85ec) = 0;
    if ((*(int far *)(Dx8 + 0x85ec) & 7) != 0)
        return;

    matchCount = (int far *)(match_position + 0x7d62);
    ++*matchCount;
    lessonActive = (int far *)(Dx8 + 0x85f0);
    if (*lessonActive == 0) {
        GiveLesson(TutLesson);
        *lessonActive = 1;
    } else if (LessonDone(TutLesson))
        ++TutLesson;

check_match_count:
    if (*matchCount > 15) {
        now = (int)MacTickCount();
        if (now < TimeTemp)
            goto show_feedback;
        if (now > TimeTemp)
            goto check_match_count;
        if (now <= TimeTemp)
            goto show_feedback;
        *lessonActive = 0;
        if (OptionStates[4] != 0)
            goto show_feedback;
        SetDefaultWindPrompt();
        return;
    }

show_feedback:
    lesson = MeMode;
    if (lesson == 0) {
        if (MeWarnHealth > MeHealth) {
            if (MeHealth >= 10)
                goto low_health_notice;
            EditMessage(AdviceStrs[0], AdviceStrs[1], 0x78, 0, 1);
            return;
        }
        if (MeHealth < 10) {
            EditMessage(AdviceStrs[0], AdviceStrs[1], 0x78, 0, 1);
            return;
        }
    }

low_health_notice:
    if (HealthB <= BlkWarnHealth) {
        EditMessage(AdviceStrs[4], AdviceStrs[5], 0x78, 0, 0);
        return;
    }

    dug = TilesDugB;
    if (dug < BpopT && lesson == 0 && MeNestStarted == 0 && dug == 0) {
        EditMessage(AdviceStrs[6], AdviceStrs[7], 0x78, 0, 0);
        return;
    }
    EditMessage(AdviceStrs[8], AdviceStrs[9], 0x78, 0, 0);
}

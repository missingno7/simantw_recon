/* Feedback: tutorial tick gate followed by conditional tutorial/advice messages. */
extern char far match_position[];
extern unsigned char far Dx8[];
extern int near MeHealth;
extern int near HealthB;
extern int near BpopT;
extern int far TutLesson;
extern int far MeNestStarted;
extern unsigned long far * far AdviceStrs;
extern long far MacTickCount(void);
extern void far GiveLesson(int lesson);
extern int far LessonDone(int lesson);
extern void far EditMessage(long position, int width, int p3, int p4);
extern void far SetDefaultWindPrompt(void);

void far Feedback(void)
{
    int far * volatile matchCount;
    int far * volatile lessonActive;
    int lesson;
    int dug;
    long now;

    if (*(int far *)(match_position + 0x80b4) != 0)
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
        now = MacTickCount();
        if (now < *(long far *)(match_position + 0x9b10))
            goto show_feedback;
        if (now > *(long far *)(match_position + 0x9b10))
            goto check_match_count;
        if (now <= *(long far *)(match_position + 0x9b10))
            goto show_feedback;
        *lessonActive = 0;
        if (*(int far *)(Dx8 + 0x85fa) != 0)
            goto show_feedback;
        SetDefaultWindPrompt();
        return;
    }

show_feedback:
    lesson = *(int far *)(Dx8 + 0x9fe8);
    if (lesson == 0) {
        if (HealthB > MeHealth) {
            if (MeHealth >= 10)
                goto low_health_notice;
            EditMessage(AdviceStrs[0], 0x78, 0, 1);
            return;
        }
        if (MeHealth < 10) {
            EditMessage(AdviceStrs[0], 0x78, 0, 1);
            return;
        }
    }

low_health_notice:
    if (HealthB <= *(int far *)(Dx8 + 0x769c)) {
        EditMessage(AdviceStrs[2], 0x78, 0, 0);
        return;
    }

    dug = *(int far *)(Dx8 + 0x72c8);
    if (dug < BpopT && lesson == 0 && MeNestStarted == 0 && dug == 0) {
        EditMessage(AdviceStrs[3], 0x78, 0, 0);
        return;
    }
    EditMessage(AdviceStrs[4], 0x78, 0, 0);
}

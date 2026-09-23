/* Feedback: periodic tutorial bookkeeping and advice prompts, transcribed from observed flow. */
extern char far match_position[];
extern unsigned char far Dx8[];
extern int near MeHealth;
extern int near HealthB;
extern int near BpopT;
extern int far TutLesson;
extern int far MeNestStarted;
extern unsigned int far * far AdviceStrs;
extern long far MacTickCount(void);
extern void far GiveLesson(int lesson);
extern int far LessonDone(int lesson);
extern void far EditMessage(int p0, int p1, int width, int p3, int p4);
extern void far SetDefaultWindPrompt(void);

void far Feedback(void)
{
    int far *matchCount;
    int far *tickStamp;
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
    if (*(int far *)(Dx8 + 0x85f0) == 0) {
        GiveLesson(*(int far *)(Dx8 + 0x85ee));
        *(int far *)(Dx8 + 0x85f0) = 1;
    } else if (LessonDone(*(int far *)(Dx8 + 0x85ee))) {
        ++*(int far *)(Dx8 + 0x85ee);
    }

    if (*matchCount > 15) {
        tickStamp = (int far *)(match_position + 0x9b10);
        now = MacTickCount();
        if (now > *(long far *)tickStamp) {
            *(int far *)(Dx8 + 0x85f0) = 0;
            if (*(int far *)(Dx8 + 0x85fa) == 0) {
                SetDefaultWindPrompt();
                return;
            }
        } else
            goto feedback_advice;
    } else {
feedback_advice:
        lesson = *(int far *)(Dx8 + 0x9fe8);
        if (lesson == 0) {
            if (HealthB > MeHealth) {
                EditMessage(AdviceStrs[0], AdviceStrs[1], 0x78, 0, 1);
                return;
            }
            if (MeHealth < 10) {
                EditMessage(AdviceStrs[4], AdviceStrs[5], 0x78, 0, 0);
                return;
            }
            if (MeHealth >= 10) {
                EditMessage(AdviceStrs[4], AdviceStrs[5], 0x78, 0, 0);
                return;
            }
        }

        if (HealthB <= *(int far *)(Dx8 + 0x769c)) {
            EditMessage(AdviceStrs[8], AdviceStrs[9], 0x78, 0, 0);
            return;
        }

        dug = *(int far *)(Dx8 + 0x72c8);
        if (dug < BpopT && lesson == 0 && MeNestStarted == 0 && dug == 0) {
            EditMessage(AdviceStrs[12], AdviceStrs[13], 0x78, 0, 0);
            return;
        }
        EditMessage(AdviceStrs[16], AdviceStrs[17], 0x78, 0, 0);
        return;
    }

    lesson = *(int far *)(Dx8 + 0x9fe8);
    if (lesson == 0) {
        if (HealthB > MeHealth) {
            EditMessage(AdviceStrs[0], AdviceStrs[1], 0x78, 0, 1);
            return;
        }
        if (MeHealth < 10) {
            EditMessage(AdviceStrs[4], AdviceStrs[5], 0x78, 0, 0);
            return;
        }
        if (MeHealth >= 10) {
            EditMessage(AdviceStrs[4], AdviceStrs[5], 0x78, 0, 0);
            return;
        }
    }
    if (HealthB <= *(int far *)(Dx8 + 0x769c)) {
        EditMessage(AdviceStrs[8], AdviceStrs[9], 0x78, 0, 0);
        return;
    }
    dug = *(int far *)(Dx8 + 0x72c8);
    if (dug < BpopT && lesson == 0 && MeNestStarted == 0 && dug == 0) {
        EditMessage(AdviceStrs[12], AdviceStrs[13], 0x78, 0, 0);
        return;
    }
    EditMessage(AdviceStrs[16], AdviceStrs[17], 0x78, 0, 0);
}

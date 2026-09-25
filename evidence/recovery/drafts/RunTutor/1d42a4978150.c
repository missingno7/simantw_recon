extern int far TutLesson;
#define TutCount (*(&TutLesson - 1))
#define TutFlag  (*(&TutLesson + 1))

extern int far match_position[];

extern void far GiveLesson(int lesson);
extern int far LessonDone(int lesson);
extern long far MacTickCount(void);

void far RunTutor(void)
{
    struct { int far *p; } h1;
    struct { int far *p; } h2;

    if (++TutCount > 0x400)
        TutCount = 0;
    if (TutCount & 7)
        return;

    h1.p = &match_position[16049];
    h2.p = &TutFlag;
    if (*h2.p == 0) {
        GiveLesson(TutLesson);
        *h2.p = 1;
        *h1.p = 0;
        return;
    }

    if (LessonDone(TutLesson)) {
        TutLesson++;
    } else {
        if (*h1.p > 0xf)
            return;
        if (MacTickCount() <= *(long far *)&match_position[19848])
            return;
    }
    *h2.p = 0;
}

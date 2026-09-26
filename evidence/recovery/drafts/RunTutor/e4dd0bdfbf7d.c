extern int far TutorCnt;
extern int far TutLesson;
extern int far TutGiven;
#define TutCount TutorCnt
#define TutFlag  TutGiven

extern int far TutHowLong;
extern long far TimeTemp;

extern void far GiveLesson(int lesson);
extern int far LessonDone(int lesson);
extern long far MacTickCount(void);

void far RunTutor(void)
{
    struct { int far *p; } h1;
    struct { int far *p; } h2;

    {
        int countCopy;
        countCopy = ++TutCount;
        if (countCopy > 0x400) {
            countCopy = 0;
            TutCount = countCopy;
        }
        if (countCopy & 7)
            return;
    }

    h1.p = &TutHowLong;
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
        if (MacTickCount() <= TimeTemp)
            return;
    }
    *h2.p = 0;
}

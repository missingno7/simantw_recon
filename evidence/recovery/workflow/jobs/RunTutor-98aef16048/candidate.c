extern int far Dx8w[];
#define TutCount Dx8w[0x42f6]
#define TutLessonW Dx8w[0x42f7]
#define TutFlagW Dx8w[0x42f8]

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
    h2.p = &TutFlagW;
    if (*h2.p == 0) {
        GiveLesson(TutLessonW);
        *h2.p = 1;
        *h1.p = 0;
        return;
    }

    if (LessonDone(TutLessonW)) {
        TutLessonW++;
    } else {
        if (*h1.p > 0xf)
            return;
        if (MacTickCount() <= *(long far *)&match_position[19848])
            return;
    }
    *h2.p = 0;
}

extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define TutCount (*(int far *)&AT(0x85ec))
#define TutFlag  (*(int far *)&AT(0x85f0))

extern int far TutLesson;
extern int far match_position[];

extern void far GiveLesson(int lesson);
extern int far LessonDone(int lesson);
extern long far MacTickCount(void);

void far RunTutor(void)
{
    int far *p1;
    int far *p2;

    if (++TutCount > 0x400)
        TutCount = 0;
    if (TutCount & 7)
        return;

    p1 = &match_position[16049];
    p2 = &TutFlag;
    if (*p2 == 0) {
        GiveLesson(TutLesson);
        *p2 = 1;
        p1 = &match_position[16049];
        *p1 = 0;
        return;
    }

    if (LessonDone(TutLesson)) {
        TutLesson++;
    } else {
        if (*p1 > 0xf)
            return;
        if (MacTickCount() <= *(long far *)&match_position[19848])
            return;
    }
    *p2 = 0;
}

extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define WORD_AT(off) (*(int far *)&AT(off))

extern int far match_position[];

extern void far GiveLesson(int lesson);
extern int far LessonDone(int lesson);
extern long far MacTickCount(void);

void far RunTutor(void)
{
    struct { int far *p; } h1;
    struct { int far *p; } h2;

    if (++WORD_AT(0x85ec) > 0x400)
        WORD_AT(0x85ec) = 0;
    if (WORD_AT(0x85ec) & 7)
        return;

    h1.p = &match_position[16049];
    h2.p = (int far *)&AT(0x85f0);
    if (*h2.p == 0) {
        GiveLesson(WORD_AT(0x85ee));
        *h2.p = 1;
        *h1.p = 0;
        return;
    }

    if (LessonDone(WORD_AT(0x85ee))) {
        WORD_AT(0x85ee)++;
    } else {
        if (*h1.p > 0xf)
            return;
        if (MacTickCount() <= *(long far *)&match_position[19848])
            return;
    }
    *h2.p = 0;
}

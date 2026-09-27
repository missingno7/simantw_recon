/*
 * UnRecruitRed: walk the red-recruit A-list from the top (ListIndexA,
 * far selector slot 0xc4d2 -- the same index RecruitRed reads/writes,
 * see src/recovered/wf_RecruitRed-253bf13685.c), decrementing first
 * each iteration (a do-while with the decrement at the top, matching
 * the bottom test reusing the already-decremented index).  A record
 * whose AlistT type byte (Dx8+0x2f62) is nonzero and above 0x7f (a
 * live red ant) is retired -- its AlistM mode byte (Dx8+0x2b78) is
 * cleared to 0 when currently 6.
 */
extern int far ListIndexA;
extern unsigned char far Dx8[];

void far UnRecruitRed(void)
{
    int index;

    index = ListIndexA;
    if (index <= 0)
        return;

    do {
        int type;

        index--;
        type = Dx8[index + 0x2f62];
        if (type != 0 && type > 0x7f) {
            if (Dx8[index + 0x2b78] == 6)
                Dx8[index + 0x2b78] = 0;
        }
    } while (index > 0);
}

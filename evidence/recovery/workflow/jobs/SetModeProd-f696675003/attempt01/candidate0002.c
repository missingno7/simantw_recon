/*
 * SetModeProd: choose the B colony's production mode.  The first three
 * far ModePopB counts are summed; each count is scaled to a 0..65535
 * share of the total (unsigned long arithmetic) and the original count
 * subtracted, giving how far each mode is above its share.  The mode
 * with the largest surplus (first one wins ties, none above zero gives
 * mode 0) selects ModeMe from the far ModeTabB table.
 */
extern int far ModePopB[];
extern int far ModeTabB[];
extern int far ModeMe;

void far SetModeProd(void)
{
    int scaled[6];
    int diff[6];
    int total;
    int i;
    int far *p;
    int near *q;
    int best;
    int max;

    total = 0;
    for (p = ModePopB; p < ModePopB + 3; p++)
        total += *p;
    for (i = 0; i < 3; i++)
        scaled[i] = (unsigned long)ModePopB[i] * total / 0xffffL;
    for (i = 0; i < 3; i++)
        diff[i] = scaled[i] - ModePopB[i];
    i = 0;
    max = 0;
    best = 0;
    for (q = diff; q < diff + 3; q++) {
        if (*q > max) {
            max = *q;
            best = i;
        }
        i++;
    }
    ModeMe = ModeTabB[best];
}

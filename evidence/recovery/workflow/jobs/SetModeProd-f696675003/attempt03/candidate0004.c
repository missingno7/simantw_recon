/*
 * SetModeProd: choose the B colony's production mode.  The three far
 * ModePopB caste counts are summed; each far modeLevels share (0..65535)
 * is scaled by the total (unsigned long arithmetic) and the actual count
 * subtracted, giving how far each caste is below its wanted level.  The mode
 * with the largest surplus (first one wins ties, none above zero gives
 * mode 0) selects ModeMe from the far ModeTabB table.
 */
extern int far ModePopB[];
extern int far modeLevels[];
extern int far ModeTabB[];
extern int far ModeMe;

void far SetModeProd(void)
{
    int scaled[6];
    int diff[6];
    int total;
    int best;
    int i;
    int max;
    int near *q;

    total = 0;
    for (i = 0; i < 3; i++)
        total += ModePopB[i];
    for (i = 0; i < 3; i++)
        scaled[i] = (unsigned)modeLevels[i] * (long)total / 65535L;
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

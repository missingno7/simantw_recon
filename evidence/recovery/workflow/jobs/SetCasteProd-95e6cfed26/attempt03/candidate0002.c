/*
 * SetCasteProd: choose which caste the black colony should produce next.
 * The current populations of the four castes (CastePopB[1..4]) and the
 * ideal caste levels (IdealCaste[0..3]) are totalled; each caste's
 * current and ideal percentages are computed with a 32-bit product and
 * the runtime long division (zero when the total is not positive).  The
 * caste whose current share falls furthest below its ideal share (most
 * negative difference, index 0 by default) selects MakeMe from the
 * black caste table.  The population total variable is reused for the
 * chosen index (both live in the same frame slot).
 */
extern int near CastePopB[];
extern int far IdealCaste[];
extern int far CasteTabB[];
extern int far MakeMe;

void far SetCasteProd(void)
{
    register int best;
    int i;
    int total;
    int ideal;
    int pct[4];
    int want[4];

    total = 0;
    ideal = 0;
    for (i = 0; i < 4; i++) {
        total += CastePopB[i + 1];
        ideal += IdealCaste[i];
    }
    for (i = 0; i < 4; i++) {
        if (total <= 0)
            pct[i] = 0;
        else
            pct[i] = 100L * CastePopB[i + 1] / total;
        if (ideal <= 0)
            want[i] = 0;
        else
            want[i] = 100L * IdealCaste[i] / ideal;
    }
    best = 0;
    total = 0;
    for (i = 0; i < 4; i++) {
        if (pct[i] - want[i] < best) {
            best = pct[i] - want[i];
            total = i;
        }
    }
    MakeMe = CasteTabB[total];
}

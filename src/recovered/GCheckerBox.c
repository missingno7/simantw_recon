/* Candidate reconstruction of the checker-box color adapter. */
extern unsigned int near _foreColor;
extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);

void GCheckerBox(int left, int top, int right, int bottom)
{
    unsigned int pattern;
    pattern = (((_foreColor >> 8) + 0x10) << 8) | 0x20;
    GPatBox(left, top, right, bottom, pattern);
}

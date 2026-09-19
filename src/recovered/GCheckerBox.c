/* Candidate reconstruction of the checker-box color adapter. */
extern unsigned int near _foreColor;
extern void far GPatBox(unsigned int pattern, int left, int top, int right, int bottom);

void GCheckerBox(int left, int top, int right, int bottom)
{
    unsigned int pattern;
    pattern = (((_foreColor >> 8) + 0x10) << 8) | 0x20;
    GPatBox(pattern, left, top, right, bottom);
}

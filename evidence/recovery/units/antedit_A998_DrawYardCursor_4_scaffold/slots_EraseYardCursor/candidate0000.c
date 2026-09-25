struct YardPoint {
    int x;
    int y;
};

extern struct YardPoint far CurYardPnt;
extern int near patchRgn2[];
extern void far InvertPatch(int x, int y);

void EraseYardCursor(void)
{
    if (patchRgn2[9]) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 0;
    }
}

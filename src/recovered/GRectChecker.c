struct CheckerRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near _foreColor;
extern void far GPatBox(int left, int top, int right, int bottom, int pattern);

void GRectChecker(struct CheckerRect far *rect)
{
    int pattern;
    pattern = (((_foreColor >> 8) + 16) << 8) | 0x20;
    GPatBox(rect->left, rect->top, rect->right, rect->bottom, pattern);
}

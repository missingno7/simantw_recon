/*
 * SetTriLatPoint: place a point at a given "lateral" level inside the
 * caste/mode triangle diagram.  level->frac is a 0..65535 fixed-point
 * fraction of the triangle's height; the point's y is triHeight-2
 * scaled by (1-frac) plus rect->top.  level->weight, combined with the
 * remaining row width (triWidth minus twice the frac-scaled triWidthL
 * margin), gives x along the sloped edge scaled by frac, plus
 * rect->right and the margin; frac==0xFFFF (unset) or too few rows left
 * (<3) instead place x at rect->left.  x is stored two pixels in from
 * the computed edge.
 */
struct TriLevel {
    unsigned int frac;
    int unused2;
    unsigned int weight;
};

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Point {
    int x;
    int y;
};

extern unsigned int far triWidth;
extern unsigned int far triWidthL;
extern unsigned int far triHeight;

void far SetTriLatPoint(struct TriLevel far *level, struct Rect far *rect, struct Point far *out)
{
    unsigned int widthTerm;
    int row;
    int x;
    unsigned long fracL;
    register struct Point far *pOut;

    pOut = out;
    fracL = level->frac;
    pOut->y = (triHeight - 2) * (0xFFFFUL - fracL) / 65535UL;
    pOut->y += rect->top;

    widthTerm = triWidthL * fracL / 65535UL;
    row = triWidth - 2 * widthTerm;

    if (level->frac != 0xFFFF && row >= 3)
        x = (long)(row - 3) * level->weight / (unsigned long)(0xFFFF - level->frac) + rect->right + widthTerm;
    else
        x = rect->left;
    pOut->x = x + 2;
}

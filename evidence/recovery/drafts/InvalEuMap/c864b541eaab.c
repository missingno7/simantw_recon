/*
 * InvalEuMap: mark a rectangle of edit-map cells (columns left..right,
 * rows top..bottom) as invalid (-1) in the private far word buffer that
 * mirrors the edit view (editWidth cells per row).  The left/top edges
 * are clamped at 0, otherwise the right/bottom edges at 127 and 63; only
 * cells inside the editWidth by editHeight view are written.
 */
extern int near editWidth;
extern int near editHeight;
static int far *euMap;

void far InvalEuMap(int left, int top, int right, int bottom)
{
    int row;
    int col;
    int cell;
    int index;
    int far *p;

    if (left < 0)
        left = 0;
    else if (right > 127)
        right = 127;
    if (top < 0)
        top = 0;
    else if (bottom > 63)
        bottom = 63;
    for (row = top; row <= bottom; row++) {
        cell = editWidth * row + left;
        for (col = left, index = cell; col <= right; col++, index++) {
            if (col >= 0 && col < editWidth && row >= 0 && row < editHeight)
                euMap[index] = -1;
        }
        cell += editWidth;
    }
}

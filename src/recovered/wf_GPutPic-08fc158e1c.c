/*
 * Hypothesis: dispatch a picture record to the color or monochrome
 * renderer.  The record begins with two word dimensions and its payload
 * begins four bytes later; the final argument is the renderer mask.
 */
extern unsigned char near displayType;
extern void far DoBitmap(int x, int y, int width, int height,
                         void far *data, int mask);
extern void far DoMonoBitmap(int x, int y, int width, int height,
                             void far *data, int mask);

void far GPutPic(int x, int y, unsigned char far *picture, int mask)
{
    struct Local {
        int x;
        int y;
    } local;

    local.x = x;
    local.y = y;
    if (!(displayType & 1))
        DoBitmap(local.x, local.y, *(int far *)picture,
                 *(int far *)(picture + 2), (void far *)(picture + 4),
                 mask);
    else
        DoMonoBitmap(local.x, local.y, *(int far *)picture,
                     *(int far *)(picture + 2),
                     (void far *)(picture + 4), mask);
}

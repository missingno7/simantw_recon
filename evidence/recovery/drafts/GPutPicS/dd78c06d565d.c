/*
 * Hypothesis: GPutPicS preserves the first two coordinates in a two-word
 * local, then adapts the remaining five arguments for the bitmap renderer.
 * Single-display mode selects DoMonoBitmap; otherwise DoBitmap is used.
 */
extern unsigned char near displayType;
extern void far DoBitmap(int x, int y, int arg3, int arg4,
                         int arg5, int arg6, int arg7);
extern void far DoMonoBitmap(int x, int y, int arg3, int arg4,
                             int arg5, int arg6, int arg7);

void far GPutPicS(int first, int second, int third, int fourth,
                  int fifth, int sixth, int seventh)
{
    struct Local {
        int x;
        int y;
    } local;

    local.x = first;
    local.y = second;
    if (!(displayType & 1))
        DoBitmap(local.x, local.y, fifth, sixth,
                 third, fourth, seventh);
    else
        DoMonoBitmap(local.x, local.y, fifth, sixth,
                     third, fourth, seventh);
}

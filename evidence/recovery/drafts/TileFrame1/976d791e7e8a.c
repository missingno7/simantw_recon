/*
 * TileFrame1(top, bottom, left, right): draws a rectangular frame border
 * into MapA using the same inline rectangle-fill shape as MakeOutletH/V
 * (rep-stosb from a doubly-nested loop, width/height computed by
 * subtracting the same bound twice so the degenerate single-row/column
 * cases still produce a real runtime width/height of 1 rather than being
 * folded away): the left edge column (rows top..bottom) is filled with
 * 0x54, the right edge column with 0x51, the top edge row (columns
 * left..right) with 0x5a, the bottom edge row with 0x5b, each guarded by
 * top<=bottom or left<=right respectively, and finally the four corners
 * are set individually: (top,left)=0x53, (bottom,left)=0x55,
 * (top,right)=0x50, (bottom,right)=0x52. MapA is reused verbatim from the
 * admitted MakePlugH/MakePlugV/MakeKnob/MakePenny/MakeClip family in this
 * same unit (simone:3120), all of which index it as MapA[(row<<6)+col].
 */
extern unsigned char near MapA[];

void far TileFrame1(int top, int bottom, int left, int right)
{
    int r;
    int c;

    for (r = top; r <= bottom; r++) {
        for (c = left; c <= left; c++)
            MapA[(r << 6) + c] = 0x54;
    }

    for (r = top; r <= bottom; r++) {
        for (c = right; c <= right; c++)
            MapA[(r << 6) + c] = 0x51;
    }

    for (r = top; r <= top; r++) {
        for (c = left; c <= right; c++)
            MapA[(r << 6) + c] = 0x5a;
    }

    for (r = bottom; r <= bottom; r++) {
        for (c = left; c <= right; c++)
            MapA[(r << 6) + c] = 0x5b;
    }

    MapA[(top << 6) + left] = 0x53;
    MapA[(bottom << 6) + left] = 0x55;
    MapA[(top << 6) + right] = 0x50;
    MapA[(bottom << 6) + right] = 0x52;
}

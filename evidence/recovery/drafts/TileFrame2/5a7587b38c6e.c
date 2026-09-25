/*
 * TileFrame2(top, bottom, left, right): second frame-border variant, byte-
 * identical in size and structure to the accepted-shape TileFrame1 sibling
 * (build/grind/agentW/TileFrame1.c, MATCH_BLOCKED) with different tile
 * codes: left edge column (rows top..bottom) = 0x51, right edge column =
 * 0x54, top edge row (columns left..right) = 0x5b, bottom edge row = 0x5a,
 * each guarded the same way, and corners (top,left)=0x56,
 * (bottom,left)=0x58, (top,right)=0x57, (bottom,right)=0x59. MapA is
 * reused verbatim from the admitted MakePlugH/MakePlugV/MakeKnob/
 * MakePenny/MakeClip family in this same unit (simone:3120).
 */
extern unsigned char near MapA[];

void far TileFrame2(int top, int bottom, int left, int right)
{
    int r;
    int c;

    for (r = top; r <= bottom; r++) {
        for (c = left; c <= left; c++)
            MapA[(r << 6) + c] = 0x51;
    }

    for (r = top; r <= bottom; r++) {
        for (c = right; c <= right; c++)
            MapA[(r << 6) + c] = 0x54;
    }

    for (r = top; r <= top; r++) {
        for (c = left; c <= right; c++)
            MapA[(r << 6) + c] = 0x5b;
    }

    for (r = bottom; r <= bottom; r++) {
        for (c = left; c <= right; c++)
            MapA[(r << 6) + c] = 0x5a;
    }

    MapA[(top << 6) + left] = 0x56;
    MapA[(bottom << 6) + left] = 0x58;
    MapA[(top << 6) + right] = 0x57;
    MapA[(bottom << 6) + right] = 0x59;
}

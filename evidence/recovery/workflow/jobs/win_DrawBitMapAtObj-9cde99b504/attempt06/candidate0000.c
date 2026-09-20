/*
 * Draw the bitmap descriptor stored in an object when its drawable flag is
 * set.  The descriptor's first word is an offset into this code segment, so
 * the historical call passes it as a far pointer with CS as its segment.  If
 * the bitmap draw reports failure, fill the object rectangle using the mono
 * pattern combined with the current foreground color.
 */
struct BitmapObject {
    unsigned int bitmapOffset;
    unsigned int bitmapArgument;
    unsigned char reserved[0x20];
    unsigned char flags;
};

extern int far win_DrawBitMap(unsigned int bitmapOffset,
                              int bitmapArgument, int value);
extern void far GRectFill(unsigned int objectOffset,
                          unsigned int objectSegment, int color);
extern char near monoPat;
extern int near _foreColor;

void win_DrawBitMapAtObj(struct BitmapObject far *object, int value)
{
    int color;

    if ((object->flags & 1) == 0)
        return;

    if (win_DrawBitMap(object->bitmapOffset, object->bitmapArgument, value) == 0) {
        color = (int)monoPat | _foreColor;
        GRectFill((unsigned int)object,
                  (unsigned int)(((unsigned long)object) >> 16), color);
    }
}

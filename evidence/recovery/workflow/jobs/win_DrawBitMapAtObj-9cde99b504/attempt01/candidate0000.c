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

extern int near win_DrawBitMap(unsigned char far *bitmap,
                               int bitmapArgument, int value);
extern void far GRectFill(struct BitmapObject far *object, int color);
extern char near monoPat;
extern int near _foreColor;

void win_DrawBitMapAtObj(struct BitmapObject far *object, int value)
{
    if ((object->flags & 1) == 0)
        return;

    if (win_DrawBitMap((unsigned char far *)object->bitmapOffset,
                       object->bitmapArgument, value) == 0)
        GRectFill(object, (int)monoPat | _foreColor);
}

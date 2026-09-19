/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
struct WinObject {
    unsigned char unused[0x24];
    unsigned char flags;
};

extern void far win_DrawObjectI(unsigned int offset, unsigned int segment);

void win_DrawObject(struct WinObject far *object)
{
    if (object->flags & 1)
        win_DrawObjectI((unsigned int)(unsigned long)object,
                        (unsigned int)((unsigned long)object >> 16));
}

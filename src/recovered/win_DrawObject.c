struct GameObject {
    unsigned char reserved[0x24];
    unsigned int flags;
};

extern void far win_DrawObjectI(unsigned long object);

void win_DrawObject(struct GameObject far *object)
{
    if (object->flags & 1)
        win_DrawObjectI((unsigned long)object);
}

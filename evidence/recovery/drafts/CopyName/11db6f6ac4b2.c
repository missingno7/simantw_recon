/* Space-fill a 16-byte name, copy at most 16 source bytes, and terminate. */
extern void far * memset(void far *, int, unsigned);
extern unsigned strlen(char far *);
extern void far * memcpy(void far *, const void far *, unsigned);
void CopyName(char far *destination, const char far *source)
{
    unsigned length;
    memset(destination, ' ', 16);
    length = strlen((char far *)source);
    if (length > 16)
        length = 16;
    memcpy(destination, source, length);
    destination[15] = 0;
}

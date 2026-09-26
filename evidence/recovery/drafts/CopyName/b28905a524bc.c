extern void *memset(void *, int, unsigned);
extern unsigned strlen(const char far *);
extern void *memcpy(void *, const void far *, unsigned);
/* Pad a 16-byte name with spaces, copy the source prefix, and terminate. */
void CopyName(char far *destination, const char far *source)
{
    unsigned length;
    memset(destination, ' ', 16);
    length = strlen(source);
    if (length > 16)
        length = 16;
    memcpy(destination, source, length);
    destination[15] = 0;
}

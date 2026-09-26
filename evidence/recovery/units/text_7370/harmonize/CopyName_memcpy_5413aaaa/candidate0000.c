extern void *memset(void *, int, unsigned);
extern unsigned strlen(const char far *);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
/* Pad a 16-byte name with spaces, copy the source prefix, and terminate. */
void CopyName(char far *destination, const char far *source)
{
    int length;
    memset(destination, ' ', 16);
    length = strlen(source);
    if (length > 16)
        length = 16;
    memcpy(destination, source, length);
    destination[15] = 0;
}

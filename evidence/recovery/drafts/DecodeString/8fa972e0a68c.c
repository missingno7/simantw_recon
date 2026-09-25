/* Pointer walk hypothesis: MSC recognizes the zero terminator scan as REPNE SCASB. */
/* DecodeString replaces the previous decoded buffer and swaps the high and low nibbles of each byte. */
static unsigned int decodedHandle;
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far mem_Free(int handle);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

char far * far DecodeString(char far *source)
{
    unsigned int i;
    char far *cursor;
    char far *destination;
    i = 0;
    if (decodedHandle != 0) {
        mem_Unlock(decodedHandle);
        mem_Free(decodedHandle);
    }
    cursor = source;
    while (*cursor != 0) cursor++;
    decodedHandle = mem_Alloc((unsigned long)(cursor - source), 1, "decode");
    destination = (char far *)mem_Lock(decodedHandle);
    for (i = 0; source[i] != 0; i++) {
        signed char c;
        c = source[i];
        destination[i] = (char)((c << 4) | (c >> 4));
    }
    destination[i] = 0;
    return destination;
}

/* DecodeString releases the old decoded buffer, allocates a replacement, and swaps each source byte's nibbles. */
static unsigned int decodedHandle;
static char far decodedBufferName[] = "DecodeString";
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far mem_Free(int handle);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
char far * far DecodeString(char far *source)
{
    unsigned int length;
    unsigned int i;
    char far *destination;
    length = 0;
    while (source[length] != 0) length++;
    if (decodedHandle != 0) {
        mem_Unlock(decodedHandle);
        mem_Free(decodedHandle);
    }
    decodedHandle = mem_Alloc((unsigned long)length, 1, decodedBufferName);
    destination = (char far *)mem_Lock(decodedHandle);
    i = 0;
    while (source[i] != 0) {
        unsigned char c;
        c = (unsigned char)source[i];
        destination[i] = (char)((c << 4) | (c >> 4));
        i++;
    }
    destination[i] = 0;
    return destination;
}

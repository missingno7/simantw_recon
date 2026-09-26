/* The shift-and-mask expression matches the nibble-swap arithmetic in the target. */
static unsigned int decodedHandle = 0;
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far mem_Free(int handle);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern unsigned int far strlen(char far *text);
char far * far DecodeString(char far *source)
{
    unsigned int i;
    char far *destination;
    i = 0;
    if (decodedHandle != 0) {
        mem_Unlock(decodedHandle);
        mem_Free(decodedHandle);
    }
    decodedHandle = mem_Alloc((unsigned long)strlen(source), 1, "decode");
    destination = (char far *)mem_Lock(decodedHandle);
    for (i = 0; source[i] != 0; i++) {
        signed char c;
        c = source[i];
        destination[i] = (char)((c << 4) ^ ((((c << 4) ^ (c >> 4))) & 0x0f));
    }
    destination[i] = 0;
    return destination;
}

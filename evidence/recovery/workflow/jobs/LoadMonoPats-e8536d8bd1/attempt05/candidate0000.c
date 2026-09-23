/* Load the two monochrome pattern blocks, complementing packed bytes as
   they are copied into the data segment's pattern arrays. */
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far *far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far Punt(char far *message, ...);
extern unsigned char near YardPats[24];
extern unsigned char near DMPat[];

void far LoadMonoPats(void)
{
    unsigned int handle;
    unsigned char far *source;
    unsigned char far *destination;
    unsigned int firstCount;
    int secondCount;

    handle = db_LoadObject(0x2710, 0x16, 0);
    source = (unsigned char far *)mem_Lock(handle);
    if (handle == 0 || *(unsigned int far *)source != 0x300)
        Punt("Cannot load monochrome patterns.");
    source += 2;
    destination = (unsigned char far *)YardPats;
    firstCount = 0x18;
    do {
        *destination++ = (unsigned char)~*source++;
    } while (--firstCount != 0);
    mem_Unlock(handle);
    db_PurgeObject(0x2710, 0x16);

    handle = db_LoadObject(0x271a, 0x16, 0);
    if (handle == 0)
        Punt("Cannot load monochrome patterns.");
    source = (unsigned char far *)mem_Lock(handle);
    destination = (unsigned char far *)DMPat;
    secondCount = (int)((signed char)source[1]) << 3;
    source += 2;
    if (secondCount > 0) {
        do {
            *destination++ = (unsigned char)~*source++;
        } while (--secondCount != 0);
    }
    mem_Unlock(handle);
    db_PurgeObject(0x271a, 0x16);
}

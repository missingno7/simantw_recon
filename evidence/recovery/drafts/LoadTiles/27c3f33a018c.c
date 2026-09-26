/*
 * Hypothesis: load the edit bitmap resources from the object database,
 * copy each locked resource into a display-ready buffer, convert its mask
 * on color displays, then release the database object for later reuse.
 */
extern unsigned char near displayType;
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far db_UnhookObject(int object, int kind);
extern unsigned long far mem_Size(unsigned int handle);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern void far ConvertMaskBitmap(void far *destination, void far *source);

void far LoadTiles(void)
{
    unsigned int sourceHandle;
    unsigned int displayHandle;
    char far *source;
    char far *destination;
    unsigned long bytes;
    unsigned long i;
    int resource;

    for (resource = 0x0d; resource <= 0x14; ++resource) {
        sourceHandle = db_LoadObject(resource, 9, 1);
        if (sourceHandle == 0) {
            db_UnhookObject(resource, 9);
            continue;
        }

        bytes = mem_Size(sourceHandle);
        source = (char far *)mem_Lock(sourceHandle);
        displayHandle = mem_Alloc(bytes + 0x80L, 1, (char far *)0);
        if (displayHandle != 0) {
            destination = (char far *)mem_Lock(displayHandle);
            if (destination != 0 && source != 0) {
                for (i = 0; i < bytes; ++i)
                    destination[i] = source[i];
                if ((displayType & 1) == 0)
                    ConvertMaskBitmap(destination, source);
            }
            mem_Unlock(displayHandle);
        }

        mem_Unlock(sourceHandle);
        if (displayHandle == 0)
            mem_Free(sourceHandle);
        db_PurgeObject(resource, 9);
        db_UnhookObject(resource, 9);
    }
}

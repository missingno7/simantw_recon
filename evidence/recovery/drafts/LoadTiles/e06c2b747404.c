/*
 * Hypothesis: load the edit bitmap resources from the object database,
 * copy each locked resource into a display-ready buffer, convert its mask
 * on color displays, then release the database object for later reuse.
 */
extern unsigned char near displayType;
extern int far match_position;
extern int far match_length;
extern int far editBufInvalidFlag[];
extern int far pack_buf;
extern int far TERRAINset;
extern int far tileDsp;
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far db_UnhookObject(int object, int kind);
extern unsigned long far mem_Size(unsigned int handle);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern void far * far _fmemcpy(void far *destination, const void far *source, unsigned int count);
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
    unsigned int frame;

    match_position = 0;
    match_length = 0;
    editBufInvalidFlag[0] = 0;
    TERRAINset = 0;
    if (pack_buf != 0)
        mem_Free((unsigned int)pack_buf);
    pack_buf = 0;

    sourceHandle = db_LoadObject(0x0a, 9, 1);
    if (sourceHandle != 0) {
        source = (char far *)mem_Lock(sourceHandle);
        if (source != 0) {
            bytes = mem_Size(sourceHandle);
            if ((displayType & 1) == 0) {
                for (frame = 0; frame < 3; ++frame) {
                    if ((unsigned long)(frame + 1) * 0x50L < bytes)
                        ConvertMaskBitmap(source + frame * 0x50,
                                          source + frame * 0x50 + 0x10);
                }
            }
            mem_Unlock(sourceHandle);
        }
    }
    db_UnhookObject(0x0a, 9);
    displayType = 1;
    tileDsp = 1;
    displayType = 0x0a;

    for (resource = 0x12; resource <= 0x14; ++resource) {
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
                _fmemcpy(destination, source, (unsigned int)bytes);
                if ((displayType & 1) == 0) {
                    for (frame = 0; frame < 3; ++frame) {
                        if ((unsigned long)(frame + 1) * 0x50L < bytes)
                            ConvertMaskBitmap(destination + frame * 0x50,
                                              source + frame * 0x50 + 0x10);
                    }
                }
            }
            mem_Unlock(displayHandle);
        }

        mem_Unlock(sourceHandle);
        if (displayHandle == 0)
            mem_Free(sourceHandle);
        db_PurgeObject(resource, 9);
        db_UnhookObject(resource, 9);
    }

    for (resource = 0x0f; resource <= 0x11; ++resource) {
        sourceHandle = db_LoadObject(resource, 9, 1);
        if (sourceHandle != 0) {
            source = (char far *)mem_Lock(sourceHandle);
            bytes = mem_Size(sourceHandle);
            displayHandle = mem_Alloc(bytes + 0x80L, 1, (char far *)0);
            if (displayHandle != 0 && source != 0) {
                destination = (char far *)mem_Lock(displayHandle);
                _fmemcpy(destination, source, (unsigned int)bytes);
                if (displayType != 0x0a)
                    ConvertMaskBitmap(destination, source);
                mem_Unlock(displayHandle);
            }
            mem_Unlock(sourceHandle);
            db_PurgeObject(resource, 9);
        }
        db_UnhookObject(resource, 9);
    }

    for (resource = 0x0d; resource <= 0x0e; ++resource) {
        sourceHandle = db_LoadObject(resource, 9, 1);
        if (sourceHandle != 0) {
            source = (char far *)mem_Lock(sourceHandle);
            bytes = mem_Size(sourceHandle);
            displayHandle = mem_Alloc(bytes + 0x80L, 1, (char far *)0);
            if (displayHandle != 0 && source != 0) {
                destination = (char far *)mem_Lock(displayHandle);
                _fmemcpy(destination, source, (unsigned int)bytes);
                ConvertMaskBitmap(destination, source);
                mem_Unlock(displayHandle);
            }
            mem_Unlock(sourceHandle);
            db_PurgeObject(resource, 9);
        }
        db_UnhookObject(resource, 9);
    }
}

/*
 * Load the editor's three tile families.  A display buffer is kept for the
 * nest and over tiles; on indexed displays each 0xa0-byte source tile is
 * expanded into a 0x80-byte color bitmap and its trailing mask.  True-color
 * displays retain the three source resources as 0x5000-byte bands.
 */
static int __based(__segname("SIMANT_DATA_GROUP")) terrainSetState;
extern int far TERRAINset;
extern unsigned int __based(__segname("PACK")) terrainTiles;
extern int __based(__segname("PACK")) tileBufOver;
extern int __based(__segname("PACK")) tileBufNest;
extern int far tileDsp;
extern unsigned char near displayType;

extern void far mem_Free(unsigned int handle);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far db_UnhookObject(int object, int kind);
extern unsigned long far mem_Size(unsigned int handle);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far *_fmemcpy(void far *destination, const void far *source,
                          unsigned int count);
extern void far ConvertMaskBitmap(unsigned char huge *colorBits,
                                  unsigned char huge *maskBits,
                                  unsigned char huge *source,
                                  int height, int width);

void far LoadTiles(void)
{
    int far *overHandle;
    int __based(__segname("PACK")) *nestHandle;
    unsigned int __based(__segname("PACK")) *terrainHandle;
    unsigned int dbHandle;
    unsigned int copySize;
    unsigned int rows;
    unsigned long rowOffset;
    unsigned long bandOffset;
    unsigned char far *copyDestination;
    unsigned char far *copySource;
    unsigned char huge *convertDestination;
    unsigned char huge *convertSource;
    unsigned char huge *pixels12;
    unsigned char huge *pixels13;
    unsigned char huge *pixels14;
    unsigned char huge *pixels0f;
    unsigned char huge *pixels10;
    unsigned char huge *pixels11;

    overHandle = &tileBufOver;
    *overHandle = 0;
    nestHandle = &tileBufNest;
    *nestHandle = 0;
    terrainHandle = &terrainTiles;
    *terrainHandle = 0;

    if (terrainSetState != 0) {
        terrainSetState = 0;
        TERRAINset = 0;
        if (*terrainHandle != 0)
            mem_Free(*terrainHandle);
        *terrainHandle = db_LoadObject(0x0a, 9, 1);
        db_UnhookObject(0x0a, 9);
    }

    if ((displayType & 1) == 0) {
        tileDsp = 1;
        if (displayType == 0x0a) {
            /* Cache the three nest images consecutively in the nest buffer. */
            *nestHandle = mem_Alloc(0xf009L, 1, (char far *)"tilebufnest");
            copyDestination = (unsigned char far *)mem_Lock(*nestHandle);

            dbHandle = db_LoadObject(0x12, 9, 1);
            copySize = (unsigned int)mem_Size(dbHandle);
            copySource = (unsigned char far *)mem_Lock(dbHandle);
            _fmemcpy(copyDestination, copySource, copySize);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x12, 9);

            dbHandle = db_LoadObject(0x13, 9, 1);
            copySize = (unsigned int)mem_Size(dbHandle);
            copySource = (unsigned char far *)mem_Lock(dbHandle);
            _fmemcpy(copyDestination + 0x4000, copySource, copySize);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x13, 9);

            dbHandle = db_LoadObject(0x14, 9, 1);
            copySize = (unsigned int)mem_Size(dbHandle);
            copySource = (unsigned char far *)mem_Lock(dbHandle);
            _fmemcpy(copyDestination + 0x8000, copySource, copySize);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x14, 9);
            mem_Unlock(*nestHandle);

            /* Cache the three overlay images in the over buffer. */
            *overHandle = mem_Alloc(0xf009L, 1, (char far *)"tilebufover");
            copyDestination = (unsigned char far *)mem_Lock(*overHandle);

            dbHandle = db_LoadObject(0x0f, 9, 1);
            copySize = (unsigned int)mem_Size(dbHandle);
            copySource = (unsigned char far *)mem_Lock(dbHandle);
            _fmemcpy(copyDestination, copySource, copySize);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x0f, 9);

            dbHandle = db_LoadObject(0x10, 9, 1);
            copySize = (unsigned int)mem_Size(dbHandle);
            copySource = (unsigned char far *)mem_Lock(dbHandle);
            _fmemcpy(copyDestination + 0x4000, copySource, copySize);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x10, 9);

            dbHandle = db_LoadObject(0x11, 9, 1);
            copySize = (unsigned int)mem_Size(dbHandle);
            copySource = (unsigned char far *)mem_Lock(dbHandle);
            _fmemcpy(copyDestination + 0x8000, copySource, copySize);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x11, 9);
            mem_Unlock(*overHandle);
        } else {
            /* Convert each fixed 128-tile family into the nest buffer. */
            *nestHandle = mem_Alloc(0xf009L, 1, (char far *)"tilebufnest");
            convertDestination = (unsigned char huge *)mem_Lock(*nestHandle);

            dbHandle = db_LoadObject(0x12, 9, 1);
            (void)mem_Size(dbHandle);
            convertSource = (unsigned char huge *)mem_Lock(dbHandle);
            rowOffset = 0L;
            rows = 0x80;
            do {
                pixels12 = convertDestination + rowOffset;
                ConvertMaskBitmap(pixels12, pixels12 + 0x80L,
                                  convertSource + rowOffset, 0x10, 0x10);
                rowOffset += 0xa0L;
            } while (--rows != 0);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x12, 9);

            dbHandle = db_LoadObject(0x13, 9, 1);
            (void)mem_Size(dbHandle);
            convertSource = (unsigned char huge *)mem_Lock(dbHandle);
            rowOffset = 0L;
            bandOffset = 0x5000L;
            rows = 0x80;
            do {
                pixels13 = convertDestination + bandOffset + rowOffset;
                ConvertMaskBitmap(pixels13, pixels13 + 0x80L,
                                  convertSource + rowOffset, 0x10, 0x10);
                rowOffset += 0xa0L;
            } while (--rows != 0);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x13, 9);

            dbHandle = db_LoadObject(0x14, 9, 1);
            (void)mem_Size(dbHandle);
            convertSource = (unsigned char huge *)mem_Lock(dbHandle);
            rowOffset = 0L;
            bandOffset = 0xa000L;
            rows = 0x80;
            do {
                pixels14 = convertDestination + bandOffset + rowOffset;
                ConvertMaskBitmap(pixels14, pixels14 + 0x80L,
                                  convertSource + rowOffset, 0x10, 0x10);
                rowOffset += 0xa0L;
            } while (--rows != 0);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x14, 9);
            mem_Unlock(*nestHandle);

            /* Repeat the mask conversion for the overlay family. */
            *overHandle = mem_Alloc(0xf009L, 1, (char far *)"tilebufover");
            convertDestination = (unsigned char huge *)mem_Lock(*overHandle);

            dbHandle = db_LoadObject(0x0f, 9, 1);
            (void)mem_Size(dbHandle);
            convertSource = (unsigned char huge *)mem_Lock(dbHandle);
            rowOffset = 0L;
            rows = 0x80;
            do {
                pixels0f = convertDestination + rowOffset;
                ConvertMaskBitmap(pixels0f, pixels0f + 0x80L,
                                  convertSource + rowOffset, 0x10, 0x10);
                rowOffset += 0xa0L;
            } while (--rows != 0);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x0f, 9);

            dbHandle = db_LoadObject(0x10, 9, 1);
            (void)mem_Size(dbHandle);
            convertSource = (unsigned char huge *)mem_Lock(dbHandle);
            rowOffset = 0L;
            bandOffset = 0x5000L;
            rows = 0x80;
            do {
                pixels10 = convertDestination + bandOffset + rowOffset;
                ConvertMaskBitmap(pixels10, pixels10 + 0x80L,
                                  convertSource + rowOffset, 0x10, 0x10);
                rowOffset += 0xa0L;
            } while (--rows != 0);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x10, 9);

            dbHandle = db_LoadObject(0x11, 9, 1);
            (void)mem_Size(dbHandle);
            convertSource = (unsigned char huge *)mem_Lock(dbHandle);
            rowOffset = 0L;
            bandOffset = 0xa000L;
            rows = 0x80;
            do {
                pixels11 = convertDestination + bandOffset + rowOffset;
                ConvertMaskBitmap(pixels11, pixels11 + 0x80L,
                                  convertSource + rowOffset, 0x10, 0x10);
                rowOffset += 0xa0L;
            } while (--rows != 0);
            mem_Unlock(dbHandle);
            db_PurgeObject(0x11, 9);
            mem_Unlock(*overHandle);
        }
    } else {
        /* Copy the two variable-sized display objects into their own buffers. */
        tileDsp = 3;
        *nestHandle = mem_Alloc(mem_Size(dbHandle = db_LoadObject(0x0d, 9, 1)),
                                1, (char far *)"tilebufnest");
        copyDestination = (unsigned char far *)mem_Lock(*nestHandle);
        copySource = (unsigned char far *)mem_Lock(dbHandle);
        copySize = (unsigned int)mem_Size(dbHandle);
        _fmemcpy(copyDestination, copySource, copySize);
        mem_Unlock(dbHandle);
        mem_Unlock(*nestHandle);
        db_PurgeObject(0x0d, 9);

        *overHandle = mem_Alloc(mem_Size(dbHandle = db_LoadObject(0x0e, 9, 1)),
                                1, (char far *)"tilebufover");
        copyDestination = (unsigned char far *)mem_Lock(*overHandle);
        copySource = (unsigned char far *)mem_Lock(dbHandle);
        copySize = (unsigned int)mem_Size(dbHandle);
        _fmemcpy(copyDestination, copySource, copySize);
        mem_Unlock(dbHandle);
        mem_Unlock(*overHandle);
        db_PurgeObject(0x0e, 9);
    }
}

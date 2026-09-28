/* _SaveGame: copy the default file name, estimate space from the private
   eight-byte save records, and write them to the selected DOS file. */
struct DiskFreeInfo { unsigned totalClusters; unsigned freeClusters; unsigned sectorsPerCluster; unsigned bytesPerSector; };
struct SaveRecord { unsigned blockCount; unsigned blockSize; void far *buffer; };
extern char far Dx8[];
extern int far FileSelect(char far *path, int saveMode);
extern int far dos_getdiskfree(unsigned drive, struct DiskFreeInfo far *info);
extern int far access(char far *path, int mode);
extern int far lcreat(char far *path, int attribute);
extern int far lwrite(int handle, void far *data, unsigned length);
extern int far lclose(int handle);
extern int far unlink(char far *path);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void PopMsg(char far *text);

extern void far Error(char far *message, char far *detail);
extern int near errno;
extern char far * far sys_errlist[];
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned style);

extern int near gGameNeedsSaving;
extern int near rootWnd;
extern char __based(__segname("DGROUP")) _ctype_[];

int far SaveGame(int allowSave)
{
    int result;
    char errorText[100];
    char path[100];
    struct DiskFreeInfo disk;
    struct SaveRecord far *record;
    unsigned char far *defaultName;
    int driveChar;
    int drive;
    unsigned handle;
    unsigned written;
    unsigned recordBytesNeeded;
    unsigned freeBytes;
    unsigned long freeProduct;
    unsigned long sizeProduct;

    /* Private defaults and records are in the packet's segment-8 selector. */
    result = 0;
    path[0] = 0;
    defaultName = Dx8;
    defaultName += 0x9520;
    if (!defaultName || !defaultName[0] || !allowSave)
        goto finish;
    strcpy(path, (char far *)defaultName);
    if (!path[0] || !FileSelect(path, 1))
        goto finish;

    driveChar = path[0];
    drive = driveChar;
    if (_ctype_[driveChar + 1] & 2)
        drive = driveChar - 0x20;
    dos_getdiskfree((unsigned)(drive - '@'), &disk);

    record = (struct SaveRecord far *)(Dx8 + 0x9570);
    recordBytesNeeded = 0;
    while (record->blockSize != 0) {
        recordBytesNeeded += record->blockCount * record->blockSize;
        ++record;
    }

    freeProduct = (unsigned long)disk.freeClusters * disk.sectorsPerCluster;
    freeProduct *= disk.bytesPerSector;
    sizeProduct = (unsigned long)recordBytesNeeded * 125L;
    if (sizeProduct / 100L > freeProduct) {
        strcpy(path, (char far *)defaultName);
        goto finish;
    }
    freeBytes = (unsigned)freeProduct;

    if (access(path, 0) == 0)
        handle = (unsigned)lcreat(path, 1);
    else
        handle = (unsigned)lcreat(path, 0);
    if ((int)handle <= 0)
        goto io_error;

    record = (struct SaveRecord far *)(Dx8 + 0x9570);
    while (record->blockSize != 0) {
        written = record->blockCount * record->blockSize;
        if (lwrite((int)handle, record->buffer, written) == 0xffff)
            goto write_error;
        ++record;
    }
    lclose((int)handle);
    gGameNeedsSaving = 0;
    PopMsg(path);
    result = 1;
    goto finish;

write_error:
    path[0] = 0;
    sprintf(errorText, "Unable to write %s", path);
    Error(errorText, sys_errlist[errno]);
    lclose((int)handle);
    unlink(path);
    result = 0;
    goto finish;

io_error:
    sprintf(errorText, "Unable to create %s", path);
    Error(errorText, sys_errlist[errno]);
    result = 0;

finish:
    return result;
}

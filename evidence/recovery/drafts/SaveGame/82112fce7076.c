/* _SaveGame: copy the default file name, estimate space from the private
   eight-byte save records, and write them to the selected DOS file. */
struct DiskFreeInfo { unsigned totalClusters; unsigned freeClusters; unsigned sectorsPerCluster; unsigned bytesPerSector; };
struct SaveRecord { unsigned blockCount; unsigned blockSize; unsigned kind; unsigned aux; };
extern char far Dx8[];
extern int far FileSelect(char far *path, int saveMode);
extern int far dos_getdiskfree(unsigned drive, struct DiskFreeInfo far *info);
extern int far access(char far *path, int mode);
extern int far lcreat(char far *path, int attribute);
extern int far lwrite(int handle, void far *data, unsigned length);
extern int far lclose(int handle);
extern int far unlink(char far *path);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far PopMsg(char far *message);
extern void far Error(char far *message, char far *detail);
extern int near errno;
extern char far * far sys_errlist[];
extern int far MessageBox(int window, char far *text, char far *caption, unsigned type);
extern int near gGameNeedsSaving;
extern int near rootWnd;

int far SaveGame(int allowSave)
{
    int result;
    char path[116];
    char errorText[100];
    struct DiskFreeInfo disk;
    struct SaveRecord far *records;
    unsigned char far *defaultName;
    unsigned char far *recordBytes;
    unsigned char drive;
    unsigned i;
    unsigned handle;
    unsigned written;
    unsigned recordBytesNeeded;
    unsigned freeBytes;
    unsigned long freeProduct;
    unsigned long sizeProduct;

    /* Private defaults and records are in the packet's segment-8 selector. */
    result = 0;
    path[0] = 0;
    defaultName = (unsigned char far *)(Dx8 + 0x9520);
    if (!defaultName || !defaultName[0] || !allowSave)
        goto finish;
    strcpy(path, (char far *)defaultName);
    if (!path[0] || FileSelect(path, 1))
        goto finish;

    drive = (unsigned char)path[0];
    if (drive >= 'a' && drive <= 'z')
        drive = (unsigned char)(drive - 0x20);
    dos_getdiskfree((unsigned)(drive - '@'), &disk);

    records = (struct SaveRecord far *)(Dx8 + 0x9570);
    recordBytesNeeded = 0;
    for (i = 0; records[i].blockSize != 0; ++i)
        recordBytesNeeded += records[i].blockCount * records[i].blockSize;

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

    records = (struct SaveRecord far *)(Dx8 + 0x9570);
    for (i = 0; records[i].blockSize != 0; ++i) {
        recordBytes = (unsigned char far *)Dx8;
        written = (unsigned)(records[i].blockCount * records[i].blockSize);
        if (lwrite((int)handle, recordBytes, written) == 0xffff)
            goto write_error;
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

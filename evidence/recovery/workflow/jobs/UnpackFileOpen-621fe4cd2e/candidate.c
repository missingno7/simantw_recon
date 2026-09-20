/*
 * Open the packed input in the historical read-only DOS mode.  The handle
 * is stored beside the configured far unpack buffer; a failed open returns
 * zero, while a successful open initializes that buffer and reports one.
 */
extern int near unpackHandle;
extern int far open(char far *name, unsigned int mode);
extern void far UnpackInit(void far *buffer, unsigned int size);

int UnpackFileOpen(char far *name)
{
    char far *file;

    file = name;
    unpackHandle = open(file, 0x8000);
    if (unpackHandle <= 0)
        return 0;
    UnpackInit(((void far **)&unpackHandle)[-1], 0);
    return 1;
}

extern int near unpackHandle;
extern int far open(char far *name, unsigned int mode);
extern void far UnpackInit(void far *buffer, unsigned int size);

int far UnpackFileOpen(char far *name)
{
    unpackHandle = open(name, 0x8000);
    if (unpackHandle > 0) {
        UnpackInit(((void far **)&unpackHandle)[-1], 0);
        return 1;
    }
    return 0;
}

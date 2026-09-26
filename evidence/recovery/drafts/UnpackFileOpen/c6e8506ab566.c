/* Keep the opened handle in a local before testing it. */
extern int far open(char far *name, int mode);
extern void near UnpackInit(void far *source, unsigned int limit);
extern int near unpackHandle;
static unsigned int buffer_size = 0;
static void far *buffer_pointer = 0;
int far UnpackFileOpen(char far *name)
{
    int handle;
    handle = open(name, 0x8000);
    unpackHandle = handle;
    if (handle > 0) {
        UnpackInit(buffer_pointer, 0);
        return 1;
    }
    return 0;
}

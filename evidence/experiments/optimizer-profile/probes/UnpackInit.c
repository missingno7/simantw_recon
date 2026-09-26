/* Reset the saved unpack state and fill the configured far output buffer. */
extern unsigned char far *near unpackBuffer;
extern unsigned int near unpackSize;
extern unsigned int near unpackUsed;
extern unsigned int near unpackState;
extern void far *near unpackSource;
extern int near unpackLimit;
extern void far *_fmemset(void far *destination, int value,
                          unsigned int count);

void UnpackInit(void far *source, int limit)
{
    (void)_fmemset(unpackBuffer, 0x20, 0x0fee);
    unpackSize = 0x0fee;
    unpackUsed = 0;
    unpackState = 0;
    unpackSource = source;
    if (limit < 0)
        limit = 0x7fff;
    unpackLimit = limit;
}

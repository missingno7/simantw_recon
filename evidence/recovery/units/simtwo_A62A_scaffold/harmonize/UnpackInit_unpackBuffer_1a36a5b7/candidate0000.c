/*
 * Reset the unpacker for a new far source.  The configured output buffer is
 * filled with spaces, counters are cleared, and a negative requested limit
 * is replaced by the historical maximum positive word value.
 */
extern void far *near unpackBuffer;
extern unsigned int near unpackSize;
extern unsigned int near unpackUsed;
extern unsigned int near unpackState;
extern void far *near unpackSource;
extern int near unpackLimit;

void UnpackInit(void far *source, int limit)
{
    int i;

    for (i = 0; i < 0xfee; ++i)
        unpackBuffer[i] = 0x20;
    unpackSize = 0xfee;
    unpackUsed = 0;
    unpackState = 0;
    unpackSource = source;
    if (limit < 0)
        limit = 0x7fff;
    unpackLimit = limit;
}

extern unsigned char __based(__segname("PACK")) pack_buf[];
static unsigned char far * near packBuffer = pack_buf;
static void far * near unpackSource = 0;
static int near unpackLimit = 0;
static unsigned int near unpackSize = 0;
static unsigned int near unpackUsed = 0;
static unsigned int near unpackReadCount = 0;
static unsigned int near unpackInputCount = 0;
static unsigned int near unpackMatchLength = 0;
static int near unpackState = 0;
void UnpackInit(void far *source, int limit)
{
    int i;
    for (i = 0; i < 0xfee; ++i)
        packBuffer[i] = 0x20;
    unpackSize = 0xfee;
    unpackUsed = 0;
    unpackState = 0;
    unpackSource = source;
    if (limit < 0)
        limit = 0x7fff;
    unpackLimit = limit;
}

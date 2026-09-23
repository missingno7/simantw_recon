/* Initialize the LZSS state, including its zero-valued private words. */
extern unsigned char near rsrvptrs[];
static unsigned char far *history = (unsigned char far *)rsrvptrs;
extern unsigned int near pack_threshold;
static unsigned char far *packedInput = 0;
static unsigned int packedRemaining = 0;
static unsigned int historyPosition = 0;
static unsigned int bitBuffer = 0;
static unsigned int savedDx = 0;
static unsigned int savedCx = 0;
static int matchRemaining = 0;
static int unpackResume = 0;

void far UnpackInit(unsigned char far *input, int available)
{
    unsigned int i;
    for (i = 0; i < 0xfee; ++i)
        history[i] = 0x20;
    historyPosition = 0xfee;
    bitBuffer = 0;
    unpackResume = 0;
    packedInput = input;
    packedRemaining = available;
    if (packedRemaining < 0)
        packedRemaining = 0x7fff;
}

/* Decode one LZSS output chunk from the persistent packed stream. */
extern unsigned char near rsrvptrs[];
static unsigned char far *history = (unsigned char far *)rsrvptrs;
extern unsigned int near pack_threshold;
static unsigned char far *packedInput;
static unsigned int packedRemaining;
static unsigned int historyPosition;
static unsigned int bitBuffer;
static unsigned int savedDx;
static unsigned int savedCx;
static unsigned int matchRemaining;
static unsigned int unpackResume;

int far Unpack(unsigned char far *output, unsigned int outputCount)
{
    unsigned int produced;
    unsigned char flags;
    unsigned char first;
    unsigned char second;
    unsigned int sourcePosition;
    unsigned int length;
    unsigned char value;

    produced = 0;
    flags = (unsigned char)bitBuffer;
    while (outputCount != 0) {
        if ((flags & 0x100) == 0) {
            if (packedRemaining == 0)
                break;
            flags = *packedInput++;
            --packedRemaining;
            bitBuffer = flags | 0xff00;
        } else {
            bitBuffer >>= 1;
            flags = (unsigned char)bitBuffer;
        }
        if (flags & 1) {
            if (packedRemaining == 0)
                break;
            value = *packedInput++;
            --packedRemaining;
            *output++ = value;
            rsrvptrs[historyPosition] = value;
            historyPosition = (historyPosition + 1) & 0xfff;
            ++produced;
            --outputCount;
        } else {
            if (packedRemaining < 2)
                break;
            first = *packedInput++;
            second = *packedInput++;
            packedRemaining -= 2;
            sourcePosition = first | ((unsigned int)(second & 0xf0) << 4);
            length = (second & 0x0f) + pack_threshold;
            while (length != 0 && outputCount != 0) {
                value = rsrvptrs[sourcePosition];
                sourcePosition = (sourcePosition + 1) & 0xfff;
                *output++ = value;
                rsrvptrs[historyPosition] = value;
                historyPosition = (historyPosition + 1) & 0xfff;
                ++produced;
                --outputCount;
                --length;
            }
        }
        bitBuffer >>= 1;
    }
    unpackResume = 0;
    savedCx = bitBuffer;
    savedDx = 0;
    matchRemaining = 0;
    return produced;
}

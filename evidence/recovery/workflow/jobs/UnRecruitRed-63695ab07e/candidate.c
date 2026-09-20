/*
 * Walk the red-recruit records backward through the private Dx8 segment.
 * A record whose counter exceeds 0x7f is retired when its type byte is 6;
 * the loop stops at the first non-positive index.
 */
extern unsigned char far Dx8[];

void UnRecruitRed(void)
{
    int index;

    index = *(unsigned int far *)((char far *)Dx8 + 0x80f0);
    if (index <= 0)
        return;

    --index;
    while (index > 0) {
        unsigned int count;

        count = Dx8[0x2f62 + index];
        if (count > 0x7f && Dx8[0x2b78 + index] == 6)
            Dx8[0x2b78 + index] = 0;
        --index;
    }
}

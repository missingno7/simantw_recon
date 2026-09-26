/* Swap the two bytes in each successive word of a far buffer. The signed
   byte count rejects nonpositive spans; an odd positive span rounds up. */
void far FlipWords(unsigned char far *bytes, long length)
{
    long i;
    unsigned char saved;

    if (length <= 0L)
        return;

    for (i = 0L; i < length; i += 2L) {
        saved = bytes[i];
        bytes[i] = bytes[i + 1L];
        bytes[i + 1L] = saved;
    }
}

/* Reverse the byte order within each word of a 32-bit value. */
unsigned long FlipLong(unsigned long value)
{
    union { unsigned long all; unsigned word[2]; } bits;
    bits.all = value;
    bits.word[0] = (unsigned)((bits.word[0] << 8) | (bits.word[0] >> 8));
    bits.word[1] = (unsigned)((bits.word[1] << 8) | (bits.word[1] >> 8));
    return bits.all;
}

/* Swap the byte order of a 16-bit word using its byte representation. */
unsigned FlipWord(unsigned value)
{
    union { unsigned word; unsigned char byte[2]; } bits;
    bits.word = value;
    {
        unsigned char first = bits.byte[0];
        bits.byte[0] = bits.byte[1];
        bits.byte[1] = first;
    }
    return bits.word;
}

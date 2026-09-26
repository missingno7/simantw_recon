/* Byte-reverse the two bytes of a word. */
unsigned FlipWord(unsigned value)
{
    return (unsigned)((value << 8) | (value >> 8));
}

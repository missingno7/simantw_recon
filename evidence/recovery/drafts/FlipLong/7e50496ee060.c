/* Reverse the byte order separately in each word of a long. */
unsigned long FlipLong(unsigned long value)
{
    unsigned *words = (unsigned *)&value;
    words[0] = (unsigned)((words[0] << 8) | (words[0] >> 8));
    words[1] = (unsigned)((words[1] << 8) | (words[1] >> 8));
    return value;
}

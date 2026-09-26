/* Copy bytes forward from the source far pointer to the destination. */
void far BlockMove(unsigned char far *source, unsigned char far *destination, unsigned int count)
{
    unsigned int i;
    for (i = 0; i < count; ++i) destination[i] = source[i];
}

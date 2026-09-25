void far BlockMove(unsigned char far *source, unsigned char far *destination,
                   unsigned int count)
{
    while (count--)
        *destination++ = *source++;
}

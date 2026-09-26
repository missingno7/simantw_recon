/* Move a counted far byte range, copying backward when the destination
   begins within the source range and forward otherwise. */
void far MaMemMove(unsigned char far *destination,
                   unsigned char far *source,
                   unsigned long length)
{
    if (length == 0UL)
        return;

    if (destination < source) {
        while (length != 0UL) {
            *destination++ = *source++;
            --length;
        }
    } else {
        destination += length - 1UL;
        source += length - 1UL;
        while (length != 0UL) {
            *destination-- = *source--;
            --length;
        }
    }
}
